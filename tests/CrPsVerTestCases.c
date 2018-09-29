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

#include "PcktFunctions/CrPsPcktVer.h"
#include "PcktFunctions/CrPsPckt.h"
#include "DataPool/CrPsDpVer.h"
#include "CrPsServTypeId.h"
#include "CrPsConstants.h"
#include "CrPsTestUtilities.h"

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
  rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERFAILEDACCREP_STYPE, 7, 0);
  if (rep == NULL)
	  return 0;
  if (CrFwOutCmpGetServType(rep) != 1)
	  return 0;
  if (CrFwOutCmpGetServSubType(rep) != 2)
	  return 0;
  if (CrFwOutCmpGetDiscriminant(rep) != 7)
	  return 0;

  pckt = CrFwOutCmpGetPckt(rep);
  if (getVerFailedAccRepTcFailCode(pckt) != 7)
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
  if (CrFwOutCmpGetDiscriminant(rep) != 9)
	  return 0;

  pckt = CrFwOutCmpGetPckt(rep);
  if (getVerFailedStartRepTcFailCode(pckt) != 9)
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
  if (CrFwOutCmpGetDiscriminant(rep) != 33)
	  return 0;

  pckt = CrFwOutCmpGetPckt(rep);
  if (getVerFailedPrgrRepTcFailCode(pckt) != 33)
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
  rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERFAILEDTERMREP_STYPE, 31, 0);
  if (rep == NULL)
	  return 0;
  if (CrFwOutCmpGetServType(rep) != 1)
	  return 0;
  if (CrFwOutCmpGetServSubType(rep) != 8)
	  return 0;
  if (CrFwOutCmpGetDiscriminant(rep) != 31)
	  return 0;

  pckt = CrFwOutCmpGetPckt(rep);
  if (getVerFailedTermRepTcFailCode(pckt) != 31)
	  return 0;
  setVerFailedTermRepTcPcktId(pckt,4096);
  if (getVerFailedTermRepTcPcktId(pckt) != 4096)
	  return 0;

  CrFwOutFactoryReleaseOutCmp(rep);			/* Release the report */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != nAllocatedRep)
	  return 0;

  /* Create a (1,10) report and check its attributes */
  rep = CrFwOutFactoryMakeOutCmp(VER_TYPE, VERFAILEDROUTINGREP_STYPE, 255, 0);
  if (rep == NULL)
	  return 0;
  if (CrFwOutCmpGetServType(rep) != 1)
	  return 0;
  if (CrFwOutCmpGetServSubType(rep) != 10)
	  return 0;
  if (CrFwOutCmpGetDiscriminant(rep) != 255)
	  return 0;

  pckt = CrFwOutCmpGetPckt(rep);
  if (getVerFailedTermRepTcFailCode(pckt) != 31)
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
  FwSmDesc_t inFactory, outManager, inCmd, inLoader;
  CrFwPckt_t inPckt;
  CrFwDestSrc_t illegalDest = 99;
  CrPsNOfCmd_t nOfCmdFailedRerouting = getDpVerNOfReroutingFailed();
  CrPsThirteenBit_t pcktId;
  FwSmDesc_t outCmpArr[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP];

  /* Check if number of Allocated Packets = 0*/
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Instantiate and configure InFactory, InLoader and OutManager */
  inFactory = CrFwInFactoryMake();
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  inLoader = CrFwInLoaderMake();
  CrFwCmpInit(inLoader);
  CrFwCmpReset(inLoader);
  outManager = CrFwOutManagerMake(0);
  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);

  /* Create a Sample 1 Command of type (255,1) with an illegal destination */
  inPckt = CrPsTestUtilitiesCreateSAmple1Pckt(illegalDest,1,1,1,1,1,1);
  pcktId = getTcHeaderPcktType(inPckt)*(2^13)+getTcHeaderSecHeaderFlag(inPckt)*(2^13)+getTcHeaderAPID(inPckt);

  inCmd = CrFwInFactoryMakeInCmd(inPckt);
  if (inCmd == NULL)
      return 0;

  /* Load the Sample 1 Command with the illegal destination in the InLoader */
  CrFwOutLoaderLoad(inCmd);

  /* Verify that a (1,10) report is now pending in the OutManager and that
   * data pool variables have been updated accordingly */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;
  if (CrPsTestUtilitiesCheckOutManagerCmd(outManager,0,1,10) != 1)
      return 0;
  if (getDpVerInvDestRerouting() != illegalDest)
      return 0;
  if (getDpVerNOfReroutingFailed() != nOfCmdFailedRerouting+1)
      return 0;
  if (getDpVerPcktIdReroutingFailed() != pcktId)
      return 0;

  /* Release all allocated commands and reports */
  CrFwInFactoryReleaseInCmd(inCmd);     /* This releases the Sample 1 Command */
  CrFwCmpReset(outManager);             /* This releases the (1,10) report */
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Fill the outfactory */
  for (i=0;i<CR_FW_OUTFACTORY_MAX_NOF_OUTCMP;i++)
    outCmpArr[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);

  /* Create again a Sample 1 Command of type (255,1) with an illegal destination  and load it in the InLoader */
  inPckt = CrPsTestUtilitiesCreateSAmple1Pckt(illegalDest,1,1,1,1,1,1);
  CrFwOutLoaderLoad(inCmd);

  /* Verify that no (1,10) report was created */
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
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

  return 1;
}
