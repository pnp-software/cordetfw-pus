/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(11,24) ScdEnbGrpCmd.
 *
 * @note This file was generated on 2018-07-14 19:50:20
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsScdEnbGrpCmd.h"

/**
 * Start action of TC(11,24) ScdEnbGrpCmd.
 * Run the procedure Start Action of (11,24) and (11,25) Command of figure
 * \image html CrPsCmd11s24And25Start.png "Start Action of
 * Command to Enable or Disable Scheduling Groups". This procedure iterates
 * over the list of group identifiers in the command and rejects those which
 * are not in use.
 * @param smDesc The state machine descriptor.
 */
void CrPsScdEnbGrpCmdStartAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsScdEnbGrpCmdStartAction");
   return ;
}

/**
 * Progress action of TC(11,24) ScdEnbGrpCmd.
 * For all group identifiers accepted by the Start Action, the following is
 * done: the isGroupEnabled flag of the group is set to 'Enabled'. After all
 * identifiers have been processed, the action outcome is set to 'completed'.
 * @param smDesc The state machine descriptor.
 */
void CrPsScdEnbGrpCmdProgressAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsScdEnbGrpCmdProgressAction");
   return ;
}

