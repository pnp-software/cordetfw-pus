/**
 * @file CrPsPcktReroutingFailFunc.c
 * @ingroup Serv1
 * @ingroup procedures
 *
 * @brief This procedure is run when the InLoader has found a packet with invalid destination
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

/** CrPsPcktReroutingFail function definitions */
#include "CrPsPcktReroutingFail.h"

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
static CrFwDestSrc_t invDest;
static CrPsThirteenBit_t tcPcktId;

/* ------------------------------------------------------------------------------------ */
/** Action for node N1. */
void CrPsPcktReroutingFailN1(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);
  FwPrDesc_t inPckt;

  /* Generate error report INLOADER_INV_DEST */
  inPckt = CrPsVerConfigGetInPckt();
  CrFwRepErrPckt(crInLoaderInvDest, 0, 0, inPckt);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N2. */
void CrPsPcktReroutingFailN2(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);

  /* Retrieve an OutComponent of type (1,10) from the OutFactory */
  rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERFAILEDROUTINGREP_STYPE, 0, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N3. */
void CrPsPcktReroutingFailN3(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);

  /* Generate error report OUTFACTORY_FAIL */
  CrFwRepErrKind(psOutFactoryFail, 0, 0, VER_TYPE, VERFAILEDROUTINGREP_STYPE, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N4. */
void CrPsPcktReroutingFailN4(FwPrDesc_t prDesc) {  FwSmDesc_t inCmd;
  CrFwDestSrc_t inPcktSrc;
  CrFwPckt_t inPckt, outPckt;
  CrPsSixteenBit_t tcPcktSeqCtrl;
  CrFwOutcome_t failCode;
  CrPsFailData_t failData;
  CrFwServType_t type;
  CrFwServSubType_t subType;
  CrFwDiscriminant_t disc;
  CrPsThreeBit_t tcPcktVersNmb;
  CrPsNOfCmd_t nOfCmds;

  /* Configure report (1,10) */
  inPckt = CrPsVerConfigGetInPckt();
  outPckt = CrFwOutCmpGetPckt(rep);
  type = CrPsVerConfigGetServType();
  subType = CrPsVerConfigGetServSubType();
  disc = CrPsVerConfigGetDisc();
  invDest = CrFwPcktGetDest(inPckt);
  tcPcktVersNmb = getTcHeaderPcktVersionNmb(inPckt);
  tcPcktSeqCtrl = getTcHeaderSeqFlags(inPckt)*0x400+getTcHeaderSeqCount(inPckt);
  tcPcktId = getTcHeaderPcktType(inPckt)*0x100+getTcHeaderSecHeaderFlag(inPckt)*0x80+getTcHeaderAPID(inPckt);

  setVerFailedRoutingRepPcktVersNumber(outPckt,tcPcktVersNmb);
  setVerFailedRoutingRepTcPcktId(outPckt, tcPcktId);
  setVerFailedRoutingRepTcPcktSeqCtrl(outPckt, tcPcktSeqCtrl);
  setVerFailedRoutingRepInvDest(outPckt, invDest);
  setVerFailedRoutingRepTcType(outPckt, type);
  setVerFailedRoutingRepTcSubType(outPckt, subType);
  setVerFailedRoutingRepTcDisc(outPckt, disc);

  /* Set the destination of the report to the source of the in-coming packet */
  inPcktSrc = CrFwPcktGetSrc(inPckt);
  CrFwOutCmpSetDest(rep, inPcktSrc);

  /* Load report in the Outloader */
  CrFwOutLoaderLoad(rep);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N5. */
void CrPsPcktReroutingFailN5(FwPrDesc_t prDesc) {
  CrPsNOfCmd_t nOfReroutingFailed;
  CRFW_UNUSED(prDesc);

  /* Increment data pool variable nOfReroutingFailed */
  nOfReroutingFailed = getDpVerNOfReroutingFailed();
  setDpVerNOfReroutingFailed(nOfReroutingFailed+1);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N6. */
void CrPsPcktReroutingFailN6(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);

  /* Update data pool variable pcktIdRerouting, invDestRerouting */
  setDpVerPcktIdReroutingFailed(tcPcktId);
  setDpVerInvDestRerouting(invDest);

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/** Guard on the Control Flow from DECISION1 to N1. */
FwPrBool_t CrPsPcktReroutingFailG1(FwPrDesc_t prDesc) {
  FwPrDesc_t inPckt;

  /* [ Packet encapsulates a report ] */
  inPckt = CrPsVerConfigGetInPckt();
  if (CrFwPcktGetCmdRepType(inPckt) == crRepType)
      return 1;
  else
      return 0;
}


/** Guard on the Control Flow from DECISION2 to N3. */
FwPrBool_t CrPsPcktReroutingFailG2(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);

  /* [ OutFactory fails to generate OutComponent ] */
  if (rep == NULL)
      return 1;
  else
      return 0;
}

/* ----------------------------------------------------------------------------------------------------------------- */

