/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TM(3,26) HkDiagRep.
 *
 * @note This file was generated on 2018-07-25 18:43:06
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsHkDiagRep.h"

/**
 * Enable check of TM(3,26) HkDiagRep.
 * The enable status is read from the isEnabled field of the Report Definition
 * corresponding to the report’s SID
 * @param smDesc The state machine descriptor.
 * @return The enable check result.
 */
CrFwBool_t CrPsHkDiagRepEnableCheck(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsHkDiagRepEnableCheck");
   return 1;
}

/**
 * Ready check of TM(3,26) HkDiagRep.
 * Run the procedure of figure \image html CrPsRep3s25Ready.png "Ready
 * Check of Service 3 HK or Diagnostic Report"
 * @param smDesc The state machine descriptor.
 * @return The ready check result.
 */
CrFwBool_t CrPsHkDiagRepReadyCheck(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsHkDiagRepReadyCheck");
   return 1;
}

/**
 * Update action of TM(3,26) HkDiagRep.
 * Load the value of the simply-commutated data items from the data pool and
 * that of the super-commutated data items from the Sampling Buffer associated
 * to the report’s SID according to the Report Definition
 * @param smDesc The state machine descriptor.
 */
void CrPsHkDiagRepUpdateAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsHkDiagRepUpdateAction");
   return ;
}
