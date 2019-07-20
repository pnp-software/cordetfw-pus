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
 * Convenience function to initialize a parameter monitor.
 * No checks are done on the legality of the function arguments.
 *
 * @param parMonId the identifier of the parameter monitor
 * @param parId the identifier of the data pool item being monitored
 * @param monPrFnc the pointer to the function implementing the monitoring procedure
 * @param per the period of the monitor
 * @param repNmb the repetition number of the monitor
 * @param evtId the identifier of the event associated to the monitor
 * @param valDataItemId the identifier of the data item used for validity check of parameter monitor
 * @param valExpVal rxpected value for validity check of parameter monitor
 * @param valMask the mask used for validity check of parameter monitor
 */
void CrPsMonTestCaseInitParMon(CrPsParMonId_t parMonId, CrPsParId_t parId, CrPsMonPrFnc_t monPrFnc,
        CrPsMonPer_t per, CrPsMonPer_t repNmb, CrPsEvtId_t evtId, CrPsParId_t valDataItemId,
        CrPsValMask_t valExpVal, CrPsValMask_t valMask);



#endif /* CRPS_MONTESTCASES_H_ */
