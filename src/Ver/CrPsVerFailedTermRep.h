/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TM(1,8) VerFailedTermRep.
 *
 * @note This file was generated on 2018-07-14 19:50:20
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSVERFAILEDTERMREP_H_
#define CRPSVERFAILEDTERMREP_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Enable check of TM(1,8) VerFailedTermRep.
 * Service 1 reports retrieve their enable status from the OurRegistry as a
 * function of their type, sub-type and discriminant
 * @param smDesc The state machine descriptor.
 * @return The enable check result.
 */
CrFwBool_t CrPsVerFailedTermRepEnableCheck(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSVERFAILEDTERMREP_H */
