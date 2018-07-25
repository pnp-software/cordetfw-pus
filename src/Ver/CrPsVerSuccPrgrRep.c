/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TM(1,5) VerSuccPrgrRep.
 *
 * @note This file was generated on 2018-07-25 18:43:06
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsVerSuccPrgrRep.h"

/**
 * Enable check of TM(1,5) VerSuccPrgrRep.
 * #TM(1,5)
 * @param smDesc The state machine descriptor.
 * @return The enable check result.
 */
CrFwBool_t CrPsVerSuccPrgrRepEnableCheck(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsVerSuccPrgrRepEnableCheck");
   return 1;
}

