/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TM(5,8) EvtDisIdRep.
 *
 * @note This file was generated on 2018-07-10 22:34:00
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsEvtDisIdRep.h"

/**
 * Update action of TM(5,8) EvtDisIdRep.
 * Load the list of disabled event identifiers from arrays isEidEnabled1 to
 * isEidEnabled4
 * @param smDesc The state machine descriptor.
 */
void CrPsEvtDisIdRepUpdateAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsEvtDisIdRepUpdateAction");
   return 1;
}