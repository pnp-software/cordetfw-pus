/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TM(13,1) LptDownFirstRep.
 *
 * @note This file was generated on 2018-07-14 19:50:20
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsLptDownFirstRep.h"

/**
 * Enable check of TM(13,1) LptDownFirstRep.
 * Report is enabled if the LPT State Machine is in state DOWN_TRANSFER
 * @param smDesc The state machine descriptor.
 * @return The enable check result.
 */
CrFwBool_t CrPsLptDownFirstRepEnableCheck(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsLptDownFirstRepEnableCheck");
   return 1;
}

/**
 * Update action of TM(13,1) LptDownFirstRep.
 * The following actions are performed:
 *
 * (a) Load the first part of the large packet from the LPT Buffer
 * (b) Set the transaction identifier equal to largeMsgTransId
 * (c) Set the part number equal to partSeqNmb
 * (d) Increment partSeqNmb; and decrement lptRemSize by partSize
 * (e) Set the action outcome to: 'completed'
 * @param smDesc The state machine descriptor.
 */
void CrPsLptDownFirstRepUpdateAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsLptDownFirstRepUpdateAction");
   return ;
}
