/**
 * @file CrPsVerTestCases.h
 * @ingroup PUSTestsuite
 *
 * @brief Declaration of the test cases for the Request Verification Service.
 * The test cases in this module depend on each other and must be executed in the order
 * in which they are declared.
 * In many cases, service 1 is exercised by using the Sample 1 Command of the Dummy Service
 * (see <code>CrPsInCmdDumSample1.h</code>.
 *
 * @author Christian Reimers <christian.reimersy@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 * @author Alessandro Pasetti  <pasetti@pnp-software.com>
 *
 * @copyright P&P Software GmbH, 2018 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#ifndef CRPS_VERTESTCASES_H_
#define CRPS_VERTESTCASES_H_

/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"

/**
 * Test the getter and setter functions for service 1.
 * The following actions are performed:
 * - Create a (1,*) report and verify selected report parameters
 * - Check selected service 1 data pool parameters
 * .
 */
CrFwBool_t CrPsVerTestCase1();

/**
 * Test the generation of a (1,10) report.
 * The following actions are performed:
 * - Load a command with an invalid destination into the InLoader and verify that
 *   a (1,10) report is loaded into the OutLoader and that it carries the illegal
 *   destination as a parameter
 * - Verify that data pool variable nOfReroutingFailed has been incremented by 1
 * - Verify that data pool variables pcktIdReroutingFailed has the same value as the
 *   pcktId of the command with the invalid destination
 * - Verify that data pool variable invDestRerouting is equal to the invalid
 *   destination
 * - Fill up the OutFactory to the point where there are no more free slots and
 *   load a command with an invalid destination into the InLoader and verify that
 *   error report OUTFACTORY_FAIL is generated
 * - Check selected service 1 data pool parameters
 * .
 * @verify Packet Rerouting Failure Procedure, Report handling branch
 * @verify Packet Rerouting Failure Procedure, Nominal command handling branch
 * @verify Packet Rerouting Failure Procedure, Non-Nominal command handling branch
 * @errRep Error Report, OUTFACTORY_FAIL
 * @verify Observable, nOfReroutingFailed
 * @verify Observable, invDestRerouting
 * @verify Observable, pcktIdReroutingFailed
 */
CrFwBool_t CrPsVerTestCase2();

/**
 * Test the generation of the success reports of service 1
 * The following actions are performed in this test:
 * - Create a Sample 1 dummy command (see <code>CrPsInCmdDumSample1.h</code> and
 *   configure it such that all its checks are passed.
 *   The progress check is configured such that two progress steps are performed.
 * - Load and execute the dummy command and then verify that one (1,1),
 *   one (1,3), two (1,5) and one (1,7) reports are generated.
 * 
 * @verify Command Verification Success Procedure, Nominal branches
 * @verify Command Progress Success Procedure, Nominal branches
 */
CrFwBool_t CrPsVerTestCase3();


#endif /* CRPS_VERTESTCASES_H_ */
