/**
 * @file CrPsHkTestCases.c
 * @ingroup PUSTestsuite
 *
 * @brief Implementation of test cases for the Housekeeping Service.
 *
 * @author Alessandro Pasetti  <pasetti@pnp-software.com>
 * 
 * @copyright P&P Software GmbH, 2018 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 */

#include "CrPsHkTestCases.h"

/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"

/* Include configuration files */
#include "CrFwInStreamUserPar.h"
#include "CrFwOutRegistryUserPar.h"
#include "CrFwOutFactoryUserPar.h"
#include "CrFwRepErrStub.h"

/* Include framework files */
#include "CrFwCmpData.h"
#include "OutRegistry/CrFwOutRegistry.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include "InCmd/CrFwInCmd.h"
#include "InFactory/CrFwInFactory.h"
#include "OutFactory/CrFwOutFactory.h"
#include "OutLoader/CrFwOutLoader.h"
#include "OutManager/CrFwOutManager.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"

#include "Pckt/CrPsPcktHk.h"
#include "Pckt/CrPsPcktEvt.h"
#include "Pckt/CrPsPckt.h"
#include "DataPool/CrPsDpVer.h"
#include "DataPool/CrPsDpEvt.h"
#include "Hk/CrPsHkConfig.h"
#include "CrPsServTypeId.h"
#include "CrPsConstants.h"
#include "CrPsTypes.h"
#include "CrPsTestUtilities.h"
#include "Dum/CrPsInCmdDumSample1Ctrl.h"
#include "CrPsOutStreamStub.h"
#include "DataPool/CrPsDp.h"
#include "DataPool/CrPsDpHk.h"
#include "DataPool/CrPsDpFct.h"

/* Include system files */
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsHkTestCase1() {
  int rdlPos,i;
  FwSmDesc_t rep, outFactory;
  CrPsParId_t parId1[HK_NOFITEMS_SID_HK_CNT] = HK_DEF_SID_HK_CNT;
  CrPsParId_t parId2[HK_NOFITEMS_SID_N_OF_EVT] = HK_DEF_SID_N_OF_EVT;

  CrFwSetAppErrCode(crNoAppErr);

  /* Initialize and configure the OutFactory */
  outFactory = CrFwOutFactoryMake();
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);

  /* Get a free slot and create the RDL entry for the first pre-defined HK packet */
  rdlPos = CrPsHkConfigGetFreeRdlSlot();
  if (rdlPos == -1)
      return 0;

  rep = CrFwOutFactoryMakeOutCmp(HK_TYPE, HKREP_STYPE, 0, LEN_HK_REP_SID_HK_CNT);
  if (rep == NULL)
      return 0;
  CrPsHkConfigHkRep(rep, rdlPos, SID_HK_CNT, HK_NOFITEMS_SID_HK_CNT, 0, 1, &parId1[0]);
  if (CrPsHkConfigGetRdlSlot(SID_HK_CNT) != rdlPos)
      return 0;
  assert(SID_HK_CNT == 2);      /* The test only works if the predefined reports have SIDs 1 and 2 */

  /* Get a free slot and create the RDL entry for the second pre-defined HK packet */
  rdlPos = CrPsHkConfigGetFreeRdlSlot();
  if (rdlPos == -1)
      return 0;

  rep = CrFwOutFactoryMakeOutCmp(HK_TYPE, HKREP_STYPE, 0, LEN_HK_REP_SID_N_OF_EVT);
  if (rep == NULL)
      return 0;
  CrPsHkConfigHkRep(rep, rdlPos, SID_N_OF_EVT, HK_NOFITEMS_SID_N_OF_EVT, 0, 2, &parId2[0]);
  if (CrPsHkConfigGetRdlSlot(SID_N_OF_EVT) != rdlPos)
      return 0;
  assert(SID_N_OF_EVT == 1);      /* The test only works if the predefined reports have SIDs 1 and 2 */

  /* Fill up the RDL and then attempt to get a free slot */
  for (i=0; i<HK_N_REP_DEF-2; i++) {
      rdlPos = CrPsHkConfigGetFreeRdlSlot();
      if (rdlPos == -1)
          return 0;
      CrPsHkConfigHkRep(rep, rdlPos, i+SID_HK_CNT+1, HK_NOFITEMS_SID_N_OF_EVT, 0, 2, parId1);
      assert((i+SID_HK_CNT)<HK_MAX_SID);    /* Check that we have used a legal SID */
  }
  if (CrPsHkConfigGetFreeRdlSlot() != -1)
      return 0;

  /* Clear the RDL */
  for (i=0; i<HK_N_REP_DEF; i++) {
      CrPsHkConfigClearSid(i+1);
  }

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsHkTestCase2() {
  CrFwPckt_t pckt;
  FwSmDesc_t inCmd, rep;
  FwSmDesc_t outManager;
  short int rdlPos, i;
  CrPsParId_t parId[2] = {DpIdnOfAllocatedInCmd, DpIdnOfAllocatedInRep};

  /* Reset the framework components */
  CrPsTestUtilitiesResetFw();
  outManager = CrFwOutManagerMake(0);

  /* Create a (3,1) command */
  inCmd = CrPsHkTestCaseMake3s1(1, 2, parId);

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != HK_TYPE)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != HKCREHKCMD_STYPE)
    return 0;

  /* Fill-up the RDL with reports with the layout of the pre-defined report SID_N_OF_EVT and with increasing SID */
  for (i=0; i<HK_N_REP_DEF; i++) {
      rep = CrFwOutFactoryMakeOutCmp(HK_TYPE, HKREP_STYPE, 0, LEN_HK_REP_SID_N_OF_EVT);
      rdlPos = CrPsHkConfigGetFreeRdlSlot();
      if (rdlPos == -1)
          return 0;
      CrPsHkConfigHkRep(rep, rdlPos, i+1, 1, 0, 2, parId);
  }

  /* Execute and terminate the InCommand  (this simulates the action of an InManager) */
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);

  /*check that the InCommand is in ABORTED state*/
  if (!CrFwInCmdIsInAborted(inCmd))
    return 0;

  /* Check that there is a pending OutComponent of type (1,4) */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != HK_N_REP_DEF+1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,0,4,VER_FULL_RDL,0) != 1)
      return 0;

  /* ---------------------------------------- Step 2 ---------------------------*/
  /* Remove all RDL entries but the first one */
  for (i=1; i<HK_N_REP_DEF; i++) {
      CrPsHkConfigClearSid(i+1);
      if (rdlPos == -1)
          return 0;
  }

  /* Create a (3,1) command with illegal SID and then execute and verify error */
  inCmd = CrPsHkTestCaseMake3s1(1, 2, parId);
  pckt = CrFwInCmdGetPckt(inCmd);
  setHkCreHkCmdSID(pckt,HK_MAX_SID+1);

  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);
  if (!CrFwInCmdIsInAborted(inCmd))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != HK_N_REP_DEF+2)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,1,4,VER_ILL_SID,HK_MAX_SID+1) != 1)
      return 0;

  /* ---------------------------------------- Step 3 ---------------------------*/
  /* Create a (3,1) command with SID equal to zero and then execute and verify error */
  inCmd = CrPsHkTestCaseMake3s1(1, 2, parId);
  pckt = CrFwInCmdGetPckt(inCmd);
  setHkCreHkCmdSID(pckt,0);

  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);
  if (!CrFwInCmdIsInAborted(inCmd))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != HK_N_REP_DEF+3)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,2,4,VER_ILL_SID,0) != 1)
      return 0;

  /* ---------------------------------------- Step 4 ---------------------------*/
  /* Create a (3,1) command to have an illegal number of data items and then execute and verify error */
  inCmd = CrPsHkTestCaseMake3s1(1, 2, parId);
  pckt = CrFwInCmdGetPckt(inCmd);
  setHkCreHkCmdN1(pckt, HK_MAX_N_SIMPLE+1);

  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);
  if (!CrFwInCmdIsInAborted(inCmd))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != HK_N_REP_DEF+4)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,3,4,VER_ILL_NID,HK_MAX_N_SIMPLE+1) != 1)
      return 0;

  /* ---------------------------------------- Step 3 ---------------------------*/
  /* Create a (3,1) command to have an illegal data item identifier and then execute and verify error */
  inCmd = CrPsHkTestCaseMake3s1(1, 2, parId);
  pckt = CrFwInCmdGetPckt(inCmd);
  setHkCreHkCmdN1ParamId(pckt, 0, DpIdParamsLowest-1);

  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);
  if (!CrFwInCmdIsInAborted(inCmd))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != HK_N_REP_DEF+5)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,4,4,VER_ILL_DI_ID,DpIdParamsLowest-1) != 1)
      return 0;

  /* ---------------------------------------- Step 3 ---------------------------*/
  /* Create a (3,1) command to have an illegal data item identifier and then execute and verify error */
  inCmd = CrPsHkTestCaseMake3s1(1, 2, parId);
  pckt = CrFwInCmdGetPckt(inCmd);
  setHkCreHkCmdN1ParamId(pckt, 0, DpIdVarsHighest+1);

  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);
  if (!CrFwInCmdIsInAborted(inCmd))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != HK_N_REP_DEF+6)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,5,4,VER_ILL_DI_ID,DpIdVarsHighest+1) != 1)
      return 0;

  /* ---------------------------------------- Step 3 ---------------------------*/
  /* Change the InCommand's SID to be equal to 1 and then execute and verify error */
  inCmd = CrPsHkTestCaseMake3s1(1, 2, parId);
  pckt = CrFwInCmdGetPckt(inCmd);
  setHkCreHkCmdSID(pckt,1);

  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);
  if (!CrFwInCmdIsInAborted(inCmd))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != HK_N_REP_DEF+7)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,6,4,VER_SID_IN_USE,1) != 1)
      return 0;
  /* ---------------------------------------------------------------------------*/
  /* Clear all entries in the RDL */
  CrPsTestUtilitiesClearRDL();

  /* Reset the framework components */
  CrPsTestUtilitiesResetFw();

  /* Check that no packets are allocated */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsHkTestCase3() {
  FwSmDesc_t inCmd;
  FwSmDesc_t outManager = CrFwOutManagerMake(0);
  CrPsSID_t preDefSID = 1;
  CrPsParId_t parId[HK_NOFITEMS_SID_N_OF_EVT] = HK_DEF_SID_N_OF_EVT;    /* Pre-defined HK report */
  CrFwDestSrc_t src3s1 = EVT_DEST;
  CrFwPckt_t pckt;
  short int rdlPos;
  CrPsCycleCnt_t collectionInt;
  CrPsNEvtRep_t SID_N_OF_EVTnOfDetectedEvts[4];

  /* Reset the framework components */
  CrPsTestUtilitiesResetFw();

  /* Create a (3,1) command and set its source */
  inCmd = CrPsHkTestCaseMake3s1(preDefSID, HK_NOFITEMS_SID_N_OF_EVT, parId);
  pckt = CrFwInCmdGetPckt(inCmd);
  CrFwPcktSetSrc(pckt, src3s1);

  /* Execute and terminate the InCommand  (this simulates the action of an InManager) */
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);

  /*check that the InCommand is in TERMINATED state*/
  if (!CrFwInCmdIsInTerminated(inCmd))
    return 0;

  /* Check that there is a pending OutComponent of type (3,1) */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmp(outManager,0,HK_TYPE,HKREP_STYPE,preDefSID) != 1)
      return 0;

  /* Execute the OutManager and verify that no HK report is generated */
  CrFwCmpExecute(outManager);
  if (CrPsOutStreamStubGetHandoverCnt()>0)
      return 0;

  /* Enable the pending HK report in the RDL, execute it again and check that the report is generated */
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID);
  setDpHkIsEnabledItem(rdlPos, 1);
  CrFwCmpExecute(outManager);
  if (CrPsOutStreamStubGetHandoverCnt() != 1)
      return 0;
  pckt = CrPsOutStreamStubGetPckt(0);
  if (CrFwPcktGetDest(pckt) != src3s1)
      return 0;

  /* Execute OutManager twice and verify that the report is generated twice */
  CrFwCmpExecute(outManager);
  CrFwCmpExecute(outManager);
  if (CrPsOutStreamStubGetHandoverCnt() != 3)
      return 0;

  /* Verify that the content of the report is updated at each execution */
  setDpEvtNOfDetectedEvtsItem(0,111);   /* This is the first item in the HK report */
  CrFwCmpExecute(outManager);
  if (CrPsOutStreamStubGetHandoverCnt() != 4)
      return 0;
  pckt = CrPsOutStreamStubGetPckt(0);
  getHkRep_SID_N_OF_EVTnOfDetectedEvts(pckt, SID_N_OF_EVTnOfDetectedEvts);
  if ((SID_N_OF_EVTnOfDetectedEvts[0] != 111) && (SID_N_OF_EVTnOfDetectedEvts[0] != 111*256))   /* The check covers both endianness cases */
      return 0;

  /* Change execution period and verify the generation frequency changes too */
  collectionInt = 3;
  setDpHkPeriodItem(rdlPos, collectionInt);
  CrFwCmpExecute(outManager);
  CrFwCmpExecute(outManager);
  CrFwCmpExecute(outManager);
  if (CrPsOutStreamStubGetHandoverCnt() != 5)
      return 0;

  /* Set cycle counter and period to zero and verify that report is generated only once */
  setDpHkPeriodItem(rdlPos, 0);
  setDpHkCycleCntItem(rdlPos, 0);
  CrFwCmpExecute(outManager);
  if (CrPsOutStreamStubGetHandoverCnt() != 6)
      return 0;
  CrFwCmpExecute(outManager);
  CrFwCmpExecute(outManager);
  CrFwCmpExecute(outManager);
  CrFwCmpExecute(outManager);
  CrFwCmpExecute(outManager);
  CrFwCmpExecute(outManager);
  if (CrPsOutStreamStubGetHandoverCnt() != 6)
      return 0;

  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Reset the framework components */
  CrPsTestUtilitiesResetFw();

  /* Check that no packets are allocated */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsHkTestCase4() {
  FwSmDesc_t inCmd3s5, inCmd3s1, inCmd3s7;
  FwSmDesc_t outManager = CrFwOutManagerMake(0);
  CrPsParId_t parId2[HK_NOFITEMS_SID_HK_CNT] = HK_DEF_SID_HK_CNT;    /* Pre-defined HK report */
  CrPsParId_t parId1[HK_NOFITEMS_SID_N_OF_EVT] = HK_DEF_SID_N_OF_EVT;    /* Pre-defined HK report */
  CrPsSID_t sid[2] = {1, 2};
  CrPsSID_t preDefSID1 = 1;
  CrPsSID_t preDefSID2 = 2;
  int nOfOutCmp, rdlPos;
  CrFwPckt_t pckt;
  CrFwDestSrc_t inCmdSrc = 99;

  /* Reset the framework components and clear the RDL*/
  CrPsTestUtilitiesResetFw();
  CrPsHkConfigInit();

  /* Create a (3,5) command and execute it */
  inCmd3s5 = CrPsHkTestCaseMake3s5(sid, 2);
  CrFwCmpExecute(inCmd3s5);
  CrFwInCmdTerminate(inCmd3s5);

  /*check that the InCommand is in PROGRESS state and one (1,6) report was generated */
  if (!CrFwInCmdIsInProgress(inCmd3s5))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,0,6,VER_ILL_SID,1) != 1)
      return 0;

  /* Execute the command again and verify that it terminates */
  CrFwCmpExecute(inCmd3s5);
  CrFwInCmdTerminate(inCmd3s5);
  if (!CrFwInCmdIsInAborted(inCmd3s5))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 3)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,1,6,VER_ILL_SID,2) != 1)
      return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,2,8,VER_MI_S3_FD,2) != 1)
      return 0;

  /* -------------------------------------------------------------------------- */
  /* Load two HK reports */

  inCmd3s1 = CrPsHkTestCaseMake3s1(preDefSID1, HK_NOFITEMS_SID_N_OF_EVT, parId1);
  CrFwCmpExecute(inCmd3s1);
  CrFwInCmdTerminate(inCmd3s1);
  inCmd3s1 = CrPsHkTestCaseMake3s1(preDefSID2, HK_NOFITEMS_SID_HK_CNT, parId2);
  CrFwCmpExecute(inCmd3s1);
  CrFwInCmdTerminate(inCmd3s1);

  /* Create a (3,5) command with one loaded and one illegal SID */
  sid[0] = preDefSID1;
  sid[1] = HK_MAX_SID+1;    /* Illegal SID */
  inCmd3s5 = CrPsHkTestCaseMake3s5(sid, 2);
  nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
  CrFwCmpExecute(inCmd3s5);
  CrFwInCmdTerminate(inCmd3s5);
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp)
      return 0;
  CrFwCmpExecute(inCmd3s5);
  CrFwInCmdTerminate(inCmd3s5);
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp+2)
      return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,nOfOutCmp,6,VER_ILL_SID,HK_MAX_SID+1) != 1)
      return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,nOfOutCmp+1,8,VER_MI_S3_FD,1) != 1)
      return 0;

  /* Check that the first SID is now enabled */
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID1);
  if (getDpHkIsEnabledItem(rdlPos) != 1)
      return 0;
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID2);
  if (getDpHkIsEnabledItem(rdlPos) != 0)
      return 0;

  /* -------------------------------------------------------------------------- */
  /* Create a (3,5) command with two loaded SIDs */
  sid[0] = preDefSID1;
  sid[1] = preDefSID2;
  inCmd3s5 = CrPsHkTestCaseMake3s5(sid, 2);
  nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
  CrFwCmpExecute(inCmd3s5);
  CrFwInCmdTerminate(inCmd3s5);
  CrFwCmpExecute(inCmd3s5);
  CrFwInCmdTerminate(inCmd3s5);
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp)
      return 0;

  /* Check that both SIDs are now enabled */
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID1);
  if (getDpHkIsEnabledItem(rdlPos) != 1)
      return 0;
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID2);
  if (getDpHkIsEnabledItem(rdlPos) != 1)
      return 0;

  /* -------------------------------------------------------------------------- */
  /* Disable SID */
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID1);
  setDpHkIsEnabledItem(rdlPos, 0);

  /* Create a (3,7) command with one loaded SID and with non-standard source */
  sid[0] = preDefSID1;
  inCmd3s7 = CrPsHkTestCaseMake3s5(sid, 2);
  CrFwInCmdSetSrc(inCmd3s7, inCmdSrc);
  pckt = CrFwInCmdGetPckt(inCmd3s7);
  CrFwPcktSetServSubType(pckt, HKENBDIAGCMD_STYPE);

  CrFwCmpExecute(inCmd3s7);
  CrFwInCmdTerminate(inCmd3s7);

  /* Check that SID is now enabled and that it has the expected destination */
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID1);
  if (getDpHkIsEnabledItem(rdlPos) != 1)
      return 0;
  if (getDpHkDestItem(rdlPos) != inCmdSrc)
      return 0;

  /* -------------------------------------------------------------------------- */
  /*Release the InCommands */
  CrFwInFactoryReleaseInCmd(inCmd3s5);
  CrFwInFactoryReleaseInCmd(inCmd3s7);

  /* Reset the framework components */
  CrPsTestUtilitiesResetFw();

  /* Check that no packets are allocated */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsHkTestCase5() {
  FwSmDesc_t inCmd3s6, inCmd3s1, inCmd3s8;
  FwSmDesc_t outManager = CrFwOutManagerMake(0);
  CrPsParId_t parId2[HK_NOFITEMS_SID_HK_CNT] = HK_DEF_SID_HK_CNT;    /* Pre-defined HK report */
  CrPsParId_t parId1[HK_NOFITEMS_SID_N_OF_EVT] = HK_DEF_SID_N_OF_EVT;    /* Pre-defined HK report */
  CrPsSID_t sid[2] = {1, 2};
  CrPsSID_t preDefSID1 = 1;
  CrPsSID_t preDefSID2 = 2;
  int nOfOutCmp, rdlPos;
  CrFwPckt_t pckt;

  /* Reset the framework components and clear the RDL*/
  CrPsTestUtilitiesResetFw();
  CrPsHkConfigInit();

  /* Create a (3,6) command and execute it */
  inCmd3s6 = CrPsHkTestCaseMake3s6(sid, 2);
  CrFwCmpExecute(inCmd3s6);
  CrFwInCmdTerminate(inCmd3s6);

  /*check that the InCommand is in PROGRESS state and one (1,6) report was generated */
  if (!CrFwInCmdIsInProgress(inCmd3s6))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,0,6,VER_ILL_SID,1) != 1)
      return 0;

  /* Execute the command again and verify that it terminates */
  CrFwCmpExecute(inCmd3s6);
  CrFwInCmdTerminate(inCmd3s6);
  if (!CrFwInCmdIsInAborted(inCmd3s6))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 3)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,1,6,VER_ILL_SID,2) != 1)
      return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,2,8,VER_MI_S3_FD,2) != 1)
      return 0;

  /* -------------------------------------------------------------------------- */
  /* Load two HK reports and then enable them */
  inCmd3s1 = CrPsHkTestCaseMake3s1(preDefSID1, HK_NOFITEMS_SID_N_OF_EVT, parId1);
  CrFwCmpExecute(inCmd3s1);
  CrFwInCmdTerminate(inCmd3s1);
  inCmd3s1 = CrPsHkTestCaseMake3s1(preDefSID2, HK_NOFITEMS_SID_HK_CNT, parId2);
  CrFwCmpExecute(inCmd3s1);
  CrFwInCmdTerminate(inCmd3s1);
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID1);
  setDpHkIsEnabledItem(rdlPos, 1);
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID2);
  setDpHkIsEnabledItem(rdlPos, 1);

  /* Create a (3,6) command with one loaded and one illegal SID */
  sid[0] = preDefSID1;
  sid[1] = HK_MAX_SID+1;    /* Illegal SID */
  inCmd3s6 = CrPsHkTestCaseMake3s6(sid, 2);
  nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
  CrFwCmpExecute(inCmd3s6);
  CrFwInCmdTerminate(inCmd3s6);
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp)
      return 0;
  CrFwCmpExecute(inCmd3s6);
  CrFwInCmdTerminate(inCmd3s6);
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp+2)
      return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,nOfOutCmp,6,VER_ILL_SID,HK_MAX_SID+1) != 1)
      return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,nOfOutCmp+1,8,VER_MI_S3_FD,1) != 1)
      return 0;

  /* Check that the first SID is now disabled */
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID1);
  if (getDpHkIsEnabledItem(rdlPos) != 0)
      return 0;
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID2);
  if (getDpHkIsEnabledItem(rdlPos) != 1)
      return 0;

  /* -------------------------------------------------------------------------- */
  /* Create a (3,6) command with two loaded SIDs */
  sid[0] = preDefSID1;
  sid[1] = preDefSID2;
  inCmd3s6 = CrPsHkTestCaseMake3s6(sid, 2);
  nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
  CrFwCmpExecute(inCmd3s6);
  CrFwInCmdTerminate(inCmd3s6);
  CrFwCmpExecute(inCmd3s6);
  CrFwInCmdTerminate(inCmd3s6);
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp)
      return 0;

  /* Check that both SIDs are now disabled */
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID1);
  if (getDpHkIsEnabledItem(rdlPos) != 0)
      return 0;
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID2);
  if (getDpHkIsEnabledItem(rdlPos) != 0)
      return 0;

  /* -------------------------------------------------------------------------- */
  /* Enable SID */
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID1);
  setDpHkIsEnabledItem(rdlPos, 1);

  /* Create a (3,8) command with one loaded SID */
  sid[0] = preDefSID1;
  inCmd3s8 = CrPsHkTestCaseMake3s6(sid, 2);
  pckt = CrFwInCmdGetPckt(inCmd3s8);
  CrFwPcktSetServSubType(pckt, HKENBDIAGCMD_STYPE);

  CrFwCmpExecute(inCmd3s8);
  CrFwInCmdTerminate(inCmd3s8);

  /* Check that the SID is now disabled */
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID1);
  if (getDpHkIsEnabledItem(rdlPos) != 0)
      return 0;

  /* -------------------------------------------------------------------------- */
  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd3s6);

  /* Reset the framework components */
  CrPsTestUtilitiesResetFw();

  /* Check that no packets are allocated */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsHkTestCase6() {
  FwSmDesc_t inCmd3s3, inCmd3s1, inCmd3s4;
  FwSmDesc_t outManager = CrFwOutManagerMake(0);
  CrPsParId_t parId1[HK_NOFITEMS_SID_N_OF_EVT] = HK_DEF_SID_N_OF_EVT;    /* Pre-defined HK report */
  CrPsParId_t parId2[HK_NOFITEMS_SID_HK_CNT] = HK_DEF_SID_HK_CNT;    /* Pre-defined HK report */
  CrPsParId_t parId3[2] = {1, 2};
  CrPsSID_t sid[3];
  CrPsSID_t preDefSID1 = 1;
  CrPsSID_t preDefSID2 = 2;
  CrPsSID_t preDefSID3 = 6;
  int nOfOutCmp, rdlPos;
  CrFwPckt_t pckt;

  /* Reset the framework components and clear the RDL*/
  CrPsTestUtilitiesResetFw();
  CrPsHkConfigInit();

  /* Load three HK reports and then enable the first one */
  inCmd3s1 = CrPsHkTestCaseMake3s1(preDefSID1, HK_NOFITEMS_SID_N_OF_EVT, parId1);
  CrFwCmpExecute(inCmd3s1);
  CrFwInCmdTerminate(inCmd3s1);
  inCmd3s1 = CrPsHkTestCaseMake3s1(preDefSID2, HK_NOFITEMS_SID_HK_CNT, parId2);
  CrFwCmpExecute(inCmd3s1);
  CrFwInCmdTerminate(inCmd3s1);
  inCmd3s1 = CrPsHkTestCaseMake3s1(preDefSID3, 2, parId3);
  CrFwCmpExecute(inCmd3s1);
  CrFwInCmdTerminate(inCmd3s1);
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID1);
  setDpHkIsEnabledItem(rdlPos, 1);

  /* Create a (3,3) command and execute */
  sid[0] = preDefSID2+1;        /* Not loaded SID */
  sid[1] = HK_MAX_SID+1;        /* Illegal SID */
  sid[2] = preDefSID1;          /* Enabled SID */
  inCmd3s3 = CrPsHkTestCaseMake3s3(sid, 3);
  nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
  CrFwCmpExecute(inCmd3s3);
  CrFwInCmdTerminate(inCmd3s3);

  /* Check that the InCommand is in PROGRESS state and one (1,6) report was generated */
  if (!CrFwInCmdIsInProgress(inCmd3s3))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,nOfOutCmp,6,VER_ILL_SID,preDefSID2+1) != 1)
      return 0;

  /* Execute the command again and check that it is in PROGRESS state and one (1,6) report was generated */
  CrFwCmpExecute(inCmd3s3);
  CrFwInCmdTerminate(inCmd3s3);
  if (!CrFwInCmdIsInProgress(inCmd3s3))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 2)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,nOfOutCmp+1,6,VER_ILL_SID,HK_MAX_SID+1) != 1)
      return 0;

  /* Execute the command again and verify that it terminates */
  CrFwCmpExecute(inCmd3s3);
  CrFwInCmdTerminate(inCmd3s3);
  if (!CrFwInCmdIsInAborted(inCmd3s3))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 4)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,nOfOutCmp+2,6,VER_ENB_SID,preDefSID1) != 1)
      return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,nOfOutCmp+3,8,VER_MI_S3_FD,3) != 1)
      return 0;

  /* -------------------------------------------------------------------------- */
  /* Create a (3,3) command with one loaded, legal and disabled SID */
  sid[0] = preDefSID2;
  inCmd3s3 = CrPsHkTestCaseMake3s3(sid, 1);
  CrFwCmpExecute(inCmd3s3);
  CrFwInCmdTerminate(inCmd3s3);
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 4)
      return 0;

  /* Check that the second SID has been deleted */
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID2);
  if (rdlPos != -1)
      return 0;
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID1);
  if (rdlPos == -1)
      return 0;
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID3);
  if (rdlPos == -1)
      return 0;

  /* -------------------------------------------------------------------------- */
  /* Create a (3,4) command with one loaded, legal and disabled SID */
  sid[0] = preDefSID3;
  inCmd3s4 = CrPsHkTestCaseMake3s3(sid, 1);
  pckt = CrFwInCmdGetPckt(inCmd3s4);
  CrFwPcktSetServSubType(pckt, HKDELDIAGCMD_STYPE);
  CrFwCmpExecute(inCmd3s4);
  CrFwInCmdTerminate(inCmd3s4);

  /* Check that the first and third SID have been deleted */
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID2);
  if (rdlPos != -1)
      return 0;
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID1);
  if (rdlPos == -1)
      return 0;
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID3);
  if (rdlPos != -1)
      return 0;

  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd3s3);

  /* Reset the framework components */
  CrPsTestUtilitiesResetFw();

  /* Check that no packets are allocated */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsHkTestCase7() {
  FwSmDesc_t inCmd3s31, inCmd3s1, inCmd3s32;
  FwSmDesc_t outManager = CrFwOutManagerMake(0);
  CrPsParId_t parId1[HK_NOFITEMS_SID_N_OF_EVT] = HK_DEF_SID_N_OF_EVT;    /* Pre-defined HK report */
  CrPsSID_t sid[3];
  CrPsCycleCnt_t period[3];
  CrPsSID_t preDefSID1 = 1;
  int nOfOutCmp, rdlPos;
  CrFwCounterU1_t nOfGenOutCmp;
  CrFwPckt_t pckt;

  /* Reset the framework components and clear the RDL*/
  CrPsTestUtilitiesResetFw();
  CrPsHkConfigInit();

  /* Load one HK report and enable it */
  inCmd3s1 = CrPsHkTestCaseMake3s1(preDefSID1, HK_NOFITEMS_SID_N_OF_EVT, parId1);
  CrFwCmpExecute(inCmd3s1);
  CrFwInCmdTerminate(inCmd3s1);
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID1);
  setDpHkIsEnabledItem(rdlPos, 1);

  /* Execute the OutManager 3 times and verify that the (3,25) report is generated 3 times */
  nOfGenOutCmp = CrPsOutStreamStubGetHandoverCnt();
  CrFwCmpExecute(outManager);
  CrFwCmpExecute(outManager);
  CrFwCmpExecute(outManager);
  if (CrPsOutStreamStubGetHandoverCnt() != nOfGenOutCmp+3)
      return 0;

  /* Create a (3,31) command */
  sid[0] = preDefSID1+1;        /* Not loaded SID */
  sid[1] = HK_MAX_SID+1;        /* Illegal SID */
  sid[2] = preDefSID1;          /* Loaded SID */
  period[0] = 5;
  period[1] = 4;
  period[2] = 3;
  inCmd3s31 = CrPsHkTestCaseMake3s31(sid, period, 3);
  nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
  CrFwCmpExecute(inCmd3s31);
  CrFwInCmdTerminate(inCmd3s31);

  /* Check that the InCommand is in PROGRESS state and one (1,6) report was generated */
  if (!CrFwInCmdIsInProgress(inCmd3s31))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,nOfOutCmp,6,VER_ILL_SID,preDefSID1+1) != 1)
      return 0;

  /* Execute the command again and check that it is in PROGRESS state and one (1,6) report was generated */
  CrFwCmpExecute(inCmd3s31);
  CrFwInCmdTerminate(inCmd3s31);
  if (!CrFwInCmdIsInProgress(inCmd3s31))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 2)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,nOfOutCmp+1,6,VER_ILL_SID,HK_MAX_SID+1) != 1)
      return 0;

  /* Execute the command again and verify that it terminates */
  CrFwCmpExecute(inCmd3s31);
  CrFwInCmdTerminate(inCmd3s31);
  if (!CrFwInCmdIsInAborted(inCmd3s31))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 3)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,nOfOutCmp+2,8,VER_MI_S3_FD,2) != 1)
      return 0;

  /* Verify that the period of the (3,25) has been modified */
  if (getDpHkPeriodItem(rdlPos) != period[2])
      return 0;

  /* Execute again the OutManager 3 times and verify that the (3,25) is only generated once */
  nOfGenOutCmp = CrPsOutStreamStubGetHandoverCnt();
  CrFwCmpExecute(outManager);
  CrFwCmpExecute(outManager);
  CrFwCmpExecute(outManager);
  if (CrPsOutStreamStubGetHandoverCnt() != nOfGenOutCmp+4)  /* 3 service 1 reports + 1 HK report */
      return 0;

  /* Create a (3,32) command */
  sid[0] = preDefSID1;    /* Loaded SID */
  period[0] = 10;
  inCmd3s32 = CrPsHkTestCaseMake3s31(sid, period, 1);
  pckt = CrFwInCmdGetPckt(inCmd3s32);
  CrFwPcktSetServSubType(pckt, HKMODPERDIAGCMD_STYPE);
  CrFwCmpExecute(inCmd3s32);
  CrFwInCmdTerminate(inCmd3s32);

  /* Check that the InCommand has terminated execution and the period has been modified as expected */
  if (!CrFwInCmdIsInTerminated(inCmd3s32))
    return 0;
  if (getDpHkPeriodItem(rdlPos) != period[0])
      return 0;

  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd3s31);
  CrFwInFactoryReleaseInCmd(inCmd3s32);

  /* Reset the framework components */
  CrPsTestUtilitiesResetFw();

  /* Check that no packets are allocated */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsHkTestCase8() {
  FwSmDesc_t inCmd3s27, inCmd3s1;
  FwSmDesc_t outManager = CrFwOutManagerMake(0);
  CrPsParId_t parId1[HK_NOFITEMS_SID_N_OF_EVT] = HK_DEF_SID_N_OF_EVT;    /* Pre-defined HK report */
  CrPsSID_t sid[3];
  CrPsSID_t preDefSID1 = 2;
  int nOfOutCmp, rdlPos;
  CrFwCounterU1_t nOfGenOutCmp;
  CrFwPckt_t pckt;

  /* Reset the framework components and clear the RDL*/
  CrPsTestUtilitiesResetFw();
  CrPsHkConfigInit();

  /* Load one HK report and set its period to zero */
  inCmd3s1 = CrPsHkTestCaseMake3s1(preDefSID1, HK_NOFITEMS_SID_N_OF_EVT, parId1);
  pckt = CrFwInCmdGetPckt(inCmd3s1);
  setHkCreHkCmdCollectionInterval(pckt, 0);
  CrFwCmpExecute(inCmd3s1);
  CrFwInCmdTerminate(inCmd3s1);
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID1);

  /* Execute the OutManager 3 times and verify that the (3,25) report is not generated */
  nOfGenOutCmp = CrPsOutStreamStubGetHandoverCnt();
  CrFwCmpExecute(outManager);
  CrFwCmpExecute(outManager);
  CrFwCmpExecute(outManager);
  if (CrPsOutStreamStubGetHandoverCnt() != nOfGenOutCmp)
      return 0;
  if (getDpHkCycleCntItem(rdlPos) != 3)
      return 0;

  /* Create a (3,27) command */
  sid[0] = preDefSID1+1;        /* Not loaded SID */
  sid[1] = HK_MAX_SID+1;        /* Illegal SID */
  sid[2] = preDefSID1;          /* Loaded SID */
  inCmd3s27 = CrPsHkTestCaseMake3s27(sid, 3);
  nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
  CrFwCmpExecute(inCmd3s27);
  CrFwInCmdTerminate(inCmd3s27);

  /* Check that the InCommand is in PROGRESS state and one (1,6) report was generated */
  if (!CrFwInCmdIsInProgress(inCmd3s27))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,nOfOutCmp,6,VER_ILL_SID,preDefSID1+1) != 1)
      return 0;

  /* Execute the command again and check that it is in PROGRESS state and one (1,6) report was generated */
  CrFwCmpExecute(inCmd3s27);
  CrFwInCmdTerminate(inCmd3s27);
  if (!CrFwInCmdIsInProgress(inCmd3s27))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 2)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,nOfOutCmp+1,6,VER_ILL_SID,HK_MAX_SID+1) != 1)
      return 0;

  /* Execute the command again and verify that it terminates */
  CrFwCmpExecute(inCmd3s27);
  CrFwInCmdTerminate(inCmd3s27);
  if (!CrFwInCmdIsInAborted(inCmd3s27))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 3)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,nOfOutCmp+2,8,VER_MI_S3_FD,2) != 1)
      return 0;

  /* Verify that the cycle counter of the (3,25) has been modified and that the report is enabled */
  if (getDpHkCycleCntItem(rdlPos) != getDpHkPeriodItem(rdlPos))
      return 0;
  if (getDpHkIsEnabledItem(rdlPos) != 1)
      return 0;

  /* Execute again the OutManager 3 times and verify that the (3,25) is only generated once */
  nOfGenOutCmp = CrPsOutStreamStubGetHandoverCnt();
  CrFwCmpExecute(outManager);
  CrFwCmpExecute(outManager);
  CrFwCmpExecute(outManager);
  if (CrPsOutStreamStubGetHandoverCnt() != nOfGenOutCmp+4)      /* 3 service 1 reports + 1 HK report */
      return 0;

  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd3s27);

  /* Reset the framework components */
  CrPsTestUtilitiesResetFw();

  /* Check that no packets are allocated */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsHkTestCase9() {
  FwSmDesc_t inCmd3s9, inCmd3s1, rep3s10;
  FwSmDesc_t outManager = CrFwOutManagerMake(0);
  CrPsParId_t parId1[HK_NOFITEMS_SID_N_OF_EVT] = HK_DEF_SID_N_OF_EVT;    /* Pre-defined HK report */
  CrPsParId_t parId2[HK_NOFITEMS_SID_HK_CNT] = HK_DEF_SID_HK_CNT;    /* Pre-defined HK report */
  CrPsSID_t sid[3];
  CrPsSID_t preDefSID1 = 2;
  CrPsSID_t preDefSID2 = 5;
  CrFwPckt_t pckt;
  CrFwOutFactoryPoolIndex_t nOfOutCmp;

  /* Reset the framework components and clear the RDL*/
  CrPsTestUtilitiesResetFw();
  CrPsHkConfigInit();

  /* Load two HK reports  */
  inCmd3s1 = CrPsHkTestCaseMake3s1(preDefSID1, HK_NOFITEMS_SID_N_OF_EVT, parId1);
  CrFwCmpExecute(inCmd3s1);
  CrFwInCmdTerminate(inCmd3s1);
  inCmd3s1 = CrPsHkTestCaseMake3s1(preDefSID2, HK_NOFITEMS_SID_HK_CNT, parId2);
  CrFwCmpExecute(inCmd3s1);
  CrFwInCmdTerminate(inCmd3s1);

  /* Create a (3,9) command */
  sid[0] = preDefSID1;          /* Loaded SID */
  sid[1] = HK_MAX_SID+1;        /* Illegal SID */
  sid[2] = preDefSID2;          /* Loaded SID */
  inCmd3s9 = CrPsHkTestCaseMake3s9(sid, 3);
  nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
  CrFwCmpExecute(inCmd3s9);
  CrFwInCmdTerminate(inCmd3s9);

  /* Check that the InCommand is in PROGRESS state and one (3,10) report was generated */
  if (!CrFwInCmdIsInProgress(inCmd3s9))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmp(outManager,nOfOutCmp,HK_TYPE,HKREPSTRUCTHKREP_STYPE,0) != 1)
      return 0;

  /* Execute the command again and check that it is in PROGRESS state and one (1,6) report was generated */
  CrFwCmpExecute(inCmd3s9);
  CrFwInCmdTerminate(inCmd3s9);
  if (!CrFwInCmdIsInProgress(inCmd3s9))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 2)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,nOfOutCmp+1,6,VER_ILL_SID,HK_MAX_SID+1) != 1)
      return 0;

  /* Execute the command again and verify that it terminates and one more (3,10) and (1,8) report was generated */
  CrFwCmpExecute(inCmd3s9);
  CrFwInCmdTerminate(inCmd3s9);
  if (!CrFwInCmdIsInAborted(inCmd3s9))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 4)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmp(outManager,nOfOutCmp+2,HK_TYPE,HKREPSTRUCTHKREP_STYPE,0) != 1)
      return 0;

  /* Verify the content of the first (3,10) report */
  rep3s10 = CrPsTestUtilitiesGetItemFromOutManager(outManager, nOfOutCmp);
  pckt = CrFwOutCmpGetPckt(rep3s10);
  if (getHkRepStructHkRepSID(pckt) != preDefSID1)
    return 0;
  if (getHkRepStructHkRepPerGenActionStatus(pckt) != 0)
    return 0;
  if (getHkRepStructHkRepCollectionInterval(pckt) != 1)
    return 0;
  if (getHkRepStructHkRepN1(pckt) != HK_NOFITEMS_SID_N_OF_EVT)
    return 0;
  if (getHkRepStructHkRepN1ParamId(pckt, 0) != parId1[0])
    return 0;
  if (getHkRepStructHkRepN1ParamId(pckt, 1) != parId1[1])
    return 0;

  /* Verify the content of the second (3,10) report */
  rep3s10 = CrPsTestUtilitiesGetItemFromOutManager(outManager, nOfOutCmp+2);
  pckt = CrFwOutCmpGetPckt(rep3s10);
  if (getHkRepStructHkRepSID(pckt) != preDefSID2)
    return 0;
  if (getHkRepStructHkRepPerGenActionStatus(pckt) != 0)
    return 0;
  if (getHkRepStructHkRepCollectionInterval(pckt) != 1)
    return 0;
  if (getHkRepStructHkRepN1(pckt) != HK_NOFITEMS_SID_HK_CNT)
    return 0;
  if (getHkRepStructHkRepN1ParamId(pckt, 0) != parId2[0])
    return 0;

  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd3s9);

  /* Reset the framework components */
  CrPsTestUtilitiesResetFw();

  /* Check that no packets are allocated */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsHkTestCase10() {
  FwSmDesc_t inCmd;
  FwSmDesc_t outManager = CrFwOutManagerMake(0);
  CrPsSID_t preDefSID = 1;
  CrPsParId_t parId[HK_NOFITEMS_SID_N_OF_EVT] = HK_DEF_SID_N_OF_EVT;    /* Pre-defined HK report */
  CrFwDestSrc_t src3s1 = EVT_DEST;
  CrFwPckt_t pckt;
  short int rdlPos;

  /* Reset the framework components */
  CrPsTestUtilitiesResetFw();

  /* Create a (3,2) command and set its source */
  inCmd = CrPsHkTestCaseMake3s1(preDefSID, HK_NOFITEMS_SID_N_OF_EVT, parId);
  pckt = CrFwInCmdGetPckt(inCmd);
  CrFwPcktSetServSubType(pckt, HKCREDIAGCMD_STYPE);
  CrFwPcktSetSrc(pckt, src3s1);

  /* Execute and terminate the InCommand  (this simulates the action of an InManager) */
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);

  /*check that the InCommand is in TERMINATED state*/
  if (!CrFwInCmdIsInTerminated(inCmd))
    return 0;

  /* Check that there is a pending OutComponent of type (3,26) */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmp(outManager,0,HK_TYPE,HKDIAGREP_STYPE,preDefSID) != 1)
      return 0;

  /* Execute the OutManager and verify that no HK report is generated */
  CrFwCmpExecute(outManager);
  if (CrPsOutStreamStubGetHandoverCnt()>0)
      return 0;

  /* Enable the pending HK report in the RDL, execute it again and check that the report is generated */
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID);
  setDpHkIsEnabledItem(rdlPos, 1);
  CrFwCmpExecute(outManager);
  if (CrPsOutStreamStubGetHandoverCnt() != 1)
      return 0;
  pckt = CrPsOutStreamStubGetPckt(0);
  if (CrFwPcktGetDest(pckt) != src3s1)
      return 0;

  /* Execute OutManager twice and verify that the report is generated twice */
  CrFwCmpExecute(outManager);
  CrFwCmpExecute(outManager);
  if (CrPsOutStreamStubGetHandoverCnt() != 3)
      return 0;

  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Reset the framework components */
  CrPsTestUtilitiesResetFw();

  /* Check that no packets are allocated */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsHkTestCase11() {
  FwSmDesc_t inCmd3s1, inCmd3s28;
  FwSmDesc_t outManager = CrFwOutManagerMake(0);
  CrPsParId_t parId1[HK_NOFITEMS_SID_N_OF_EVT] = HK_DEF_SID_N_OF_EVT;    /* Pre-defined HK report */
  CrPsSID_t sid[3];
  CrPsSID_t preDefSID1 = 2;
  int nOfOutCmp, rdlPos;
  CrFwCounterU1_t nOfGenOutCmp;
  CrFwPckt_t pckt;

  /* Reset the framework components and clear the RDL*/
  CrPsTestUtilitiesResetFw();
  CrPsHkConfigInit();

  /* Load one diagnostic report and set its period to zero */
  inCmd3s1 = CrPsHkTestCaseMake3s1(preDefSID1, HK_NOFITEMS_SID_N_OF_EVT, parId1);
  pckt = CrFwInCmdGetPckt(inCmd3s1);
  CrFwPcktSetServSubType(pckt, HKDIAGREP_STYPE);
  setHkCreHkCmdCollectionInterval(pckt, 0);
  CrFwCmpExecute(inCmd3s1);
  CrFwInCmdTerminate(inCmd3s1);
  rdlPos = CrPsHkConfigGetRdlSlot(preDefSID1);

  /* Execute the OutManager 3 times and verify that the (3,26) report is not generated */
  nOfGenOutCmp = CrPsOutStreamStubGetHandoverCnt();
  CrFwCmpExecute(outManager);
  CrFwCmpExecute(outManager);
  CrFwCmpExecute(outManager);
  if (CrPsOutStreamStubGetHandoverCnt() != nOfGenOutCmp)
      return 0;
  if (getDpHkCycleCntItem(rdlPos) != 3)
      return 0;

  /* Create a (3,28) command */
  sid[0] = preDefSID1;      /* Loaded SID */
  inCmd3s28 = CrPsHkTestCaseMake3s27(sid, 1);
  pckt = CrFwInCmdGetPckt(inCmd3s28);
  CrFwPcktSetServSubType(pckt, HKONESHOTDIAGCMD_STYPE);
  nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
  CrFwCmpExecute(inCmd3s28);
  CrFwInCmdTerminate(inCmd3s28);

  /* Check that the InCommand has terminated */
  if (!CrFwInCmdIsInTerminated(inCmd3s28))
    return 0;

  /* Verify that the cycle counter of the (3,26) has been modified and that the report is enabled */
  if (getDpHkCycleCntItem(rdlPos) != getDpHkPeriodItem(rdlPos))
      return 0;
  if (getDpHkIsEnabledItem(rdlPos) != 1)
      return 0;

  /* Execute again the OutManager 3 times and verify that the (3,26) is only generated once */
  nOfGenOutCmp = CrPsOutStreamStubGetHandoverCnt();
  CrFwCmpExecute(outManager);
  CrFwCmpExecute(outManager);
  CrFwCmpExecute(outManager);
  if (CrPsOutStreamStubGetHandoverCnt() != nOfGenOutCmp+1)
      return 0;

  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd3s28);

  /* Reset the framework components */
  CrPsTestUtilitiesResetFw();

  /* Check that no packets are allocated */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsHkTestCase12() {
  FwSmDesc_t inCmd3s11, inCmd3s1, rep3s12;
  FwSmDesc_t outManager = CrFwOutManagerMake(0);
  CrPsParId_t parId1[HK_NOFITEMS_SID_N_OF_EVT] = HK_DEF_SID_N_OF_EVT;    /* Pre-defined HK report */
  CrPsSID_t sid[1];
  CrPsSID_t preDefSID1 = 2;
  CrFwPckt_t pckt;
  CrFwOutFactoryPoolIndex_t nOfOutCmp;

  /* Reset the framework components and clear the RDL*/
  CrPsTestUtilitiesResetFw();
  CrPsHkConfigInit();

  /* Load one HK report */
  inCmd3s1 = CrPsHkTestCaseMake3s1(preDefSID1, HK_NOFITEMS_SID_N_OF_EVT, parId1);
  CrFwCmpExecute(inCmd3s1);
  CrFwInCmdTerminate(inCmd3s1);

  /* Create a (3,11) command */
  sid[0] = preDefSID1;          /* Loaded SID */
  inCmd3s11 = CrPsHkTestCaseMake3s9(sid, 1);
  pckt = CrFwInCmdGetPckt(inCmd3s11);
  CrFwPcktSetServSubType(pckt, HKREPSTRUCTDIAGCMD_STYPE);
  nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
  CrFwCmpExecute(inCmd3s11);
  CrFwInCmdTerminate(inCmd3s11);

  /* Check that the InCommand is in terminated state and one (3,12) report was generated */
  if (!CrFwInCmdIsInTerminated(inCmd3s11))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmp(outManager,nOfOutCmp,HK_TYPE,HKREPSTRUCTDIAGREP_STYPE,0) != 1)
      return 0;

  /* Verify the content of the (3,12) report */
  rep3s12 = CrPsTestUtilitiesGetItemFromOutManager(outManager, nOfOutCmp);
  pckt = CrFwOutCmpGetPckt(rep3s12);
  if (getHkRepStructHkRepSID(pckt) != preDefSID1)
    return 0;
  if (getHkRepStructHkRepPerGenActionStatus(pckt) != 0)
    return 0;
  if (getHkRepStructHkRepCollectionInterval(pckt) != 1)
    return 0;
  if (getHkRepStructHkRepN1(pckt) != HK_NOFITEMS_SID_N_OF_EVT)
    return 0;
  if (getHkRepStructHkRepN1ParamId(pckt, 0) != parId1[0])
    return 0;
  if (getHkRepStructHkRepN1ParamId(pckt, 1) != parId1[1])
    return 0;

  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd3s11);

  /* Reset the framework components */
  CrPsTestUtilitiesResetFw();

  /* Check that no packets are allocated */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
FwSmDesc_t CrPsHkTestCaseMake3s1(CrPsSID_t sid, CrPsNPar_t N1, CrPsParId_t* parId) {
  CrFwPckt_t pckt;
  int i;

  pckt = CrFwPcktMake(CR_FW_MAX_PCKT_LENGTH);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,HK_TYPE);
  CrFwPcktSetServSubType(pckt,HKCREHKCMD_STYPE);
  CrFwPcktSetSrc(pckt,EVT_DEST);
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

/*-----------------------------------------------------------------------------*/
FwSmDesc_t CrPsHkTestCaseMake3s3(CrPsSID_t* sid, CrPsNSID_t N1) {
  CrFwPckt_t pckt;
  CrPsNSID_t i;

  pckt = CrFwPcktMake(CR_FW_MAX_PCKT_LENGTH);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,HK_TYPE);
  CrFwPcktSetServSubType(pckt,HKDELHKCMD_STYPE);
  CrFwPcktSetSrc(pckt,EVT_DEST);
  CrFwPcktSetDest(pckt,0);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);
  CrFwPcktSetSeqCnt(pckt,1);
  setHkEnbHkCmdN(pckt, N1);
  for (i=0; i<N1; i++)
      setHkEnbHkCmdSID(pckt, i, sid[i]);

  return CrFwInFactoryMakeInCmd(pckt);
}


/*-----------------------------------------------------------------------------*/
FwSmDesc_t CrPsHkTestCaseMake3s5(CrPsSID_t* sid, CrPsNSID_t N1) {
  CrFwPckt_t pckt;
  CrPsNSID_t i;

  pckt = CrFwPcktMake(CR_FW_MAX_PCKT_LENGTH);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,HK_TYPE);
  CrFwPcktSetServSubType(pckt,HKENBHKCMD_STYPE);
  CrFwPcktSetSrc(pckt,EVT_DEST);
  CrFwPcktSetDest(pckt,0);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);
  CrFwPcktSetSeqCnt(pckt,1);
  setHkEnbHkCmdN(pckt, N1);
  for (i=0; i<N1; i++)
      setHkEnbHkCmdSID(pckt, i, sid[i]);

  return CrFwInFactoryMakeInCmd(pckt);
}

/*-----------------------------------------------------------------------------*/
FwSmDesc_t CrPsHkTestCaseMake3s6(CrPsSID_t* sid, CrPsNSID_t N1) {
  CrFwPckt_t pckt;
  CrPsNSID_t i;

  pckt = CrFwPcktMake(CR_FW_MAX_PCKT_LENGTH);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,HK_TYPE);
  CrFwPcktSetServSubType(pckt,HKDISHKCMD_STYPE);
  CrFwPcktSetSrc(pckt,EVT_DEST);
  CrFwPcktSetDest(pckt,0);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);
  CrFwPcktSetSeqCnt(pckt,1);
  setHkEnbHkCmdN(pckt, N1);
  for (i=0; i<N1; i++)
      setHkEnbHkCmdSID(pckt, i, sid[i]);

  return CrFwInFactoryMakeInCmd(pckt);
}

/*-----------------------------------------------------------------------------*/
FwSmDesc_t CrPsHkTestCaseMake3s9(CrPsSID_t* sid, CrPsNSID_t N1) {
  CrFwPckt_t pckt;
  CrPsNSID_t i;

  pckt = CrFwPcktMake(CR_FW_MAX_PCKT_LENGTH);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,HK_TYPE);
  CrFwPcktSetServSubType(pckt,HKREPSTRUCTHKCMD_STYPE);
  CrFwPcktSetSrc(pckt,EVT_DEST);
  CrFwPcktSetDest(pckt,0);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);
  CrFwPcktSetSeqCnt(pckt,1);
  setHkRepStructHkCmdN(pckt, N1);
  for (i=0; i<N1; i++)
      setHkRepStructHkCmdSID(pckt, i, sid[i]);

  return CrFwInFactoryMakeInCmd(pckt);
}

/*-----------------------------------------------------------------------------*/
FwSmDesc_t CrPsHkTestCaseMake3s27(CrPsSID_t* sid, CrPsNSID_t N1) {
  CrFwPckt_t pckt;
  CrPsNSID_t i;

  pckt = CrFwPcktMake(CR_FW_MAX_PCKT_LENGTH);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,HK_TYPE);
  CrFwPcktSetServSubType(pckt,HKONESHOTHKCMD_STYPE);
  CrFwPcktSetSrc(pckt,EVT_DEST);
  CrFwPcktSetDest(pckt,0);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);
  CrFwPcktSetSeqCnt(pckt,1);
  setHkOneShotHkCmdN(pckt, N1);
  for (i=0; i<N1; i++)
      setHkOneShotHkCmdSID(pckt, i, sid[i]);

  return CrFwInFactoryMakeInCmd(pckt);
}

/*-----------------------------------------------------------------------------*/
FwSmDesc_t CrPsHkTestCaseMake3s31(CrPsSID_t* sid, CrPsCycleCnt_t* period, CrPsNSID_t N1) {
  CrFwPckt_t pckt;
  CrPsNSID_t i;

  pckt = CrFwPcktMake(CR_FW_MAX_PCKT_LENGTH);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,HK_TYPE);
  CrFwPcktSetServSubType(pckt,HKMODPERHKCMD_STYPE);
  CrFwPcktSetSrc(pckt,EVT_DEST);
  CrFwPcktSetDest(pckt,0);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);
  CrFwPcktSetSeqCnt(pckt,1);
  setHkModPerHkCmdN(pckt, N1);
  for (i=0; i<N1; i++) {
      setHkModPerHkCmdSID(pckt, i, sid[i]);
      setHkModPerHkCmdCollectionInterval(pckt, i, period[i]);
  }

  return CrFwInFactoryMakeInCmd(pckt);
}
