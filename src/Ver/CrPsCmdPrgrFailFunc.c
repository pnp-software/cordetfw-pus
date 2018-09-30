/**
 * @file CrPsCmdPrgrFailFunc.c
 * @ingroup Serv1
 * @ingroup procedures
 *
 * @brief This procedure is run when a command has failed its progress check.
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

/** CrPsCmdPrgrFail function definitions */
#include "CrPsOutCmpVerFailedPrgrRep.h"

/** FW Profile function definitions */
#include "FwPrConstants.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwSmConfig.h"

/** CORDET FW function definitions */
#include "Pckt/CrFwPckt.h"
#include "CrFwCmpData.h"
#include "CrFwUserConstants.h"
#include "OutFactory/CrFwOutFactory.h"
#include "OutLoader/CrFwOutLoader.h"
#include "OutCmp/CrFwOutCmp.h"
#include "CrFwRepErr.h"
#include "CrFwRepInCmdOutcome.h"
#include "InCmd/CrFwInCmd.h"

/** PUS Extension function definitions */
#include "DataPool/CrPsDp.h"
#include "DataPool/CrPsDpTst.h"
#include "CrPsTypes.h"
#include "CrPsServTypeId.h"
#include "DataPool/CrPsDpVer.h"
#include "Ver/CrPsVerConfig.h"
#include "PcktFunctions/CrPsPckt.h"
#include "PcktFunctions/CrPsPcktVer.h"

#include <stdlib.h>
#include <assert.h>

static FwSmDesc_t rep;
static CrFwProgressStepId_t prgrStepId;
static CrPsThirteenBit_t tcPcktId;

/* ------------------------------------------------------------------------------------ */
/** Action for node N2. */
void CrPsCmdPrgrFailN2(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);

  /* Retrieve an OutComponent of type (1,5) from the OutFactory */
  rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERFAILEDPRGRREP_STYPE, 0, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N3. */
void CrPsCmdPrgrFailN3(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);

  /* Generate error report OUTFACTORY_FAIL */
  CrFwRepErrKind(psOutFactoryFail, 0, 0, VER_TYPE, VERSUCCPRGRREP_STYPE, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N4. */
void CrPsCmdPrgrFailN4(FwPrDesc_t prDesc) {
  CrFwDestSrc_t inPcktSrc;
  CrFwPckt_t inPckt, outPckt;
  CrPsSixteenBit_t tcPcktSeqCtrl;
  CrFwOutcome_t failCode;
  CrPsFailData_t failData;
  CrFwServType_t type;
  CrFwServSubType_t subType;
  CrFwDiscriminant_t disc;
  CrPsThreeBit_t tcPcktVersNmb;
  FwSmDesc_t inCmd;

  /* Configure report (1,10) */
  inCmd = CrPsVerConfigGetInCmd();
  inPckt = CrPsVerConfigGetInPckt();
  outPckt = CrFwOutCmpGetPckt(rep);
  type = CrPsVerConfigGetServType();
  subType = CrPsVerConfigGetServSubType();
  disc = CrPsVerConfigGetDisc();
  failCode = CrPsVerConfigGetFailCode();
  failData = getDpVerFailData();

  tcPcktVersNmb = getTcHeaderPcktVersionNmb(inPckt);
  tcPcktSeqCtrl = getTcHeaderSeqFlags(inPckt)*0x400+getTcHeaderSeqCount(inPckt);
  tcPcktId = getTcHeaderPcktType(inPckt)*0x100+getTcHeaderSecHeaderFlag(inPckt)*0x80+getTcHeaderAPID(inPckt);
  prgrStepId = CrFwInCmdGetProgressStepId(inCmd);

  setVerFailedPrgrRepPcktVersNumber(outPckt,tcPcktVersNmb);
  setVerFailedPrgrRepTcPcktId(outPckt, tcPcktId);
  setVerFailedPrgrRepTcPcktSeqCtrl(outPckt, tcPcktSeqCtrl);
  setVerFailedPrgrRepTcFailCode(outPckt, failCode);
  setVerFailedPrgrRepTcFailData(outPckt, failData);
  setVerFailedPrgrRepTcType(outPckt, type);
  setVerFailedPrgrRepTcSubType(outPckt, subType);
  setVerFailedPrgrRepTcDisc(outPckt, disc);

  /* Set the destination of the report to the source of the in-coming packet */
  inPcktSrc = CrFwPcktGetSrc(inPckt);
  CrFwOutCmpSetDest(rep, inPcktSrc);

  /* Load report in the Outloader */
  CrFwOutLoaderLoad(rep);

  /* Increment data pool variable nOfPrgrFailed */
  setDpVerNOfPrgrFailed(getDpVerNOfPrgrFailed()+1);

  /* Update data pool variable pcktIdPrgrFailed and prgrStepFailed */
  setDpVerPcktIdPrgrFailed(tcPcktId);
  setDpVerStepPrgrFailed(prgrStepId);

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION2 to N3. */
FwPrBool_t CrPsCmdPrgrFailG1(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);

  /* [ OutFactory fails to generate OutComponent ] */
  if (rep == NULL)
    return 1;
  else
    return 0;
}

/* ----------------------------------------------------------------------------------------------------------------- */

