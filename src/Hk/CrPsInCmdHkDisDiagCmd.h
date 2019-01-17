/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(3,8) HkDisDiagCmd as an incoming command.
 *
 * @note This file was generated on 2018-10-28 17:05:47
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSINCMDHKDISDIAGCMD_H_
#define CRPSINCMDHKDISDIAGCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Start action of TC(3,8) HkDisDiagCmd.
 * Run the procedure Start Action of Multi-SID Command of figure
 * \image html CrPsCmd3SidStart.png "Start Action of Multi-SID
 * Command"
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdHkDisDiagCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(3,8) HkDisDiagCmd.
 * #TM(3,60
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdHkDisDiagCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSINCMDHKDISDIAGCMD_H */