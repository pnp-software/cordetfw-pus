/**
 * @file CrPsCmd17s3PrgrFunc.c
 * @ingroup Serv17
 * @ingroup procedures 
 *
 * @brief Define functions implementing the Progress Action of the command (17,3) of <code>CrPsCmd17s3Prgr.h</code>.
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
#include "CrPsTstConfig.h"
#include "CrPsServTypeId.h"
#include "DataPool/CrPsDp.h"
#include "DataPool/CrPsDpTst.h"
#include "CrPsTypes.h"

/** FW Profile function definitions */
#include "FwSmConstants.h"
#include "FwPrConstants.h"
#include "FwPrConfig.h"
#include "FwSmConfig.h"

/* Framework function definitions */
#include "OutFactory/CrFwOutFactory.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutLoader/CrFwOutLoader.h"
#include "CrFwTime.h"
#include "CrFwCmpData.h"

#include <stdlib.h>


/* ------------------------------------------------------------------------------------ */
/* Action for node N1. */
void CrPsTestOnBoardConnectionPrgrN1(FwPrDesc_t prDesc) {
  FwSmDesc_t rep17s4;
  FwSmDesc_t cmd17s3;
  CrPsTstData_t* prTstData;
  CrFwDestSrc_t srcId;
  CrFwCmpData_t* cmpData;

  /* Retrieve the data structure attached to the procedure */
  prTstData = (CrPsTstData_t*)FwPrGetData(prDesc);

  /* Retrieve the (17,4) report retrieved from the OutFactory by the Start Action of the (17,3)
   * and is available in the data structure attached to the Progress Action Procedure */
  rep17s4 = prTstData->rep17s4;

  /* Retrieve the descriptor of the (17,3) command which is being executed
   * (this is part of the data structure attached to the Progress Action Procedure) */
  cmd17s3 = prTstData->cmd17s3;

  /* Get the source of the (17,3) command  */
  srcId = CrFwInCmdGetSrc(cmd17s3);

  /* Configure the (17,4) report with a destination equal to the source of the (17,3),
   * load it in the Outloader and set action outcome to 'completed' */
  CrFwOutCmpSetDest(rep17s4, srcId);
  CrFwOutLoaderLoad(rep17s4);

  /* Set outcome to 'success' and completion outcome to 'not completed' */
  CrFwSetSmOutcome(cmd17s3, 1);
  CrFwInCmdSetProgressActionCompleted(cmd17s3, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N2. */
void CrPsTestOnBoardConnectionPrgrN2(FwPrDesc_t prDesc) {
  FwSmDesc_t cmd17s3;
  CrPsTstData_t* prTstData;
  CrFwCmpData_t* cmpData;

  /* Retrieve the data structure attached to the procedure */
  prTstData = (CrPsTstData_t*)FwPrGetData(prDesc);

  /* Retrieve the descriptor of the (17,3) command which is being executed
   * (this is part of the data structure attached to the Progress Action Procedure) */
  cmd17s3 = prTstData->cmd17s3;

  /* Set outcome to 'success' and completion outcome to 'completed' */
  CrFwSetSmOutcome(cmd17s3, 1);
  CrFwInCmdSetProgressActionCompleted(cmd17s3, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N3. */
void CrPsTestOnBoardConnectionPrgrN3(FwPrDesc_t prDesc) {
  FwSmDesc_t rep17s4;
  FwSmDesc_t cmd17s3;
  CrPsTstData_t* prTstData;
  CrFwCmpData_t* cmpData;

  /* Retrieve the data structure attached to the procedure */
  prTstData = (CrPsTstData_t*)FwPrGetData(prDesc);

  /* Retrieve the descriptor of the (17,3) command which is being executed
   * (this is part of the data structure attached to the Progress Action Procedure) */
  cmd17s3 = prTstData->cmd17s3;

  /* Set outcome to 'success' and completion outcome to 'completed' */
  CrFwSetSmOutcome(cmd17s3, 1);
  CrFwInCmdSetProgressActionCompleted(cmd17s3, 1);

  /* Retrieve the (17,4) report which was created by the Start Action of the (17,3) and
   * which is available in the data structure attached to the Progress Action Procedure */
  rep17s4 = prTstData->rep17s4;

  /* Release the (17,4) report */
  CrFwOutFactoryReleaseOutCmp(rep17s4);
  prTstData->isRep17s4Alive = 0;

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/* ------------------------------------------------------------------------------------ */
/* Guard on the Control Flow from DECISION1 to N1. */
FwPrBool_t CrPsTestOnBoardConnectionPrgrG11(FwPrDesc_t prDesc) {
  CrFwDestSrc_t src;
  CrFwTime_t timeOut;
  CrFwTime_t curTime;
  CrFwTime_t startTime;

  CRFW_UNUSED(prDesc);

  /* [ (areYouAliveSrc > 0) &&
       (time elapsed since command execution started smaller than areYouAliveTimeOut) ] */

  /* Get areYouAliveSrc from data pool */
  src = getDpTstAreYouAliveSrc();

  /* Get areYouAliveTimeOut from data pool */
  timeOut = getDpTstAreYouAliveTimeOut();

  /* Get the time when command execution started from the data pool */
  startTime = getDpTstAreYouAliveStart();

  /* Get the current time */
  curTime = CrFwGetCurrentTime();

  if (src == 0)
	  return 0;

  if ((curTime-startTime)>=timeOut )
	  return 0;

  return 1;
}

/* ------------------------------------------------------------------------------------ */
/* Guard on the Control Flow from DECISION1 to N2. */
FwPrBool_t CrPsTestOnBoardConnectionPrgrG12(FwPrDesc_t prDesc) {
  CrFwDestSrc_t src;
  CrFwTime_t timeOut;
  CrFwTime_t curTime;
  CrFwTime_t startTime;

  CRFW_UNUSED(prDesc);

  /* [ (areYouAliveSrc == 0) &&
        (time elapsed since command execution started smaller than areYouAliveTimeOut) ] */

  /* Get areYouAliveSrc from data pool */
  src = getDpTstAreYouAliveSrc();

  /* Get areYouAliveTimeOut from data pool */
  timeOut = getDpTstAreYouAliveTimeOut();

  /* Get the time when command execution started from the data pool */
  startTime = getDpTstAreYouAliveStart();

  /* Get the current time */
  curTime = CrFwGetCurrentTime();

  if (src != 0)
	  return 0;

  if ((curTime-startTime)>=timeOut )
	  return 0;

  return 1;
}
