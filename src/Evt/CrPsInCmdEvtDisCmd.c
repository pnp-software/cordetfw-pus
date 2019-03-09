/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(5,6) EvtDisCmd as an incoming command.
 *
 * @note This file was generated on 2018-10-28 17:05:47
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsInCmdEvtDisCmd.h"
#include "CrPsServTypeId.h"
#include "CrPsTypes.h"
#include "CrPsEvtConfig.h"
#include "DataPool/CrPsDpEvt.h"
#include "Pckt/CrPsPcktEvt.h"
#include "DataPool/CrPsDpVer.h"

#include "OutRegistry/CrFwOutRegistry.h"
#include "InCmd/CrFwInCmd.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "OutCmp/CrFwOutCmp.h"

/**
 * Progress action of TC(5,6) EvtDisCmd.
 * For each valid EID found by the Start Action of the command: set the
 * corresponding element of the array isEidEnabled to false and then increment
 * nDisabledEid x (’x’ is the severity level of the EID). Set the action
 * outcome to ’completed’.
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdEvtDisCmdProgressAction(FwSmDesc_t smDesc) {
  CrFwPckt_t evtPckt = CrFwInCmdGetPckt(smDesc);
  CrPsNEvtId_t nEvtId;
  CrPsEvtId_t eid;
  unsigned int sevLevel;
  CrFwProgressStepId_t progressStepId;
  CrPsNEvtId_t nOfDisabledEvt;

  /* Get the progress step identifier */
  progressStepId = CrFwInCmdGetProgressStepId(smDesc);

  /* Get the number of EIDs in the command */
  nEvtId = getEvtDisCmdN(evtPckt);

  /* Get the event identifier to be process in the current cycle */
  eid = getEvtDisCmdEventId(evtPckt, progressStepId);

  /* Try to disable the argument event identifier */
  sevLevel = CrPsEvtConfigSetEidEnableStatus(eid, 0);

  if (sevLevel == 0) {     /* The EID is not defined */
    setDpVerFailData(eid);
    CrFwSetSmOutcome(smDesc, VER_ILL_EID);
  } else {
    nOfDisabledEvt = getDpEvtNOfDisabledEidItem(sevLevel-1);
    setDpEvtNOfDisabledEidItem(sevLevel-1,nOfDisabledEvt+1);
    CrFwSetSmOutcome(smDesc, 1);
  }

  /* Update progress step identifier */
  progressStepId++;
  CrFwInCmdSetProgressStepId(smDesc, progressStepId);

  /* Set completion outcome */
  if (progressStepId < nEvtId)
    CrFwInCmdSetProgressActionCompleted(smDesc, 0);
  else
    CrFwInCmdSetProgressActionCompleted(smDesc, 1);
}
