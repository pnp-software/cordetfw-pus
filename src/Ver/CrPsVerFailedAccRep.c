/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TM(1,2) VerFailedAccRep.
 *
 * @note This file was generated on 2018-07-25 18:43:06
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsVerFailedAccRep.h"

/**
 * Enable check of TM(1,2) VerFailedAccRep.
 * Service 1 reports retrieve their enable status from the OurRegistry as a
 * function of their type, sub-type and discriminant
 * @param smDesc The state machine descriptor.
 * @return The enable check result.
 */
CrFwBool_t CrPsVerFailedAccRepEnableCheck(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsVerFailedAccRepEnableCheck");
   return 1;
}

