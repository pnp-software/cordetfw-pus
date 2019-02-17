/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(3,1) HkCreHkCmd as an incoming command.
 *
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 *
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "CrPsInCmdHkCreHkCmd.h"
#include "CrPsHkConfig.h"
#include "CrPsTypes.h"
#include "Pckt/CrPsPcktHk.h"
#include "CrPsServTypeId.h"
#include "DataPool/CrPsDp.h"
#include "DataPool/CrPsDpVer.h"

/* Include CORDET Framework Files */
#include "OutLoader/CrFwOutLoader.h"
#include "InCmd/CrFwInCmd.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "OutFactory/CrFwOutFactory.h"
#include "CrFwRepErr.h"

static FwSmDesc_t rep3s25;
static int rdlSlot;
static CrPsSID_t sid;
static CrPsNPar_t N1;
static CrFwPckt_t pckt;

/* ------------------------------------------------------------------------------------ */
/**
 * Start action of TC(3,1) HkCreHkCmd.
 * @limitation The following rejection criterium for the (3,1) command is not implemented:
 * reject command if any parameter identifiers are duplicated
 *
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdHkCreHkCmdStartAction(FwSmDesc_t smDesc) {
  CrPsNPar_t i;
  CrFwPcktLength_t len;
  CrPsParId_t parId;

  /* Get the raw command packet */
  pckt = CrFwInCmdGetPckt(smDesc);

  /* Check if there are free slots in the RDL */
  rdlSlot = CrPsHkConfigGetFreeRdlSlot();
  if (rdlSlot == -1) {
    CrFwSetSmOutcome(smDesc, VER_FULL_RDL);
    return;
  }

  /* Check legality constraints on command parameters - Check legality of SID */
  sid = getHkCreHkCmdSID(pckt);
  if (sid == 0) {
    CrFwSetSmOutcome(smDesc, VER_ILL_SID);
    setDpVerFailData(1);
    return;
  }

  if (sid > HK_MAX_SID) {
    CrFwSetSmOutcome(smDesc, VER_ILL_SID);
    setDpVerFailData(1);
    return;
  }

  /* Check legality constraints on command parameters - Check legality of number of parameters */
  N1 = getHkCreHkCmdN1(pckt);
  if (N1 > HK_MAX_N_SIMPLE) {
    CrFwSetSmOutcome(smDesc, VER_ILL_NID);
    setDpVerFailData(6);
    return;
  }

  /* Check legality constraints on command parameters - Check legality of parameter identifiers */
  /* Also: compute the length of the (3,25) packet -- this is useful later                      */
  len = LEN_HK_REP + 2;     /* Include length of checksum at end of packet                      */
  for (i=0; i<N1; i++) {
    parId = getHkCreHkCmdN1ParamId(pckt, i);
    len = len + getDpSize(parId);
    if (getHkCreHkCmdN1ParamId(pckt, i) == 0) {
      CrFwSetSmOutcome(smDesc, VER_ILL_DI_ID);
      setDpVerFailData(9);
      return;
    }
    if (getHkCreHkCmdN1ParamId(pckt, i) > HK_MAX_ID) {
      CrFwSetSmOutcome(smDesc, VER_ILL_DI_ID);
      setDpVerFailData(9);
      return;
    }
  }

  /* Check the SID in the command is not already in use */
  if (CrPsHkConfigGetRdlSlot(sid) != -1) {
    CrFwSetSmOutcome(smDesc, VER_SID_IN_USE);
    setDpVerFailData(sid);
    return;
  }

  /* Retrieve the (3,25) packet from the OutFactory */
  rep3s25 = CrFwOutFactoryMakeOutCmp(HK_TYPE, HKREP_STYPE, 0, len);

  /* If (3,25) packet generation failed, generate error report */
  if (rep3s25 == NULL) {
    CrFwRepErrKind(psOutFactoryFail, 0, 0, HK_TYPE, HKREP_STYPE, 0);
    CrFwSetSmOutcome(smDesc, VER_REP_CR_FD);
    return;
  }

  /* Set action outcome to 'success' */
  CrFwSetSmOutcome(smDesc, 1);
}

/* ------------------------------------------------------------------------------------ */
/**
 * Progress action of TC(3,1) HkCreHkCmd.
 * Add the definition of the new report to the RDL, set its enabled status to
 * ’disabled’, and set the action outcome to ’completed’
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdHkCreHkCmdProgressAction(FwSmDesc_t smDesc) {
  CrFwDestSrc_t dest;
  CrPsCycleCnt_t collectionInt;
  CrPsParId_t* parId;

  /* Configure the (3,25) report */
  dest = CrFwInCmdGetSrc(smDesc);
  collectionInt = getHkCreHkCmdCollectionInterval(pckt);
  parId = getHkCreHkCmdN1ParamIdArray(pckt);

  CrPsHkConfigHkRep(rep3s25, rdlSlot, sid, N1, dest, collectionInt, parId);

  /* Load the report in the OutLoader */
  CrFwOutLoaderLoad(rep3s25);

  /* Set outcome to 'success' and completion outcome to 'completed' */
  CrFwSetSmOutcome(smDesc, 1);
  CrFwInCmdSetProgressActionCompleted(smDesc, 1);
}

