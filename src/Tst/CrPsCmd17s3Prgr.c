/**
 * @file CrPsCmd17s3Prgr.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jun 7 2018 18:44:45
 */

#include "CrPsCmd17s3Prgr.h"

/** FW Profile function definitions */
#include "FwPrDCreate.h"
#include "FwPrConfig.h"

/** CrPsCmd17s3Prgr function definitions */
#include <stdlib.h>

/** Guard on the Control Flow from DECISION1 to N3. */
FwPrBool_t CrPsTestOnBoardConnectionPrgrG13(FwPrDesc_t prDesc)
{
	return 1;
}

/* ----------------------------------------------------------------------------------------------------------------- */
FwPrDesc_t CrPsCmd17s3PrgrCreate(void* prData)
{
	const FwPrCounterU2_t DECISION1 = 1;		/* The identifier of decision node DECISION1 in procedure CrPsCmd17s3Prgr */
	const FwPrCounterU2_t N_OUT_OF_DECISION1 = 3;	/* The number of control flows out of decision node DECISION1 in procedure CrPsCmd17s3Prgr */

	/** Create the procedure */
	FwPrDesc_t prDesc = FwPrCreate(
		3,	/* N_ANODES - The number of action nodes */
		1,	/* N_DNODES - The number of decision nodes */
		7,	/* N_FLOWS - The number of control flows */
		3,	/* N_ACTIONS - The number of actions */
		3	/* N_GUARDS - The number of guards */
	);

	/** Configure the procedure */
	FwPrSetData(prDesc, prData);
	FwPrAddDecisionNode(prDesc, DECISION1, N_OUT_OF_DECISION1);
	FwPrAddActionNode(prDesc, CrPsCmd17s3Prgr_N1, &CrPsTestOnBoardConnectionPrgrN1);
	FwPrAddActionNode(prDesc, CrPsCmd17s3Prgr_N2, &CrPsTestOnBoardConnectionPrgrN2);
	FwPrAddActionNode(prDesc, CrPsCmd17s3Prgr_N3, &CrPsTestOnBoardConnectionPrgrN3);
	FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsCmd17s3Prgr_N1, &CrPsTestOnBoardConnectionPrgrG11);
	FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsCmd17s3Prgr_N2, &CrPsTestOnBoardConnectionPrgrG12);
	FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsCmd17s3Prgr_N3, &CrPsTestOnBoardConnectionPrgrG13);
	FwPrAddFlowActToFin(prDesc, CrPsCmd17s3Prgr_N1, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsCmd17s3Prgr_N2, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsCmd17s3Prgr_N3, NULL);
	FwPrAddFlowIniToDec(prDesc, DECISION1, NULL);

	return prDesc;
}