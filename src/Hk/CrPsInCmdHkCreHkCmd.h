/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(3,1) HkCreHkCmd as an incoming command.
 *
 * @note This file was generated on 2018-09-30 23:01:15
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSINCMDHKCREHKCMD_H_
#define CRPSINCMDHKCREHKCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Start action of TC(3,1) HkCreHkCmd.
 * Run the procedure Start Action of HkCreate Command of figure
 * \image html CrPsCmd3s1Start.png "Start Action of HkCreate Command"
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdHkCreHkCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(3,1) HkCreHkCmd.
 * Add the definition of the new report to the RDL, set its enabled status to
 * ’disabled’, and set the action outcome to ’completed’
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdHkCreHkCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSINCMDHKCREHKCMD_H */
