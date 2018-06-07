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
#include "CrPsServTypeId.h"
#include "DataPool/CrPsDp.h"
#include "DataPool/CrPsDpTst.h"
#include "CrPsDpTypes.h"

/** FW Profile function definitions */
#include "FwSmConstants.h"
#include "FwPrConstants.h"

/* Framework function definitions */
#include "OutFactory/CrFwOutFactory.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutLoader/CrFwOutLoader.h"

#include <stdlib.h>


/* ------------------------------------------------------------------------------------ */
/* Action for node N1. */
void CrPsTestOnBoardConnectionPrgrN1(FwPrDesc_t prDesc) {
  FwSmDesc_t rep17s4;
  FwSmDesc_t cmd17s3;
  CrPsTstData_t* prTstData;
  CrFwDestSrc_t destId;
  CrFwDestSrc_t srcId;
  CrFwCmpData_t* cmpData;

  /* Retrieve the data structure attached to the procedure */
  prTstData = (CrPsTstData_t*)FwPrGetData(prDesc);

  /* Retrieve the (17,4) report has been retrieved from the OutFactory by the Start Action of the (17,3)
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

  /* Set outcome to 'success' */
  cmpData = (CrFwCmpData_t*) FwSmGetData(cmd17s3);
  cmpData->outcome = 1;

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

  /* Set action outcome in the (17,3) command to 'continue' */
  cmpData = (CrFwCmpData_t*) FwSmGetData(cmd17s3);
  cmpData->outcome = 2;

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

  /* Set action outcome in the (17,3) command to 'failed' */
  cmpData = (CrFwCmpData_t*) FwSmGetData(cmd17s3);
  cmpData->outcome = 0;

  /* Retrieve the (17,4) report has been retrieved from the OutFactory by the Start Action of the (17,3)
   * and is available in the data structure attached to the Progress Action Procedure */
  rep17s4 = prTstData->rep17s4;

  /* Release the (17,4) report */
  CrFwOutFactoryReleaseOutCmp(rep17s4);

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/* Guard on the Control Flow from DECISION1 to N1. */
FwPrBool_t CrPsTestOnBoardConnectionPrgrG11(FwPrDesc_t prDesc) {
  DestSrc_t src;
  TimeSec_t timeOut;
  TimeSec_t curTime;

  CRFW_UNUSED(prDesc);

  /* [ (areYouAliveSrc > 0) &&
       (time elapsed since command execution started smaller than areYouAliveTimeOut) ] */

  /* Get areYouAliveSrc from data pool */
  src = getDpAreYouAliveSrc();

  /* Get areYouAliveTimeOut from data pool */
  timeOut = getDpAreYouAliveTimeOut();

  if (src == 0)
	  return 0;

  if (timeOut )

  if (appId > 0 && timeOut_cnt < timeOut)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/* ------------------------------------------------------------------------------------ */
/* Guard on the Control Flow from DECISION1 to N2. */
FwPrBool_t CrPsTestOnBoardConnectionPrgrG12(FwPrDesc_t prDesc) {
  CrPsApid_t    appId;
  CrPsTimeOut_t timeOut;

  CRFW_UNUSED(prDesc);

  /* [ (areYouAliveSrc == 0) &&
        (time elapsed since command execution started smaller than areYouAliveTimeOut) ] */

  /* Get areYouAliveSrc from data pool */
  appId = getDpAreYouAliveSrc();

  /* Get areYouAliveTimeOut from data pool */
  timeOut = getDpAreYouAliveTimeOut();

  if (appId == 0 && timeOut_cnt < timeOut)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

/* ------------------------------------------------------------------------------------ */
/* Guard on the Control Flow from DECISION1 to N3. */
FwPrBool_t CrPsTestOnBoardConnectionPrgrG13(FwPrDesc_t prDesc) {
  CrPsTimeOut_t timeOut; 

  CRFW_UNUSED(prDesc);

  /* [ (time elapsed since command execution started equal or greater than areYouAliveTimeOut) ] */

  /* Get areYouAliveTimeOut from data pool */
  timeOut = getDpAreYouAliveTimeOut();

  if (timeOut_cnt >= timeOut) {
      return 1;
  } else
      return 0;

}
