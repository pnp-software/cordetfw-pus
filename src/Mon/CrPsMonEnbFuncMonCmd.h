/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TC(12,17) MonEnbFuncMonCmd.
 *
 * @note This file was generated on 2018-07-10 22:34:00
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSMONENBFUNCMONCMD_H_
#define CRPSMONENBFUNCMONCMD_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Start action of TC(12,17) MonEnbFuncMonCmd.
 * Set the action outcome to 'failed' if the Parameter Monitoring Function is
 * 'disabled'; otherwise set the action outcome to 'success'.
 * @param smDesc The state machine descriptor.
 */
void CrPsMonEnbFuncMonCmdStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of TC(12,17) MonEnbFuncMonCmd.
 * Set the enable status of the Functional Monitoring Function in the data
 * pool to 'enabled'. Set the action outcome to 'completed'.
 * @param smDesc The state machine descriptor.
 */
void CrPsMonEnbFuncMonCmdProgressAction(FwSmDesc_t smDesc);


/*----------------------------------------------------------------------------*/
#endif /* CRPSMONENBFUNCMONCMD_H */