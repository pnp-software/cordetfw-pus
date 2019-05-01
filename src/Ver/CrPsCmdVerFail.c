/**
 * @file CrPsCmdVerFail.c
 *
 * @author FW Profile code generator version 5.23
 * @date Created on: May 1 2019 23:57:54
 */

#include "CrPsCmdVerFail.h"

/* FW Profile function definitions */
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"

/* CrPsCmdVerFail function definitions */
#include <stdlib.h>

/* Guard on the Control Flow from DECISION2 to N4. */
FwPrBool_t CrPsCmdVerFailG1E(FwPrDesc_t prDesc)
{	(void)prDesc;
	return 1;
}

/* ----------------------------------------------------------------------------------------------------------------- */
FwPrDesc_t CrPsCmdVerFailCreate(void* prData)
{
	const FwPrCounterU2_t DECISION2 = 1;		/** The identifier of decision node DECISION2 in procedure CrPsCmdVerFail */
	const FwPrCounterU2_t N_OUT_OF_DECISION2 = 2;	/* The number of control flows out of decision node DECISION2 in procedure CrPsCmdVerFail */

	/** Create the procedure */
	FwPrDesc_t prDesc = FwPrCreate(
		3,	/* N_ANODES - The number of action nodes */
		1,	/* N_DNODES - The number of decision nodes */
		6,	/* N_FLOWS - The number of control flows */
		3,	/* N_ACTIONS - The number of actions */
		2	/* N_GUARDS - The number of guards */
	);

	/** Configure the procedure */
	FwPrSetData(prDesc, prData);
	FwPrAddActionNode(prDesc, CrPsCmdVerFail_N2, &CrPsCmdVerFailN2);
	FwPrAddDecisionNode(prDesc, DECISION2, N_OUT_OF_DECISION2);
	FwPrAddActionNode(prDesc, CrPsCmdVerFail_N3, &CrPsCmdVerFailN3);
	FwPrAddActionNode(prDesc, CrPsCmdVerFail_N4, &CrPsCmdVerFailN4);
	FwPrAddFlowIniToAct(prDesc, CrPsCmdVerFail_N2, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsCmdVerFail_N2, DECISION2, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsCmdVerFail_N3, &CrPsCmdVerFailG1);
	FwPrAddFlowDecToAct(prDesc, DECISION2, CrPsCmdVerFail_N4, &CrPsCmdVerFailG1E);
	FwPrAddFlowActToFin(prDesc, CrPsCmdVerFail_N3, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsCmdVerFail_N4, NULL);

	return prDesc;
}

