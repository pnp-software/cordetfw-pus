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

/* Include system files */
#include <stdlib.h>
#include <unistd.h>

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsEvtTestCase1() {
  CrFwPckt_t pckt;
  FwSmDesc_t rep;
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
CrFwBool_t CrPsEvtTestCase1() {
  CrFwPckt_t pckt;
  FwSmDesc_t rep;
  unsigned int sevLev, nAllocatedRep;
  FwSmDesc_t outRegistry, outFactory, outLoader, outManager;
  CrFwPckt_t pckt;

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

  /* Retrieve number of allocated OutComponents */
  nAllocatedRep = CrFwOutFactoryGetNOfAllocatedOutCmp();

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
  if (CrPsTestUtilitiesCheckOutManagerCmd(outManager,0,5,1,EVT_DUMMY_1) != 1)
      return 0;

  /* Check the parameter of the level 1 event */
  pckt = CrFwOutCmp(CrPsTestUtilitiesGetItemFromOutManager(outManager,0));
  if (getEvtRep1_EVT_DUMMY_1Par(pckt) != 11)
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
