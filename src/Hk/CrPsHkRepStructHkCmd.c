/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(3,9) HkRepStructHkCmd.
 *
 * @note This file was generated on 2018-07-10 22:34:00
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsHkRepStructHkCmd.h"

/**
 * Start action of TC(3,9) HkRepStructHkCmd.
 * Run the procedure Start Action of Multi-SID Command of figure
 * \image html CrPsCmd3SidStart.png "Start Action of Multi-SID
 * Command"
 * @param smDesc The state machine descriptor.
 */
void CrPsHkRepStructHkCmdStartAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsHkRepStructHkCmdStartAction");
   return 1;
}

/**
 * Progress action of TC(3,9) HkRepStructHkCmd.
 * Run the procedure Progress Action of Report Service 3 Structure of figure
 * \image html CrPsCmd3s9Prgr.png "Progress Action of Report Service 3
 * Structure Command"
 * @param smDesc The state machine descriptor.
 */
void CrPsHkRepStructHkCmdProgressAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsHkRepStructHkCmdProgressAction");
   return 1;
}

/**
 * Termination action of TC(3,9) HkRepStructHkCmd.
 * Set action outcome to ’success’ if all valid SIDs in the command were
 * successfully processed by the progress action; set it to ’failure’
 * otherwise
 * @param smDesc The state machine descriptor.
 */
void CrPsHkRepStructHkCmdTerminationAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsHkRepStructHkCmdTerminationAction");
   return 1;
}

