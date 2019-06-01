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

/**
 * Test the monitor procedures which check the value of a monitored parameter (CrPsMonConfig.h).
 * The following actions are performed:
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


#endif /* CRPS_MONTESTCASES_H_ */
