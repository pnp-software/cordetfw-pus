/**
 * @file CrPsHkTestCases.h
 * @ingroup PUSTestsuite
 *
 * @brief Declaration of the test cases for the Housekeeping Service.
 * The test cases in this module depend on each other and must be executed in the order
 * in which they are declared.
 *
 * @author Alessandro Pasetti  <pasetti@pnp-software.com>
 *
 * @copyright P&P Software GmbH, 2018 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#ifndef CRPS_HKTESTCASES_H_
#define CRPS_HKTESTCASES_H_

/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
/* Include PUS Extension Files */
#include "Pckt/CrPsPcktHk.h"

/**
 * Test the functions in the housekeeping configuration module (CrPsHkConfig.h).
 * The following actions are performed:
 * - Initialize the housekeeping service and then verify the operation to get a free slot in the RDL
 * - Use function #CrPsHkConfigHkRep to load the pre-defined HK reports (SID #LEN_HK_REP_SID_HK_CNT
 *   and #LEN_HK_REP_SID_N_OF_EVT) and then verify that the corresponding SIDs are found in
 *   the RDL at the expected location
 * - Fill up the RDL and then verify that no free RDL slot can be retrieved
 * - Clear all SIDs but those pre-defined for testing purposes by the PUS Extension and verify success
 *   of clear operation
 * .
 * @verify Hk Config, Operation to set the define report in the RDL
 * @verify Hk Config, Operation to clear a SID from the RDL
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsHkTestCase1();

/**
 * Verify the start failure cases for the (3,1) command to create a new housekeeping report.
 * The following actions are performed:
 * - Fill up the RDL and then execute a (3,1) command and verify that the command fails with a
 *   (1,4) report with error code VER_FULL_RDL
 * - Bring the RDL back to its original state and then execute a (3,1) command with an illegal SID
 *   and verify that the command is rejected with a (1,4) report with error code VER_ILL_SID
 * - Execute a (3,1) command with an SID equal to zero
 *   and verify that the command is rejected with a (1,4) report with error code VER_ILL_SID
 * - Execute a (3,1) command with an illegal parameter identifier
 *   and verify that the command is rejected with a (1,4) report with error code VER_ILL_DI_ID
 * - Execute a (3,1) command with a parameter identifier equal to zero
 *   and verify that the command is rejected with a (1,4) report with error code VER_ILL_DI_ID
 * - Execute a (3,1) command with a SID which is already in use
 *   and verify that the command is rejected with a (1,4) report with error code VER_SID_IN_USE
 * - Execute a (3,1) command with an illegal number of data item identifiers
 *   and verify that the command is rejected with a (1,4) report with error code VER_ILL_NID
 * .
 * @verify Create HK Command, Start Failure with error code VER_FULL_RDL
 * @verify Create HK Command, Start Failure with error code VER_ILL_SID
 * @verify Create HK Command, Start Failure with error code VER_ILL_DP_ID
 * @verify Create HK Command, Start Failure with error code VER_ILL_NID
 * @verify Create HK Command, Start Failure with error code VER_SID_IN_USE
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsHkTestCase2();

/**
 * Verify execution of a nominal command to create a new housekeeping report and verify the execution of
 * the report is has loaded.
 * The following actions are performed:
 * - One (3,1) command is created to load a HK report with two data pool items and it is verified that
 *   the report is loaded in the OutManager
 * - The OutManager is executed and it is verified that no HK report is generated (because, by default,
 *   it is disabled)
 * - The HK report is enabled in the RDL and then the OutManager is executed again and it is verified
 *   that it is generated and that its destination is the same as the source of the (3,1) command
 * - It is verified that the report is generated at each execution of the OutManager and that the data
 *   it carries are updated at each generation
 * - The generation period is modified in the RDL and it is verified that a matching change in the generation
 *   frequency of the report occurs
 * - The generation period and the cycle counter are set to zero and it is verified that the report is
 *   only generated once (one-shot mode)
 * .
 * @verify Create HK Command, Successful execution
 * @verify HK Report, Execution while disabled
 * @verify HK Report, Execution while enabled with collection period equal to 1
 * @verify HK Report, Execution while enabled with collection period greater than 1
 * @verify HK Report, Execution while enabled with collection period equal to zero
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsHkTestCase3();

/**
 * Verify execution of a command to enable a housekeeping report.
 * The following actions are performed:
 * - One (3,5) command is created carrying 2 legal SIDs neither of which is loaded in the RDL and it is verified
 *   that executing the command twice results in the generation of two (1,6) and one (1,8) reports
 * - One (3,5) command is created carrying one legal and loaded SID and one out-of-range SID and it is verified
 *   that executing the command twice results in the first SID being enabled
 * - One (3,5) command is created carrying two loaded SIDs and it is verified
 *   that executing the command twice results in the both SIDs being enabled
 * .
 * @verify Enable Generation of a HK Report Structure, All SIDs are not loaded in the RDL
 * @verify Enable Generation of a HK Report Structure, Some SIDs are loaded in the RDL and others are illegal
 * @verify Enable Generation of a HK Report Structure, All SIDs are loaded in the RDL
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsHkTestCase4();

/**
 * Verify execution of a command to disable a housekeeping report.
 * The following actions are performed:
 * - One (3,5) command is created carrying 2 legal SIDs neither of which is loaded in the RDL and it is verified
 *   that executing the command twice results in the generation of two (1,6) and one (1,8) reports
 * - One (3,5) command is created carrying one legal and loaded SID and one out-of-range SID and it is verified
 *   that executing the command twice results in the first SID being disabled
 * - One (3,5) command is created carrying two loaded SIDs and it is verified
 *   that executing the command twice results in the both SIDs being disabled
 * .
 * @verify Disable Generation of a HK Report Structure, All SIDs are not loaded in the RDL
 * @verify Disable Generation of a HK Report Structure, Some SIDs are loaded in the RDL and others are illegal
 * @verify Disable Generation of a HK Report Structure, All SIDs are loaded in the RDL
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsHkTestCase5();

/**
 * Verify execution of a command to delete a housekeeping report.
 * The following actions are performed:
 * - One (3,3) command is created carrying 3 SIDs of which one is not loaded, one is illegal and one is enabled
 *   and it is verified
 *   that executing the command three results in the generation of three (1,6) and one (1,8) reports
 * - One (3,3) command is created carrying one legal, loaded and disabled SID and it is verified
 *   that executing the command results in the SID being deleted
 * .
 * @verify Delete HK Report Structure, SID is not loaded in the RDL
 * @verify Delete HK Report Structure, SID is illegal
 * @verify Delete HK Report Structure, SID is enabled
 * @verify Delete HK Report Structure, SID is loaded and disabled
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsHkTestCase6();

/**
 * Verify execution of a command to modify the collection period of a housekeeping report.
 * The following actions are performed:
 * - One (3,25) report is created and loaded with a collection period of 1 and it is verified that
 *   the report is generated at each execution of its OutManager
 * - One (3,31) command is created carrying the SID of the report created at the previous step,
 *   one out-of-range SID, and
 *   one SID which is within range but not currently loaded; the command is executed and it is
 *   verified that the period of the housekeeping report has been modified as expected
 * .
 * @verify Modify HK Report Collection Interval, SID is loaded in the RDL
 * @verify Modify HK Report Collection Interval, SID is not loaded in the RDL
 * @verify Modify HK Report Collection Interval, SID is out-of-range
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsHkTestCase7();

/**
 * Create a (3,1) command for test purposes.
 * The command is configured according to the function parameters and:
 * - Source and destination are both set to zero.
 * - The acknowledge flags are set to: 'no acknowledge'.
 * - The sequence and group numbers are set to 1.
 * - The collection interval is set to 1
 * .
 * @param sid the SID of the new command
 * @param N1 the number of data items in the new command
 * @param parId the array holding the identifiers of the data items in the command
 *
 */
FwSmDesc_t CrPsHkTestCaseMake3s1(CrPsSID_t sid, CrPsNPar_t N1, CrPsParId_t* parId);

/**
 * Create a (3,3) command for test purposes.
 * The command is configured according to the function parameters and:
 * - Source and destination are both set to zero.
 * - The acknowledge flags are set to: 'no acknowledge'.
 * - The sequence and group numbers are set to 1.
 * - The collection interval is set to 1
 * .
 * @param sid the SIDs to be deleted
 * @param N1 the number of SIDs in the command
 *
 */
FwSmDesc_t CrPsHkTestCaseMake3s3(CrPsSID_t* sid, CrPsNSID_t N1);

/**
 * Create a (3,5) command for test purposes.
 * The command is configured according to the function parameters and:
 * - Source and destination are both set to zero.
 * - The acknowledge flags are set to: 'no acknowledge'.
 * - The sequence and group numbers are set to 1.
 * - The collection interval is set to 1
 * .
 * @param sid the SIDs to be enabled
 * @param N1 the number of SIDs in the command
 *
 */
FwSmDesc_t CrPsHkTestCaseMake3s5(CrPsSID_t* sid, CrPsNSID_t N1);

/**
 * Create a (3,6) command for test purposes.
 * The command is configured according to the function parameters and:
 * - Source and destination are both set to zero.
 * - The acknowledge flags are set to: 'no acknowledge'.
 * - The sequence and group numbers are set to 1.
 * - The collection interval is set to 1
 * .
 * @param sid the SIDs to be disabled
 * @param N1 the number of SIDs in the command
 *
 */
FwSmDesc_t CrPsHkTestCaseMake3s6(CrPsSID_t* sid, CrPsNSID_t N1);

/**
 * Create a (3,31) command for test purposes.
 * The command is configured according to the function parameters and:
 * - Source and destination are both set to zero.
 * - The acknowledge flags are set to: 'no acknowledge'.
 * - The sequence and group numbers are set to 1.
 * - The collection interval is set to 1
 * .
 * @param sid the SIDs to be  whose collection interval (period) is to
 * be modified
 * @param period the modified collection intervals (period)
 * @param N1 the number of SIDs whose collection interval (period) is to
 * be modified
 *
 */
FwSmDesc_t CrPsHkTestCaseMake3s31(CrPsSID_t* sid, CrPsCycleCnt_t* period, CrPsNSID_t N1);




#endif /* CRPS_HKTESTCASES_H_ */
