/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(12,6) MonDelParMonDefCmd.
 *
 * @note This file was generated on 2018-07-14 19:50:20
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSMONDELPARMONDEFCMD_H_
#define CRPSMONDELPARMONDEFCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Start action of TC(12,6) MonDelParMonDefCmd.
 * Run the procedure Start Action of (12,6) Command of figure
 * \ref{fig:Cmd12s6Start}
 * @param smDesc The state machine descriptor.
 */
void CrPsMonDelParMonDefCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(12,6) MonDelParMonDefCmd.
 * For all parameter monitor identifiers which have been accepted by the Start
 * Action: delete the parameter monitor from the Parameter Monitor Definition
 * List (PMDL). Increment the data pool variable representing the number of
 * remaining available PMDL entries by the number of deleted parameter
 * monitoring definitions. Set the action outcome to 'completed'.
 * @param smDesc The state machine descriptor.
 */
void CrPsMonDelParMonDefCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSMONDELPARMONDEFCMD_H */
