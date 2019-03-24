/**
 * @file
 * @ingroup PUSTestsuite
 *
 * Implementation of stub for InLoader component.
 * This stub is used in the Test Suite of the PUS Extension of the CORDET Framework.
 *
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

#include "CrFwUserConstants.h"

/** Return value of function <code>CrFwInLoaderStubGetReroutingDestination</code>. */
static CrFwDestSrc_t reroutingDest = 0;

/* ---------------------------------------------------------------------------------------------*/
/**
 * Function to set the return value of function <code>::CrFwInLoaderTestCaseGetReroutingDestination</code>.
 * @param retValue the return value of function <code>::CrFwInLoaderTestCaseGetReroutingDestination</code>.
 */
void CrFwInLoaderStubSetReroutingDest(CrFwDestSrc_t retValue) {
	reroutingDest = retValue;
}

/* ---------------------------------------------------------------------------------------------*/
CrFwDestSrc_t CrFwInLoaderStubGetReroutingDestination(CrFwDestSrc_t pcktDest) {
	(void)(pcktDest);
	return reroutingDest;
}


