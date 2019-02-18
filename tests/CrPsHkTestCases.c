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

/* Include system files */
#include <stdlib.h>
#include <unistd.h>

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsHkTestCase1() {
  int rdlPos,i;
  FwSmDesc_t rep;
  CrPsParId_t parId1[HK_NOFITEMS_SID_HK_CNT] = HK_DEF_SID_HK_CNT;
  CrPsParId_t parId2[HK_NOFITEMS_SID_N_OF_EVT] = HK_DEF_SID_N_OF_EVT;

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
  CrPsHkConfigHkRep(rep, rdlPos, SID_HK_CNT, HK_NOFITEMS_SID_HK_CNT, 0, 1, &parId1[0]);
  if (CrPsHkConfigGetRdlSlot(SID_HK_CNT) != rdlPos)
      return 0;

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

  /* Attempt to set enable status of a non-existent SID */
  if (CrPsHkConfigSetSidEnableStatus(HK_MAX_SID+1, 1) != -1)
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
  setHkCreHkCmdSID(pckt,HK_MAX_SID+1);                             /* Illegal SID */
  setHkCreHkCmdCollectionInterval(pckt, 0);
  setHkCreHkCmdN1(pckt, HK_MAX_N_SIMPLE+1);             /* Illegal number of data items */
  for (i=0; i<HK_MAX_N_SIMPLE+1; i++)
      setHkCreHkCmdN1ParamId(pckt, i, DpIdParamsLowest-1+i);  /* The first parameter ID is illegal */

  /*Create an InCommand out of the (3,1) packet*/
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

  /* Execute and terminate the InCommand  (this simulates the action of an InManager) */
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

  /* ---------------------------------------- Step 2 ---------------------------*/
  /* Remove RDL entries added for this test */
  for (i=0; i<HK_N_REP_DEF-2; i++) {
      rdlPos = CrPsHkConfigClearSid(120+i);
      if (rdlPos == -1)
          return 0;
  }
  CrFwOutFactoryReleaseOutCmp(rep);

  /* Re-create the InCommand and verify that now it is rejected because of the illegal SID */
  inCmd = CrFwInFactoryMakeInCmd(pckt);
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);
  if (!CrFwInCmdIsInTerminated(inCmd))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 2)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,1,4,VER_ILL_SID,0) != 1)
      return 0;

  /* ---------------------------------------- Step 3 ---------------------------*/
  /* Change the InCommand's SID to be legal and verify that now it is rejected because
   * of the illegal parameter identifier */
  setHkCreHkCmdSID(pckt,HK_MAX_SID);      /* Legal SID */
  inCmd = CrFwInFactoryMakeInCmd(pckt);
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);
  if (!CrFwInCmdIsInTerminated(inCmd))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 3)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,1,4,VER_ILL_DI_ID,0) != 1)
      return 0;

  /* ---------------------------------------- Step 3 ---------------------------*/
  /* Change the InCommand's SID to be legal and verify that now it is rejected because
   * of the illegal parameter identifier */
  setHkCreHkCmdSID(pckt,SID_N_OF_EVT);      /* SID already in use */
  setHkCreHkCmdN1ParamId(pckt, 0, DpIdParamsLowest);  /* Legal parameter ID */
  inCmd = CrFwInFactoryMakeInCmd(pckt);
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);
  if (!CrFwInCmdIsInTerminated(inCmd))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 3)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,1,4,VER_SID_IN_USE,0) != 1)
      return 0;

  /* ---------------------------------------- Step 4 ---------------------------*/
  /* Change the InCommand's SID to be legal and verify that now it is rejected because
   * of the illegal parameter identifier */
  setHkCreHkCmdSID(pckt,HK_MAX_SID);      /* Legal SID */
  setHkCreHkCmdN1ParamId(pckt, 0, DpIdParamsLowest);  /* The first parameter ID is now legal */
  inCmd = CrFwInFactoryMakeInCmd(pckt);
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);
  if (!CrFwInCmdIsInTerminated(inCmd))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 3)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,1,4,VER_ILL_NID,0) != 1)
      return 0;

  /* ---------------------------------------------------------------------------*/
  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Check that no packets are allocated */
  if (CrFwPcktGetNOfAllocated() != 0)
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

