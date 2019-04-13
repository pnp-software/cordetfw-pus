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
 * @return 1 if the test is successful; zero otherwise
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
 * @verify Procedure, Packet Rerouting Failure, Report handling branch
 * @verify Procedure, Packet Rerouting Failure, Nominal command handling branch
 * @verify Procedure, Packet Rerouting Failure, Non-Nominal command handling branch
 * @verify Error Report, OUTFACTORY_FAIL
 * @verify Data Pool, nOfReroutingFailed
 * @verify Data Pool, invDestRerouting
 * @verify Data Pool, pcktIdReroutingFailed
 * @verify Report, Failed Routing Verification
 * @return 1 if the test is successful; zero otherwise
 */
CrFwBool_t CrPsVerTestCase2();

/**
 * Test the generation of the success reports of service 1.
 * The following actions are performed in this test:
 * - Create a Sample 1 dummy command (see <code>CrPsInCmdDumSample1.h</code> and
 *   configure it such that all its checks are passed.
 *   The progress check is configured such that two progress steps are performed.
 * - Load and execute the dummy command and then verify that one (1,1),
 *   one (1,3), two (1,5) and one (1,7) reports are generated.
 * .
 * @verify Procedure, Command Verification Success, Nominal branches
 * @verify Procedure, Command Progress Success, Nominal branches
 * @verify Report, Successful Acceptance Verification Report
 * @verify Report, Successful Start of Execution Verification Report
 * @verify Report, Successful Progress of Execution Verification Report
 * @verify Report, Successful Termination of Execution Verification Report
 * @return 1 if the test is successful; zero otherwise
 */
CrFwBool_t CrPsVerTestCase3();

/**
 * Test the generation of the failure reports of service 1.
 * The following actions are performed in this test:
 * - Create a Sample 1 dummy command (see <code>CrPsInCmdDumSample1.h</code>) and
 *   configure it such that its validity check is failed, execute it and
 *   verify that a (1,2) report is generated.
 * - Create a Sample 1 dummy command (see <code>CrPsInCmdDumSample1.h</code>) and
 *   configure it such that its validity check is passed and its start action fails,
 *   execute it and verify that a (1,4) report is generated.
 * - Create a Sample 1 dummy command (see <code>CrPsInCmdDumSample1.h</code>) and
 *   configure it such that its validity check and start action are passed and its
 *   progress action fails, execute it and verify that a (1,6) report is generated.
 * - Create a Sample 1 dummy command (see <code>CrPsInCmdDumSample1.h</code>) and
 *   configure it such that its validity check, start and progress action are passed and its
 *   termination action fails, execute it and verify that a (1,8) report is generated.
 * .
 * @verify Procedure, Command Verification Failed, Nominal branch
 * @verify Procedure, Command Progress Failed, Nominal branch
 * @verify Report, Failed Acceptance Verification
 * @verify Report, Failed Start of Execution Verification
 * @verify Report, Failed Progress of Execution Verification
 * @verify Report, Failed Termination of Execution Verification
 * @verify Data Pool, failCode
 * @return 1 if the test is successful; zero otherwise
 */
CrFwBool_t CrPsVerTestCase4();

/**
 * Test the OUTFACTORY_FAIL branch of the service 1 procedures (except for the Re-routing
 * Failure Procedure).
 * The following actions are performed in this test:
 * - Fill up the OutFactory such that no more OutComponents are available
 * - Create a Sample 1 dummy command (see <code>CrPsInCmdDumSample1.h</code>) and
 *   configure it such that: its acceptance and start check are passed and its progress
 *   check is passed on the first progress step but failed on the second progress step.
 * - One would expect the following reports to be generated: (1,1), (1,3) and (1,6)
 *   but it is verifed that none of them is generated.
 * - Create another Sample 1 dummy command (see <code>CrPsInCmdDumSample1.h</code>) and
 *   configure it such that: its acceptance, start and progress checks are passed but its
 *   termination check fails and verify that no service 1 reports are generated for it.
 * .
 * @verify Procedure, Command Verification Success, OUTFACTORY_FAIL branch
 * @verify Procedure, Command Verification Failed, OUTFACTORY_FAIL branch
 * @verify Procedure, Command Progress Success, OUTFACTORY_FAIL branch
 * @verify Procedure, Command Progress Failure, OUTFACTORY_FAIL branch
 * @return 1 if the test is successful; zero otherwise
 */
CrFwBool_t CrPsVerTestCase5();

#endif /* CRPS_VERTESTCASES_H_ */
