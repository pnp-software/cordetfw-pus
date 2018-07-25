/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(13,129) LptStartDownCmd.
 *
 * @note This file was generated on 2018-07-25 18:43:06
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsLptStartDownCmd.h"

/**
 * Start action of TC(13,129) LptStartDownCmd.
 * The following actions are performed:
 *
 * (a) Determine the identifier of the LPT Buffer for the up-transfer by
 * computing: (x MOD LPT_N_BUF) where `x' is the Large Message Transaction
 * Identifier
 * (b) Set action outcome to 'success' if the LPT State Machine is in state
 * INACTIVE; otherwise set the action outcome to `failure'
 * @param smDesc The state machine descriptor.
 */
void CrPsLptStartDownCmdStartAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsLptStartDownCmdStartAction");
   return ;
}

/**
 * Progress action of TC(13,129) LptStartDownCmd.
 * Send command StartDownTransfer to the LPT State Machine
 * @param smDesc The state machine descriptor.
 */
void CrPsLptStartDownCmdProgressAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsLptStartDownCmdProgressAction");
   return ;
}

