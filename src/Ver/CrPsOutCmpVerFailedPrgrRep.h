/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TM(1,6) VerFailedPrgrRep as an out-going report.
 *
 * @note This file was generated on 2018-09-28 23:45:49
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSOUTCMPVERFAILEDPRGRREP_H_
#define CRPSOUTCMPVERFAILEDPRGRREP_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Enable check of TM(1,6) VerFailedPrgrRep.
 * #TM(1,6)
 * @param smDesc The state machine descriptor.
 * @return The enable check result.
 */
CrFwBool_t CrPsVerFailedPrgrRepEnableCheck(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSOUTCMPVERFAILEDPRGRREP_H */
