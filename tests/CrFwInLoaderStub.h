/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Declaration of the stub for the InLoader Component (see <code>CrFwInLoader.h</code>).
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

#ifndef CRFW_INLOADER_TESTCASES_H_
#define CRFW_INLOADER_TESTCASES_H_

#include "CrFwConstants.h"
#include "CrFwUserConstants.h"

/**
 * Test implementation of the function which checks the legality of a destination and
 * returns the re-routing destination.
 * This test implementation can be configured to return either zero (to signify that the argument
 * destination is invalid) or a positive integer (to represent a re-routing destination).
 * This function must conform to the prototype defined by <code>::CrFwInLoaderGetReroutingDest_t</code>.
 * @param pcktDest the packet destination.
 * @return the re-routing destination or zero if the argument destination is illegal.
 */
CrFwDestSrc_t CrFwInLoaderStubGetReroutingDestination(CrFwDestSrc_t pcktDest);

/**
 * Set the return value of <code>::CrFwInLoaderStubGetReroutingDestination</code>.
 * @param retValue the desired return value of <code>::CrFwInLoaderStubGetReroutingDestination</code>
 */
void CrFwInLoaderStubSetReroutingDest(CrFwDestSrc_t retValue);

#endif /* CRFW_INLOADER_TESTCASES_H_ */
