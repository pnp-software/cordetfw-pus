/**
 * @file CrPsEvtTestCases.h
 * @ingroup PUSTestsuite
 *
 * @brief Declaration of the test cases for the Event Reporting Service.
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

#ifndef CRPS_EVTTESTCASES_H_
#define CRPS_EVTTESTCASES_H_

/* Include framework files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"

/**
 * Test the functions in the event configuration module.
 * The following actions are performed:
 * - The position and severity of an event identifier are retrieved using function
 *   #CrPsEvtConfigGetEidPos and their correctness is verified
 * - An attempt is made to retrieve the position and severity of a non-existent event identifier
 *   using function #CrPsEvtConfigGetEidPos and it is verified that the function detects
 *   the illegal event
 * - The enable status of an event identifier is set and its value is then verified
 * - The enable status of a non-existent event identifier is set and it is verified that the
 *   non-existence of the event identifier is detected
 * - The severity level of an event identifier is recovered and its correctness is verified
 * - The severity level of a non-existent event identifier is recovered and it is verified that
 *   the non-existence of the event identifier is recognized
 * - Function #CrPsEvtConfigGetNextEvtId to iterate over the event identifier is verified
 *   for legal and illegal input values
 * .
 * @verify Evt Config, Operation to retrieve position and severity level of event identifier
 * @verify Evt Config, Operation to set the enable status of an event identifier
 * @verify Evt Config, Operation to read the enable status of an event identifier
 * @verify Evt Config, Operation to read the severity level of an event identifier
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsEvtTestCase1();

/**
 * Test the generation of event reports pre-defined by the PUS Extension.
 * The following actions are performed:
 * - Generate the pre-defined event EVT_DUMMY_1 and verify that one event report is
 *   pending in the OutManager and that its type, sub-type and event identifier are
 *   as expected
 * - Verify that the level 1 observables in the data pool have been correctly updated
 *   (last event identifier, time stamp of last event, and number of generated events)
 * - Repeat the previous step for the pre-defined dummy events of severity levels 2 to 4
 * .
 * @verify Event Report 1, Nominal case
 * @verify Event Report 2, Nominal case
 * @verify Event Report 3, Nominal case
 * @verify Event Report 4, Nominal case
 * @verify Data Pool, EvtLastEvtEid_x
 * @verify Data Pool, EvtLastEvtTime_x
 * @verify Data Pool, EvtNOfDetectedEvts_x
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsEvtTestCase2();


#endif /* CRPS_EVTTESTCASES_H_ */
