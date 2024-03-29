/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(13,10) LptUpInterCmd as an incoming command.
 *
 * @note This file was generated on 2018-09-29 23:48:04
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsInCmdLptUpInterCmd.h"

/**
 * Start action of TC(13,10) LptUpInterCmd.
 * Run the Procedure Up-Transfer Start Action of figure
 * \image html CrPsCmd13s10Start.png "Up-Transfer Start Action".
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdLptUpInterCmdStartAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsInCmdLptUpInterCmdStartAction");
   return ;
}

/**
 * Progress action of TC(13,10) LptUpInterCmd.
 * The following actions are performed:
 *
 * (a) Copy the up-transfer data to LPT Buffer and increment lptSize by the
 * amount of copied data
 * (b) Set lptTime to the current time
 * (c) Set patSeqNmb to the part sequence number carried by the command
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdLptUpInterCmdProgressAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsInCmdLptUpInterCmdProgressAction");
   return ;
}

