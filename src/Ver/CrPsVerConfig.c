/*
 * @file CrPsVerConfig.c
 *
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This file is part of the PUS Extension of the CORDET Framework.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <stdlib.h>

#include "CrPsVerConfig.h"
#include "CrPsCmdPrgrFail.h"
#include "CrPsCmdPrgrSucc.h"
#include "CrPsCmdVerFail.h"
#include "CrPsPcktReroutingFail.h"

#include "DataPool/CrPsDpVer.h"
/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
/* Include configuration files */
#include "CrFwCmpData.h"

/** Singleton instance of Procedure for Command Progress Failure */
static FwPrDesc_t CmdPrgrFail = NULL;

/** Singleton instance of Procedure for Command Progress Success */
static FwPrDesc_t CmdPrgrSucc = NULL;

/** Singleton instance of Procedure for Command Verification Failure */
static FwPrDesc_t CmdVerFail = NULL;

/** Singleton instance of Procedure for Command Verification Success */
static FwPrDesc_t CmdVerSucc = NULL;

/** Singleton instance of Procedure for Packet Acceptance Success */
static FwPrDesc_t PcktReroutingFail = NULL;


/** The data attached to the Service 1 Procedures */
static CrPsVerData_t prVerData;

/*------------------------------------------------------------------------*/
void CrPsVerConfigInit() {
	/* Create the two procedure instances */
	CmdPrgrFail = CrPsCmdPrgrFailCreate(&prVerData);
	CmdPrgrSucc = CrPsCmdPrgrSuccCreate(&prVerData);
	CmdVerFail = CrPsCmdVerFailCreate(&prVerData);
	CmdVerSucc = CrPsCmdVerSuccCreate(&prVerData);
	PcktReroutingFail = CrPsPcktReroutingFailCreate(&prVerData);
}

/*------------------------------------------------------------------------*/
void CrPsVerConfigSetPrData(CrFwRepInCmdOutcome_t outcome, CrFwServType_t servType,
        CrFwServSubType_t servSubType, CrFwDiscriminant_t disc, CrFwOutcome_t failCode, FwSmDesc_t inCmd) {
	prVerData->disc = disc;
	prVerData->failCode = failCode;
	prVerData->inCmd = inCmd;
	prVerData->outcome = outcome;
	prVerData->servSubType = servSubType;
	prVerData->servType = servType;
}

/*------------------------------------------------------------------------*/
CrFwRepInCmdOutcome_t CrPsVerConfigGetOutcome() {
    return prVerData->outcome;
}

/*------------------------------------------------------------------------*/
CrFwServType_t CrPsVerConfigGetServType() {
    return prVerData->servType;
}

/*------------------------------------------------------------------------*/
CrFwServSubType_t CrPsVerConfigGetServSubType() {
    return prVerData->servSubType;
}

/*------------------------------------------------------------------------*/
CrFwDiscriminant_t CrPsVerConfigGetDisc() {
    return prVerData->disc;
}

/*------------------------------------------------------------------------*/
CrFwOutcome_t CrPsVerConfigGetFailCode() {
    return prVerData->failCode;
}

/*------------------------------------------------------------------------*/
FwSmDesc_t CrPsVerConfigGetInCmd() {
    return prVerData->inCmd;
}

/*------------------------------------------------------------------------*/
FwPrDesc_t CrPsVerConfigGetCmdPrgrFail() {
	return CmdPrgrFail;
}

/*------------------------------------------------------------------------*/
FwPrDesc_t CrPsVerConfigGetCmdPrgrSucc() {
	return CmdPrgrSucc;
}

/*------------------------------------------------------------------------*/
FwPrDesc_t CrPsVerConfigGetCmdVerFail() {
	return CmdVerFail;
}

/*------------------------------------------------------------------------*/
FwPrDesc_t CrPsVerConfigGetCmdVerSucc() {
	return CmdVerSucc;
}

/*------------------------------------------------------------------------*/
FwPrDesc_t CrPsVerConfigGetPcktReroutingFail() {
	return PcktReroutingFail;
}
