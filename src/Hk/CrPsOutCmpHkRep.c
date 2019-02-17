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
#include "DataPool/CrPsDpHk.h"
#include "CrPsHkConfig.h"

/* --------------------------------------------------------------------------- */
/**
 * The Ready Check performs the following actions:
 *
 * (a) If the report's cycle counter in the RDL is equal to the report's
 * period in the RDL, then the report's cycle counter in the RDL is reset to
 * zero
 * (b) If the report's cycle counter in the RDL is equal to zero and the
 * report is enabled in the RDL, then the outcome of the Ready Check is set
 * to: 'ready'; otherwise it is set to 'not ready'
 * (c) The report's cycle counter in the RDL is incremented by 1
 *
 * NB: This logic ensures that the report's cycle counter increments from zero
 * to the report's period and then is reset. The report is 'ready' when its
 * cycle counter is equal to zero. The report's cycle counter is initialized
 * to zero at application's initialization (for pre-defined reports) or when
 * the report is created (for dynamically defined commands)
 * @param smDesc The state machine descriptor.
 * @return The ready check result.
 */
CrFwBool_t CrPsOutCmpHkRepReadyCheck(FwSmDesc_t smDesc) {
  CrFwBool_t temp;
  int rdlPos = CrPsHkConfigGetRdlIndex(smDesc);
  CrPsCycleCnt_t cycleCnt;

  if (getDpHkCycleCntItem(rdlPos) == getDpHkPeriodItem(rdlPos))
      setDpHkCycleCntItem(rdlPos, 0);

  temp = 0;
  if (getDpHkCycleCntItem(rdlPos) == 0)
     if (getDpHkIsEnabledItem(rdlPos) == 1)
        temp = 1;

  cycleCnt = getDpHkCycleCntItem(rdlPos);
  setDpHkCycleCntItem(rdlPos, cycleCnt+1);

  return temp;
}

/* --------------------------------------------------------------------------- */
/**
 * Repeat check of TM(3,25) HkRep.
 * Returns 'repeat' if the report's SID is defined in the RDL.
 * Otherwise it returns 'no repeat'.
 * @param smDesc The state machine descriptor.
 * @return The repeat check result.
 */
CrFwBool_t CrPsOutCmpHkRepRepeatCheck(FwSmDesc_t smDesc) {
  int rdlPos = CrPsHkConfigGetRdlIndex(smDesc);

  if (getDpHkSidItem(rdlPos) == 0)
    return 0;
  else
    return 1;
}

/* --------------------------------------------------------------------------- */
/**
 * Update action of TM(3,25) HkRep.
 * Load the value of the simply-commutated data items from the data pool and
 * that of the super-commutated data items from the Sampling Buffer associated
 * to the report’s SID according to the Report Definition
 * @param smDesc The state machine descriptor.
 */
void CrPsOutCmpHkRepUpdateAction(FwSmDesc_t smDesc) {
  int rdlPos = CrPsHkConfigGetRdlIndex(smDesc);
  CrPsHkConfigUpdateRep(rdlPos, smDesc);
}
