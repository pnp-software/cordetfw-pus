/**
 * @file CrPsTestUtilities.h
 * @ingroup PUSTestsuite
 *
 * @brief Implementation of utility functions to support testing of the PUS Extension.
 *
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 *
 * @copyright P&P Software GmbH, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#include "CrPsTestUtilities.h"
#include "Pckt/CrPsPcktVer.h"

/* Include FW Profile files */
#include "FwSmCore.h"
#include "FwSmConfig.h"

/* Include framework files */
#include "CrFwCmpData.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "OutManager/CrFwOutManager.h"
#include "Pckt/CrFwPckt.h"
#include "DataPool/CrPsDpHk.h"
#include "OutFactory/CrFwOutFactory.h"
#include "InFactory/CrFwInFactory.h"
#include "OutManager/CrFwOutManager.h"
#include "InManager/CrFwInManager.h"
#include "InRegistry/CrFwInRegistry.h"
#include "OutRegistry/CrFwOutRegistry.h"
#include "OutLoader/CrFwOutLoader.h"
#include "CrPsServTypeId.h"
#include "Pckt/CrPsPcktHk.h"
#include "Hk/CrPsHkConfig.h"

/*-----------------------------------------------------------------------------*/
CrFwPckt_t CrPsTestUtilitiesCreateSAmple1Pckt(CrFwDestSrc_t dest, CrFwBool_t accAck, CrFwBool_t startAck,
         CrFwBool_t prgAck, CrFwBool_t termAck, CrFwSeqCnt_t seqCnt, CrFwGroup_t group) {
  CrFwPckt_t inPckt;

  inPckt = CrFwPcktMake(100);
  CrFwPcktSetServType(inPckt,255);
  CrFwPcktSetServSubType(inPckt,1);
  CrFwPcktSetCmdRepType(inPckt, crCmdType);
  CrFwPcktSetCmdRepId(inPckt,0);
  CrFwPcktSetSrc(inPckt,0);
  CrFwPcktSetDest(inPckt,dest);
  CrFwPcktSetGroup(inPckt,group);
  CrFwPcktSetAckLevel(inPckt,accAck,startAck,prgAck,termAck);
  CrFwPcktSetSeqCnt(inPckt,seqCnt);
  return inPckt;
 }

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsTestUtilitiesCheckOutManagerCmp(FwSmDesc_t outManager, int i,
                 CrFwServType_t servType, CrFwServSubType_t servSubType, CrFwDiscriminant_t disc) {
  CrFwCmpData_t* outManagerData;
  CrFwOutManagerData_t* outManagerCSData;
  FwSmDesc_t outCmp;

  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[i];
  if (outCmp == NULL)
      return 0;
  if (CrFwOutCmpGetServType(outCmp) != servType)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != servSubType)
    return 0;
  if (disc != 0)
    if (CrFwOutCmpGetDiscriminant(outCmp) != disc)
      return 0;
  
  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsTestUtilitiesCheckOutManagerCmdRejRep(FwSmDesc_t outManager, int i,
                          CrFwServSubType_t servSubType, CrPsFailCode_t failCode, CrPsFailData_t failData) {
  CrFwCmpData_t* outManagerData;
  CrFwOutManagerData_t* outManagerCSData;
  FwSmDesc_t outCmp;
  CrFwPckt_t pckt;

  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[i];
  pckt = CrFwOutCmpGetPckt(outCmp);
  if (outCmp == NULL)
      return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != servSubType)
    return 0;
  if (failCode != 0) {
    if (getVerFailedPrgrRepTcFailCode(pckt) != failCode)
      return 0;
    if (failData != 0)
      if (getVerFailedPrgrRepTcFailData(pckt) != failData)
        return 0;
  }

  return 1;
}
  
/*-----------------------------------------------------------------------------*/
FwSmDesc_t CrPsTestUtilitiesGetItemFromInManager(FwSmDesc_t inManager, int i) {
  CrFwCmpData_t* inManagerDataLocal = (CrFwCmpData_t*)FwSmGetData(inManager);
  CrFwInManagerData_t* inManagerCSData = (CrFwInManagerData_t*)inManagerDataLocal->cmpSpecificData;
  return inManagerCSData->pcrl[i];
}

/*-----------------------------------------------------------------------------*/
FwSmDesc_t CrPsTestUtilitiesGetItemFromOutManager(FwSmDesc_t outManager, int i) {
  CrFwCmpData_t* outManagerData;
  CrFwOutManagerData_t* outManagerCSData;

  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  return outManagerCSData->pocl[i];
}

/*-----------------------------------------------------------------------------*/
void CrPsTestUtilitiesClearRDL() {
  int i;
  CrPsSID_t sid;

  for (i=0; i<HK_N_REP_DEF; i++)
    setDpHkSidItem(i, 0);

  for (sid=1; sid<HK_MAX_SID; sid++)
    CrPsHkConfigClearSid(sid);
}

/*-----------------------------------------------------------------------------*/
void CrPsTestUtilitiesResetFw() {
  FwSmDesc_t outFactory, outLoader, outRegistry, outManager, outStream;
  FwSmDesc_t inFactory, inRegistry, inManager;

  CrFwSetAppErrCode(crNoAppErr);

  outManager = CrFwOutManagerMake(0);
  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  outFactory = CrFwOutFactoryMake();
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  outLoader = CrFwOutLoaderMake();
  CrFwCmpInit(outLoader);
  CrFwCmpReset(outLoader);
  outRegistry = CrFwOutRegistryMake();
  CrFwCmpInit(outRegistry);
  CrFwCmpReset(outRegistry);
  outStream = CrFwOutStreamMake(0);
  CrFwCmpInit(outStream);
  CrFwCmpReset(outStream);

  inManager = CrFwInManagerMake(0);
  CrFwCmpInit(inManager);
  CrFwCmpReset(inManager);
  inFactory = CrFwInFactoryMake();
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  inRegistry = CrFwInRegistryMake();
  CrFwCmpInit(inRegistry);
  CrFwCmpReset(inRegistry);

}

/*-----------------------------------------------------------------------------*/
FwSmDesc_t CrPsTestUtilitiesMake3s1(CrPsSID_t sid, CrPsNPar_t N1, CrPsParId_t* parId) {
  CrFwPckt_t pckt;
  int i;

  pckt = CrFwPcktMake(CR_FW_MAX_PCKT_LENGTH);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,HK_TYPE);
  CrFwPcktSetServSubType(pckt,HKCREHKCMD_STYPE);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,0);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);
  CrFwPcktSetSeqCnt(pckt,1);
  setHkCreHkCmdSID(pckt,sid);
  setHkCreHkCmdCollectionInterval(pckt, 1);
  setHkCreHkCmdN1(pckt, N1);
  for (i=0; i<N1; i++)
      setHkCreHkCmdN1ParamId(pckt, i, parId[i]);

  return CrFwInFactoryMakeInCmd(pckt);

}
