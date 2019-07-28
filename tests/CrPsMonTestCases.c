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
