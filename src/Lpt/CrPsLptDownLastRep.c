/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TM(13,3) LptDownLastRep.
 *
 * @note This file was generated on 2018-07-25 18:43:06
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsLptDownLastRep.h"

/**
 * Enable check of TM(13,3) LptDownLastRep.
 * Report is enabled if the LPT State Machine is in state DOWN_TRANSFER
 * @param smDesc The state machine descriptor.
 * @return The enable check result.
 */
CrFwBool_t CrPsLptDownLastRepEnableCheck(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsLptDownLastRepEnableCheck");
   return 1;
}

/**
 * Update action of TM(13,3) LptDownLastRep.
 * The following actions are performed:
 *
 * (a) Load the last part of the large packet from the LPT Buffer
 * (b) Set the transaction identifier equal to largeMsgTransId
 * (c) Set the partnumber equal to partSeqNmb
 * (d) Set the action outcome to: 'completed'
 * @param smDesc The state machine descriptor.
 */
void CrPsLptDownLastRepUpdateAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsLptDownLastRepUpdateAction");
   return ;
}
