/**
 * @file
 *
 * Interface for configuring the Event Reporting Service.
 *
 * Configuration operations are defined to:
 * - Initialize the data structures used by the Event Reporting Service
 * - Check the legality of an event identifier
 * - Manage the enable/disable status of the event identifier
 * .
 *
 * This module operates on the following data structures:
 * - The List Of Event Identifier: an array holding the list of event identifiers (in increasing
 *   order) for each severity level
 * - The List Event Identifier Enable Status: an array holding the enable status of
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
 * Return true if the event identifier is legal; false otherwise.
 * An event identifier E is legal if a service 5 packet is defined which has E
 * as its event identifier.
 *
 * @param evtId the event identifier
 * @return true if the event identifier is legal; false otherwise
 */
CrFwBool_t CrPsEvtConfigIsEidLegal(CrPsEvtId_t evtId);

/**
 * Return the pointer to the array of disabled event identifiers for the argument severity level.
 * If the severity level is out-of-range, NULL is returned.
 * @return the pointer to the array of disabled event identifiers for the argument severity level
 * or NULL if the severity level is out-of-range
 */
CrPsEvtId_t* CrPsEvtConfigGetListOfDisabledEid(unsigned int severityLevel);

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
