/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(13,130) LptAbortDownCmd.
 *
 * @note This file was generated on 2018-07-14 19:50:20
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsLptAbortDownCmd.h"

/**
 * Start action of TC(13,130) LptAbortDownCmd.
 * The following actions are performed:
 *
 * (a) Determine the identifier of the LPT Buffer for the up-transfer by
 * computing: (x MOD LPT_N_BUF) where `x' is the Large Message Transaction
 * Identifier
 * (b) Set action outcome to 'success' if the LPT State Machine is in state
 * DOWN_TRANSFER; otherwise set the action outcome to `failure'
 * @param smDesc The state machine descriptor.
 */
void CrPsLptAbortDownCmdStartAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsLptAbortDownCmdStartAction");
   return ;
}

/**
 * Progress action of TC(13,130) LptAbortDownCmd.
 * Send command Abort to the LPT State Machine
 * @param smDesc The state machine descriptor.
 */
void CrPsLptAbortDownCmdProgressAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsLptAbortDownCmdProgressAction");
   return ;
}

