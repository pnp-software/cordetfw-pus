/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(12,8) MonRepParMonDefCmd.
 *
 * @note This file was generated on 2018-07-25 18:43:06
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSMONREPPARMONDEFCMD_H_
#define CRPSMONREPPARMONDEFCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Start action of TC(12,8) MonRepParMonDefCmd.
 * Run the Start Action of (12,8) Command Procedure of figure
 * \ref{fig:Cmd12s8Start}
 * @param smDesc The state machine descriptor.
 */
void CrPsMonRepParMonDefCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(12,8) MonRepParMonDefCmd.
 * Configure the (12,9) reports created by the Start Action and load them in
 * the OutLoader. Set the action outcome to 'success' if the load operation is
 * successful and to 'failed' otherwise.
 * @param smDesc The state machine descriptor.
 */
void CrPsMonRepParMonDefCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSMONREPPARMONDEFCMD_H */
