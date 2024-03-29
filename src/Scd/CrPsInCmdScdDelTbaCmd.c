/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(11,5) ScdDelTbaCmd as an incoming command.
 *
 * @note This file was generated on 2018-09-29 23:48:04
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsInCmdScdDelTbaCmd.h"

/**
 * Start action of TC(11,5) ScdDelTbaCmd.
 * Run the procedure Start Action of (11,22) Command of figure
 * \image html CrPsCmd11s22Start.png "Start Action of Command to
 * Create Scheduling Group". This procedure iterates over the list of group
 * identifiers in the command and rejects those which are out-of-limit or
 * which are already in use.
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdScdDelTbaCmdStartAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsInCmdScdDelTbaCmdStartAction");
   return ;
}

/**
 * Progress action of TC(11,5) ScdDelTbaCmd.
 * For each group identifier which has been accepted by the Start Action, the
 * following is done:
 *
 * (a) The group identifier is marked as in use (its InUse flag is set to
 * true)
 * (b) The enable status of the group identifier is set in accordance with the
 * enable status parameter in the command
 *
 * After all identifiers have been processed, the action outcome is set to:
 * 'completed'.
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdScdDelTbaCmdProgressAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsInCmdScdDelTbaCmdProgressAction");
   return ;
}

