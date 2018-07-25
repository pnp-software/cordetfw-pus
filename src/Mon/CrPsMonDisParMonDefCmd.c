/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(12,2) MonDisParMonDefCmd.
 *
 * @note This file was generated on 2018-07-25 18:43:06
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsMonDisParMonDefCmd.h"

/**
 * Start action of TC(12,2) MonDisParMonDefCmd.
 * Run the procedure Start Action of Multi-Parameter Monitor Commands of
 * figure \ref{fig:Cmd12s1and2Start}
 * @param smDesc The state machine descriptor.
 */
void CrPsMonDisParMonDefCmdStartAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsMonDisParMonDefCmdStartAction");
   return ;
}

/**
 * Progress action of TC(12,2) MonDisParMonDefCmd.
 * For every valid Parameter Monitor Identifier in the command: stop its
 * Monitor Procedure and set its checking status (attribute checkStatus) to
 * UNCHECKED. Decrement the data pool variable representing the number of
 * enabled parameter monitors by the number of disabled parameter monitors.
 * Set the action outcome to 'completed'.
 * @param smDesc The state machine descriptor.
 */
void CrPsMonDisParMonDefCmdProgressAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsMonDisParMonDefCmdProgressAction");
   return ;
}

