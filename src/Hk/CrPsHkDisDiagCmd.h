/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(3,8) HkDisDiagCmd.
 *
 * @note This file was generated on 2018-07-25 18:43:06
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSHKDISDIAGCMD_H_
#define CRPSHKDISDIAGCMD_H_

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
void CrPsHkDisDiagCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(3,8) HkDisDiagCmd.
 * #TM(3,60
 * @param smDesc The state machine descriptor.
 */
void CrPsHkDisDiagCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSHKDISDIAGCMD_H */
