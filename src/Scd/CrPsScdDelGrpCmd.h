/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(11,23) ScdDelGrpCmd.
 *
 * @note This file was generated on 2018-07-10 22:34:00
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSSCDDELGRPCMD_H_
#define CRPSSCDDELGRPCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Start action of TC(11,23) ScdDelGrpCmd.
 * Run the procedure Start Action of (11,23) Command of figure
 * \image html CrPsCmd11s23Start.png "Start Action of Command to
 * Delete Scheduling Groups". This procedure iterates over the list of group
 * identifiers (or, if the number of groups to be deleted is equal to zero,
 * over all groups currently in use) and rejects those whose identifiers is
 * out-of-limits or which have activities associated to them.
 * @param smDesc The state machine descriptor.
 */
void CrPsScdDelGrpCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(11,23) ScdDelGrpCmd.
 * For all group identifiers accepted by the Start Action, the following is
 * done: the group is deleted by setting its InUse flag to false. After all
 * identifiers have been processed, the action outcome is set to: 'completed'.
 * @param smDesc The state machine descriptor.
 */
void CrPsScdDelGrpCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSSCDDELGRPCMD_H */
