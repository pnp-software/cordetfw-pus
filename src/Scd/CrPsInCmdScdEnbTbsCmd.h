/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(11,1) ScdEnbTbsCmd as an incoming command.
 *
 * @note This file was generated on 2018-10-28 17:05:47
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSINCMDSCDENBTBSCMD_H_
#define CRPSINCMDSCDENBTBSCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Progress action of TC(11,1) ScdEnbTbsCmd.
 * Set the enable status of the time-based schedule execution function to:
 * enabled and start the Time-Based Schedule Execution Procedure of figure
 * \image html CrPsTbsExec "Time-Based Schedule Execution Procedure"
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdScdEnbTbsCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSINCMDSCDENBTBSCMD_H */