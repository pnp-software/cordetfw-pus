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

#include "Pckt/CrPsPcktVer.h"
#include "Pckt/CrPsPcktEvt.h"
#include "Pckt/CrPsPckt.h"
#include "DataPool/CrPsDpVer.h"
#include "DataPool/CrPsDpEvt.h"
#include "Evt/CrPsEvtConfig.h"
#include "CrPsServTypeId.h"
#include "CrPsConstants.h"
#include "CrPsTypes.h"
#include "CrPsTestUtilities.h"
#include "Dum/CrPsInCmdDumSample1Ctrl.h"
#include "Evt/CrPsEvtGenPreDefEvt.h"

/* Include system files */
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

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
  FwSmDesc_t outManager;
  int sevLevel = 1;

  /* Reset the framework components */
  CrPsTestUtilitiesResetFw();
  outManager = CrFwOutManagerMake(0);

  /* Initialize all event related data pool entries */
  setDpEvtLastEvtEidItem(sevLevel-1,0);
  setDpEvtLastEvtTimeItem(sevLevel-1, 0);
  setDpEvtNOfDetectedEvtsItem(sevLevel-1, 0);

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
  if (getEvtInfoRep_EVT_DUMMY_1Par(pckt) != 11)
      return 0;

  /* Verify the discriminant of the event report */
  if (CrFwOutCmpGetDiscriminant(rep) != EVT_DUMMY_1)
      return 0;
  if (getEvtInfoRepEventId(pckt) != EVT_DUMMY_1)
      return 0;

  /* Execute the OutManager so that the event will be executed, too */
  CrFwCmpExecute(outManager);

  /* Check observables related to level 1 events */
  if (getDpEvtLastEvtEidItem(sevLevel-1) != EVT_DUMMY_1)
      return 0;
  if (fabs(getDpEvtLastEvtTimeItem(sevLevel-1)-CrFwGetCurrentTime()) < 0.001)
      return 0;
  if (getDpEvtNOfDetectedEvtsItem(sevLevel-1) != 1)
      return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsEvtTestCase3() {
  CrFwPckt_t pckt;
  FwSmDesc_t rep;
  FwSmDesc_t outManager;
  int sevLevel = 2;

  /* Reset the framework components */
  CrPsTestUtilitiesResetFw();
  outManager = CrFwOutManagerMake(0);

  /* Initialize all event related data pool entries */
  setDpEvtLastEvtEidItem(sevLevel-1,0);
  setDpEvtLastEvtTimeItem(sevLevel-1, 0);
  setDpEvtNOfDetectedEvtsItem(sevLevel-1, 0);

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
  if (getEvtInfoRepEventId(pckt) != EVT_DUMMY_2)
      return 0;

  /* Execute the OutManager so that the event will be executed, too */
  CrFwCmpExecute(outManager);

  /* Check observables related to event */
  if (getDpEvtLastEvtEidItem(sevLevel-1) != EVT_DUMMY_2)
      return 0;
  if (fabs(getDpEvtLastEvtTimeItem(sevLevel-1)-CrFwGetCurrentTime()) < 0.001)
      return 0;
  if (getDpEvtNOfDetectedEvtsItem(sevLevel-1) != 1)
      return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsEvtTestCase4() {
  CrFwPckt_t pckt;
  FwSmDesc_t rep;
  FwSmDesc_t outManager;
  int sevLevel = 3;

  /* Reset the framework components */
  CrPsTestUtilitiesResetFw();
  outManager = CrFwOutManagerMake(0);

  /* Initialize all event related data pool entries */
  setDpEvtLastEvtEidItem(sevLevel-1,0);
  setDpEvtLastEvtTimeItem(sevLevel-1, 0);
  setDpEvtNOfDetectedEvtsItem(sevLevel-1, 0);

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
  if (getEvtInfoRep_EVT_DUMMY_1Par(pckt) != 127)
      return 0;

  /* Verify the discriminant of the event report */
  if (CrFwOutCmpGetDiscriminant(rep) != EVT_DUMMY_3)
      return 0;
  if (getEvtInfoRepEventId(pckt) != EVT_DUMMY_3)
      return 0;

  /* Execute the OutManager so that the event will be executed, too */
  CrFwCmpExecute(outManager);

  /* Check observables related to level 1 events */
  if (getDpEvtLastEvtEidItem(sevLevel-1) != EVT_DUMMY_3)
      return 0;
  if (fabs(getDpEvtLastEvtTimeItem(sevLevel-1)-CrFwGetCurrentTime()) < 0.001)
      return 0;
  if (getDpEvtNOfDetectedEvtsItem(sevLevel-1) != 1)
      return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsEvtTestCase5() {
  CrFwPckt_t pckt;
  FwSmDesc_t rep;
  FwSmDesc_t outManager;
  int sevLevel = 4;

  /* Reset the framework components */
  CrPsTestUtilitiesResetFw();
  outManager = CrFwOutManagerMake(0);

  /* Initialize all event related data pool entries */
  setDpEvtLastEvtEidItem(sevLevel-1,0);
  setDpEvtLastEvtTimeItem(sevLevel-1, 0);
  setDpEvtNOfDetectedEvtsItem(sevLevel-1, 0);

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
  if (getEvtInfoRepEventId(pckt) != EVT_DUMMY_4)
      return 0;

  /* Execute the OutManager so that the event will be executed, too */
  CrFwCmpExecute(outManager);

  /* Check observables related to event */
  if (getDpEvtLastEvtEidItem(sevLevel-1) != EVT_DUMMY_4)
      return 0;
  if (fabs(getDpEvtLastEvtTimeItem(sevLevel-1)-CrFwGetCurrentTime()) < 0.001)
      return 0;
  if (getDpEvtNOfDetectedEvtsItem(sevLevel-1) != 1)
      return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsEvtTestCase6() {
  CrFwPckt_t pckt;
  FwSmDesc_t inCmd;
  CrFwCmdRepIndex_t evt1Index, evt4Index;
  CrFwCrc_t crc;

  /* Reset the framework components */
  CrPsTestUtilitiesResetFw();

  /* Initialize all event related data pool entries */
  setDpEvtNOfDisabledEidItem(0,0);
  setDpEvtNOfDisabledEidItem(3, 0);

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  /* Check initial enable status of two dummy events */
  evt1Index = CrFwOutRegistryGetCmdRepIndex(EVT_TYPE, EVTINFOREP_STYPE);
  evt4Index = CrFwOutRegistryGetCmdRepIndex(EVT_TYPE, EVTHIGHSEVREP_STYPE);
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
  crc = CrFwPcktComputeCrc(pckt);
  CrFwPcktSetCrc(pckt, crc);
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
  if (getDpEvtNOfDisabledEidItem(0) != 1)
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
  if (getDpEvtNOfDisabledEidItem(3) != 1)
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
  crc = CrFwPcktComputeCrc(pckt);
  CrFwPcktSetCrc(pckt, crc);
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
  if (getDpEvtNOfDisabledEidItem(0) != 0)
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
  if (getDpEvtNOfDisabledEidItem(3) != 0)
    return 0;
  if (CrFwOutRegistryIsDiscriminantEnabled(evt1Index, EVT_DUMMY_1) != 1)
    return 0;
  if (CrFwOutRegistryIsDiscriminantEnabled(evt4Index, EVT_DUMMY_4) != 1)
    return 0;

  /*Release the InCommand and reset the fw components*/
  CrFwInFactoryReleaseInCmd(inCmd);
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
CrFwBool_t CrPsEvtTestCase7() {
  CrFwPckt_t pckt;
  FwSmDesc_t inCmd;
  FwSmDesc_t outManager;
  CrFwCmdRepIndex_t evt1Index;
  CrFwCrc_t crc;

  /* Reset the framework components */
  CrPsTestUtilitiesResetFw();
  outManager = CrFwOutManagerMake(0);

  /* Initialize all event related data pool entries */
  setDpEvtNOfDisabledEidItem(0, 0);
  setDpEvtNOfDisabledEidItem(1, 0);

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  /* Check that no outComponents are allocated */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Check initial enable status of two dummy events */
  evt1Index = CrFwOutRegistryGetCmdRepIndex(EVT_TYPE, EVTINFOREP_STYPE);
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
  crc = CrFwPcktComputeCrc(pckt);
  CrFwPcktSetCrc(pckt, crc);
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
  crc = CrFwPcktComputeCrc(pckt);
  CrFwPcktSetCrc(pckt, crc);
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

  /*Release the InCommand and reset the fw components */
  CrFwInFactoryReleaseInCmd(inCmd);
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
CrFwBool_t CrPsEvtTestCase8() {
  CrFwPckt_t pckt, pckt1, pckt2;
  FwSmDesc_t inCmd, rep5s8;
  FwSmDesc_t outManager;
  CrFwCrc_t crc;

  CrFwSetAppErrCode(crNoAppErr);

  /* Instantiate and configure InFactory, InLoader, OutManager and InStream */
  CrPsTestUtilitiesResetFw();
  outManager = CrFwOutManagerMake(0);

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
      return 0;

  /* Check that no outComponents are allocated */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Disable two event identifiers */
  CrPsEvtConfigSetEidEnableStatus (EVT_DUMMY_1, 0);
  setDpEvtNOfDisabledEidItem(0,1);
  CrPsEvtConfigSetEidEnableStatus (EVT_DUMMY_3, 0);
  setDpEvtNOfDisabledEidItem(2,1);

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
  crc = CrFwPcktComputeCrc(pckt);
  CrFwPcktSetCrc(pckt, crc);

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
  /* Disable 12 event identifiers */
  CrPsEvtConfigSetEidEnableStatus (EVT_DUMMY_1, 0);
  CrPsEvtConfigSetEidEnableStatus (EVT_DOWN_ABORT, 0);
  CrPsEvtConfigSetEidEnableStatus (EVT_UP_ABORT, 0);
  setDpEvtNOfDisabledEidItem(0, 3);

  CrPsEvtConfigSetEidEnableStatus (EVT_CLST_FULL, 0);
  CrPsEvtConfigSetEidEnableStatus (EVT_DUMMY_2, 0);
  setDpEvtNOfDisabledEidItem(1, 2);

  CrPsEvtConfigSetEidEnableStatus (EVT_MON_LIM_I, 0);
  CrPsEvtConfigSetEidEnableStatus (EVT_MON_LIM_R, 0);
  CrPsEvtConfigSetEidEnableStatus (EVT_MON_DEL_R, 0);
  CrPsEvtConfigSetEidEnableStatus (EVT_MON_DEL_I, 0);
  CrPsEvtConfigSetEidEnableStatus (EVT_FMON_FAIL, 0);
  CrPsEvtConfigSetEidEnableStatus (EVT_DUMMY_3, 0);
  setDpEvtNOfDisabledEidItem(2, 6);

  CrPsEvtConfigSetEidEnableStatus (EVT_DUMMY_4, 0);
  setDpEvtNOfDisabledEidItem(3, 1);

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
  crc = CrFwPcktComputeCrc(pckt);
  CrFwPcktSetCrc(pckt, crc);

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
  if (getEvtDisRepN(pckt1) != 8)
    return 0;
  if (getEvtDisRepN(pckt2) != 4)
    return 0;
  if (getEvtDisRepEventId(pckt2,0) != EVT_MON_DEL_I)
    return 0;

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
CrFwBool_t CrPsEvtTestCase9() {
  FwSmDesc_t inCmd;
  FwSmDesc_t outCmpArr[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP];
  unsigned int i;
  CrFwPckt_t pckt;
  CrFwCounterU2_t errRepPos;
  CrFwCrc_t crc;

  /* Reset the framework components */
  CrPsTestUtilitiesResetFw();

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
  crc = CrFwPcktComputeCrc(pckt);
  CrFwPcktSetCrc(pckt, crc);

  /*Create an InCommand out of the 5,7 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* Execute and terminate the InCommand (this simulates the action of an InManager) */
  errRepPos = CrFwRepErrStubGetPos();
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);

  /* Verify generation of error report */
  if (CrFwRepErrStubGetPos() != errRepPos+2)    /* One for (5,8) and one for (1,4) */
      return 0;
  if (CrFwRepErrStubGetErrCode(errRepPos+1) != psOutFactoryFail)
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
