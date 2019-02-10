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
 * - All pre-defined SIDs are loaded in the RDL
 * .
 * @constraint If an application needs some housekeeing packets to be enabled by default, it
 * must enable them (using function #CrPsHkConfigSetSidEnableStatus) as part of its initialization
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
 * The initial enable state of the newly created packet is: 'disabled'.
 *
 * The function scans the RDL until it finds and empty slot and then fills it
 * with the argument packet definition.
 * The function returns the index of the slot where new packet has been defined
 * (the index of the first slot is zero) or it returns -1 if no empty slot was found.
 *
 * @param sid the Structure Identifier (SID) of the new packet
 * @param nOfItems the number of items in the new packet
 * @param collectionInt the collection interval for the new packet (expressed as an integer
 * number of collection periods of length HK_COLLECT_PER)
 * @param parId the array holding the identifiers of the <code>nOfItems</code> items in the
 * new packet
 * @return the slot (starting from zero) where the argument SID has been inserted in the RDL or -1
 * if no empty slot in the RDL has been found
 */
int CrPsHkConfigLoadSidDef(CrPsSID_t sid, CrPsNPar_t nOfItems,
                        CrPsCollectInterval_t collectionInt, CrPsParId_t* parId);


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
CrPsHkConfigUpdateRepDef(unsigned int rdlSlot, void* target);




/*----------------------------------------------------------------------------*/
#endif /* CRPSHKCONFIG_H_ */
