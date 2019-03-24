/**
 * @file
 * @ingroup man_hk
 *
 * Implementation of TC(3,3) HkDelHkCmd as an incoming command.
 * The header file CrPsInCmdHkDelHkCmd.h for this body file was
 * generated automatically by the CORDET Editor.
 * This module also implements the TC(3,4) command to delete a diagnostic report definition.
 *
 * @note This file was generated on 2019-03-05 14:03:04
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsInCmdHkDelHkCmd.h"
#include "InCmd/CrFwInCmd.h"
#include "Pckt/CrPsPcktHk.h"
#include "Hk/CrPsHkConfig.h"
#include "DataPool/CrPsDpVer.h"
#include "DataPool/CrPsDpHk.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"

void CrPsInCmdHkDelHkCmdProgressAction(FwSmDesc_t smDesc) {
  CrFwPckt_t hkPckt = CrFwInCmdGetPckt(smDesc);
  CrPsNSID_t nSid;
  CrPsSID_t sid;
  CrFwProgressStepId_t progressStepId;
  short int rdlPos;

  /* Get the progress step identifier */
  progressStepId = CrFwInCmdGetProgressStepId(smDesc);

  /* Get the number of SIDs in the command */
  nSid = getHkEnbHkCmdN(hkPckt);

  /* Get the SID to be process in the current cycle */
  sid = getHkEnbHkCmdSID(hkPckt, progressStepId);

  /* Get the RDL slot for the argument SID */
  rdlPos = CrPsHkConfigGetRdlSlot(sid);

  /* Clear SID (if the SID is loaded in the RDL and is disabled) */
  if (rdlPos > -1)
    if (getDpHkIsEnabledItem(rdlPos) == 0)
      CrPsHkConfigClearSid(sid);

  if (rdlPos < 0) {
    setDpVerFailData(sid);
    CrFwSetSmOutcome(smDesc, VER_ILL_SID);
  }

  if (getDpHkIsEnabledItem(rdlPos) == 1) {
    setDpVerFailData(sid);
    CrFwSetSmOutcome(smDesc, VER_ENB_SID);
  }

  /* Update progress step identifier */
  progressStepId++;
  CrFwInCmdSetProgressStepId(smDesc, progressStepId);

  /* Set completion outcome */
  if (progressStepId < nSid)
    CrFwInCmdSetProgressActionCompleted(smDesc, 0);
  else
    CrFwInCmdSetProgressActionCompleted(smDesc, 1);}

/*--------------------------------------------------------------------------------*/
void CrPsInCmdHkDelHkCmdTerminationAction(FwSmDesc_t smDesc) {
  CrFwProgressStepId_t nOfFailedSteps = CrFwInCmdGetNOfProgressFailure(smDesc);
  if (nOfFailedSteps > 0) {
    setDpVerFailData(nOfFailedSteps);
    CrFwSetSmOutcome(smDesc, VER_MI_S3_FD);
  } else
    CrFwSetSmOutcome(smDesc, 1);
}
