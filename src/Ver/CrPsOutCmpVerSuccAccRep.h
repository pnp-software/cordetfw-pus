/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TM(1,1) VerSuccAccRep as an out-going report.
 *
 * @note This file was generated on 2018-10-28 17:05:47
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSOUTCMPVERSUCCACCREP_H_
#define CRPSOUTCMPVERSUCCACCREP_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Enable check of TM(1,1) VerSuccAccRep.
 * Service 1 reports retrieve their enable status from the OutRegistry as a
 * function of their type, sub-type and discriminant
 * @param smDesc The state machine descriptor.
 * @return The enable check result.
 */
CrFwBool_t CrPsOutCmpVerSuccAccRepEnableCheck(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSOUTCMPVERSUCCACCREP_H */
