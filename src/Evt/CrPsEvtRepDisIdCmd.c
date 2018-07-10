/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(5,7) EvtRepDisIdCmd.
 *
 * @note This file was generated on 2018-07-10 22:34:00
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsEvtRepDisIdCmd.h"

/**
 * Start action of TC(5,7) EvtRepDisIdCmd.
 * Retrieve (5,8) report from OutFactory and set action outcome to 'success’
 * if retrieval succeeds. If the retrieval fails, generate error report
 * OUTFACTORY FAILED and set outcome of Start Action to ’failed’
 * @param smDesc The state machine descriptor.
 */
void CrPsEvtRepDisIdCmdStartAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsEvtRepDisIdCmdStartAction");
   return 1;
}

/**
 * Progress action of TC(5,7) EvtRepDisIdCmd.
 * Configure the (5,8) report with a destination equal to the source of the
 * (5,7) command, load it in the OutLoader, and set the action outcome to
 * ’completed’
 * @param smDesc The state machine descriptor.
 */
void CrPsEvtRepDisIdCmdProgressAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsEvtRepDisIdCmdProgressAction");
   return 1;
}
