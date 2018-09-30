/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(3,6) HkDisHkCmd as an incoming command.
 *
 * @note This file was generated on 2018-09-30 23:01:15
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSINCMDHKDISHKCMD_H_
#define CRPSINCMDHKDISHKCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Start action of TC(3,6) HkDisHkCmd.
 * Run the procedure Start Action of Multi-SID Command of figure
 * \image html CrPsCmd3SidStart.png "Start Action of Multi-SID
 * Command"
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdHkDisHkCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(3,6) HkDisHkCmd.
 * Set to false the enable flag of the entries in the RDL corresponding to the
 * SIDs which have been identified as valid by the Start Action and then set
 * the action outcome to ’completed’
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdHkDisHkCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSINCMDHKDISHKCMD_H */
