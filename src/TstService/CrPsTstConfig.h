/**
 * @file CrPsTstInit.c
 * @ingroup Serv17
 *
 * @brief Define functions to configure the Test Service (service 17).
 * This module defines:
 * - The initialization function for service 17 (<code>::CrPsTstInit</code>)
 * - The getter functions for the procedures used by the service 17 commands
 * .
 * The initialization function must be called as part of the initialization of the host application.
 * The getter functions may be called at any time after the module has been initialized.
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
	 * They need the command descriptor to access its 'outcome' field.
	 */
	FwSmDesc_t cmd17s3;
	/** The descriptor of the (17,4) report triggered by the (17,3) command.
	 * The Procedure implementing the Start Action of a (17,3) command creates a (17,4) report.
	 * THe report is configured by the Progress Action of the (17,3) command.
	 * This field is used to transfer the report instance from the Start Action Procedure to the
	 * Progress Action Procedure.
	 */
	FwSmDesc_t rep17s4;
} CrPsTstData_t;

/**
 * Initialize the Test Service.
 * This function must be called before service 17 can be used in the host application.
 * The function should typically be called as part of the initialization of the host application.
 *
 * This function: (a) creates and configures the procedures which implement the Start Action and the
 * Progress Action of the On-Board Connection Command, and (b) it initializes the data pool parameters
 * for the test service by calling function <code>::initDpTst</code>.
 *
 * The initialization process is declared successful if it was possible to create the two procedure
 * instances.
 * The procedure instances can be retrieved using functions <code>::CrPsTstConfigGetStart17s3</code>
 * and <code>::CrPsTstConfigGetPrgr17s3</code>.
 *
 * No configuration check (through function <code>::FwPrCheck</code> is done.
 * Such a check should not be part of the operational implementation of service 17.
 * If it is needed (as is typically the case during the development and debug phase of an application),
 * it can be done in a separate module.
 *
 * @descCmd17s3 the descriptor of the (17,3) command instance to which the procedures created by this module
 * are attached
 * @return 1 if the initialization was successful and 0 otherwise
 */
CrFwBool_t CrPsTstConfigInit();

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
