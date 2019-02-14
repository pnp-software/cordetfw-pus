/**
 * @file
 *
 * Implementation of the configuration interface for the Housekeeping Service.
 *
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 *
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "Hk/CrPsHkConfig.h"
#include "Pckt/CrPsPcktHk.h"
#include "CrPsTypes.h"
#include "CrPsServTypeId.h"
#include "CrFwUserConstants.h"
#include "CrPsConstants.h"
#include "DataPool/CrPsDp.h"

#include <assert.h>

/* List of super-commutated sample repetition numbers (rep[1] .. rep[nGroup]) */
static unsigned int lstSampleRep[HK_MAX_N_GR];
/* List of numbers nRep[1] .. nRep[nGroup] of data items in each super-commutated group */
static CrPsNPar_t lstNSampRep[HK_MAX_N_GR];
/* List of identifiers of data items in the report */
static CrPsParId_t lstId[HK_N_REP_DEF*HK_MAX_N_ITEMS];

/* RDL Index Buffer */
static int rdlPosBuf[HK_N_REP_DEF];

/* ----------------------------------------------------------------------------------- */
static int CrPsHkConfigGetRdlSlot(CrPsSID_t sid) {
  int i;

  for (i=0; i<HK_N_REP_DEF; i++)
    if (getDpHkSidItem(i) == sid)
      return i;

  return -1;
}


/* ----------------------------------------------------------------------------------- */
void CrPsHkConfigInit() {
  int i;

  /* Check non-overlap of parameter and variable data pool identifiers */
  if (DpIdParamsHighest >= DpIdVarsLowest)
    CrFwSetAppErrCode(crPsDpParVarIdOverlap);

  /* Initialize RDL to be empty (an RDL slot is empty if its SID is equal to 0) */
  for (i=0; i<HK_N_REP_DEF; i++)
    setDpHkSidItem(i, 0);
}

/* ----------------------------------------------------------------------------------- */
int CrPsHkConfigSetSidEnableStatus(CrPsSID_t sid, CrFwBool_t enableStatus) {
  int rdlPos;

  rdlPos = CrPsHkConfigGetRdlSlot(sid);
  if (rdlPos > -1)
    setDpHkIsEnabledItem(rdlPos, enableStatus);

  return rdlPos;
}

/* ----------------------------------------------------------------------------------- */
int CrPsHkConfigClearSid(CrPsSID_t sid) {
  int rdlPos;

  rdlPos = CrPsHkConfigGetRdlSlot(sid);
  if (rdlPos > -1)
    setDpHkSidItem(rdlPos, 0);

  return rdlPos;
}

/* ----------------------------------------------------------------------------------- */
void CrPsHkConfigLoadSidDef(unsigned int rdlPos, CrPsSID_t sid, CrPsNPar_t nOfItems, CrFwDestSrc_t dest,
                                    CrPsCycleCnt_t collectionInt, CrPsParId_t* parId) {
  CrPsNPar_t i;

  setDpHkSidItem(rdlPos, sid);
  setDpHkNSimpleItem(rdlPos, nOfItems);
  setDpHkDestItem(rdlPos, dest);
  setDpHkIsEnabledItem(rdlPos, 0);
  setDpHkPeriodItem(rdlPos, collectionInt);
  for (i=0; i<nOfItems; i++)
    lstId[rdlPos*HK_MAX_N_ITEMS + i] = parId[i];
}

/* ----------------------------------------------------------------------------------- */
void CrPsHkConfigUpdateRep(unsigned int rdlSlot, void* target) {
  int i, pos;
  CrPsParId_t parId;
  size_t elementLength;
  unsigned int nOfElements;

  pos = 0;
  for (i=0; i<getDpHkNSimpleItem(rdlSlot); i++) {
    parId = lstId[rdlSlot*HK_MAX_N_ITEMS + i];
    getDpValueEx(parId, target+pos, &elementLength, &nOfElements);
    pos = pos + elementLength+nOfElements;
  }
}

int CrPsHkConfigGetFreeRdlSlot() {
  int i;
  for (i=0; i<HK_N_REP_DEF; i++)
    if (getDpHkSidItem(i) != 0)
      return i;

  return -1;
}

