/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(12,24) MonDelFuncMonDefCmd.
 *
 * @note This file was generated on 2018-07-14 19:50:20
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSMONDELFUNCMONDEFCMD_H_
#define CRPSMONDELFUNCMONDEFCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Start action of TC(12,24) MonDelFuncMonDefCmd.
 * Run the Command (12,24) Start Action Procedure of figure
 * \ref{fig:Cmd12s24Start}
 * @param smDesc The state machine descriptor.
 */
void CrPsMonDelFuncMonDefCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(12,24) MonDelFuncMonDefCmd.
 * For all functional monitors which have been accepted for execution by the
 * Start Action: remove the functional monitor from the FMDL Increment the
 * data pool variable representing the number of remaining available
 * functional monitors by the number of deleted functional monitors. Set the
 * action outcome to 'completed'.
 * @param smDesc The state machine descriptor.
 */
void CrPsMonDelFuncMonDefCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSMONDELFUNCMONDEFCMD_H */
