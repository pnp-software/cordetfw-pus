/**
 * @file CrPsProcCTLMain.c
 *
 * @author FW Profile code generator version 5.23
 * @date Created on: Sep 15 2019 23:5:35
 */

/** CrPsProcCTL function definitions */
#include "CrPsProcCTL.h"

/** FW Profile function definitions */
#include "FwPrConstants.h"
#include "FwPrDCreate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ----------------------------------------------------------------------------------------------------------------- */

/* Action for node N2. */
void CrPsProcCTLN2(FwPrDesc_t prDesc)
{	(void)prDesc;
	printf("  Action for node N2.\n");
}

/* Action for node N3. */
void CrPsProcCTLN3(FwPrDesc_t prDesc)
{	(void)prDesc;
	printf("  Action for node N3.\n");
}

/* Action for node N4. */
void CrPsProcCTLN4(FwPrDesc_t prDesc)
{	(void)prDesc;
	printf("  Action for node N4.\n");
}

/* Action for node N5. */
void CrPsProcCTLN5(FwPrDesc_t prDesc)
{	(void)prDesc;
	printf("  Action for node N5.\n");
}

/* Guard on the Control Flow from DECISION1 to Final Node. */
FwPrBool_t CrPsProcCTLF1(FwPrDesc_t prDesc)
{	(void)prDesc;
	printf("  Guard on the Control Flow from DECISION1 to Final Node.\n");
	return rand()>RAND_MAX/2 ? 1 : 0;
}

/* Guard on the Control Flow from DECISION2 to N3. */
FwPrBool_t CrPsProcCTLF2(FwPrDesc_t prDesc)
{	(void)prDesc;
	printf("  Guard on the Control Flow from DECISION2 to N3.\n");
	return rand()>RAND_MAX/2 ? 1 : 0;
}

/* ----------------------------------------------------------------------------------------------------------------- */

int main(void)
{
	/** Define the procedure descriptor (PRD) */
	FwPrDesc_t prDesc = CrPsProcCTLCreate(NULL);

	srand(time(NULL));

	/** Check that the procedure is properly configured */
	if (FwPrCheck(prDesc) != prSuccess) {
		printf("The procedure CrPsProcCTL is NOT properly configured ... FAILURE\n");
		return EXIT_FAILURE;
	}

	printf("The procedure CrPsProcCTL is properly configured ... SUCCESS\n");

	/** Start the procedure, and execute it a few times */
	FwPrStart(prDesc);
	FwPrExecute(prDesc);
	FwPrExecute(prDesc);
	FwPrExecute(prDesc);
	FwPrExecute(prDesc);

	return EXIT_SUCCESS;
}