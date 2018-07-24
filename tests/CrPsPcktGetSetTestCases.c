/**
 * @file CrPsGetSetTestCases.c
 * @ingroup PUSTestsuite
 *
 * @brief Implementation of the test cases for all Getter and Setter components.
 *
 * @author Christian Reimers <christian.reimersy@univie.ac.at>
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

/* Include system files */
#include <CrPsPkt.h>
#include <unistd.h>
#include <stdlib.h>

/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
/* Include configuration files */
#include "CrFwUserConstants.h"

/* Include framework files */
#include "CrFwCmpData.h"
#include "InStream/CrFwInStream.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutFactory/CrFwOutFactory.h"
#include "InFactory/CrFwInFactory.h"
#include "Pckt/CrFwPckt.h"

#include "CrFwTime.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"

#include "DataPool/CrPsDp.h"
#include "DataPool/CrPsDpTst.h"

#define MAX_CHAR 255
#define MAX_SHORT 65535
#define MAX_INT 4294967295u
#define MIN_VAL 0

/* ---------------------------------------------------------------------------------------------*/

CrFwBool_t CrPsPcktGetSetTestCase1() {

  CrFwPckt_t pckt, pckt2, pckt3;
  uint8_t  tim[6], timi[6];
  char    *pstart;
  uint16_t pcktsize = 30;

  CrFwSetAppErrCode(crNoAppErr);

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a Packet */
  pckt = CrFwPcktMake(pcktsize);

  /*test all TC header Getter and Setter*/
  setTcHeaderPcktVersionNmb(pckt, 0);
  if (getTcHeaderPcktVersionNmb(pckt) != 0) 
    return 0; 

  setTcHeaderPcktVersionNmb(pckt, 7);
  if (getTcHeaderPcktVersionNmb(pckt) != 7) 
    return 0;

  setTcHeaderPcktType(pckt, 0);
  if (getTcHeaderPcktType(pckt) != 0) 
    return 0; 
  setTcHeaderPcktType(pckt, 1);
  if (getTcHeaderPcktType(pckt) != 1) 
    return 0; 

  setTcHeaderSecHeaderFlag(pckt, 0);
  if (getTcHeaderSecHeaderFlag(pckt) != 0) 
    return 0; 
  setTcHeaderSecHeaderFlag(pckt, 1);
  if (getTcHeaderSecHeaderFlag(pckt) != 1) 
    return 0; 

  setTcHeaderAPID(pckt, 0);
  if (getTcHeaderAPID(pckt) != 0) 
    return 0; 
  setTcHeaderAPID(pckt, 2047);
  if (getTcHeaderAPID(pckt) != 2047) 
    return 0; 

  setTcHeaderSeqFlags(pckt, 0);
  if (getTcHeaderSeqFlags(pckt) != 0) 
    return 0; 
  setTcHeaderSeqFlags(pckt, 3);
  if (getTcHeaderSeqFlags(pckt) != 3) 
    return 0; 

  setTcHeaderSeqCount(pckt, 0);
  if (getTcHeaderSeqCount(pckt) != 0) 
    return 0; 
  setTcHeaderSeqCount(pckt, 16383);
  if (getTcHeaderSeqCount(pckt) != 16383) 
    return 0; 

  setTcHeaderPcktDataLen(pckt, 0);
  if (getTcHeaderPcktDataLen(pckt) != 0) 
    return 0; 
  setTcHeaderPcktDataLen(pckt, MAX_SHORT);
  if (getTcHeaderPcktDataLen(pckt) != MAX_SHORT) 
    return 0; 

  setTcHeaderPUSVersion(pckt, 0);
  if (getTcHeaderPUSVersion(pckt) != 0) 
    return 0; 
  setTcHeaderPUSVersion(pckt, 15);
  if (getTcHeaderPUSVersion(pckt) != 15) 
    return 0; 

  setTcHeaderAckAccFlag(pckt, 0);
  if (getTcHeaderAckAccFlag(pckt) != 0) 
    return 0; 
  setTcHeaderAckAccFlag(pckt, 1);
  if (getTcHeaderAckAccFlag(pckt) != 1) 
    return 0; 

  setTcHeaderAckStartFlag(pckt, 0);
  if (getTcHeaderAckStartFlag(pckt) != 0) 
    return 0; 
  setTcHeaderAckStartFlag(pckt, 1);
  if (getTcHeaderAckStartFlag(pckt) != 1) 
    return 0; 

  setTcHeaderAckProgFlag(pckt, 0);
  if (getTcHeaderAckProgFlag(pckt) != 0) 
    return 0; 
  setTcHeaderAckProgFlag(pckt, 1);
  if (getTcHeaderAckProgFlag(pckt) != 1) 
    return 0; 

  setTcHeaderAckTermFlag(pckt, 0);
  if (getTcHeaderAckTermFlag(pckt) != 0) 
    return 0; 
  setTcHeaderAckTermFlag(pckt, 1);
  if (getTcHeaderAckTermFlag(pckt) != 1) 
    return 0; 

  setTcHeaderServType(pckt, 0);
  if (getTcHeaderServType(pckt) != 0) 
    return 0; 
  setTcHeaderServType(pckt, MAX_CHAR);
  if (getTcHeaderServType(pckt) != MAX_CHAR) 
    return 0; 

  setTcHeaderServSubType(pckt, 0);
  if (getTcHeaderServSubType(pckt) != 0) 
    return 0; 
  setTcHeaderServSubType(pckt, MAX_CHAR);
  if (getTcHeaderServSubType(pckt) != MAX_CHAR) 
    return 0; 

  setTcHeaderSrcId(pckt, 0);
  if (getTcHeaderSrcId(pckt) != 0) 
    return 0; 

  setTcHeaderSrcId(pckt, MAX_CHAR);
  if (getTcHeaderSrcId(pckt) != MAX_CHAR) 
    return 0; 

  /*release packet and create a new one!*/
  CrFwPcktRelease(pckt);

  /* Allocate a Packet */
  pckt2 = CrFwPcktMake(pcktsize);

  /* Check that only one packet is allocated*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /*test all TM header Getter and Setter*/
  setTmHeaderPcktVersionNmb(pckt2, 0);
  if (getTmHeaderPcktVersionNmb(pckt2) != 0) 
    return 0; 
  setTmHeaderPcktVersionNmb(pckt, 7);
  if (getTmHeaderPcktVersionNmb(pckt2) != 7) 
    return 0; 

  setTmHeaderPcktType(pckt2, 0);
  if (getTmHeaderPcktType(pckt2) != 0) 
    return 0; 
  setTmHeaderPcktType(pckt2, 1);
  if (getTmHeaderPcktType(pckt2) != 1) 
    return 0; 

  setTmHeaderSecHeaderFlag(pckt2, 0);
  if (getTmHeaderSecHeaderFlag(pckt2) != 0) 
    return 0; 
  setTmHeaderSecHeaderFlag(pckt2, 1);
  if (getTmHeaderSecHeaderFlag(pckt2) != 1) 
    return 0; 

  setTmHeaderAPID(pckt2, 0);
  if (getTmHeaderAPID(pckt2) != 0) 
    return 0; 
  setTmHeaderAPID(pckt2, 2047);
  if (getTmHeaderAPID(pckt2) != 2047) 
    return 0; 

  setTmHeaderSeqFlags(pckt2, 0);
  if (getTmHeaderSeqFlags(pckt2) != 0) 
    return 0; 
  setTmHeaderSeqFlags(pckt2, 3);
  if (getTmHeaderSeqFlags(pckt2) != 3) 
    return 0; 

  setTmHeaderSeqCount(pckt2, 0);
  if (getTmHeaderSeqCount(pckt2) != 0) 
    return 0; 
  setTmHeaderSeqCount(pckt2, 16383);
  if (getTmHeaderSeqCount(pckt2) != 16383) 
    return 0; 

  setTmHeaderPcktDataLen(pckt2, 0);
  if (getTmHeaderPcktDataLen(pckt2) != 0) 
    return 0; 
  setTmHeaderPcktDataLen(pckt2, MAX_SHORT);
  if (getTmHeaderPcktDataLen(pckt2) != MAX_SHORT) 
    return 0; 

  setTmHeaderPUSVersion(pckt2, 0);
  if (getTmHeaderPUSVersion(pckt2) != 0) 
    return 0; 
  setTmHeaderPUSVersion(pckt2, 15);
  if (getTmHeaderPUSVersion(pckt2) != 15) 
    return 0; 

  setTmHeaderSpaceTimeRefStatus(pckt2, 0);
  if (getTmHeaderSpaceTimeRefStatus(pckt2) != 0) 
    return 0; 
  setTmHeaderSpaceTimeRefStatus(pckt2, 15);
  if (getTmHeaderSpaceTimeRefStatus(pckt2) != 15) 
    return 0; 

  setTmHeaderServType(pckt2, 0);
  if (getTmHeaderServType(pckt2) != 0) 
    return 0; 
  setTmHeaderServType(pckt2, MAX_CHAR);
  if (getTmHeaderServType(pckt2) != MAX_CHAR) 
    return 0; 

  setTmHeaderServSubType(pckt2, 0);
  if (getTmHeaderServSubType(pckt2) != 0) 
    return 0; 
  setTmHeaderServSubType(pckt2, MAX_CHAR);
  if (getTmHeaderServSubType(pckt2) != MAX_CHAR) 
    return 0; 

  setTmHeaderDestId(pckt2, 0);
  if (getTmHeaderDestId(pckt2) != 0) 
    return 0; 
  setTmHeaderDestId(pckt2, MAX_CHAR);
  if (getTmHeaderDestId(pckt2) != MAX_CHAR) 
    return 0; 

  tim[0] = 0;
  tim[1] = 0;
  tim[2] = 0;
  tim[3] = 0;
  tim[4] = 0;
  tim[5] = 0;

  setTmHeaderTime(pckt2, tim);
  getTmHeaderTime(pckt2, timi);
  if (memcmp(tim, timi, sizeof(tim))) 
    return 0; 

  tim[0] = MAX_CHAR;
  tim[1] = MAX_CHAR;
  tim[2] = MAX_CHAR;
  tim[3] = MAX_CHAR;
  tim[4] = MAX_CHAR;
  tim[5] = MAX_CHAR;

  setTmHeaderTime(pckt2, tim);
  getTmHeaderTime(pckt2, timi);
  if (memcmp(tim, timi, sizeof(tim))) 
    return 0; 

  /*release packet and create a new one!*/
  CrFwPcktRelease(pckt2);
  pckt3 = CrFwPcktMake(pcktsize);

  /* Check remaining getter and setter functions for header information */
  CrFwPcktSetCmdRepType(pckt3,crCmdType);
  if (CrFwPcktGetCmdRepType(pckt3) != crCmdType) 
    return 0;

  CrFwPcktSetCmdRepType(pckt3,crRepType);
  if (CrFwPcktGetCmdRepType(pckt3) != crRepType)
    return 0;

  if (CrFwPcktGetLength(pckt3) != pcktsize) 
    return 0;

  CrFwPcktSetCmdRepId(pckt3,1);
  if (CrFwPcktGetCmdRepId(pckt3) != 0) 
    return 0;

  CrFwPcktSetSeqCnt(pckt3,0);
  if (CrFwPcktGetSeqCnt(pckt3) != 0) 
    return 0;

  CrFwPcktSetServType(pckt3,17);
  if (CrFwPcktGetServType(pckt3) != 17) 
    return 0;

  CrFwPcktSetServSubType(pckt3,1);
  if (CrFwPcktGetServSubType(pckt3) != 1) 
    return 0;

  CrFwPcktSetDiscriminant(pckt3,0);
  if (CrFwPcktGetDiscriminant(pckt3) != 0) 
    return 0; 

  CrFwPcktSetSrc(pckt3,12);
  if (CrFwPcktGetSrc(pckt3) != 12) 
    return 0;
  
  /* Turn the packet into a command packet */
  CrFwPcktSetCmdRepType(pckt3,crCmdType);

  /* Check the command acknowledge bits */
  CrFwPcktSetAckLevel(pckt3,1,0,0,0);
  if (CrFwPcktIsAcceptAck(pckt3) != 1) 
    return 0;
  if (CrFwPcktIsStartAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsProgressAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsTermAck(pckt3) != 0) 
    return 0;


  CrFwPcktSetAckLevel(pckt3,0,1,0,0);
  if (CrFwPcktIsAcceptAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsStartAck(pckt3) != 1) 
    return 0;
  if (CrFwPcktIsProgressAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsTermAck(pckt3) != 0) 
    return 0;


  CrFwPcktSetAckLevel(pckt3,0,0,1,0);
  if (CrFwPcktIsAcceptAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsStartAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsProgressAck(pckt3) != 1) 
    return 0;
  if (CrFwPcktIsTermAck(pckt3) != 0) 
    return 0;


  CrFwPcktSetAckLevel(pckt3,0,0,0,1);
  if (CrFwPcktIsAcceptAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsStartAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsProgressAck(pckt3) != 0) 
    return 0;
  if (CrFwPcktIsTermAck(pckt3) != 1) 
    return 0;

  CrFwPcktSetGroup(pckt3,2);
  if (CrFwPcktGetGroup(pckt3) != 2) 
    return 0;

  pstart = CrFwPcktGetParStart(pckt3);
  CRFW_UNUSED(pstart);

  /*release packet */
  CrFwPcktRelease(pckt3);

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
	return 0;

  return 1;   
}



