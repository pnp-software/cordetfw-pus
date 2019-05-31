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

/** The pointers to the functions implementing the Parameter Monitors */
static CrPsMonPrFnc_t monFncPr[MON_N_PMON];


/* ----------------------------------------------------------------------------------- */
void CrPsMonConfigInit() {
  monFncPr = CrPsMonFncPrCreate(NULL);
  return;
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
CrPsValCheckExpVal_t CrPsMonConfigOutOfLimitCheck(CrPsParMonId_t parMonId) {

  /* Retrieve the value of the monitored parameter */
  CrPsParId_t parId = getDpMonDataItemIdItem(parMonId);



}

