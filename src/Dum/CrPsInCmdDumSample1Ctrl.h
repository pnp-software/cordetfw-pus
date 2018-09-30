/**
 * @file
 * @ingroup PUSTestsuite
 *
 * Control interface for the Sample 1 InCommand used in the Test Suite.
 * An InCommand is defined by defining the functions which override its
 * adaptation points, namely (see <code>CrPsInCmd.h</code>):
 * - The Validity Check Operation
 * - The Ready Check Operation
 * - The Start Action Operation
 * - The Progress Action Operation
 * - The Termination Action Operation
 * - The Abort Action Operation
 * .
 * The Sample 1 InCommand is a dummy command which provides dummy implementations
 * for all the above checks and actions.
 * The outcome of the checks and actions is controlled through flags and counters.
 * This interface defines the functions through which the values of these flags
 * and counters can be set and read.
 *
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This file is part of the PUS Extension of the CORDET Framework.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#ifndef CRFW_INCMDDUMSAMPLE1CTRL_H_
#define CRFW_INCMDDUMSAMPLE1CTRL_H_

/* Include configuration files */
#include "CrFwUserConstants.h"
/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile components */
#include "FwSmCore.h"

/**
 * Set the value of the Validity Flag (see <code>::CrPsInCmdDumSample1ValidityCheck</code>).
 * @param flag the value of the validity flag
 */
void CrPsInCmdDumSample1SetValidityFlag(CrFwBool_t flag);

/**
 * Return the value of the InCommand type computed by the validity check function
 * <code>::CrPsInCmdDumSample1ValidityCheck</code>
 * @return the value of the InCommand type computed by the validity check function
 *         <code>::CrPsInCmdDumSample1ValidityCheck</code>
 */
CrFwServType_t CrPsInCmdDumSample1GetType();

/**
 * Set the value of the Ready Flag (see <code>::CrPsInCmdDumSample1ReadyCheck</code>).
 * @param flag the value of the ready flag
 */
void CrPsInCmdDumSample1SetReadyFlag(CrFwBool_t flag);

/**
 * Set the value of the Start Action Outcome Counter
 * (see <code>::CrPsInCmdDumSample1StartAction</code>).
 * @param outcome the value of the Start Action Outcome
 */
void CrPsInCmdDumSample1SetStartActionOutcome(CrFwOutcome_t outcome);

/**
 * Get the value of the Start Action Counter (see <code>::CrPsInCmdDumSample1StartAction</code>).
 * @return the value of the Start Action Counter
 */
CrFwCounterU1_t CrPsInCmdDumSample1GetStartActionCounter();

/**
 * Sets the progress step flag used by the progress action of the sample InCommand (if the flag
 * is set, the progress action increments the progress step identifier).
 *
 * @param flag the value of the progress step flag
 */
void CrPsInCmdDumSample1SetProgressStepFlag(CrFwBool_t flag);

/**
 * Set the value of the Progress Action Outcome Counter
 * (see <code>::CrPsInCmdDumSample1ProgressAction</code>).
 * @param outcome the value of the Progress Action Outcome
 */
void CrPsInCmdDumSample1SetProgressActionOutcome(CrFwOutcome_t outcome);

/**
 * Get the value of the Progress Action Counter (see <code>::CrPsInCmdDumSample1ProgressAction</code>).
 * @return the value of the Progress Action Counter
 */
CrFwCounterU1_t CrPsInCmdDumSample1GetProgressActionCounter();

/**
 * Set the value of the Abort Action Outcome Counter
 * (see <code>::CrPsInCmdDumSample1AbortAction</code>).
 * @param outcome the value of the Abort Action Outcome
 */
void CrPsInCmdDumSample1SetAbortActionOutcome(CrFwOutcome_t outcome);

/**
 * Get the value of the Abort Action Counter (see <code>::CrPsInCmdDumSample1AbortAction</code>).
 * @return the value of the Abort Action Counter
 */
CrFwCounterU1_t CrPsInCmdDumSample1GetAbortActionCounter();

/**
 * Set the value of the Termination Action Outcome Counter
 * (see <code>::CrPsInCmdDumSample1TerminationAction</code>).
 * @param outcome the value of the Termination Action Outcome
 */
void CrPsInCmdDumSample1SetTerminationActionOutcome(CrFwOutcome_t outcome);

/**
 * Get the value of the Termination Action Counter (see <code>::CrPsInCmdDumSample1TerminationAction</code>).
 * @return the value of the Termination Action Counter
 */
CrFwCounterU1_t CrPsInCmdDumSample1GetTerminationActionCounter();

#endif /* CRFW_INCMDDUMSAMPLE1CTRL_H_ */
