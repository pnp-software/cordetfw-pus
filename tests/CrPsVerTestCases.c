/**
 * @file CrPsVerTestCases.c
 * @ingroup PUSTestsuite
 *
 * @brief Implementation of test cases for the Request Verification Service.
 *
 * @author Christian Reimers <christian.reimersy@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 * @author Alessandro Pasetti  <pasetti@pnp-software.com>
 * 
 * @copyright P&P Software GmbH, 2018 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 */

/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
/* Include configuration files */
#include "CrFwInStreamUserPar.h"
#include "CrFwOutRegistryUserPar.h"
#include "CrFwOutFactoryUserPar.h"
/* Include framework files */
#include "CrFwCmpData.h"
#include "OutRegistry/CrFwOutRegistry.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include "InCmd/CrFwInCmd.h"
#include "InFactory/CrFwInFactory.h"
#include "OutFactory/CrFwOutFactory.h"
#include "OutLoader/CrFwOutLoader.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"

#include "Pckt/CrPsPcktVer.h"
#include "Pckt/CrPsPckt.h"
#include "DataPool/CrPsDpVer.h"
#include "CrPsServTypeId.h"
#include "CrPsConstants.h"
#include "CrPsTestUtilities.h"
#include "Dum/CrPsInCmdDumSample1Ctrl.h"

/* Include system files */
#include <stdlib.h>
#include <unistd.h>

/*-----------------------------------------------------------------------------*/
CrFwBool_t CrPsVerTestCase1() {
  CrFwPckt_t pckt;
  FwSmDesc_t rep;
  FwSmDesc_t outFactory;
  unsigned int nAllocatedRep;

  CrFwSetAppErrCode(crNoAppErr);
  nAllocatedRep = CrFwOutFactoryGetNOfAllocatedOutCmp();

  /* Instantiate and configure OutFactory  */
  outFactory = CrFwOutFactoryMake();
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  if (!CrFwCmpIsInConfigured(outFactory))
    return 0;

   /* Create a (1,1) report and check its attributes */
  rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERSUCCACCREP_STYPE, 0, 0);
  if (rep == NULL)
	  return 0;
  if (CrFwOutCmpGetServType(rep) != 1)
	  return 0;
  if (CrFwOutCmpGetServSubType(rep) != 1)
	  return 0;
  if (CrFwOutCmpGetDiscriminant(rep) != 0)
	  return 0;

  pckt = CrFwOutCmpGetPckt(rep);
  setVerSuccAccRepTcPcktId(pckt, 13);
  if (getVerSuccAccRepTcPcktId(pckt) != 13)
	  return 0;

  CrFwOutFactoryReleaseOutCmp(rep);			/* Release the report */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nAllocatedRep)
	  return 0;

  /* Create a (1,2) report and check its attributes */
  rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERFAILEDACCREP_STYPE, 0, 0);
  if (rep == NULL)
	  return 0;
  if (CrFwOutCmpGetServType(rep) != 1)
	  return 0;
  if (CrFwOutCmpGetServSubType(rep) != 2)
	  return 0;
  if (CrFwOutCmpGetDiscriminant(rep) != 0)
	  return 0;

  pckt = CrFwOutCmpGetPckt(rep);
  if (getVerFailedAccRepTcFailCode(pckt) != 0)
	  return 0;

  CrFwOutFactoryReleaseOutCmp(rep);			/* Release the report */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nAllocatedRep)
	  return 0;

  /* Create a (1,3) report and check its attributes */
  rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERSUCCSTARTREP_STYPE, 0, 0);
  if (rep == NULL)
	  return 0;
  if (CrFwOutCmpGetServType(rep) != 1)
	  return 0;
  if (CrFwOutCmpGetServSubType(rep) != 3)
	  return 0;
  if (CrFwOutCmpGetDiscriminant(rep) != 0)
	  return 0;

  pckt = CrFwOutCmpGetPckt(rep);
  setVerSuccStartRepPcktVersNumber(pckt,7);
  if (getVerSuccStartRepPcktVersNumber(pckt) != 7)
	  return 0;

  CrFwOutFactoryReleaseOutCmp(rep);			/* Release the report */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nAllocatedRep)
	  return 0;

  /* Create a (1,4) report and check its attributes */
  rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERFAILEDSTARTREP_STYPE, 0, 0);
  if (rep == NULL)
	  return 0;
  if (CrFwOutCmpGetServType(rep) != 1)
	  return 0;
  if (CrFwOutCmpGetServSubType(rep) != 4)
	  return 0;
  if (CrFwOutCmpGetDiscriminant(rep) != 0)
	  return 0;

  pckt = CrFwOutCmpGetPckt(rep);
  if (getVerFailedStartRepTcFailCode(pckt) != 0)
	  return 0;
  setVerFailedStartRepTcPcktSeqCtrl(pckt,257);
  if (getVerFailedStartRepTcPcktSeqCtrl(pckt) != 257)
	  return 0;

  CrFwOutFactoryReleaseOutCmp(rep);			/* Release the report */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nAllocatedRep)
	  return 0;

  /* Create a (1,5) report and check its attributes */
  rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERSUCCPRGRREP_STYPE, 0, 0);
  if (rep == NULL)
	  return 0;
  if (CrFwOutCmpGetServType(rep) != 1)
	  return 0;
  if (CrFwOutCmpGetServSubType(rep) != 5)
	  return 0;
  if (CrFwOutCmpGetDiscriminant(rep) != 0)
	  return 0;

  pckt = CrFwOutCmpGetPckt(rep);
  setVerSuccPrgrRepPcktVersNumber(pckt,1);
  if (getVerSuccPrgrRepPcktVersNumber(pckt) != 1)
	  return 0;

  CrFwOutFactoryReleaseOutCmp(rep);			/* Release the report */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nAllocatedRep)
	  return 0;

  /* Create a (1,6) report and check its attributes */
  rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERFAILEDPRGRREP_STYPE, 0, 0);
  if (rep == NULL)
	  return 0;
  if (CrFwOutCmpGetServType(rep) != 1)
	  return 0;
  if (CrFwOutCmpGetServSubType(rep) != 6)
	  return 0;
  if (CrFwOutCmpGetDiscriminant(rep) != 0)
	  return 0;

  pckt = CrFwOutCmpGetPckt(rep);
  if (getVerFailedPrgrRepTcFailCode(pckt) != 0)
	  return 0;
  setVerFailedPrgrRepTcPcktSeqCtrl(pckt,257);
  if (getVerFailedPrgrRepTcPcktSeqCtrl(pckt) != 257)
	  return 0;

  CrFwOutFactoryReleaseOutCmp(rep);			/* Release the report */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nAllocatedRep)
	  return 0;

  /* Create a (1,7) report and check its attributes */
  rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERSUCCTERMREP_STYPE, 0, 0);
  if (rep == NULL)
	  return 0;
  if (CrFwOutCmpGetServType(rep) != 1)
	  return 0;
  if (CrFwOutCmpGetServSubType(rep) != 7)
	  return 0;
  if (CrFwOutCmpGetDiscriminant(rep) != 0)
	  return 0;

  pckt = CrFwOutCmpGetPckt(rep);
  setVerSuccTermRepPcktVersNumber(pckt,4);
  if (getVerSuccTermRepPcktVersNumber(pckt) != 4)
	  return 0;

  CrFwOutFactoryReleaseOutCmp(rep);			/* Release the report */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nAllocatedRep)
	  return 0;

  /* Create a (1,8) report and check its attributes */
  rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERFAILEDTERMREP_STYPE, 0, 0);
  if (rep == NULL)
	  return 0;
  if (CrFwOutCmpGetServType(rep) != 1)
	  return 0;
  if (CrFwOutCmpGetServSubType(rep) != 8)
	  return 0;
  if (CrFwOutCmpGetDiscriminant(rep) != 0)
	  return 0;

  pckt = CrFwOutCmpGetPckt(rep);
  if (getVerFailedTermRepTcFailCode(pckt) != 0)
	  return 0;
  setVerFailedTermRepTcPcktId(pckt,4096);
  if (getVerFailedTermRepTcPcktId(pckt) != 4096)
	  return 0;

  CrFwOutFactoryReleaseOutCmp(rep);			/* Release the report */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nAllocatedRep)
	  return 0;

  /* Create a (1,10) report and check its attributes */
  rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERFAILEDROUTINGREP_STYPE, 0, 0);
  if (rep == NULL)
	  return 0;
  if (CrFwOutCmpGetServType(rep) != 1)
	  return 0;
  if (CrFwOutCmpGetServSubType(rep) != 10)
	  return 0;
  if (CrFwOutCmpGetDiscriminant(rep) != 0)
	  return 0;

  pckt = CrFwOutCmpGetPckt(rep);
  if (getVerFailedTermRepTcFailCode(pckt) != 0)
	  return 0;
  setVerFailedRoutingRepInvDest(pckt,10);
  if (getVerFailedRoutingRepInvDest(pckt) != 10)
	  return 0;
  setVerFailedRoutingRepTcType(pckt,31);
  if (getVerFailedRoutingRepTcType(pckt) != 31)
	  return 0;

  CrFwOutFactoryReleaseOutCmp(rep);			/* Release the report */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nAllocatedRep)
	  return 0;

  /* Check application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
	return 0;

  return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsVerTestCase2() {
  unsigned short i;
  FwSmDesc_t inFactory, outManager, inLoader, inStream, inManager;
  CrPsNOfCmd_t nOfCmdFailedRerouting = getDpVerNOfReroutingFailed();
  FwSmDesc_t outCmpArr[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP];
  CrFwDestSrc_t illDest = 7;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Instantiate and configure InFactory, InLoader, OutManager and InStream */
  inFactory = CrFwInFactoryMake();
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  inLoader = CrFwInLoaderMake();
  CrFwCmpInit(inLoader);
  CrFwCmpReset(inLoader);
  outManager = CrFwOutManagerMake(0);
  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  inStream = CrFwInStreamMake(0);
  CrFwCmpInit(inStream);
  CrFwCmpReset(inStream);
  inManager = CrFwInManagerMake(0);
  CrFwCmpInit(inManager);
  CrFwCmpReset(inManager);

  /* Instantiate and configure the InStreamStub to hold a dummy packet with an illegal destination */
  CrFwInStreamStubSetPcktCollectionCnt(1);  /* Only one packet is loaded */
  CrFwInStreamStubSetPcktSeqCnt(1);
  CrFwInStreamStubSetPcktGroup(1);
  CrFwInStreamStubSetPcktType(255,1,0);     /* Sets the type, sub-type and discriminant */
  CrFwInStreamStubSetPcktDest(illDest);
  CrFwInStreamStubSetPcktCmdRepId(1);
  CrFwInStreamStubSetPcktAckLevel(1,1,1,1);
  CrFwInStreamStubSetPcktCmdRepType(crCmdType);

  /* The InStreamStub now holds a dummy packet with an invalid destination and this is loaded in the InLoader */
  CrFwInStreamPcktAvail(inStream);          /* Dummy packet is loaded in InStream */
  CrFwInLoaderSetInStream(inStream);
  CrFwCmpExecute(inLoader);                 /* Dummy packet is collected from InStream and loaded in InManager */

  /* Verify that a (1,10) report is now pending in the OutManager and that
   * data pool variables have been updated accordingly */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmd(outManager,0,1,10) != 1)
      return 0;
  if (getDpVerInvDestRerouting() != illDest)
      return 0;
  if (getDpVerNOfReroutingFailed() != nOfCmdFailedRerouting+1)
      return 0;
  if (getDpVerPcktIdReroutingFailed() != illDest*16+0x1000)
      return 0;

  /* Release all allocated commands and reports (the dummy packet with illegal destination is released by the InLoader */
  CrFwCmpReset(outManager);             /* This releases the (1,10) report */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Fill the outfactory */
  for (i=0;i<CR_FW_OUTFACTORY_MAX_NOF_OUTCMP;i++)
    outCmpArr[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);

  /* Load again a dummy Sample 1 Command of type (255,1) with an illegal destination  and load it in the InLoader */
  CrFwInStreamStubSetPcktCollectionCnt(1);  /* Only one packet is loaded */
  CrFwInStreamPcktAvail(inStream);          /* Collect dummy packet */
  CrFwCmpExecute(inLoader);                 /* Load dummy packet in InLoader */

  /* Verify that no (1,10) report was created */
  if (  CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;
  if (getDpVerNOfReroutingFailed() != nOfCmdFailedRerouting+1)
      return 0;

  /* Release all outcomponents, that have been created to fill the outfactory */
  for (i=0;i<CR_FW_OUTFACTORY_MAX_NOF_OUTCMP;i++)
    CrFwOutFactoryReleaseOutCmp(outCmpArr[i]);

  /* Check and then reset application errors */
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;
  CrFwSetAppErrCode(crNoAppErr);
  
  return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsVerTestCase3() {
  FwSmDesc_t outManager, inLoader, inStream, inManager;
  CrFwProgressStepId_t prgrStepId;
  FwSmDesc_t sample1Cmd, rep1s5;
  CrFwPckt_t rep1s5Pckt;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
     return 0;

  /* Instantiate InFactory, InLoader, OutManager and InStream (configured in previous test case */
  inLoader = CrFwInLoaderMake();
  outManager = CrFwOutManagerMake(0);
  inStream = CrFwInStreamMake(0);
  inManager = CrFwInManagerMake(0);

  /* Instantiate and configure the InStreamStub to hold a Sample 1 Command (255,1) */
  CrFwInStreamStubSetPcktCollectionCnt(1);  /* Only one packet is loaded */
  CrFwInStreamStubSetPcktCmdRepType(crCmdType);
  CrFwInStreamStubSetPcktSeqCnt(1);
  CrFwInStreamStubSetPcktGroup(1);
  CrFwInStreamStubSetPcktType(255,1,0);     /* Sets the type, sub-type and discriminant */
  CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID);
  CrFwInStreamStubSetPcktCmdRepId(1);
  CrFwInStreamStubSetPcktAckLevel(1,1,1,1);

  /* Configure the Sample 1 Command to pass all its checks and repeat the prorgress action */
  CrPsInCmdDumSample1SetValidityFlag(1);
  CrPsInCmdDumSample1SetReadyFlag(1);
  CrPsInCmdDumSample1SetStartActionOutcome(1);
  CrPsInCmdDumSample1SetProgressStepFlag(0);        /* do not increment progress step */
  CrPsInCmdDumSample1SetProgressActionOutcome(2);   /* continue execution of progress action */
  CrPsInCmdDumSample1SetTerminationActionOutcome(1);

  /* The InStreamStub now holds a dummy packet with an invalid destination and this is loaded in the InLoader */
  CrFwInStreamPcktAvail(inStream);          /* Dummy packet is loaded in InStream */
  CrFwInLoaderSetInStream(inStream);
  CrFwCmpExecute(inLoader);                 /* Dummy packet is collected from InStream and loaded in InManager */
  sample1Cmd = CrPsTestUtilitiesGetItemFromInManager(inManager, 0);

  /* Verify that a (1,1) was generated during the command's loading process */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmd(outManager,0,1,1) != 1)
    return 0;

  /* Execute the Sample 1 command a few times and verify that a (1,3) was generated */
  CrFwCmpExecute(inManager);
  CrFwCmpExecute(inManager);
  CrFwCmpExecute(inManager);
  CrFwCmpExecute(inManager);
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 2)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmd(outManager,1,1,3) != 1)
    return 0;

  /* Configure the Sample 1 command to complete a progress step and verify that a (1,5) is generated */
  prgrStepId = CrFwInCmdGetProgressStepId(sample1Cmd);
  CrPsInCmdDumSample1SetProgressStepFlag(1);        /* complete progress step at next command execution */
  CrFwCmpExecute(inManager);
  CrPsInCmdDumSample1SetProgressStepFlag(0);        /* do not increment progress step at next command execution */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 3)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmd(outManager,2,1,5) != 1)
    return 0;
  rep1s5 = CrPsTestUtilitiesGetItemFromOutManager(outManager, 2);
  rep1s5Pckt = CrFwOutCmpGetPckt(rep1s5);
  if (getVerSuccPrgrRepTcPrgStep(rep1s5Pckt) != prgrStepId+1)
    return 0;

  /* Execute the Sample 1 command a few more times and verify that no service reports are generated */
  CrFwCmpExecute(inManager);
  CrFwCmpExecute(inManager);
  CrFwCmpExecute(inManager);
  CrFwCmpExecute(inManager);
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 3)
    return 0;

  /* Configure the Sample 1 command to complete another progress step and verify that another (1,5) is generated */
  prgrStepId = CrFwInCmdGetProgressStepId(sample1Cmd);
  CrPsInCmdDumSample1SetProgressStepFlag(1);        /* complete progress step at next command execution */
  CrFwCmpExecute(inManager);
  CrPsInCmdDumSample1SetProgressStepFlag(0);        /* do not increment progress step at next command execution */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 4)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmd(outManager,3,1,5) != 1)
    return 0;
  rep1s5 = CrPsTestUtilitiesGetItemFromOutManager(outManager, 3);
  rep1s5Pckt = CrFwOutCmpGetPckt(rep1s5);
  if (getVerSuccPrgrRepTcPrgStep(rep1s5Pckt) != prgrStepId+1)
    return 0;

  /* Configure the Sample 1 command to terminate execution and verify that a (1,7) is generated */
  CrPsInCmdDumSample1SetProgressActionOutcome(1);   /* terminate execution of progress action */
  CrPsInCmdDumSample1SetTerminationActionOutcome(1);
  CrFwCmpExecute(inManager);
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 5)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmd(outManager,4,1,7) != 1)
    return 0;

  /* Reset all components used in the test case */
  CrFwCmpReset(inManager);
  CrFwCmpReset(outManager);
  CrFwCmpReset(inStream);
  CrFwCmpReset(inLoader);

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
     return 0;

  /* Check and then reset application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
     return 0;

  return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsVerTestCase4() {
  FwSmDesc_t outManager, inLoader, inStream, inManager;
  CrFwProgressStepId_t prgrStepId;
  FwSmDesc_t sample1Cmd, rep1s5;
  CrFwPckt_t rep1s5Pckt;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
     return 0;

  /* Instantiate InFactory, InLoader, OutManager and InStream (configured in previous test case */
  inLoader = CrFwInLoaderMake();
  outManager = CrFwOutManagerMake(0);
  inStream = CrFwInStreamMake(0);
  inManager = CrFwInManagerMake(0);

  /* ---------------------------------- Step 1 ----------------------------------- */
  /* Instantiate and configure the InStreamStub to hold a Sample 1 Command (255,1) */
  CrFwInStreamStubSetPcktCollectionCnt(1);  /* Only one packet is loaded */
  CrFwInStreamStubSetPcktCmdRepType(crCmdType);
  CrFwInStreamStubSetPcktSeqCnt(1);
  CrFwInStreamStubSetPcktGroup(1);
  CrFwInStreamStubSetPcktType(255,1,0);     /* Sets the type, sub-type and discriminant */
  CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID);
  CrFwInStreamStubSetPcktCmdRepId(1);
  CrFwInStreamStubSetPcktAckLevel(1,1,1,1);

  /* Configure the Sample 1 Command to fail its validity check */
  CrPsInCmdDumSample1SetValidityFlag(0);

  /* The InStreamStub now holds a Sample 1 Command which fails its validity check */
  CrFwInStreamPcktAvail(inStream);          /* SAmple packet is loaded in InStream */
  CrFwInLoaderSetInStream(inStream);
  CrFwCmpExecute(inLoader);                 /* Sample packet is collected from InStream and loaded in InManager */

  /* Verify that a (1,2) was generated during the command's loading process and then reset OutManager */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmd(outManager,0,1,2) != 1)
    return 0;
  CrFwCmpReset(outManager);                 /* Clears queue of pending service 1 reports in OutManager */

  /* ---------------------------------- Step 2 ----------------------------------- */
  /* Instantiate and configure the InStreamStub to hold a Sample 1 Command (255,1) */
  CrFwInStreamStubSetPcktCollectionCnt(1);  /* Load one more packet */

  /* Configure the Sample 1 Command to fail its start action */
  CrPsInCmdDumSample1SetValidityFlag(1);
  CrPsInCmdDumSample1SetReadyFlag(1);
  CrPsInCmdDumSample1SetStartActionOutcome(0);

  /* The InStreamStub now holds a Sample 1 Command which fails its start action */
  CrFwInStreamPcktAvail(inStream);          /* Sample packet is loaded in InStream */
  CrFwInLoaderSetInStream(inStream);
  CrFwCmpExecute(inLoader);                 /* Sample packet is collected from InStream and loaded in InManager */
  CrFwCmpExecute(inManager);

  /* Verify that a (1,1) and (1,4) were generated during the command's loading process and then reset OutManager */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 2)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmd(outManager,0,1,1) != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmd(outManager,1,1,4) != 1)
    return 0;
  CrFwCmpReset(outManager);                 /* Clears queue of pending service 1 reports in OutManager */

  /* ---------------------------------- Step 3 ----------------------------------- */
  /* Instantiate and configure the InStreamStub to hold a Sample 1 Command (255,1) */
  CrFwInStreamStubSetPcktCollectionCnt(1);  /* Load one more packet */

  /* Configure the Sample 1 Command to fail its progress action */
  CrPsInCmdDumSample1SetValidityFlag(1);
  CrPsInCmdDumSample1SetReadyFlag(1);
  CrPsInCmdDumSample1SetStartActionOutcome(1);
  CrPsInCmdDumSample1SetProgressActionOutcome(0);   /* fail progress action */
  CrPsInCmdDumSample1SetProgressStepFlag(1);        /* increment progress step at next command execution */

  /* The InStreamStub now holds a Sample 1 Command which fails its progress action */
  CrFwInStreamPcktAvail(inStream);          /* Sample packet is loaded in InStream */
  CrFwInLoaderSetInStream(inStream);
  CrFwCmpExecute(inLoader);                 /* Sample packet is collected from InStream and loaded in InManager */
  sample1Cmd = CrPsTestUtilitiesGetItemFromInManager(inManager, 0);
  CrFwCmpExecute(inManager);
  prgrStepId = CrFwInCmdGetProgressStepId(sample1Cmd);

  /* Verify that a (1,1), (1,3) and (1,6) were generated during the command's loading process and then reset OutManager */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 3)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmd(outManager,0,1,1) != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmd(outManager,1,1,3) != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmd(outManager,2,1,6) != 1)
    return 0;
  rep1s5 = CrPsTestUtilitiesGetItemFromOutManager(outManager, 2);
  rep1s5Pckt = CrFwOutCmpGetPckt(rep1s5);
  if (getVerSuccPrgrRepTcPrgStep(rep1s5Pckt) != prgrStepId)
    return 0;
  CrFwCmpReset(outManager);                 /* Clears queue of pending service 1 reports in OutManager */

  /* ---------------------------------- Step 4 ----------------------------------- */
  /* Instantiate and configure the InStreamStub to hold a Sample 1 Command (255,1) */
  CrFwInStreamStubSetPcktCollectionCnt(1);  /* Load one more packet */

  /* Configure the Sample 1 Command to fail its termination action */
  CrPsInCmdDumSample1SetValidityFlag(1);
  CrPsInCmdDumSample1SetReadyFlag(1);
  CrPsInCmdDumSample1SetStartActionOutcome(1);
  CrPsInCmdDumSample1SetProgressActionOutcome(1);   /* termination execution of progress action */
  CrPsInCmdDumSample1SetProgressStepFlag(1);        /* increment progress step at next command execution */
  CrPsInCmdDumSample1SetTerminationActionOutcome(0);

  /* The InStreamStub now holds a Sample 1 Command which fails its termination action */
  CrFwInStreamPcktAvail(inStream);          /* Sample packet is loaded in InStream */
  CrFwInLoaderSetInStream(inStream);
  CrFwCmpExecute(inLoader);                 /* Sample packet is collected from InStream and loaded in InManager */
  sample1Cmd = CrPsTestUtilitiesGetItemFromInManager(inManager, 0);
  CrFwCmpExecute(inManager);
  prgrStepId = CrFwInCmdGetProgressStepId(sample1Cmd);

  /* Verify that a (1,1), (1,3) and (1,6) were generated during the command's loading process and then reset OutManager */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 4)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmd(outManager,0,1,1) != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmd(outManager,1,1,3) != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmd(outManager,2,1,5) != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmd(outManager,3,1,8) != 1)
    return 0;

  /* Reset all components used in the test case */
  CrFwCmpReset(inManager);
  CrFwCmpReset(outManager);
  CrFwCmpReset(inStream);
  CrFwCmpReset(inLoader);

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
     return 0;

  /* Check and then reset application errors */
  if (CrFwGetAppErrCode() != crNoAppErr)
     return 0;

  return 1;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsVerTestCase5() {
  FwSmDesc_t inLoader, inStream, inManager, outManager;
  FwSmDesc_t outCmpArr[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP];
  int i;

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
     return 0;

  /* Instantiate InFactory, InLoader, OutManager and InStream (configured in previous test case */
  inLoader = CrFwInLoaderMake();
  inStream = CrFwInStreamMake(0);
  inManager = CrFwInManagerMake(0);
  outManager = CrFwOutManagerMake(0);

  /* Fill the OutFactory */
  for (i=0;i<CR_FW_OUTFACTORY_MAX_NOF_OUTCMP;i++)
    outCmpArr[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);

  /* ---------------------------------- New Step --------------------------------- */
  /* Instantiate and configure the InStreamStub to hold a Sample 1 Command (255,1) */
  CrFwInStreamStubSetPcktCollectionCnt(1);  /* Only one packet is loaded */
  CrFwInStreamStubSetPcktCmdRepType(crCmdType);
  CrFwInStreamStubSetPcktSeqCnt(1);
  CrFwInStreamStubSetPcktGroup(1);
  CrFwInStreamStubSetPcktType(255,1,0);     /* Sets the type, sub-type and discriminant */
  CrFwInStreamStubSetPcktDest(CR_FW_HOST_APP_ID);
  CrFwInStreamStubSetPcktCmdRepId(1);
  CrFwInStreamStubSetPcktAckLevel(1,1,1,1);

  /* Configure the Sample 1 Command to pass its progress action but remaing pending */
  CrPsInCmdDumSample1SetValidityFlag(1);
  CrPsInCmdDumSample1SetReadyFlag(1);
  CrPsInCmdDumSample1SetStartActionOutcome(1);
  CrPsInCmdDumSample1SetProgressActionOutcome(2);   /* continue execution */
  CrPsInCmdDumSample1SetProgressStepFlag(1);        /* increment progress step at next command execution */

  /* The InStreamStub now holds a Sample 1 Command which passes its progress action and then remains pending */
  CrFwInStreamPcktAvail(inStream);          /* Sample packet is loaded in InStream */
  CrFwInLoaderSetInStream(inStream);
  CrFwCmpExecute(inLoader);                 /* Sample packet is collected from InStream and loaded in InManager */
  CrFwCmpExecute(inManager);

  /* Verify that no service 1 reports were generated */
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;

  /* Configure Sample 1 Command to fail its next progress step and then execute it again */
  CrPsInCmdDumSample1SetProgressActionOutcome(0);   /* continue execution */
  CrFwCmpExecute(inManager);

  /* Verify that no service 1 reports were generated */
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;

  /* ---------------------------------- New Step --------------------------------- */
  /* Instantiate and configure the InStreamStub to hold a Sample 1 Command (255,1) */
  CrFwInStreamStubSetPcktCollectionCnt(1);  /* Load one more packet */

  /* Configure the Sample 1 Command to fail its termination action */
  CrPsInCmdDumSample1SetValidityFlag(1);
  CrPsInCmdDumSample1SetReadyFlag(1);
  CrPsInCmdDumSample1SetStartActionOutcome(1);
  CrPsInCmdDumSample1SetProgressActionOutcome(1);   /* termination execution of progress action */
  CrPsInCmdDumSample1SetProgressStepFlag(1);        /* increment progress step at next command execution */
  CrPsInCmdDumSample1SetTerminationActionOutcome(0);

  /* The InStreamStub now holds a Sample 1 Command which fails its termination action */
  CrFwInStreamPcktAvail(inStream);          /* Sample packet is loaded in InStream */
  CrFwInLoaderSetInStream(inStream);
  CrFwCmpExecute(inLoader);                 /* Sample packet is collected from InStream and loaded in InManager */
  CrFwCmpExecute(inManager);

  /* Verify that no service 1 reports were generated */
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;

  /* Release all OutComponents, that have been created to fill the outfactory */
  for (i=0;i<CR_FW_OUTFACTORY_MAX_NOF_OUTCMP;i++)
    CrFwOutFactoryReleaseOutCmp(outCmpArr[i]);

  /* Reset all components used in the test case */
  CrFwCmpReset(inManager);
  CrFwCmpReset(inStream);
  CrFwCmpReset(inLoader);

  /* Check if number of Allocated Packets = 0*/
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
     return 0;

  /* Check and then reset application errors */
  /* Check and then reset application errors */
  if (CrFwGetAppErrCode() != crOutCmpAllocationFail)
    return 0;
  CrFwSetAppErrCode(crNoAppErr);

  return 1;
}
