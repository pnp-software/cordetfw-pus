/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(12,4) MonDelAllParMonCmd as an incoming command.
 *
 * @note This file was generated on 2018-09-30 23:01:15
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSINCMDMONDELALLPARMONCMD_H_
#define CRPSINCMDMONDELALLPARMONCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Start action of TC(12,4) MonDelAllParMonCmd.
 * Set action outcome to 'success' if the parameter monitoring function is
 * disabled and if none of the currently defined parameter monitors is
 * attached to a functional monitor which is protected; otherwise set the
 * action outcome to 'failed
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdMonDelAllParMonCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(12,4) MonDelAllParMonCmd.
 * Delete all entries from the Parameter Monitoring Definition List (PMDL) and
 * delete all entries from the Check Transition List (CTL). Set the data pool
 * variable representing the number of remaining available PMDL entries equal
 * to the size of the PMDL. Set the action outcome to 'completed'.
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdMonDelAllParMonCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSINCMDMONDELALLPARMONCMD_H */
