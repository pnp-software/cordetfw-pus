/**
 * @file
 *
 * Interface for configuring the Housekeeping Reporting Service.
 *
 * Configuration operations are defined to:
 * - Initialize the data structures used by the Housekeeping Service
 * - Manage the enable status of a SID
 * .
 *
 * This module operates on the <i>Report Definition List</i> (RDL).
 * The RDL holds #HK_N_REP_DEF <i>Report Definitions</i>.
 * The value of #HK_N_REP_DEF represents the maximum number of housekeeping
 * reports which may be defined at any given time.
 * Each Report Definition defines one housekeeping/diagnostic report in terms of the
 * following items:
 * - Structure identifier (SID, Integer in range: 1..#HK_MAX_SID). A value of zero indicates
 *   that the Report Definition is empty.
 * - Collection period in units of HK_COLLECT_PER (Positive integer for periodic reports
 *   or zero for one-shot reports)
 * - Cycle counter (Integer in the range: 0..CollectonPeriod-1)
 * - Enable flag (true if generation of the report is enabled
 * - The identifier of the destination application to which the report is sent
 * - The number of simply-commutated data items in the report (Integer in range: 1..#HK_MAX_N_SIMPLE)
 * - List of super-commutated sample repetition numbers (rep[1] .. rep[nGroup]),  the number of groups
 *   is in the range: 0..HK_MAX_N_GR and each repetition number is in the range: 1..HK_MAX_REP
 * - List of numbers nRep[1] .. nRep[nGroup] of data items in each super-commutated group (each nRep[i]
 *   is in range: 1..HK_MAX_N_REP)
 * - List of identifiers of data items in the report (not more than HK_MAX_N_ITEMS
 *   data items and each identifier is in range: 1..HK_MAX_ID)
 * - The identifier of the sampling buffer holding the super-commutated data item values
 *   (an integer in the range: 1..HK_N_SAMP_BUF)
 * .
 * Some of RDL data structures are defined in the data pool.
 * The others are defined in this module.
 *
 * Each Report Definition in the RDL holds the definition of a pending (3,25) or (3,26) report.
 * The pending (3,25) or (3,26) report is represented by an object of type #FwSmDesc_t.
 * The report object needs a link to the RDL slot where its definition resides.
 * This link is established through the RDL Index Buffer maintained in this module.
 * This consists of an array of #HK_N_REP_DEF elements with the i-th element having the value i.
 * When a new (3,25) or (3,26) report is created and its definition is stored in the i-th
 * element of the RDL Index Buffer, a pointer to this element is passed to the FwSmDesc_t object
 * representing the (3,25) or (3,26) report.
 * This module offers function to set up the link between a (3,25) or (3,26) report and its RDL index
 * and to retrieve this link.
 *
 * @limitation The over-sampling mechanism for housekeeping reports is not supported
 *
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 *
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */
#ifndef CRPSHKCONFIG_H_
#define CRPSHKCONFIG_H_

#include "CrPsTypes.h"

/**
 * Initialize the Housekeeping Service.
 * This function must be called before the houekeeping service can be used in the host application.
 * The function should typically be called as part of the initialization of the host application.
 * The following actions are performed:
 * - Verify that the range of data pool identifiers for the parameters and the variables do not
 *   overlap and set the application error code to #crPsDpParVarIdOverlap if they do
 * - The RDL is initialized to be empty
 * - Instantiate the Ready Check Procedures (one for each RDL slot)
 * .
 * @constraint If an application needs pre-defined housekeeping reports, it must define them in the
 * RDL as part of its initialization (it can use for this purpose the initializers generated in
 * CrPsPcktHk.h by the CORDET Editor; see #CrPsHkTestCase1 for an example).
 */
void CrPsHkConfigInit();

/**
 * Set the enable status of the argument structure identifier (SID).
 * This function scans all the Report Definitions in the RDL and, if it finds
 * one with the SID equal to the argument SID, it sets its enable status to
 * <code>enableStatus</code> and returns the slot occupied by the SID in the RDL (starting
 * from zero).
 * If no report definition with the argument SID is found, the function returns -1.
 *
 * @param sid the Structure Identifier (SID)
 * @param enableStatus the enable status
 * @return the slot (starting from zero) where the argument SID is stored in the RDL or -1
 * if the argument SID is not found in the RDL
 */
int CrPsHkConfigSetSidEnableStatus(CrPsSID_t sid, CrFwBool_t enableStatus);

/**
 * Clear the argument Stucture Identifier (SID) from the RDL.
 * This function scans all the Report Definitions in the RDL and, if it finds
 * one with the SID equal to the argument SID, it removes it from the RDL.
 * The SID is removed by setting the 'sid' field of the RDL entry to zero.
 * The function returns the index of the RDL slot where the argument SID has been found
 * (the first slot has index 0) or -1 if the argument SID was not found in the RDL.
 *
 * @param sid the Structure Identifier (SID) to be removed from the RDL
 * @return the slot (starting from zero) where the argument SID is stored in the RDL or -1
 * if the argument SID is not found in the RDL
 */
int CrPsHkConfigClearSid(CrPsSID_t sid);

/**
 * Define a new packet in the Report Definition List (RDL).
 * The packet is defined in terms of: structure identifier (SID), number of items,
 * collection interval, and list of identifiers of items.
 * The initial enable state of the newly created packet is set to: 'disabled'.
 * The packet is defined at the rdlPos-th slot in the RDL.
 * No check is done to verify that this slot is free.
 *
 * @constraint The housekeeping reports shall be loaded into an OutManager which is activated
 * with a period of length HK_COLLECT_PER
 *
 * @param rdlPos the slot in the RDL where the new packet is loaded (the first slot has index zero)
 * @param sid the Structure Identifier (SID) of the new packet
 * @param nOfItems the number of items in the new packet
 * @param collectionInt the collection interval for the new packet (expressed as an integer
 * number of collection periods of length HK_COLLECT_PER)
 * @param dest the destination of the new packet
 * @param parId the array holding the identifiers of the <code>nOfItems</code> items in the
 * new packet
 * @return the slot (starting from zero) where the argument SID has been inserted in the RDL or -1
 * if no empty slot in the RDL has been found
 */
void CrPsHkConfigLoadSidDef(unsigned int rdlPos, CrPsSID_t sid, CrPsNPar_t nOfItems, CrFwDestSrc_t dest,
                                        CrPsCycleCnt_t collectionInt, CrPsParId_t* parId);

/**
 * Collect the value of the data pool items in the packet defined in the <code>rdlSlot</code>-th slot of the RDL
 * and place their values in sequence in the array <code>target</code>.
 * The argument parameter rdlSlot must be in the range 0..(HK_N_REP_DEF-1).
 * If it is out-of-range, the application behaviour becomes unpredictable.
 *
 * @param rdlSlot the index of the RDL slot where the packet to be updated is located (the first slot has
 * index zero)
 * @param target the array where the values of the data pool items in the packet in the RDL slot
 */
void CrPsHkConfigUpdateRep(unsigned int rdlSlot, void* target);

/**
 * Get the index of the RDL slot where the report with the argument SID is stored (the index of the first slot
 * is zero).
 * If no report with the argument SID is defined in the RDL, a value of -1 is returned.
 *
 * @param sid the structure identifier (SID)
 * @return the index of the RDL slot where the report with the argument SID is stored (the index of the first slot
 * is zero)
 */
int CrPsHkConfigGetRdlSlot(CrPsSID_t sid);

/**
 * Get the index of a free RDL slot.
 * If no free RDL slot can be found, the function returns -1.
 *
 * @return the index of a free RDL slot or -1 if the RDL is full
 */
int CrPsHkConfigGetFreeRdlSlot();

/**
void CrPsHkConfigLinkRepToRdlIndexBuf(FwSmDesc_t rep);

/*----------------------------------------------------------------------------*/
#endif /* CRPSHKCONFIG_H_ */
