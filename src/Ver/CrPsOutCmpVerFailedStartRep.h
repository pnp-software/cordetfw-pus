/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TM(1,4) VerFailedStartRep as an out-going report.
 *
 * @note This file was generated on 2018-09-30 23:01:15
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSOUTCMPVERFAILEDSTARTREP_H_
#define CRPSOUTCMPVERFAILEDSTARTREP_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Enable check of TM(1,4) VerFailedStartRep.
 * Service 1 reports retrieve their enable status from the OutRegistry as a
 * function of their type, sub-type and discriminant
 * @param smDesc The state machine descriptor.
 * @return The enable check result.
 */
CrFwBool_t CrPsOutCmpVerFailedStartRepEnableCheck(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSOUTCMPVERFAILEDSTARTREP_H */
