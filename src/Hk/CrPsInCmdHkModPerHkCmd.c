/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(3,31) HkModPerHkCmd as an incoming command.
 *
 * @note This file was generated on 2019-03-05 14:03:04
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsInCmdHkEnbHkCmd.h"
#include "InCmd/CrFwInCmd.h"
#include "Pckt/CrPsPcktHk.h"
#include "Hk/CrPsHkConfig.h"
#include "DataPool/CrPsDpVer.h"
#include "DataPool/CrPsDpHk.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"

/**
 * Progress action of TC(3,31) HkModPerHkCmd.
 * The Structure Identifiers (SIDs) are processed in sequence and in the order
 * in which they are stored in the command. Each SID is processed in an
 * execution cycle. Each execution cycle counts as a progress step. At each
 * execution, the progress action performs the following actions:
 *
 * (a) If the SID is not loaded in the Report Definition List (RDL), then: the
 * unknown SID is loaded into verFailData and the Success Outcome is set to
 * VER_ILL_SID
 * (b) If the SID is loaded in the RDL, then its period is set to the value
 * specified in the command
 * (c) The Completion Outcome of the action is set to 'completed' if all SIDs
 * carried by the command have been processed; otherwise it is set to 'not
 * completed'.
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdHkModPerHkCmdProgressAction(FwSmDesc_t smDesc)  {
    CrFwPckt_t hkPckt = CrFwInCmdGetPckt(smDesc);
    CrPsNSID_t nSid;
    CrPsSID_t sid;
    CrFwProgressStepId_t progressStepId;
    short int rdlPos;
    CrPsCycleCnt_t period;

    /* Get the progress step identifier */
    progressStepId = CrFwInCmdGetProgressStepId(smDesc);

    /* Get the number of SIDs in the command */
    nSid = getHkModPerHkCmdN(hkPckt);

    /* Get the SID to be process in the current cycle */
    sid = getHkModPerHkCmdSID(hkPckt, progressStepId);

    /* Get the RDL slot for the argument SID */
    rdlPos = CrPsHkConfigGetRdlSlot(sid);

    /* Modify SID's period (if the SID is loaded in the RDL) */
    if (rdlPos < 0) {
      setDpVerFailData(sid);
      CrFwSetSmOutcome(smDesc, VER_ILL_SID);
    } else {
      period = getHkModPerHkCmdCollectionInterval(hkPckt,progressStepId);
      setDpHkPeriodItem(rdlPos,period);
      CrFwSetSmOutcome(smDesc, 1);
    }

    /* Update progress step identifier */
    progressStepId++;
    CrFwInCmdSetProgressStepId(smDesc, progressStepId);

    /* Set completion outcome */
    if (progressStepId < nSid)
      CrFwInCmdSetProgressActionCompleted(smDesc, 0);
    else
      CrFwInCmdSetProgressActionCompleted(smDesc, 1);
}

