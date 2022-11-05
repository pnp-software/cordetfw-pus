/**
 * @file
 *
 * Implementation of TM(17,2) TstAreYouAliveRep as an incoming report.
 *
 */
#ifndef CRPSINREPTSTAREYOUALIVEREP_H_
#define CRPSINREPTSTAREYOUALIVEREP_H_

#include "CrPsConstants.h"
#include "CrPsTypes.h"

#include "FwSmCore.h"
#include "CrFwConstants.h"

/**
 * Update action of TM(17,2) TstAreYouAliveRep.
 * Set AreYouAliveSrc to the source of the report
 * @param prDesc The descriptor of the Execution Procedure of the InReport.
 */
void CrPsInRepTstAreYouAliveRepUpdateAction(FwPrDesc_t prDesc);

/*----------------------------------------------------------------------------*/
#endif /* CRPSINREPTSTAREYOUALIVEREP_H */
