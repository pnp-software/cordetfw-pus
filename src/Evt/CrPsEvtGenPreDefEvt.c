/**
 * @file
 * @ingroup man_evt
 *
 * Implementation of CrPsEvtGenPreDefEvt.h.
 *
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 *
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

#include "Evt/CrPsEvtConfig.h"
#include "CrPsEvtGenPreDefEvt.h"
#include "Pckt/CrPsPcktEvt.h"
#include "CrPsServTypeId.h"
#include "CrPsTypes.h"
#include "assert.h"

#include "OutFactory/CrFwOutFactory.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "CrFwUserConstants.h"
#include "OutLoader/CrFwOutLoader.h"
#include "OutCmp/CrFwOutCmp.h"
#include "CrFwRepErr.h"


/* ----------------------------------------------------------------------------------- */
void CrPsEvtGenPreDefEvtNoPar(CrPsEvtId_t evtId) {
  unsigned int sevLevel;
  FwSmDesc_t evtRep;
  CrFwPckt_t evtPckt;

  /* Get the event severity level */
  sevLevel = CrPsEvtConfigGetSevLevel(evtId);

  /* - retrieves an OutComponent to encapsulate the event report from the OutFactory */
  switch (sevLevel) {
    case 2:
      evtRep = CrFwOutFactoryMakeOutCmp(EVT_TYPE,EVTLOWSEVREP_STYPE,0,LEN_EVT_LOWSEVREP);
      break;
    case 4:
      evtRep = CrFwOutFactoryMakeOutCmp(EVT_TYPE,EVTHIGHSEVREP_STYPE,0,LEN_EVT_HIGHSEVREP);
      break;
    default:
      CrFwSetAppErrCode(crPsEvtIllEvtId);
      return;
  }

  /* Generate error report if OutFactory failed to return a component */
  if (evtRep == NULL) {
    CrFwRepErrKind(psOutFactoryFail, 0, 0, EVT_TYPE, (CrFwServSubType_t)sevLevel, evtId);
    return;
  }

  /* Set the event identifier */
  evtPckt = CrFwOutCmpGetPckt(evtRep);
  if (sevLevel == 2) {
    setEvtLowSevRepEventId(evtPckt, evtId);
  } else {
    setEvtHighSevRepEventId(evtPckt, evtId);;
  }

  /* Load event report in th2 OutLoader */
  CrFwOutLoaderLoad(evtRep);
}

/* ----------------------------------------------------------------------------------- */
void CrPsEvtGenPreDefEvtDummyPar(CrPsEvtId_t evtId, CrPsEightBit_t dummyPar) {
  unsigned int sevLevel;
  FwSmDesc_t evtRep;
  CrFwPckt_t evtPckt;

  /* Get the event severity level */
  sevLevel = CrPsEvtConfigGetSevLevel(evtId);

  /* Retrieves an OutComponent to encapsulate the event report from the OutFactory */
  switch (sevLevel) {
    case 1:
      evtRep = CrFwOutFactoryMakeOutCmp(EVT_TYPE,EVTINFOREP_STYPE,0,LEN_EVT_INFOREP);
      break;
    case 3:
      evtRep = CrFwOutFactoryMakeOutCmp(EVT_TYPE,EVTINFOREP_STYPE,0,LEN_EVT_MEDSEVREP);
      break;
    default:
      CrFwSetAppErrCode(crPsEvtIllEvtId);
      return;
  }

  /* Generate error report if OutFactory failed to return a component */
  if (evtRep == NULL) {
    CrFwRepErrKind(psOutFactoryFail, 0, 0, EVT_TYPE, (CrFwServSubType_t)sevLevel, evtId);
    return;
  }

  /* Configure and load event report in the OutLoader */
  evtPckt = CrFwOutCmpGetPckt(evtRep);
  if (sevLevel == 1) {
    setEvtInfoRepEventId(evtPckt, evtId);
    setEvtInfoRep_EVT_DUMMY_1Par(evtPckt, dummyPar);
  } else {
    setEvtMedSevRepEventId(evtPckt, evtId);
    setEvtMedSevRep_EVT_DUMMY_3Par(evtPckt, dummyPar);
  }

  CrFwOutLoaderLoad(evtRep);
}

