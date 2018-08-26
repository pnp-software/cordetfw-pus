/**
 * @file CrPsVerServUserPar.h
 * @ingroup PUSTestsuite
 * @ingroup PUSTestconfig 
 *
 * @brief User-modifiable parameters for the Request Verification Service.
 *
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#ifndef CRPS_VERSERV_USERPAR_H_
#define CRPS_VERSERV_USERPAR_H_

#include "UtilityFunctions/CrFwUtilityFunctions.h"

/**
 * The function which implements the Service 1 Progress Step Completed Check.
 * The PUS stipulates that a Successful Progress of Execution Report (1,5) is generated at
 * the completion of each progress step.
 * By default, in the CORDET Framework, a progress step for an incoming command corresponds to
 * one execution of the InCommand which encapsulates the incoming command.
 * This function can be used to reduce the frequency with which the (1,5) reports are generated.
 * The function is called by <code>::CrFwRepInCmdOutcome</code> at the completion of a
 * progress step for an InCommand.
 * If the function returns a non-zero value, then <code>::CrFwRepInCmdOutcome</code> generates
 * a (1,5) report for the InCommand. The return value of the function is interpreted as the
 * current step number.
 *
 * This function must conform to the prototype defined by <code>::CrPsStepCompleted_t</code>.
 * The function specified here is a default which always returns 1.
 * This is equivalent to treating each execution of an InCommand as a "progress step" in
 * the sense of service 1.
 */
#define CR_PS_STEP_COMPLETED TBD

#endif /* CRPS_VERSERV_USERPAR_H_ */
