/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(3,3) HkDelHkCmd as an incoming command.
 *
 * @note This file was generated on 2018-09-29 23:48:04
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSINCMDHKDELHKCMD_H_
#define CRPSINCMDHKDELHKCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Start action of TC(3,3) HkDelHkCmd.
 * Run the procedure of \image html CrPsCmd3s3Start.png "Start Action
 * of Command to Delete HK Packet" to identify the valid SIDs in the command
 * argument
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdHkDelHkCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(3,3) HkDelHkCmd.
 * Delete the entries in the RDL corresponding to the SIDs which have been
 * identified as valid by the Start Action and then set the action outcome to
 * ’completed’
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdHkDelHkCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSINCMDHKDELHKCMD_H */
