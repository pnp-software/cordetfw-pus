/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(12,21) MonProtFuncMonDefCmd.
 *
 * @note This file was generated on 2018-07-25 18:43:06
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSMONPROTFUNCMONDEFCMD_H_
#define CRPSMONPROTFUNCMONDEFCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Start action of TC(12,21) MonProtFuncMonDefCmd.
 * Run the procedure Start Action of Multi-Functional Monitor Commands of
 * figure \ref{fig:Cmd12FMonIdStart}
 * @param smDesc The state machine descriptor.
 */
void CrPsMonProtFuncMonDefCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(12,21) MonProtFuncMonDefCmd.
 * For each functional monitor which has been accepted for execution by the
 * Start Action: set its status to protected in the FMDL. Set the action
 * outcome to 'completed'.
 * @param smDesc The state machine descriptor.
 */
void CrPsMonProtFuncMonDefCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSMONPROTFUNCMONDEFCMD_H */
