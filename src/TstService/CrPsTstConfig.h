/**
 * @file CrPsTstInit.c
 * @ingroup Serv17
 *
 * @brief Define functions to configure the Test Service (service 17).
 * This module defines the initialization function for service 17 (<code>::CrPsTstInit</code>.
 * This function must be called by the user as part of the initialization of the host application
 * and it defines the functions to access the procedures which implement the Start and Progress
 * actions of the On-Board Connection Command (17,3).
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

#ifndef SRC_TSTSERVICE_CRPSTSTCONFIG_H_
#define SRC_TSTSERVICE_CRPSTSTCONFIG_H_

/**
 * Initialize the Test Service.
 * This function creates and configures the procedures which implement the Start Action and the
 * Progress Action of the On-Board Connection Command.
 * The procedure instances can be retrieved using functions <code>::CrPsTstConfigGetStart17s3</code>
 * and <code>::CrPsTstConfigGetPrgr17s3</code>.
 */
void CrPsTstConfigInit();

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


#endif /* SRC_TSTSERVICE_CRPSTSTCONFIG_H_ */
