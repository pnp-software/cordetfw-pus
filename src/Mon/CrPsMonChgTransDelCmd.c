/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(12,3) MonChgTransDelCmd.
 *
 * @note This file was generated on 2018-07-10 22:34:00
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsMonChgTransDelCmd.h"

/**
 * Start action of TC(12,3) MonChgTransDelCmd.
 * Set action outcome to 'success' if the argument of the command (the new
 * maximum reporting delay) is a positive integer; otherwise, set the outcome
 * to 'failure'
 * @param smDesc The state machine descriptor.
 */
void CrPsMonChgTransDelCmdStartAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsMonChgTransDelCmdStartAction");
   return 1;
}

/**
 * Progress action of TC(12,3) MonChgTransDelCmd.
 * Update the maximum report delay in the data pool with the value in the
 * command
 * @param smDesc The state machine descriptor.
 */
void CrPsMonChgTransDelCmdProgressAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsMonChgTransDelCmdProgressAction");
   return 1;
}
