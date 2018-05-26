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

/**
 * Initialize the Test Service.
 * This function must be called before service 17 can be used in the host application.
 * The function should typically be called as part of the initialization of the host application.
 *
 * This function creates and configures the procedures which implement the Start Action and the
 * Progress Action of the On-Board Connection Command.
 * The initialization process is declared successful if it was possible to create the two procedure
 * instances.
 * The procedure instances can be retrieved using functions <code>::CrPsTstConfigGetStart17s3</code>
 * and <code>::CrPsTstConfigGetPrgr17s3</code>.
 *
 * Note that no configuration check (through function <code>::FwPrCheck</code> is done.
 * Such a check should not be part of the operational implementation of service 17.
 * If it is needed (as is typically the case during the development and debug phase of an application),
 * it can be done in a separate module.
 *
 * @return 1 if the initialization was successful and 0 otherwise
 */
CrFwBool_t CrPsTstConfigInit();

/**
 * Return the instance of the procedure implementing the Start Action for the (17,3) command.
 * This function should only be called after function <code>::CrPsTstConfigInit</code> (which
 * creates and configures the Start Action procedure) has been called.
 */
FwSmDesc_t CrPsTstConfigGetStart17s3();

/**
 * Return the instance of the procedure implementing the Progress Action for the (17,3) command.
 * This function should only be called after function <code>::CrPsTstConfigInit</code> (which
 * creates and configures the Start Action procedure) has been called.
 */
FwSmDesc_t CrPsTstConfigGetPrgr17s3();


#endif /* CRPSTSTCONFIG_H_ */
