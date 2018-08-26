/**
 * @file
 * @ingroup CrTestSuiteGroup
 *
 * Implementation of the InCommand Outcome Reporting interface of
 * <code>CrFwRepInCmdOutcome.h</code>.
 * The implementation of this interface is one of the adaptation points of the
 * CORDET Framework.
 * This file provides the implementation for the PUS Extension of the CORDET Framework.
 *
 * In keeping with the PUS, this implementation generates service 1 reports to report
 * the outcome of a command.
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This file is part of the PUS Extension of the CORDET Framework.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#include <stdlib.h>
/* Include Framework Files */
#include "CrFwConstants.h"
#include "CrFwUserConstants.h"
#include "CrFwRepInCmdOutcome.h"
#include "Pckt/CrFwPckt.h"
#include "CrFwVerServUserPar.h"

/** Pointer to function which determines whether an execution step has been completed (see <code>::CR_PS_STEP_COMPLETED</code>. */
static CrPsStepCompleted_t isStepCompleted = CR_PS_STEP_COMPLETED;

/*-----------------------------------------------------------------------------------------*/
/**
 * This functions handles the processing outcome of an InCommand.
 * All values of <code>outcome</code> are handled with the exception of <code>::crCmdAckLdFail</code>
 * which is handed by <code>::CrFwRepInCmdOutcomeCreFail</code>.
 */
void CrFwRepInCmdOutcome(CrFwRepInCmdOutcome_t outcome, CrFwInstanceId_t instanceId, CrFwServType_t servType,
                         CrFwServSubType_t servSubType, CrFwDiscriminant_t disc, CrFwOutcome_t failCode, FwSmDesc_t inCmd) {
  FwPrDesc_t serv1Pr;

  switch (outcome) {
    case crCmdAckAccFail:		/* Report an acceptance failure */
    	 CrPsVerConfigSetPrData(outcome, servType, servSubType, disc, failCode, inCmd);
         serv1Pr = CrPsVerConfigGetCmdVerFail();
         FwPrRun(serv1Pr);
         break;
    case crCmdAckAccSucc:		/* Report an acceptance success */
         CrPsVerConfigSetPrData(outcome, servType, servSubType, disc, failCode, inCmd);
    	 serv1Pr = CrPsVerConfigGetCmdVerSucc();
         FwPrRun(serv1Pr);
         break;
    case crCmdAckStrFail:		/* Report a start failure */
         CrPsVerConfigSetPrData(outcome, servType, servSubType, disc, failCode, inCmd);
    	 serv1Pr = CrPsVerConfigGetCmdVerFail();
         FwPrRun(serv1Pr);
         break;
    case crCmdAckStrSucc:		/* Report a start success */
         CrPsVerConfigSetPrData(outcome, servType, servSubType, disc, failCode, inCmd);
         serv1Pr = CrPsVerConfigGetCmdVerSucc();
         FwPrRun(serv1Pr);
         break;
    case crCmdAckPrgFail:		/* Report a progress failure */
         CrPsVerConfigSetPrData(outcome, servType, servSubType, disc, failCode, inCmd);
    	 serv1Pr = CrPsVerConfigGetCmdPrgrFail();
         FwPrRun(serv1Pr);
         break;
    case crCmdAckPrgSucc:		/* Report a progress success */
         if (isStepCompleted(inCmd) == 1) {
             CrPsVerConfigSetPrData(outcome, servType, servSubType, disc, failCode, inCmd);
             serv1Pr = CrPsVerConfigGetCmdPrgrSucc();
             FwPrRun(serv1Pr);
         }
         break;
    case crCmdAckTrmFail:		/* Report a termination failure */
         CrPsVerConfigSetPrData(outcome, servType, servSubType, disc, failCode, inCmd);
         serv1Pr = CrPsVerConfigGetCmdVerFail();
         FwPrRun(serv1Pr);
         break;
    case crCmdAckTrmSucc:		/* Report a termination success */
         CrPsVerConfigSetPrData(outcome, servType, servSubType, disc, failCode, inCmd);
         serv1Pr = CrPsVerConfigGetCmdVerSucc();
         FwPrRun(serv1Pr);
         break;
    case crCmdAckLdFail:		/* Report a failure to load the InCommand in its InManager */
        CrPsVerConfigSetPrData(outcome, servType, servSubType, disc, VER_CMD_LD_FD, inCmd);
        serv1Pr = CrPsVerConfigGetCmdVerFail();
        FwPrRun(serv1Pr);
        break;
    }
}

/*------------------------------------------------------------------------------------------------------*/
void CrFwRepInCmdOutcomeCreFail(CrFwRepInCmdOutcome_t outcome, CrFwOutcome_t failCode, CrFwPckt_t pckt) {
    FwPrDesc_t serv1Pr;
    CrPsVerConfigSetPrData(outcome, CrFwPcktGetServType(pckt), CrFwPcktGetServSubType(pckt),
                                                   CrFwPcktGetDiscriminant(pckt), VER_CRE_FD, NULL);
    serv1Pr = CrPsVerConfigGetCmdVerFail();
    FwPrRun(serv1Pr);
}

