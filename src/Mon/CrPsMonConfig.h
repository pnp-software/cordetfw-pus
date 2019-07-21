/**
 * @file
 * @ingroup man_mon
 *
 * Interface for configuring the On-Board Monitoring Service.
 *
 * This module defines operation to:
 * - Initialize the data structures used by the Monitoring Service
 * - Initialize the PMDL
 * - Implement the monitor procedures
 * .
 *
 * This module operates on the <i>Parameter Monitor Definition List</i> (PMDL).
 * The PMDL holds #MON_N_PMON <i>Parameter Monitor Definitions</i>.
 * Each Parameter Monitor Definition defines a parameter monitor.
 * The items which define the PMDL are defined in the data pool.
 *
 * Each monitor procedure is implemented by a function.
 * This module defines the functions implementing the out-of-limit and
 * expected value monitor procedures.
 * The monitoring limits are stored in the data pool as generic 32-bit numbers
 * which, depending on the type of the monitored parameter, are cast to
 * float, integer or unsigned integer.
 *
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 *
 * @copyright P&P Software GmbH, 2019
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */
#ifndef CRPSMONCONFIG_H_
#define CRPSMONCONFIG_H_

#include "CrPsTypes.h"

/**
 * Type for a pointer to a function implementing a service 12 Monitor Procedure.
 * The function takes as an input the identifier of the parameter monitor; it
 * executes the check encapsulated in the parameter monitor, and it returns the
 * new status of the parameter monitor.
 * A function conforming to this type should implement the following behaviour:
 * - It extracts the identifier of the monitored parameter from the parameter monitor
 * - It retrieves the value of the monitored parameter from the data pool
 * - It retrieves from the parameter monitor the type of monitoring check to be
 *   applied to the monitored parameter
 * - It retrieves from the data pool the monitoring limits applicable to the
 *   monitored parameter
 * - It performs the monitoring check and returns its outcome
 * .
 */
typedef CrPsValCheckExpVal_t (*CrPsMonPrFnc_t)(CrPsParMonId_t);

/**
 * Initialize the Parameter Monitor Definition List (PMDL).
 * This function must be called before the monitoring service can be used in the host application.
 * The function should typically be called as part of the initialization of the host application.
 * The following actions are performed by this function:
 * - Instantiate the Monitoring Function Procedure
 * - Initialize the PMDL through function #CrPsMonConfigInitPMDL
 * .
 * @constraint If an application needs pre-defined parameter monitors, it must define them in the
 * PMDL as part of its initialization.
 */
void CrPsMonConfigInit();

/**
 * Return the descriptor of the Parameter Monitoring Procedure.
 *
 * @return the descriptor of the Parameter Monitoring Procedure
 */
FwPrDesc_t CrPsConfigGetParMonPr();

/**
 * Initialize the Parameter Monitor Definition List (PMDL).
 * The following actions are performed by this function:
 * - All period counters in the PMDL are initialized to zero
 * - All repetition counters in the PMDL are initialized to zero
 * - All checking status in the PMDL are initialized to UNCHECKED
 * - The number of available parameter monitors is set to MON_N_PMON
 * - The number of enabled parameter monitors is set to zero
 * .
 */
void CrPsMonConfigInitPMDL();

/**
 * Monitor Procedure implementing a limit check for a real-valued data item.
 * This function returns:
 * - MON_ABOVE if the parameter value is above its upper limit
 * - MON_BELOW if the parameter value is below its lower limit
 * - MON_VALID in all other cases
 * .
 * The lower and upper limits are stored as parameters in the data pool
 * in arrays lowerLimit[] and upperLimit[].
 *
 * The function first retrieves from the data pool the size of the monitored
 * parameter.
 * If the size is 4, the function assumes the monitored parameter to be of
 * type 'float'.
 * If the size is 8, the function assumes the monitored parameter to be of
 * type 'double'.
 * In other cases, the application error code is set to #CrPsIllRMonParSize
 * and the function returns MON_VALID.
 *
 * This function assumes that:
 * - The data pool item pointed at by <code>parMonId</code>
 *   is either a float or a double
 * - The 'float' type is 4-byte wide
 * - The 'double' type is 8-byte wide
 * .
 * The bottom two assumptions are verified through an assertion.
 *
 * @param parMonId the identifier of the parameter monitor
 * @return the outcome of the limit check
 */
CrPsParMonCheckStatus_t CrPsMonConfigOutOfLimitCheckR(CrPsParMonId_t parMonId);

/**
 * Monitor Procedure implementing a limit check for a signed integer-valued data item.
 * This function returns:
 * - MON_ABOVE if the parameter value is above its upper limit
 * - MON_BELOW if the parameter value is below its lower limit
 * - MON_VALID in all other cases
 * .
 * The lower and upper limits are stored as parameters in the data pool
 * in arrays lowerLimit[] and upperLimit[].
 *
 * This function assumes that:
 * - The data pool item pointed at by <code>parMonId</code>
 *   is a signed integer type of 1, 2 or 4 bytes of size
 * - The 'int' type is 4-byte wide
 * - The 'short int' type is 2-byte wide
 * - The 'char' type is 1-byte wide
 * .
 * The bottom three assumptions are verified through an assertion.
 *
 * @param parMonId the identifier of the parameter monitor
 * @return the outcome of the limit check
 */
CrPsParMonCheckStatus_t CrPsMonConfigOutOfLimitCheckSI(CrPsParMonId_t parMonId);

/**
 * Monitor Procedure implementing a limit check for an unsigned integer-valued data item.
 * This function returns:
 * - MON_ABOVE if the parameter value is above its upper limit
 * - MON_BELOW if the parameter value is below its lower limit
 * - MON_VALID in all other cases
 * .
 * The lower and upper limits are stored as parameters in the data pool
 * in arrays lowerLimit[] and upperLimit[].
 *
 * This function assumes that:
 * - The data pool item pointed at by <code>parMonId</code>
 *   is an unsigned integer type of 1, 2 or 4 bytes of size
 * - The 'unsigned int' type is 4-byte wide
 * - The 'unsigned short int' type is 2-byte wide
 * - The 'unsigned char' type is 1-byte wide
 * .
 * The bottom three assumptions are verified through an assertion.
 *
 * @param parMonId the identifier of the parameter monitor
 * @return the outcome of the limit check
 */
CrPsParMonCheckStatus_t CrPsMonConfigOutOfLimitCheckUI(CrPsParMonId_t parMonId);

/**
 * Monitor Procedure implementing an expected value check for unsigned integers.
 * This function returns:
 * - MON_NOT_EXP if the parameter value differs from its expected value
 * - MON_VALID in all other cases
 * .
 * The expected value is stored as parameters in the data pool
 * in array expValue[].
 *
 * @param parMonId the identifier of the parameter monitor
 * @return the outcome of the limit check
 */
CrPsParMonCheckStatus_t CrPsMonConfigExpValCheckUI(CrPsParMonId_t parMonId);

/**
 * Monitor Procedure implementing an expected value check for signed integers.
 * This function returns:
 * - MON_NOT_EXP if the parameter value differs from its expected value
 * - MON_VALID in all other cases
 * .
 * The expected value is stored as parameters in the data pool
 * in array expValue[].
 *
 * @param parMonId the identifier of the parameter monitor
 * @return the outcome of the limit check
 */
CrPsParMonCheckStatus_t CrPsMonConfigExpValCheckSI(CrPsParMonId_t parMonId);

/**
 * Return the function implementing the monitor procedure for the i-th
 * parameter monitor.
 *
 * @param i the index of the parameter monitor
 * @return the function implementing the monitor procedure for the i-th
 * parameter monitor.
 */
CrPsMonPrFnc_t CrPsMonConfigGetMonPrFnc(CrPsParMonId_t i);

/**
 * Set the function implementing the monitor procedure for the i-th
 * parameter monitor.
 *
 * @param i the index of the parameter monitor
 * @param monPrFnc the function implementing the monitor procedure for the i-th
 * parameter monitor.
 */
void CrPsMonConfigSetMonPrFnc(CrPsParMonId_t i, CrPsMonPrFnc_t monPrFnc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSMONCONFIG_H_ */
