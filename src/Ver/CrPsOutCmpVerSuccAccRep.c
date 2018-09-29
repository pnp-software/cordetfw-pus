/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TM(1,1) VerSuccAccRep as an out-going report.
 *
 * @note This file was generated on 2018-08-19 17:56:57
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsOutCmpVerSuccAccRep.h"

/**
 * Enable check of TM(1,1) VerSuccAccRep.
 * Service 1 reports retrieve their enable status from the OurRegistry as a
 * function of their type, sub-type and discriminant
 * @param smDesc The state machine descriptor.
 * @return The enable check result.
 */
CrFwBool_t CrPsOutCmpVerSuccAccRepEnableCheck(FwSmDesc_t smDesc) {
   CRFW_UNUSED(smDesc);
   DBG("CrPsVerSuccAccRepEnableCheck");
   return 1;
}

