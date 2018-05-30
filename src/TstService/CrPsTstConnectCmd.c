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

#include "DataPool/CrPsDp.h"

#include <stdlib.h>

void CrPsTestOnBoardConnectionStartAction(FwSmDesc_t smDesc) {
  CrPsTstData_t* startPrData;
  FwPrDesc_t startPr;

  /* Load the descriptor of the (17,3) command in the data of the Start Action Procedure */
  startPr = CrPsTstConfigGetStart17s3();
  startPrData = FwPrGetData(startPr);
  startPrData->cmd17s3 = smDesc;

  /* Run the procedure Start Action of OnBoardConnectCmd Command */
  FwPrRun(startPr);

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsTestOnBoardConnectionProgressAction(FwSmDesc_t smDesc) {
	  CrPsTstData_t* prgrPrData;
	  FwPrDesc_t prgrPr;

	  /* Load the descriptor of the (17,3) command in the data of the Start Action Procedure */
	  prgrPr = CrPsTstConfigGetPrgr17s3();
	  prgrPrData = FwPrGetData(prgrPr);
	  prgrPrData->cmd17s3 = smDesc;

	  /* Run the procedure Start Action of OnBoardConnectCmd Command */
	  FwPrRun(prgrPr);

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
