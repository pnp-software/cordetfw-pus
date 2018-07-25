/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(3,5) HkEnbHkCmd.
 *
 * @note This file was generated on 2018-07-25 18:43:06
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSHKENBHKCMD_H_
#define CRPSHKENBHKCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Start action of TC(3,5) HkEnbHkCmd.
 * Run the procedure Start Action of Multi-SID Command of figure
 * \image html CrPsCmd3SidStart.png "Start Action of Multi-SID
 * Command"
 * @param smDesc The state machine descriptor.
 */
void CrPsHkEnbHkCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(3,5) HkEnbHkCmd.
 * For the entries in the RDL corresponding to the SIDs which have been
 * identified as valid by the Start Action: set enabled flag to true and set
 * the cycle counter to 0. Set the action outcome to ’completed’
 * @param smDesc The state machine descriptor.
 */
void CrPsHkEnbHkCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSHKENBHKCMD_H */
