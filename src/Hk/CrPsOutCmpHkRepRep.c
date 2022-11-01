/**
 * @file
 * @ingroup man_hk
 *
 * Implementation of TM(3,25) HkRep as an out-going report.
 * This module also implements the (3,26) diagnostic report.
 * The header file CrPsOutCmpHkRep.h for this body file was
 * generated automatically by the CORDET Editor.
 *
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 *
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "CrPsOutCmpHkRepRep.h"
#include "DataPool/CrPsDpHk.h"
#include "Pckt/CrPsPcktHk.h"
#include "CrPsHkConfig.h"
#include "OutCmp/CrFwOutCmp.h"

/** The index of the RDL slot (starting from zero) */
static short int rdlPos;

/* --------------------------------------------------------------------------- */
CrFwBool_t CrPsOutCmpHkRepRepReadyCheck(FwSmDesc_t smDesc) {
  CrFwBool_t temp;
  CrPsSID_t sid;
  CrFwPckt_t pckt = CrFwOutCmpGetPckt(smDesc);
  CrPsCycleCnt_t cycleCnt;

  sid = getHkRepSID(pckt);
  rdlPos = CrPsHkConfigGetRdlSlot(sid);
  if (rdlPos == -1)
      return 0;

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
CrFwBool_t CrPsOutCmpHkRepRepRepeatCheck(FwSmDesc_t smDesc) {
  (void)smDesc;
  if (getDpHkSidItem(rdlPos) == 0)
    return 0;
  else
    return 1;
}

/* --------------------------------------------------------------------------- */
void CrPsOutCmpHkRepRepUpdateAction(FwSmDesc_t smDesc) {
  CrPsHkConfigUpdateRep(rdlPos, smDesc);
}
