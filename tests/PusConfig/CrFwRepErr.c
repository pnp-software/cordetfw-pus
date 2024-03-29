/**
 * @file CrFwRepErr.c
 * @ingroup man_config
 *
 * Implementation of the error reporting interface of <code>CrFwRepErr.h</code>
 * for the PUS Extension of the CORDET Framework.
 * The implementation of this interface is one of the adaptation points of the
 * CORDET Framework.
 *
 * This implementation does the following: for each error condition it generates
 * a service 5 event with the exception of the "Instance Id and Destination"
 * error condition for which it generates a (1,10) report.
 *
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @author Christian Reimers <christian.reimers@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 *
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#include <stdlib.h>
#include <stdio.h>

/* Include Framework Files */
#include "CrFwConstants.h"
#include "CrFwRepErr.h"
#include "FwPrCore.h"

/* Include Configuration Files */
#include "CrFwRepErrStub.h"
#include "Ver/CrPsVerConfig.h"

/** The size of the error report array */
#define CR_FW_ERR_REP_ARRAY_SIZE 100

/** The size in number of bytes of the parameter part of an error report */
#define CR_FW_ERR_REP_PAR_SIZE 12

/**
 * The structure for an error report.
 * Note that error reports may have a variable number of error parameters
 * of various types (the number and type and parameters depends on the type
 * of error).
 * This implementation assumes that the parameters allocated to the error
 * report do not take more than CR_FW_ERR_REP_PAR_SIZE bytes of memory.
 */
typedef struct {
	/** The error code */
	CrFwRepErrCode_t errCode;
	/** The type identifier of the component which generates the error report */
	CrFwTypeId_t typeId;
	/** The instance identifier of the component which generates the error report */
	CrFwInstanceId_t instanceId;
	/** The parameters associated to the error report */
	CrFwCounterU1_t par[CR_FW_ERR_REP_PAR_SIZE];
} CrFwErrRep_t;

/** The error report array */
static CrFwErrRep_t errRepArray[CR_FW_ERR_REP_ARRAY_SIZE];

/** The position in the error report array at which the next error report will be written */
static CrFwCounterU2_t errRepPos = 0;

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU2_t CrFwRepErrStubGetPos() {
	return errRepPos;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwRepErrStubReset() {
	errRepPos = 0;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwRepErr(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId, CrFwInstanceId_t instanceId) {
	CrFwCounterU1_t i;

	errRepArray[errRepPos].errCode = errCode;
	errRepArray[errRepPos].instanceId = instanceId;
	errRepArray[errRepPos].typeId = typeId;
	for (i=0; i<CR_FW_ERR_REP_PAR_SIZE; i++)
		errRepArray[errRepPos].par[i] = 0;

	errRepPos = (CrFwCounterU2_t)((errRepPos + 1) % CR_FW_ERR_REP_ARRAY_SIZE);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwRepErrDestSrc(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId, CrFwInstanceId_t instanceId,
                       CrFwDestSrc_t destSrc) {
	CrFwCounterU1_t i;

	errRepArray[errRepPos].errCode = errCode;
	errRepArray[errRepPos].instanceId = instanceId;
	errRepArray[errRepPos].typeId = typeId;
	errRepArray[errRepPos].par[0] = destSrc;
	for (i=1; i<CR_FW_ERR_REP_PAR_SIZE; i++)
		errRepArray[errRepPos].par[i] = 0;

	errRepPos = (CrFwCounterU2_t)((errRepPos + 1) % CR_FW_ERR_REP_ARRAY_SIZE);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwRepErrInstanceIdAndDest(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId,
                                 CrFwInstanceId_t instanceId, CrFwInstanceId_t secondaryInstanceId,
								 CrFwDestSrc_t dest, CrFwPckt_t pckt) {
    FwPrDesc_t serv1Pr;

    CrPsVerConfigSetPrData(0, 0, 0, 0, 0, NULL, pckt);
    serv1Pr = CrPsVerConfigGetPcktReroutingFail();
    FwPrRun(serv1Pr);
}


/*-----------------------------------------------------------------------------------------*/
void CrFwRepErrGroup(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId, CrFwInstanceId_t instanceId,
                     CrFwGroup_t group) {
	CrFwCounterU1_t i;

	errRepArray[errRepPos].errCode = errCode;
	errRepArray[errRepPos].instanceId = instanceId;
	errRepArray[errRepPos].typeId = typeId;
	errRepArray[errRepPos].par[0] = group;
	for (i=1; i<CR_FW_ERR_REP_PAR_SIZE; i++)
		errRepArray[errRepPos].par[i] = 0;

	errRepPos = (CrFwCounterU2_t)((errRepPos + 1) % CR_FW_ERR_REP_ARRAY_SIZE);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwRepErrSeqCnt(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId, CrFwInstanceId_t instanceId,
                      CrFwSeqCnt_t expSeqCnt, CrFwSeqCnt_t actSeqCnt, CrFwPckt_t pckt) {
	CrFwCounterU1_t i;
	CrFwSeqCnt_t temp;

	errRepArray[errRepPos].errCode = errCode;
	errRepArray[errRepPos].instanceId = instanceId;
	errRepArray[errRepPos].typeId = typeId;
	temp = expSeqCnt;
	errRepArray[errRepPos].par[0] = temp % 256;
	temp = temp >> 8;
	errRepArray[errRepPos].par[1] = temp % 256;
	temp = temp >> 8;
	errRepArray[errRepPos].par[2] = temp % 256;
	temp = temp >> 8;
	errRepArray[errRepPos].par[3] = temp % 256;
	temp = actSeqCnt;
	errRepArray[errRepPos].par[4] = temp % 256;
	temp = temp >> 8;
	errRepArray[errRepPos].par[5] = temp % 256;
	temp = temp >> 8;
	errRepArray[errRepPos].par[6] = temp % 256;
	temp = temp >> 8;
	errRepArray[errRepPos].par[7] = temp % 256;

	for (i=8; i<CR_FW_ERR_REP_PAR_SIZE; i++)
		errRepArray[errRepPos].par[i] = pckt[i];

	errRepPos = (CrFwCounterU2_t)((errRepPos + 1) % CR_FW_ERR_REP_ARRAY_SIZE);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwRepErrInstanceIdAndOutcome(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId,
                                    CrFwInstanceId_t instanceId, CrFwInstanceId_t secondaryInstanceId, CrFwOutcome_t outcome) {
	CrFwCounterU1_t i;

	errRepArray[errRepPos].errCode = errCode;
	errRepArray[errRepPos].instanceId = instanceId;
	errRepArray[errRepPos].typeId = typeId;
	errRepArray[errRepPos].par[0] = outcome;
	errRepArray[errRepPos].par[1] = (CrFwCounterU1_t)(secondaryInstanceId % 256);
	errRepArray[errRepPos].par[2] = (CrFwCounterU1_t)(secondaryInstanceId >> 8);
	for (i=3; i<CR_FW_ERR_REP_PAR_SIZE; i++)
		errRepArray[errRepPos].par[i] = 255;

	errRepPos = (CrFwCounterU2_t)((errRepPos + 1) % CR_FW_ERR_REP_ARRAY_SIZE);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwRepErrKind(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId,
                                    CrFwInstanceId_t instanceId, CrFwServType_t  servType,
									CrFwServSubType_t servSubType, CrFwDiscriminant_t disc) {
	CrFwCounterU1_t i;

	errRepArray[errRepPos].errCode = errCode;
	errRepArray[errRepPos].instanceId = instanceId;
	errRepArray[errRepPos].typeId = typeId;
	errRepArray[errRepPos].par[0] = (CrFwCounterU1_t)(servType % 256);;
	errRepArray[errRepPos].par[1] = (CrFwCounterU1_t)(servSubType % 256);
	errRepArray[errRepPos].par[2] = (CrFwCounterU1_t)(disc % 256);
	for (i=3; i<CR_FW_ERR_REP_PAR_SIZE; i++)
		errRepArray[errRepPos].par[i] = 255;

	errRepPos = (CrFwCounterU2_t)((errRepPos + 1) % CR_FW_ERR_REP_ARRAY_SIZE);
}
/*-----------------------------------------------------------------------------------------*/
CrFwRepErrCode_t CrFwRepErrStubGetErrCode(CrFwCounterU2_t errRepPos) {
	return errRepArray[errRepPos].errCode;
}

/*-----------------------------------------------------------------------------------------*/
CrFwTypeId_t CrFwRepErrStubGetTypeId(CrFwCounterU2_t errRepPos) {
	return errRepArray[errRepPos].typeId;
}

/*-----------------------------------------------------------------------------------------*/
CrFwInstanceId_t CrFwRepErrStubGetInstanceId(CrFwCounterU2_t errRepPos) {
	return errRepArray[errRepPos].instanceId;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU1_t* CrFwRepErrStubGetParArray(CrFwCounterU2_t errRepPos) {
	return errRepArray[errRepPos].par;
}

/*-----------------------------------------------------------------------------------------*/
CrFwDestSrc_t CrFwRepErrStubGetDest(CrFwCounterU2_t errRepPos) {
	return errRepArray[errRepPos].par[0];
}

/*-----------------------------------------------------------------------------------------*/
CrFwSeqCnt_t CrFwRepErrStubGetExpSeqCnt(CrFwCounterU2_t errRepPos) {
	return (CrFwSeqCnt_t)(errRepArray[errRepPos].par[0]+errRepArray[errRepPos].par[1]*256+
	        errRepArray[errRepPos].par[2]*(65536)+errRepArray[errRepPos].par[3]*(16777216));
}

/*-----------------------------------------------------------------------------------------*/
CrFwSeqCnt_t CrFwRepErrStubGetActualSeqCnt(CrFwCounterU2_t errRepPos) {
	return (CrFwSeqCnt_t)(errRepArray[errRepPos].par[4]+errRepArray[errRepPos].par[5]*256+
	        errRepArray[errRepPos].par[6]*(65536)+errRepArray[errRepPos].par[7]*(16777216));
}

/*-----------------------------------------------------------------------------------------*/
CrFwInstanceId_t CrFwRepErrStubGetSecondatyInstanceId(CrFwCounterU2_t errRepPos) {
	return (CrFwInstanceId_t)(errRepArray[errRepPos].par[1]+256*errRepArray[errRepPos].par[2]);
}

/*-----------------------------------------------------------------------------------------*/
CrFwOutcome_t CrFwRepErrStubGetOutcome(CrFwCounterU2_t errRepPos) {
	return errRepArray[errRepPos].par[0];
}

/*-----------------------------------------------------------------------------------------*/
void CrFwRepErrPckt(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId, CrFwInstanceId_t instanceId, CrFwPckt_t pckt) {
  CRFW_UNUSED(pckt);

  /* This function is called by the N1 node of the Packet Rerouting Failure Procedure */

  printf("CrFwRepErrPckt: error %d generated by component %d of type %d\n",errCode,instanceId,typeId);
  printf("                pckt: \n");
  return;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwRepErrRep(CrFwRepErrCode_t errCode, CrFwTypeId_t typeId, CrFwInstanceId_t instanceId, FwSmDesc_t rep) {
  CRFW_UNUSED(rep);
  printf("CrFwRepErrRep: error %d generated by component %d of type %d\n",errCode,instanceId,typeId);
  printf("               rep: \n");
  return;
}
