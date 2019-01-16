/**
 * @file
 *
 * Interface for configuring the Event Reporting Service.
 * No configuration operations are defined at framework level.
 * This is therefore an abstract interface for which each application must provide
 * an implementation.
 *
 * The PUS Extension of the CORDET Framework offers an implementation which
 * is used for testing purposes (see CrPsEvtConfig.c).
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
 * Return the severity level corresponding to a given event identifier.
 * @param evtId An event identifier
 * @return the severity level for the argument event identifier (an integer in the
 * range 1..4) or zero if the argument event identifier is not recognized
 */
unsigned int CrPsEvtConfigGetSeverity(CrPsEvtId_t evtId);

/**
 * Initialize the Event Reporting Service.
 * This function must be called before service 1 can be used in the host application.
 * The function should typically be called as part of the initialization of the host application.
 *
 * No initialization actions are defined at framework level but applications should
 * to implement this function to set: (a) the initial enable state of the event
 * identifiers and (b) to allocated each event identifier to its severity level.
 */
void CrPsEvtConfigInit();

/*----------------------------------------------------------------------------*/
#endif /* CRPSEVTCONFIG_H_ */
