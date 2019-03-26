/**
 * @file
 * @ingroup man_hk
 *
 * Implementation of TC(3,9) HkRepStructHkCmd as an incoming command.
 * This module is also used to implement the TC(3,11).
 * The header file CrPsInCmdHkRepStructHkCmd.h for this body file was
 * generated automatically by the CORDET Editor.
 *
 * @note This file was generated on 2018-09-29 23:48:04
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsInCmdHkRepStructHkCmd.h"
#include "InCmd/CrFwInCmd.h"
#include "Pckt/CrPsPcktHk.h"
#include "Hk/CrPsHkConfig.h"
#include "DataPool/CrPsDpVer.h"
#include "DataPool/CrPsDpHk.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutLoader/CrFwOutLoader.h"
#include "OutFactory/CrFwOutFactory.h"
#include "CrFwRepErr.h"
#include "CrPsServTypeId.h"

void CrPsInCmdHkRepStructHkCmdProgressAction(FwSmDesc_t smDesc) {
    CrFwPckt_t hkPckt = CrFwInCmdGetPckt(smDesc);
    CrPsNSID_t nSid;
    CrPsSID_t sid;
    CrFwProgressStepId_t progressStepId;
    short int rdlPos;
    CrFwServSubType_t subTypeRepStruct;
    FwSmDesc_t repStruct;
    CrFwPcktLength_t repStructLen;
    CrFwDestSrc_t srcCmd;
    CrPsNPar_t nPar, i;
    CrFwPckt_t repStructPckt;

    /* Get the progress step identifier */
    progressStepId = CrFwInCmdGetProgressStepId(smDesc);

    /* Get the number of SIDs in the command */
    nSid = getHkEnbHkCmdN(hkPckt);

    /* Get the SID to be process in the current cycle */
    sid = getHkRepStructHkCmdSID(hkPckt, progressStepId);

    /* Get the RDL slot for the argument SID */
    rdlPos = CrPsHkConfigGetRdlSlot(sid);

    /* Check if the SID is loaded in the RDL and, if so, load the SID structure report */
    if (rdlPos < 0) {
      setDpVerFailData(sid);
      CrFwSetSmOutcome(smDesc, VER_ILL_SID);
    } else {
      /* Compute the sub-type of the SID Structure Report */
      subTypeRepStruct = CrFwInCmdGetServSubType(smDesc) + 1;

      /* Compute the length of the SID Structure Report */
      nPar = getDpHkNSimpleItem(rdlPos);
      repStructLen = LEN_HK_REPSTRUCTHKREP+sizeof(CrPsSID_t)+sizeof(CrPsEnDis_t)+
              sizeof(CrPsCycleCnt_t)+sizeof(CrPsNPar_t)+nPar*sizeof(CrPsParId_t);

      /* Attempt to retrieve the SID Structure Report from the OutFactory. */
      repStruct = CrFwOutFactoryMakeOutCmp(HK_TYPE, subTypeRepStruct, 0, repStructLen);
      if (repStruct == NULL) {
        CrFwRepErrKind(psOutFactoryFail, 0, 0, HK_TYPE, subTypeRepStruct, 0);
        CrFwSetSmOutcome(smDesc, VER_CRE_FD);
      } else {
        srcCmd = CrFwInCmdGetSrc(smDesc);
        CrFwOutCmpSetDest(repStruct, srcCmd);
        repStructPckt = CrFwOutCmpGetPckt(repStruct);
        setHkRepStructHkRepSID(repStructPckt, sid);
        setHkRepStructHkRepPerGenActionStatus(repStructPckt, getDpHkIsEnabledItem(rdlPos));
        setHkRepStructHkRepCollectionInterval(repStructPckt, getDpHkPeriodItem(rdlPos));
        setHkRepStructHkRepN1(repStructPckt, nPar);
        for (i=0; i<nPar; i++)
            setHkRepStructHkRepN1ParamId(repStructPckt, i, CrPsHkConfigGetParamId(rdlPos, i));

        CrFwOutLoaderLoad(repStruct);
        CrFwSetSmOutcome(smDesc, 1);
      }
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
