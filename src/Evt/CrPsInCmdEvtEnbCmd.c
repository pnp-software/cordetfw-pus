/**
 * @file
 * @ingroup man_evt
 *
 * Implementation of TC(5,5) EvtEnbCmd as an incoming command.
 * The header file for this implementation file (CrPsInCmdEvtEnbCmd.h) was
 * generated by the CORDET Editor.
 *
 * The execution of this command extends over N cycles where N is the number of
 * event identifiers held by the command.
 * Each execution cycle is treated as a progress step cycle.
 * The progress step identifier of the n-th execution cycle is equal to n.
 *
 */

#include "CrPsInCmdEvtEnbCmd.h"
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

void CrPsInCmdEvtEnbCmdProgressAction(FwSmDesc_t smDesc) {
   CrFwPckt_t evtPckt = CrFwInCmdGetPckt(smDesc);
   CrPsNEvtId_t nEvtId;
   CrPsEvtId_t eid;
   unsigned int sevLevel;
   CrFwProgressStepId_t progressStepId;
   CrPsNEvtId_t nOfDisabledEvt;

   /* Get the progress step identifier */
   progressStepId = CrFwInCmdGetProgressStepId(smDesc);

   /* Get the number of EIDs in the command */
   nEvtId = getEvtEnbCmdN(evtPckt);

   /* Get the event identifier to be processed in the current cycle */
   eid = getEvtEnbCmdEventId(evtPckt, progressStepId);

   /* Try to enable the argument event identifier */
   sevLevel = CrPsEvtConfigSetEidEnableStatus(eid, 1);

   if (sevLevel == 0) {     /* The EID is not defined */
     setDpVerFailData(eid);
     CrFwSetSmOutcome(smDesc, VER_ILL_EID);
   } else {
     nOfDisabledEvt = getDpEvtNOfDisabledEidItem(sevLevel-1);
     setDpEvtNOfDisabledEidItem(sevLevel-1,nOfDisabledEvt-1);
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

/*--------------------------------------------------------------------------*/
void CrPsInCmdEvtEnbCmdTerminationAction(FwSmDesc_t smDesc) {
  CrFwProgressStepId_t nOfFailedSteps = CrFwInCmdGetNOfProgressFailure(smDesc);
  if (nOfFailedSteps > 0) {
    setDpVerFailData(nOfFailedSteps);
    CrFwSetSmOutcome(smDesc, VER_ILL_EID);
  } else
    CrFwSetSmOutcome(smDesc, 1);
}
