/**
 * @file CrPsCmdPrgrSuccFunc.c
 * @ingroup Serv1
 * @ingroup procedures
 *
 * @brief This procedure is run when a command has passed its progress check
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

/** CrPsCmdPrgrSucc function definitions */
#include "CrPsCmdPrgrSucc.h"

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

/** PUS Extension function declarations */
#include "DataPool/CrPsDp.h"
#include "DataPool/CrPsDpVer.h"
#include "Ver/CrPsVerConfig.h"
#include "CrPsTypes.h"
#include "CrPsServTypeId.h"
#include "Pckt/CrPsPckt.h"
#include "Pckt/CrPsPcktVer.h"

#include <stdlib.h>
#include <assert.h>

static FwSmDesc_t rep;


/* ----------------------------------------------------------------------------------------------------------------- */
/** Action for node N2. */
void CrPsCmdPrgrSuccN2(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);

  /* Retrieve an OutComponent of type (1,5) from the OutFactory */
  rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERSUCCPRGRREP_STYPE, 0, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N3. */
void CrPsCmdPrgrSuccN3(FwPrDesc_t prDesc) {
    CRFW_UNUSED(prDesc);

    /* Generate error report OUTFACTORY_FAIL */
    CrFwRepErrKind(psOutFactoryFail, 0, 0, VER_TYPE, VERSUCCPRGRREP_STYPE, 0);

    return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N4. */
void CrPsCmdPrgrSuccN4(FwPrDesc_t prDesc) {
    FwSmDesc_t inCmd;
    CrFwDestSrc_t inCmdSrc;
    CrFwPckt_t inPckt, outPckt;
    CrPsSixteenBit_t tcPcktSeqCtrl;
    CrPsThirteenBit_t tcPcktId;
    CrFwProgressStepId_t prgrStepId;

    /* Configure report and load it in the OutLoader */
    outPckt = CrFwOutCmpGetPckt(rep);
    inCmd = CrPsVerConfigGetInCmd();
    inPckt = CrFwInCmdGetPckt(inCmd);
    tcPcktSeqCtrl = getTcHeaderSeqFlags(inPckt)*(2^14)+getTcHeaderSeqCount(inPckt);
    tcPcktId = getTcHeaderPcktType(inPckt)*(2^13)+getTcHeaderSecHeaderFlag(inPckt)*(2^13)+getTcHeaderAPID(inPckt);
    prgrStepId = CrFwInCmdGetProgressStepId(inCmd);

    setVerSuccPrgrRepPcktVersNumber(outPckt, getTcHeaderPcktVersionNmb(inCmd));
    setVerSuccPrgrRepTcPcktSeqCtrl(outPckt, tcPcktSeqCtrl);
    setVerSuccPrgrRepTcPcktId(outPckt, tcPcktId);
    setVerSuccPrgrRepTcPrgStep(outPckt, prgrStepId);

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

/** Guard on the Control Flow from DECISION2 to N3. */
FwPrBool_t CrPsCmdPrgrSuccG1(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);

  /* [ OutFactory fails to generate OutComponent ] */
  if (rep == NULL)
      return 1;
  else
      return 0;
}

/* ----------------------------------------------------------------------------------------------------------------- */

