/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(11,21) ScdDisSubSchedCmd.
 *
 * @note This file was generated on 2018-07-14 19:50:20
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsScdDisSubSchedCmd.h"

/**
 * Start action of TC(11,21) ScdDisSubSchedCmd.
 * Run the procedure of figure
 * \image html CrPsCmd11s20And21Start.jpg "Start Action of
 * Commands to Enable and Disable Sub-Schedules". This procedure checks all
 * the sub-schedule identifiers in the command and rejects those which are
 * invalid (i.e. either outside the range: 1..SCD_N_SUB_TBS or pointing at an
 * empty sub-schuedule).
 * @param smDesc The state machine descriptor.
 */
void CrPsScdDisSubSchedCmdStartAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsScdDisSubSchedCmdStartAction");
   return ;
}

/**
 * Progress action of TC(11,21) ScdDisSubSchedCmd.
 * For all the sub-schedule identifiers which have passed the Start Check,set
 * their isSubSchedEnabled attribute to false.
 * @param smDesc The state machine descriptor.
 */
void CrPsScdDisSubSchedCmdProgressAction(FwSmDesc_t smDesc)
{
   CRFW_UNUSED(smDesc);
   DBG("CrPsScdDisSubSchedCmdProgressAction");
   return ;
}

