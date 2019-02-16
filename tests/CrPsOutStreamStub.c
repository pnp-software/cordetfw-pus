/**
 * @file
 *
 * Implementation of OutStream stub.
 *
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This file is part of the CORDET Framework.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#include "CrPsOutStreamStub.h"
#include "CrFwRepErrStub.h"

/* Include configuration files */
#include "CrFwOutStreamUserPar.h"
#include "CrFwCmpData.h"

/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"

/* Include framework files */
#include "OutStream/CrFwOutStream.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "Pckt/CrFwPckt.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"

#include <stdlib.h>
#include <assert.h>

/** Size of ring buffer where the incoming packets are stored */
#define CR_PS_OUTSTREAMSTUB_N 10

/** Ring buffer where the incoming packets are stored */
static CrFwPckt_t ringBuffer[CR_PS_OUTSTREAMSTUB_N*CR_FW_MAX_PCKT_LENGTH];

/** Ring buffer pointer (pointer to the next free location in the ring buffer) */
static unsigned int ringBufferPtr = 0;

/** Counter incremented every time the packet hand-over operation is called */
static CrFwCounterU1_t pcktHandOverCnt = 0;

/** Return value of the packet hand-over operation */
static CrFwBool_t pcktHandOverFlag = 1;

/** Outcome of dummy check */
static CrFwBool_t checkFlag = 1;

/** Outcome of dummy action */
static CrFwBool_t actionFlag = 1;

/** Counter incremented by stub Shutdown Operation */
static CrFwCounterU1_t shutdownCnt = 0;

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsOutStreamStubPcktHandover(CrFwPckt_t pckt) {
	unsigned int i;

	pcktHandOverCnt++;

	if (pcktHandOverFlag == 1) {
	    for (i=0; i<CR_FW_MAX_PCKT_LENGTH; i++)
	        ringBuffer[ringBufferPtr*CR_FW_MAX_PCKT_LENGTH+i] = pckt[i];
	    ringBufferPtr++;
	    if (ringBufferPtr == CR_PS_OUTSTREAMSTUB_N)
	        ringBufferPtr = 0;
	}

	return pcktHandOverFlag;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwPckt_t CrPsOutStreamStubGetPckt(unsigned int i) {
    assert(i < (CR_PS_OUTSTREAMSTUB_N+1));
    if (ringBufferPtr > i)
        return &ringBuffer[(ringBufferPtr-i-1)*CR_FW_MAX_PCKT_LENGTH];

    return &ringBuffer[(CR_PS_OUTSTREAMSTUB_N-(i-ringBufferPtr))*CR_FW_MAX_PCKT_LENGTH];
}

/* ---------------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrPsOutStreamStubGetHandoverCnt() {
	return pcktHandOverCnt;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwCounterU1_t CrPsOutStreamStubGetShutdownCnt() {
	return shutdownCnt;
}

/* ---------------------------------------------------------------------------------------------*/
void CrPsOutStreamStubSetHandoverFlag(CrFwBool_t flag) {
	pcktHandOverFlag = flag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrPsOutStreamStubDummyCheck(FwPrDesc_t prDesc) {
	CrFwCmpData_t* outStreamData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	outStreamData->outcome = (CrFwOutcome_t)checkFlag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrPsOutStreamStubSetCheckFlag(CrFwBool_t flag) {
	checkFlag = flag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrPsOutStreamStubInitAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* outStreamBaseData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	CrFwOutStreamData_t* cmpSpecificData = (CrFwOutStreamData_t*)outStreamBaseData->cmpSpecificData;
	if (cmpSpecificData->seqCnt == NULL)
		CrFwOutStreamDefInitAction(prDesc);
	outStreamBaseData->outcome = (CrFwOutcome_t)actionFlag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrPsOutStreamStubConfigAction(FwPrDesc_t prDesc) {
	CrFwCmpData_t* outStreamData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	CrFwOutStreamDefConfigAction(prDesc);
	outStreamData->outcome = (CrFwOutcome_t)actionFlag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrPsOutStreamStubSetActionFlag(CrFwBool_t flag) {
	actionFlag = flag;
}

/* ---------------------------------------------------------------------------------------------*/
void CrPsOutStreamStubShutdown(FwSmDesc_t smDesc) {
	shutdownCnt++;
	CrFwOutStreamDefShutdownAction(smDesc);
}
