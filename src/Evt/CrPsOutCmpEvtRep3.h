/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TM(5,3) EvtRep3 as an out-going report.
 *
 * @note This file was generated on 2018-09-30 23:01:15
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSOUTCMPEVTREP3_H_
#define CRPSOUTCMPEVTREP3_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Enable check of TM(5,3) EvtRep3.
 * Update service 5 observable nOfDetectedEvt x (’x’ is the event severity
 * level) and then retrieve the enable status from the Our-Registry as a
 * function of the report type, sub-type and discriminant
 * @param smDesc The state machine descriptor.
 * @return The enable check result.
 */
CrFwBool_t CrPsOutCmpEvtRep3EnableCheck(FwSmDesc_t smDesc);

/**
 * Update action of TM(5,3) EvtRep3.
 * Update service 5 observables: nOfGenEvtRep x, lastEvtEid i, lastEvtTime x
 * (’x’ is the event severity level). Note that the parameter values are set
 * by the application which creates the event report at the time it creates
 * the event report.
 * @param smDesc The state machine descriptor.
 */
void CrPsOutCmpEvtRep3UpdateAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSOUTCMPEVTREP3_H */
