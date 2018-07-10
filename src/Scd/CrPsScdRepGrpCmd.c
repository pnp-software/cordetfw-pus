/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(11,26) ScdRepGrpCmd.
 *
 * @note This file was generated on 2018-07-10 22:34:00
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsScdRepGrpCmd.h"

/**
 * Start action of TC(11,26) ScdRepGrpCmd.
 * Retrieve a (11,27) report from the OutFactory. If the retrieval fails,
 * generate error report OUTFACTORY_FAIL and set action outcome to 'failure'.
 * Otherwise, set action outcome to 'success'.
 * @param smDesc The state machine descriptor.
 */
void CrPsScdRepGrpCmdStartAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsScdRepGrpCmdStartAction");
   return 1;
}

/**
 * Progress action of TC(11,26) ScdRepGrpCmd.
 * Configure the (11,27) report created by the Start Action and load it in the
 * OutLoader. Set the action outcome to 'success' if the load operation is
 * successful and to 'failed' otherwise.
 * @param smDesc The state machine descriptor.
 */
void CrPsScdRepGrpCmdProgressAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsScdRepGrpCmdProgressAction");
   return 1;
}
