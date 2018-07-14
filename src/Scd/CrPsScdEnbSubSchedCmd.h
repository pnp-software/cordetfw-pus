/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(11,20) ScdEnbSubSchedCmd.
 *
 * @note This file was generated on 2018-07-14 19:50:20
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSSCDENBSUBSCHEDCMD_H_
#define CRPSSCDENBSUBSCHEDCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Start action of TC(11,20) ScdEnbSubSchedCmd.
 * Run the procedure of figure
 * \image html CrPsCmd11s20And21Start.jpg "Start Action of
 * Commands to Enable and Disable Sub-Schedules". This procedure checks all
 * the sub-schedule identifiers in the command and rejects those which are
 * invalid (i.e. either outside the range: 1..SCD_N_SUB_TBS or pointing at an
 * empty sub-schuedule).
 * @param smDesc The state machine descriptor.
 */
void CrPsScdEnbSubSchedCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(11,20) ScdEnbSubSchedCmd.
 * For all the sub-schedule identifiers which have passed the Start Check,set
 * their isSubSchedEnabled attribute to false.
 * @param smDesc The state machine descriptor.
 */
void CrPsScdEnbSubSchedCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSSCDENBSUBSCHEDCMD_H */
