/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(11,3) ScdResTbsCmd.
 *
 * @note This file was generated on 2018-07-10 22:34:00
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSSCDRESTBSCMD_H_
#define CRPSSCDRESTBSCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Progress action of TC(11,3) ScdResTbsCmd.
 * (a) Set the enabled status of the time-based schedule execution function
 * to: disabled.
 * (b) Clear all entries in the time-based schedule (TBS). An entry in the TBS
 * is cleared by setting its release time attribute to zero.
 * (c) Delete all sub-schedules and set the number of in use sub-schedules
 * (nOfInUseSubSched) to zero. A sub-schedule is deleted by setting its inUse
 * flag to false.
 * (d) Delete all schedule groups and set the number of in use groups
 * (nOfInUseGroup) to zero. A group is deleted by setting its inUse flag to
 * false.
 * @param smDesc The state machine descriptor.
 */
void CrPsScdResTbsCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSSCDRESTBSCMD_H */