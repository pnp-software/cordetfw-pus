/**
 * @file
 * @ingroup man_evt
 *
 * Interface for configuring the Event Reporting Service.
 *
 * Configuration operations are defined to:
 * - Initialize the data structures used by the Event Reporting Service
 * - Check the legality of an event identifier
 * - Manage the enable/disable status of the event identifier
 * - Provides an <i>Event Position Buffer</i> to allow different modules to exchange information
 *   about the position of an event identifier between different modules
 * - Provides an <i>iterator</i> to iterate through the event identifiers
 * .
 *
 * This module operates on the following data structures:
 * - The Lists Of Event Identifier: an array holding the list of event identifiers (in increasing
 *   order) for each severity level
 * - The Lists Event Identifier Enable Status: an array holding the enable status of
 *   the event identifiers for each severity level
 * .
 * The event identifiers recognized by this module are those for which a service 5 packet
 * is defined.
 * Thus, event identifier E is recognized at severity level S, if a packet of type (5,S) is
 * defined with event identifier equal to E.
 *
 * @constraint The initialization function #CrPsEvtConfigInit must be called as part of
 * the initialization of the host application.
 *
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 *
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */
#ifndef CRPSEVTCONFIG_H_
#define CRPSEVTCONFIG_H_

#include "CrPsTypes.h"

/**
 * Return the position of the argument event identifier within the List of Event Identifiers
 * of the argument severity level (the first position is 0).
 * If the argument event identifier is undefined or if the severity level is out-of-range,
 * the function returns -1.
 *
 * An event identifierEvent identifier E is legal for severity level S is legal if a packet of type
 * (5,S) has been defined with event identifier E.
 *
 * The severity level is an integer in range [1,4].
 * If the severity level is out of range, the function returns 'false'.
 *
 * @param evtId the event identifier
 * @param severityLevel the severity level (an integer in the range [1,4])
 * @return the position of the event identifier in the List of Event Identifiers for the argument
 * severity level (starting from 0), or -1 if the event identifier is not recognized or
 * the severity level is out-of-range
 */
int CrPsEvtConfigGetEidPos(CrPsEvtId_t evtId, unsigned int severityLevel);

/**
 * Set the enable status of the argument event identifier.
 * The enable status is set both in the List of Event Identifier Enable Status and in
 * the OutRegistry.
 * If the event identifier is not defined, no action is taken and zero is returned;
 * otherwise the event's severity level (an integer in the range 1..4) is returned.
 *
 * @param evtId the event identifier
 * @param enableStatus the enable status
 * @return the event severity level if the event identifier is defined and its enable status is set;
 * zero otherwise
 */
unsigned int CrPsEvtConfigSetEidEnableStatus (CrPsEvtId_t evtId, CrFwBool_t enableStatus);

/**
 * Get the enable status of the argument event identifier.
 * If the event identifier is not defined, 'false' is returned.
 *
 * @param evtId the event identifier
 * @return the enable status
 */
CrFwBool_t CrPsEvtConfigGetEidEnableStatus (CrPsEvtId_t evtId);

/**
 * Return the severity level of an event identifier.
 * If the event identifier is illegal, the function returns zero.
 * An event identifier E is legal if a service 5 packet is defined which has E
 * as its event identifier.
 *
 * @param evtId the event identifier
 * @return the severity level of an event identifier if it is legal; return 0 otherwise
 */
unsigned int CrPsEvtConfigGetSevLevel(CrPsEvtId_t evtId);

/**
 * Return the pointer to the array of event identifiers for the argument severity level.
 * If the severity level is out-of-range, NULL is returned.
 * @return the pointer to the array of disabled event identifiers for the argument severity level
 * or NULL if the severity level is out-of-range
 */
CrPsEvtId_t* CrPsEvtConfigGetListOfEid(unsigned int severityLevel);

/**
 * Return the pointer to the array of event identifier enabled status for the argument severity level.
 * If the severity level is out-of-range, NULL is returned.
 * @return the pointer to the array of disabled event identifiers for the argument severity level
 * or NULL if the severity level is out-of-range
 */
CrFwBool_t* CrPsEvtConfigGetListOfDisabledEid(unsigned int severityLevel);

/**
 * Reset the iterator which iterates over all disabled events.
 * The iterator is accessed through function #CrPsEvtConfigIter.
 */
void CrPsEvtConfigResetIter();

/**
 * Iterate over all disabled event identifiers.
 * The iterator is reset with function #CrPsEvtConfigResetIter.
 * After the iterator has been reset, each call to this function moves the iterator to the next
 * disabled event and returns its event identifier.
 * The iteration is done in order of increasing identifier starting from the first severity 1 event
 * identifier until the last severity 4 event identifier.
 * When the last event identifier is reached, the function returns a zero event identifier and
 * stops the iteration.
 *
 * @param eid the event identifier at which the iterator has stopped in the last call to the
 * function or zero if the iterator has completed the iteration over all event identifiers
 */
void CrPsEvtConfigIter(CrPsEvtId_t* eid);

/**
 * Initialize the Event Reporting Service.
 * This function must be called before service 1 can be used in the host application.
 * The function should typically be called as part of the initialization of the host application.
 *
 * No initialization actions are defined at framework level.
 */
void CrPsEvtConfigInit();

/*----------------------------------------------------------------------------*/
#endif /* CRPSEVTCONFIG_H_ */
