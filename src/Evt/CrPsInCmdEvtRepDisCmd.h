/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(5,7) EvtRepDisCmd as an incoming command.
 *
 * @note This file was generated on 2018-10-28 20:42:51
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSINCMDEVTREPDISCMD_H_
#define CRPSINCMDEVTREPDISCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Start action of TC(5,7) EvtRepDisCmd.
 * Retrieve (5,8) report from OutFactory and set action outcome to 'success’
 * if retrieval succeeds. If the retrieval fails, generate error report
 * OUTFACTORY FAILED and set outcome of Start Action to ’failed’
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdEvtRepDisCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(5,7) EvtRepDisCmd.
 * Configure the (5,8) report with a destination equal to the source of the
 * (5,7) command, load it in the OutLoader, and set the action outcome to
 * ’completed’
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdEvtRepDisCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSINCMDEVTREPDISCMD_H */
