/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(3,6) HkDisHkCmd.
 *
 * @note This file was generated on 2018-07-10 22:34:00
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsHkDisHkCmd.h"

/**
 * Start action of TC(3,6) HkDisHkCmd.
 * Run the procedure Start Action of Multi-SID Command of figure
 * \image html CrPsCmd3SidStart.png "Start Action of Multi-SID
 * Command"
 * @param smDesc The state machine descriptor.
 */
void CrPsHkDisHkCmdStartAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsHkDisHkCmdStartAction");
   return 1;
}

/**
 * Progress action of TC(3,6) HkDisHkCmd.
 * Set to false the enable flag of the entries in the RDL corresponding to the
 * SIDs which have been identified as valid by the Start Action and then set
 * the action outcome to ’completed’
 * @param smDesc The state machine descriptor.
 */
void CrPsHkDisHkCmdProgressAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsHkDisHkCmdProgressAction");
   return 1;
}
