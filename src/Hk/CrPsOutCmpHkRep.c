/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TM(3,25) HkRep as an out-going report.
 *
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 *
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "CrPsOutCmpHkRep.h"

/**
 * Enable check of TM(3,25) HkRep.
 * The enable status is read from the isEnabled field of the Report Definition
 * corresponding to the report’s SID
 * @param smDesc The state machine descriptor.
 * @return The enable check result.
 */
CrFwBool_t CrPsOutCmpHkRepReadyCheck(FwSmDesc_t smDesc) {
}

/**
 * Repeat check of TM(3,25) HkRep.
 * Returns 'repeat' if the report's SID is defined in the RDL.
 * Otherwise it returns 'no repeat'.
 * @param smDesc The state machine descriptor.
 * @return The repeat check result.
 */
CrFwBool_t CrPsOutCmpHkRepRepeatCheck(FwSmDesc_t smDesc) {
  int rdlPos = (int)FwSmGetData(smDesc);

  if (getDpHkSidItem(rdlPos) == 0)
    return 0;
  else
    return 1;
}

/**
 * Update action of TM(3,25) HkRep.
 * Load the value of the simply-commutated data items from the data pool and
 * that of the super-commutated data items from the Sampling Buffer associated
 * to the report’s SID according to the Report Definition
 * @param smDesc The state machine descriptor.
 */
void CrPsOutCmpHkRepUpdateAction(FwSmDesc_t smDesc) {
}
