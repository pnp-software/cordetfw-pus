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

/* Include system files */
#include <stdlib.h>
#include <unistd.h>

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsHkTestCase1() {
  int rdlPos,i;
  FwSmDesc_t rep;
  CrPsParId_t* parId1[HK_NOFITEMS_SID_HK_CNT] = HK_DEF_SID_HK_CNT;
  CrPsParId_t* parId2[HK_NOFITEMS_SID_N_OF_EVT] = HK_DEF_SID_N_OF_EVT;

  CrFwSetAppErrCode(crNoAppErr);

  /* Initialize the HK Service */
  CrPsHkConfigInit();

  /* Get a free slot and create the RDL entry for the first pre-defined HK packet */
  rdlPos = CrPsHkConfigGetFreeRdlSlot();
  if (rdlPos == -1)
      return 0;

  rep = CrFwOutFactoryMakeOutCmp(HK_TYPE, HKREP_STYPE, 0, LEN_HK_REP_SID_HK_CNT);
  if (rep == NULL)
      return 0;
  CrPsHkConfigHkRep(rep, rdlPos, SID_HK_CNT, HK_NOFITEMS_SID_HK_CNT, 0, 1, parId1);
  if (CrPsHkConfigGetRdlSlot(SID_HK_CNT) != rdlPos)
      return 0;

  /* Get a free slot and create the RDL entry for the second pre-defined HK packet */
  rdlPos = CrPsHkConfigGetFreeRdlSlot();
  if (rdlPos == -1)
      return 0;

  rep = CrFwOutFactoryMakeOutCmp(HK_TYPE, HKREP_STYPE, 0, LEN_HK_REP_SID_N_OF_EVT);
  if (rep == NULL)
      return 0;
  CrPsHkConfigHkRep(rep, rdlPos, SID_N_OF_EVT, HK_NOFITEMS_SID_N_OF_EVT, 0, 2, parId1);
  if (CrPsHkConfigGetRdlSlot(SID_N_OF_EVT) != rdlPos)
      return 0;

  /* Attempt to set enable status of a non-existent SID */
  if (CrPsHkConfigSetSidEnableStatus(0, 1) != -1)
      return 0;

  /* Set the enable status of an existing SID */
  if (CrPsHkConfigSetSidEnableStatus(SID_N_OF_EVT, 1) != rdlPos)
      return 0;

  /* Fill up the RDL and then attempt to get a free slot */
  for (i=0; i<HK_N_REP_DEF-2; i++) {
      rdlPos = CrPsHkConfigGetFreeRdlSlot();
      if (rdlPos == -1)
          return 0;
      CrPsHkConfigHkRep(rep, rdlPos, SID_N_OF_EVT+100+i, HK_NOFITEMS_SID_N_OF_EVT, 0, 2, parId1);
  }
  if (CrPsHkConfigGetFreeRdlSlot() != -1)
      return 0;

  /* Attempt to clear a non-existent SID */
  if (CrPsHkConfigClearSid(0) != -1)
      return 0;

  /* Clear the SIDs inserted to fill up the RDL (but leave the two pre-defined SIDs */
  for (i=0; i<HK_N_REP_DEF-2; i++) {
      if (CrPsHkConfigClearSid(SID_N_OF_EVT+100+i) == -1)
          return 0;
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
  FwSmDesc_t outRegistry, outFactory, outLoader, outManager;
  int rdlPos, i;
  CrPsParId_t parId[1] = {1};

  CrFwSetAppErrCode(crNoAppErr);

  /* Initialize and reset the framework components */
  outRegistry = CrFwOutRegistryMake();
  CrFwCmpInit(outRegistry);
  CrFwCmpReset(outRegistry);
  outFactory = CrFwOutFactoryMake();
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  outManager = CrFwOutManagerMake(0);
  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  outLoader = CrFwOutLoaderMake();
  CrFwCmpInit(outLoader);
  CrFwCmpReset(outLoader);

  /* Create a (3,1) command */
  pckt = CrFwPcktMake(CR_FW_MAX_PCKT_LENGTH);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,HK_TYPE);
  CrFwPcktSetServSubType(pckt,HKREP_STYPE);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);
  CrFwPcktSetSeqCnt(pckt,2);
  setHkCreHkCmdSID(pckt,SID_N_OF_EVT+100);
  setHkCreHkCmdCollectionInterval(pckt, 0);
  setHkCreHkCmdN1(pckt, 1);
  setHkCreHkCmdN1ParamId(pckt, 0, 1);

  /*Creating an InCommand out of the 5,6 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != HK_TYPE)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != HKCREHKCMD_STYPE)
    return 0;

  /* Fill-up the RDL (two pre-defined SIDs are already loaded -- test case 1) */
  rep = CrFwOutFactoryMakeOutCmp(HK_TYPE, HKREP_STYPE, 0, CR_FW_MAX_PCKT_LENGTH);
  for (i=0; i<HK_N_REP_DEF-2; i++) {
      rdlPos = CrPsHkConfigGetFreeRdlSlot();
      if (rdlPos == -1)
          return 0;
      CrPsHkConfigHkRep(rep, rdlPos, 120+i, 1, 0, 2, parId);
  }

  /* Execute and terminate  the InCommand  (this simulates the action of an InManager) */
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);

  /*check that the InCommand is in TERMINATED state*/
  if (!CrFwInCmdIsInTerminated(inCmd))
    return 0;

  /* Check that there is one pending OutComponent of type (1,4) */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,0,4,VER_FULL_RDL,0) != 1)
      return 0;

  /* Remove RDL entries added for this test */
  rep = CrFwOutFactoryMakeOutCmp(HK_TYPE, HKREP_STYPE, 0, CR_FW_MAX_PCKT_LENGTH);
  for (i=0; i<HK_N_REP_DEF-2; i++) {
      rdlPos = CrPsHkConfigClearSid(120+i);
      if (rdlPos == -1)
          return 0;
  }
  CrFwOutFactoryReleaseOutCmp(rep);




  /* Reset all components used in the test case */
  CrFwCmpReset(outLoader);
  CrFwCmpReset(outManager);
  CrFwCmpReset(outFactory);
  CrFwCmpReset(outRegistry);

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsEvtTestCase3() {
  CrFwPckt_t pckt;
  FwSmDesc_t rep;
  FwSmDesc_t outRegistry, outFactory, outLoader, outManager;

  CrFwSetAppErrCode(crNoAppErr);

  /* Initialize and reset the framework components */
  outRegistry = CrFwOutRegistryMake();
  CrFwCmpInit(outRegistry);
  CrFwCmpReset(outRegistry);
  outFactory = CrFwOutFactoryMake();
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  outManager = CrFwOutManagerMake(0);
  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  outLoader = CrFwOutLoaderMake();
  CrFwCmpInit(outLoader);
  CrFwCmpReset(outLoader);

  /* Initialize all event related data pool entries */
  setDpEvtLastEvtEid_2(0);
  setDpEvtLastEvtTime_2(0);
  setDpEvtNOfDetectedEvts_2(0);

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  /* Generate a dummy event of level 2 */
  CrPsEvtGenPreDefEvtNoPar(EVT_DUMMY_2);

  /* Check that there is one pending OutComponent of type (5,2) */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmp(outManager,0,5,2,EVT_DUMMY_2) != 1)
      return 0;
  rep = CrPsTestUtilitiesGetItemFromOutManager(outManager,0);
  pckt = CrFwOutCmpGetPckt(rep);

  /* Verify the discriminant of the event report */
  if (CrFwOutCmpGetDiscriminant(rep) != EVT_DUMMY_2)
      return 0;
  if (getEvtRep1EventId(pckt) != EVT_DUMMY_2)
      return 0;

  /* Execute the OutManager so that the event will be executed, too */
  CrFwCmpExecute(outManager);

  /* Check observables related to event */
  if (getDpEvtLastEvtEid_2() != EVT_DUMMY_2)
      return 0;
  if (abs(getDpEvtLastEvtTime_2()-CrFwGetCurrentTime()) < 0.001)
      return 0;
  if (getDpEvtNOfDetectedEvts_2() != 1)
      return 0;

  /* Reset all components used in the test case */
  CrFwCmpReset(outLoader);
  CrFwCmpReset(outManager);
  CrFwCmpReset(outFactory);
  CrFwCmpReset(outRegistry);

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsEvtTestCase4() {
  CrFwPckt_t pckt;
  FwSmDesc_t rep;
  FwSmDesc_t outRegistry, outFactory, outLoader, outManager;

  CrFwSetAppErrCode(crNoAppErr);

  /* Initialize and reset the framework components */
  outRegistry = CrFwOutRegistryMake();
  CrFwCmpInit(outRegistry);
  CrFwCmpReset(outRegistry);
  outFactory = CrFwOutFactoryMake();
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  outManager = CrFwOutManagerMake(0);
  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  outLoader = CrFwOutLoaderMake();
  CrFwCmpInit(outLoader);
  CrFwCmpReset(outLoader);

  /* Initialize all event related data pool entries */
  setDpEvtLastEvtEid_3(0);
  setDpEvtLastEvtTime_3(0);
  setDpEvtNOfDetectedEvts_3(0);

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  /* Generate a dummy event of level 3 */
  CrPsEvtGenPreDefEvtDummyPar(EVT_DUMMY_3, 127);

  /* Check that there is one pending OutComponent of type (5,3) */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmp(outManager,0,5,3,EVT_DUMMY_3) != 1)
      return 0;

  /* Check the parameter of the event */
  rep = CrPsTestUtilitiesGetItemFromOutManager(outManager,0);
  pckt = CrFwOutCmpGetPckt(rep);
  if (getEvtRep1_EVT_DUMMY_1Par(pckt) != 127)
      return 0;

  /* Verify the discriminant of the event report */
  if (CrFwOutCmpGetDiscriminant(rep) != EVT_DUMMY_3)
      return 0;
  if (getEvtRep1EventId(pckt) != EVT_DUMMY_3)
      return 0;

  /* Execute the OutManager so that the event will be executed, too */
  CrFwCmpExecute(outManager);

  /* Check observables related to level 1 events */
  if (getDpEvtLastEvtEid_3() != EVT_DUMMY_3)
      return 0;
  if (abs(getDpEvtLastEvtTime_3()-CrFwGetCurrentTime()) < 0.001)
      return 0;
  if (getDpEvtNOfDetectedEvts_3() != 1)
      return 0;

  /* Reset all components used in the test case */
  CrFwCmpReset(outLoader);
  CrFwCmpReset(outManager);
  CrFwCmpReset(outFactory);
  CrFwCmpReset(outRegistry);

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsEvtTestCase5() {
  CrFwPckt_t pckt;
  FwSmDesc_t rep;
  FwSmDesc_t outRegistry, outFactory, outLoader, outManager;

  CrFwSetAppErrCode(crNoAppErr);

  /* Initialize and reset the framework components */
  outRegistry = CrFwOutRegistryMake();
  CrFwCmpInit(outRegistry);
  CrFwCmpReset(outRegistry);
  outFactory = CrFwOutFactoryMake();
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  outManager = CrFwOutManagerMake(0);
  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  outLoader = CrFwOutLoaderMake();
  CrFwCmpInit(outLoader);
  CrFwCmpReset(outLoader);

  /* Initialize all event related data pool entries */
  setDpEvtLastEvtEid_4(0);
  setDpEvtLastEvtTime_4(0);
  setDpEvtNOfDetectedEvts_4(0);

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  /* Generate a dummy event of level 4 */
  CrPsEvtGenPreDefEvtNoPar(EVT_DUMMY_4);

  /* Check that there is one pending OutComponent of type (5,4) */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmp(outManager,0,5,4,EVT_DUMMY_4) != 1)
      return 0;
  rep = CrPsTestUtilitiesGetItemFromOutManager(outManager,0);
  pckt = CrFwOutCmpGetPckt(rep);

  /* Verify the discriminant of the event report */
  if (CrFwOutCmpGetDiscriminant(rep) != EVT_DUMMY_4)
      return 0;
  if (getEvtRep1EventId(pckt) != EVT_DUMMY_4)
      return 0;

  /* Execute the OutManager so that the event will be executed, too */
  CrFwCmpExecute(outManager);

  /* Check observables related to event */
  if (getDpEvtLastEvtEid_4() != EVT_DUMMY_4)
      return 0;
  if (abs(getDpEvtLastEvtTime_4()-CrFwGetCurrentTime()) < 0.001)
      return 0;
  if (getDpEvtNOfDetectedEvts_4() != 1)
      return 0;

  /* Reset all components used in the test case */
  CrFwCmpReset(outLoader);
  CrFwCmpReset(outManager);
  CrFwCmpReset(outFactory);
  CrFwCmpReset(outRegistry);

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsEvtTestCase6() {
  CrFwPckt_t pckt;
  FwSmDesc_t inCmd;
  FwSmDesc_t outRegistry, inFactory;
  CrFwCmdRepIndex_t evt1Index, evt4Index;

  CrFwSetAppErrCode(crNoAppErr);

  /* Instantiate and configure InFactory, InLoader and InStream */
  inFactory = CrFwInFactoryMake();
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  outRegistry = CrFwOutRegistryMake();
  CrFwCmpInit(outRegistry);
  CrFwCmpReset(outRegistry);

  /* Initialize all event related data pool entries */
  setDpEvtNOfDisabledEid_1(0);
  setDpEvtNOfDisabledEid_4(0);

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  /* Check initial enable status of two dummy events */
  evt1Index = CrFwOutRegistryGetCmdRepIndex(EVT_TYPE, EVTREP1_STYPE);
  evt4Index = CrFwOutRegistryGetCmdRepIndex(EVT_TYPE, EVTREP4_STYPE);
  if (CrFwOutRegistryIsDiscriminantEnabled(evt1Index, EVT_DUMMY_1) != 1)
    return 0;
  if (CrFwOutRegistryIsDiscriminantEnabled(evt4Index, EVT_DUMMY_4) != 1)
    return 0;

  /* Create a (5,6) Packet with two event identifiers */
  pckt = CrFwPcktMake(CR_FW_MAX_PCKT_LENGTH);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,EVT_TYPE);
  CrFwPcktSetServSubType(pckt,EVTDISCMD_STYPE);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);
  CrFwPcktSetSeqCnt(pckt,2);
  setEvtDisCmdN(pckt, 2);       /* 2 event identifiers */
  setEvtDisCmdEventId(pckt, 0, EVT_DUMMY_1);
  setEvtDisCmdEventId(pckt, 1, EVT_DUMMY_4);

  /*Creating an InCommand out of the 5,6 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != EVT_TYPE)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != EVTDISCMD_STYPE)
    return 0;

  /* Execute and terminate  the InCommand  (this simulates the action of an InManager) */
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);

  /*check that the InCommand is in PROGRESS state*/
  if (!CrFwInCmdIsInProgress(inCmd))
    return 0;

  /* Check that only the first EID has been disabled */
  if (getDpEvtNOfDisabledEid_1() != 1)
    return 0;
  if (CrFwOutRegistryIsDiscriminantEnabled(evt1Index, EVT_DUMMY_1) != 0)
    return 0;
  if (CrFwOutRegistryIsDiscriminantEnabled(evt4Index, EVT_DUMMY_4) != 1)
    return 0;

  /* Execute again the InCommand  */
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);

  /*check that the InCommand is in TERMINATED state*/
  if (!CrFwInCmdIsInTerminated(inCmd))
    return 0;

  /* Check that both EIDs have been disabled */
  if (getDpEvtNOfDisabledEid_4() != 1)
    return 0;
  if (CrFwOutRegistryIsDiscriminantEnabled(evt1Index, EVT_DUMMY_1) != 0)
    return 0;
  if (CrFwOutRegistryIsDiscriminantEnabled(evt4Index, EVT_DUMMY_4) != 0)
    return 0;

  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Create a (5,5) Packet with the same two event identifiers */
  pckt = CrFwPcktMake(CR_FW_MAX_PCKT_LENGTH);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,EVT_TYPE);
  CrFwPcktSetServSubType(pckt,EVTENBCMD_STYPE);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);
  CrFwPcktSetSeqCnt(pckt,2);
  setEvtDisCmdN(pckt, 2);       /* 2 event identifiers */
  setEvtDisCmdEventId(pckt, 0, EVT_DUMMY_1);
  setEvtDisCmdEventId(pckt, 1, EVT_DUMMY_4);

  /*Creating an InCommand out of the 5,5 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != EVT_TYPE)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != EVTENBCMD_STYPE)
    return 0;

  /* Execute and terminate  the InCommand (this simulates the action of an InManager) */
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);

  /*check that the InCommand is in PROGRESS state*/
  if (!CrFwInCmdIsInProgress(inCmd))
    return 0;

  /* Check that only the first EID has been enabled */
  if (getDpEvtNOfDisabledEid_1() != 0)
    return 0;
  if (CrFwOutRegistryIsDiscriminantEnabled(evt1Index, EVT_DUMMY_1) != 1)
    return 0;
  if (CrFwOutRegistryIsDiscriminantEnabled(evt4Index, EVT_DUMMY_4) != 0)
    return 0;

  /* Execute again the InCommand  */
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);

  /*check that the InCommand is in TERMINATED state*/
  if (!CrFwInCmdIsInTerminated(inCmd))
    return 0;

  /* Check that both EIDs have been disabled */
  if (getDpEvtNOfDisabledEid_4() != 0)
    return 0;
  if (CrFwOutRegistryIsDiscriminantEnabled(evt1Index, EVT_DUMMY_1) != 1)
    return 0;
  if (CrFwOutRegistryIsDiscriminantEnabled(evt4Index, EVT_DUMMY_4) != 1)
    return 0;

  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Reset all components used in the test case */
  CrFwCmpReset(inFactory);
  CrFwCmpReset(outRegistry);

  /* Check that no packets are allocated */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;


  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsEvtTestCase7() {
  CrFwPckt_t pckt;
  FwSmDesc_t inCmd;
  FwSmDesc_t outRegistry, inFactory, outFactory, outManager, outLoader;
  CrFwCmdRepIndex_t evt1Index;

  CrFwSetAppErrCode(crNoAppErr);

  /* Instantiate and configure InFactory, InLoader, OutManager and InStream */
  inFactory = CrFwInFactoryMake();
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  outRegistry = CrFwOutRegistryMake();
  CrFwCmpInit(outRegistry);
  CrFwCmpReset(outRegistry);
  outFactory = CrFwOutFactoryMake();
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  outManager = CrFwOutManagerMake(0);
  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  outLoader = CrFwOutLoaderMake();
  CrFwCmpInit(outLoader);
  CrFwCmpReset(outLoader);

  /* Initialize all event related data pool entries */
  setDpEvtNOfDisabledEid_1(0);
  setDpEvtNOfDisabledEid_2(0);

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  /* Check that no outComponents are allocated */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Check initial enable status of two dummy events */
  evt1Index = CrFwOutRegistryGetCmdRepIndex(EVT_TYPE, EVTREP1_STYPE);
  if (CrFwOutRegistryIsDiscriminantEnabled(evt1Index, EVT_DUMMY_2) != 1)
    return 0;

  /* Create a (5,6) Packet with two event identifiers (one illegal and one illegal) */
  pckt = CrFwPcktMake(CR_FW_MAX_PCKT_LENGTH);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,EVT_TYPE);
  CrFwPcktSetServSubType(pckt,EVTDISCMD_STYPE);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);
  CrFwPcktSetSeqCnt(pckt,2);
  setEvtDisCmdN(pckt, 2);       /* 2 event identifiers */
  setEvtDisCmdEventId(pckt, 0, EVT_DUMMY_1);        /* Legal event identifier */
  setEvtDisCmdEventId(pckt, 1, EVT_DUMMY_4+200);    /* Illegal event identifier */

  /*Creating an InCommand out of the 5,6 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* Execute and terminate  the InCommand  (this simulates the action of an InManager) */
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);

  /*check that the InCommand is in PROGRESS state*/
  if (!CrFwInCmdIsInProgress(inCmd))
    return 0;

  /* Check that the first EID has been disabled */
  if (CrFwOutRegistryIsDiscriminantEnabled(evt1Index, EVT_DUMMY_1) != 0)
    return 0;

  /* Execute again the InCommand  */
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);

  /*check that the InCommand is in ABORTED state*/
  if (!CrFwInCmdIsInAborted(inCmd))
    return 0;

  /* Check that a (1,6) and (1,8) reports have been loaded in the OutManager with failure code VER_ILL_EID */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 2)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmp(outManager,0,1,6,VER_ILL_EID) != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,0,6,VER_ILL_EID,EVT_DUMMY_4+200) != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,1,8,VER_ILL_EID,1) != 1)
    return 0;

  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Create a (5,5) Packet with two event identifiers (one illegal and one illegal) */
  pckt = CrFwPcktMake(CR_FW_MAX_PCKT_LENGTH);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,EVT_TYPE);
  CrFwPcktSetServSubType(pckt,EVTENBCMD_STYPE);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);
  CrFwPcktSetSeqCnt(pckt,2);
  setEvtDisCmdN(pckt, 2);       /* 2 event identifiers */
  setEvtDisCmdEventId(pckt, 0, EVT_DUMMY_4+200);        /* Illegal event identifier */
  setEvtDisCmdEventId(pckt, 1, EVT_DUMMY_1);            /* Legal event identifier */

  /*Creating an InCommand out of the 5,5 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* Execute and terminate  the InCommand  (this simulates the action of an InManager) */
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);

  /*check that the InCommand is in PROGRESS state*/
  if (!CrFwInCmdIsInProgress(inCmd))
    return 0;

  /* Check that a (1,6) and (1,8) reports have been loaded in the OutManager with failure code VER_ILL_EID */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 3)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmp(outManager,2,1,6,VER_ILL_EID) != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,2,6,VER_ILL_EID,EVT_DUMMY_4+200) != 1)
    return 0;

  /* Execute again the InCommand  */
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);

  /* Check that the first EID has been enabled and that there are no new service 1 reports */
  if (CrFwOutRegistryIsDiscriminantEnabled(evt1Index, EVT_DUMMY_1) != 1)
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 4)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,3,8,VER_ILL_EID,1) != 1)
    return 0;

  /*check that the InCommand is in ABORTED state*/
  if (!CrFwInCmdIsInAborted(inCmd))
    return 0;

  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Reset all components used in the test case */
  CrFwCmpReset(inFactory);
  CrFwCmpReset(outRegistry);
  CrFwCmpReset(outManager);
  CrFwCmpReset(outFactory);
  CrFwCmpReset(outLoader);

  /* Check that no packets are allocated */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;


  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}


/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsEvtTestCase8() {
  CrFwPckt_t pckt, pckt1, pckt2;
  FwSmDesc_t inCmd, rep5s8;
  FwSmDesc_t outRegistry, inFactory, outFactory, outManager, outLoader, outStream;

  CrFwSetAppErrCode(crNoAppErr);

  /* Instantiate and configure InFactory, InLoader, OutManager and InStream */
  inFactory = CrFwInFactoryMake();
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  outRegistry = CrFwOutRegistryMake();
  CrFwCmpInit(outRegistry);
  CrFwCmpReset(outRegistry);
  outFactory = CrFwOutFactoryMake();
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  outManager = CrFwOutManagerMake(0);
  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  outLoader = CrFwOutLoaderMake();
  CrFwCmpInit(outLoader);
  CrFwCmpReset(outLoader);
  outStream = CrFwOutStreamMake(0);     /* OutStream associated to destination EVT_DEST */
  CrFwCmpInit(outStream);
  CrFwCmpReset(outStream);

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  /* Check that no outComponents are allocated */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Disable two event identifiers */
  CrPsEvtConfigSetEidEnableStatus (EVT_DUMMY_1, 0);
  setDpEvtNOfDisabledEid_1(1);
  CrPsEvtConfigSetEidEnableStatus (EVT_DUMMY_3, 0);
  setDpEvtNOfDisabledEid_3(1);

  /* Create a (5,7) Packet */
  pckt = CrFwPcktMake(LEN_EVT_REPDISCMD);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,EVT_TYPE);
  CrFwPcktSetServSubType(pckt,EVTREPDISCMD_STYPE);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,EVT_DEST);       /* This will be the destination of the (5,8) report */
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);
  CrFwPcktSetSeqCnt(pckt,2);

  /*Create an InCommand out of the 5,7 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* Execute and terminate the InCommand (this simulates the action of an InManager) */
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);

  /*check that the InCommand is in TERMINATED state*/
  if (!CrFwInCmdIsInTerminated(inCmd))
    return 0;

  /* Check that a (5,8) report has been loaded in the OutManager */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmp(outManager,0,5,8,0) != 1)
    return 0;
  rep5s8 = CrPsTestUtilitiesGetItemFromOutManager(outManager, 0);
  pckt = CrFwOutCmpGetPckt(rep5s8);

  /* Execute the OutManager (this causes the (5,8) report to be executed */
  CrFwCmpExecute(outManager);

  /* The following checks are dangerous because the outCmp has already been released!!!!
   * They only work because the pckt of the released outCmp has not yet been overwritten */
  if (getEvtDisRepN(pckt) != 2)
    return 0;
  if (getEvtDisRepEventId(pckt,0) != EVT_DUMMY_1)
    return 0;
  if (getEvtDisRepEventId(pckt,1) != EVT_DUMMY_3)
    return 0;

  /*----------------------------------- Step 2 ------------------------------------------*/
  /* Disable 8 event identifiers */
  CrPsEvtConfigSetEidEnableStatus (EVT_DUMMY_1, 0);
  CrPsEvtConfigSetEidEnableStatus (EVT_DOWN_ABORT, 0);
  CrPsEvtConfigSetEidEnableStatus (EVT_UP_ABORT, 0);
  setDpEvtNOfDisabledEid_1(3);
  CrPsEvtConfigSetEidEnableStatus (EVT_MON_LIM_I, 0);
  CrPsEvtConfigSetEidEnableStatus (EVT_MON_DEL_R, 0);
  CrPsEvtConfigSetEidEnableStatus (EVT_MON_DEL_I, 0);
  CrPsEvtConfigSetEidEnableStatus (EVT_FMON_FAIL, 0);
  CrPsEvtConfigSetEidEnableStatus (EVT_DUMMY_3, 0);
  setDpEvtNOfDisabledEid_3(5);

  /* Create a (5,7) Packet */
  pckt = CrFwPcktMake(LEN_EVT_REPDISCMD);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,EVT_TYPE);
  CrFwPcktSetServSubType(pckt,EVTREPDISCMD_STYPE);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,EVT_DEST);       /* This will be the destination of the (5,8) report */
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);
  CrFwPcktSetSeqCnt(pckt,2);

  /*Create an InCommand out of the 5,7 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* Execute and terminate the InCommand (this simulates the action of an InManager) */
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);

  /*check that the InCommand is in TERMINATED state*/
  if (!CrFwInCmdIsInTerminated(inCmd))
    return 0;

  /* Check that two (5,8) reports have been loaded in the OutManager */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 2)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmp(outManager,0,5,8,0) != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmp(outManager,1,5,8,0) != 1)
    return 0;
  rep5s8 = CrPsTestUtilitiesGetItemFromOutManager(outManager, 0);
  pckt1 = CrFwOutCmpGetPckt(rep5s8);
  rep5s8 = CrPsTestUtilitiesGetItemFromOutManager(outManager, 1);
  pckt2 = CrFwOutCmpGetPckt(rep5s8);

  /* Execute the OutManager (this causes the (5,8) reports to be executed */
  CrFwCmpExecute(outManager);

  /* The following checks are dangerous because the outCmp has already been released!!!!
   * They only work because the pckt of the released outCmp has not yet been overwritten */
  if (getEvtDisRepN(pckt1) != 7)
    return 0;
  if (getEvtDisRepN(pckt2) != 1)
    return 0;
  if (getEvtDisRepEventId(pckt2,0) != EVT_DUMMY_3)
    return 0;

  /* Reset all components used in the test case */
  CrFwCmpReset(inFactory);
  CrFwCmpReset(outRegistry);
  CrFwCmpReset(outManager);
  CrFwCmpReset(outFactory);
  CrFwCmpReset(outLoader);

  /* Check that no packets are allocated */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsEvtTestCase9() {
  FwSmDesc_t outRegistry, outFactory, outLoader, outManager, inCmd;
  FwSmDesc_t outCmpArr[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP];
  unsigned int i;
  CrFwPckt_t pckt;
  CrFwCounterU2_t errRepPos;

  CrFwSetAppErrCode(crNoAppErr);

  /* Initialize and reset the framework components */
  outRegistry = CrFwOutRegistryMake();
  CrFwCmpInit(outRegistry);
  CrFwCmpReset(outRegistry);
  outFactory = CrFwOutFactoryMake();
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  outManager = CrFwOutManagerMake(0);
  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  outLoader = CrFwOutLoaderMake();
  CrFwCmpInit(outLoader);
  CrFwCmpReset(outLoader);

  /* Fill the outfactory */
  for (i=0;i<CR_FW_OUTFACTORY_MAX_NOF_OUTCMP;i++)
    outCmpArr[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);

  /* Retrieve pointer position in the Stub Error Report */
  errRepPos = CrFwRepErrStubGetPos();

  /* Attempt to generate a pre-defined parameterless event */
  CrPsEvtGenPreDefEvtNoPar(EVT_DUMMY_2);
  if (CrFwRepErrStubGetPos() != errRepPos+1)
      return 0;
  if (CrFwRepErrStubGetErrCode(errRepPos) != psOutFactoryFail)
      return 0;

  /* The Error Code has been set by the OutFactory and must be reset */
  if (CrFwGetAppErrCode()!=crOutCmpAllocationFail)
      return 0;
  CrFwSetAppErrCode(crNoAppErr);

  /* Attempt to generate a pre-defined event with dummy parameter */
  CrPsEvtGenPreDefEvtDummyPar(EVT_DUMMY_1, 1);
  if (CrFwRepErrStubGetPos() != errRepPos+2)
      return 0;
  if (CrFwRepErrStubGetErrCode(errRepPos+1) != psOutFactoryFail)
      return 0;

  /* The Error Code has been set by the OutFactory and must be reset */
  if (CrFwGetAppErrCode()!=crOutCmpAllocationFail)
      return 0;
  CrFwSetAppErrCode(crNoAppErr);

  /*------------------------------------------------ Step 2 ------------------------------------------*/
  /* Create a (5,7) Packet */
  pckt = CrFwPcktMake(LEN_EVT_REPDISCMD);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,EVT_TYPE);
  CrFwPcktSetServSubType(pckt,EVTREPDISCMD_STYPE);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,EVT_DEST);       /* This will be the destination of the (5,8) report */
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);
  CrFwPcktSetSeqCnt(pckt,2);

  /*Create an InCommand out of the 5,7 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* Execute and terminate the InCommand (this simulates the action of an InManager) */
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);

  /* Verify generation of error report */
  if (CrFwRepErrStubGetPos() != errRepPos+3)
      return 0;
  if (CrFwRepErrStubGetErrCode(errRepPos+2) != psOutFactoryFail)
      return 0;

  /* The Error Code has been set by the OutFactory and must be reset */
  if (CrFwGetAppErrCode()!=crOutCmpAllocationFail)
      return 0;
  CrFwSetAppErrCode(crNoAppErr);

  /* Release all outcomponents, that have been created to fill the outfactory */
  for (i=0;i<CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1;i++)
    CrFwOutFactoryReleaseOutCmp(outCmpArr[i]);

  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Reset all components used in the test case */
  CrFwCmpReset(outRegistry);
  CrFwCmpReset(outManager);
  CrFwCmpReset(outFactory);
  CrFwCmpReset(outLoader);

  /* Check that no packets are allocated */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}
