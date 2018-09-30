/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(3,27) HkOneShotHkCmd as an incoming command.
 *
 * @note This file was generated on 2018-09-30 23:01:15
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSINCMDHKONESHOTHKCMD_H_
#define CRPSINCMDHKONESHOTHKCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Ready check of TC(3,27) HkOneShotHkCmd.
 * Return 'command is ready'
 * @param smDesc The state machine descriptor.
 * @return The ready check result.
 */
CrFwBool_t CrPsInCmdHkOneShotHkCmdReadyCheck(FwSmDesc_t smDesc);

/**
 * Start action of TC(3,27) HkOneShotHkCmd.
 * Run the procedure Start Action of Multi-SID Command of figure 9.3
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdHkOneShotHkCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(3,27) HkOneShotHkCmd.
 * Run the procedure Progress Action of Generate One-Shot Housekeeping Report
 * of figure 9.6
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdHkOneShotHkCmdProgressAction(FwSmDesc_t smDesc);

/**
 * Termination action of TC(3,27) HkOneShotHkCmd.
 * Set action outcome to ’success’ if all valid SIDs in the command were
 * successfully processed by the progress action; set it to ’failure’
 * otherwise
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdHkOneShotHkCmdTerminationAction(FwSmDesc_t smDesc);

/**
 * Abort action of TC(3,27) HkOneShotHkCmd.
 * Do nothing
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdHkOneShotHkCmdAbortAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSINCMDHKONESHOTHKCMD_H */
