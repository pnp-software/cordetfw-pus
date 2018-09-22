/**
 * @file CrPsSpcTstAreYouAliveCmd.c
 * @ingroup Serv17
 * @ingroup InCmd
 *
 * @brief Implementation of the Perform Connection Test in-coming command packet.
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

#include "CrPsInCmdTstAreYouAliveCmd.h"

/* CrFramework includes */
#include "OutFactory/CrFwOutFactory.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutLoader/CrFwOutLoader.h"
#include "CrFwCmpData.h"
#include "CrFwRepErr.h"

/* FW Profile includes */
#include "FwSmConfig.h"

/* Configuration files */
#include "CrPsServTypeId.h"
#include "CrFwUserConstants.h"

#include <stdlib.h>

static FwSmDesc_t rep;


/* ------------------------------------------------------------------------------------ */
void CrPsTstAreYouAliveCmdStartAction(FwSmDesc_t smDesc) {
  CrFwCmpData_t* inData;

  /* Retrieve (17,2) report from OutFactory and set action outcome
     to \success' if retrieval succeeds. If the retrieval fails, generate
     error report OUTFACTORY FAILED and set outcome of Start
     Action to 'failed' with failure code VER_REP_CR_FD */

  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  rep = CrFwOutFactoryMakeOutCmp(TST_TYPE, TSTAREYOUALIVEREP_STYPE, 0, 0);

  if (rep != NULL) {
      inData->outcome = 1;
  } else {
      CrFwRepErrKind(psOutFactoryFail, inData->typeId, inData->instanceId, TST_TYPE, TSTAREYOUALIVEREP_STYPE, 0);
      inData->outcome = VER_REP_CR_FD;
  }

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsTstAreYouAliveCmdProgressAction(FwSmDesc_t smDesc) {
  CrFwDestSrc_t    source;

  /* Configure the (17,2) report with a destination equal to the
     source of the (17,1) command, load it in the OutLoader, and
     set action outcome to 'completed' */

  source = CrFwInCmdGetSrc(smDesc);
  CrFwOutCmpSetDest(rep, source);

  /* load the report in the OutLoader */
  CrFwOutLoaderLoad(rep);

  /* Set the outcome to 'success' */
  CrFwSetSmOutcome(smDesc, 1);

  return;
}
