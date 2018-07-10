/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(12,5) MonAddParMonDefCmd.
 *
 * @note This file was generated on 2018-07-10 22:34:00
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsMonAddParMonDefCmd.h"

/**
 * Start action of TC(12,5) MonAddParMonDefCmd.
 * Run the procedure Start Action of (12,5) Command of figure
 * \ref{fig:Cmd12s5Start}
 * @param smDesc The state machine descriptor.
 */
void CrPsMonAddParMonDefCmdStartAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsMonAddParMonDefCmdStartAction");
   return 1;
}

/**
 * Progress action of TC(12,5) MonAddParMonDefCmd.
 * For all parameter monitor definitions which have been accepted by the start
 * action: add the definition to the Parameter Monitor Definition List (PMDL),
 * set the checking status of the new parameter monitor to 'unchecked', reset
 * its repetition counter and phase counter to zero. Decrement the data pool
 * variable representing the number of remaining available entries in the PMDL
 * by the number of added parameter monitors. Set the action outcome to
 * 'completed'.
 * @param smDesc The state machine descriptor.
 */
void CrPsMonAddParMonDefCmdProgressAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsMonAddParMonDefCmdProgressAction");
   return 1;
}

