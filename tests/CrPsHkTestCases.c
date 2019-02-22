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
#include "DataPool/CrPsDp.h"
#include "DataPool/CrPsDpHk.h"

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
  inCmd = CrPsTestUtilitiesMake3s1(1, 2, parId);

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
  inCmd = CrPsTestUtilitiesMake3s1(1, 2, parId);
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
  inCmd = CrPsTestUtilitiesMake3s1(1, 2, parId);
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
  inCmd = CrPsTestUtilitiesMake3s1(1, 2, parId);
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
  inCmd = CrPsTestUtilitiesMake3s1(1, 2, parId);
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
  /* Create a (3,1) command to have a data item identifier equal to zero and then execute and verify error */
  inCmd = CrPsTestUtilitiesMake3s1(1, 2, parId);
  pckt = CrFwInCmdGetPckt(inCmd);
  setHkCreHkCmdN1ParamId(pckt, 0, 0);

  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);
  if (!CrFwInCmdIsInAborted(inCmd))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != HK_N_REP_DEF+6)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,5,4,VER_ILL_DI_ID,0) != 1)
      return 0;

  /* ---------------------------------------- Step 3 ---------------------------*/
  /* Change the InCommand's SID to be equal to 1 and then execute and verify error */
  inCmd = CrPsTestUtilitiesMake3s1(1, 2, parId);
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
  CrPsParId_t parId[2] = {DpIdnOfAllocatedInCmd, DpIdnOfAllocatedInRep};

  /* Reset the framework components */
  CrPsTestUtilitiesResetFw();

  /* Create a (3,1) command */
  inCmd = CrPsTestUtilitiesMake3s1(1, 2, parId);;

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






  /* ---------------------------------------------------------------------------*/
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
