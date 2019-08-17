/**
 * @file CrPsMonTestCases.c
 * @ingroup PUSTestsuite
 *
 * @brief Implementation of test cases for the On-Board Monitoring Service.
 *
 * @author Alessandro Pasetti  <pasetti@pnp-software.com>
 * 
 * @copyright P&P Software GmbH, 2019
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 */

#include "CrPsMonTestCases.h"

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

#include "Pckt/CrPsPcktMon.h"
#include "Pckt/CrPsPcktEvt.h"
#include "Pckt/CrPsPckt.h"
#include "DataPool/CrPsDp.h"
#include "DataPool/CrPsDpMon.h"
#include "DataPool/CrPsDpEvt.h"
#include "Mon/CrPsMonConfig.h"
#include "CrPsServTypeId.h"
#include "CrPsConstants.h"
#include "CrPsTypes.h"
#include "CrPsTestUtilities.h"
#include "CrPsOutStreamStub.h"

/* Include system files */
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsMonTestCase1() {
  float lowerLimFloat, upperLimFloat, valFloat;
  double valDouble;
  int lowerLimInt, upperLimInt, valInt;
  unsigned int lowerLimUInt, upperLimUInt, valUInt, expVal, expValMask;
  short valShort;
  char valChar;
  unsigned short valUShort;
  unsigned char valUChar;
  CrPsParMonId_t parMonId = 1;

  /* Call the initialization function of the monitoring service */
  CrPsMonConfigInit();

  /* The monitor procedure for float values is verified on variable DpIdlastEvtTime */
  lowerLimFloat = 1.3;
  upperLimFloat = 1.7;

  /* Definition of parameter monitor */
  CrPsMonConfigInitParMon(parMonId, DpIdlastEvtTime, MON_PR_OOL_R, 0, 0, 0, 0, 0,
          (CrPsThirtytwoBit_t*)&lowerLimFloat, 0, (CrPsThirtytwoBit_t*)&upperLimFloat, 0);

  /* Verify check for real-valued data item */
  valFloat = 1.5;
  if (setDpValue(DpIdlastEvtTime, &valFloat) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckR(parMonId) != MON_VALID)
      return 0;

  valFloat = lowerLimFloat - 0.1;
  if (setDpValue(DpIdlastEvtTime, &valFloat) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckR(parMonId) != MON_BELOW)
      return 0;

  valFloat = upperLimFloat + 0.1;
  if (setDpValue(DpIdlastEvtTime, &valFloat) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckR(parMonId) != MON_ABOVE)
      return 0;

  /* ------------------------------------------------------------- */
  /* Verify check for data item of double type */
  /* Definition of parameter monitor */
  CrPsMonConfigInitParMon(parMonId, DpIddummyDouble, MON_PR_OOL_R, 0, 0, 0, 0, 0,
          (CrPsThirtytwoBit_t*)&lowerLimFloat, 0, (CrPsThirtytwoBit_t*)&upperLimFloat, 0);

  /* Verify check for real-valued data item */
  valDouble = 1.6;
  if (setDpValue(DpIddummyDouble, &valDouble) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckR(parMonId) != MON_VALID)
      return 0;

  valDouble = lowerLimFloat - 0.2;
  if (setDpValue(DpIddummyDouble, &valDouble) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckR(parMonId) != MON_BELOW)
      return 0;

  valDouble = upperLimFloat + 0.2;
  if (setDpValue(DpIddummyDouble, &valDouble) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckR(parMonId) != MON_ABOVE)
      return 0;


  /* ------------------------------------------------------------- */
  /* Verify check for 32-bit integer data item */
  lowerLimInt = -4;
  upperLimInt = 20;
  CrPsMonConfigInitParMon(parMonId, DpIddummy32Bit, MON_PR_OOL_SI, 0, 0, 0, 0, 0,
          (CrPsThirtytwoBit_t*)&lowerLimInt, 0, (CrPsThirtytwoBit_t*)&upperLimInt, 0);

  valInt = 13;
  if (setDpValue(DpIddummy32Bit, &valInt) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckSI(parMonId) != MON_VALID)
      return 0;

  valInt = lowerLimInt - 1;
  if (setDpValue(DpIddummy32Bit, &valInt) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckSI(parMonId) != MON_BELOW)
      return 0;

  valInt = upperLimInt + 1;
  if (setDpValue(DpIddummy32Bit, &valInt) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckSI(parMonId) != MON_ABOVE)
      return 0;

  /* ------------------------------------------------------------- */
  /* Verify check for 16-bit integer data item */
  CrPsMonConfigInitParMon(parMonId, DpIddummy16Bit, MON_PR_OOL_SI, 0, 0, 0, 0, 0,
          (CrPsThirtytwoBit_t*)&lowerLimInt, 0, (CrPsThirtytwoBit_t*)&upperLimInt, 0);

  valShort = 13;
  if (setDpValue(DpIddummy16Bit, &valShort) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckSI(parMonId) != MON_VALID)
      return 0;

  valShort = (short)(lowerLimInt - 1);
  if (setDpValue(DpIddummy16Bit, &valShort) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckSI(parMonId) != MON_BELOW)
      return 0;

  valShort = (short)(upperLimInt + 1);
  if (setDpValue(DpIddummy16Bit, &valShort) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckSI(parMonId) != MON_ABOVE)
      return 0;

  /* ------------------------------------------------------------- */
  /* Verify check for 8-bit integer data item */
  CrPsMonConfigInitParMon(parMonId, DpIddummy8Bit, MON_PR_OOL_SI, 0, 0, 0, 0, 0,
          (CrPsThirtytwoBit_t*)&lowerLimInt, 0, (CrPsThirtytwoBit_t*)&upperLimInt, 0);

  valChar = 13;
  if (setDpValue(DpIddummy8Bit, &valChar) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckSI(parMonId) != MON_VALID)
      return 0;

  valChar = (char)(lowerLimInt - 1);
  if (setDpValue(DpIddummy8Bit, &valChar) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckSI(parMonId) != MON_BELOW)
      return 0;

  valChar = (char)(upperLimInt + 1);
  if (setDpValue(DpIddummy8Bit, &valChar) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckSI(parMonId) != MON_ABOVE)
      return 0;

  /* ------------------------------------------------------------- */
  /* Verify check for 32-bit unsigned integer data item */
  lowerLimUInt = 120;
  upperLimUInt = 140;
  CrPsMonConfigInitParMon(parMonId, DpIddummy32Bit, MON_PR_OOL_UI, 0, 0, 0, 0, 0,
          (CrPsThirtytwoBit_t*)&lowerLimUInt, 0, (CrPsThirtytwoBit_t*)&upperLimUInt, 0);

  valUInt = 128;
  if (setDpValue(DpIddummy32Bit, &valUInt) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckUI(parMonId) != MON_VALID)
      return 0;

  valUInt = (unsigned int)(lowerLimUInt - 1);
  if (setDpValue(DpIddummy32Bit, &valUInt) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckUI(parMonId) != MON_BELOW)
      return 0;

  valUInt = (unsigned int)(upperLimUInt + 1);
  if (setDpValue(DpIddummy32Bit, &valUInt) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckUI(parMonId) != MON_ABOVE)
      return 0;

  /* ------------------------------------------------------------- */
  /* Verify check for 16-bit unsigned integer data item */
  CrPsMonConfigInitParMon(parMonId, DpIddummy16Bit, MON_PR_OOL_UI, 0, 0, 0, 0, 0,
          (CrPsThirtytwoBit_t*)&lowerLimUInt, 0, (CrPsThirtytwoBit_t*)&upperLimUInt, 0);

  valUShort = 128;
  if (setDpValue(DpIddummy16Bit, &valUShort) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckUI(parMonId) != MON_VALID)
      return 0;

  valUShort = (unsigned short)(lowerLimUInt - 1);
  if (setDpValue(DpIddummy16Bit, &valUShort) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckUI(parMonId) != MON_BELOW)
      return 0;

  valUShort = (unsigned short)(upperLimUInt + 1);
  if (setDpValue(DpIddummy16Bit, &valUShort) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckUI(parMonId) != MON_ABOVE)
      return 0;

  /* ------------------------------------------------------------- */
  /* Verify check for 8-bit unsigned integer data item */
  CrPsMonConfigInitParMon(parMonId, DpIddummy8Bit, MON_PR_OOL_UI, 0, 0, 0, 0, 0,
          (CrPsThirtytwoBit_t*)&lowerLimUInt, 0, (CrPsThirtytwoBit_t*)&upperLimUInt, 0);

  valUChar = 128;
  if (setDpValue(DpIddummy8Bit, &valUChar) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckUI(parMonId) != MON_VALID)
      return 0;

  valUChar = (unsigned char)(lowerLimUInt - 1);
  if (setDpValue(DpIddummy8Bit, &valUChar) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckUI(parMonId) != MON_BELOW)
      return 0;

  valUChar = (unsigned char)(upperLimUInt + 1);
  if (setDpValue(DpIddummy8Bit, &valUChar) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckUI(parMonId) != MON_ABOVE)
      return 0;

  /* ------------------------------------------------------------- */
  /* Verify expected value check for 32-bit unsigned integer data item */
  expVal = 6;
  expValMask = 6;
  CrPsMonConfigInitParMon(parMonId, DpIddummy32Bit, MON_PR_EXP, 0, 0, 0, 0, 0,
          (CrPsThirtytwoBit_t*)&expValMask, 0, (CrPsThirtytwoBit_t*)&expVal, 0);

  valUInt = 15;
  if (setDpValue(DpIddummy32Bit, &valUInt) == 0)
      return 0;
  if (CrPsMonConfigExpValCheck(parMonId) != MON_VALID)
      return 0;

  valUInt = 8;
  if (setDpValue(DpIddummy32Bit, &valUInt) == 0)
      return 0;
  if (CrPsMonConfigExpValCheck(parMonId) != MON_NOT_EXP)
      return 0;

  /* ------------------------------------------------------------- */
  /* Verify expected value check for 16-bit unsigned integer data item */
  CrPsMonConfigInitParMon(parMonId, DpIddummy16Bit, MON_PR_EXP, 0, 0, 0, 0, 0,
          (CrPsThirtytwoBit_t*)&expValMask, 0, (CrPsThirtytwoBit_t*)&expVal, 0);

  valUShort = 15;
  if (setDpValue(DpIddummy16Bit, &valUShort) == 0)
      return 0;
  if (CrPsMonConfigExpValCheck(parMonId) != MON_VALID)
      return 0;

  valUShort = 8;
  if (setDpValue(DpIddummy16Bit, &valUShort) == 0)
      return 0;
  if (CrPsMonConfigExpValCheck(parMonId) != MON_NOT_EXP)
      return 0;

  /* ------------------------------------------------------------- */
  /* Verify expected value check for 8-bit unsigned integer data item */
  CrPsMonConfigInitParMon(parMonId, DpIddummy8Bit, MON_PR_EXP, 0, 0, 0, 0, 0,
          (CrPsThirtytwoBit_t*)&expValMask, 0, (CrPsThirtytwoBit_t*)&expVal, 0);

  valUChar = 15;
  if (setDpValue(DpIddummy8Bit, &valUChar) == 0)
      return 0;
  if (CrPsMonConfigExpValCheck(parMonId) != MON_VALID)
      return 0;

  valUChar = 16;
  if (setDpValue(DpIddummy8Bit, &valUChar) == 0)
      return 0;
  if (CrPsMonConfigExpValCheck(parMonId) != MON_NOT_EXP)
      return 0;

  return 1;
}

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsMonTestCase2() {
  FwSmDesc_t inCmd12s15, inCmd12s16;
  FwSmDesc_t outManager = CrFwOutManagerMake(0);
  CrFwDestSrc_t src = 12;
  CrFwOutFactoryPoolIndex_t nOfOutCmp;

  /* Reset the framework components and the PMDL */
  CrPsTestUtilitiesResetFw();
  CrPsMonConfigInitPMDL();

  /* ----------------------------- step 1 ------------------------------------------- */
  /* Create and execute a (12,15) command */
  inCmd12s15 = CrPsMonTestCaseMake12s15(src);
  nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
  CrFwCmpExecute(inCmd12s15);
  CrFwInCmdTerminate(inCmd12s15);

  /* Check that the InCommand is in terminated state and 2 service 1 reports were generated (successful start and term) */
  if (!CrFwInCmdIsInTerminated(inCmd12s15))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 2)
    return 0;

  /* Check enable state of service 12 and of Parameter Monitor Procedure */
  if (getDpMonParMonFuncEnbStatus() == DISABLED)
      return 0;
  if (FwPrIsStarted(CrPsConfigGetParMonPr()) != 1)
      return 0;
  if (getDpMonServUser() != src)
      return 0;

  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd12s15);

  /* ----------------------------- step 2 ------------------------------------------- */
  /* Create and execute a second (12,15) command */
  inCmd12s15 = CrPsMonTestCaseMake12s15(src);
  nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
  CrFwCmpExecute(inCmd12s15);
  CrFwInCmdTerminate(inCmd12s15);

  /* Check that the InCommand is in aborted state and 1 service 1 reports was generated (failed start) */
  if (!CrFwInCmdIsInAborted(inCmd12s15))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 1)
    return 0;

  /* Check enable state of service 12 and of Parameter Monitor Procedure */
  if (getDpMonParMonFuncEnbStatus() == DISABLED)
      return 0;

  if (FwPrIsStarted(CrPsConfigGetParMonPr()) != 1)
      return 0;

  /* Verify the content of the (1,4) report */
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,2,4,VER_MON_ENB,0) != 1)
      return 0;

  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd12s15);

  /* ----------------------------- step 3 ------------------------------------------- */
  /* Create and execute a (12,16) command */
  inCmd12s16 = CrPsMonTestCaseMake12s16();
  nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
  CrFwCmpExecute(inCmd12s16);
  CrFwInCmdTerminate(inCmd12s16);

  /* Check that the InCommand is in terminated state and 2 service 1 reports were generated (successful start and term) */
  if (!CrFwInCmdIsInTerminated(inCmd12s16))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 2)
    return 0;

  /* Check enable state of service 12 and of Parameter Monitor Procedure */
  if (getDpMonParMonFuncEnbStatus() != DISABLED)
      return 0;
  if (FwPrIsStarted(CrPsConfigGetParMonPr()) != 0)
      return 0;

  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd12s16);

  /* ----------------------------- step 4 ------------------------------------------- */
  /* Create and execute a second (12,16) command */
  inCmd12s16 = CrPsMonTestCaseMake12s16(src);
  nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
  CrFwCmpExecute(inCmd12s16);
  CrFwInCmdTerminate(inCmd12s16);

  /* Check that the InCommand is in aborted state and 1 service 1 reports was generated (failed start) */
  if (!CrFwInCmdIsInAborted(inCmd12s16))
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 1)
    return 0;

  /* Check enable state of service 12 and of Parameter Monitor Procedure */
  if (getDpMonParMonFuncEnbStatus() != DISABLED)
      return 0;
  if (FwPrIsStarted(CrPsConfigGetParMonPr()) != 0)
      return 0;

  /* Verify the content of the (1,4) report */
  if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,5,4,VER_MON_DIS,0) != 1)
      return 0;

  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd12s16);

  /* ---------------------------------- clean-up --------------------------------------- */

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

/* --------------------------------------------------------------------------- */
CrFwBool_t CrPsMonTestCase3() {
    CrPsNParMon_t NParMon = 2;
    CrPsParMonId_t parMonId[2] = {1, 2};
    CrPsParId_t parId[2] = {DpIddummy16Bit, DpIddummy32Bit};
    CrPsMonPer_t per[2] = {1, 1};
    CrPsMonPer_t repNmb[2] = {1, 1};
    CrPsParId_t valDataItemId[2] = {0, 0};
    CrPsEvtId_t lim1Eid[2] = {0, 0};
    CrPsEvtId_t lim2Eid[2] = {0, 0};
    FwSmDesc_t inCmd12s5;
    FwSmDesc_t outManager = CrFwOutManagerMake(0);
    int nOfOutCmp;

    /* Reset the framework components */
    CrPsTestUtilitiesResetFw();

    /* -------------------------------------- step 1 -------------------------- */
    /* Simulate a full PMDL */
    setDpMonNmbAvailParMon(0);

    /* Instantiate (12,5) command and execute it once */
    inCmd12s5 = CrPsMonTestCaseMake12s5(1, parMonId, parId, per, repNmb, valDataItemId, LIM_CHECK, lim1Eid, lim2Eid);
    nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
    CrFwCmpExecute(inCmd12s5);
    CrFwInCmdTerminate(inCmd12s5);

    /* Check that the InCommand is in ABORTED state and one (1,3), (1,6) and (1,8) report was generated */
    if (!CrFwInCmdIsInAborted(inCmd12s5))
      return 0;
    if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 3)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,1,6,VER_PMDL_FULL,parMonId[0]) != 1)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,2,8,VER_MI_S12_FD,0) != 1)
      return 0;

    /*Release the InCommand */
    CrFwInFactoryReleaseInCmd(inCmd12s5);

    /* Reset the framework components */
    CrPsTestUtilitiesResetFw();

    /* -------------------------------------- step 2 -------------------------- */
    /* Simulate an empty PMDL */
    setDpMonNmbAvailParMon(MON_N_PMON);

    /* Instantiate (12,5) with invalid PMON identifiers */
    parMonId[0] = 0;
    parMonId[1] = MON_N_PMON+1;
    inCmd12s5 = CrPsMonTestCaseMake12s5(2, parMonId, parId, per, repNmb, valDataItemId, LIM_CHECK, lim1Eid, lim2Eid);
    nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
    CrFwCmpExecute(inCmd12s5);
    CrFwInCmdTerminate(inCmd12s5);

    /* Check that the InCommand is in PROGRESS state and one (1,3) and one (1,6) report was generated */
    if (!CrFwInCmdIsInProgress(inCmd12s5))
      return 0;
    if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 2)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,1,6,VER_ILL_MON,parMonId[0]) != 1)
      return 0;

    /* Execute it again and check it goes into ABORTED */
    CrFwCmpExecute(inCmd12s5);
    CrFwInCmdTerminate(inCmd12s5);
    if (!CrFwInCmdIsInAborted(inCmd12s5))
      return 0;
    if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 4)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,2,6,VER_ILL_MON,parMonId[1]) != 1)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,3,8,VER_MI_S12_FD,0) != 1)
      return 0;

    /*Release the InCommand */
    CrFwInFactoryReleaseInCmd(inCmd12s5);

    /* Reset the framework components */
    CrPsTestUtilitiesResetFw();

    /* -------------------------------------- step 3 -------------------------- */
    /* Instantiate (12,5) with invalid identifiers of monitored parameters */
    parMonId[0] = 1;
    parMonId[1] = MON_N_PMON;
    parId[0] = 0;
    parId[1] = DpIdVarsHighest+1;
    inCmd12s5 = CrPsMonTestCaseMake12s5(2, parMonId, parId, per, repNmb, valDataItemId, LIM_CHECK, lim1Eid, lim2Eid);
    nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
    CrFwCmpExecute(inCmd12s5);
    CrFwInCmdTerminate(inCmd12s5);

    /* Check that the InCommand is in PROGRESS state and one (1,3) and one (1,6) report was generated */
    if (!CrFwInCmdIsInProgress(inCmd12s5))
      return 0;
    if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 2)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,1,6,VER_MON_ILL_DI,parMonId[0]) != 1)
      return 0;

    /* Execute it again and check it goes into ABORTED */
    CrFwCmpExecute(inCmd12s5);
    CrFwInCmdTerminate(inCmd12s5);
    if (!CrFwInCmdIsInAborted(inCmd12s5))
      return 0;
    if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 4)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,2,6,VER_MON_ILL_DI,parMonId[1]) != 1)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,3,8,VER_MI_S12_FD,0) != 1)
      return 0;

    /*Release the InCommand */
    CrFwInFactoryReleaseInCmd(inCmd12s5);

    /* Reset the framework components */
    CrPsTestUtilitiesResetFw();

    /* -------------------------------------- step 4 -------------------------- */
    /* Instantiate (12,5) with invalid identifiers of validity parameters */
    parMonId[0] = 1;
    parMonId[1] = MON_N_PMON;
    parId[0] = 1;
    parId[1] = DpIdVarsHighest;
    valDataItemId[0] = DpIdParamsLowest-1;
    valDataItemId[1] = DpIdVarsHighest+1;
    inCmd12s5 = CrPsMonTestCaseMake12s5(2, parMonId, parId, per, repNmb, valDataItemId, LIM_CHECK, lim1Eid, lim2Eid);
    nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
    CrFwCmpExecute(inCmd12s5);
    CrFwInCmdTerminate(inCmd12s5);

    /* Check that the InCommand is in PROGRESS state and one (1,3) and one (1,6) report was generated */
    if (!CrFwInCmdIsInProgress(inCmd12s5))
      return 0;
    if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 2)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,1,6,VER_ILL_VAL_DI,parMonId[0]) != 1)
      return 0;

    /* Execute it again and check it goes into ABORTED */
    CrFwCmpExecute(inCmd12s5);
    CrFwInCmdTerminate(inCmd12s5);
    if (!CrFwInCmdIsInAborted(inCmd12s5))
      return 0;
    if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 4)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,2,6,VER_ILL_VAL_DI,parMonId[1]) != 1)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,3,8,VER_MI_S12_FD,0) != 1)
      return 0;

    /*Release the InCommand */
    CrFwInFactoryReleaseInCmd(inCmd12s5);

    /* Reset the framework components */
    CrPsTestUtilitiesResetFw();

    /* -------------------------------------- step 5 -------------------------- */
    /* Instantiate (12,5) with invalid parameter monitor identifier */
    parMonId[0] = 1;
    parMonId[1] = MON_N_PMON;
    parId[0] = 1;
    parId[1] = DpIdVarsHighest;
    valDataItemId[0] = DpIdParamsLowest;
    valDataItemId[1] = DpIdVarsHighest+1;
    inCmd12s5 = CrPsMonTestCaseMake12s5(2, parMonId, parId, per, repNmb, valDataItemId, DEL_CHECK, lim1Eid, lim2Eid);
    nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
    CrFwCmpExecute(inCmd12s5);
    CrFwInCmdTerminate(inCmd12s5);

    /* Check that the InCommand is in PROGRESS state and one (1,3) and one (1,6) report was generated */
    if (!CrFwInCmdIsInProgress(inCmd12s5))
      return 0;
    if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 2)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,1,6,VER_MON_ILL_PR,parMonId[0]) != 1)
      return 0;

    /* Execute it again and check it goes into ABORTED */
    CrFwCmpExecute(inCmd12s5);
    CrFwInCmdTerminate(inCmd12s5);
    if (!CrFwInCmdIsInAborted(inCmd12s5))
      return 0;
    if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 4)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,2,6,VER_MON_ILL_PR,parMonId[1]) != 1)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,3,8,VER_MI_S12_FD,0) != 1)
      return 0;

    /*Release the InCommand */
    CrFwInFactoryReleaseInCmd(inCmd12s5);

    /* Reset the framework components */
    CrPsTestUtilitiesResetFw();

    /* Verify that the PMDL is still empty */
    if (getDpMonNmbAvailParMon() != MON_N_PMON)
      return 0;

  return 1;
}

/* --------------------------------------------------------------------------- */
CrFwBool_t CrPsMonTestCase4() {
    CrPsParMonId_t parMonId[2] = {1, 2};
    CrPsParId_t parId[2] = {DpIddummy16Bit, DpIddummy32Bit};
    CrPsMonPer_t per[2] = {1, 1};
    CrPsMonPer_t repNmb[2] = {1, 1};
    CrPsParId_t valDataItemId[2] = {0, 0};
    CrPsEvtId_t lim1Eid[2] = {0, 0};
    CrPsEvtId_t lim2Eid[2] = {0, 0};
    FwSmDesc_t inCmd12s5, inCmd12s6;
    FwSmDesc_t outManager = CrFwOutManagerMake(0);
    int nOfOutCmp;

    /* Reset the framework components */
    CrPsTestUtilitiesResetFw();

    /* Simulate an empty PMDL */
    setDpMonNmbAvailParMon(MON_N_PMON);

    /* -------------------------------------- step 1 -------------------------- */
    /* Instantiate the (12,5) command and execute it once */
    inCmd12s5 = CrPsMonTestCaseMake12s5(1, parMonId, parId, per, repNmb, valDataItemId, LIM_CHECK, lim1Eid, lim2Eid);
    nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
    CrFwCmpExecute(inCmd12s5);
    CrFwInCmdTerminate(inCmd12s5);

    /* Check that the InCommand is in TERMINATED state and one (1,3), (1,5) and (1,7) report was generated */
    if (!CrFwInCmdIsInTerminated(inCmd12s5))
      return 0;
    if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 3)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,0,3,0,0) != 1)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,1,5,0,0) != 1)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,2,7,0,0) != 1)
      return 0;

    /* Verify that 1 PMON is now allocated */
    if (getDpMonNmbAvailParMon() != MON_N_PMON-1)
      return 0;

    /* Reset the framework components */
    CrPsTestUtilitiesResetFw();

    /* -------------------------------------- step 2 -------------------------- */
    /* Instantiate the (12,6) command and execute it once */
    inCmd12s6 = CrPsMonTestCaseMake12s6(1, parMonId);
    nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
    CrFwCmpExecute(inCmd12s6);
    CrFwInCmdTerminate(inCmd12s6);

    /* Check that the InCommand is in TERMINATED state and one (1,3), (1,5) and (1,7) report was generated */
    if (!CrFwInCmdIsInTerminated(inCmd12s6))
      return 0;
    if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 3)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,0,3,0,0) != 1)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,1,5,0,0) != 1)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,2,7,0,0) != 1)
      return 0;

    /* Verify that 1 PMON is now allocated */
    if (getDpMonNmbAvailParMon() != MON_N_PMON)
      return 0;

    /*Release the InCommand */
    CrFwInFactoryReleaseInCmd(inCmd12s5);

    /* Reset the framework components */
    CrPsTestUtilitiesResetFw();

   return 1;
}

/* --------------------------------------------------------------------------- */
CrFwBool_t CrPsMonTestCase5() {
    CrPsParMonId_t parMonId[2] = {1, 2};
    CrPsParMonId_t parMonIdDel[4] = {2, 0, MON_N_PMON+1, 1};
    CrPsParId_t parId[2] = {DpIddummy16Bit, DpIddummy32Bit};
    CrPsMonPer_t per[2] = {1, 1};
    CrPsMonPer_t repNmb[2] = {1, 1};
    CrPsParId_t valDataItemId[2] = {0, 0};
    CrPsEvtId_t lim1Eid[2] = {0, 0};
    CrPsEvtId_t lim2Eid[2] = {0, 0};
    FwSmDesc_t inCmd12s5, inCmd12s6;
    FwSmDesc_t outManager = CrFwOutManagerMake(0);
    int nOfOutCmp;

    /* Reset the framework components */
    CrPsTestUtilitiesResetFw();

    /* Simulate an empty PMDL */
    setDpMonNmbAvailParMon(MON_N_PMON);

    /* -------------------------------------- step 1 -------------------------- */
    /* Instantiate the (12,5) command and execute it once */
    inCmd12s5 = CrPsMonTestCaseMake12s5(1, parMonId, parId, per, repNmb, valDataItemId, LIM_CHECK, lim1Eid, lim2Eid);
    nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
    CrFwCmpExecute(inCmd12s5);
    CrFwInCmdTerminate(inCmd12s5);

    /* Enable the newly created PMON */
    setDpMonParMonEnbStatusItem(parMonId[0], ENABLED);

    /* Check that the InCommand is in TERMINATED state and one (1,3), (1,5) and (1,7) report was generated */
    if (!CrFwInCmdIsInTerminated(inCmd12s5))
      return 0;
    if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 3)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,0,3,0,0) != 1)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,1,5,0,0) != 1)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,2,7,0,0) != 1)
      return 0;

    /* Verify that 1 PMON is now allocated */
    if (getDpMonNmbAvailParMon() != MON_N_PMON-1)
      return 0;

    /* Reset the framework components */
    CrPsTestUtilitiesResetFw();

    /* -------------------------------------- step 1 -------------------------- */
    /* Instantiate the (12,6) command and execute it four times */
    inCmd12s6 = CrPsMonTestCaseMake12s6(4, parMonIdDel);
    nOfOutCmp = CrFwOutFactoryGetNOfAllocatedOutCmp();
    CrFwCmpExecute(inCmd12s6);
    CrFwInCmdTerminate(inCmd12s6);
    CrFwCmpExecute(inCmd12s6);
    CrFwInCmdTerminate(inCmd12s6);
    CrFwCmpExecute(inCmd12s6);
    CrFwInCmdTerminate(inCmd12s6);
    CrFwCmpExecute(inCmd12s6);
    CrFwInCmdTerminate(inCmd12s6);

    /* Check that InCommand is in ABORTED state and one (1,3), four (1,6) and one (1,8) reports were generated */
    if (!CrFwInCmdIsInAborted(inCmd12s6))
      return 0;
    if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nOfOutCmp + 6)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,0,3,0,0) != 1)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,1,6,VER_ILL_MON,parMonIdDel[0]) != 1)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,2,6,VER_ILL_MON,parMonIdDel[1]) != 1)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,3,6,VER_ILL_MON,parMonIdDel[2]) != 1)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,4,6,VER_MON_ENB,parMonIdDel[3]) != 1)
      return 0;
    if (CrPsTestUtilitiesCheckOutManagerCmdRejRep(outManager,5,8,VER_MI_S12_FD,0) != 1)
      return 0;

    /* Verify that 1 PMON is still allocated */
    if (getDpMonNmbAvailParMon() != MON_N_PMON-1)
      return 0;

    /*Release the InCommand */
    CrFwInFactoryReleaseInCmd(inCmd12s5);

    /* Reset the framework components and the monitoring service*/
    CrPsTestUtilitiesResetFw();
    CrPsMonConfigInit();

   return 1;
}




/* --------------------------------------------------------------------------- */
FwSmDesc_t CrPsMonTestCaseMake12s6(CrPsNParMon_t NParMon, CrPsParMonId_t* parMonId) {
    CrFwPckt_t pckt;
    CrFwCrc_t crc;
    int i;

    pckt = CrFwPcktMake(CR_FW_MAX_PCKT_LENGTH);
    CrFwPcktSetCmdRepType(pckt,crCmdType);
    CrFwPcktSetServType(pckt,MON_TYPE);
    CrFwPcktSetServSubType(pckt,MONDELPARMONDEFCMD_STYPE);
    CrFwPcktSetSrc(pckt,0);
    CrFwPcktSetDest(pckt,0);
    CrFwPcktSetGroup(pckt,1);
    CrFwPcktSetAckLevel(pckt,1,1,1,1);
    CrFwPcktSetSeqCnt(pckt,1);
    setMonDelParMonDefCmdNParMon(pckt, NParMon);

    for (i=0; i<NParMon; i++)
        setMonDelParMonDefCmdParMonId(pckt, i, parMonId[i]);

    crc = CrFwPcktComputeCrc(pckt);
    CrFwPcktSetCrc(pckt, crc);

    return CrFwInFactoryMakeInCmd(pckt);
}

/* --------------------------------------------------------------------------- */
FwSmDesc_t CrPsMonTestCaseMake12s5(CrPsNParMon_t NParMon, CrPsParMonId_t* parMonId, CrPsParId_t* parId,
        CrPsMonPer_t* per, CrPsMonPer_t* repNmb, CrPsParId_t* valDataItemId, CrPsMonCheckType_t CheckType,
        CrPsEvtId_t* lim1Eid, CrPsEvtId_t* lim2Eid) {
    CrFwPckt_t pckt;
    CrFwCrc_t crc;
    int i;

    pckt = CrFwPcktMake(CR_FW_MAX_PCKT_LENGTH);
    CrFwPcktSetCmdRepType(pckt,crCmdType);
    CrFwPcktSetServType(pckt,MON_TYPE);
    CrFwPcktSetServSubType(pckt,MONADDPARMONDEFCMD_STYPE);
    CrFwPcktSetSrc(pckt,0);
    CrFwPcktSetDest(pckt,0);
    CrFwPcktSetGroup(pckt,1);
    CrFwPcktSetAckLevel(pckt,1,1,1,1);
    CrFwPcktSetSeqCnt(pckt,1);
    setMonAddParMonDefCmdNParMon(pckt, NParMon);
    for (i=0; i<NParMon; i++) {
        setMonAddParMonDefCmdParMonId(pckt, i, parMonId[i]);
        setMonAddParMonDefCmdMonParId(pckt, i, parId[i]);
        setMonAddParMonDefCmdValCheckParId(pckt, i, valDataItemId[i]);
        setMonAddParMonDefCmdValCheckParMask(pckt, i, 1);
        setMonAddParMonDefCmdValCheckExpVal(pckt, i, 1);
        setMonAddParMonDefCmdMonPer(pckt, i, per[i]);
        setMonAddParMonDefCmdRepNmb(pckt, i, repNmb[i]);
        setMonAddParMonDefCmdCheckType(pckt, i, CheckType);
        setMonAddParMonDefCmdCheckTypeData1(pckt, i, MON_TEST_CASE_LIM1);
        setMonAddParMonDefCmdCheckTypeData1(pckt, i, lim1Eid[i]);
        setMonAddParMonDefCmdCheckTypeData3(pckt, i, MON_TEST_CASE_LIM2);
        setMonAddParMonDefCmdCheckTypeData1(pckt, i, lim2Eid[i]);
    }

    crc = CrFwPcktComputeCrc(pckt);
    CrFwPcktSetCrc(pckt, crc);

    return CrFwInFactoryMakeInCmd(pckt);
}

/* --------------------------------------------------------------------------- */
FwSmDesc_t CrPsMonTestCaseMake12s15(CrFwDestSrc_t cmdSrc) {
    CrFwPckt_t pckt;
    CrFwCrc_t crc;

    pckt = CrFwPcktMake(LEN_MON_ENBPARMONFUNCCMD);
    CrFwPcktSetCmdRepType(pckt,crCmdType);
    CrFwPcktSetServType(pckt,MON_TYPE);
    CrFwPcktSetServSubType(pckt,MONENBPARMONFUNCCMD_STYPE);
    CrFwPcktSetSrc(pckt,cmdSrc);
    CrFwPcktSetDest(pckt,0);
    CrFwPcktSetGroup(pckt,1);
    CrFwPcktSetAckLevel(pckt,1,1,1,1);
    CrFwPcktSetSeqCnt(pckt,1);
    crc = CrFwPcktComputeCrc(pckt);
    CrFwPcktSetCrc(pckt, crc);

    return CrFwInFactoryMakeInCmd(pckt);
}

/* --------------------------------------------------------------------------- */
FwSmDesc_t CrPsMonTestCaseMake12s16() {
    CrFwPckt_t pckt;
    CrFwCrc_t crc;

    pckt = CrFwPcktMake(LEN_MON_DISPARMONFUNCCMD);
    CrFwPcktSetCmdRepType(pckt,crCmdType);
    CrFwPcktSetServType(pckt,MON_TYPE);
    CrFwPcktSetServSubType(pckt,MONDISPARMONFUNCCMD_STYPE);
    CrFwPcktSetSrc(pckt,0);
    CrFwPcktSetDest(pckt,0);
    CrFwPcktSetGroup(pckt,1);
    CrFwPcktSetAckLevel(pckt,1,1,1,1);
    CrFwPcktSetSeqCnt(pckt,1);
    crc = CrFwPcktComputeCrc(pckt);
    CrFwPcktSetCrc(pckt, crc);

    return CrFwInFactoryMakeInCmd(pckt);
}
