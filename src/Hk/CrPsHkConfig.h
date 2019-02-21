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
 * In order to establish the link between a housekeeping report and the RDL slot where its
 * definition is stored, the following is done:
 * - An array is defined with size #HK_MAX_SID (the maximum value of a SID)
 * - The j-th element of this array is equal to -1 if the report with SID equal to j is not
 *   in the RDL (i.e. if it is not being generated) and is otherwise equal to the index of the
 *   RDL slot where the report is defined.
 * .
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
 * RDL as part of its initialization using function #CrPsHkConfigHkRep. For packets defined in the
 * CORDET Editor, an initializers with the list of their parameter identifiers is generated in
 * CrPsPcktHk.h; see #CrPsHkTestCase1 for an example).
 */
void CrPsHkConfigInit();

/**
 * Clear the argument Stucture Identifier (SID) from the RDL.
 * This function retrieves the index of the RDL slot where the argument SID is defined and
 * then removes the definition from the RDL.
 * The SID is removed by setting the 'sid' field of the RDL entry to zero.
 * If the argument SID is not defined in the RDL, then the behaviour of the function is undefined.
 *
 * @param sid the Structure Identifier (SID) to be removed from the RDL
 */
void CrPsHkConfigClearSid(CrPsSID_t sid);

/**
 * Configure a new housekeeping report and store its definition in the RDL.
 * The packet is defined in terms of: structure identifier (SID), number of items,
 * collection interval, and list of identifiers of items.
 * The initial enable state of the newly created packet is set to: 'disabled'.
 * The packet is defined at the rdlPos-th slot in the RDL.
 * No check is done to verify that this slot is free and no checks are done on the
 * legality of the other function parameters (out-of-limit values might result
 * in memory corruption).
 *
 * @constraint Since the collection interval of housekeeping packets is defined as an
 * integer number of HK_COLLECT_PER periods, housekeeping reports shall be loaded into
 * an OutManager which is activated with a period of length HK_COLLECT_PER
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
void CrPsHkConfigHkRep(FwSmDesc_t rep, short int rdlPos, CrPsSID_t sid, CrPsNPar_t nOfItems,
                                CrFwDestSrc_t dest, CrPsCycleCnt_t collectionInt, CrPsParId_t* parId);

/**
 * Collect the value of the data pool items in the packet defined in the <code>rdlSlot</code>-th slot of the RDL
 * and place their values in the argument report (assumed to be a housekeeping report).
 * The argument parameter rdlSlot must be in the range 0..(HK_N_REP_DEF-1).
 * If it is out-of-range, the application behaviour becomes unpredictable.
 *
 * @param rdlSlot the index of the RDL slot where the packet to be updated is located (the first slot has
 * index zero)
 * @param hkRep the housekeeping report
 */
void CrPsHkConfigUpdateRep(short int rdlSlot, FwSmDesc_t hkRep);

/**
 * Get the index of the RDL slot where the report with the argument SID is stored (the index of the first slot
 * is zero).
 * If no report with the argument SID is defined in the RDL, a value of -1 is returned.
 *
 * @param sid the structure identifier (SID)
 * @return the index of the RDL slot where the report with the argument SID is stored (the index of the first slot
 * is zero)
 */
short int CrPsHkConfigGetRdlSlot(CrPsSID_t sid);

/**
 * Get the index of a free RDL slot.
 * If no free RDL slot can be found, the function returns -1.
 *
 * @return the index of a free RDL slot or -1 if the RDL is full
 */
short int CrPsHkConfigGetFreeRdlSlot();

/*----------------------------------------------------------------------------*/
#endif /* CRPSHKCONFIG_H_ */
