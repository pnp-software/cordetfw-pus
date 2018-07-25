/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TM(3,10) HkRepStructHkRep.
 *
 * @note This file was generated on 2018-07-25 18:43:06
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsHkRepStructHkRep.h"

/**
 * Enable check of TM(3,10) HkRepStructHkRep.
 * The enable status is read from the isEnabled field of the Report Definition
 * corresponding to the report’s SID
 * @param smDesc The state machine descriptor.
 * @return The enable check result.
 */
CrFwBool_t CrPsHkRepStructHkRepEnableCheck(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsHkRepStructHkRepEnableCheck");
   return 1;
}

/**
 * Update action of TM(3,10) HkRepStructHkRep.
 * Load the SID definition from the RDL
 * @param smDesc The state machine descriptor.
 */
void CrPsHkRepStructHkRepUpdateAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsHkRepStructHkRepUpdateAction");
   return ;
}
