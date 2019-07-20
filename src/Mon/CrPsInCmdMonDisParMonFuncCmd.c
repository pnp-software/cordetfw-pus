/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(12,16) MonDisParMonFuncCmd as an incoming command.
 *
 * @note This file was generated on 2018-09-29 23:48:04
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsInCmdMonDisParMonFuncCmd.h"
#include "CrPsMonConfig.h"
#include "DataPool/CrPsDpMon.h"
#include "DataPool/CrPsDpVer.h"
#include "InCmd/CrFwInCmd.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "FwPrCore.h"

/* ------------------------------------------------------------------ */
void CrPsInCmdMonDisParMonFuncCmdStartAction(FwSmDesc_t smDesc) {
    if (getDpMonParMonFuncEnbStatus() == DISABLED) {
        setDpVerFailData(0);
        CrFwSetSmOutcome(smDesc, VER_MON_DIS);
        return;
    }

    /* Set action outcome to 'success' */
    CrFwSetSmOutcome(smDesc, 1);
}

/* ------------------------------------------------------------------ */
void CrPsInCmdMonDisParMonFuncCmdProgressAction(FwSmDesc_t smDesc) {

    /* Stop the Parameter Monitoring Function */
    FwPrStop(CrPsConfigGetParMonPr());

    /* Set Parameter Monitoring Function status to 'disabled' */
    setDpMonParMonFuncEnbStatus(DISABLED);

    /* Set outcome to 'success' and completion outcome to 'completed' */
    CrFwSetSmOutcome(smDesc, 1);
    CrFwInCmdSetProgressActionCompleted(smDesc, 1);
}

