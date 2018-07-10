/**
 * @file
 * @ingroup gen_cfw
 *
 * Implementation of TM(13,16) LptUpAbortRep.
 *
 * @note This file was generated on 2018-07-10 22:34:00
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSLPTUPABORTREP_H_
#define CRPSLPTUPABORTREP_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Update action of TM(13,16) LptUpAbortRep.
 * The large message transaction identifier is taken from parameter
 * largeMsgTransId and the failure reason is read from variable lptFailCode.
 * @param smDesc The state machine descriptor.
 */
void CrPsLptUpAbortRepUpdateAction(FwSmDesc_t smDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSLPTUPABORTREP_H */