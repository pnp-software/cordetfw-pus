/**
 * @file
 * @ingroup man_mon
 *
 * Implementation of the configuration interface for the On-Board Monitoring Service.
 *
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 *
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "CrPsMonConfig.h"
#include "CrPsMonFncPr.h"
#include "Pckt/CrPsPcktMon.h"
#include "CrPsTypes.h"
#include "CrPsServTypeId.h"
#include "CrFwUserConstants.h"
#include "CrPsConstants.h"
#include "DataPool/CrPsDp.h"
#include "DataPool/CrPsDpMon.h"

/* Include CORDET Framework Files */
#include "OutCmp/CrFwOutCmp.h"
#include "InCmd/CrFwInCmd.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"

/* Include FW Profile Files */
#include "FwSmConfig.h"

/* Include assert macro */
#include "assert.h"

/** The pointer to the functions implementing the Parameter Monitors */
static CrPsMonPrFnc_t monFncPr[MON_N_PMON] = {NULL};

/** The pointer to the Parameter Monitoring Procedure */
static FwPrDesc_t parMonPr;

/* ----------------------------------------------------------------------------------- */
void CrPsMonConfigInit() {
  parMonPr = CrPsMonFncPrCreate(NULL);
  CrPsMonConfigInitPMDL();
  return;
}

/* ----------------------------------------------------------------------------------- */
FwPrDesc_t CrPsConfigGetParMonPr() {
  return parMonPr;
}

/* ----------------------------------------------------------------------------------- */
void CrPsMonConfigInitPMDL() {
  int i;

  for (i=0; i<MON_N_PMON; i++) {
      setDpMonPerCntItem(i,0);
      setDpMonRepCntItem(i,0);
      setDpMonCheckStatusItem(i,MON_UNCHECKED);
  }
}

/* ----------------------------------------------------------------------------------- */
CrPsParMonCheckStatus_t CrPsMonConfigOutOfLimitCheckR(CrPsParMonId_t parMonId) {
  float lowerLim, upperLim, floatVal;
  double doubleVal;
  size_t size;
  CrPsParId_t parId;
  CrPsThirtytwoBit_t buffer;
  float* bufferFloat = (float*)&buffer;
  unsigned int nElements;

  /* Verify size of float and double types */
  assert(sizeof(float)==4);
  assert(sizeof(double)==8);

  /* Retrieve the monitoring limits */
  buffer = getDpMonLowerLimitItem(parMonId);
  lowerLim = *bufferFloat;
  buffer = getDpMonUpperLimitItem(parMonId);
  upperLim = *bufferFloat;

  /* Retrieve the value of the monitored parameter */
  parId = getDpMonDataItemIdItem(parMonId);
  size = getDpSizeElem(parId);
  if (size == 4) {
      getDpValueEx(parId, &floatVal, &size, &nElements);
      if (floatVal > upperLim)
          return MON_ABOVE;
      if (floatVal < lowerLim)
          return MON_BELOW;
      return MON_VALID;
  }
  if (size == 8) {
      getDpValueEx(parId, &doubleVal, &size, &nElements);
      if (doubleVal > upperLim)
          return MON_ABOVE;
      if (doubleVal < lowerLim)
          return MON_BELOW;
      return MON_VALID;
  }

  CrFwSetAppErrCode(CrPsIllRMonParSize);
  return MON_VALID;
}

/* ----------------------------------------------------------------------------------- */
CrPsParMonCheckStatus_t CrPsMonConfigOutOfLimitCheckSI(CrPsParMonId_t parMonId) {
  int lowerLim, upperLim, intVal;
  short int shortIntVal;
  char charIntVal;
  size_t size;
  CrPsParId_t parId;
  CrPsThirtytwoBit_t buffer;
  int* bufferInt = (int*)&buffer;
  unsigned int nElements;

  /* Verify size of integer types */
  assert(sizeof(int)==4);
  assert(sizeof(short int)==2);
  assert(sizeof(char)==1);

  /* Retrieve the monitoring limits */
  buffer = getDpMonLowerLimitItem(parMonId);
  lowerLim = *bufferInt;
  buffer = getDpMonUpperLimitItem(parMonId);
  upperLim = *bufferInt;

  /* Retrieve the value of the monitored parameter */
  parId = getDpMonDataItemIdItem(parMonId);
  size = getDpSizeElem(parId);
  if (size == 4) {
      getDpValueEx(parId, &intVal, &size, &nElements);
      if (intVal > upperLim)
          return MON_ABOVE;
      if (intVal < lowerLim)
          return MON_BELOW;
      return MON_VALID;
  }
  else if (size == 2) {
      getDpValueEx(parId, &shortIntVal, &size, &nElements);
      if (shortIntVal > upperLim)
          return MON_ABOVE;
      if (shortIntVal < lowerLim)
          return MON_BELOW;
      return MON_VALID;
  }
  else if (size == 1) {
      getDpValueEx(parId, &charIntVal, &size, &nElements);
      if (charIntVal > upperLim)
          return MON_ABOVE;
      if (charIntVal < lowerLim)
          return MON_BELOW;
      return MON_VALID;
  }
  else {
      CrFwSetAppErrCode(CrPsIllSIMonParSize);
      return MON_VALID;
  }
}

/* ----------------------------------------------------------------------------------- */
CrPsParMonCheckStatus_t CrPsMonConfigOutOfLimitCheckUI(CrPsParMonId_t parMonId) {
  unsigned int lowerLim, upperLim, intVal;
  unsigned short int shortIntVal;
  unsigned char charIntVal;
  size_t size;
  CrPsParId_t parId;
  CrPsThirtytwoBit_t buffer;
  unsigned int* bufferInt = (unsigned int*)&buffer;
  unsigned int nElements;

  /* Verify size of integer types */
  assert(sizeof(unsigned int)==4);
  assert(sizeof(unsigned short int)==2);
  assert(sizeof(unsigned char)==1);

  /* Retrieve the monitoring limits */
  buffer = getDpMonLowerLimitItem(parMonId);
  lowerLim = *bufferInt;
  buffer = getDpMonUpperLimitItem(parMonId);
  upperLim = *bufferInt;

  /* Retrieve the value of the monitored parameter */
  parId = getDpMonDataItemIdItem(parMonId);
  size = getDpSizeElem(parId);
  if (size == 4) {
      getDpValueEx(parId, &intVal, &size, &nElements);
      if (intVal > upperLim)
          return MON_ABOVE;
      if (intVal < lowerLim)
          return MON_BELOW;
      return MON_VALID;
  }
  else if (size == 2) {
      getDpValueEx(parId, &shortIntVal, &size, &nElements);
      if (shortIntVal > upperLim)
          return MON_ABOVE;
      if (shortIntVal < lowerLim)
          return MON_BELOW;
      return MON_VALID;
  }
  else if (size == 1) {
      getDpValueEx(parId, &charIntVal, &size, &nElements);
      if (charIntVal > upperLim)
          return MON_ABOVE;
      if (charIntVal < lowerLim)
          return MON_BELOW;
      return MON_VALID;
  }
  else {
      CrFwSetAppErrCode(CrPsIllUIMonParSize);
      return MON_VALID;
  }
}

/* ----------------------------------------------------------------------------------- */
CrPsParMonCheckStatus_t CrPsMonConfigExpValCheckUI(CrPsParMonId_t parMonId) {
    CrPsThirtytwoBit_t buffer;
    unsigned int* bufferInt = (unsigned int*)&buffer;
    unsigned int nElements;
    unsigned int expValue;
    unsigned int intVal;
    unsigned short intShort;
    unsigned char intChar;
    CrPsParId_t parId;
    size_t size;

    /* Verify size of integer types */
    assert(sizeof(unsigned int)==4);
    assert(sizeof(unsigned short int)==2);
    assert(sizeof(unsigned char)==1);

    /* Retrieve the expected value */
    buffer = getDpMonExpValueItem(parMonId);
    expValue = *bufferInt;

    /* Retrieve the value of the monitored parameter */
    parId = getDpMonDataItemIdItem(parMonId);
    size = getDpSizeElem(parId);
    if (size == 4) {
        getDpValueEx(parId, &intVal, &size, &nElements);
        if (intVal != expValue)
            return MON_NOT_EXP;
        else
            return MON_VALID;
    }
    else if (size == 2) {
        getDpValueEx(parId, &intShort, &size, &nElements);
        intVal = (unsigned short)intShort;
        if (intVal != expValue)
            return MON_NOT_EXP;
        else
            return MON_VALID;
    }
    else if (size == 1) {
        getDpValueEx(parId, &intChar, &size, &nElements);
        intVal = (unsigned char)intChar;
        if (intVal != expValue)
            return MON_NOT_EXP;
        else
            return MON_VALID;
    }
    else {
        CrFwSetAppErrCode(CrPsIllUIMonParSize);
        return MON_VALID;
    }
}

/* ----------------------------------------------------------------------------------- */
CrPsParMonCheckStatus_t CrPsMonConfigExpValCheckSI(CrPsParMonId_t parMonId) {
    CrPsThirtytwoBit_t buffer;
    int* bufferInt = (int*)&buffer;
    unsigned int nElements;
    int expValue;
    int intVal;
    short intShort;
    char intChar;
    CrPsParId_t parId;
    size_t size;

    /* Verify size of integer types */
    assert(sizeof(int)==4);
    assert(sizeof(short int)==2);
    assert(sizeof(char)==1);

    /* Retrieve the expected value */
    buffer = getDpMonExpValueItem(parMonId);
    expValue = *bufferInt;

    /* Retrieve the value of the monitored parameter */
    parId = getDpMonDataItemIdItem(parMonId);
    size = getDpSizeElem(parId);
    if (size == 4) {
        getDpValueEx(parId, &intVal, &size, &nElements);
        if (intVal != expValue)
            return MON_NOT_EXP;
        else
            return MON_VALID;
    }
    else if (size == 2) {
        getDpValueEx(parId, &intShort, &size, &nElements);
        intVal = (short)intShort;
        if (intVal != expValue)
            return MON_NOT_EXP;
        else
            return MON_VALID;
    }
    else if (size == 1) {
        getDpValueEx(parId, &intChar, &size, &nElements);
        intVal = (char)intChar;
        if (intVal != expValue)
            return MON_NOT_EXP;
        else
            return MON_VALID;
    }
    else {
        CrFwSetAppErrCode(CrPsIllUIMonParSize);
        return MON_VALID;
    }
}
