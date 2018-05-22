/**
 * @file CrPsTstConnectCmd.c
 * @ingroup Serv17
 * @ingroup InCmd
 *
 * @brief Implementation of the Perform Connection Test in-coming command (17,3).
 *
 * @author Christian Reimers <christian.reimers@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 *
 * last modification: 22.01.2018
 *
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

#include "CrPsTstConnectCmd.h"
#include "CrPsTstConfig.h"

/* CrFramework includes */
#include "Pckt/CrFwPckt.h"
#include "OutFactory/CrFwOutFactory.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutLoader/CrFwOutLoader.h"
#include "CrFwCmpData.h"

/* FwProfile includes */
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwSmConfig.h"

#include "CrPsUtilitiesServTest.h"
#include "Services/General/CrPsConstants.h"
#include "Services/General/CrPsPktServTest.h"
#include "DataPool/CrPsDp.h"
#include "DataPool/CrPsDpServTest.h"

#include <stdlib.h>

void CrPsTestOnBoardConnectionStartAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t       *cmpDataStart;
  CrFwInCmdData_t     *cmpSpecificData;
  CrFwPckt_t           inPckt;
  DestSrc_t            appId;

  /* Run the procedure Start Action of OnBoardConnectCmd Command */

  /* Get in packet */
  cmpDataStart    = (CrFwCmpData_t   *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpDataStart->cmpSpecificData;
  inPckt          = cmpSpecificData->pckt;

  /* get identifier of application with which the connection test is done */
  appId = getTstConnectCmdAppId(inPckt);

  /* store in data pool */
  setDpOnBoardConnectDest(appId);

  /* Load the descriptor of the (17,3) command in the Start Procedure */
  FwPrSetData(CrPsTstConfigGetStart17s3(), smDesc);

  /* Run the procedure */
  FwPrRun(CrPsTstConfigGetStart17s3());

  cmpDataStart->outcome =

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsTestOnBoardConnectionProgressAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t      *cmpDataPrgr;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          inPckt;
  CrFwDestSrc_t       srcId;
  prDataPrgrAction_t *prDataPrgrActionPtr;

  /* Run the procedure Progress Action of OnBoardConnectCmd Command (see figure 13.2 in PP-DF-COR-003) */

  /* Get in packet */
  cmpDataPrgr     = (CrFwCmpData_t   *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpDataPrgr->cmpSpecificData;
  inPckt          = cmpSpecificData->pckt;

  /* Get the InCmd source and set it in the prData */
  srcId = CrFwPcktGetSrc(inPckt);

  /* Set prData of procedure */
  prDataPrgrActionPtr = FwPrGetData(getPrDescServTestOnBoardConnPrgr());
  prDataPrgrActionPtr->source = srcId;
  prDataPrgrActionPtr->stepId = timeOut_cnt;
  FwPrSetData(getPrDescServTestOnBoardConnPrgr(), prDataPrgrActionPtr);

  /* Run the procedure */
  FwPrRun(getPrDescServTestOnBoardConnPrgr());

  /* Get procedure parameters */
  prDataPrgrActionPtr = FwPrGetData(getPrDescServTestOnBoardConnPrgr());

  /* Set the Outcome*/
  cmpDataPrgr->outcome = prDataPrgrActionPtr->outcome;

  /* Increment timeout counter */
  timeOut_cnt++;

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsTestOnBoardConnectionTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t      *inData;
  prDataPrgrAction_t *prDataPrgrActionPtr;
  uint16_t            outcome;

  /* TODO: Set action outcome to 'success' if the (17,4) report was issued and to 'failure' otherwise */

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  /* Get procedure parameters */
  prDataPrgrActionPtr = (prDataPrgrAction_t*) FwPrGetData(getPrDescServTestOnBoardConnPrgr());

  /* Get the Outcome*/
  outcome = prDataPrgrActionPtr->outcome;

  if (outcome == 1)
    {
      inData->outcome = 1;
    }
  else if ((outcome == 0) || (outcome > 2))
    {
      inData->outcome = 0;
    }

  return;
}
