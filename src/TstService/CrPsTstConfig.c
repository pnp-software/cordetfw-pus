/*
 * @file CrPsTstConfig.c
 *
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This file is part of the :US Extension of the CORDET Framework.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <stdlib.h>

#include "CrPsTstConfig.h"
#include "DataPool/CrPsDpTst.h"
/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
/* Include configuration files */
#include "CrFwCmpData.h"

/** Singleton instance of Procedure for Start Action of Command (17,3). */
static FwSmDesc_t Cmd17s3Start = NULL;

/** Singleton instance of Procedure for Progress Action of Command (17,3). */
static FwSmDesc_t Cmd17s3Prgr = NULL;

/**
 * The data attached to the Start and Progress Action Procedures.
 */
static CrFwTstData_t prTstData;


/*------------------------------------------------------------------------*/
CrFwBool_t CrPsTstConfigInit() {
	CrFwCmpData_t* inCmdData;

	/* Create the two procedure instances */
	Cmd17s3Prgr = CrPsCmd17s3PrgrCreate(&prTstData);
	Cmd17s3Start = CrPsCmd17s3StartCreate(&prTstData);

	if (Cmd17s3Start == NULL)
		return 0;

	if (Cmd17s3Prgr == NULL)
		return 0;

	/* Initialize the data pool parameters for the Test Service */
	initDpTst();

	return 1;
}

/*------------------------------------------------------------------------*/
FwPrDesc_t CrPsTstConfigGetStart17s3() {
	return Cmd17s3Start;
}

/*------------------------------------------------------------------------*/
FwPrDesc_t CrPsTstConfigGetPrgr17s3() {
	return Cmd17s3Prgr;
}
