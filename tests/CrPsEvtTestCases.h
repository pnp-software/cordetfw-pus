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
 * Test the functions in the event configuration module (CrPsEvtConfig.h).
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
 * .
 * @verify Config, Evt, Operation to retrieve position and severity level of event identifier
 * @verify Config, Evt, Operation to set the enable status of an event identifier
 * @verify Config, Evt, Operation to read the enable status of an event identifier
 * @verify Config, Evt, Operation to read the severity level of an event identifier
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsEvtTestCase1();

/**
 * Test the generation of the dummy event report of severity level 1 pre-defined by the PUS Extension.
 * The following actions are performed:
 * - Generate the pre-defined event EVT_DUMMY_1 and verify that one event report is
 *   pending in the OutManager and that its type, sub-type and event identifier are
 *   as expected
 * - Verify that the level 1 observables in the data pool have been correctly updated
 *   (last event identifier, time stamp of last event, and number of generated events)
 * - Verify that the event identifier is correct and equal to its discriminant
 * .
 * @verify Report, Event Severity 1, Nominal case
 * @verify Data Pool, EvtLastEvtEid_1
 * @verify Data Pool, EvtLastEvtTime_1
 * @verify Data Pool, EvtNOfDetectedEvts_1
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsEvtTestCase2();

/**
 * Test the generation of the dummy event report of severity level 2 pre-defined by the PUS Extension.
 * The following actions are performed:
 * - Generate the pre-defined event EVT_DUMMY_2 and verify that one event report is
 *   pending in the OutManager and that its type, sub-type and event identifier are
 *   as expected
 * - Verify that the level 2 observables in the data pool have been correctly updated
 *   (last event identifier, time stamp of last event, and number of generated events)
 * - Verify that the event identifier is correct and equal to its discriminant
 * .
 * @verify Report, Event Severity 2, Nominal case
 * @verify Data Pool, EvtLastEvtEid_2
 * @verify Data Pool, EvtLastEvtTime_2
 * @verify Data Pool, EvtNOfDetectedEvts_2
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsEvtTestCase3();

/**
 * Test the generation of the dummy event report of severity level 3 pre-defined by the PUS Extension.
 * The following actions are performed:
 * - Generate the pre-defined event EVT_DUMMY_3 and verify that one event report is
 *   pending in the OutManager and that its type, sub-type and event identifier are
 *   as expected
 * - Verify that the level 3 observables in the data pool have been correctly updated
 *   (last event identifier, time stamp of last event, and number of generated events)
 * - Verify that the event identifier is correct and equal to its discriminant
 * .
 * @verify Report, Event Severity 3, Nominal case
 * @verify Data Pool, EvtLastEvtEid_3
 * @verify Data Pool, EvtLastEvtTime_3
 * @verify Data Pool, EvtNOfDetectedEvts_3
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsEvtTestCase4();

/**
 * Test the generation of the dummy event report of severity level 4 pre-defined by the PUS Extension.
 * The following actions are performed:
 * - Generate the pre-defined event EVT_DUMMY_4 and verify that one event report is
 *   pending in the OutManager and that its type, sub-type and event identifier are
 *   as expected
 * - Verify that the level 4 observables in the data pool have been correctly updated
 *   (last event identifier, time stamp of last event, and number of generated events)
 * - Verify that the event identifier is correct and equal to its discriminant
 * .
 * @verify Report, Event Severity 4, Nominal case
 * @verify Data Pool, EvtLastEvtEid_4
 * @verify Data Pool, EvtLastEvtTime_4
 * @verify Data Pool, EvtNOfDetectedEvts_4
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsEvtTestCase5();

/**
 * Test the event enable and disable telecommands in the nominal case of a legal event identifier.
 * The following actions are performed:
 * - Verify that the default enable state of the events is: 'enabled'
 * - Instantiate a command of type (5,6) carrying two legal event identifiers and execute it
 *   and verify that the argument event identifiers are disabled and that the counters of
 *   disabled events has been increased
 * - Instantiate a command of type (5,5) carrying two legal event identifiers and execute it
 *   and verify that the argument event identifiers are enabled and that the counters of
 *   disabled events has been decremented
 * .
 * @verify Command, Enable Generation of Event Identifiers, Multiple legal event identifiers
 * @verify Command, Disable Generation of Event Identifiers, Multiple legal event identifiers
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsEvtTestCase6();

/**
 * Test the event enable and disable telecommands in the case of a mixture of legal and
 * illegal event identifiers.
 * The following actions are performed:
 * - Instantiate a command of type (5,6) carrying one illegal and one legal event identifier and execute it
 *   and verify that the legal event identifiers has been disabled and that the
 *   illegal event identifier has been loaded in verFailData and that a (1,5) report
 *   with failure code VER_ILL_EID has been generated
 * - Instantiate a command of type (5,5) carrying the same identifiers as the (5,6) but
 *   in revere order and execute it
 *   and verify that the legal event identifiers has been enabled and that the
 *   illegal event identifier has been loaded in verFailData and that a (1,5) report
 *   with failure code VER_ILL_EID has been generated
 * .
 * @verify Command, Enable Generation of Event Identifiers, Mixed legal and illegal event identifiers
 * @verify Command, Disable Generation of Event Identifiers, Mixed legal and illegal event identifiers
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsEvtTestCase7();

/**
 * Test the telecommand to report the disabled event identifiers.
 * The following actions are performed:
 * - Disable TWO event identifiers and then instantiate a command of type (5,7) and execute
 *   it and verify that it triggers the generation of one (5,8) report carrying the disabled
 *   identifier
 * - Disable 12 event identifiers  and then instantiate a command of type (5,7) and execute
 *   it and verify that it triggers the generation of two (5,8) reports carrying the disabled
 *   identifiers
 * .
 * @verify Command, Report Disabled Event Identifiers, Nominal case
 * @verify Report, Disabled Event Identifiers, Case of single (5,8) report
 * @verify Report, Disabled Event Identifiers, Case of multiple (5,8) reports
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsEvtTestCase8();

/**
 * Test the event service in a situation where the OutFactory is full and unable to generate
 * new reports.
 * The following actions are performed:
 * - Fill the OutFactory and then attempt to generate a pre-defined event and verify that
 *   an error report of type OUTFACTORY_FAIL is generated
 * - Generate and execute a (5,7) command and verify that no (5,8) report is generated and
 *   than an error report of type OUTFACTORY_FAIL is generated
 * .
 * @verify Generate Pre-Defined Event, Parameterless event OUTFACTORY_FAIL error case
 * @verify Report, Disabled Event Identifiers, Case of full OutFactory
 *
 * @return 1 if the test was successful, 0 otherwise
 */
CrFwBool_t CrPsEvtTestCase9();

#endif /* CRPS_EVTTESTCASES_H_ */
