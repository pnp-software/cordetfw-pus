/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TM(3,26) HkDiagRep as an out-going report.
 *
 * @note This file was generated on 2018-10-28 17:05:47
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSOUTCMPHKDIAGREP_H_
#define CRPSOUTCMPHKDIAGREP_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Enable check of TM(3,26) HkDiagRep.
 * The enable status is read from the isEnabled field of the Report Definition
 * corresponding to the report’s SID
 * @param smDesc The state machine descriptor.
 * @return The enable check result.
 */
CrFwBool_t CrPsOutCmpHkDiagRepEnableCheck(FwSmDesc_t smDesc);

/**
 * Ready check of TM(3,26) HkDiagRep.
 * Run the procedure of figure \image html CrPsRep3s25Ready.png "Ready
 * Check of Service 3 HK or Diagnostic Report"
 * @param smDesc The state machine descriptor.
 * @return The ready check result.
 */
CrFwBool_t CrPsOutCmpHkDiagRepReadyCheck(FwSmDesc_t smDesc);

/**
 * Update action of TM(3,26) HkDiagRep.
 * Load the value of the simply-commutated data items from the data pool and
 * that of the super-commutated data items from the Sampling Buffer associated
 * to the report’s SID according to the Report Definition
 * @param smDesc The state machine descriptor.
 */
void CrPsOutCmpHkDiagRepUpdateAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSOUTCMPHKDIAGREP_H */