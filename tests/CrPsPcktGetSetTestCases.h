/**
 * @file CrPsPcktGetSetTestCases.h
 * @ingroup PUSTestsuite
 *
 * @brief Declaration of the test cases for the Getter and Setter functions of the command/report packets.
 *
 * @author Christian Reimers <christian.reimersy@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 *
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#ifndef CRPS_PCKTGETSET_TESTCASES_H_
#define CRPS_PCKTGETSET_TESTCASES_H_

/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"

/**
 * Test the Getter and Setter functions for all Packet Header parameters (Tm and Tc Header).
 * The test case sets each header parameter and the reads it back and verifies its value.
 * For each header parameter field, two different values are tried.
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsPcktGetSetTestCase1();

#endif /* CRPS_PCKTGETSET_TESTCASES_H_ */
