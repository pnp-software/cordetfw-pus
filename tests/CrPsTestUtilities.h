/**
 * @file CrPsTestUtilities.h
 * @ingroup PUSTestsuite
 *
 * @brief Declarations of utility functions to support testing of the PUS Extension.
 *
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 *
 * @copyright P&P Software GmbH, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 */

#ifndef CRPS_TESTUTILITIES_H_
#define CRPS_TESTUTILITIES_H_

/* Include PUS Extension files */
#include "CrPsTypes.h"

/* Include framework files */
#include "CrFwConstants.h"

/* Include FW Profile files */
#include "FwSmConstants.h"

/**
 * Create a packet holding a Sample 1 Command with the characteristics specified by the
 * function parameters.
 * The Sample 1 Command belongs to the Dummy Service 255.
 * It is used for testing purposes and is defined in <code>CrPsInCmdDumSample1.h</code>.
 *
 * @param dest the destination of the Sample 1 Command
 * @param accAck the acceptance acknowledge flag of the Sample 1 Command
 * @param startAck the start acknowledge flag of the Sample 1 Command
 * @param prgAck the progress acknowledge flag of the Sample 1 Command
 * @param termAck the termination acknowledge flag of the Sample 1 Command
 * @param seqCnt the sequence counter of the Sample 1 Command
 * @param group the groupd of the Sample 1 Command
 * @return the packet holding the Sample 1 Command could be created, false otherwise
 */
 CrFwPckt_t CrPsTestUtilitiesCreateSAmple1Pckt(CrFwDestSrc_t dest, CrFwBool_t accAck, CrFwBool_t startAck,
         CrFwBool_t prgAck, CrFwBool_t termAck, CrFwSeqCnt_t seqCnt, CrFwGroup_t group);

/**
 * Function to verify that the i-th entry in the POCL of an OutManager contains an OutComponent
 * of a given type, sub-type, and discriminant.
 * When an OutComponent is loaded onto an OutManager, it is stored in its "Pending Out-Component List"
 * or POCL.
 * This function extracts the i-th entry in the POCL and checks whether its type and sub-type
 * match the type and sub-type values given as function parameters.
 * If the argument discriminant is different from zero, it also checks whether there is a match for
 * the discriminant value.
 * If the i-th entry in the POCL is empty, the function return false.
 *
 * @param outManager the OutManager whose POCL is checked
 * @param i the index of the entry in the POCL which is checked (starting from zero)
 * @param servType the expected type of the OutComponent at the i-th position in the POCL
 * @param servSubType the expected sub-type of the OutComponent at the i-th position in the POCL
 * @param  disc the expected value of the discriminant at the i-th position in the POCL (or zero if
 * no check on the discriminant is desired)
 * @return true if the i-th entry in the POCL has the stated type, sub-type and discriminant, false otherwise
 */
CrFwBool_t CrPsTestUtilitiesCheckOutManagerCmp(FwSmDesc_t outManager, int i,
                          CrFwServType_t servType, CrFwServSubType_t servSubType, CrFwDiscriminant_t disc);

/**
 * Function to verify that the i-th entry in the POCL of an OutManager contains a service 1 failure
 * report of a certain sub-type, failure code, and failure data.
 * When an OutComponent is loaded onto an OutManager, it is stored in its "Pending Out-Component List"
 * or POCL.
 * This function extracts the i-th entry in the POCL and checks whether its type is 1 and its sub-type,
 * failure code and failure data match the sub-type, failure code and failure data given as function parameters.
 * If the i-th entry in the POCL is empty, the function return false.
 *
 * @param outManager the OutManager whose POCL is checked
 * @param i the index of the entry in the POCL which is checked (starting from zero)
 * @param servSubType the expected sub-type of the OutComponent at the i-th position in the POCL
 * @param failCode the expected value of the failure code at the i-th position in the POCL (or zero if
 * no check on the discriminant is desired)
 * @param failData the expected value of the failure data at the i-th position in the POCL (only checked
 * if the discriminant is non-zero and the value of <code>failData</code> is non-zero)
 * @return true if the i-th entry in the POCL has the stated sub-type, failure code, and failure data, false otherwise
 */
CrFwBool_t CrPsTestUtilitiesCheckOutManagerCmdRejRep(FwSmDesc_t outManager, int i,
                          CrFwServSubType_t servSubType, CrPsFailCode_t failCode, CrPsFailData_t failData);

/**
 * Convenience function to print to stdout the content of the POCL of the argument OutManager.
 * @param outManager the OutManager whose POCL is checked
 */
void CrPsTestUtilitiesPrintOutManagerPOCL(FwSmDesc_t outManager);

/**
 * Return the item which is currently loaded in the i-th entry of the PCRL of the argument InManager.
 *
 * @param inManager the InManager
 * @param i the index of the entry in the PCRL
 * @return the entry in the i-th element of the PCRL (starting from zero)
 */
FwSmDesc_t CrPsTestUtilitiesGetItemFromInManager(FwSmDesc_t inManager, int i);

/**
 * Return the OutComponent which is currently loaded in the i-th entry of the POCL of the argument OutManager.
 *
 * @param outManager the outManager
 * @param i the index of the entry in the PCRL
 * @return the entry in the i-th element of the POCL (starting from zero)
 */
FwSmDesc_t CrPsTestUtilitiesGetItemFromOutManager(FwSmDesc_t outManager, int i);

/**
 * Clear all entries in the RDL.
 */
void CrPsTestUtilitiesClearRDL();

/**
 * Reset the framework components in preparation for a new test.
 * This function:
 * - Sets the application error code to 'no error'
 * - Initializes and configures the frist OutManager
 * - Initializes and configures the OutLoader
 * - Initializes and configures the OutFactory
 * - Initializes and configures the OutRegistry
 * - Initializes and configures the first InManager
 * - Initializes and configures the InFactory
 * - Initializes and configures the first OutStream
 * .
 */
void CrPsTestUtilitiesResetFw();

#endif /* CRPS_TESTUTILITIES_H_ */
