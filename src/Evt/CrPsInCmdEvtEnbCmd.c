/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(5,5) EvtEnbCmd as an incoming command.
 *
 * The execution of this command extends over N cycles where N is the number of
 * event identifiers held by the command.
 * Each execution cycle is treated as a progress step cycle.
 * The progress step identifier of the n-th execution cycle is equal to n.
 *
 * If an event identifier is encountered to which no severity limit is associated
 * (through function #CrPsEvtConfigGetSeverity), then the application error code
 * is set to: #CrPsEvtIdWithNoSevLevel.
 *
 * @note This file was generated on 2018-10-28 17:05:47
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
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

/**
 * Progress action of TC(5,5) EvtEnbCmd.
 * The event identifiers are processed in sequence and in the order in which
 * they are stored in the event report. Each event identifier is processed in
 * an execution cycle. Each execution cycle counts as a progress step. At each
 * execution, the progress action performs the following actions:
 *
 * (a) If the event identifier is illegal, then: the illegal EID is loaded
 * into verFailData and the Success Outcome is set to VER_ILL_EID
 * (b) If the event identified is legal, then: its enable status is set to
 * 'enabled'; the value of nDisabledEid x (’x’ is the severity level of the
 * EID) is decremented; and the Success Outcome of the action is set to
 * 'success'
 * (c) The Completion Outcome of the action is set to 'completed' if all event
 * identifiers carried by the command have been processed; otherwise it is set
 * to 'not completed'.
 *
 * The enable status of the event identifier is stored in the OutRegistry
 * component of the CORDET Framework.
 *
 * @param smDesc The descriptor of the state machine encapsulating the (5,5) command.
 */
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

   /* Get the event identifier to be process in the current cycle */
   eid = getEvtEnbCmdEventId(evtPckt, progressStepId);

   /* Try to enable the argument event identifier */
   sevLevel = CrPsEvtConfigSetEidEnableStatus(eid, 1);

   if (sevLevel == 0) {     /* The EID is not defined */
     setDpVerFailData(eid);
     CrFwSetSmOutcome(smDesc, VER_ILL_EID);
   } else {
     switch (sevLevel) {
       case 1:
         nOfDisabledEvt = getDpEvtNOfDisabledEid_1();
         setDpEvtNOfDisabledEid_1(nOfDisabledEvt-1);
         break;
       case 2:
         nOfDisabledEvt = getDpEvtNOfDisabledEid_2();
         setDpEvtNOfDisabledEid_2(nOfDisabledEvt-1);
         break;
       case 3:
         nOfDisabledEvt = getDpEvtNOfDisabledEid_3();
         setDpEvtNOfDisabledEid_3(nOfDisabledEvt-1);
         break;
       case 4:
         nOfDisabledEvt = getDpEvtNOfDisabledEid_4();
         setDpEvtNOfDisabledEid_4(nOfDisabledEvt-1);
         break;
       default:
         CrFwSetAppErrCode(CrPsEvtIllSevLevel);
     }
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

/**
 * Termination action of TC(5,5) EvtEnbCmd.
 * The action outcome is set to 'success' if all progress steps were
 * successful. Otherwise, the action outcome is set to VER_ILL_EID and the
 * number of failed progress steps (which corresponds to the number of illegal
 * event identifier in the command) is loaded in verFailData.
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdEvtEnbCmdTerminationAction(FwSmDesc_t smDesc) {
  CrFwProgressStepId_t nOfFailedSteps = CrFwInCmdGetNOfProgressFailure(smDesc);
  if (nOfFailedSteps > 0) {
    setDpVerFailData(nOfFailedSteps);
    CrFwSetSmOutcome(smDesc, VER_ILL_EID);
  } else
    CrFwSetSmOutcome(smDesc, 1);
}
