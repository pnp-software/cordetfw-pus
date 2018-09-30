/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TM(13,2) LptDownInterRep as an out-going report.
 *
 * @note This file was generated on 2018-09-30 23:01:15
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSOUTCMPLPTDOWNINTERREP_H_
#define CRPSOUTCMPLPTDOWNINTERREP_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Enable check of TM(13,2) LptDownInterRep.
 * Report is enabled if the LPT State Machine is in state DOWN_TRANSFER
 * @param smDesc The state machine descriptor.
 * @return The enable check result.
 */
CrFwBool_t CrPsOutCmpLptDownInterRepEnableCheck(FwSmDesc_t smDesc);

/**
 * Repeat check of TM(13,2) LptDownInterRep.
 * Report is repeated as long as lptRemSize is greater than partSize
 * @param smDesc The state machine descriptor.
 * @return The repeat check result.
 */
CrFwBool_t CrPsOutCmpLptDownInterRepRepeatCheck(FwSmDesc_t smDesc);

/**
 * Update action of TM(13,2) LptDownInterRep.
 * The following actions are performed:
 *
 * (a) Load the next part of the large packet from the LPT Buffer
 * (b) Set the transaction identifier equal to largeMsgTransId
 * (c) Set the part number equal to partSeqNmb
 * (d) Increase partSeqNmb
 * (e) Decrement lptRemSize by partSize
 * (f) Set the action outcome to: 'completed'
 * @param smDesc The state machine descriptor.
 */
void CrPsOutCmpLptDownInterRepUpdateAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSOUTCMPLPTDOWNINTERREP_H */
