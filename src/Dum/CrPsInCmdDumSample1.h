/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(255,1) DumSample1 as an incoming command.
 *
 * @note This file was generated on 2018-09-30 23:01:15
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSINCMDDUMSAMPLE1_H_
#define CRPSINCMDDUMSAMPLE1_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Validity check of TC(255,1) DumSample1.
 * The Validity Check Operation for this command:
 * (a) Retrieves the InCommand type and loads it in an internal variable which
 * can be accessed with function <code>::CrFwInCmdSample1GetType</code>.
 * (b) Returns the value of an internal flag (the Validity Flag) whose value
 * is set through function <code>::CrFwInCmdSample1SetValidityFlag</code>.
 *
 * @param smDesc The state machine descriptor.
 * @return The validity check result.
 */
CrFwBool_t CrPsInCmdDumSample1ValidityCheck(FwPrDesc_t prDesc);

/**
 * Ready check of TC(255,1) DumSample1.
 * The Ready Check returns the value of an internal flag (the Ready Flag)
 * whose value is set through function
 * <code>::CrFwInCmdSample1SetReadyFlag</code>.
 * @param smDesc The state machine descriptor.
 * @return The ready check result.
 */
CrFwBool_t CrPsInCmdDumSample1ReadyCheck(FwSmDesc_t smDesc);

/**
 * Start action of TC(255,1) DumSample1.
 * This action sets the outcome to the value of an internal counter (the Start
 * Action Outcome Counter) whose value is set through function
 * <code>::CrFwInCmdSample1SetStartActionOutcome</code> and it increments the
 * value of a counter (the Start Action Counter) whose value is read through
 * function <code>::CrFwInCmdSample1GetStartActionCounter</code>.
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdDumSample1StartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(255,1) DumSample1.
 * This action:
 * (a) Sets the outcome to the value of an internal counter (the Progress
 * Action Outcome Counter) whose value is set through function
 * <code>::CrFwInCmdSample1SetProgressActionOutcome</code>, and
 * (b) It increments the progress step identifier if the progress step flag is
 * set (its value is controlled through function
 * <code>::CrFwInCmdSample1SetProgressActionFlag</code>.
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdDumSample1ProgressAction(FwSmDesc_t smDesc);

/**
 * Termination action of TC(255,1) DumSample1.
 * This actions sets the outcome to the value of an internal counter (the
 * Termination Action Outcome Counter) whose value is set through function
 * <code>::CrFwInCmdSample1SetTerminationActionOutcome</code> and it
 * increments the value of a counter (the Termination Action Counter) whose
 * value is read through function
 * <code>::CrFwInCmdSample1GetTerminationActionCounter</code>.
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdDumSample1TerminationAction(FwSmDesc_t smDesc);

/**
 * Abort action of TC(255,1) DumSample1.
 * This action sets the outcome to the value of an internal counter (the Abort
 * Action Outcome Counter) whose value is set through function
 * <code>::CrFwInCmdSample1SetAbortActionOutcome</code> and it increments the
 * value of a counter (the Abort Action Counter) whose value is read through
 * function <code>::CrFwInCmdSample1GetAbortActionCounter</code>.
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdDumSample1AbortAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSINCMDDUMSAMPLE1_H */
