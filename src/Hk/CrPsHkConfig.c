/**
 * @file
 * @ingroup man_hk
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
#include "DataPool/CrPsDpHk.h"

/* Include CORDET Framework Files */
#include "OutCmp/CrFwOutCmp.h"
#include "InCmd/CrFwInCmd.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"

/* Include FW Profile Files */
#include "FwSmConfig.h"

#include <assert.h>

/** List of identifiers of data items in the reports defined in the RDL */
static CrPsParId_t lstId[HK_N_REP_DEF*HK_MAX_N_ITEMS];

/**
 * Array of flags indicating whether a SID is currently defined in the RDL.
 * If the report with a SID equal to j is pending in the RDL, then rdlIndex[j] holds
 * the index of the RDL slot where the report is loaded. Otherwise, rdlIndex[j] is equal to -1.  */
static short int rdlIndex[HK_MAX_SID+1];

/* ----------------------------------------------------------------------------------- */
void CrPsHkConfigInit() {
  int i;

  /* Check non-overlap of parameter and variable data pool identifiers */
  if (DpIdParamsHighest >= DpIdVarsLowest)
    CrFwSetAppErrCode(crPsDpParVarIdOverlap);

  /* Initialize RDL to be empty (an RDL slot is empty if its SID is equal to 0) */
  for (i=0; i<HK_N_REP_DEF; i++)
    setDpHkSidItem(i, 0);

  /* Initialize of RDL Slot Index */
  for (i=1; i<HK_MAX_SID+1; i++)
    rdlIndex[i] = -1;
}

/* ----------------------------------------------------------------------------------- */
void CrPsHkConfigClearSid(CrPsSID_t sid) {
  short int rdlPos = rdlIndex[sid];
  setDpHkSidItem(rdlPos, 0);
  rdlIndex[sid] = -1;
}

/* ----------------------------------------------------------------------------------- */
void CrPsHkConfigHkRep(FwSmDesc_t rep, short int rdlPos, CrPsSID_t sid, CrPsNPar_t nOfItems,
                    CrFwDestSrc_t dest, CrPsCycleCnt_t collectionInt, CrPsParId_t* parId) {
  CrPsNPar_t i;
  CrFwPckt_t pckt = CrFwOutCmpGetPckt(rep);

  /* Configure the report */
  CrFwOutCmpSetDest(rep, dest);
  setHkRepSID(pckt, sid);

  /* Set up report's definition in the RDL */
  setDpHkSidItem(rdlPos, sid);
  setDpHkNSimpleItem(rdlPos, nOfItems);
  setDpHkDestItem(rdlPos, dest);
  setDpHkIsEnabledItem(rdlPos, 0);
  setDpHkPeriodItem(rdlPos, collectionInt);
  setDpHkCycleCntItem(rdlPos, 0);

  for (i=0; i<nOfItems; i++)
    lstId[rdlPos*HK_MAX_N_ITEMS + i] = parId[i];

  /* Set up the link between the report and the RDL slot where it is defined */
  rdlIndex[sid] = rdlPos;
}

/* ----------------------------------------------------------------------------------- */
void CrPsHkConfigHkRepOnBoard(FwSmDesc_t rep, short int rdlPos, FwSmDesc_t createCmd) {
    CrPsNPar_t i;
    CrFwPckt_t pcktCmd = CrFwInCmdGetPckt(createCmd);
    CrFwPckt_t pcktRep = CrFwOutCmpGetPckt(rep);
    CrPsSID_t sid;
    CrPsNPar_t nOfItems;
    CrFwDestSrc_t dest;
    CrPsCycleCnt_t collectionInt;

    /* Configure the report */
    dest = CrFwInCmdGetSrc(createCmd);
    CrFwOutCmpSetDest(rep, dest);
    sid = getHkCreHkCmdSID(pcktCmd);
    setHkRepSID(pcktRep, sid);

    /* Set up report's definition in the RDL */
    setDpHkSidItem(rdlPos, sid);
    nOfItems = getHkCreHkCmdN1(pcktCmd);
    setDpHkNSimpleItem(rdlPos, nOfItems);
    setDpHkDestItem(rdlPos, dest);
    setDpHkIsEnabledItem(rdlPos, 0);
    collectionInt = getHkCreHkCmdCollectionInterval(pcktCmd);
    setDpHkPeriodItem(rdlPos, collectionInt);
    setDpHkCycleCntItem(rdlPos, 0);

    for (i=0; i<nOfItems; i++)
      lstId[rdlPos*HK_MAX_N_ITEMS + i] = getHkCreHkCmdN1ParamId(pcktCmd,i);

    /* Set up the link between the report and the RDL slot where it is defined */
    rdlIndex[sid] = rdlPos;
}

/* ----------------------------------------------------------------------------------- */
void CrPsHkConfigUpdateRep(short int rdlSlot, FwSmDesc_t hkRep) {
  int i, pos;
  CrPsParId_t parId;
  size_t elementLength;
  unsigned int nOfElements;
  CrFwPckt_t pckt = CrFwOutCmpGetPckt(hkRep);

  pos = LEN_HK_REP - sizeof(CrFwCrc_t);
  for (i=0; i<getDpHkNSimpleItem(rdlSlot); i++) {
    parId = lstId[rdlSlot*HK_MAX_N_ITEMS + i];
    getDpValueEx(parId, &pckt[pos], &elementLength, &nOfElements);
    pos = pos + elementLength*nOfElements;
  }
}

/* ----------------------------------------------------------------------------------- */
short int CrPsHkConfigGetFreeRdlSlot() {
  int i;
  for (i=0; i<HK_N_REP_DEF; i++)
    if (getDpHkSidItem(i) == 0)
      return i;

  return -1;
}

/* ----------------------------------------------------------------------------------- */
short int CrPsHkConfigGetRdlSlot(CrPsSID_t sid) {
  if (sid > HK_MAX_SID)
    return -1;
  return rdlIndex[sid];
}

/* ----------------------------------------------------------------------------------- */
CrPsParId_t CrPsHkConfigGetParamId(short int rdlSlot, CrPsNPar_t i) {
  return lstId[rdlSlot*HK_MAX_N_ITEMS + i];
}
