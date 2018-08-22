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

#include "CrPsInCmdTstConnectCmd.h"
#include "CrPsTstConfig.h"

/* CrFramework includes */
#include "Pckt/CrFwPckt.h"
#include "OutFactory/CrFwOutFactory.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutLoader/CrFwOutLoader.h"
#include "OutRegistry/CrFwOutRegistry.h"
#include "CrFwCmpData.h"

/* FwProfile includes */
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwSmConfig.h"

#include "DataPool/CrPsDp.h"

#include <stdlib.h>

void CrPsTstConnectCmdStartAction(FwSmDesc_t smDesc) {
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
void CrPsTstConnectCmdProgressAction(FwSmDesc_t smDesc) {
  FwPrDesc_t prgrPr;

  /* Run the procedure Start Action of OnBoardConnectCmd Command */
  prgrPr = CrPsTstConfigGetPrgr17s3();
  FwPrRun(prgrPr);

  return;
}

/* ------------------------------------------------------------------------------------ */
void CrPsTstConnectCmdTerminationAction(FwSmDesc_t smDesc) {
  FwPrDesc_t cmd17s3;
  CrPsTstData_t* prTstData;

  /* Get the data structure attached to the Start and Progress Procedures of the (17,3) command */
  cmd17s3 = CrPsTstConfigGetStart17s3();
  prTstData = (CrPsTstData_t*)FwPrGetData(cmd17s3);

  /* Set action outcome to 'success' if the (17,4) report was issued and to 'failure' otherwise.
   * If the (17,4) report was issued, then prTstData->isRep17s4Alive is equal to 1, otherwise
   * it is equal to 0
   */
  CrFwSetSmOutcome(smDesc,prTstData->isRep17s4Alive);

  return;
}
