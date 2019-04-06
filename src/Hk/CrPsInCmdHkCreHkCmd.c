/**
 * @file
 * @ingroup man_hk
 *
 * Implementation of TC(3,1) HkCreHkCmd as an incoming command.
 * The header file CrPsInCmdHkCreHkCmd.h for this body file was
 * generated automatically by the CORDET Editor.
 * This file also implements the TC(3,2) to create a diagnostic report definition.
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

/** The (3,25) report created by the command */
static FwSmDesc_t rep;
/** The index of the RDL slot where the report is stored */
static short int rdlSlot;
/** The SID of the report to be created */
static CrPsSID_t sid;
/** The number of data items in the report to be created */
static CrPsNPar_t N1;
/** The packet holding the command */
static CrFwPckt_t pckt;

/* ------------------------------------------------------------------------------------ */
void CrPsInCmdHkCreHkCmdStartAction(FwSmDesc_t smDesc) {
  CrPsNPar_t i;
  CrFwPcktLength_t len;
  CrPsParId_t parId;
  CrFwServSubType_t servSubType;

  /* Get the raw command packet */
  pckt = CrFwInCmdGetPckt(smDesc);

  /* Get the service sub-type */
  servSubType = CrFwInCmdGetServSubType(smDesc);

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
    setDpVerFailData(sid);
    return;
  }

  if (sid > HK_MAX_SID) {
    CrFwSetSmOutcome(smDesc, VER_ILL_SID);
    setDpVerFailData(sid);
    return;
  }

  /* Check legality constraints on command parameters - Check legality of number of parameters */
  N1 = getHkCreHkCmdN1(pckt);
  if (N1 > HK_MAX_N_SIMPLE) {
    CrFwSetSmOutcome(smDesc, VER_ILL_NID);
    setDpVerFailData(N1);
    return;
  }

  /* Check legality constraints on command parameters - Check legality of parameter identifiers */
  /* Also: compute the length of the (3,25) packet -- this is useful later                      */
  len = LEN_HK_REP;
  for (i=0; i<N1; i++) {
    parId = getHkCreHkCmdN1ParamId(pckt, i);
    len = len + getDpSize(parId);
    if (parId < DpIdParamsLowest) {
      CrFwSetSmOutcome(smDesc, VER_ILL_DI_ID);
      setDpVerFailData(parId);
      return;
    }
    if (parId > DpIdVarsHighest) {
      CrFwSetSmOutcome(smDesc, VER_ILL_DI_ID);
      setDpVerFailData(parId);
      return;
    }
  }

  /* Check the SID in the command is not already in use */
  if (CrPsHkConfigGetRdlSlot(sid) != -1) {
    CrFwSetSmOutcome(smDesc, VER_SID_IN_USE);
    setDpVerFailData(sid);
    return;
  }

  /* Retrieve the report packet from the OutFactory */
  if (servSubType == HKCREHKCMD_STYPE)
    rep = CrFwOutFactoryMakeOutCmp(HK_TYPE, HKREP_STYPE, 0, len);
  else
    rep = CrFwOutFactoryMakeOutCmp(HK_TYPE, HKDIAGREP_STYPE, 0, len);


  /* If report packet generation failed, generate error report */
  if (rep == NULL) {
    CrFwRepErrKind(psOutFactoryFail, 0, 0, HK_TYPE, HKREP_STYPE, 0);
    CrFwSetSmOutcome(smDesc, VER_REP_CR_FD);
    return;
  }

  /* Set action outcome to 'success' */
  CrFwSetSmOutcome(smDesc, 1);
}

/* ------------------------------------------------------------------------------------ */
void CrPsInCmdHkCreHkCmdProgressAction(FwSmDesc_t smDesc) {

  /* Configure the housekeeping report */
  CrPsHkConfigHkRepOnBoard(rep, rdlSlot, smDesc);

  /* Load the report in the OutLoader */
  CrFwOutLoaderLoad(rep);

  /* Set outcome to 'success' and completion outcome to 'completed' */
  CrFwSetSmOutcome(smDesc, 1);
  CrFwInCmdSetProgressActionCompleted(smDesc, 1);
}

