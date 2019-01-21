/**
 * @file CrPsTstConfig.c
 * @ingroup Serv17
 *
 * @brief Define functions to configure the Test Service (service 17).
 * This module defines:
 * - The initialization function for service 17 (<code>::CrPsTstInit</code>)
 * - The getter functions for the procedures used by the service 17 commands
 * .
 *
 * @constraint The initialization function #CrPsTstConfigInit must be called as part
 * of the initialization of the host application.
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

#ifndef CRPSTSTCONFIG_H_
#define CRPSTSTCONFIG_H_

/** FW Profile function definitions */
#include "FwSmConstants.h"

/** CORDET Framework type definitions */
#include "CrFwConstants.h"

/**
 * Type for the Component Data attached to the procedures which implement the
 * the Start and Progress actions of the (17,3) command.
 */
typedef struct CrPsTstData {
	/** The descriptor of the (17,3) command to which the Start or Progress procedure is attached.
	 * The Start and Progress procedures determine the outcome of the command to which they are
	 * attached.
	 * They therefore need the command descriptor to access its 'outcome' field.
	 */
	FwSmDesc_t cmd17s3;
	/** The descriptor of the (17,4) report triggered by the (17,3) command.
	 * The Procedure implementing the Start Action of a (17,3) command creates a (17,4) report.
	 * THe report is configured by the Progress Action of the (17,3) command.
	 * This field is used to transfer the report instance from the Start Action Procedure to the
	 * Progress Action Procedure.
	 */
	FwSmDesc_t rep17s4;
	/** This flag is set to 1 when the (17,4) report is created by the Start Action of the
	 * (17,3) command and it is reset to 0 if the report is released by the Progress Action
	 * of the (17,3) command.
	 */
	CrFwBool_t isRep17s4Alive;
} CrPsTstData_t;

/**
 * Initialize the Test Service.
 * This function must be called before service 17 can be used in the host application.
 * The function should typically be called as part of the initialization of the host application.
 *
 * This function creates and configures the procedures which implement the Start Action and the
 * Progress Action of the On-Board Connection Command.
 *
 * No check is performed on the successful creation of the test service procedures.
 * This is acceptable because this function is only called during the application initialization
 * phase.
 * Its success or failure can therefore be determined statically.
 *
 * No configuration check (through function <code>::FwPrCheck</code>) is done.
 * Such a check should not be part of the operational implementation of service 17.
 * If it is needed (as is typically the case during the development and debug phase of an application),
 * it should be done in a separate module.
 *
 * The procedure instances can be retrieved using functions <code>::CrPsTstConfigGetStart17s3</code>
 * and <code>::CrPsTstConfigGetPrgr17s3</code>.
 */
void CrPsTstConfigInit();

/**
 * Return the instance of the procedure implementing the Start Action for the (17,3) command.
 * This function should only be called after function <code>::CrPsTstConfigInit</code> (which
 * creates and configures the Start Action procedure) has been called.
 * If the initialization failed, this function might return NULL.
 *
 * @return the descriptor of the procedure implementing the Stat Action of the (17,3) command
 */
FwPrDesc_t CrPsTstConfigGetStart17s3();

/**
 * Return the instance of the procedure implementing the Progress Action for the (17,3) command.
 * This function should only be called after function <code>::CrPsTstConfigInit</code> (which
 * creates and configures the Start Action procedure) has been called.
 * If the initialization failed, this function might return NULL.
 *
 * @return the descriptor of the procedure implementing the Stat Action of the (17,3) command
 */
FwPrDesc_t CrPsTstConfigGetPrgr17s3();


#endif /* CRPSTSTCONFIG_H_ */
