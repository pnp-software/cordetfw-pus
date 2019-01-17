/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(3,2) HkCreDiagCmd as an incoming command.
 *
 * @note This file was generated on 2018-09-29 23:48:04
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsInCmdHkCreDiagCmd.h"

/**
 * Start action of TC(3,2) HkCreDiagCmd.
 * Run the procedure Start Action of HkCreate Command of figure
 * \image html CrPsCmd3s1Start.png "Start Action of HkCreate Command"
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdHkCreDiagCmdStartAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsInCmdHkCreDiagCmdStartAction");
   return ;
}

/**
 * Progress action of TC(3,2) HkCreDiagCmd.
 * Add the definition of the new report to the RDL, set its enabled status to
 * ’disabled’, and set the action outcome to ’completed’
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdHkCreDiagCmdProgressAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsInCmdHkCreDiagCmdProgressAction");
   return ;
}
