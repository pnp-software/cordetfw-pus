/**
 * @file CrPsTestSuite.c
 * @ingroup PUSTestsuite
 *
 * Test Suite for the PUS extension of the CORDET Framework.
 * This file defines the <code>main</code> program for the PUS test suite.
 * The PUS test suite executes a number of test cases in sequence and reports
 * the outcome of each test case.
 *
 * @author Christian Reimers <christian.reimers@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 *
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** The number of tests in the test suite. */
#define NOF_TESTS 17

/* Include framework files */
#include "CrFwConstants.h"
#include "Aux/CrFwAux.h"

/* Include test suite files for the PUS extension */
#include "CrPsPcktGetSetTestCases.h"
#include "CrPsTstTestCases.h"
#include "CrPsVerTestCases.h"
#include "CrPsEvtTestCases.h"

/* Include files with service initialization functions */
#include "Ver/CrPsVerConfig.h"
#include "Tst/CrPsTstConfig.h"
#include "Evt/CrPsEvtConfig.h"

/**
 * Main program for the test suite.
 * The test suite executes a number of test cases in sequence and reports
 * the outcome of each test case.
 * A test case can either fail or succeed and reports its outcome as boolean.
 * @return always returns EXIT_SUCCESS
 */
int main() {
	uint32_t i;
	CrFwBool_t testOutcome;
	CrFwConfigCheckOutcome_t configCheckOutcome;
	char* testNames[NOF_TESTS];
	typedef CrFwBool_t (*testCase_t)();
	testCase_t testCases[NOF_TESTS]; /* array of pointers to SM test case functions */

	/* Check consistency of configuration parameters */
	configCheckOutcome = CrFwAuxConfigCheck();
	if (configCheckOutcome != crConsistencyCheckSuccess) {
		if (configCheckOutcome == crOutRegistryConfigParInconsistent)
			printf("Consistency check of OutRegistry parameters failed\n");
		if (configCheckOutcome == crOutFactoryConfigParInconsistent)
			printf("Consistency check of OutFactory parameters failed\n");
		if (configCheckOutcome == crInFactoryInCmdConfigParInconsistent)
			printf("Consistency check of InCommand parameters in InFactory failed\n");
		if (configCheckOutcome == crInFactoryInRepConfigParInconsistent)
			printf("Consistency check of InReport parameters in InFactory failed\n");
		return EXIT_SUCCESS;
	}
	printf("Consistency check of configuration parameters ran successfully...\n");

	/* Set the names of the SM tests and the functions executing the tests */
    i=0;

	/*Getter and Setter*/
	testNames[i] = "PusExt_PacketGetterSetter_TestCase1";
	testCases[i] = &CrPsPcktGetSetTestCase1;
	i+=1;
	testNames[i] = "PusExt_CrPsTst_TestCase1";
	testCases[i] = &CrPsTstTestCase1;
	i+=1;
	testNames[i] = "PusExt_CrPsTst_TestCase2";
	testCases[i] = &CrPsTstTestCase2;
	i+=1;
	testNames[i] = "PusExt_CrPsTst_TestCase3";
	testCases[i] = &CrPsTstTestCase3;
	i+=1;
	testNames[i] = "PusExt_CrPsTst_TestCase4";
	testCases[i] = &CrPsTstTestCase4;
	i+=1;
    testNames[i] = "PusExt_CrPsVer_TestCase1";
    testCases[i] = &CrPsVerTestCase1;
    i+=1;
    testNames[i] = "PusExt_CrPsVer_TestCase2";
    testCases[i] = &CrPsVerTestCase2;
    i+=1;
    testNames[i] = "PusExt_CrPsVer_TestCase3";
    testCases[i] = &CrPsVerTestCase3;
    i+=1;
    testNames[i] = "PusExt_CrPsVer_TestCase4";
    testCases[i] = &CrPsVerTestCase4;
    i+=1;
    testNames[i] = "PusExt_CrPsVer_TestCase5";
    testCases[i] = &CrPsVerTestCase5;
    i+=1;
    testNames[i] = "PusExt_CrPsEvt_TestCase1";
    testCases[i] = &CrPsEvtTestCase1;
    i+=1;
    testNames[i] = "PusExt_CrPsEvt_TestCase2";
    testCases[i] = &CrPsEvtTestCase2;
    i+=1;
    testNames[i] = "PusExt_CrPsEvt_TestCase3";
    testCases[i] = &CrPsEvtTestCase3;
    i+=1;
    testNames[i] = "PusExt_CrPsEvt_TestCase4";
    testCases[i] = &CrPsEvtTestCase4;
    i+=1;
    testNames[i] = "PusExt_CrPsEvt_TestCase5";
    testCases[i] = &CrPsEvtTestCase5;
    i+=1;
    testNames[i] = "PusExt_CrPsEvt_TestCase6";
    testCases[i] = &CrPsEvtTestCase6;
    i+=1;
    testNames[i] = "PusExt_CrPsEvt_TestCase7";
    testCases[i] = &CrPsEvtTestCase7;

	/* Initialize the services which are used by the test cases */
	CrPsVerConfigInit();
	CrPsTstConfigInit();

	/* Run test cases in sequence */
	for (i=0; i<NOF_TESTS; i++) {
		testOutcome = testCases[i]();
		if (testOutcome == 1)
			printf("Test case %s ran successfully ...\n", testNames[i]);
		else
			printf("Test case %s failed!\n", testNames[i]);
	}

	return EXIT_SUCCESS;
}

