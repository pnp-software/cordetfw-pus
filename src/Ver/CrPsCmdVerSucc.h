/**
 * @file
 * This header file declares the function to create one instance of the CrPsCmdVerSucc procedure.
 * The procedure is configured with a set of function pointers representing the non-default
 * actions and guards of the procedure. Some of these functions may also be declared in
 * this header file in accordance with the configuration of the procedure in the FW Profile
 * Editor. In the latter case, the user has to provide an implementation for these functions
 * in a user-supplied body file.
 *
 * This header file has been automatically generated by the FW Profile Editor.
 * The procedure created by this file is shown in the figure below.
 * @image html CrPsCmdVerSucc.png
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Aug 22 2018 19:50:4
 */

/** Make sure to include this header file only once */
#ifndef CRPSCMDVERSUCC_H_
#define CRPSCMDVERSUCC_H_

/** FW Profile function definitions */
#include "FwPrConstants.h"

/** Action node identifiers */
#define CrPsCmdVerSucc_N2 (1)		/* The identifier of action node N2 in procedure CrPsCmdVerSucc */
#define CrPsCmdVerSucc_N3 (2)		/* The identifier of action node N3 in procedure CrPsCmdVerSucc */
#define CrPsCmdVerSucc_N4 (3)		/* The identifier of action node N4 in procedure CrPsCmdVerSucc */

/**
 * Create a new procedure descriptor.
 * This interface creates the procedure descriptor dynamically.
 * @param prData the pointer to the procedure data.
 * A value of NULL is legal (note that the default value of the pointer
 * to the procedure data when the procedure is created is NULL).
 * @return the pointer to the procedure descriptor
 */
FwPrDesc_t CrPsCmdVerSuccCreate(void* prData);

/**
 * Action for node N2.
 * <pre>
 * Retrieve an OutComponent of
 * type (1,1), (1,3), or (1,7) from OutFactory
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmdVerSuccN2(FwPrDesc_t prDesc);

/**
 * Action for node N3.
 * <pre>
 * Generate error report
 * OUTFACTORY_FAIL
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmdVerSuccN3(FwPrDesc_t prDesc);

/**
 * Action for node N4.
 * <pre>
 * Configure report and
 * load it in the OutLoader
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmdVerSuccN4(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION2 to N3.
 * <pre>
 *  OutFactory fails to
 * generate OutComponent 
 * </pre>
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmdVerSuccG1(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION2 to N4.
 *  Else 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmdVerSuccG1E(FwPrDesc_t prDesc);

#endif /* CrPsCmdVerSucc_H_ */