/**
 * @file CrPsEvtTestCases.c
 * @ingroup PUSTestsuite
 *
 * @brief Implementation of test cases for the Event Reporting Service.
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

#include "Pckt/CrPsPcktVer.h"
#include "Pckt/CrPsPcktEvt.h"
#include "Pckt/CrPsPckt.h"
#include "DataPool/CrPsDpVer.h"
#include "DataPool/CrPsDpEvt.h"
#include "Evt/CrPsEvtConfig.h"
#include "CrPsServTypeId.h"
#include "CrPsConstants.h"
#include "CrPsTestUtilities.h"
#include "Dum/CrPsInCmdDumSample1Ctrl.h"
#include "Evt/CrPsEvtGenPreDefEvt.h"

/* Include system files */
#include <stdlib.h>
#include <unistd.h>

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsEvtTestCase1() {
  unsigned int sevLev;
  FwSmDesc_t outRegistry;

  CrFwSetAppErrCode(crNoAppErr);

  /* Initialize and reset the OutRegistry (which is used in module CrPsEvtConfig) */
  outRegistry = CrFwOutRegistryMake();
  CrFwCmpInit(outRegistry);
  CrFwCmpReset(outRegistry);

  /* Check position of event identifier */
  if (CrPsEvtConfigGetEidPos(EVT_DUMMY_4, 6) != -1)     /* Illegal severity level */
      return 0;
  if (CrPsEvtConfigGetEidPos(EVT_DUMMY_4, 1) != -1)     /* Incorrect severity level */
      return 0;
  if (CrPsEvtConfigGetEidPos(EVT_DUMMY_4, 4) != 0)
      return 0;
  if (CrPsEvtConfigGetEidPos(EVT_DUMMY_4+1000, 4) != -1) /* Non-existent event identifier */
      return 0;

  /* Check setting of enabled status */
  if (CrPsEvtConfigGetEidEnableStatus(EVT_DUMMY_4) != 1)    /* Check default enabled status */
      return 0;

  sevLev = CrPsEvtConfigSetEidEnableStatus(EVT_DUMMY_4, 0); /* Disable event */
  if (sevLev != 4)
      return 0;
  if (CrPsEvtConfigGetEidEnableStatus(EVT_DUMMY_4) != 0)
      return 0;

  sevLev = CrPsEvtConfigSetEidEnableStatus(EVT_DUMMY_4, 1); /* Enable event */
  if (sevLev != 4)
      return 0;
  if (CrPsEvtConfigGetEidEnableStatus(EVT_DUMMY_4) != 1)
      return 0;

  sevLev = CrPsEvtConfigSetEidEnableStatus(EVT_DUMMY_4+1000, 0); /* Non-existent event */
  if (sevLev != 0)
      return 0;

  /* Check function to get the severity level of an event */
  if (CrPsEvtConfigGetSevLevel(EVT_DUMMY_1) != 1)
    return 0;
  if (CrPsEvtConfigGetSevLevel(EVT_DUMMY_2) != 2)
    return 0;
  if (CrPsEvtConfigGetSevLevel(EVT_MON_DEL_I) != 3)
    return 0;
  if (CrPsEvtConfigGetSevLevel(EVT_DUMMY_4) != 4)
    return 0;

  if (CrPsEvtConfigGetSevLevel(EVT_DUMMY_4+1000) != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsEvtTestCase2() {
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
  setDpEvtLastEvtEid_1(0);
  setDpEvtLastEvtTime_1(0);
  setDpEvtNOfDetectedEvts_1(0);

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  /* Generate a dummy event of level 1 */
  CrPsEvtGenPreDefEvtDummyPar(EVT_DUMMY_1, 11);

  /* Check that there is one pending OutComponent of type (5,1) */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmp(outManager,0,5,1,EVT_DUMMY_1) != 1)
      return 0;

  /* Check the parameter of the event */
  rep = CrPsTestUtilitiesGetItemFromOutManager(outManager,0);
  pckt = CrFwOutCmpGetPckt(rep);
  if (getEvtRep1_EVT_DUMMY_1Par(pckt) != 11)
      return 0;

  /* Verify the discriminant of the event report */
  if (CrFwOutCmpGetDiscriminant(rep) != EVT_DUMMY_1)
      return 0;
  if (getEvtRep1EventId(pckt) != EVT_DUMMY_1)
      return 0;

  /* Execute the OutManager so that the event will be executed, too */
  CrFwCmpExecute(outManager);

  /* Check observables related to level 1 events */
  if (getDpEvtLastEvtEid_1() != EVT_DUMMY_1)
      return 0;
  if (abs(getDpEvtLastEvtTime_1()-CrFwGetCurrentTime()) < 0.001)
      return 0;
  if (getDpEvtNOfDetectedEvts_1() != 1)
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

  /* Instantiate and configure InFactory, InLoader, OutManager and InStream */
  inFactory = CrFwInFactoryMake();
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  outRegistry = CrFwOutRegistryMake();
  CrFwCmpInit(outRegistry);
  CrFwCmpReset(outRegistry);

  /* Initialize all event related data pool entries */
  setDpEvtNOfDisabledEid_1(0);
  setDpEvtNOfDisabledEid_2(0);

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

