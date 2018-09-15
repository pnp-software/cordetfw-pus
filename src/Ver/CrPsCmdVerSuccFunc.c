/**
 * @file CrPsCmdVerSuccFunc.c
 * @ingroup Serv1
 * @ingroup procedures
 *
 * @brief This procedure is run when a command has passed its acceptance, start or termination check
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 18:2:22
 *
 * @author Christian Reimers <christian.reimers@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
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

#include "DataPool/CrPsDp.h"
#include "DataPool/CrPsDpTst.h"
#include "CrPsTypes.h"
#include "CrPsServTypeId.h"

#include <stdlib.h>
#include <assert.h>

static FwSmDesc_t rep;

/* ------------------------------------------------------------------------------------ */
/** Action for node N2. */
void CrPsCmdVerSuccN2(FwPrDesc_t prDesc) {
  CrFwRepInCmdOutcome_t outcome = CrPsVerConfigGetOutcome();

  /* Retrieve an OutComponent of type (1,1), (1,3) or (1,7) from the OutFactory */
  if (outcome == crCmdAckAccSucc)
      rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERSUCCACCREP_STYPE, 0, 0);
  else if (outcome == crCmdAckStrSucc)
      rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERSUCCSTARTREP_STYPE, 0, 0);
  else
      rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERSUCCTERMREP_STYPE, 0, 0);

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N3. */
void CrPsCmdVerSuccN3(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);

  /* Generate error report OUTFACTORY_FAIL */
  CrFwRepErrKind(psOutFactoryFail, 0, 0, CrPsVerConfigGetServType(), CrPsVerConfigGetServSubType, CrPsVerConfigGetDisc());

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N4. */
void CrPsCmdVerSuccN4(FwPrDesc_t prDesc) {
  FwSmDesc_t inCmd;
  CrFwDestSrc_t inCmdSrc;
  CrFwPckt_t inPckt;
  CrFwRepInCmdOutcome_t outcome;
  CrPsSixteenBit_t tcPcktSeqCtrl;
  CrPsThirteenBit_t tcPcktId;

  /* Configure report and load it in the OutLoader */
  outcome = CrPsVerConfigGetOutcome();
  inCmd = CrPsVerConfigGetInCmd();
  inPckt = CrFwInCmdGetPckt(inCmd);
  tcPcktSeqCtrl = getTcHeaderSeqFlags(inPckt)*(2^14)+getTcHeaderSeqCount(inPckt);
  tcPcktId = getTcHeaderPcktType(inPckt)*(2^13)+getTcHeaderSecHeaderFlag(inPckt)*2^13+getTcHeaderAPID(inPckt);

  switch (outcome) {
    case crCmdAckAccSucc:
        setVerSuccAccRepPckttVersNumber(inPckt, getTcHeaderPcktVersionNmb(inCmd));
        setVerSuccAccRepTcPcktSeqCtrl(inPckt, tcPcktSeqCtrl);
        setVerSuccAccRepTcPcktId(inPckt, tcPcktId);
        break;
    case crCmdAckStrSucc:
        setVerSuccStartRepPckttVersNumber(inPckt, getTcHeaderPcktVersionNmb(inCmd));
        setVerSuccStartRepTcPcktSeqCtrl(inPckt, tcPcktSeqCtrl);
        setVerSuccStartRepTcPcktId(inPckt, tcPcktId);
        break;
    case crCmdAckTrmSucc:
        setVerSuccTermRepPckttVersNumber(inPckt, getTcHeaderPcktVersionNmb(inCmd));
        setVerSuccTermRepTcPcktSeqCtrl(inPckt, tcPcktSeqCtrl);
        setVerSuccTermRepTcPcktId(inPckt, tcPcktId);
        break;
    default:
        assert(0);
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

/** Guard on the Control Flow from DECISION2 to N3. */
FwPrBool_t CrPsCmdVerSuccG1(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);

  /* [ OutFactory fails to generate OutComponent ] */
  if (rep == NULL)
      return 1;
  else
      return 0;
}

/* ----------------------------------------------------------------------------------------------------------------- */

