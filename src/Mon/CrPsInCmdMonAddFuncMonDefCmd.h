/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(12,23) MonAddFuncMonDefCmd as an incoming command.
 *
 * @note This file was generated on 2018-09-29 23:48:04
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSINCMDMONADDFUNCMONDEFCMD_H_
#define CRPSINCMDMONADDFUNCMONDEFCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Start action of TC(12,23) MonAddFuncMonDefCmd.
 * Run the Start Action of (12,23) Command Procedure of figure
 * \ref{fig:Cmd12s23Start}.
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdMonAddFuncMonDefCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(12,23) MonAddFuncMonDefCmd.
 * For each functional monitor identifier accepted for execution by the Start
 * Action: add the functional monitor definition to the FMDL, set its checking
 * status to 'unchecked', set its enable status to 'disabled', and set its
 * protected status to 'unprotected'. Decrement the data pool variable
 * representing the number of remaining available functional monitors by the
 * number of added functional monitors. Set the action outcome to 'completed'.
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdMonAddFuncMonDefCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSINCMDMONADDFUNCMONDEFCMD_H */
