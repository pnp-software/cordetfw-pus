/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TM(5,2) EvtRep2.
 *
 * @note This file was generated on 2018-07-14 19:50:20
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsEvtRep2.h"

/**
 * Enable check of TM(5,2) EvtRep2.
 * Update service 5 observable nOfDetectedEvt x (’x’ is the event severity
 * level) and then retrieve the enable status from the Our-Registry as a
 * function of the report type, sub-type and discriminant
 * @param smDesc The state machine descriptor.
 * @return The enable check result.
 */
CrFwBool_t CrPsEvtRep2EnableCheck(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsEvtRep2EnableCheck");
   return 1;
}

/**
 * Update action of TM(5,2) EvtRep2.
 * Update service 5 observables: nOfGenEvtRep x, lastEvtEid i, lastEvtTime x
 * (’x’ is the event severity level). Note that the parameter values are set
 * by the application which creates the event report at the time it creates
 * the event report.
 * @param smDesc The state machine descriptor.
 */
void CrPsEvtRep2UpdateAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsEvtRep2UpdateAction");
   return ;
}
