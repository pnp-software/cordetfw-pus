/**
 * @file CrPsCmdVerSuccFunc.c
 * @ingroup man_ver
 *
 * @brief Implementation for the actions and guards in the Command Verification Success Procedure.
 * This procedure is created and configured in module CrPsCmdVerSucc.h.
 * This module is automatically generated by the FW Profile Editor.
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

/** CrPsCmdVerSucc function definitions */
#include "CrPsCmdVerSucc.h"

/** FW Profile function definitions */
#include "FwPrConstants.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwSmConfig.h"

/** CORDET FW function definitions */
#include "Pckt/CrFwPckt.h"
#include "CrFwCmpData.h"
#include "OutFactory/CrFwOutFactory.h"
#include "OutLoader/CrFwOutLoader.h"
#include "OutCmp/CrFwOutCmp.h"
#include "CrFwRepInCmdOutcome.h"
#include "InCmd/CrFwInCmd.h"
#include "CrFwRepErr.h"

/** PUS Extension function definitions */
#include "DataPool/CrPsDp.h"
#include "DataPool/CrPsDpTst.h"
#include "CrPsTypes.h"
#include "CrPsServTypeId.h"
#include "DataPool/CrPsDpVer.h"
#include "Ver/CrPsVerConfig.h"
#include "Pckt/CrPsPckt.h"
#include "Pckt/CrPsPcktVer.h"

#include <stdlib.h>
#include <assert.h>

/** The report of type (1,1), (1,3) or (1,7) */
static FwSmDesc_t rep;
/** The report sub-type */
static CrFwServSubType_t repSubType;

/* ------------------------------------------------------------------------------------ */
/* Action for node N2. */
void CrPsCmdVerSuccN2(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);
  CrFwRepInCmdOutcome_t outcome = CrPsVerConfigGetOutcome();

  /* Retrieve an OutComponent of type (1,1), (1,3) or (1,7) from the OutFactory */
  switch (outcome) {
    case crCmdAckAccSucc:   /* Acceptance check was passed */
        repSubType = VERSUCCACCREP_STYPE;
        rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERSUCCACCREP_STYPE, 0, 0);
        break;
    case crCmdAckStrSucc:   /* Start action was successful */
        repSubType = VERSUCCSTARTREP_STYPE;
        rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERSUCCSTARTREP_STYPE, 0, 0);
        break;
    default:                /* Termination action was successful */
        repSubType = VERSUCCTERMREP_STYPE;
        rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERSUCCTERMREP_STYPE, 0, 0);
        assert(outcome == crCmdAckTrmSucc);
  }

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N3. */
void CrPsCmdVerSuccN3(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);

  /* Generate error report OUTFACTORY_FAIL */
  CrFwRepErrKind(psOutFactoryFail, 0, 0, VER_TYPE, repSubType, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/* Action for node N4. */
void CrPsCmdVerSuccN4(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);
  FwSmDesc_t inCmd;
  CrFwDestSrc_t inCmdSrc;
  CrFwPckt_t inPckt, outPckt;
  CrFwRepInCmdOutcome_t outcome;
  CrPsSixteenBit_t tcPcktSeqCtrl;
  CrPsThirteenBit_t tcPcktId;
  CrPsSixteenBit_t versNmbPcktId;

  /* Configure report and load it in the OutLoader */
  outPckt = CrFwOutCmpGetPckt(rep);
  outcome = CrPsVerConfigGetOutcome();
  inCmd = CrPsVerConfigGetInCmd();
  inPckt = CrFwInCmdGetPckt(inCmd);
  tcPcktSeqCtrl = getTcHeaderSeqFlags(inPckt)*(2^14)+getTcHeaderSeqCount(inPckt);
  tcPcktId = getTcHeaderPcktType(inPckt)*(2^13)+getTcHeaderSecHeaderFlag(inPckt)*(2^13)+getTcHeaderAPID(inPckt);
  versNmbPcktId = getTcHeaderPcktVersionNmb(inCmd);
  versNmbPcktId = (versNmbPcktId<<13) + tcPcktId;

  switch (outcome) {
    case crCmdAckAccSucc:
        setVerSuccAccRepVersNmbTcPcktId(outPckt,versNmbPcktId);
        setVerSuccAccRepTcPcktSeqCtrl(outPckt, tcPcktSeqCtrl);
        break;
    case crCmdAckStrSucc:
        setVerSuccStartRepVersNmbTcPcktId(outPckt,versNmbPcktId);
        setVerSuccStartRepTcPcktSeqCtrl(outPckt, tcPcktSeqCtrl);
        break;
    default:
        setVerSuccTermRepVersNmbTcPcktId(outPckt,versNmbPcktId);
        setVerSuccTermRepTcPcktSeqCtrl(outPckt, tcPcktSeqCtrl);
        assert (outcome == crCmdAckTrmSucc);
  }

  /* Set the destination of the report to the source of the in-coming packet */
  inCmdSrc = CrFwInCmdGetSrc(inCmd);
  CrFwOutCmpSetDest(rep, inCmdSrc);

  /* Load report in the Outloader */
  CrFwOutLoaderLoad(rep);

  return;
}

/* ------------------------------------------------------------------------------------ */
/**************/
/*** GUARDS ***/
/**************/

/* Guard on the Control Flow from DECISION2 to N3. */
FwPrBool_t CrPsCmdVerSuccG1(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);

  /* [ OutFactory fails to generate OutComponent ] */
  if (rep == NULL)
      return 1;
  else
      return 0;
}

/* ----------------------------------------------------------------------------------------------------------------- */

