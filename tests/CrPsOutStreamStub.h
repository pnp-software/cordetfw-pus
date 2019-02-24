/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Interface for the OutStream stub.
 * The OutStream stub is used in the test suite of the PUS Extension
 * of the CORDET Framework.
 *
 * This stup is configured by default to accept the handover of a packet
 * and to store it in a ring buffer.
 * A function is provided to access the entries in the ring buffer.
 *
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This file is part of the CORDET Framework.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#ifndef CRPS_OUTSTREAMSTUB_H_
#define CRPS_OUTSTREAMSTUB_H_

/* Include configuration files */
#include "CrFwUserConstants.h"
/* Include Framework Files */
#include "CrFwConstants.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"

/**
 * Dummy implementation of an initialization or configuration check for an OutStream.
 * The outcome of this check is given by the value of a settable flag (<code>checkFlag</code>)
 * whose value is set through function <code>::CrPsOutStreamStubSetCheckFlag</code>
 * (the default value represents "initialization successful").
 * @param prDesc the initialization or configuration procedure descriptor (this parameter
 * is not used).
 */
void CrPsOutStreamStubDummyCheck(FwPrDesc_t prDesc);

/**
 * Set the value of the check flag which determines the outcome of the dummy check of
 * <code>::CrPsOutStreamStubDummyCheck</code> (the default value represents "check successful").
 * @param flag the check flag
 */
void CrPsOutStreamStubSetCheckFlag(CrFwBool_t flag);

/**
 * Dummy implementation of a configuration action for an OutStream.
 * The outcome of this implementation is given by the value of a settable flag
 * (<code>actionFlag</code>) whose value is set through function
 * <code>::CrPsOutStreamStubSetActionFlag</code>.
 * The default value of the settable flag represents "action successful".
 *
 * Like all application-specific OutStream Initialization Actions, this function
 * also calls the default OutStream Initialization Action (<code>::CrFwOutStreamDefInitAction</code>)
 * to ensure that default initialization actions are performed.
 * The <code>::CrFwOutStreamDefInitAction</code> function dynamically allocates
 * memory for an internal OutStream data structure. In order to avoid memory
 * leaks, function <code>::CrFwOutStreamDefInitAction</code> is only called if
 * the OutStream data structure has not yet been initialized.
 *
 * @param prDesc the initialization or configuration procedure descriptor (this parameter
 * is not used).
 */
void CrPsOutStreamStubInitAction(FwPrDesc_t prDesc);

/**
 * Dummy implementation of a configuration action for an OutStream.
 * This function resets the handover counter to zero.
 * The outcome of the action is given by the value of a settable flag
 * (<code>actionFlag</code>) whose value is set through function
 * <code>::CrPsOutStreamStubSetActionFlag</code>.
 * The default value of the settable flag represents "action successful".
 *
 * Like all application-specific OutStream Configuration Actions, this function
 * also calls the default OutStream Configuration Action.
 *
 * @param prDesc the initialization or configuration procedure descriptor (this parameter
 * is not used).
 */
void CrPsOutStreamStubConfigAction(FwPrDesc_t prDesc);

/**
 * Set the value of the action flag which determines the outcome of the initialization of
 * configuration action.
 * The default value of the settable flag represents "action successful".
 * @param flag the action flag
 */
void CrPsOutStreamStubSetActionFlag(CrFwBool_t flag);

/**
 * Stub function implementing the hand-over operation for the OutStream.
 * This function increments a counter when it is called and returns
 * the value of a pre-defined flag.
 * The value of the counter can be read with function
 * <code>::CrPsOutStreamStubGetHandoverCnt</code>.
 * The value of the flag can be set with function
 * <code>::CrPsOutStreamStubSetHandoverFlag</code>.
 * If flag <code>::CrPsOutStreamStubSetHandoverFlag</code> is true, then
 * the a copy of the packet is stored in a ring buffer.
 * The entries in the ring buffer can be retrieved using function
 * <code>::CrPsOutStreamStubGetPckt</code>.
 * @param pckt the packet (not used in this stub)
 * @return the value of flag <code>pcktHandOverFlag</code>
 */
CrFwBool_t CrPsOutStreamStubPcktHandover(CrFwPckt_t pckt);

/**
 * Return the value of the handover counter which is incremented
 * by the packet handover function in <code>::CrPsOutStreamStubPcktHandover</code>.
 * @return the value of the handover counter
 */
CrFwCounterU1_t CrPsOutStreamStubGetHandoverCnt();

/**
 * Set the value of the handover flag which determines the outcome of the packet
 * handover in <code>::CrPsOutStreamStubPcktHandover</code>.
 * The default value causes the OoutStream to accept the packet handover.
 * @param flag the handover flag
 */
void CrPsOutStreamStubSetHandoverFlag(CrFwBool_t flag);

/**
 * Stub function implementing the shutdown operation for an OutStream.
 * This function increments a counter and then calls the default shutdown
 * operation (<code>::CrFwOutStreamDefShutdownAction</code>).
 * The value of the counter can be read with function
 * <code>::CrPsOutStreamStubGetHandoverCnt</code>.
 * @param smDesc the state machine descriptor of the OutStream
 */
void CrPsOutStreamStubShutdown(FwSmDesc_t smDesc);

/**
 * Return the value of the shutdown counter which is incremented
 * by the packet shutdown function in <code>::CrPsOutStreamStubShutdown</code>.
 * @return the value of the shutdown counter
 */
CrFwCounterU1_t CrPsOutStreamStubGetShutdownCnt();

/**
 * Return the pointer to the i-th most recent packet handed over to the
 * OutStream through function <code>CrPsOutStreamStubPcktHandover</code>.
 * The capacity of the rin buffer is given by constant #CR_PS_OUTSTREAMSTUB_N.
 *
 * @param the index of the packet to be returned (a value of zero returns the
 * last packet entered in the ring buffer; a value of 1 returns the last-but-one
 * packet entered in the ring buffer; and so on)
 * @return the pointer to the i-th most recent packet handed over to the
 * OutStream stub
 */
CrFwPckt_t CrPsOutStreamStubGetPckt(unsigned int i);

#endif /* CRPS_OUTSTREAMSTUB_H_ */
