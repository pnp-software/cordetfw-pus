/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(12,5) MonAddParMonDefCmd as an incoming command.
 *
 * @note This file was generated on 2018-09-29 23:48:04
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSINCMDMONADDPARMONDEFCMD_H_
#define CRPSINCMDMONADDPARMONDEFCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Start action of TC(12,5) MonAddParMonDefCmd.
 * Run the procedure Start Action of (12,5) Command of figure
 * \ref{fig:Cmd12s5Start}
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdMonAddParMonDefCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(12,5) MonAddParMonDefCmd.
 * For all parameter monitor definitions which have been accepted by the start
 * action: add the definition to the Parameter Monitor Definition List (PMDL),
 * set the checking status of the new parameter monitor to 'unchecked', reset
 * its repetition counter and phase counter to zero. Decrement the data pool
 * variable representing the number of remaining available entries in the PMDL
 * by the number of added parameter monitors. Set the action outcome to
 * 'completed'.
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdMonAddParMonDefCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSINCMDMONADDPARMONDEFCMD_H */
