/**
 * @file
 * This header file declares the function to create one instance of the CrPsMonFncPr procedure.
 * The procedure is configured with a set of function pointers representing the non-default
 * actions and guards of the procedure. Some of these functions may also be declared in
 * this header file in accordance with the configuration of the procedure in the FW Profile
 * Editor. In the latter case, the user has to provide an implementation for these functions
 * in a user-supplied body file.
 *
 * This header file has been automatically generated by the FW Profile Editor.
 * The procedure created by this file is shown in the figure below.
 * @image html CrPsMonFncPr.png
 *
 * @author FW Profile code generator version 5.23
 * @date Created on: Jun 1 2019 17:15:41
 */

/* Make sure to include this header file only once */
#ifndef CRPSMONFNCPR_H_
#define CRPSMONFNCPR_H_

/* FW Profile constant definitions */
#include "FwPrConstants.h"

/* Action node identifiers */
#define CrPsMonFncPr_N1 (1)		/**< The identifier of action node N1 in procedure CrPsMonFncPr */
#define CrPsMonFncPr_N2 (2)		/**< The identifier of action node N2 in procedure CrPsMonFncPr */
#define CrPsMonFncPr_N3 (3)		/**< The identifier of action node N3 in procedure CrPsMonFncPr */
#define CrPsMonFncPr_N4 (4)		/**< The identifier of action node N4 in procedure CrPsMonFncPr */
#define CrPsMonFncPr_N5 (5)		/**< The identifier of action node N5 in procedure CrPsMonFncPr */
#define CrPsMonFncPr_N9 (6)		/**< The identifier of action node N9 in procedure CrPsMonFncPr */
#define CrPsMonFncPr_N10 (7)		/**< The identifier of action node N10 in procedure CrPsMonFncPr */
#define CrPsMonFncPr_N11 (8)		/**< The identifier of action node N11 in procedure CrPsMonFncPr */
#define CrPsMonFncPr_N12 (9)		/**< The identifier of action node N12 in procedure CrPsMonFncPr */
#define CrPsMonFncPr_N13 (10)		/**< The identifier of action node N13 in procedure CrPsMonFncPr */
#define CrPsMonFncPr_N14 (11)		/**< The identifier of action node N14 in procedure CrPsMonFncPr */
#define CrPsMonFncPr_N15 (12)		/**< The identifier of action node N15 in procedure CrPsMonFncPr */

/**
 * Create a new procedure descriptor.
 * This interface creates the procedure descriptor dynamically.
 * @param prData the pointer to the procedure data.
 * A value of NULL is legal (note that the default value of the pointer
 * to the procedure data when the procedure is created is NULL).
 * @return the pointer to the procedure descriptor
 */
FwPrDesc_t CrPsMonFncPrCreate(void* prData);

/**
 * Action for node N1.
 * i = -1 
 * @param prDesc the procedure descriptor
 */
void CrPsMonFncPrN1(FwPrDesc_t prDesc);

/**
 * Action for node N2.
 * Increment i
 * @param prDesc the procedure descriptor
 */
void CrPsMonFncPrN2(FwPrDesc_t prDesc);

/**
 * Action for node N3.
 * <pre>
 * Execute Monitor Procedure and 
 * store its return value in monPrRetVal
 * </pre>
 * @param prDesc the procedure descriptor
 */
void CrPsMonFncPrN3(FwPrDesc_t prDesc);

/**
 * Action for node N4.
 * <pre>
 * Increment period counter
 * of i-th Parameter Monitor
 * </pre>
 * @param prDesc the procedure descriptor
 */
void CrPsMonFncPrN4(FwPrDesc_t prDesc);

/**
 * Action for node N5.
 * <pre>
 * TBD
 * </pre>
 * @param prDesc the procedure descriptor
 */
void CrPsMonFncPrN5(FwPrDesc_t prDesc);

/**
 * Action for node N9.
 * monPrPrevRetVal = monPrRetVal
 * @param prDesc the procedure descriptor
 */
void CrPsMonFncPrN9(FwPrDesc_t prDesc);

/**
 * Action for node N10.
 * <pre>
 * Set period
 * counter to zero
 * </pre>
 * @param prDesc the procedure descriptor
 */
void CrPsMonFncPrN10(FwPrDesc_t prDesc);

/**
 * Action for node N11.
 * <pre>
 * Set repetition counter to zero
 * and checking status to INVALID  
 * </pre>
 * @param prDesc the procedure descriptor
 */
void CrPsMonFncPrN11(FwPrDesc_t prDesc);

/**
 * Action for node N12.
 * <pre>
 * Set repetition
 * counter to zero
 * </pre>
 * @param prDesc the procedure descriptor
 */
void CrPsMonFncPrN12(FwPrDesc_t prDesc);

/**
 * Action for node N13.
 * <pre>
 * Increment repetiion counter
 * with saturation at the repetiion number
 * </pre>
 * @param prDesc the procedure descriptor
 */
void CrPsMonFncPrN13(FwPrDesc_t prDesc);

/**
 * Action for node N14.
 * <pre>
 * Set checking status equal to
 * return value of monitor procedure,
 * add an entry in Check Transition List,
 * notify functional monitors to whcih the
 * parameter monitor belongs and run
 * the CTL Processing Procedure
 * </pre>
 * @param prDesc the procedure descriptor
 */
void CrPsMonFncPrN14(FwPrDesc_t prDesc);

/**
 * Action for node N15.
 * <pre>
 * Generate Pre-Defined
 * Event associated to par. monitor
 * </pre>
 * @param prDesc the procedure descriptor
 */
void CrPsMonFncPrN15(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION2 to DECISION6.
 * <pre>
 * The i-th Parameter
 * Monitor is disabled 
 * </pre>
 * @param prDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsMonFncPrIsParDis(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION4 to DECISION7.
 * <pre>
 * Period counter of i-th Parameter
 * Monitor is smaller than its Period 
 * </pre>
 * @param prDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsMonFncPrIsPerSmaller(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION6 to N1.
 * <pre>
 * All parameter monitors in PMDL
 * have been processed 
 * </pre>
 * @param prDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsMonFncPrGN1(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION8 to N11.
 * <pre>
 * Parameter
 * is invalid 
 * </pre>
 * @param prDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsMonFncPrIsParInv(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION9 to N12.
 * Flag_1 
 * @param prDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsMonFncPrIsFlag1(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION10 to N14.
 * Flag_2 
 * @param prDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsMonFncPrIsFlag2(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION11 to N15.
 * Flag_3
 * @param prDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsMonFncPrIsFlag3(FwPrDesc_t prDesc);

#endif /* CrPsMonFncPr_H_ */

