/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TM(1,7) VerSuccTermRep.
 *
 * @note This file was generated on 2018-07-10 22:34:00
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSVERSUCCTERMREP_H_
#define CRPSVERSUCCTERMREP_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Enable check of TM(1,7) VerSuccTermRep.
 * Service 1 reports retrieve their enable status from the OurRegistry as a
 * function of their type, sub-type and discriminant
 * @param smDesc The state machine descriptor.
 * @return The enable check result.
 */
CrFwBool_t CrPsVerSuccTermRepEnableCheck(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSVERSUCCTERMREP_H */
