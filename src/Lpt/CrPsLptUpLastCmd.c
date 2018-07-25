/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(13,11) LptUpLastCmd.
 *
 * @note This file was generated on 2018-07-25 18:43:06
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsLptUpLastCmd.h"

/**
 * Start action of TC(13,11) LptUpLastCmd.
 * Run the Procedure Up-Transfer Start Action of figure
 * \image html CrPsCmd13s10Start.png "Up-Transfer Start Action".
 * @param smDesc The state machine descriptor.
 */
void CrPsLptUpLastCmdStartAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsLptUpLastCmdStartAction");
   return ;
}

/**
 * Progress action of TC(13,11) LptUpLastCmd.
 * The following actions are performed:
 *
 * (a) Copy the lptSize up-transfer data to LPT Buffer and increment lptSize
 * by the amount of copied data
 * (b) Set current time
 * (c) Set patSeqNmb to the part sequence number carried by the command
 * (d) Send EndUpTransfer command to LPT State Machine
 * (e) Set action outcome to: 'completed'
 * @param smDesc The state machine descriptor.
 */
void CrPsLptUpLastCmdProgressAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsLptUpLastCmdProgressAction");
   return ;
}

