/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(11,2) ScdDisTbsCmd.
 *
 * @note This file was generated on 2018-07-10 22:34:00
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSSCDDISTBSCMD_H_
#define CRPSSCDDISTBSCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Progress action of TC(11,2) ScdDisTbsCmd.
 * Set the enable status of the time-based schedule execution function to:
 * disabled and stop the Time-Based Schedule Execution Procedure of figure
 * \image html CrPsTbsExec "Time-Based Schedule Execution Procedure"
 * @param smDesc The state machine descriptor.
 */
void CrPsScdDisTbsCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSSCDDISTBSCMD_H */