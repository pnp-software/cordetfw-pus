/**
 * @file CrFwRepInCmdOutCome.c
 * @ingroup PUSTestsuite
 * @ingroup PUSTestconfig 
 *
 * Default implementation of the InCommand Outcome Reporting interface of
 * <code>CrFwRepInCmdOutcome.h</code>.
 * The implementation of this interface is one of the adaptation points of the
 * CORDET Framework.
 * This file provides a default implementation which is primarily intended to
 * support testing.
 * It is expected that applications will provide their own implementation.
 * Application will therefore normally replace this file with their own file
 * providing their application-specific implementation.
 *
 * This implementation stores the InCommand Outcome Reports in a pre-allocated array with
 * a fixed size.
 * The array is managed as a ring-buffer.
 * Functions are provide to let external components access the InCommand Outcome Report array.
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * @author Christian Reimers <christian.reimers@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 *
 * last modification: 22.01.2018
 *
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#include <stdlib.h>
/* Include Framework Files */
#include "CrFwConstants.h"
#include "CrFwRepInCmdOutcome.h"
/* Include Configuration Files */
#include "CrFwRepInCmdOutcomeStub.h"

/** The size of the InCommand Outcome Report array */
#define CR_FW_INCMD_OUTCOME_REP_ARRAY_SIZE 100

/** The structure for an InCommand Outcome Report. */
typedef struct {
	/** The outcome of the InCommand */
	CrFwRepInCmdOutcome_t outcome;
	/** The failure code (only meaningful for failure outcomes) */
	CrFwOutcome_t failCode;
	/** The service type of the InCommand whose outcome is being reported */
	CrFwServType_t servType;
	/** The service sub-type of the InCommand whose outcome is being reported */
	CrFwServSubType_t servSubType;
	/** The discriminant of the InCommand whose outcome is being reported */
	CrFwDiscriminant_t discriminant;
	/** The instance identifier of the InCommand whose outcome is being reported */
	CrFwInstanceId_t instanceId;
} CrFwInCmdOutcomeRep_t;

/** The InCommand Outcome Report array */
static CrFwInCmdOutcomeRep_t inCmdOutcomeRepArray[CR_FW_INCMD_OUTCOME_REP_ARRAY_SIZE];

/** The position in the InCommand Outcome Report array at which the next
 * InCommand Outcome Report will be written */
static CrFwCounterU2_t inCmdOutcomeRepPos = 0;

/*-----------------------------------------------------------------------------------------*/
CrFwCounterU2_t CrFwRepInCmdOutcomeStubGetPos() {
	return inCmdOutcomeRepPos;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwRepInCmdOutcomeStubReset() {
	inCmdOutcomeRepPos = 0;
}

/*-----------------------------------------------------------------------------------------*/
CrFwRepInCmdOutcome_t CrFwRepInCmdOutcomeStubGetOutcome(CrFwCounterU2_t repPos) {
	return inCmdOutcomeRepArray[repPos].outcome;
}

/*-----------------------------------------------------------------------------------------*/
CrFwOutcome_t CrFwRepInCmdOutcomeStubGetFailCode(CrFwCounterU2_t repPos) {
	return inCmdOutcomeRepArray[repPos].failCode;
}

/*-----------------------------------------------------------------------------------------*/
CrFwInstanceId_t CrFwRepInCmdOutcomeStubGetInstanceId(CrFwCounterU2_t repPos) {
	return inCmdOutcomeRepArray[repPos].instanceId;
}

/*-----------------------------------------------------------------------------------------*/
CrFwServType_t CrFwRepInCmdOutcomeStubGetServType(CrFwCounterU2_t repPos) {
	return inCmdOutcomeRepArray[repPos].servType;
}

/*-----------------------------------------------------------------------------------------*/
CrFwServSubType_t CrFwRepInCmdOutcomeStubGetServSubType(CrFwCounterU2_t repPos) {
	return inCmdOutcomeRepArray[repPos].servSubType;
}

/*-----------------------------------------------------------------------------------------*/
CrFwDiscriminant_t CrFwRepInCmdOutcomeStubGetDiscriminant(CrFwCounterU2_t repPos) {
	return inCmdOutcomeRepArray[repPos].discriminant;
}
