/**
 * @file CrPsTstTestCases.h
 * @ingroup PUSTestsuite
 *
 * @brief Declaration of the test cases for the Test Service Components.
 * The test cases in this module depend on each other and must be executed in the order
 * in which they are declared.
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
 */

#ifndef CRPS_TSTTESTCASES_H_
#define CRPS_TSTTESTCASES_H_

/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"

/**
 * Test the getter and setter functions for service 17.
 * The following actions are performed:
 * - Create a (17,2) report and check its header parameters
 * - Create a (17,3) command and check its application parameters
 * - Create a (17,4) report and check its header parameters
 * - Check the service 17 data pool parameters
 * .
 * @verify Packet, Test service parameters
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsTstTestCase1();

/**
 * Test the Are-You-Alive Command and Reports (17,1) and (17,2) of the Test Service.
 * This test performs the following actions:
 * - Initialize service 17
 * - Instantiate and configure the OutFactory, the InFactory and OutManager
 * - Instantiate and execute a (17,1) command and it verifies that this results in a
 *   a (17,2) report being instantiated and loaded in the OutManager
 * - Execute again the (17,1) command and verifies that it terminates
 * - Execute the (17,2) report and verifies that it terminates
 * - Repeat the previous steps for the case where the OutFactory is full and verifies
 *   that the (17,1) command fails its Start Action
 * .
 * @verify Command, Are-You-Alive, Start Action Nominal Branch
 * @verify Command, Are-You-Alive, Start Action Failure Branch
 * @verify Command, Are-You-Alive, Progress Action
 * @verify Report, Are-You-Alive
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsTstTestCase2();

/**
 * Test the Test Connection Service of service 17 when the command has an
 * illegal destination for the connection test.
 * This test performs the following actions:
 * - Initialize the set of legal destinations and the time-out for the (17,3) command
 * - Create a (17,3) command with an illegal destination for the connection test
 * - Execute the (17,3) and verify that its start action fails and that a (1,4) report is generated
 *   with failure code VER_REP_CR_FD
 * - Create a (17,3) command with a legal destination for the connection test
 * - Execute the (17,3) command and verify that a (17,1) command is issued to the correct destination
 * - Create a (17,2) report as a response to the (17,1) and execute it
 * - Execute again the (17,3) command and verify that it completes its execution
 * .
 * @verify Command, Connection Test, Start Action Illegal Destination Branch
 * @verify Command, Connection Test, Start Action Nominal Branches
 * @verify Command, Connection Test, Progress Action Left Branch
 * @verify Command, Connection Test, Progress Action Middle Branch
 * @verify Report, Start Failure, Failure Code VER_REP_CR_FD
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsTstTestCase3();

/**
 * Test failure branches of the (17,3) start and progress actions.
 * This test relies on the initialization of the service 17 data pool parameters made in test
 * <code>CrPsServTestConnTestCase2</code>.
 * The following actions are performed in this test:
 * - Create a (17,3) command at a time when there is only one free slot in the OutFactory and then
 *   execute it and verify that the (17,4) OutComponent cannot be allocated and therefore the
 *   command terminates with a Start Failure
 * - Advance time to the point where it has a non-zero value
 * - Create a (17,3) command with nominal parameters and at a time when there are free slots
 *   in the OutFactory and then execute it once. This causes a (17,1) to be created and loaded into
 *   its OutManager
 * - Execute the (17,3) a few more times and verify that it remains pending waiting for the (17,2)
 * - Set the time-out to a very small value such that the time-out is exceeded
 *   and then execute again the (17,3) and verify that it is aborted because the time-out has expired
 * .
 * @verify Command, Connection Test, Connection Test, Start Action Retrieval of Second OutComponent Fails
 * @verify Connection Test Command, Start Action Retrieval of First OutComponent Fails
 * @verify Connection Test Command, Progress Action right Branch (failure)
 * @verify Report, Start Failure, Failure Code VER_REP_CR_FD
 * @verify Report, Termination Failure, Failure Code VER_TST_TO
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrPsTstTestCase4();

#endif /* CRPS_TSTTESTCASES_H_ */
