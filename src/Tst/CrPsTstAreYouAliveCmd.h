/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(17,1) TstAreYouAliveCmd.
 *
 * @note This file was generated on 2018-07-14 19:50:20
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSTSTAREYOUALIVECMD_H_
#define CRPSTSTAREYOUALIVECMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Start action of TC(17,1) TstAreYouAliveCmd.
 * Retrieve (17,2) report from OutFactory and set action outcome to 'success'
 * if the retrieval succeeds. If the retrieval fails, generate error report
 * OUTFACTORY FAILED and set outcome of Start Action to ’failed’
 * @param smDesc The state machine descriptor.
 */
void CrPsTstAreYouAliveCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(17,1) TstAreYouAliveCmd.
 * Configure the (17,2) report with a destination equal to the source of the
 * (17,1), load it in the OutLoader, and then set the action outcome to
 * ’completed’
 * @param smDesc The state machine descriptor.
 */
void CrPsTstAreYouAliveCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSTSTAREYOUALIVECMD_H */
