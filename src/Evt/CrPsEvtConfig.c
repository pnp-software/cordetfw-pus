/**
 * @file
 *
 * Implementation of the configuration interface for the Event Reporting Service.
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
#include "Pckt/CrPsPcktEvt.h"
#include "CrPsTypes.h"
#include "CrPsServTypeId.h"

/* Define arrays holding event identifiers in increasing order */
static CrPsEvtId_t listOfEid_1[N_OF_DER_PCKT_EVT_REP1] = LIST_OF_DER_PCKT_EVT_REP1;
static CrPsEvtId_t listOfEid_2[N_OF_DER_PCKT_EVT_REP2] = LIST_OF_DER_PCKT_EVT_REP2;
static CrPsEvtId_t listOfEid_3[N_OF_DER_PCKT_EVT_REP3] = LIST_OF_DER_PCKT_EVT_REP3;
static CrPsEvtId_t listOfEid_4[N_OF_DER_PCKT_EVT_REP4] = LIST_OF_DER_PCKT_EVT_REP4;

/* The i-th element of these arrays holds the idenable status of the i-th event identifier */
static CrFwBool_t isEidDisabled_1[N_OF_DER_PCKT_EVT_REP1];
static CrFwBool_t isEidDisabled_2[N_OF_DER_PCKT_EVT_REP2];
static CrFwBool_t isEidDisabled_3[N_OF_DER_PCKT_EVT_REP3];
static CrFwBool_t isEidDisabled_4[N_OF_DER_PCKT_EVT_REP4];

/* Event Position Buffer */
static unsigned int evtSevLevel;
static unsigned int evtPos;

/* ------------------------------------------------------------------------------------------------ */
void CrPsEvtConfigInit() {
   return;
}

/* ------------------------------------------------------------------------------------------------ */
int CrPsEvtConfigGetEidPos(CrPsEvtId_t evtId, unsigned int severityLevel) {
  unsigned int lower, upper, pos;
  CrPsEvtId_t* listOfEid;

  lower = 0;
  switch (severityLevel) {
    case 1:
      upper = N_OF_DER_PCKT_EVT_REP1;
      listOfEid = listOfEid_1;
      break;
    case 2:
      upper = N_OF_DER_PCKT_EVT_REP2;
      listOfEid = listOfEid_2;
      break;
    case 3:
      upper = N_OF_DER_PCKT_EVT_REP3;
      listOfEid = listOfEid_3;
      break;
    case 4:
      upper = N_OF_DER_PCKT_EVT_REP4;
      listOfEid = listOfEid_4;
      break;
    default:            /* Illegal severity level */
      return -1;
  }

  /* Loop is guaranteed to be exited because we halve the search interval in each cycle */
  while (1) {
    pos = lower + (upper - lower)/2;
    if (listOfEid[pos] == evtId)
      return pos;
    if (listOfEid[pos] > evtId)
      lower = pos;
    if (listOfEid[pos] < evtId)
      upper = pos;
    if (lower == upper)
      return -1;
  }
}

/* ------------------------------------------------------------------------------------------------ */
unsigned int CrPsEvtConfigSetEidEnableStatus (CrPsEvtId_t evtId, CrFwBool_t enableStatus) {
  unsigned int pos;
  unsigned int sevLevel;
  CrPsEvtId_t* isEidDisabled = NULL;

  pos = CrPsEvtConfigGetEidPos(1);
  if (pos != -1) {
    isEidDisabled = isEidDisabled_1;
    sevLevel = 1;
  }

  pos = CrPsEvtConfigGetEidPos(2);
  if (pos != -1) {
    isEidDisabled = isEidDisabled_2;
    sevLevel = 2;
  }

  pos = CrPsEvtConfigGetEidPos(3);
  if (pos != -1) {
    isEidDisabled = isEidDisabled_3;
    sevLevel = 3;
  }

  pos = CrPsEvtConfigGetEidPos(4);
  if (pos != -1) {
    isEidDisabled = isEidDisabled_4;
    sevLevel = 4;
  }

  if (isEidDisabled == NULL)
    return 0;

  if (enableStatus == 0) {
    isEidDisabled[pos] = 1;
    CrFwOutRegistrySetEnable(EVT_TYPE,sevLevel,evtId,0);
  } else {
    isEidDisabled[pos] = 0;
    CrFwOutRegistrySetEnable(EVT_TYPE,sevLevel,evtId,0);
  }

  return sevLevel;
}

/* ------------------------------------------------------------------------------------------------ */
CrFwBool_t CrPsEvtConfigGetEidEnableStatus (CrPsEvtId_t evtId) {
  unsigned int pos;
  CrPsEvtId_t* isEidDisabled = NULL;

  pos = CrPsEvtConfigGetEidPos(1);
  if (pos != -1)
    isEidDisabled = isEidDisabled_1;

  pos = CrPsEvtConfigGetEidPos(2);
  if (pos != -1)
    isEidDisabled = isEidDisabled_2;

  pos = CrPsEvtConfigGetEidPos(3);
  if (pos != -1)
    isEidDisabled = isEidDisabled_3;

  pos = CrPsEvtConfigGetEidPos(4);
  if (pos != -1)
    isEidDisabled = isEidDisabled_4;

  if (isEidDisabled == NULL)
    return 0;

  if (isEidDisabled[pos] == 1)
    return 0;
  else
    return 1;
}

/* ------------------------------------------------------------------------------------------------ */
CrFwBool_t CrPsEvtConfigIsEidLegal(CrPsEvtId_t evtId) {
  if (CrPsEvtConfigGetEidPos(1) != -1)
    return 1;
  if (CrPsEvtConfigGetEidPos(2) != -1)
    return 1;
  if (CrPsEvtConfigGetEidPos(3) != -1)
    return 1;
  if (CrPsEvtConfigGetEidPos(4) != -1)
    return 1;

  return 0;
}

/* ------------------------------------------------------------------------------------------------ */
CrPsEvtId_t* CrPsEvtConfigGetListOfEid(unsigned int severityLevel) {
  switch (severityLevel) {
    case 1:
      return listOfEid_1;
    case 2:
      return listOfEid_2;
    case 3:
      return listOfEid_3;
    case 4:
      return listOfEid_4;
    default:            /* Illegal severity level */
      return NULL;
  }
}

/* ------------------------------------------------------------------------------------------------ */
CrFwBool_t* CrPsEvtConfigGetListOfDisabledEid(unsigned int severityLevel) {
    switch (severityLevel) {
      case 1:
        return isEidDisabled_1;
      case 2:
        return isEidDisabled_2;
      case 3:
        return isEidDisabled_3;
      case 4:
        return isEidDisabled_4;
      default:            /* Illegal severity level */
        return NULL;
    }
}

/* ------------------------------------------------------------------------------------------------ */
void CrPsEvtConfigLoadEvtIdPos(unsigned int sevLevel, unsigned int pos) {
  evtSevLevel = sevLevel;
  evtPos = pos;
}

/* ------------------------------------------------------------------------------------------------ */
void CrPsEvtConfigGetEvtIdPos(unsigned int* pSevLevel, unsigned int* pPos) {
  *pSevLevel = evtSevLevel;
  *pPos = evtPos;
}

/* ------------------------------------------------------------------------------------------------ */
void CrPsEvtConfigGetNextEvtId(unsigned int sevLevel, unsigned int pos,
                                            unsigned int* nextSevLevel, unsigned int* nextPos) {

   /* Handle default case where we are within a List of Event Identifiers */
   *nextSevLevel = sevLevel;
   *nextPos = pos + 1;

   /* Handle case where we are at the end of a List of Event Identifiers */
   switch (sevLevel) {
       case 1:
           if (pos >= N_OF_DER_PCKT_EVT_REP1) {
               *nextSevLevel = sevLevel + 1;
               *nextPos = 0;
           }
           break;
       case 2:
           if (pos >= N_OF_DER_PCKT_EVT_REP2) {
               *nextSevLevel = sevLevel + 1;
               *nextPos = 0;
           }
           break;
       case 3:
           if (pos >= N_OF_DER_PCKT_EVT_REP3) {
               *nextSevLevel = sevLevel + 1;
               *nextPos = 0;
           }
           break;
       case 4:
           if (pos >= N_OF_DER_PCKT_EVT_REP4) {
               *nextSevLevel = 0;
               *nextPos = 0;
           }
           break;
       default:
           *nextSevLevel = -1;
           *nextPos = 0;
   }
}
