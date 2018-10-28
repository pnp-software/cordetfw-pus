/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TM(5,1) EvtRep1 as an out-going report.
 *
 * @note This file was generated on 2018-10-28 17:05:47
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSOUTCMPEVTREP1_H_
#define CRPSOUTCMPEVTREP1_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Enable check of TM(5,1) EvtRep1.
 * Update service 5 observable nOfDetectedEvt x (’x’ is the event severity
 * level) and then retrieve the enable status from the Our-Registry as a
 * function of the report type, sub-type and discriminant
 * @param smDesc The state machine descriptor.
 * @return The enable check result.
 */
CrFwBool_t CrPsOutCmpEvtRep1EnableCheck(FwSmDesc_t smDesc);

/**
 * Update action of TM(5,1) EvtRep1.
 * Update service 5 observables: nOfGenEvtRep x, lastEvtEid i, lastEvtTime x
 * (’x’ is the event severity level). Note that the parameter values are set
 * by the application which creates the event report at the time it creates
 * the event report.
 * @param smDesc The state machine descriptor.
 */
void CrPsOutCmpEvtRep1UpdateAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSOUTCMPEVTREP1_H */
