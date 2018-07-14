/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(12,22) MonUnprotFuncMonDefCmd.
 *
 * @note This file was generated on 2018-07-14 19:50:20
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSMONUNPROTFUNCMONDEFCMD_H_
#define CRPSMONUNPROTFUNCMONDEFCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Start action of TC(12,22) MonUnprotFuncMonDefCmd.
 * Run the Start Action of Multi-Functional Monitor Command Procedure of
 * figure \ref{fig:Cmd12FMonIdStart} and set action outcome to 'success'
 * @param smDesc The state machine descriptor.
 */
void CrPsMonUnprotFuncMonDefCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(12,22) MonUnprotFuncMonDefCmd.
 * For all the valid functional monitor identifiers in the command: unprotect
 * the functional monitor by setting its isProtected flag in the FDML to true.
 * Set action outcome to 'success'.
 * @param smDesc The state machine descriptor.
 */
void CrPsMonUnprotFuncMonDefCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSMONUNPROTFUNCMONDEFCMD_H */
