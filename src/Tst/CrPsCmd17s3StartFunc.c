/**
 * @file CrPsCmd17s3StartFunc.c
 * @ingroup man_ver7
 * @ingroup procedures 
 *
 * @brief This procedure is run by the Start Action of the command (17,3)
 *
 * @author Christian Reimers <christian.reimers@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * 
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

/** CrPsCmd17s3Start function definitions */
#include "CrPsCmd17s3Start.h"
#include "CrPsServTypeId.h"
#include "CrPsTstConfig.h"
#include "Pckt/CrPsPcktTst.h"
#include "DataPool/CrPsDp.h"
#include "DataPool/CrPsDpVer.h"
#include "DataPool/CrPsDpTst.h"
#include "CrPsConstants.h"
#include "CrPsTypes.h"

/** FW Profile function definitions */
#include "FwSmConstants.h"
#include "FwPrConstants.h"
#include "FwSmConfig.h"
#include "FwPrConfig.h"

/* Framework function definitions */
#include "OutFactory/CrFwOutFactory.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutLoader/CrFwOutLoader.h"
#include "CrFwTime.h"
#include "CrFwCmpData.h"
#include "CrFwRepErr.h"

#include <stdlib.h>

/** The (17,1) command generated by the connection test command */
static FwSmDesc_t cmd17s1;

/** The (17,4) report generated by the connection test command */
static FwSmDesc_t rep17s4;

/* ------------------------------------------------------------------------------------ */
/* Action for node N1. */
void CrPsTestOnBoardConnectionStartN1(FwPrDesc_t prDesc) {
  CrFwDestSrc_t areYouAliveSrc;
  CrFwTime_t curTime;

  CRFW_UNUSED(prDesc);

  /* Set areYouAliveSrc to zero */
  areYouAliveSrc = 0;
  setDpTstAreYouAliveSrc(areYouAliveSrc);

  /* Set areYouAliveStart to the current time */
  curTime = CrFwGetCurrentTime();
  setDpTstAreYouAliveStart(curTime);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N2. */
void CrPsTestOnBoardConnectionStartN2(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);

  /* Retrieve an OutComponent of type (17,1) from the OutFactory */
  cmd17s1 = CrFwOutFactoryMakeOutCmp(TST_TYPE, TSTAREYOUALIVECMD_STYPE, 0, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N3. */
void CrPsTestOnBoardConnectionStartN3(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);

  /* Generate error report OUTFACTORY_FAIL */
  CrFwRepErrKind(psOutFactoryFail, 0, 0, TST_TYPE, TSTAREYOUALIVEREP_STYPE, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N4. */
void CrPsTestOnBoardConnectionStartN4(FwPrDesc_t prDesc) {
  CrPsTstData_t* prDescData;
  FwSmDesc_t cmd17s3;
  CrFwPckt_t pcktCmd17s3;
  CrFwDestSrc_t destId;

  /* Configure (17,1) OutComponent */

  /* Get identifier of application to which the (17,1) command must be sent.
   * This is a parameter of the (17,3) command and it must therefore be retrieved
   * from the (17.3) command. */
  prDescData = (CrPsTstData_t*)FwPrGetData(prDesc);
  cmd17s3 = prDescData->cmd17s3;
  pcktCmd17s3 = CrFwInCmdGetPckt(cmd17s3);
  destId = getTstConnectCmdAppId(pcktCmd17s3);

  /* Set OutComponent parameters */
  CrFwOutCmpSetDest(cmd17s1, destId);

  /* Copy the destination of the (17,1) to the data pool */
  setDpTstOnBoardConnectDest(destId);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N5. */
void CrPsTestOnBoardConnectionStartN5(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);

  /* Load OutComponent in OutLoader */
  CrFwOutLoaderLoad(cmd17s1);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N7. */
void CrPsTestOnBoardConnectionStartN7(FwPrDesc_t prDesc) {
  CrPsTstData_t* prTstData;
  CrFwCmpData_t* cmpData;
  FwSmDesc_t cmd17s3;

  /* Set outcome of Start Action to 'success' */
  prTstData = FwPrGetData(prDesc);
  cmd17s3 = prTstData->cmd17s3;
  cmpData = (CrFwCmpData_t*) FwSmGetData(cmd17s3);
  cmpData->outcome = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N8. */
void CrPsTestOnBoardConnectionStartN8(FwPrDesc_t prDesc) {
  CrPsTstData_t* prTstData;
  CrFwCmpData_t* cmpData;
  FwSmDesc_t cmd17s3;

  /* Set outcome of Start Action to 'failure' with failure code VER_REP_CR_FD */

  /* Set outcome in InCmd prData to 'failure' (failure code to VER_REP_CR_FD) */
  prTstData = (CrPsTstData_t*)FwPrGetData(prDesc);
  cmd17s3 = prTstData->cmd17s3;
  CrFwSetSmOutcome(cmd17s3, VER_REP_CR_FD);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N9. */
void CrPsTestOnBoardConnectionStartN9(FwPrDesc_t prDesc) {
  CrPsTstData_t* prTstData;

  /* Retrieve an OutComponent of type (17,4) from the OutFactory */
  rep17s4 = CrFwOutFactoryMakeOutCmp(TST_TYPE, TSTCONNECTREP_STYPE, 0, 0);

  /* Load the (17,4) OutComponent in the data of the Start Action Procedure.
   * This allows the (17,4) procedure to be passed to the Progress Action Procedure.
   */
  prTstData = (CrPsTstData_t*)FwPrGetData(prDesc);
  prTstData->rep17s4 = rep17s4;
  prTstData->isRep17s4Alive = 1;

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N10. */
void CrPsTestOnBoardConnectionStartN10(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);

  /* Release (17,1) OutComponent */
  CrFwOutFactoryReleaseOutCmp(cmd17s1);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Guard on the Control Flow from DECISION1 to N1. */
FwPrBool_t CrPsTestOnBoardConnectionStartG1(FwPrDesc_t prDesc) {
  int i;
  CrPsTstData_t* prDescData;
  FwSmDesc_t cmd17s3;
  CrFwPckt_t pcktCmd17s3;
  CrFwDestSrc_t destId, appId;

  /* [ Identifier of target application is legal ] */

  /* Get identifier of application to which the (17,1) command must be sent.
   * This is a parameter of the (17,3) command and it must therefore be retrieved
   * from the (17.3) command. */
  prDescData = (CrPsTstData_t*)FwPrGetData(prDesc);
  cmd17s3 = prDescData->cmd17s3;
  pcktCmd17s3 = CrFwInCmdGetPckt(cmd17s3);
  destId = getTstConnectCmdAppId(pcktCmd17s3);

  /* get all target application IDs and check them */
  for (i=0; i<TST_N_DEST; i++) {
      appId = getDpTstOnBoardConnectDestLstItem(i);
      if (destId == appId)
        return 1;
  }

  return 0;
}

/* ------------------------------------------------------------------------------------ */
/* Guard on the Control Flow from DECISION2 to N3. */
FwPrBool_t CrPsTestOnBoardConnectionStartG2(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);

  /* [ OutFactory fails to generate OutComponent ] */
  if (cmd17s1 == NULL)
    return 1;
  else
    return 0;
}

/* ------------------------------------------------------------------------------------ */
/* Guard on the Control Flow from DECISION3 to N4. */
FwPrBool_t CrPsTestOnBoardConnectionStartG3(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);

  /* [ OutFactory returns OutComponent ] */
  if (rep17s4 != NULL)
    return 1;
  else
    return 0;
}
