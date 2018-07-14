/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(12,25) MonRepFuncMonDefCmd.
 *
 * @note This file was generated on 2018-07-14 19:50:20
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsMonRepFuncMonDefCmd.h"

/**
 * Start action of TC(12,25) MonRepFuncMonDefCmd.
 * Run the Start Action of (12,25) Command Procedure of figure
 * \image html Cmd12s25Start.png "Start Action for Command 12,5"
 * @param smDesc The state machine descriptor.
 */
void CrPsMonRepFuncMonDefCmdStartAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsMonRepFuncMonDefCmdStartAction");
   return ;
}

/**
 * Progress action of TC(12,25) MonRepFuncMonDefCmd.
 * Configure the (12,26) reports created by the Start Action and load them in
 * the OutLoader. Set the action outcome to 'success' if the load operation is
 * successful and to "failed' otherwise.
 * @param smDesc The state machine descriptor.
 */
void CrPsMonRepFuncMonDefCmdProgressAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsMonRepFuncMonDefCmdProgressAction");
   return ;
}

