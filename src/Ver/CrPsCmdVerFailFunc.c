/**
 * @file CrPsCmdVerFailFunc.c
 * @ingroup Serv1
 * @ingroup procedures
 *
 * @brief This procedure is run when a command has failed its start check or its termination check
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
 
/** CrPsCmdVerFail function definitions */
#include "CrPsCmdVerFail.h"

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
#include "Pckt/CrPsPckt.h"
#include "Pckt/CrPsPcktVer.h"

#include <stdlib.h>
#include <assert.h>

static FwSmDesc_t rep;
CrFwServSubType_t repSubType;


/* ------------------------------------------------------------------------------------ */
/** Action for node N2. */
void CrPsCmdVerFailN2(FwPrDesc_t prDesc) {
  CrFwRepInCmdOutcome_t outcome = CrPsVerConfigGetOutcome();

  /* Retrieve an OutComponent of type (1,2), (1,4) or (1,8) from the OutFactory */
  switch (outcome) {
    case crCmdAckAccFail:   /* InCommand failed its validity check */
         repSubType = VERFAILEDACCREP_STYPE;
         rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERFAILEDACCREP_STYPE, 0, 0);
         break;
    case crCmdAckStrFail:   /* InCommand Start Action has failed */
         repSubType = VERFAILEDSTARTREP_STYPE;
         rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERFAILEDSTARTREP_STYPE, 0, 0);
         break;
    case crCmdAckTrmFail:    /* InCommand Termination Action failed */
         repSubType = VERFAILEDTERMREP_STYPE;
         rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERFAILEDTERMREP_STYPE, 0, 0);
         break;
    case crCmdAckLdFail:    /* InCommand could not be loaded in its InManager */
         repSubType = VERFAILEDACCREP_STYPE;
         rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERFAILEDACCREP_STYPE, 0, 0);
         break;
    default:                /* InCommand component could not be created (crCmdAckCreFail) */
         repSubType = VERFAILEDACCREP_STYPE;
         rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERFAILEDACCREP_STYPE, 0, 0);
         assert(outcome == crCmdAckCreFail);
  }

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N3. */
void CrPsCmdVerFailN3(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);

  /* Generate error report OUTFACTORY_FAIL */
  CrFwRepErrKind(psOutFactoryFail, 0, 0, VER_TYPE, repSubType, CrPsVerConfigGetFailCode());

  return;
}

/* ------------------------------------------------------------------------------------ */
/** Action for node N4. */
void CrPsCmdVerFailN4(FwPrDesc_t prDesc) {
  FwSmDesc_t inCmd;
  CrFwDestSrc_t inCmdSrc;
  CrFwPckt_t inPckt, outPckt;
  CrFwRepInCmdOutcome_t outcome;
  CrPsSixteenBit_t tcPcktSeqCtrl;
  CrPsThirteenBit_t tcPcktId;
  CrFwOutcome_t failCode;
  CrPsFailData_t failData;
  CrFwServType_t type;
  CrFwServSubType_t subType;
  CrFwDiscriminant_t disc;
  CrPsThreeBit_t tcPcktVersNmb;
  CrPsNOfCmd_t nOfCmds;

  /* Configure report and load it in the OutLoader */
  outPckt = CrFwOutCmpGetPckt(rep);
  outcome = CrPsVerConfigGetOutcome();
  failCode = CrPsVerConfigGetFailCode();
  type = CrPsVerConfigGetServType();
  subType = CrPsVerConfigGetServSubType();
  disc = CrPsVerConfigGetDisc();
  failData = getDpVerFailData();
  inCmd = CrPsVerConfigGetInCmd();
  if (inCmd != NULL)      /* If the InCommand creation failed, InCmd is NULL */
    inPckt = CrFwInCmdGetPckt(inCmd);
  else
    inPckt = CrPsVerConfigGetInPckt();
  tcPcktVersNmb = getTcHeaderPcktVersionNmb(inPckt);
  tcPcktSeqCtrl = getTcHeaderSeqFlags(inPckt)*0x4000+getTcHeaderSeqCount(inPckt);
  tcPcktId = getTcHeaderPcktType(inPckt)*0x1000+getTcHeaderSecHeaderFlag(inPckt)*0x800+getTcHeaderAPID(inPckt);

  switch (outcome) {
    case crCmdAckAccFail:   /* InCommand failed its validity check */
        setVerFailedAccRepPcktVersNumber(outPckt, tcPcktVersNmb);
        setVerFailedAccRepTcPcktSeqCtrl(outPckt, tcPcktSeqCtrl);
        setVerFailedAccRepTcPcktId(outPckt, tcPcktId);
        setVerFailedAccRepTcFailCode(outPckt, failCode);
        setVerFailedAccRepTcFailData(outPckt, failData);
        setVerFailedAccRepTcType(outPckt, type);
        setVerFailedAccRepTcSubType(outPckt, subType);
        setVerFailedAccRepTcDisc(outPckt, disc);
        /* Update data pool variables related to acceptance failure */
        setDpVerFailCodeAccFailed(failCode);
        nOfCmds = getDpVerNOfAccFailed();
        setDpVerNOfAccFailed(nOfCmds+1);
        setDpVerPcktIdAccFailed(tcPcktId);
        break;
    case crCmdAckStrFail:   /* InCommand Start Action has failed */
        setVerFailedStartRepPcktVersNumber(outPckt, tcPcktVersNmb);
        setVerFailedStartRepTcPcktSeqCtrl(outPckt, tcPcktSeqCtrl);
        setVerFailedStartRepTcPcktId(outPckt, tcPcktId);
        setVerFailedStartRepTcFailCode(outPckt, failCode);
        setVerFailedStartRepTcFailData(outPckt, failData);
        setVerFailedStartRepTcType(outPckt, type);
        setVerFailedStartRepTcSubType(outPckt, subType);
        setVerFailedStartRepTcDisc(outPckt, disc);
        /* Update data pool variables related to start failure */
        setDpVerFailCodeStartFailed(failCode);
        nOfCmds = getDpVerNOfStartFailed();
        setDpVerNOfStartFailed(nOfCmds+1);
        setDpVerPcktIdStartFailed(tcPcktId);
        break;
    case crCmdAckTrmFail:    /* InCommand Termination Action failed */
        setVerFailedTermRepPcktVersNumber(outPckt, tcPcktVersNmb);
        setVerFailedTermRepTcPcktSeqCtrl(outPckt, tcPcktSeqCtrl);
        setVerFailedTermRepTcPcktId(outPckt, tcPcktId);
        setVerFailedTermRepTcFailCode(outPckt, failCode);
        setVerFailedTermRepTcFailData(outPckt, failData);
        setVerFailedTermRepTcType(outPckt, type);
        setVerFailedTermRepTcSubType(outPckt, subType);
        setVerFailedTermRepTcDisc(outPckt, disc);
        /* Update data pool variables related to termination failure */
        setDpVerFailCodeTermFailed(failCode);
        nOfCmds = getDpVerNOfTermFailed();
        setDpVerNOfTermFailed(nOfCmds+1);
        setDpVerPcktIdTermFailed(tcPcktId);
        break;
    case crCmdAckLdFail:    /* InCommand could not be loaded in its InManager */
        setVerFailedAccRepPcktVersNumber(outPckt, tcPcktVersNmb);
        setVerFailedAccRepTcPcktSeqCtrl(outPckt, tcPcktSeqCtrl);
        setVerFailedAccRepTcPcktId(outPckt, tcPcktId);
        setVerFailedAccRepTcFailCode(outPckt, failCode);
        setVerFailedAccRepTcFailData(outPckt, failData);
        setVerFailedAccRepTcType(outPckt, type);
        setVerFailedAccRepTcSubType(outPckt, subType);
        setVerFailedAccRepTcDisc(outPckt, disc);
        /* Update data pool variables related to start failure */
        setDpVerFailCodeStartFailed(failCode);
        nOfCmds = getDpVerNOfStartFailed();
        setDpVerNOfStartFailed(nOfCmds+1);
        setDpVerPcktIdStartFailed(tcPcktId);
        break;
    default:                /* InCommand component could not be created (crCmdAckCreFail) */
        setVerFailedAccRepPcktVersNumber(outPckt, 0);
        setVerFailedAccRepTcPcktSeqCtrl(outPckt, 0);
        setVerFailedAccRepTcPcktId(outPckt, 0);
        setVerFailedAccRepTcFailCode(outPckt, failCode);
        setVerFailedAccRepTcFailData(outPckt, 0);
        setVerFailedAccRepTcType(outPckt, type);
        setVerFailedAccRepTcSubType(outPckt, subType);
        setVerFailedAccRepTcDisc(outPckt, disc);
        /* Update data pool variables related to acceptance failure */
        setDpVerFailCodeAccFailed(failCode);
        nOfCmds = getDpVerNOfAccFailed();
        setDpVerNOfAccFailed(nOfCmds+1);
        setDpVerPcktIdAccFailed(tcPcktId);
        assert(outcome == crCmdAckCreFail);
  }

  /* Set the destination of the report to the source of the in-coming packet */
  inCmdSrc = CrFwPcktGetSrc(inPckt);
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
FwPrBool_t CrPsCmdVerFailG1(FwPrDesc_t prDesc) {
  CRFW_UNUSED(prDesc);

  /* [ OutFactory fails to generate OutComponent ] */
  if (rep == NULL)
     return 1;
  else
     return 0;
}