/**
 * @file CrFwPckt.c
 * @ingroup PUSTestsuite
 * @ingroup PUSTestconfig 
 *
 * Default implementation of the packet interface of <code>CrFwPckt.h</code>.
 * The implementation of this interface is one of the adaptation points of the
 * CORDET Framework.
 *
 * This interface provides functions to create and release packets and to access
 * the attributes of the command and report headers.
 * The getter and setter functions for the header attributes are implemented in
 * accordance with the "usual" layout for PUS packet headers.
 * The functions to create and release packets dynamically are implemented as follows:
 *
 * - Memory is pre-allocated for a predefined number of packets of fixed size.
 * - Packets can be either "in use" or "not in use".
 * - A packet is in use if it has been requested through a call to <code>::CrFwPcktMake</code>
 *   and has not yet been released through a call to <code>::CrFwPcktRelease</code>.
 * - The implementation provided in this file uses global data structures to hold
 *   the pool of pre-allocated packets.
 * .
 *
 * This implementation is provided for the Test Suite of the PUS Extension of the
 * CORDET Framework.
 * Most applications will want to provide a version adapted to their needs.
 *
 * The following notes apply to the attribute getter and setter functions:
 * - Standard PUS attributes are accessed through the functions defined in
 *   <code>CrPsPck.h</code>
 * - The discriminant is only defined for packets in services 1, 3, 5 and 13.
 *   The discriminant is assumed to have the same position in all packets of the
 *   same type
 * - The report identifier is not modelled (its setter function does nothing and the
 *   getter function returns zero)
 * - The CORDET Group attribute is treated as equivalent to the PUS PCAT attribute
 *   (the 4 least significant bits of the APID)
 * - The destination of a command is mapped to the PID part of the APID
 * - The source of a report is mapped to the PID part of the APID
 * .
 *
 * The setter functions for the packet attributes assume that the packet length is
 * adequate to hold the attributes.
 * Compliance with this constraint is not checked by the setter functions.
 * Its violation may result in memory corruption.
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

#include "Pckt/CrPsPckt.h"
#include "CrFwUserConstants.h"
#include "CrFwConstants.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "Pckt/CrFwPckt.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "CrPsServTypeId.h"
#include "Pckt/CrPsPcktEvt.h"
#include "Pckt/CrPsPcktVer.h"

#include <stdlib.h>

/**
 * The array holding the packets.
 * Packets are stored in this array in blocks of size CR_FW_MAX_PCKT_LENGTH.
 */
static char pcktArray[CR_FW_MAX_NOF_PCKTS*CR_FW_MAX_PCKT_LENGTH];

/**
 * The array holding the "in use" status of the packets.
 * A packet is in use if it has been requested through a call to the "make" function
 * and has not yet been released through a call to the "release" function.
 */
static CrFwBool_t pcktInUse[CR_FW_MAX_NOF_PCKTS] = {0};

/** The number of currently allocated packets. */
static CrFwCounterU2_t nOfAllocatedPckts = 0;

/*-----------------------------------------------------------------------------------------*/
CrFwPckt_t CrFwPcktMake(CrFwPcktLength_t pcktLength) {
	CrFwCounterU2_t i;
	if (pcktLength > CR_FW_MAX_PCKT_LENGTH) {
		CrFwSetAppErrCode(crPcktAllocationFail);
		return NULL;
	}

	if (pcktLength < 1) {
		CrFwSetAppErrCode(crPcktAllocationFail);
		return NULL;
	}

	for (i=0; i<CR_FW_MAX_NOF_PCKTS; i++) {
		if (pcktInUse[i] == 0) {
			pcktInUse[i] = 1;
			setTmHeaderPcktDataLen((&pcktArray[i*CR_FW_MAX_PCKT_LENGTH]), pcktLength);
			nOfAllocatedPckts++;
			return (&pcktArray[i*CR_FW_MAX_PCKT_LENGTH]);
		}
	}
	CrFwSetAppErrCode(crPcktAllocationFail);
	return NULL;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktRelease(CrFwPckt_t pckt) {
	CrFwCounterU2_t i;

	for (i=0; i<CR_FW_MAX_NOF_PCKTS; i++) {
		if (pckt == &pcktArray[i*CR_FW_MAX_PCKT_LENGTH]) {
			if (pcktInUse[i] == 0) {
				CrFwSetAppErrCode(crPcktRelErr);
			} else {
				nOfAllocatedPckts--;
				pcktInUse[i] = 0;
			}
			return;
		}
	}

	CrFwSetAppErrCode(crPcktRelErr);
	return;
}

/*-----------------------------------------------------------------------------------------*/
CrFwBool_t CrFwPcktIsAvail(CrFwPcktLength_t pcktLength) {
	CrFwCounterU2_t i;

	if (pcktLength > CR_FW_MAX_PCKT_LENGTH)
		return 0;

	if (pcktLength < 1)
		return 0;

	for (i=0; i<CR_FW_MAX_NOF_PCKTS; i++) {
		if (pcktInUse[i] == 0)
			return 1;
	}
	return 0;
}

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU2_t CrFwPcktGetNOfAllocated() {
	return nOfAllocatedPckts;
}

/*-----------------------------------------------------------------------------------------*/
CrFwPcktLength_t CrFwPcktGetMaxLength() {
	return CR_FW_MAX_PCKT_LENGTH;
}

/*-----------------------------------------------------------------------------------------*/
CrFwPcktLength_t CrFwPcktGetLength(CrFwPckt_t pckt) {
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
		return (CrFwPcktLength_t) getTmHeaderPcktDataLen(pckt);
	else
		return (CrFwPcktLength_t) getTcHeaderPcktDataLen(pckt);
}

/*-----------------------------------------------------------------------------------------*/
CrFwCmdRepType_t CrFwPcktGetCmdRepType(CrFwPckt_t p){
	if (getTcHeaderPcktType(p) == 0)
		return crRepType;
	else
		return crCmdType;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetCmdRepType(CrFwPckt_t pckt, CrFwCmdRepType_t type) {
	if (type == crRepType)
		setTmHeaderPcktType(pckt, 0);
	else
		setTcHeaderPcktType(pckt, 1);
}

/*-----------------------------------------------------------------------------------------*/
CrFwInstanceId_t CrFwPcktGetCmdRepId(CrFwPckt_t pckt) {
	/* Field not present */
	(void)(pckt);
	return 0;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetCmdRepId(CrFwPckt_t pckt, CrFwInstanceId_t id) {
	/* Field not present */
	(void)(pckt);
	(void)(id);
}

/*-----------------------------------------------------------------------------------------*/
CrFwSeqCnt_t CrFwPcktGetSeqCnt(CrFwPckt_t pckt) {
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
		return (CrFwSeqCnt_t) getTmHeaderSeqCount(pckt);
	else
		return (CrFwSeqCnt_t) getTcHeaderSeqCount(pckt);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetSeqCnt(CrFwPckt_t pckt, CrFwSeqCnt_t seqCnt) {
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
		setTmHeaderSeqCount(pckt, seqCnt);
	else
		setTcHeaderSeqCount(pckt, seqCnt);
}

/*-----------------------------------------------------------------------------------------*/
CrFwTimeStamp_t CrFwPcktGetTimeStamp(CrFwPckt_t pckt) {
	CrFwTimeStamp_t time;
	getTmHeaderTime(pckt, &time);
	return time;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetTimeStamp(CrFwPckt_t pckt, CrFwTimeStamp_t timeStamp) {
	setTmHeaderTime(pckt, &timeStamp);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetServType(CrFwPckt_t pckt, CrFwServType_t servType) {
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
		setTmHeaderServType(pckt, servType);
	else
		setTcHeaderServType(pckt, servType);
}

/*-----------------------------------------------------------------------------------------*/
CrFwServType_t CrFwPcktGetServType(CrFwPckt_t pckt) {
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
		return (CrFwServSubType_t) getTmHeaderServType(pckt);
	else
		return (CrFwServSubType_t) getTcHeaderServType(pckt);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetServSubType(CrFwPckt_t pckt, CrFwServSubType_t servSubType) {
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
		setTmHeaderServSubType(pckt, servSubType);
	else
		setTcHeaderServSubType(pckt, servSubType);
}

/*-----------------------------------------------------------------------------------------*/
CrFwServSubType_t CrFwPcktGetServSubType(CrFwPckt_t pckt) {
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
		return (CrFwServSubType_t) getTmHeaderServSubType(pckt);
	else
		return (CrFwServSubType_t) getTcHeaderServSubType(pckt);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetDiscriminant(CrFwPckt_t pckt, CrFwDiscriminant_t discriminant) {
	CrFwServType_t servType;

	servType = CrFwPcktGetServType(pckt);
	switch (servType) {
		case VER_TYPE:
		    //setDpVerFailCode(pckt, discriminant);
			break;
		case 3:
			// setHkCreateCmdRepStrucId(pckt, discriminant);
			break;
		case EVT_TYPE:
			//setEvtRep1EventId(pckt, discriminant);
			break;
		case 13:
			// TBD: Message Identifier
		default:
			break;
	}
}

/*-----------------------------------------------------------------------------------------*/
CrFwDiscriminant_t CrFwPcktGetDiscriminant(CrFwPckt_t pckt) {
	CrFwServType_t servType;
	CrFwServSubType_t servSubType;

	servType = CrFwPcktGetServType(pckt);
	servSubType = CrFwPcktGetServSubType(pckt);
	switch (servType) {
		case VER_TYPE:
		    switch (servSubType) {
		      case VERFAILEDACCREP_STYPE:
		        return getVerFailedAccRepTcFailCode(pckt);
		      case VERFAILEDSTARTREP_STYPE:
		        return getVerFailedStartRepTcFailCode(pckt);
		      case VERFAILEDPRGRREP_STYPE:
		        return getVerFailedPrgrRepTcFailCode(pckt);
		      case VERFAILEDTERMREP_STYPE:
		        return getVerFailedTermRepTcFailCode(pckt);
		      case VERFAILEDROUTINGREP_STYPE:
		        return getVerFailedRoutingRepTcDisc(pckt);
		      default:
		        break;
		    }
		    break;
		case 3:
			// return getHkCreateCmdRepStrucId(pckt);
		case EVT_TYPE:
		    switch (servSubType) {
		      case EVTREP1_STYPE:
		         return getEvtRep1EventId(pckt);
              case EVTREP2_STYPE:
                 return getEvtRep2EventId(pckt);
              case EVTREP3_STYPE:
                 return getEvtRep3EventId(pckt);
              case EVTREP4_STYPE:
                 return getEvtRep4EventId(pckt);
              default:
                 break;
		    }
		    break;
		case 13:
			// TBD: Message Identifier
		default:
			break;
	}
	return 0;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetDest(CrFwPckt_t pckt, CrFwDestSrc_t dest) {
	CrPsElevenBit_t apid;

	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
		setTmHeaderDestId(pckt, dest);
	else {
		apid = getTcHeaderAPID(pckt);
		apid = 0x000F & apid;   /* Remove PID part of APID */
		apid = apid + dest*16;	/* Set PID part of APID equal to destination */
		setTcHeaderAPID(pckt,apid);
	}
}

/*-----------------------------------------------------------------------------------------*/
CrFwDestSrc_t CrFwPcktGetDest(CrFwPckt_t pckt) {
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
		return (CrFwDestSrc_t) getTmHeaderDestId(pckt);
	else
		return (CrFwDestSrc_t) (getTcHeaderAPID(pckt)>>4);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetSrc(CrFwPckt_t pckt, CrFwDestSrc_t src) {
	CrPsElevenBit_t apid;

	if (CrFwPcktGetCmdRepType(pckt) == crCmdType)
		setTcHeaderSrcId(pckt, src);
	else {
		apid = getTmHeaderAPID(pckt);
		apid = 0x000F & apid;   /* Remove PID part of APID */
		apid = apid + src*16;	/* Set PID part of APID equal to destination */
		setTmHeaderAPID(pckt, apid);
	}
}

/*-----------------------------------------------------------------------------------------*/
CrFwDestSrc_t CrFwPcktGetSrc(CrFwPckt_t pckt) {
	if (CrFwPcktGetCmdRepType(pckt) == crCmdType)
		return (CrFwDestSrc_t) getTcHeaderSrcId(pckt);
	else
		return (CrFwDestSrc_t) (getTmHeaderAPID(pckt)>>4);
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetAckLevel(CrFwPckt_t pckt, CrFwBool_t accept, CrFwBool_t start,
                         CrFwBool_t progress, CrFwBool_t term) {
	if (CrFwPcktGetCmdRepType(pckt) == crCmdType) {
		setTcHeaderAckAccFlag(pckt, accept);
		setTcHeaderAckStartFlag(pckt, start);
		setTcHeaderAckProgFlag(pckt, progress);
		setTcHeaderAckTermFlag(pckt, term);
	}
}

/*-----------------------------------------------------------------------------------------*/
/** Implementation implicitly assumes that the packet holds a command */
CrFwBool_t CrFwPcktIsAcceptAck(CrFwPckt_t pckt) {
	return (CrFwBool_t) getTcHeaderAckAccFlag(pckt);
}

/*-----------------------------------------------------------------------------------------*/
/** Implementation implicitly assumes that the packet holds a command */
CrFwBool_t CrFwPcktIsStartAck(CrFwPckt_t pckt) {
	return (CrFwBool_t) getTcHeaderAckStartFlag(pckt);
}

/*-----------------------------------------------------------------------------------------*/
/** Implementation implicitly assumes that the packet holds a command */
CrFwBool_t CrFwPcktIsProgressAck(CrFwPckt_t pckt) {
	return (CrFwBool_t) getTcHeaderAckProgFlag(pckt);
}

/*-----------------------------------------------------------------------------------------*/
/** Implementation implicitly assumes that the packet holds a command */
CrFwBool_t CrFwPcktIsTermAck(CrFwPckt_t pckt) {
	return (CrFwBool_t) getTcHeaderAckTermFlag(pckt);
}

/*-----------------------------------------------------------------------------------------*/
char* CrFwPcktGetParStart(CrFwPckt_t pckt) {
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
		return (CrFwPckt_t) &pckt[sizeof(TmHeader_t)];
	else
		return (CrFwPckt_t) &pckt[sizeof(TcHeader_t)];
}

/*-----------------------------------------------------------------------------------------*/
CrFwPcktLength_t CrFwPcktGetParLength(CrFwPckt_t pckt) {
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
		return (CrFwPcktLength_t) (CrFwPcktGetLength(pckt)-sizeof(TmHeader_t));
	else
		return (CrFwPcktLength_t) (CrFwPcktGetLength(pckt)-sizeof(TcHeader_t));
}

/*-----------------------------------------------------------------------------------------*/
void CrFwPcktSetGroup(CrFwPckt_t pckt, CrFwGroup_t group) {
	CrPsElevenBit_t apid;

	if (CrFwPcktGetCmdRepType(pckt) == crRepType) {
		apid = getTmHeaderAPID(pckt);
		apid = apid & (0x7f0 + group);
		setTmHeaderAPID(pckt, apid);
	}
	else {
		apid = getTmHeaderAPID(pckt);
		apid = apid & (0x7f0 + group);
		setTmHeaderAPID(pckt, apid);
	}
}

/*-----------------------------------------------------------------------------------------*/
CrFwGroup_t CrFwPcktGetGroup(CrFwPckt_t pckt) {
	if (CrFwPcktGetCmdRepType(pckt) == crRepType)
		return (getTmHeaderAPID(pckt) % 16);
	else
		return (getTcHeaderAPID(pckt) % 16);
}




