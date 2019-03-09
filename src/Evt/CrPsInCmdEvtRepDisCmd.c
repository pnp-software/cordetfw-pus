/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(5,7) EvtRepDisCmd as an incoming command.
 *
 * @note This file was generated on 2018-10-28 17:05:47
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsInCmdEvtRepDisCmd.h"
#include "DataPool/CrPsDp.h"
#include "DataPool/CrPsDpEvt.h"
#include "Pckt/CrPsPckt.h"
#include "Evt/CrPsEvtConfig.h"
#include "CrPsConstants.h"
#include "CrPsServTypeId.h"

#include "CrFwUserConstants.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutLoader/CrFwOutLoader.h"
#include "InCmd/CrFwInCmd.h"
#include "OutFactory/CrFwOutFactory.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"

#include <assert.h>

static FwSmDesc_t rep5s8[EVT_MAX_N5S8];
static unsigned int nOfRep5s8;

/**
 * Start action of TC(5,7) EvtRepDisCmd.
 * Retrieve as many (5,8) reports from OutFactory as are needed
 * to hold the list of disabled event identifiers and set action
 * outcome to 'success’ if all retrievals succeed. If any of the
 * retrievals fail, generate error report OUTFACTORY FAILED and
 * set outcome of Start Action to ’failed’
 *
 * @constraint The number of (5,8) reports needed to carry all disabled event identifiers
 * must be smaller than EVT_MAX_N5s8. Violation of this constraint results in the application
 * error code being set to #CrPsIllNOf5s8.
 *
 * @param smDesc The descriptor of the state machine encapsulating the (5,7) command.
 */
void CrPsInCmdEvtRepDisCmdStartAction(FwSmDesc_t smDesc) {
  CrPsNEvtId_t nDisabledEvt;
  unsigned int nOfEidsInPartial5s8, maxNOfEid;
  unsigned int sizeFull5s8, sizePartial5s8, nOfFull5s8, nOfPartial5s8, i;
  size_t sizeOfEvtId, sizeOfEvtN, sizeOfHeader;

  /* Compute number of disabled events */
  nDisabledEvt = getDpEvtNOfDisabledEidItem(0) + getDpEvtNOfDisabledEidItem(1) + getDpEvtNOfDisabledEidItem(2) + getDpEvtNOfDisabledEidItem(3);

  /* Compute number of (5,8) packets required to report the disabled event identifiers */
  sizeOfEvtId = getDpSize(DpIdlastEvtEid)/4;
  sizeOfEvtN = getDpSize(DpIdnOfDisabledEid)/4;
  sizeOfHeader = sizeof(TmHeader_t);
  maxNOfEid = (CR_FW_MAX_PCKT_LENGTH - sizeOfHeader - sizeOfEvtN)/sizeOfEvtId;
  nOfFull5s8 = nDisabledEvt/maxNOfEid;
  if ((nDisabledEvt - nOfFull5s8*maxNOfEid) > 0)
    nOfPartial5s8 = 1;
  else
    nOfPartial5s8 = 0;

  /* Compute the size of the (5,8) reports */
  sizeFull5s8 = sizeOfHeader + sizeOfEvtN + maxNOfEid*sizeOfEvtId;
  nOfEidsInPartial5s8 = nDisabledEvt % maxNOfEid;
  sizePartial5s8 = sizeOfHeader + sizeOfEvtN + nOfEidsInPartial5s8*sizeOfEvtId;
  assert(sizePartial5s8 < sizeFull5s8);

  /* Check that the number of requested (5,8) reports is legal */
  nOfRep5s8 = nOfFull5s8 + nOfPartial5s8;
  if (nOfRep5s8 > EVT_MAX_N5S8) {
    nOfRep5s8 = EVT_MAX_N5S8;
    CrFwSetAppErrCode(crPsIllNOf5s8);
  }

  /* Retrieve the full (5,8) Reports */
  for (i=0; i<nOfFull5s8; i++) {
    rep5s8[i] = CrFwOutFactoryMakeOutCmp(EVT_TYPE, EVTDISREP_STYPE, 0, sizeFull5s8);
    if (rep5s8[i] == NULL) {
      CrFwSetSmOutcome(smDesc, VER_CRE_FD);
      return;
    }
  }

  /* Retrieve the partial (5,8) Reports */
  for (i=0; i<nOfPartial5s8; i++) {
    rep5s8[i+nOfFull5s8] = CrFwOutFactoryMakeOutCmp(EVT_TYPE, EVTDISREP_STYPE, 0, sizePartial5s8);
    if (rep5s8[i+nOfFull5s8] == NULL) {
      CrFwSetSmOutcome(smDesc, VER_CRE_FD);
      return;
    }
  }
}

/* ----------------------------------------------------------------------------------- */
/**
 * Progress action of TC(5,7) EvtRepDisCmd.
 * Configure the (5,8) reports with a destination equal to the source of the
 * (5,7) command and with the disabled event identifier, load them in the OutLoader,
 * and set the action outcome to ’success’.
 * @param smDesc The descriptor of the state machine encapsulating the (5,7) command.
 */
void CrPsInCmdEvtRepDisCmdProgressAction(FwSmDesc_t smDesc) {
  unsigned int i;
  CrFwDestSrc_t src5s7;

  src5s7 = CrFwInCmdGetSrc(smDesc);
  /* Process the full (5,8) reports */
  for (i=0; i<nOfRep5s8; i++) {
    CrFwOutCmpSetDest(rep5s8[i], src5s7);
    CrFwOutLoaderLoad(rep5s8[i]);
  }
  /* Set the starting position in the Event Position Buffer */
  CrPsEvtConfigResetIter();

  /* Set the action outcome to 'success' */
  CrFwSetSmOutcome(smDesc, 1);
}

