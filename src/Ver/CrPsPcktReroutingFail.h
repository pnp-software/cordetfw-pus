/**
 * @file
 * This header file declares the function to create one instance of the CrPsPcktReroutingFail procedure.
 * The procedure is configured with a set of function pointers representing the non-default
 * actions and guards of the procedure. Some of these functions may also be declared in
 * this header file in accordance with the configuration of the procedure in the FW Profile
 * Editor. In the latter case, the user has to provide an implementation for these functions
 * in a user-supplied body file.
 *
 * This header file has been automatically generated by the FW Profile Editor.
 * The procedure created by this file is shown in the figure below.
 * @image html CrPsPcktReroutingFail.png
 *
 * @author FW Profile code generator version 5.23
 * @date Created on: May 19 2019 17:58:46
 */

/* Make sure to include this header file only once */
#ifndef CRPSPCKTREROUTINGFAIL_H_
#define CRPSPCKTREROUTINGFAIL_H_

/* FW Profile constant definitions */
#include "FwPrConstants.h"

/* Action node identifiers */
#define CrPsPcktReroutingFail_N1 (1)		/**< The identifier of action node N1 in procedure CrPsPcktReroutingFail */
#define CrPsPcktReroutingFail_N2 (2)		/**< The identifier of action node N2 in procedure CrPsPcktReroutingFail */
#define CrPsPcktReroutingFail_N3 (3)		/**< The identifier of action node N3 in procedure CrPsPcktReroutingFail */
#define CrPsPcktReroutingFail_N4 (4)		/**< The identifier of action node N4 in procedure CrPsPcktReroutingFail */
#define CrPsPcktReroutingFail_N5 (5)		/**< The identifier of action node N5 in procedure CrPsPcktReroutingFail */
#define CrPsPcktReroutingFail_N6 (6)		/**< The identifier of action node N6 in procedure CrPsPcktReroutingFail */

/**
 * Create a new procedure descriptor.
 * This interface creates the procedure descriptor dynamically.
 * @param prData the pointer to the procedure data.
 * A value of NULL is legal (note that the default value of the pointer
 * to the procedure data when the procedure is created is NULL).
 * @return the pointer to the procedure descriptor
 */
FwPrDesc_t CrPsPcktReroutingFailCreate(void* prData);

/**
 * Action for node N1.
 * <pre>
 * Generate error report 
 * INLOADER_INV_DEST
 * </pre>
 * @param prDesc the procedure descriptor
 */
void CrPsPcktReroutingFailN1(FwPrDesc_t prDesc);

/**
 * Action for node N2.
 * <pre>
 * Retrieve an OutComponent
 * of type (1,10) from the OutFactory
 * </pre>
 * @param prDesc the procedure descriptor
 */
void CrPsPcktReroutingFailN2(FwPrDesc_t prDesc);

/**
 * Action for node N3.
 * <pre>
 * Generate error report
 * OUTFACTORY_FAIL
 * </pre>
 * @param prDesc the procedure descriptor
 */
void CrPsPcktReroutingFailN3(FwPrDesc_t prDesc);

/**
 * Action for node N4.
 * <pre>
 * Configure report (1,10)
 * and load it in the OutLoader
 * </pre>
 * @param prDesc the procedure descriptor
 */
void CrPsPcktReroutingFailN4(FwPrDesc_t prDesc);

/**
 * Action for node N5.
 * <pre>
 * Increment data pool
 * variable nOfReroutingFailed
 * </pre>
 * @param prDesc the procedure descriptor
 */
void CrPsPcktReroutingFailN5(FwPrDesc_t prDesc);

/**
 * Action for node N6.
 * <pre>
 * Update data pool variables
 * pcktIdRerouting, invDestRerouting
 * </pre>
 * @param prDesc the procedure descriptor
 */
void CrPsPcktReroutingFailN6(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION1 to N1.
 * Packet encapsulates a report 
 * @param prDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsPcktReroutingFailG1(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION1 to N2.
 * Else
 * @param prDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsPcktReroutingFailG1E(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION2 to N3.
 * <pre>
 *  OutFactory fails to
 * generate OutComponent 
 * </pre>
 * @param prDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsPcktReroutingFailG2(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION2 to N4.
 *  Else 
 * @param prDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsPcktReroutingFailG2E(FwPrDesc_t prDesc);

#endif /* CrPsPcktReroutingFail_H_ */

