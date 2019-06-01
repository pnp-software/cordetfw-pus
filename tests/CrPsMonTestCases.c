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
  CrPsThirtytwoBit_t* lowerLimRaw = (CrPsThirtytwoBit_t*)&lowerLimFloat;
  CrPsThirtytwoBit_t* upperLimRaw = (CrPsThirtytwoBit_t*)&upperLimFloat;

  /* The monitor procedure for float values is verified on variable DpIdlastEvtTime */
  lowerLimFloat = 1.3;
  upperLimFloat = 1.7;
  setDpMonLowerLimitItem(DpIdlastEvtTime, *lowerLimRaw);
  setDpMonUpperLimitItem(DpIdlastEvtTime, *upperLimRaw);

  valFloat = 1.5;
  if (setDpValue(DpIdlastEvtTime, &valFloat) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckR(DpIdlastEvtTime) != MON_VALID)
      return 0;

  valFloat = lowerLimFloat - 0.1;
  if (setDpValue(DpIdlastEvtTime, &valFloat) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckR(DpIdlastEvtTime) != MON_BELOW)
      return 0;

  valFloat = upperLimFloat + 0.1;
  if (setDpValue(DpIdlastEvtTime, &valFloat) == 0)
      return 0;
  if (CrPsMonConfigOutOfLimitCheckR(DpIdlastEvtTime) != MON_ABOVE)
      return 0;

  return 1;
}

