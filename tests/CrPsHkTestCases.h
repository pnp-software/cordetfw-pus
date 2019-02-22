/**
 * @file CrPsHkTestCases.h
 * @ingroup PUSTestsuite
 *
 * @brief Declaration of the test cases for the Housekeeping Service.
 * The test cases in this module depend on each other and must be executed in the order
 * in which they are declared.
 *
 * @author Alessandro Pasetti  <pasetti@pnp-software.com>
 *
 * @copyright P&P Software GmbH, 2018 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#ifndef CRPS_HKTESTCASES_H_
#define CRPS_HKTESTCASES_H_

/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"

/**
 * Test the functions in the housekeeping configuration module (CrPsHkConfig.h).
 * The following actions are performed:
 * - Initialize the housekeeping service and then verify the operation to get a free slot in the RDL
 * - Use function #CrPsHkConfigHkRep to load the pre-defined HK reports (SID #LEN_HK_REP_SID_HK_CNT
 *   and #LEN_HK_REP_SID_N_OF_EVT) and then verify that the corresponding SIDs are found in
 *   the RDL at the expected location
 * - Fill up the RDL and then verify that no free RDL slot can be retrieved
 * - Clear all SIDs but those pre-defined for testing purposes by the PUS Extension and verify success
 *   of clear operation
 * .
 * @verify Hk Config, Operation to set the define report in the RDL
 * @verify Hk Config, Operation to clear a SID from the RDL
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsHkTestCase1();

/**
 * Verify the start failure cases for the (3,1) command to create a new housekeeping report.
 * The following actions are performed:
 * - Fill up the RDL and then execute a (3,1) command and verify that the command fails with a
 *   (1,4) report with error code VER_FULL_RDL
 * - Bring the RDL back to its original state and then execute a (3,1) command with an illegal SID
 *   and verify that the command is rejected with a (1,4) report with error code VER_ILL_SID
 * - Execute a (3,1) command with an SID equal to zero
 *   and verify that the command is rejected with a (1,4) report with error code VER_ILL_SID
 * - Execute a (3,1) command with an illegal parameter identifier
 *   and verify that the command is rejected with a (1,4) report with error code VER_ILL_DI_ID
 * - Execute a (3,1) command with a parameter identifier equal to zero
 *   and verify that the command is rejected with a (1,4) report with error code VER_ILL_DI_ID
 * - Execute a (3,1) command with a SID which is already in use
 *   and verify that the command is rejected with a (1,4) report with error code VER_SID_IN_USE
 * - Execute a (3,1) command with an illegal number of data item identifiers
 *   and verify that the command is rejected with a (1,4) report with error code VER_ILL_NID
 * .
 * @verify Create HK Command, Start Failure with error code VER_FULL_RDL
 * @verify Create HK Command, Start Failure with error code VER_ILL_SID
 * @verify Create HK Command, Start Failure with error code VER_ILL_DP_ID
 * @verify Create HK Command, Start Failure with error code VER_ILL_NID
 * @verify Create HK Command, Start Failure with error code VER_SID_IN_USE
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsHkTestCase2();

/**
 * Verify execution of a nominal command to create a new housekeeping report and execution of
 * the report is has loaded.
 * The following actions are performed:
 * - One (3,1) command is created to load a HK report with two data pool items and it is verified that
 *   the report is loaded in the OutManager
 * - It is verified that the newly created HK report is disabled in the RDL and then
 *   the OutManager is executed and it is verified that no report is generated
 * .
 * @verify Create HK Command, Successful execution with error code VER_FULL_RDL
 * @verify Create HK Command, Start Failure with error code VER_ILL_SID
 * @verify Create HK Command, Start Failure with error code VER_ILL_DP_ID
 * @verify Create HK Command, Start Failure with error code VER_ILL_NID
 * @verify Create HK Command, Start Failure with error code VER_SID_IN_USE
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsHkTestCase3();



#endif /* CRPS_HKTESTCASES_H_ */
