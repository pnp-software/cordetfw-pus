/**
 * @file CrPsTstTestCases.c
 * @ingroup PUSTestsuite
 *
 * @brief Implementation of test cases for the Test Service Components.
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

#include "CrPsTstTestCases.h"

/* Include FW Profile files */
#include "FwSmCore.h"
#include "FwSmConfig.h"


/* Include framework files */
#include "CrFwCmpData.h"
#include "OutRegistry/CrFwOutRegistry.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include "InCmd/CrFwInCmd.h"
#include "InFactory/CrFwInFactory.h"
#include "OutFactory/CrFwOutFactory.h"
#include "InLoader/CrFwInLoader.h"
#include "OutLoader/CrFwOutLoader.h"
#include "InLoader/CrFwInLoader.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "CrFwTime.h"

#include "CrFwUserConstants.h"
#include "CrFwOutFactoryUserPar.h"

#include "Tst/CrPsTstConfig.h"
#include "PcktFunctions/CrPsPcktTst.h"
#include "DataPool/CrPsDpTst.h"
#include "CrPsServTypeId.h"
#include "CrPsConstants.h"

/* Include system files */
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

CrFwTime_t cmd7s3TimeOut = 2;

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsTstTestCase1() {
  CrFwPckt_t pckt;
  FwSmDesc_t cmd17s3, rep17s2, rep17s4;
  CrFwPckt_t pcktCmd17s3, pcktRep17s4;
  FwSmDesc_t inFactory, outFactory;
  unsigned int nAllocatedCmd, nAllocatedRep;

  CrFwSetAppErrCode(crNoAppErr);
  nAllocatedCmd = CrFwInFactoryGetNOfAllocatedInCmd();
  nAllocatedRep = CrFwOutFactoryGetNOfAllocatedOutCmp();

  /* Instantiate and configure OutFactory and InFactory */
  outFactory = CrFwOutFactoryMake();
  inFactory = CrFwInFactoryMake();

  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  if (!CrFwCmpIsInConfigured(outFactory))
    return 0;

  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  if (!CrFwCmpIsInConfigured(inFactory))
    return 0;

   /* Create a (17,2) report and check its attributes */
  rep17s2 = CrFwOutFactoryMakeOutCmp(TST_TYPE, TSTAREYOUALIVEREP_STYPE, 0, 0);
  if (rep17s2 == NULL)
	  return 0;
  if (CrFwOutCmpGetServType(rep17s2) != 17)
	  return 0;
  if (CrFwOutCmpGetServSubType(rep17s2) != 2)
	  return 0;
  if (CrFwOutCmpGetDiscriminant(rep17s2) != 0)
	  return 0;

  /* Release (17,2) report */
  CrFwOutFactoryReleaseOutCmp(rep17s2);
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nAllocatedRep)
	  return 0;

  /* Check getter and setter functions for (17,3) command */
  pckt = CrFwPcktMake(20);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,3);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);
  CrFwPcktSetSeqCnt(pckt,2);

  cmd17s3 = CrFwInFactoryMakeInCmd(pckt);
  if (cmd17s3 == NULL)
	  return 0;

  pcktCmd17s3 = CrFwInCmdGetPckt(cmd17s3);
  setTstConnectCmdAppId(pcktCmd17s3,1);
  if (getTstConnectCmdAppId(pcktCmd17s3) != 1)
	  return 0;

  /* Release (17,3) command */
  CrFwInFactoryReleaseInCmd(cmd17s3);
  if (CrFwInFactoryGetNOfAllocatedInCmd() != nAllocatedCmd)
	  return 0;

  /* Create a (17,4) report and check its attributes */
  rep17s4 = CrFwOutFactoryMakeOutCmp(TST_TYPE, TSTCONNECTREP_STYPE, 0, 0);
  if (rep17s4 == NULL)
	  return 0;
  if (CrFwOutCmpGetServType(rep17s4) != 17)
	  return 0;
  if (CrFwOutCmpGetServSubType(rep17s4) != 4)
	  return 0;
  if (CrFwOutCmpGetDiscriminant(rep17s4) != 0)
	  return 0;

  pcktRep17s4 = CrFwOutCmpGetPckt(rep17s4);
  setTstConnectRepAppId(pcktRep17s4,255);
  if (getTstConnectRepAppId(pcktRep17s4) != 255)
	  return 0;

  /* Release (17,4) report */
  CrFwOutFactoryReleaseOutCmp(rep17s4);
  if (CrFwInFactoryGetNOfAllocatedInCmd() != nAllocatedCmd)
	  return 0;

  /* Verify selected data pool items */
  setDpTstAreYouAliveTimeOut(1);
  if (getDpTstAreYouAliveTimeOut() != 1)
	  return 0;

  setDpTstAreYouAliveTimeOut(65537);
  if (getDpTstAreYouAliveTimeOut() != 65537)
	  return 0;

  setDpTstOnBoardConnectDestLstItem(1, 255);
  if (getDpTstOnBoardConnectDestLstItem(1) != 255)
	  return 0;

  setDpTstAreYouAliveSrc(255);
  if (getDpTstAreYouAliveSrc() != 255)
	  return 0;

  setDpTstAreYouAliveStart(1);
  if (getDpTstAreYouAliveStart() != 1)
	  return 0;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
	return 0;

  return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsTstTestCase2() {
 FwSmDesc_t inFactory, outFactory, outManager, inCmd, outCmp, outCmpArr[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP];
  CrFwPckt_t pckt;
  CrFwCmpData_t* outManagerData;
  CrFwOutManagerData_t* outManagerCSData;
  uint16_t i;
  
  /* Instantiate the OutFactory, InFactory and OutManager */
  outFactory = CrFwOutFactoryMake();
  inFactory = CrFwInFactoryMake();
  outManager = CrFwOutManagerMake(0);

  /* Initialize and Configure OutFactory, InFactory and OutManager */
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);

  /* Initialize service 17 */
  CrPsTstConfigInit();

  /* Check number of Allocated Packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Create a 17,1 Packet */
  pckt = CrFwPcktMake(20);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,1);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,2);  

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 17,1 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  if (CrFwInCmdGetServType(inCmd) != 17)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 1)
    return 0; 

  /*check that the InCommand is in ACCEPTED state*/
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0; 

  /* Check if number of Allocated OutComponents = 0*/
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Execute the InCommand  */
  CrFwCmpExecute(inCmd); 
  
  /*check that the InCommand is in PROGRESS state*/
  if (!CrFwInCmdIsInProgress(inCmd))
    return 0;  

  /* Check if number of Allocated Packets now is 2*/
  if (CrFwPcktGetNOfAllocated() != 2)
    return 0;

  /* Check if number of Allocated OutComponents now is 1 */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;

  /*Get the Data from the out Manager (there is only one Component) */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[0];

  /*Check if there is a 17,2 Report waiting in the OutManager*/
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 17)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 2)
    return 0;

  /*Terminate the InCommand*/
  CrFwInCmdTerminate(inCmd); 

  /*Check if the InCommand is in TERMINATED state*/
  if (!CrFwInCmdIsInTerminated(inCmd))
    return 0;

  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Check if number of Allocated Packets now is 1*/
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /*Check if number of Allocated InCommands is now 0*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Execute the OutComponent (17,2) */
  CrFwCmpExecute(outCmp); 

  /*Release the OutComponent*/
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check if number of Allocated OutComponents now is 0 */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Check that there are no allocated packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a 17,1 Packet */
  pckt = CrFwPcktMake(20);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,1);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,1,1,1,1);  
  CrFwPcktSetSeqCnt(pckt,2);  

  /*Creating an InCommand out of the 17,1 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Fill the outfactory so that an Error could occur (leave one free slot) */
  for (i=0;i<CR_FW_OUTFACTORY_MAX_NOF_OUTCMP;i++)
    outCmpArr[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);

  /* Execute the InCommand  */
  CrFwCmpExecute(inCmd); 

  /* Check application errors */
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;

  /*Reset application error Code*/
  CrFwSetAppErrCode(crNoAppErr);

  /* Release all outcomponents, that have been created to fill the outfactory */
  for (i=0;i<CR_FW_OUTFACTORY_MAX_NOF_OUTCMP;i++)
    CrFwOutFactoryReleaseOutCmp(outCmpArr[i]);

  /*Release the InCommand */
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Reset OutManager and check that all OutComponents are unloaded and released */
  CrFwCmpReset(outManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;
  
  /*Here the ErrorCode gets 11, because there are no outcomponents in the OutManager*/
  CrFwSetAppErrCode(crNoAppErr);

  /* Reset the OutFactory */
  CrFwCmpReset(outFactory);  
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Reset the InFactory and check that no InCommands are allocated */
  CrFwCmpReset(inFactory);
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrPsTstTestCase3() {
  /* Check 17,3 and 17,4 */
  FwSmDesc_t inFactory, inManager, outFactory, outManager, inCmd, outCmp, outCmp1, inRep1;
  CrFwPckt_t pckt, pckt2;
  CrFwCmpData_t* outManagerData;
  CrFwOutManagerData_t* outManagerCSData;
  int i;

  /* Initialize the set of destination addresses for command (17,3).
   * The legal destinations are: 1, 2, 3, etc */
  for (i=0;i<TST_N_DEST;i++)
	  setDpTstOnBoardConnectDestLstItem(i,i+1);

  /* Initialize the time-out for the (17,3) command */
  setDpTstAreYouAliveTimeOut(cmd7s3TimeOut);

   /* Instantiate and configure the OutFactory, InFactory, OutManager and inManager */
  outFactory = CrFwOutFactoryMake();
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);

  inFactory = CrFwInFactoryMake();
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);

  outManager = CrFwOutManagerMake(0);
  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);

  inManager = CrFwInManagerMake(0);
  CrFwCmpInit(inManager);
  CrFwCmpReset(inManager);

  /* Create a 17,3 Packet */
  pckt = CrFwPcktMake(20);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,3);
  CrFwPcktSetDiscriminant(pckt,0);  
  CrFwPcktSetSrc(pckt,3);
  CrFwPcktSetDest(pckt,3);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);
  CrFwPcktSetSeqCnt(pckt,2);

  /*Create an InCommand out of the 17,3 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Give the Packet a wrong appId so the start action of the command fails*/
  pckt = CrFwInCmdGetPckt(inCmd);
  setTstConnectCmdAppId(pckt, TST_N_DEST+1);

  /* Execute the InCommand and check that it is aborted  */
  CrFwCmpExecute(inCmd); 
  if (!CrFwInCmdIsInAborted(inCmd))
    return 0; 

  /* Check that no OutComponent has been allocated  */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Release the inCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Check that a (1,4) report has been generated and is loaded in the OurManager
   * and that the failure code is correctly reported in the data pool  */
  if (getDpVerFailCodeStartFailed() != VER_REP_CR_FD)
	  return 0;



  /* Check if number of Allocated Packets now is 1 - a Request Verification (1,4) should be in the Outmanager */
  /* if (CrFwPcktGetNOfAllocated() != 1)										TO BE ADDED
    return 0;

  /* Check that there is one Packet Pending in the OutManager - Request Verification (1,4) */
  /*if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 1)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager is 1 - Request Verification (1,4)*/
  /*if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 1)
    return 0;

  /* Get the Data from the out Manager (there is only one Component) */
  /*outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[0];

  /* Check if there is a 1,4 Command waiting in the OutManager (loaded) */
  /*if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)							TO BE ADDED! */
  //  return 0;
  //if (CrFwOutCmpGetServType(outCmp) != 1)
  //  return 0;
  //if (CrFwOutCmpGetServSubType(outCmp) != 4)
  //  return 0;
  //if (getVerFailedStartRepTcFailCode(outCmp) != VER_REP_CR_FD)
  //	  return 0;  */

  /*Release the OutComponent*/
  /*CrFwOutFactoryReleaseOutCmp(outCmp); */

  /* Reset the OutManager (this should clear the POCL and release all OutComponents) */
  CrFwCmpReset(outManager);

  /* Check the application error code */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* Check if number of Allocated Packets now is 0 */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* ----------------------------------------------------------------------------------- */
  /* Create a 17,3 Packet with a correct connection test destination */
  pckt = CrFwPcktMake(20);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,3);
  CrFwPcktSetDiscriminant(pckt,0);  
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,2);
  setTstConnectCmdAppId(pckt, 1);	/* destination of connection test */

  /* Check number of Allocated Packets and commands */
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Create an InCommand out of the 17,3 packet*/
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* Check number of Allocated InCommands and OutComponents */
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check that newly created InCommand is in stated ACCEPTED */
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0;

  /* Execute the InCommand  */
  CrFwCmpExecute(inCmd); 

  /* Check if now 3 Packets are Allocated:
   * - one InCommand we just created and executed
   * - one OutCommand (17,1) to the application that was specified in the parameter of the 17,3 packet
   * - and OutComponent holding the 17,4 Report is allocated (outManager Pending)
   */
  if (CrFwPcktGetNOfAllocated() != 3)
    return 0;

  /* Check if number of Allocated InCommands and OutComponents */
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 1)
    return 0;

  /* Get the Data from the out Manager (there is only one Component) */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[0];

  /* Check if there is a 17,1 Command waiting in the OutManager (loaded) */
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 17)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 1)
    return 0;

  /* Check that there is one Packet Pending in the OutManager */
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 1)
    return 0;

  /* Create a 17,2 in Report */
  pckt2 = CrFwPcktMake(20);
  CrFwPcktSetCmdRepType(pckt,crRepType);
  CrFwPcktSetServType(pckt2,17);
  CrFwPcktSetServSubType(pckt2,2);
  CrFwPcktSetDiscriminant(pckt2,0);
  CrFwPcktSetDest(pckt2,10);
  CrFwPcktSetSrc(pckt2,1);	/* Same source as the destination of the connection test */

  /* Check number of Allocated Packets and Components */
  if (CrFwPcktGetNOfAllocated() != 4)
    return 0;

  /*Create an InReport from pckt2 (17.2)*/
  inRep1 = CrFwInFactoryMakeInRep(pckt2);

  /* Check if number of Allocated InReports in the InFactory now is 1*/
  if (CrFwInFactoryGetNOfAllocatedInRep() != 1)
    return 0;

  /* Check that there are no Packets Pending or Loaded in the InManager*/
  if (CrFwInManagerGetNOfPendingInCmp(inManager) != 0)
    return 0;
  if (CrFwInManagerGetNOfLoadedInCmp(inManager) != 0)
    return 0;

  /*Load the InReport into the InManager*/
  CrFwInManagerLoad(inManager, inRep1);

  /* Check if now one Pending (inCmd)(17,3) and one Loaded (inRep)(17,2) Packets in the InManager*/
  if (CrFwInManagerGetNOfPendingInCmp(inManager) != 1)
    return 0;
  if (CrFwInManagerGetNOfLoadedInCmp(inManager) != 1)
    return 0;

  /*Execute the InManager (this will cause the 17,2 InReport to be released) */
  CrFwCmpExecute(inManager); 

  /* Check that there is now no Pending but one Loaded (inCmd)(17,3) Packets in the InManager*/
  if (CrFwInManagerGetNOfPendingInCmp(inManager) != 0)
    return 0;
  if (CrFwInManagerGetNOfLoadedInCmp(inManager) != 1)
    return 0;

  /* Check that there is one Pending and one Loaded Packet in the OutManager */
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 1)
    return 0;
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 1)
    return 0;
  
  /*Execute the InCommand*/
  CrFwCmpExecute(inCmd); 

  /* 17,4 now in the OutManager*/
  /* Check that there are now two Pending and two Loaded Packets in the OutManager */
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 2)
    return 0;
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 2)
    return 0;

  /*Terminate the InCommand*/
  CrFwInCmdTerminate(inCmd); 

  /* Get the Information from the OutManager (there are two Component!) */
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[0];
  outCmp1 = outManagerCSData->pocl[1];

  /*Check if there are a 17,1 Command and 17,4 reports waiting in the OutManager (loaded)*/
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 2)
    return 0;
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 17)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetDest(outCmp) != 1)	/* Destination taken from (17,3) parameter */
	  return 0;
  if (CrFwCmpGetTypeId(outCmp1) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp1) != 17)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp1) != 4)
    return 0;

  /* Execute the OutComponent (17,1) and (17,4) */
  CrFwCmpExecute(outCmp);
  CrFwCmpExecute(outCmp1); 

  /* Check and reset application error code (i think because there is no outstream defined) */
  CrFwSetAppErrCode(crNoAppErr);

  /* Check that there are 3 allocated packets */
  if (CrFwPcktGetNOfAllocated() != 3)
    return 0;

  /* Release the (17,3) InCommand*/
  CrFwInFactoryReleaseInCmd(inCmd);

  /* Check that now there are only 2 allocated packets (the 17,1 and 17,4) */
  if (CrFwPcktGetNOfAllocated() != 2)
    return 0;

  /* Check that there are no Allocated InCommands in the InFactory*/
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Reset framework components */
  CrFwCmpReset(outManager);				/* This releases (17,1) and (17,4) */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  CrFwCmpReset(inManager);
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;
  
  CrFwCmpReset(outFactory);  
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;
  
  CrFwCmpReset(inFactory);
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  return 1;
}

/*--------------------------------------------------------------------------------*/
CrFwBool_t CrPsTstTestCase4() {
  /* Service 17 exceptional cases */
  FwSmDesc_t inFactory, inManager, outFactory, outManager, inCmd, outCmp[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP];
  CrFwPckt_t pckt;
   CrFwTime_t initTime;
  int i;
  
  /* Check number of Allocated Packets */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Create a 17,3 Packet */
  pckt = CrFwPcktMake(20);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,3);
  CrFwPcktSetDiscriminant(pckt,0);  
  CrFwPcktSetSrc(pckt,1);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,2);
  setTstConnectCmdAppId(pckt, 1);	/* The valid destinations were set in CrPsServTestConnTestCase2 */

  /* make an inCommand out of the packet */
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* Fill the outfactory leaving only one free slot */
  for (i=0;i<CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1;i++)
    outCmp[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);
  
  /* Execute the InCommand should have been aborted and */
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);
  if (CrFwInCmdIsInAborted(inCmd) != 1)
	  return 0;

  /* The OUTFACTORY_FAIL error report and a (1,2) with VER_REP_CRFD should have been generated */
  // TBD check

  /* The Error Code has been set by the OutFactory and must be reset */
  if (CrFwGetAppErrCode()!=crOutCmpAllocationFail)
	  return 0;
  CrFwSetAppErrCode(crNoAppErr);

  /* Check that no OutComponents were loaded in the OutLoader */
  outManager = CrFwOutManagerMake(0);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
      return 0;

  /* Release all outcomponents, that have been created to fill the outfactory */
  for (i=0;i<CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1;i++)
    CrFwOutFactoryReleaseOutCmp(outCmp[i]);

  /* Release the original inCmd and reset the OutManager (where a (17,4) has been loaded by the */
  CrFwInFactoryReleaseInCmd(inCmd);

 /* Check if number of Allocated Packets now is 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Create a 17,3 Packet */
  pckt = CrFwPcktMake(20);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,3);
  CrFwPcktSetDiscriminant(pckt,0);  
  CrFwPcktSetSrc(pckt,1);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  CrFwPcktSetSeqCnt(pckt,2);

  setTstConnectCmdAppId(pckt, 1);	/* The valid destinations were set in CrPsServTestConnTestCase2 */
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /* Fill the outfactory so that an Error could occur */
  for (i=0;i<CR_FW_OUTFACTORY_MAX_NOF_OUTCMP;i++)
    outCmp[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);

  /* Execute the InCommand  */
  /* If the OutFactory is full it should fail, there is also no place for a 1,4 to be generated !!!*/
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);

  /* Release all OutComponents, that have been created to fill the outfactory */
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1;i++)
    CrFwOutFactoryReleaseOutCmp(outCmp[i]);

  /* The error code has been set by the OutFactory and must be reset */
  CrFwSetAppErrCode(crNoAppErr);

  /* Release the original inCmd */
  CrFwInFactoryReleaseInCmd(inCmd);

 /* Check if number of Allocated Packets now is 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Create a 17,3 Packet */
  pckt = CrFwPcktMake(20);
  CrFwPcktSetCmdRepType(pckt,crCmdType);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,3); 
  CrFwPcktSetSrc(pckt,1);
  CrFwPcktSetDest(pckt,10);
  CrFwPcktSetAckLevel(pckt,0,0,0,0);  
  setTstConnectCmdAppId(pckt, 1);	/* The valid destinations were set in CrPsServTestConnTestCase2 */

  /* make an inCommand out of the packet */
  inCmd = CrFwInFactoryMakeInCmd(pckt);
  
  /* Make sure the current time is non-zero */
  CrFwGetCurrentTime();		/* This causes time to be advanced */
  initTime = CrFwGetCurrentTime();

  /* Set the time-out for the (17,3) to a very high value */
  setDpTstAreYouAliveTimeOut(100.0);

  /* Execute the InCommand and verify that the start time is correctly loaded in the data pool */
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);
  if (abs(getDpTstAreYouAliveStart()-initTime)>0.0001)
     return 0;

  /* Execute the InCommand a few times and check that it remains in PROGRESS */
  /* If the OutFactory is full it should fail, there is also no place for a 1,4 to be generated !!!*/
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);
  if (CrFwInCmdIsInProgress(inCmd) != 1)
	  return 0;

  /* At this point in time there are two pending items in the OutManager: the (17,1) and the (17,4) */
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager)!=1)
  	  return 0;

  /* Reset the time-out to a very small value and then execute again the InCommand and
   * verify that it is now aborted and that the (17,4) is no longer loaded in the OutManager */
  setDpTstAreYouAliveTimeOut(0.1);
  CrFwCmpExecute(inCmd);
  CrFwInCmdTerminate(inCmd);
  if (CrFwInCmdIsInAborted(inCmd) != 1)
	  return 0;
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager)!=1)
	  return 0;

  /* Reset the OutManager and release the inCmd and check that all packets are released */
  CrFwInFactoryReleaseInCmd(inCmd);
  CrFwCmpReset(outManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Reset InManager and check that all InComponents are unloaded and released */
  inManager = CrFwInManagerMake(0);
  CrFwCmpReset(inManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(inManager) != 0)
    return 0;

  /* Reset the OutFactory */
  outFactory = CrFwOutFactoryMake();
  CrFwCmpReset(outFactory);  
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Reset the InFactory and check that no InCommands are allocated */
  inFactory = CrFwInFactoryMake();
  CrFwCmpReset(inFactory);
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;

  return 1;
}


