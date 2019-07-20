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
  int lowerLimInt, upperLimInt, expVal, valInt;
  unsigned int lowerLimUInt, upperLimUInt, expValUI, valUInt;
  short valShort;
  char valChar;
  unsigned short valUShort;
  unsigned char valUChar;
  CrPsThirtytwoBit_t* lowerLimRaw;
  CrPsThirtytwoBit_t* upperLimRaw;
  CrPsThirtytwoBit_t* expValRaw;
  CrPsParMonId_t parMonId = 1;

  /* Call the initialization function of the monitoring service */
  CrPsMonConfigInit();

  /* The monitor procedure for float values is verified on variable DpIdlastEvtTime */
  lowerLimFloat = 1.3;
  upperLimFloat = 1.7;
  lowerLimRaw = (CrPsThirtytwoBit_t*)&lowerLimFloat;
  upperLimRaw = (CrPsThirtytwoBit_t*)&upperLimFloat;
  setDpMonLowerLimitItem(parMonId, *lowerLimRaw);
  setDpMonUpperLimitItem(parMonId, *upperLimRaw);

  /* Definition of parameter monitor */
  CrPsMonTestCaseInitParMon(parMonId, DpIdlastEvtTime, NULL, 0, 0, 0, 0, 0, 0);

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
  CrPsMonTestCaseInitParMon(parMonId, DpIddummyDouble, NULL, 0, 0, 0, 0, 0, 0);

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
  CrPsMonTestCaseInitParMon(parMonId, DpIddummy32Bit, NULL, 0, 0, 0, 0, 0, 0);
  lowerLimInt = -4;
  upperLimInt = 20;
  lowerLimRaw = (CrPsThirtytwoBit_t*)&lowerLimInt;
  upperLimRaw = (CrPsThirtytwoBit_t*)&upperLimInt;
  setDpMonLowerLimitItem(parMonId, *lowerLimRaw);
  setDpMonUpperLimitItem(parMonId, *upperLimRaw);

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
  CrPsMonTestCaseInitParMon(parMonId, DpIddummy16Bit, NULL, 0, 0, 0, 0, 0, 0);

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
  CrPsMonTestCaseInitParMon(parMonId, DpIddummy8Bit, NULL, 0, 0, 0, 0, 0, 0);

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
  CrPsMonTestCaseInitParMon(parMonId, DpIddummy32Bit, NULL, 0, 0, 0, 0, 0, 0);
  lowerLimUInt = 120;
  upperLimUInt = 140;
  lowerLimRaw = (CrPsThirtytwoBit_t*)&lowerLimUInt;
  upperLimRaw = (CrPsThirtytwoBit_t*)&upperLimUInt;
  setDpMonLowerLimitItem(parMonId, *lowerLimRaw);
  setDpMonUpperLimitItem(parMonId, *upperLimRaw);

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
  CrPsMonTestCaseInitParMon(parMonId, DpIddummy16Bit, NULL, 0, 0, 0, 0, 0, 0);

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
  CrPsMonTestCaseInitParMon(parMonId, DpIddummy8Bit, NULL, 0, 0, 0, 0, 0, 0);

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
  CrPsMonTestCaseInitParMon(parMonId, DpIddummy32Bit, NULL, 0, 0, 0, 0, 0, 0);
  expValUI = 35;
  expValRaw = (CrPsThirtytwoBit_t*)&expValUI;
  setDpMonExpValueItem(parMonId, *expValRaw);

  valUInt = 35;
  if (setDpValue(DpIddummy32Bit, &valUInt) == 0)
      return 0;
  if (CrPsMonConfigExpValCheckUI(parMonId) != MON_VALID)
      return 0;

  valUInt = valUInt + 1;
  if (setDpValue(DpIddummy32Bit, &valUInt) == 0)
      return 0;
  if (CrPsMonConfigExpValCheckUI(parMonId) != MON_NOT_EXP)
      return 0;

  /* ------------------------------------------------------------- */
  /* Verify expected value check for 16-bit unsigned integer data item */
  CrPsMonTestCaseInitParMon(parMonId, DpIddummy16Bit, NULL, 0, 0, 0, 0, 0, 0);
  expValUI = 45;
  expValRaw = (CrPsThirtytwoBit_t*)&expValUI;
  setDpMonExpValueItem(parMonId, *expValRaw);

  valUShort = 45;
  if (setDpValue(DpIddummy16Bit, &valUShort) == 0)
      return 0;
  if (CrPsMonConfigExpValCheckUI(parMonId) != MON_VALID)
      return 0;

  valUShort = valUShort + 1;
  if (setDpValue(DpIddummy16Bit, &valUShort) == 0)
      return 0;
  if (CrPsMonConfigExpValCheckUI(parMonId) != MON_NOT_EXP)
      return 0;

  /* ------------------------------------------------------------- */
  /* Verify expected value check for 8-bit unsigned integer data item */
  CrPsMonTestCaseInitParMon(parMonId, DpIddummy8Bit, NULL, 0, 0, 0, 0, 0, 0);
  expValUI = 55;
  expValRaw = (CrPsThirtytwoBit_t*)&expValUI;
  setDpMonExpValueItem(parMonId, *expValRaw);

  valUChar = 55;
  if (setDpValue(DpIddummy8Bit, &valUChar) == 0)
      return 0;
  if (CrPsMonConfigExpValCheckUI(parMonId) != MON_VALID)
      return 0;

  valUChar = valUChar + 1;
  if (setDpValue(DpIddummy8Bit, &valUChar) == 0)
      return 0;
  if (CrPsMonConfigExpValCheckUI(parMonId) != MON_NOT_EXP)
      return 0;

  /* ------------------------------------------------------------- */
  /* Verify expected value check for 32-bit signed integer data item */
  CrPsMonTestCaseInitParMon(parMonId, DpIddummy32Bit, NULL, 0, 0, 0, 0, 0, 0);
  expVal = 65;
  expValRaw = (CrPsThirtytwoBit_t*)&expVal;
  setDpMonExpValueItem(parMonId, *expValRaw);

  valInt = 65;
  if (setDpValue(DpIddummy32Bit, &valInt) == 0)
      return 0;
  if (CrPsMonConfigExpValCheckSI(parMonId) != MON_VALID)
      return 0;

  valInt = valInt + 1;
  if (setDpValue(DpIddummy32Bit, &valInt) == 0)
      return 0;
  if (CrPsMonConfigExpValCheckSI(parMonId) != MON_NOT_EXP)
      return 0;

  /* ------------------------------------------------------------- */
  /* Verify expected value check for 16-bit signed integer data item */
  CrPsMonTestCaseInitParMon(parMonId, DpIddummy16Bit, NULL, 0, 0, 0, 0, 0, 0);
  expVal = 75;
  expValRaw = (CrPsThirtytwoBit_t*)&expVal;
  setDpMonExpValueItem(parMonId, *expValRaw);

  valShort = 75;
  if (setDpValue(DpIddummy16Bit, &valShort) == 0)
      return 0;
  if (CrPsMonConfigExpValCheckSI(parMonId) != MON_VALID)
      return 0;

  valShort = valShort + 1;
  if (setDpValue(DpIddummy16Bit, &valShort) == 0)
      return 0;
  if (CrPsMonConfigExpValCheckSI(parMonId) != MON_NOT_EXP)
      return 0;

  /* ------------------------------------------------------------- */
  /* Verify expected value check for 8-bit signed integer data item */
  CrPsMonTestCaseInitParMon(parMonId, DpIddummy8Bit, NULL, 0, 0, 0, 0, 0, 0);
  expVal = 85;
  expValRaw = (CrPsThirtytwoBit_t*)&expVal;
  setDpMonExpValueItem(parMonId, *expValRaw);

  valChar = 85;
  if (setDpValue(DpIddummy8Bit, &valChar) == 0)
      return 0;
  if (CrPsMonConfigExpValCheckSI(parMonId) != MON_VALID)
      return 0;

  valChar = valChar + 1;
  if (setDpValue(DpIddummy8Bit, &valChar) == 0)
      return 0;
  if (CrPsMonConfigExpValCheckSI(parMonId) != MON_NOT_EXP)
      return 0;

  return 1;
}

/* --------------------------------------------------------------------------- */
void CrPsMonTestCaseInitParMon(CrPsParMonId_t parMonId, CrPsParId_t parId, CrPsMonPrFnc_t monPrFnc,
        CrPsMonPer_t per, CrPsMonPer_t repNmb, CrPsEvtId_t evtId, CrPsParId_t valDataItemId,
        CrPsValMask_t valExpVal, CrPsValMask_t valMask) {

  dpMonParams.dataItemId[parMonId] = parId;
  dpMonParams.evtId[parMonId] = evtId;
  dpMonParams.per[parMonId] = per;
  dpMonParams.repNmb[parMonId] = repNmb;
  dpMonParams.valDataItemId[parMonId] = valDataItemId;
  dpMonParams.valExpVal[parMonId] = valExpVal;
  dpMonParams.valMask[parMonId] = valMask;
}

