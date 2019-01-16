/**
 * @file
 *
 * Implementation of the configuration interface for the Event Reporting Service.
 * This implementation is provided to support the testing of the PUS Extension of the
 * CORDET Framework.
 * In this implementation:
 * - The service initialization (function #CrPsEvtConfigInit) returns without doing
 *   anything
 * - The severity query function (function #CrPsEvtConfigGetSeverity) returns a
 *   severity level of 1 for all event identifiers defined at framework level with the exception
 *   of the event identifiers EVT_DUMMY_x which are allocated to severity level 'x'.
 * .
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

#include "CrPsEvtConfig.h"
#include "CrPsTypes.h"

unsigned int CrPsEvtConfigGetSeverity(CrPsEvtId_t evtId) {
   if (evtId == EVT_DUMMY_1)
       return 1;
   if (evtId == EVT_DUMMY_2)
       return 2;
   if (evtId == EVT_DUMMY_3)
       return 3;
   if (evtId == EVT_DUMMY_4)
       return 4;
   return 1;
}

/* ------------------------------------------------------------------------------------------------ */
void CrPsEvtConfigInit() {
   return;
}

