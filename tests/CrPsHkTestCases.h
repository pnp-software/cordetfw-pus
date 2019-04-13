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
 * @verify Config, Hk, Operation to set the define report in the RDL
 * @verify Config, Hk, Operation to clear a SID from the RDL
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
 * @verify Command, Create HK, Start Failure with error code VER_FULL_RDL
 * @verify Command, Create HK, Start Failure with error code VER_ILL_SID
 * @verify Command, Create HK, Start Failure with error code VER_ILL_DP_ID
 * @verify Command, Create HK, Start Failure with error code VER_ILL_NID
 * @verify Command, Create HK, Start Failure with error code VER_SID_IN_USE
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsHkTestCase2();

/**
 * Verify execution of a nominal command to create a new housekeeping report and verify the execution of
 * the report it has loaded.
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
 * @verify Command, Create HK, Successful execution
 * @verify Report, Hk, Execution while disabled
 * @verify Report, Hk, Execution while enabled with collection period equal to 1
 * @verify Report, Hk, Execution while enabled with collection period greater than 1
 * @verify Report, Hk, Execution while enabled with collection period equal to zero
 * @verify Data Pool, HkIsEnabled
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
 * - One (3,7) command is created carrying one SID and it is verified
 *   that executing the command once results in the SID being enabled
 *   and that the SID's destination matches the command's source
 * .
 * @verify Command, Enable Generation of a HK Report Structure, All SIDs are not loaded in the RDL
 * @verify Command, Enable Generation of a HK Report Structure, Some SIDs are loaded in the RDL and others are illegal
 * @verify Command, Enable Generation of a HK Report Structure, All SIDs are loaded in the RDL
 * @verify Command, Enable Generation of a Diagnostic Report Structure, One loaded SID
 * @verify Data Pool, hkDest
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
 * - One (3,8) command is created carrying one SID and it is verified
 *   that executing the command once results in the SID being disabled
 * .
 * @verify Command, Disable Generation of a HK Report Structure, All SIDs are not loaded in the RDL
 * @verify Command, Disable Generation of a HK Report Structure, Some SIDs are loaded in the RDL and others are illegal
 * @verify Command, Disable Generation of a HK Report Structure, All SIDs are loaded in the RDL
 * @verify Command, Disable Generation of a Diagnostic Report Structure, One loaded SID
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
 * - One (3,4) command is created carrying one legal, loaded and disabled SID and it is verified
 *   that executing the command results in the SID being deleted
 * .
 * @verify Command, Delete HK Report Structure, SID is not loaded in the RDL
 * @verify Command, Delete HK Report Structure, SID is illegal
 * @verify Command, Delete HK Report Structure, SID is enabled
 * @verify Command, Delete HK Report Structure, SID is loaded and disabled
 * @verify Command, Delete Diagnostic Report Structure, SID is loaded and disabled
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
 * - One (3,32) command is created carrying the SID of the report created at the previous step;
 *   the command is executed and it is
 *   verified that the period of the housekeeping report has been modified as expected
 * .
 * @verify Command, Modify HK Report Collection Interval, SID is loaded in the RDL
 * @verify Command, Modify HK Report Collection Interval, SID is not loaded in the RDL
 * @verify Command, Modify HK Report Collection Interval, SID is out-of-range
 * @verify Command, Modify Diagnostic Report Collection Interval, SID is loaded in the RDL
 * @verify Data Pool, HkPeriod
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsHkTestCase7();

/**
 * Verify execution of a command to generate a one-shot housekeeping report.
 * The following actions are performed:
 * - One (3,25) report is created and loaded; it is left disabled and it is verified that, when
 *   its OutManager is executed, the report is not generated
 * - One (3,27) command is created carrying the SID of the report created at the previous step,
 *   one out-of-range SID, and
 *   one SID which is within range but not currently loaded; the command is executed and then
 *   the OutManager of the report is executed and it is
 *   verified that the report is generated
 * .
 * @verify Command, Generate One-Shot Report for HK Parameters, SID is loaded in the RDL
 * @verify Command, Generate One-Shot Report for HK Parameters, SID is not loaded in the RDL
 * @verify Command, Generate One-Shot Report for HK Parameters, SID is out-of-range
 * @verify Data Pool, HkCycleCnt
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsHkTestCase8();

/**
 * Verify execution of a command to generate a Housekeeping Parameter Report Structure Report.
 * The following actions are performed:
 * - Two (3,25) reports are created and loaded
 * - One (3,9) command is created carrying the SIDs of the two reports and an illegal SID
 *   and it is verified that execution of the command causes two (3,10) reports to be generated
 *   and that their content matches the definition of the SIDs
 * - It is verified that a (1,6) report is generated in response to the illegal SID
 * .
 * @verify Report, Housekeeping Parameter Report Structure, SID is loaded in the RDL
 * @verify Report, Housekeeping Parameter Report Structure, SID is illegal
 * @verify Command, Housekeeping Parameter Report Structure Report
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsHkTestCase9();

/**
 * Verify execution of a nominal command to create a new diagnostic report and verify the execution of
 * the diagnostic report it has loaded.
 * The following actions are performed:
 * - One (3,2) command is created to load a HK report with two data pool items and it is verified that
 *   the report is loaded in the OutManager
 * - The report is enabled and then the OutManager is executed and it is verified that the HK report
 *   is generated
 * .
 * @verify Command, Create Diagnostic Report, Successful execution
 * @verify Report, Diagnostic, Execution while enabled with collection period equal to 1
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsHkTestCase10();

/**
 * Verify execution of a command to generate a one-shot diagnostic report.
 * The following actions are performed:
 * - One (3,26) report is created and loaded; it is left disabled and it is verified that, when
 *   its OutManager is executed, the report is not generated
 * - One (3,28) command is created carrying the SID of the report created at the previous step;
 *   the command is executed and then the OutManager of the report is executed and it is
 *   verified that the report is generated
 * .
 * @verify Command, Generate One-Shot Report for Diagnostic Parameters, SID is loaded in the RDL
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsHkTestCase11();

/**
 * Verify execution of a command to generate a Diagnostic Parameter Report Structure Report.
 * The following actions are performed:
 * - One (3,26) report is created and loaded
 * - One (3,11) command is created carrying the SID of the report
 *   and it is verified that execution of the command causes one (3,12) report to be generated
 *   and that its content matches the definition of the SID
 * .
 * @verify Command, Report Diagnostic Parameter Report Structure, SID is loaded in the RDL
 * @verify Report, Diagnostic Parameter Report Structure
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsHkTestCase12();

/**
 * Create a (3,1) command for test purposes.
 * The command is configured according to the function parameters and:
 * - Source is set to EVT_DEST (this is the destination to which
 *   the Stub OutStream CrPsOutStreamStub.h is attached).
 * - Destination is set to zero.
 * - The acknowledge flags are set to: 'no acknowledge'.
 * - The sequence and group numbers are set to 1.
 * - The collection interval is set to 1
 * .
 * @param sid the SID of the new command
 * @param N1 the number of data items in the new command
 * @param parId the array holding the identifiers of the data items in the command
 * @return The (3,1) command
 */
FwSmDesc_t CrPsHkTestCaseMake3s1(CrPsSID_t sid, CrPsNPar_t N1, CrPsParId_t* parId);

/**
 * Create a (3,3) command for test purposes.
 * The command is configured according to the function parameters and:
 * - Source is set to EVT_DEST (this is the destination to which
 *   the Stub OutStream CrPsOutStreamStub.h is attached).
 * - Destination is set to zero.
 * - The acknowledge flags are set to: 'no acknowledge'.
 * - The sequence and group numbers are set to 1.
 * .
 * @param sid the SIDs to be deleted
 * @param N1 the number of SIDs in the command
 * @return The (3,3) command
 */
FwSmDesc_t CrPsHkTestCaseMake3s3(CrPsSID_t* sid, CrPsNSID_t N1);

/**
 * Create a (3,5) command for test purposes.
 * The command is configured according to the function parameters and:
 * - Source is set to EVT_DEST (this is the destination to which
 *   the Stub OutStream CrPsOutStreamStub.h is attached).
 * - Destination is set to zero.
 * - The acknowledge flags are set to: 'no acknowledge'.
 * - The sequence and group numbers are set to 1.
 * .
 * @param sid the SIDs to be enabled
 * @param N1 the number of SIDs in the command
 * @return The (3,5) command
 */
FwSmDesc_t CrPsHkTestCaseMake3s5(CrPsSID_t* sid, CrPsNSID_t N1);

/**
 * Create a (3,6) command for test purposes.
 * The command is configured according to the function parameters and:
 * - Source is set to EVT_DEST (this is the destination to which
 *   the Stub OutStream CrPsOutStreamStub.h is attached).
 * - Destination is set to zero.
 * - The acknowledge flags are set to: 'no acknowledge'.
 * - The sequence and group numbers are set to 1.
 * .
 * @param sid the SIDs to be disabled
 * @param N1 the number of SIDs in the command
 * @return The (3,6) command
 */
FwSmDesc_t CrPsHkTestCaseMake3s6(CrPsSID_t* sid, CrPsNSID_t N1);

/**
 * Create a (3,9) command for test purposes.
 * The command is configured according to the function parameters and:
 * - Source is set to EVT_DEST (this is the destination to which
 *   the Stub OutStream CrPsOutStreamStub.h is attached).
 * - Destination is set to zero.
 * - The acknowledge flags are set to: 'no acknowledge'.
 * - The sequence and group numbers are set to 1.
 * .
 * @param sid the SIDs for which structure reports should be generated
 * @param N1 the number of SIDs for which structure reports are to be
 * generated
 * @return The (3,9) command
 */
FwSmDesc_t CrPsHkTestCaseMake3s9(CrPsSID_t* sid, CrPsNSID_t N1);

/**
 * Create a (3,27) command for test purposes.
 * The command is configured according to the function parameters and:
 * - Source is set to EVT_DEST (this is the destination to which
 *   the Stub OutStream CrPsOutStreamStub.h is attached).
 * - Destination is set to zero.
 * - The acknowledge flags are set to: 'no acknowledge'.
 * - The sequence and group numbers are set to 1.
 * .
 * @param sid the SIDs to be generated in one-shot mode
 * @param N1 the number of SIDs in the command
 * @return The (3,27) command
 */
FwSmDesc_t CrPsHkTestCaseMake3s27(CrPsSID_t* sid, CrPsNSID_t N1);

/**
 * Create a (3,31) command for test purposes.
 * The command is configured according to the function parameters and:
 * - Source is set to EVT_DEST (this is the destination to which
 *   the Stub OutStream CrPsOutStreamStub.h is attached).
 * - Destination is set to zero.
 * - The acknowledge flags are set to: 'no acknowledge'.
 * - The sequence and group numbers are set to 1.
 * .
 * @param sid the SIDs to be  whose collection interval (period) is to
 * be modified
 * @param period the modified collection intervals (period)
 * @param N1 the number of SIDs whose collection interval (period) is to
 * be modified
 * @return The (3,31) command
 */
FwSmDesc_t CrPsHkTestCaseMake3s31(CrPsSID_t* sid, CrPsCycleCnt_t* period, CrPsNSID_t N1);

#endif /* CRPS_HKTESTCASES_H_ */
