/**
 * @file
 *
 * Module to generate the pre-defined events of the PUS Extension of the CORDET
 * Framework.
 * For each pre-defined event, this module offers a function which takes
 * as parameters the event identifier and the event parameters
 * and which:
 * - retrieves an OutComponent to encapsulate the event report from the OutFactory,
 * - configures it with its parameters, and
 * - loads it in the OutLoader
 * .
 * If the OutComponent retrieval from the OutFactory fails, the function
 * generates an error report of type OUTFACTORY_FAIL.
 *
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 *
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */
#ifndef CRPSGENPREDEFEVT_H_
#define CRPSGENPREDEFEVT_H_

#include "CrPsTypes.h"

/**
 * Generate a parameterless event report with the given event identifier.
 * This function:
 * - retrieves an OutComponent to encapsulate the event report from the OutFactory,
 * - configures it with its parameters, and
 * - loads it in the OutLoader
 * .
 * If the OutComponent retrieval from the OutFactory fails, the function
 * generates an error report of type OUTFACTORY_FAIL.
 *
 * If no severity level can be associated to the argument event identifier,
 * the application error code is set to #CrPsEvtIdWithNoSevLevel.
 * @param evtId The event identifier
 */
void CrPsEvtGenPreDefEvtNoPar(CrPsEvtId_t evtId);

/**
 * Generate an event report with a dummy parameter.
 * This function:
 * - retrieves an OutComponent to encapsulate the event report from the OutFactory,
 * - configures it with its parameters, and
 * - loads it in the OutLoader
 * .
 * If the OutComponent retrieval from the OutFactory fails, the function
 * generates an error report of type OUTFACTORY_FAIL.
 *
 * If no severity level can be associated to the argument event identifier,
 * the application error code is set to #CrPsEvtIdWithNoSevLevel.
 * @param evtId The event identifier
 */
void CrPsEvtGenPreDefEvtDummyPar(CrPsEvtId_t evtId, CrPsEightBit_t dummyPar);


#endif /* CRPSGENPREDEFEVT_H_ */
