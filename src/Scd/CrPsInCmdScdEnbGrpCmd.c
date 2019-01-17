/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(11,24) ScdEnbGrpCmd as an incoming command.
 *
 * @note This file was generated on 2018-09-29 23:48:04
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsInCmdScdEnbGrpCmd.h"

/**
 * Start action of TC(11,24) ScdEnbGrpCmd.
 * Run the procedure Start Action of (11,24) and (11,25) Command of figure
 * \image html CrPsCmd11s24And25Start.png "Start Action of
 * Command to Enable or Disable Scheduling Groups". This procedure iterates
 * over the list of group identifiers in the command and rejects those which
 * are not in use.
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdScdEnbGrpCmdStartAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsInCmdScdEnbGrpCmdStartAction");
   return ;
}

/**
 * Progress action of TC(11,24) ScdEnbGrpCmd.
 * For all group identifiers accepted by the Start Action, the following is
 * done: the isGroupEnabled flag of the group is set to 'Enabled'. After all
 * identifiers have been processed, the action outcome is set to 'completed'.
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdScdEnbGrpCmdProgressAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsInCmdScdEnbGrpCmdProgressAction");
   return ;
}
