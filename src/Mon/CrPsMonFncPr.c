/**
 * @file CrPsMonFncPr.c
 *
 * @author FW Profile code generator version 5.23
 * @date Created on: Aug 31 2019 23:36:9
 */

#include "CrPsMonFncPr.h"

/* FW Profile function definitions */
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"

/* CrPsMonFncPr function definitions */
#include <stdlib.h>

/**
 * Guard on the Control Flow from N1 to N2.
 * Wait 1 cycle 
 * @param prDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
static FwPrBool_t code64227(FwPrDesc_t prDesc)
{	(void)prDesc;
	return (FwPrGetNodeExecCnt(prDesc) == 1);
}

/**
 * Guard on the Control Flow from DECISION2 to N4.
 * Else 
 * @param prDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
static FwPrBool_t code92152(FwPrDesc_t prDesc)
{	(void)prDesc;
	return 1;
}

/**
 * Guard on the Control Flow from DECISION4 to N10.
 * Else 
 * @param prDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
static FwPrBool_t code87098(FwPrDesc_t prDesc)
{	(void)prDesc;
	return 1;
}

/**
 * Guard on the Control Flow from DECISION6 to N2.
 * Else 
 * @param prDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
static FwPrBool_t code54789(FwPrDesc_t prDesc)
{	(void)prDesc;
	return 1;
}

/**
 * Guard on the Control Flow from DECISION7 to N2.
 * Else 
 * @param prDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
static FwPrBool_t code83698(FwPrDesc_t prDesc)
{	(void)prDesc;
	return 1;
}

/**
 * Guard on the Control Flow from DECISION8 to N3.
 * Else 
 * @param prDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
static FwPrBool_t code29960(FwPrDesc_t prDesc)
{	(void)prDesc;
	return 1;
}

/**
 * Guard on the Control Flow from DECISION9 to N13.
 * Else 
 * @param prDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
static FwPrBool_t code50767(FwPrDesc_t prDesc)
{	(void)prDesc;
	return 1;
}

/**
 * Guard on the Control Flow from DECISION10 to N9.
 * Else 
 * @param prDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
static FwPrBool_t code88301(FwPrDesc_t prDesc)
{	(void)prDesc;
	return 1;
}

/**
 * Guard on the Control Flow from DECISION11 to N9.
 * Else 
 * @param prDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
static FwPrBool_t code94350(FwPrDesc_t prDesc)
{	(void)prDesc;
	return 1;
}

/* ----------------------------------------------------------------------------------------------------------------- */
FwPrDesc_t CrPsMonFncPrCreate(void* prData)
{
	const FwPrCounterU2_t DECISION2 = 1;		/** The identifier of decision node DECISION2 in procedure CrPsMonFncPr */
	const FwPrCounterU2_t N_OUT_OF_DECISION2 = 2;	/* The number of control flows out of decision node DECISION2 in procedure CrPsMonFncPr */
	const FwPrCounterU2_t DECISION4 = 2;		/** The identifier of decision node DECISION4 in procedure CrPsMonFncPr */
	const FwPrCounterU2_t N_OUT_OF_DECISION4 = 2;	/* The number of control flows out of decision node DECISION4 in procedure CrPsMonFncPr */
	const FwPrCounterU2_t DECISION6 = 3;		/** The identifier of decision node DECISION6 in procedure CrPsMonFncPr */
	const FwPrCounterU2_t N_OUT_OF_DECISION6 = 2;	/* The number of control flows out of decision node DECISION6 in procedure CrPsMonFncPr */
	const FwPrCounterU2_t DECISION7 = 4;		/** The identifier of decision node DECISION7 in procedure CrPsMonFncPr */
	const FwPrCounterU2_t N_OUT_OF_DECISION7 = 2;	/* The number of control flows out of decision node DECISION7 in procedure CrPsMonFncPr */
	const FwPrCounterU2_t DECISION8 = 5;		/** The identifier of decision node DECISION8 in procedure CrPsMonFncPr */
	const FwPrCounterU2_t N_OUT_OF_DECISION8 = 2;	/* The number of control flows out of decision node DECISION8 in procedure CrPsMonFncPr */
	const FwPrCounterU2_t DECISION9 = 6;		/** The identifier of decision node DECISION9 in procedure CrPsMonFncPr */
	const FwPrCounterU2_t N_OUT_OF_DECISION9 = 2;	/* The number of control flows out of decision node DECISION9 in procedure CrPsMonFncPr */
	const FwPrCounterU2_t DECISION10 = 7;		/** The identifier of decision node DECISION10 in procedure CrPsMonFncPr */
	const FwPrCounterU2_t N_OUT_OF_DECISION10 = 2;	/* The number of control flows out of decision node DECISION10 in procedure CrPsMonFncPr */
	const FwPrCounterU2_t DECISION11 = 8;		/** The identifier of decision node DECISION11 in procedure CrPsMonFncPr */
	const FwPrCounterU2_t N_OUT_OF_DECISION11 = 2;	/* The number of control flows out of decision node DECISION11 in procedure CrPsMonFncPr */

	/** Create the procedure */
	FwPrDesc_t prDesc = FwPrCreate(
		12,	/* N_ANODES - The number of action nodes */
		8,	/* N_DNODES - The number of decision nodes */
		29,	/* N_FLOWS - The number of control flows */
		12,	/* N_ACTIONS - The number of actions */
		16	/* N_GUARDS - The number of guards */
	);

	/** Configure the procedure */
	FwPrSetData(prDesc, prData);
	FwPrAddActionNode(prDesc, CrPsMonFncPr_N1, &CrPsMonFncPrN1);
	FwPrAddActionNode(prDesc, CrPsMonFncPr_N2, &CrPsMonFncPrN2);
	FwPrAddDecisionNode(prDesc, DECISION2, N_OUT_OF_DECISION2);
	FwPrAddActionNode(prDesc, CrPsMonFncPr_N3, &CrPsMonFncPrN3);
	FwPrAddActionNode(prDesc, CrPsMonFncPr_N4, &CrPsMonFncPrN4);
	FwPrAddDecisionNode(prDesc, DECISION4, N_OUT_OF_DECISION4);
	FwPrAddActionNode(prDesc, CrPsMonFncPr_N9, &CrPsMonFncPrN9);
	FwPrAddDecisionNode(prDesc, DECISION6, N_OUT_OF_DECISION6);
	FwPrAddDecisionNode(prDesc, DECISION7, N_OUT_OF_DECISION7);
	FwPrAddDecisionNode(prDesc, DECISION8, N_OUT_OF_DECISION8);
	FwPrAddActionNode(prDesc, CrPsMonFncPr_N10, &CrPsMonFncPrN10);
	FwPrAddActionNode(prDesc, CrPsMonFncPr_N11, &CrPsMonFncPrN11);
	FwPrAddDecisionNode(prDesc, DECISION9, N_OUT_OF_DECISION9);
	FwPrAddActionNode(prDesc, CrPsMonFncPr_N12, &CrPsMonFncPrN12);
	FwPrAddDecisionNode(prDesc, DECISION10, N_OUT_OF_DECISION10);
	FwPrAddActionNode(prDesc, CrPsMonFncPr_N13, &CrPsMonFncPrN13);
	FwPrAddActionNode(prDesc, CrPsMonFncPr_N14, &CrPsMonFncPrN14);
	FwPrAddDecisionNode(prDesc, DECISION11, N_OUT_OF_DECISION11);
	FwPrAddActionNode(prDesc, CrPsMonFncPr_N15, &CrPsMonFncPrN15);
	FwPrAddActionNode(prDesc, CrPsMonFncPr_N5, &CrPsMonFncPrN5);
	FwPrAddFlowIniToAct(prDesc, CrPsMonFncPr_N5, NULL);
	FwPrAddFlowActToAct(prDesc, CrPsMonFncPr_N1, CrPsMonFncPr_N2, &code64227);
	FwPrAddFlowActToDec(prDesc, CrPsMonFncPr_N2, DECISION2, NULL);
	FwPrAddFlowDecToDec(prDesc, DECISION2, DECISION6, &CrPsMonFncPrIsParDis);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsMonFncPr_N4, &code92152);
	FwPrAddFlowActToDec(prDesc, CrPsMonFncPr_N3, DECISION9, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsMonFncPr_N4, DECISION4, NULL);
	FwPrAddFlowDecToDec(prDesc, DECISION4, DECISION7, &CrPsMonFncPrIsPerSmaller);
	FwPrAddFlowDecToAct(prDesc, DECISION4, CrPsMonFncPr_N10, &code87098);
	FwPrAddFlowActToDec(prDesc, CrPsMonFncPr_N9, DECISION6, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION6, CrPsMonFncPr_N1, &CrPsMonFncPrGN1);
	FwPrAddFlowDecToAct(prDesc, DECISION6, CrPsMonFncPr_N2, &code54789);
	FwPrAddFlowDecToAct(prDesc, DECISION7, CrPsMonFncPr_N1, &CrPsMonFncPrGN1);
	FwPrAddFlowDecToAct(prDesc, DECISION7, CrPsMonFncPr_N2, &code83698);
	FwPrAddFlowDecToAct(prDesc, DECISION8, CrPsMonFncPr_N11, &CrPsMonFncPrIsParInv);
	FwPrAddFlowDecToAct(prDesc, DECISION8, CrPsMonFncPr_N3, &code29960);
	FwPrAddFlowActToDec(prDesc, CrPsMonFncPr_N10, DECISION8, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsMonFncPr_N11, DECISION7, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION9, CrPsMonFncPr_N12, &CrPsMonFncPrIsFlag1);
	FwPrAddFlowDecToAct(prDesc, DECISION9, CrPsMonFncPr_N13, &code50767);
	FwPrAddFlowActToAct(prDesc, CrPsMonFncPr_N12, CrPsMonFncPr_N13, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION10, CrPsMonFncPr_N14, &CrPsMonFncPrIsFlag2);
	FwPrAddFlowDecToAct(prDesc, DECISION10, CrPsMonFncPr_N9, &code88301);
	FwPrAddFlowActToDec(prDesc, CrPsMonFncPr_N13, DECISION10, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsMonFncPr_N14, DECISION11, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION11, CrPsMonFncPr_N15, &CrPsMonFncPrIsFlag3);
	FwPrAddFlowDecToAct(prDesc, DECISION11, CrPsMonFncPr_N9, &code94350);
	FwPrAddFlowActToAct(prDesc, CrPsMonFncPr_N15, CrPsMonFncPr_N9, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsMonFncPr_N5, DECISION6, NULL);

	return prDesc;
}

