/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(3,2) HkCreDiagCmd.
 *
 * @note This file was generated on 2018-07-10 22:34:00
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsHkCreDiagCmd.h"

/**
 * Start action of TC(3,2) HkCreDiagCmd.
 * Run the procedure Start Action of HkCreate Command of figure
 * \image html CrPsCmd3s1Start.png "Start Action of HkCreate Command"
 * @param smDesc The state machine descriptor.
 */
void CrPsHkCreDiagCmdStartAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsHkCreDiagCmdStartAction");
   return 1;
}

/**
 * Progress action of TC(3,2) HkCreDiagCmd.
 * Add the definition of the new report to the RDL, set its enabled status to
 * ’disabled’, and set the action outcome to ’completed’
 * @param smDesc The state machine descriptor.
 */
void CrPsHkCreDiagCmdProgressAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsHkCreDiagCmdProgressAction");
   return 1;
}

