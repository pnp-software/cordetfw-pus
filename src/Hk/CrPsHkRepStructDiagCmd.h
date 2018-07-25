/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(3,11) HkRepStructDiagCmd.
 *
 * @note This file was generated on 2018-07-25 18:43:06
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSHKREPSTRUCTDIAGCMD_H_
#define CRPSHKREPSTRUCTDIAGCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Start action of TC(3,11) HkRepStructDiagCmd.
 * Run the procedure Start Action of Multi-SID Command of figure
 * \image html CrPsCmd3SidStart.png "Start Action of Multi-SID
 * Command"
 * @param smDesc The state machine descriptor.
 */
void CrPsHkRepStructDiagCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(3,11) HkRepStructDiagCmd.
 * Run the procedure Progress Action of Report Service 3 Structure of figure
 * \image html CrPsCmd3s9Prgr.png "Progress Action of Report Service 3
 * Structure Command"
 * @param smDesc The state machine descriptor.
 */
void CrPsHkRepStructDiagCmdProgressAction(FwSmDesc_t smDesc);

/**
 * Termination action of TC(3,11) HkRepStructDiagCmd.
 * Set action outcome to ’success’ if all valid SIDs in the command were
 * successfully processed by the progress action; set it to ’failure’
 * otherwise
 * @param smDesc The state machine descriptor.
 */
void CrPsHkRepStructDiagCmdTerminationAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSHKREPSTRUCTDIAGCMD_H */
