/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(5,5) EvtEnbId.
 *
 * @note This file was generated on 2018-07-14 19:50:20
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsEvtEnbId.h"

/**
 * Start action of TC(5,5) EvtEnbId.
 * Run the procedure Start Action of Multi-EID Command of figure
 * \image html CrPsCmd5EidStart.png "Start Action of Multi-EID
 * Command"
 * @param smDesc The state machine descriptor.
 */
void CrPsEvtEnbIdStartAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsEvtEnbIdStartAction");
   return ;
}

/**
 * Progress action of TC(5,5) EvtEnbId.
 * For each valid EID found by the Start Action of the command: set the
 * corresponding element of the array isEidEnabled to true and then decrement
 * nDisabledEid x (’x’ is the severity level of the EID). Set the action
 * outcome to ’completed’.
 * @param smDesc The state machine descriptor.
 */
void CrPsEvtEnbIdProgressAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsEvtEnbIdProgressAction");
   return ;
}

