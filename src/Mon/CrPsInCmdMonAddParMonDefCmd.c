/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(12,5) MonAddParMonDefCmd as an incoming command.
 *
 * @limitation the check on the upper limit being greater than lower limit is not implemented
 *
 * @note This file was generated on 2018-09-29 23:48:04
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsInCmdMonAddParMonDefCmd.h"
#include "CrPsMonConfig.h"
#include "Pckt/CrPsPcktMon.h"
#include "DataPool/CrPsDpMon.h"
#include "DataPool/CrPsDpVer.h"
#include "DataPool/CrPsDp.h"
#include "InCmd/CrFwInCmd.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "FwPrCore.h"

#include <assert.h>

/* ------------------------------------------------------------------------- */
void CrPsInCmdMonAddParMonDefCmdProgressAction(FwSmDesc_t smDesc) {
    CrFwPckt_t monPckt = CrFwInCmdGetPckt(smDesc);
    CrPsNParMon_t nPmon;
    CrPsParMonId_t parMonId, nmbAvailParMon;
    CrPsParId_t parId, valCheckParId;
    CrPsMonPer_t repNmb, monPer;
    CrPsExpValue_t valCheckMask, valCheckExpVal;
    CrPsMonCheckType_t checkType;
    CrPsThirtytwoBit_t checkTypeData1, checkTypeData3;
    CrPsEvtId_t checkTypeData2, checkTypeData4;
    CrPsMonPrType_t monPrType;
    CrPsDpItemSignedness_t signedness;

    CrFwProgressStepId_t progressStepId;

    /* Get the progress step identifier */
    progressStepId = CrFwInCmdGetProgressStepId(smDesc);

    /* Get the number of PMONs in the command */
    nPmon = getMonAddParMonDefCmdNParMon(monPckt);

    /* Get the PMON to be processed in the current cycle */
    parMonId = getMonAddParMonDefCmdParMonId(monPckt, progressStepId);

    /* Load the PMON ID in verFailData (just in case the step fails) */
    setDpVerFailData(parMonId);

    /* Provisionally set the action outcome to 'success' */
    CrFwSetSmOutcome(smDesc, 1);

    /* Check whether the PMDL is full */
    nmbAvailParMon = getDpMonNmbAvailParMon();
    if (nmbAvailParMon == 0)
        CrFwSetSmOutcome(smDesc, VER_PMDL_FULL);

    /* Check legality of PMON identifier */
    if (parMonId == 0)
        CrFwSetSmOutcome(smDesc, VER_ILL_MON);

    if (parMonId > MON_N_PMON)
        CrFwSetSmOutcome(smDesc, VER_ILL_MON);

    /* Get the parameters associated to the parMon */
    parId = getMonAddParMonDefCmdMonParId(monPckt, progressStepId);
    signedness = getDpItemSignedness(parId);
    repNmb = getMonAddParMonDefCmdRepNmb(monPckt, progressStepId);
    valCheckParId = getMonAddParMonDefCmdValCheckParId(monPckt, progressStepId);
    valCheckMask = getMonAddParMonDefCmdValCheckParMask(monPckt, progressStepId);
    valCheckExpVal = getMonAddParMonDefCmdValCheckExpVal(monPckt, progressStepId);
    monPer = getMonAddParMonDefCmdMonPer(monPckt, progressStepId);
    checkType = getMonAddParMonDefCmdCheckType(monPckt, progressStepId);
    checkTypeData1 = getMonAddParMonDefCmdCheckTypeData1(monPckt, progressStepId);
    checkTypeData2 = getMonAddParMonDefCmdCheckTypeData2(monPckt, progressStepId);
    checkTypeData3 = getMonAddParMonDefCmdCheckTypeData3(monPckt, progressStepId);
    checkTypeData4 = getMonAddParMonDefCmdCheckTypeData4(monPckt, progressStepId);

    /* Check legality of monitored data item identifier */
    if (parId < DpIdParamsLowest)
        CrFwSetSmOutcome(smDesc, VER_MON_ILL_DI);

    if (parId > DpIdVarsHighest)
        CrFwSetSmOutcome(smDesc, VER_MON_ILL_DI);

    /* Checl legality of validity data item identifier */
    if (valCheckParId < DpIdParamsLowest)
        CrFwSetSmOutcome(smDesc, VER_MON_ILL_DI);

    if (valCheckParId > DpIdVarsHighest)
        CrFwSetSmOutcome(smDesc, VER_MON_ILL_DI);

    /* Determine the Monitoring Procedure Type */
    switch (checkType) {
        case EXP_VAL_CHECK:
            monPrType = MON_PR_EXP;
            break;
        case LIM_CHECK:
            switch (signedness) {
                case crDpTypeUnsigned:
                    monPrType = MON_PR_OOL_UI;
                    break;
                case crDpTypeSigned:
                    monPrType = MON_PR_OOL_SI;
                    break;
                case crDpTypeReal:
                    monPrType = MON_PR_OOL_R;
                    break;
            }
            break;
        case DEL_CHECK:
            assert(0);
    }

    /* If all checks were passed, configure PMON and decrement number of available PMONs */
    if (CrFwGetSmOutcome(smDesc) == 1) {
        CrPsMonConfigInitParMon(parMonId, parId, monPrType, monPer, repNmb, valCheckParId,
            valCheckExpVal, valCheckMask, &checkTypeData1, checkTypeData2, &checkTypeData3, checkTypeData4);
        setDpMonNmbAvailParMon(nmbAvailParMon-1);
    }

    /* Update progress step identifier */
    progressStepId++;
    CrFwInCmdSetProgressStepId(smDesc, progressStepId);

    /* Set completion outcome */
    if (progressStepId < nPmon)
      CrFwInCmdSetProgressActionCompleted(smDesc, 0);
    else
      CrFwInCmdSetProgressActionCompleted(smDesc, 1);
}

/*------------------------------------------------------------------------------------*/
void CrPsInCmdMonAddParMonDefCmdTerminationAction(FwSmDesc_t smDesc) {
    CrFwProgressStepId_t nOfFailedSteps = CrFwInCmdGetNOfProgressFailure(smDesc);
    if (nOfFailedSteps > 0) {
      setDpVerFailData(nOfFailedSteps);
      CrFwSetSmOutcome(smDesc, VER_MI_S12_FD);
    } else
      CrFwSetSmOutcome(smDesc, 1);
}
