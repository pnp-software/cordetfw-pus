/**
 * @file
 * This header file declares the function to create one instance of the CrPsCmdVerFail procedure.
 * The procedure is configured with a set of function pointers representing the non-default
 * actions and guards of the procedure. Some of these functions may also be declared in
 * this header file in accordance with the configuration of the procedure in the FW Profile
 * Editor. In the latter case, the user has to provide an implementation for these functions
 * in a user-supplied body file.
 *
 * This header file has been automatically generated by the FW Profile Editor.
 * The procedure created by this file is shown in the figure below.
 * @image html CrPsCmdVerFail.png
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Aug 26 2018 1:44:38
 */

/** Make sure to include this header file only once */
#ifndef CRPSCMDVERFAIL_H_
#define CRPSCMDVERFAIL_H_

/** FW Profile function definitions */
#include "FwPrConstants.h"

/** Action node identifiers */
#define CrPsCmdVerFail_N2 (1)		/* The identifier of action node N2 in procedure CrPsCmdVerFail */
#define CrPsCmdVerFail_N3 (2)		/* The identifier of action node N3 in procedure CrPsCmdVerFail */
#define CrPsCmdVerFail_N4 (3)		/* The identifier of action node N4 in procedure CrPsCmdVerFail */
#define CrPsCmdVerFail_N5 (4)		/* The identifier of action node N5 in procedure CrPsCmdVerFail */
#define CrPsCmdVerFail_N6 (5)		/* The identifier of action node N6 in procedure CrPsCmdVerFail */

/**
 * Create a new procedure descriptor.
 * This interface creates the procedure descriptor dynamically.
 * @param prData the pointer to the procedure data.
 * A value of NULL is legal (note that the default value of the pointer
 * to the procedure data when the procedure is created is NULL).
 * @return the pointer to the procedure descriptor
 */
FwPrDesc_t CrPsCmdVerFailCreate(void* prData);

/**
 * Action for node N2.
 * <pre>
 * Retrieve an OutComponent of
 * type (1,2), (1,4) or (1,8) from OutFactory
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmdVerFailN2(FwPrDesc_t prDesc);

/**
 * Action for node N3.
 * <pre>
 * Generate error report
 * OUTFACTORY_FAIL
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmdVerFailN3(FwPrDesc_t prDesc);

/**
 * Action for node N4.
 * <pre>
 * Configure report and
 * load it in the OutLoader
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmdVerFailN4(FwPrDesc_t prDesc);

/**
 * Action for node N5.
 * <pre>
 * Increment data pool
 * variable nOfXyFailed
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmdVerFailN5(FwPrDesc_t prDesc);

/**
 * Action for node N6.
 * <pre>
 * Update data pool variable
 * pcktIdXyzFailed and failCodeXyzFailed
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmdVerFailN6(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION2 to N3.
 * <pre>
 *  OutFactory fails to
 * generate OutComponent 
 * </pre>
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmdVerFailG1(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION2 to N4.
 *  Else 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmdVerFailG1E(FwPrDesc_t prDesc);

#endif /* CrPsCmdVerFail_H_ */