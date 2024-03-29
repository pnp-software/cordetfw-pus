/**
 * @file CrPsMonTestCases.h
 * @ingroup PUSTestsuite
 *
 * @brief Declaration of the test cases for the On-Board Monitoring Service.
 * The test cases in this module depend on each other and must be executed in the order
 * in which they are declared.
 *
 * @author Alessandro Pasetti  <pasetti@pnp-software.com>
 *
 * @copyright P&P Software GmbH, 2019
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#ifndef CRPS_MONTESTCASES_H_
#define CRPS_MONTESTCASES_H_

/** Lower limit for test (12,5) commands */
#define MON_TEST_CASE_LIM1 10
/** Upper limit for test (12,5) commands */
#define MON_TEST_CASE_LIM2 20

/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
/* Include PUS Extension Files */
#include "Pckt/CrPsPcktHk.h"
#include "Mon/CrPsMonConfig.h"

/**
 * Test the monitor procedures which check the value of a monitored parameter (CrPsMonConfig.h).
 * The following actions are performed:
 * - Call the initialization function of the monitoring service
 * - Verify all possible outcomes of function #CrPsMonConfigOutOfLimitCheckR implementing the
 *   out-of-limit check for real-valued data pool items
 * - Verify all possible outcomes of function #CrPsMonConfigOutOfLimitCheckUI implementing the
 *   out-of-limit check for unsigned integer-valued data pool items
 * - Verify all possible outcomes of function #CrPsMonConfigOutOfLimitCheckSI implementing the
 *   out-of-limit check for signed integer-valued data pool items
 * - Verify all possible outcomes of function #CrPsMonConfigExpValCheck implementing the
 *   expected value check
 * .
 * @verify Procedure, Limit Check Monitor, Outcome is above limit
 * @verify Procedure, Limit Check Monitor, Outcome is below limit
 * @verify Procedure, Limit Check Monitor, Outcome is nominal
 * @verify Procedure, Expected Value Monitor, Violation is detected
 * @verify Procedure, Expected Value Monitor, No violation is detected
 * @verify Application Error Code, CrPsIllRMonParSize,
 * @verify Application Error Code, CrPsIllUIMonParSize,
 * @verify Application Error Code, CrPsIllSIMonParSize,
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsMonTestCase1();

/**
 * Test the commands to enable and disable the parameter monitoring function.
 * The following actions are performed:
 * - Instantiate and execute TC(12,15) and verify that the parameter monitoring function
 *   is enabled, the parameter monitoring function is started and the service 12 user is set
 *   equal to the source of the TC(12,15) command
 * - Execute again the TC(12,15) and verify that it is rejected with VER_MON_ENB
 * - Instantiate and execute TC(12,16) and verify that the parameter monitoring function
 *   is disabled and the parameter monitoring function is stopped
 * - Execute again the TC(12,16) and verify that it is rejected with VER_MON_DIS
 * .
 * @verify Command, Enable Parameter Monitoring Function, Nominal execution
 * @verify Command, Enable Parameter Monitoring Function, Start action fails
 * @verify Command, Enable Parameter Monitoring Function, Nominal execution
 * @verify Command, Enable Parameter Monitoring Function, Start action fails
 * @verify Command Rejection Code, VER_MON_ENB
 * @verify Command Rejection Code, VER_MON_DIS
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsMonTestCase2();

/**
 * Test the rejection cases of the command to add a paremeter monitor.
 * The following actions are performed:
 * - Configure the PMDL to be full, instantiate and execute a TC(12,5) with one PMON and verify it
 *   fails with codes VER_PMDL_FULL and VER_MI_S12_FD
 * - Configure the PMDL to be empty, instantiate and execute a TC(12,5) carrying two PMONs
 *   with illegal parameter identifiers and verify they fail with code VER_ILL_MON
 * - Instantiate and execute a TC(12,5) carrying two PMONs
 *   with illegal identifiers of monitored parameters and verify they fail with code VER_MON_ILL_DI
 * - Instantiate and execute a TC(12,5) carrying two PMONs
 *   with illegal identifiers of validity parameters and verify they fail with code VER_ILL_VAL_DI
 * - Instantiate and execute a TC(12,5) carrying a PMON
 *   with illegal monitoring check type and verify it fails with code VER_MON_ILL_PR
 * .
 * @verify Command, Add Parameter Monitoring Definition, Progress action fails due to PMDL full
 * @verify Command, Add Parameter Monitoring Definition, Progress action fails due to illegal PMON identifier
 * @verify Command, Add Parameter Monitoring Definition, Progress action fails due to illegal validity parameter identifier
 * @verify Command, Add Parameter Monitoring Definition, Progress action fails due to illegal monitored parameter
 * @verify Command, Add Parameter Monitoring Definition, Progress action fails due to illegal monitor parameter procedure
 * @verify Command Rejection Code, VER_PMDL_FULL
 * @verify Command Rejection Code, VER_ILL_MON
 * @verify Command Rejection Code, VER_ILL_VAL_DI
 * @verify Command Rejection Code, VER_MI_S12_FD
 * @verify Command Rejection Code, VER_MON_ILL_PR
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsMonTestCase3();

/**
 * Test the nominal cases of the commands to add and delete a parameter monitor.
 * The following actions are performed:
 * - Configure the PMDL to be empty, instantiate and execute one nominal TC(12,5) with one PMON and verify it
 *   is executed successfully and that the number of available PMON is decremented
 * - Instantiate and execute one nominal TC(12,6) to delete the PMON added at the previous step and verify it
 *   is executed successfully and that the number of available PMON is incremented
 * .
 * @verify Command, Add Parameter Monitoring Definition, Nominal case with one PMON
 * @verify Command, Delete Parameter Monitoring Definition, Nominal case with one PMON
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsMonTestCase4();

/**
 * Test the non-nominal cases of the command to delete a parameter monitor.
 * The following actions are performed:
 * - Configure the PMDL to be empty, instantiate and execute one nominal TC(12,5) with one PMON and then enable
 *   it
 * - Instantiate and execute one TC(12,6) to delete four PMONs with the following characteristics: the
 *   first PMON is not in use; the second one has a data item identifier which is out-of-range; the third one
 *   has a data item identifier equal to zero; and the fourth one is enabled and verify that the command
 *   is rejected with four (1,4) reports and one (1,8) report
 * .
 * @verify Command, Delete Parameter Monitoring Definition, Rejection due to PMON not in use
 * @verify Command, Delete Parameter Monitoring Definition, Rejection due to data item identifier out-of-range
 * @verify Command, Delete Parameter Monitoring Definition, Rejection due to PMON being enabled
 * @verify Command Rejection Code, VER_ILL_MON
 * @verify Command Rejection Code, VER_MON_ENB
 * @verify Command Rejection Code, VER_MI_S12_FD
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsMonTestCase5();

/**
 * Create a (12,6) command for test purposes.
 * The command is configured as follows:
 * - full service 1 acknowledgment is required.
 * .
 * @param NParMon the number of parameter monitors to be deleted
 * @param parMonId the array of identifiers of the parameter monitors
 * @return The (12,1) or (12,3) or (12,6) command
 */
FwSmDesc_t CrPsMonTestCaseMake12s6(CrPsNParMon_t NParMon, CrPsParMonId_t* parMonId);

/**
 * Create a (12,5) command for test purposes.
 * The command is configured as follows:
 * - The monitored parameter is assumed to be of unsigned integer type and
 *   the monitoring limits are set to MON_TEST_CASE_LIM1 and MON_TEST_CASE_LIM2
 * - The expected value for validity check of the parameter monitors is 1
 * - The mask used for validity check of the parameter monitors is 1
 * - full service 1 acknowledgment is required.
 * .
 * @param NParMon the number of parameter monitors to be added
 * @param parMonId the array of identifiers of the parameter monitors
 * @param parId the array of identifiers of the data pool item being monitored
 * @param per the array of periods of the monitor
 * @param repNmb the array of repetition numbers of the monitor
 * @param valDataItemId the array of identifiers of the data item used for validity check of parameter monitor
 * @param checkType the monitoring check type
 * @param lim1Eid the array of event identifiers for the low limit
 * @param lim2Eid the array of event identifiers for the upper limit
 * @return The (12,5) command
 */
FwSmDesc_t CrPsMonTestCaseMake12s5(CrPsNParMon_t NParMon, CrPsParMonId_t* parMonId, CrPsParId_t* parId,
        CrPsMonPer_t* per, CrPsMonPer_t* repNmb, CrPsParId_t* valDataItemId, CrPsMonCheckType_t CheckType,
        CrPsEvtId_t* lim1Eid, CrPsEvtId_t* lim2Eid);

/**
 * Create a (12,15) command for test purposes.
 * The command is configured to require full service 1 acknowledgment.
 * @param cmdSrc the source of the command
 * @return The (12,15) command
 */
FwSmDesc_t CrPsMonTestCaseMake12s15(CrFwDestSrc_t cmdSrc);

/**
 * Create a (12,16) command for test purposes.
 * @return The (12,16) command
 */
FwSmDesc_t CrPsMonTestCaseMake12s16();


#endif /* CRPS_MONTESTCASES_H_ */
