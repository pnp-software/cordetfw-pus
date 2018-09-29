/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(12,17) MonEnbFuncMonCmd as an incoming command.
 *
 * @note This file was generated on 2018-09-29 23:48:04
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsInCmdMonEnbFuncMonCmd.h"

/**
 * Start action of TC(12,17) MonEnbFuncMonCmd.
 * Set the action outcome to 'failed' if the Parameter Monitoring Function is
 * 'disabled'; otherwise set the action outcome to 'success'.
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdMonEnbFuncMonCmdStartAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsInCmdMonEnbFuncMonCmdStartAction");
   return ;
}

/**
 * Progress action of TC(12,17) MonEnbFuncMonCmd.
 * Set the enable status of the Functional Monitoring Function in the data
 * pool to 'enabled'. Set the action outcome to 'completed'.
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdMonEnbFuncMonCmdProgressAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsInCmdMonEnbFuncMonCmdProgressAction");
   return ;
}

