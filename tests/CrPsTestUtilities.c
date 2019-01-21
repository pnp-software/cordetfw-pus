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

/* Include FW Profile files */
#include "FwSmCore.h"
#include "FwSmConfig.h"

/* Include framework files */
#include "CrFwCmpData.h"
#include "OutManager/CrFwOutManager.h"
#include "Pckt/CrFwPckt.h"


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
FwSmDesc_t CrPsTestUtilitiesGetItemFromInManager(FwSmDesc_t inManager, int i) {
  CrFwCmpData_t* inManagerDataLocal = (CrFwCmpData_t*)FwSmGetData(inManager);
  CrFwInManagerData_t* inManagerCSData = (CrFwInManagerData_t*)inManagerDataLocal->cmpSpecificData;
  return inManagerCSData->pcrl[i];
}

/*-----------------------------------------------------------------------------*/
FwSmDesc_t  CrPsTestUtilitiesGetItemFromOutManager(FwSmDesc_t outManager, int i) {
  CrFwCmpData_t* outManagerData;
  CrFwOutManagerData_t* outManagerCSData;

  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  return outManagerCSData->pocl[i];
}
