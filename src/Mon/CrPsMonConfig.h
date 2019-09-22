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

/** Type to hold the outcome of performing a monitoring check (return value of a Monitor Procedure) */
struct CrPsMonCheckOutcome_t {
    /** Status of the parameter monitor after execution of the monitoring check */
    CrPsParMonCheckStatus_t monCheckStatus;
    /** Type of the monitor procedure which executed the monitoring check */
    CrPsMonPrType_t monPrType;

};

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
typedef CrPsParMonCheckStatus_t (*CrPsMonPrFnc_t)(CrPsParMonId_t);

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
 * Monitor Procedure implementing an expected value check.
 * This function proceed as follows:
 * - It masks the monitored parameter with its "expected value check mask"
 * - It compares the result of the masking with the expected value of the
 *   monitored parameter
 * - it returns MON_NOT_EXP if expected and masked value do not match and
 * - MON_VALID in all other cases
 * .
 * Both the mask and the expected value are of type #CrPsExpValue_t.
 * The monitored value must be of a type with a size not larger than the size
 * of #CrPsExpValue_t.
 * If the monitored value v has a type with a size smaller than #CrPsExpValue_t,
 * it is first loaded in a variable of type #CrPsExpValue_t and then it is masked.
 *
 * This function assumes the monitored data item to be of unsigned type
 * and to have a size of: 1, 2 or 4.
 * If the latter assumption is not satisfied, an assertion violation is declared.
 *
 * The expected value is stored as parameters in the data pool
 * in array expValue[].
 * Its check mask is stored in the data pool array expValueMask[].
 *
 * @constraint Only data pool items of unsigned integer type may be subjected to
 * an Expected Value Monitoring Check.
 *
 * @param parMonId the identifier of the parameter monitor
 * @return the outcome of the limit check
 */
CrPsParMonCheckStatus_t CrPsMonConfigExpValCheck(CrPsParMonId_t parMonId);

/**
 * Apply a mask to the value of a parameter.
 * This function proceeds as follows:
 * - It assumes the value of the parameter to be masked to be of type #CrPsValMask_t
 *   and retrieves its value from the data pool
 * - It performs a bit-wise operation between the value of the parameeter to be masked
 *   and the mask and returns the results of he bit-wise operation
 * .
 *
 * @constraint Masking operations should only be performed on data items of type
 * #CrPsValMask_t (outcome of function in other cases is implementation-dependent)
 * @param parToBeMasked the index of the parameter monitor
 * @return the function implementing the monitor procedure for the i-th
 * parameter monitor.
 */
CrPsValMask_t CrPsMonConfigMaskParVal(CrPsParId_t parToBeMasked, CrPsValMask_t mask);

/**
 * Get the function implementing the monitor procedure for the i-th
 * parameter monitor.
 *
 * @param i the index of the parameter monitor (starting at zero)
 * @return monPrFnc the function implementing the monitor procedure for the i-th
 * parameter monitor.
 */
CrPsMonPrFnc_t CrPsMonConfigSetMonPrFnc(CrPsParMonId_t i);

/**
 * Define a parameter monitor.
 * This function is used by the (12,5) command and can be used by the user application
 * during the application initialization phase to define the default parameter monitors.
 * No checks are done on the legality of the function arguments and no checks are done
 * to verify that the selected parameter monitor identifier is unused.
 *
 * @constraint The application shall use function #CrPsMonConfigInitParMon during the
 * application initialization phase to define the default parameter monitors.
 *
 * @param parMonId the identifier of the parameter monitor
 * @param parId the identifier of the data pool item being monitored
 * @param monPrType the type of monitor procedure
 * @param per the period of the monitor
 * @param repNmb the repetition number of the monitor
 * @param valDataItemId the identifier of the data item used for validity check of parameter monitor
 * @param valExpVal expected value for validity check of parameter monitor
 * @param valMask the mask used for validity check of parameter monitor
 * @param lim1 the low limit (for out-of-limits monitors) or the mask for the expected value check
 * @param lim1Eid the event identifier for the low limit (for out-of-limits monitors) or
 * for the expected value (for expected value monitors)
 * @param lim2 the upper limit (for out-of-limits monitors) or the expected value
 * for the expected value check
 * @param lim2Eid the event identifier for the upper limit (for out-of-limits monitors) or
 * don't care for expected value monitors1
 */
void CrPsMonConfigInitParMon(CrPsParMonId_t parMonId, CrPsParId_t parId, CrPsMonPrType_t monPrType,
        CrPsMonPer_t per, CrPsMonPer_t repNmb, CrPsParId_t valDataItemId,
        CrPsValMask_t valExpVal, CrPsValMask_t valMask, CrPsThirtytwoBit_t* lim1,
        CrPsEvtId_t lim1Eid, CrPsThirtytwoBit_t* lim2, CrPsEvtId_t lim2Eid);

/*----------------------------------------------------------------------------*/
#endif /* CRPSMONCONFIG_H_ */
