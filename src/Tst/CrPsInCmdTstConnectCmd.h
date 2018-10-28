/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(17,3) TstConnectCmd as an incoming command.
 *
 * @note This file was generated on 2018-10-28 17:05:47
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSINCMDTSTCONNECTCMD_H_
#define CRPSINCMDTSTCONNECTCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Start action of TC(17,3) TstConnectCmd.
 * Run the procedure Start Action of (17,3) Command of figure
 * \image html CrPsCmd17s3Start.png "Start Action of Command (17,3")
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdTstConnectCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(17,3) TstConnectCmd.
 * Run the procedure Progress Action of (17,3) Command of figure
 * \image html CrPsCmd17s3Prgr.png "Progress Action of Command (17,3")
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdTstConnectCmdProgressAction(FwSmDesc_t smDesc);

/**
 * Termination action of TC(17,3) TstConnectCmd.
 * Set action outcome to ’success’ if the (17,4) report was issued and to
 * ’failure’ otherwise with failure code VER_TST_TO
 * @param smDesc The state machine descriptor.
 */
void CrPsInCmdTstConnectCmdTerminationAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSINCMDTSTCONNECTCMD_H */
