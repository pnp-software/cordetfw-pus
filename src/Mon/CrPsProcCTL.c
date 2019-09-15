/**
 * @file CrPsProcCTL.c
 *
 * @author FW Profile code generator version 5.23
 * @date Created on: Sep 15 2019 23:5:35
 */

#include "CrPsProcCTL.h"

/* FW Profile function definitions */
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"

/* CrPsProcCTL function definitions */
#include <stdlib.h>

/**
 * Guard on the Control Flow from DECISION1 to N2.
 * Else
 * @param prDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
static FwPrBool_t code74209(FwPrDesc_t prDesc)
{	(void)prDesc;
	return 1;
}

/**
 * Guard on the Control Flow from DECISION2 to N4.
 * Else
 * @param prDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
static FwPrBool_t code26901(FwPrDesc_t prDesc)
{	(void)prDesc;
	return 1;
}

/* ----------------------------------------------------------------------------------------------------------------- */
FwPrDesc_t CrPsProcCTLCreate(void* prData)
{
	const FwPrCounterU2_t DECISION1 = 1;		/** The identifier of decision node DECISION1 in procedure CrPsProcCTL */
	const FwPrCounterU2_t N_OUT_OF_DECISION1 = 2;	/* The number of control flows out of decision node DECISION1 in procedure CrPsProcCTL */
	const FwPrCounterU2_t DECISION2 = 2;		/** The identifier of decision node DECISION2 in procedure CrPsProcCTL */
	const FwPrCounterU2_t N_OUT_OF_DECISION2 = 2;	/* The number of control flows out of decision node DECISION2 in procedure CrPsProcCTL */

	/** Create the procedure */
	FwPrDesc_t prDesc = FwPrCreate(
		4,	/* N_ANODES - The number of action nodes */
		2,	/* N_DNODES - The number of decision nodes */
		9,	/* N_FLOWS - The number of control flows */
		4,	/* N_ACTIONS - The number of actions */
		4	/* N_GUARDS - The number of guards */
	);

	/** Configure the procedure */
	FwPrSetData(prDesc, prData);
	FwPrAddDecisionNode(prDesc, DECISION1, N_OUT_OF_DECISION1);
	FwPrAddActionNode(prDesc, CrPsProcCTL_N2, &CrPsProcCTLN2);
	FwPrAddDecisionNode(prDesc, DECISION2, N_OUT_OF_DECISION2);
	FwPrAddActionNode(prDesc, CrPsProcCTL_N3, &CrPsProcCTLN3);
	FwPrAddActionNode(prDesc, CrPsProcCTL_N4, &CrPsProcCTLN4);
	FwPrAddActionNode(prDesc, CrPsProcCTL_N5, &CrPsProcCTLN5);
	FwPrAddFlowIniToDec(prDesc, DECISION1, NULL);
	FwPrAddFlowDecToFin(prDesc, DECISION1, &CrPsProcCTLF1);
	FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsProcCTL_N2, &code74209);
	FwPrAddFlowActToDec(prDesc, CrPsProcCTL_N2, DECISION2, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsProcCTL_N3, &CrPsProcCTLF2);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsProcCTL_N4, &code26901);
	FwPrAddFlowActToFin(prDesc, CrPsProcCTL_N3, NULL);
	FwPrAddFlowActToAct(prDesc, CrPsProcCTL_N4, CrPsProcCTL_N5, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsProcCTL_N5, NULL);

	return prDesc;
}

