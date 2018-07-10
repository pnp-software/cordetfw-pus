/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(12,16) MonDisParMonFuncCmd.
 *
 * @note This file was generated on 2018-07-10 22:34:00
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsMonDisParMonFuncCmd.h"

/**
 * Start action of TC(12,16) MonDisParMonFuncCmd.
 * Set the action outcome to 'failure' if the Functional Monitoring Function
 * is supported by the application and is enabled. Otherwise set the action
 * outcome to 'success'.
 * @param smDesc The state machine descriptor.
 */
void CrPsMonDisParMonFuncCmdStartAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsMonDisParMonFuncCmdStartAction");
   return 1;
}

/**
 * Progress action of TC(12,16) MonDisParMonFuncCmd.
 * Stop the Parameter Monitoring Procedure. Set the enable status of the
 * Parameter Monitoring Function in the data pool to: 'disabled'. Set the
 * action outcome to: 'completed'.
 * @param smDesc The state machine descriptor.
 */
void CrPsMonDisParMonFuncCmdProgressAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsMonDisParMonFuncCmdProgressAction");
   return 1;
}

