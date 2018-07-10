/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(12,2) MonDisParMonDefCmd.
 *
 * @note This file was generated on 2018-07-10 22:34:00
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSMONDISPARMONDEFCMD_H_
#define CRPSMONDISPARMONDEFCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Start action of TC(12,2) MonDisParMonDefCmd.
 * Run the procedure Start Action of Multi-Parameter Monitor Commands of
 * figure \ref{fig:Cmd12s1and2Start}
 * @param smDesc The state machine descriptor.
 */
void CrPsMonDisParMonDefCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(12,2) MonDisParMonDefCmd.
 * For every valid Parameter Monitor Identifier in the command: stop its
 * Monitor Procedure and set its checking status (attribute checkStatus) to
 * UNCHECKED. Decrement the data pool variable representing the number of
 * enabled parameter monitors by the number of disabled parameter monitors.
 * Set the action outcome to 'completed'.
 * @param smDesc The state machine descriptor.
 */
void CrPsMonDisParMonDefCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSMONDISPARMONDEFCMD_H */
