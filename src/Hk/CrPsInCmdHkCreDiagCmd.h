/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(3,2) HkCreDiagCmd as an incoming command.
 *
 * @note This file was generated on 2018-10-28 17:05:47
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSINCMDHKCREDIAGCMD_H_
#define CRPSINCMDHKCREDIAGCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Start action of TC(3,2) HkCreDiagCmd.
 * Run the procedure Start Action of HkCreate Command of figure
 * \image html CrPsCmd3s1Start.png "Start Action of HkCreate Command"
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdHkCreDiagCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(3,2) HkCreDiagCmd.
 * Add the definition of the new report to the RDL, set its enabled status to
 * ’disabled’, and set the action outcome to ’completed’
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdHkCreDiagCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSINCMDHKCREDIAGCMD_H */
