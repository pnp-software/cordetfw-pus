/**
 * @file
 * @ingroup PUSTestsuite
 *
 * Implementation of TC(255,1) DumSample1 as an incoming command.
 * This file implements both the functions defined in <code>CrPsInCmdDumSample1.h</code>
 * (which correspond to the command's actions and checks) and the
 * functions in defined in <code>CrPsInCmdDumSample1Ctrl.h</code> (which
 * control the behaviour of the command's actions and checks).
 *
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This file is part of the PUS Extension of the CORDET Framework.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#include "CrPsInCmdDumSample1Ctrl.h"
#include "CrPsInCmdDumSample1.h"

#include <stdlib.h>
/* Include configuration files */
#include "CrFwCmpData.h"
/* Include framework files */
#include "CrFwConstants.h"
#include "InCmd/CrFwInCmd.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "BaseCmp/CrFwInitProc.h"
#include "BaseCmp/CrFwResetProc.h"
#include "BaseCmp/CrFwDummyExecProc.h"
#include "OutFactory/CrFwOutFactory.h"
#include "Pckt/CrFwPckt.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include FW Profile files */
#include "FwPrConfig.h"
#include "FwPrDCreate.h"
#include "FwSmConfig.h"
#include "FwSmDCreate.h"
#include "FwPrCore.h"

/** The Validity Flag. */
static CrFwBool_t validityFlag;

/** The InCommand type as computed in the Validity Check */
static CrFwServType_t servType = 0;

/** The Ready Flag. */
static CrFwBool_t readyFlag;

/** The Start Action Outcome. */
static CrFwOutcome_t startOutcome;

/** The Progress Action Outcome. */
static CrFwOutcome_t progressOutcome;

/** The Progress Action Completion Outcome */
static CrFwBool_t progressCompletiongOutcome;

/** The Progress Step Flag. */
static CrFwBool_t progressStepFlag ;

/** The Abort Action Outcome. */
static CrFwOutcome_t abortOutcome = 0;

/** The Termination Action Outcome. */
static CrFwOutcome_t terminationOutcome;

/** The Start Action Counter. */
static CrFwCounterU1_t startCounter = 0;

/** The Progress Action Counter. */
static CrFwCounterU1_t progressCounter = 0;

/** The Termination Action Counter. */
static CrFwCounterU1_t terminationCounter = 0;

/** The abort Action Counter. */
static CrFwCounterU1_t abortCounter = 0;

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrPsInCmdDumSample1ValidityCheck(FwPrDesc_t prDesc) {
    CrFwPckt_t pckt;
    pckt = CrFwInCmdGetPcktFromPrDesc(prDesc);
    servType = CrFwPcktGetServType(pckt);
    return validityFlag;
}

/*-----------------------------------------------------------------------------------------*/
CrFwServType_t CrPsInCmdDumSample1GetType() {
    return servType;
}

/*-----------------------------------------------------------------------------------------*/
void CrPsInCmdDumSample1SetProgressStepFlag(CrFwBool_t flag) {
    progressStepFlag = flag;
}

/*-----------------------------------------------------------------------------------------*/
void CrPsInCmdDumSample1SetValidityFlag(CrFwBool_t flag) {
    validityFlag = flag;
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrPsInCmdDumSample1ReadyCheck(FwSmDesc_t smDesc) {
    (void)(smDesc);
    return readyFlag;
}

/*-----------------------------------------------------------------------------------------*/
void CrPsInCmdDumSample1SetReadyFlag(CrFwBool_t flag) {
    readyFlag = flag;
}

/*-----------------------------------------------------------------------------------------*/
void CrPsInCmdDumSample1StartAction(FwSmDesc_t smDesc) {
    CrFwSetSmOutcome(smDesc, startOutcome);
    startCounter++;
}

/*-----------------------------------------------------------------------------------------*/
void CrPsInCmdDumSample1SetStartActionOutcome(CrFwOutcome_t outcome) {
    startOutcome = outcome;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrPsInCmdDumSample1GetStartActionCounter() {
    return startCounter;
}

/*-----------------------------------------------------------------------------------------*/
void CrPsInCmdDumSample1ProgressAction(FwSmDesc_t smDesc) {
    CrFwProgressStepId_t progressStepId;
    CrFwSetSmOutcome(smDesc, progressOutcome);
    CrFwInCmdSetProgressActionCompleted(smDesc, progressCompletiongOutcome);
    progressStepId = CrFwInCmdGetProgressStepId(smDesc);
    if (progressStepFlag)
        CrFwInCmdSetProgressStepId(smDesc,progressStepId+1);

    progressCounter++;
}

/*-----------------------------------------------------------------------------------------*/
void CrPsInCmdDumSample1SetProgressActionOutcome(CrFwOutcome_t outcome) {
    progressOutcome = outcome;
}

void CrPsInCmdDumSample1SetProgressActionCompletionOutcome(CrFwBool_t outcome) {
    progressCompletiongOutcome = outcome;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrPsInCmdDumSample1GetProgressActionCounter() {
    return progressCounter;
}

/*-----------------------------------------------------------------------------------------*/
void CrPsInCmdDumSample1AbortAction(FwSmDesc_t smDesc) {
    CrFwSetSmOutcome(smDesc, abortOutcome);
    abortCounter++;
}

/*-----------------------------------------------------------------------------------------*/
void CrPsInCmdDumSample1SetAbortActionOutcome(CrFwOutcome_t outcome) {
    abortOutcome = outcome;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrPsInCmdDumSample1GetAbortActionCounter() {
    return abortCounter;
}

/*-----------------------------------------------------------------------------------------*/
void CrPsInCmdDumSample1TerminationAction(FwSmDesc_t smDesc) {
    CrFwSetSmOutcome(smDesc, terminationOutcome);
    terminationCounter++;
}

/*-----------------------------------------------------------------------------------------*/
void CrPsInCmdDumSample1SetTerminationActionOutcome(CrFwOutcome_t outcome) {
    terminationOutcome = outcome;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrPsInCmdDumSample1GetTerminationActionCounter() {
    return terminationCounter;

}

