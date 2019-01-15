/**
 * @file CrFwInStreamUserPar.h
 * @ingroup PUSTestsuite
 * @ingroup PUSTestconfig 
 * User-modifiable parameters for the InStream components (see <code>CrFwInStream.h</code>).
 * This file defines all the user-modifiable parameters for the InStream.
 * Users will normally have to modify this file as part of framework instantiation process.
 *
 * The parameters defined in this file determine the configuration of the InStream Components.
 * The value of these parameters cannot be changed dynamically.
 *
 * The default values defined in this file are those used for the testing of the
 * PUS Extension of the CORDET Framework.
 *
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#ifndef CR_FW_INSTREAM_USERPAR_H_
#define CR_FW_INSTREAM_USERPAR_H_

/* Include framework files */
#include "CrFwInStreamStub.h"
#include "InStream/CrFwInStream.h"
#include "BaseCmp/CrFwResetProc.h"
/* Include test suite files */

/**
 * The number of InStream components in the application.
 * The value of this constant must be smaller than the range of the <code>::CrFwCounterU1_t</code>
 * integer type.
 */
#define CR_FW_NOF_INSTREAM 2

/**
 * The sizes of the packet queues in the InStream components.
 * Each InStream has one packet queue.
 * This constant defines the size of the packet queue of the i-th InStream.
 * The size of the packet queue represents the maximum number of packets which
 * may remain pending in the packet queue.
 * The size of a packet queue must be a positive integer (i.e. it is not legal
 * to define a zero-size packet queue).
 */
#define CR_FW_INSTREAM_PQSIZE {3,3}

/**
 * The number of groups of the InStream components.
 * The number of groups must be a positive integer.
 * This array defines the number of groups of the i-th InStream.
 */
#define CR_FW_INSTREAM_NOF_GROUPS {1,2}

/**
 * The packet source which is managed by the InStream component.
 * Each InStream is responsible for collecting packets from one packet source.
 * This constant is the initializer for the array which defines the packet source
 * associated to the i-th InStream.
 */
#define CR_FW_INSTREAM_SRC {1,2}

/**
 * The functions implementing  the Packet Collect Operations of the InStream components.
 * Each InStream component needs to be able to collect a packet from the middleware.
 * The function implementing this packet collect operation is one of the
 * adaptation points of the framework.
 * This array defines the packet collect operations for the InStream.
 * The items in the arrays must be function pointers of type:
 * <code>::CrFwPcktCollect_t</code>.
 *
 * The packet collection operations defined in this file are the ones provided
 * by the InStream stub of <code>CrFwInStreamStub.h</code>.
 */
#define CR_FW_INSTREAM_PCKTCOLLECT {&CrFwInStreamStubPcktCollect,  \
									&CrFwInStreamStubPcktCollect}

/**
 * The functions implementing the Packet Available Check Operations of the InStream
 * components.
 * Each InStream component needs to be able to check whether the middleware is in
 * state WAITING (no packet is available for collection) or PCKT_AVAIL (a packet is
 * available for collection).
 * The functions which query the middleware to check whether a packet is available
 * or not is one of the adaptation points of the framework.
 * This array defines the Packet Available Check Operations for the InStream.
 * The items in the array must be function pointers of type:
 * <code>::CrFwPcktAvailCheck_t</code>.
 *
 * The packet available check operations defined in this file are the ones provided
 * by the InStream stub of <code>CrFwInStreamStub.h</code>.
 */
#define CR_FW_INSTREAM_PCKTAVAILCHECK {&CrFwInStreamStubIsPcktAvail,  \
									   &CrFwInStreamStubIsPcktAvail}

/**
 * The functions implementing the Initialization Check of the InStream components.
 * The InStream components are derived from the Base Component and they therefore
 * inherit its Initialization Procedure (see <code>CrFwInitProc.h</code>).
 * The initialization procedure must be configured with two actions:
 * the Initialization Action and the Initialization Check.
 * This constant defines the functions implementing the Initialization Checks
 * for the the InStream components.
 * The items in the array must be function pointers of type:
 * <code>FwPrAction_t</code>.
 *
 * Function <code>::CrFwBaseCmpDefInitCheck</code> can be used as a default
 * implementation for this function.
 *
 * The Initialization Check functions defined for the InStreams are
 * the default Initialization Check functions <code>::CrFwBaseCmpDefInitCheck</code>
 * offered by the base component.
 */
#define CR_FW_INSTREAM_INITCHECK {&CrFwBaseCmpDefInitCheck, \
								  &CrFwBaseCmpDefInitCheck}

/**
 * The functions implementing the Initialization Action of the InStream components.
 * The InStream components are derived from the Base Component and they therefore
 * inherit its Initialization Procedure (see <code>CrFwInitProc.h</code>).
 * The initialization procedure must be configured with two actions:
 * the Initialization Action and the Initialization Check.
 * This constant defines the functions implementing the Initialization Actions
 * for the the InStream components.
 * The items in the array must be function pointers of type:
 * <code>FwPrAction_t</code>.
 *
 * Function <code>::CrFwInStreamDefInitAction</code> can be used as a default
 * implementation for this function.
 * This function initializes the internal data structures for the InStream.
 * An application-specific Initialization Action should therefore include a call
 * to this function.
 *
 * The Initialization Action functions defined in this file are the default
 * Initialization Action functions <code>::CrFwInStreamDefInitAction</code>
 * offered by the InStream component.
 */
#define CR_FW_INSTREAM_INITACTION {&CrFwInStreamDefInitAction, \
								   &CrFwInStreamDefInitAction}

/**
 * The functions implementing the Configuration Check of the InStream components.
 * The InStream components are derived from the Base Component and they therefore
 * inherit its Reset Procedure (see <code>CrFwResetProc.h</code>).
 * The reset procedure must be configured with two actions:
 * the Configuration Action and the Configuration Check.
 * This constant defines the functions implementing the Configuration Checks
 * for the the InStream components.
 * The items in the array must be function pointers of type:
 * <code>FwPrAction_t</code>.
 *
 * Function <code>::CrFwBaseCmpDefConfigCheck</code> can be used as a default
 * implementation for this function.
 *
 * The Configuration Check functions defined in this file are the default
 * Configuration Check functions <code>::CrFwBaseCmpDefConfigCheck</code>
 * offered by the Base Component.
 */
#define CR_FW_INSTREAM_CONFIGCHECK {&CrFwBaseCmpDefConfigCheck, \
								    &CrFwBaseCmpDefConfigCheck}

/**
 * The functions implementing the Configuration Action of the InStream components.
 * The InStream components are derived from the Base Component and they therefore
 * inherit its Reset Procedure (see <code>CrFwResetProc.h</code>).
 * The reset procedure must be configured with two actions:
 * the Configuration Action and the Configuration Check.
 * This constant defines the functions implementing the Configuration Actions
 * for the the InStream components.
 * The items in the array must be function pointers of type:
 * <code>FwPrAction_t</code>.
 *
 * Function <code>::CrFwInStreamDefConfigAction</code> can be used as a default
 * implementation for this function.
 * This function initializes the internal data structures for the InStream.
 * An application-specific Configuration Action should therefore include a call
 * to this function.
 *
 * The Configuration Action functions defined in this file are the default
 * Configuration Action functions <code>::CrFwInStreamDefConfigAction</code>
 * offered by the InStream component.
 */
#define CR_FW_INSTREAM_CONFIGACTION {&CrFwInStreamDefConfigAction, \
								     &CrFwInStreamDefConfigAction}

/**
 * The functions implementing the Shutdown Action of the InStream components.
 * The InStream components are derived from the Base Component and they therefore
 * inherit its Shutdown Action (see <code>CrFwBaseCmp.h</code>).
 * This constant defines the shutdown functions for the the InStream components.
 * The items in the array must be function pointers of type:
 * <code>FwSmAction_t</code>.
 *
 * Function <code>::CrFwInStreamDefShutdownAction</code> can be used as a default
 * implementation for this function.
 * This function initializes the internal data structures for the InStream.
 * An application-specific Shutdown Action should therefore include a call
 * to this function.
 *
 * The Shutdown Action functions defined n this file are the default
 * Shutdown Action functions <code>::CrFwInStreamDefShutdownAction</code>
 * offered by the InStream component.
 */
#define CR_FW_INSTREAM_SHUTDOWNACTION {&CrFwInStreamDefShutdownAction, \
							     	   &CrFwInStreamDefShutdownAction}

#endif /* CR_FW_INSTREAM_USERPAR_H_ */
