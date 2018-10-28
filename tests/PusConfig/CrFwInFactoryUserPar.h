/**
 * @file
 * @ingroup gen_cfw
 *
 * This file is part of the PUS Extension of the CORDET Framework.
 *
 * @note This file was generated on 2018-10-28 20:42:51
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRFWINFACTORYUSERPAR_H_
#define CRFWINFACTORYUSERPAR_H_

#include "Hk/CrPsInCmdHkCreHkCmd.h"
#include "Hk/CrPsInCmdHkCreDiagCmd.h"
#include "Hk/CrPsInCmdHkDelHkCmd.h"
#include "Hk/CrPsInCmdHkDelDiagCmd.h"
#include "Hk/CrPsInCmdHkEnbHkCmd.h"
#include "Hk/CrPsInCmdHkDisHkCmd.h"
#include "Hk/CrPsInCmdHkEnbDiagCmd.h"
#include "Hk/CrPsInCmdHkDisDiagCmd.h"
#include "Hk/CrPsInCmdHkRepStructHkCmd.h"
#include "Hk/CrPsInCmdHkRepStructDiagCmd.h"
#include "Hk/CrPsInCmdHkOneShotHkCmd.h"
#include "Hk/CrPsInCmdHkOneShotDiagCmd.h"
#include "Evt/CrPsInCmdEvtEnbCmd.h"
#include "Evt/CrPsInCmdEvtDisCmd.h"
#include "Evt/CrPsInCmdEvtRepDisCmd.h"
#include "Scd/CrPsInCmdScdEnbTbsCmd.h"
#include "Scd/CrPsInCmdScdDisTbsCmd.h"
#include "Scd/CrPsInCmdScdResTbsCmd.h"
#include "Scd/CrPsInCmdScdInsTbaCmd.h"
#include "Scd/CrPsInCmdScdDelTbaCmd.h"
#include "Scd/CrPsInCmdScdEnbSubSchedCmd.h"
#include "Scd/CrPsInCmdScdDisSubSchedCmd.h"
#include "Scd/CrPsInCmdScdCreGrpCmd.h"
#include "Scd/CrPsInCmdScdDelGrpCmd.h"
#include "Scd/CrPsInCmdScdEnbGrpCmd.h"
#include "Scd/CrPsInCmdScdDisGrpCmd.h"
#include "Scd/CrPsInCmdScdRepGrpCmd.h"
#include "Mon/CrPsInCmdMonEnbParMonDefCmd.h"
#include "Mon/CrPsInCmdMonDisParMonDefCmd.h"
#include "Mon/CrPsInCmdMonChgTransDelCmd.h"
#include "Mon/CrPsInCmdMonDelAllParMonCmd.h"
#include "Mon/CrPsInCmdMonAddParMonDefCmd.h"
#include "Mon/CrPsInCmdMonDelParMonDefCmd.h"
#include "Mon/CrPsInCmdMonModParMonDefCmd.h"
#include "Mon/CrPsInCmdMonRepParMonDefCmd.h"
#include "Mon/CrPsInCmdMonRepOutOfLimitsCmd.h"
#include "Mon/CrPsInCmdMonRepParMonStatCmd.h"
#include "Mon/CrPsInCmdMonEnbParMonFuncCmd.h"
#include "Mon/CrPsInCmdMonDisParMonFuncCmd.h"
#include "Mon/CrPsInCmdMonEnbFuncMonCmd.h"
#include "Mon/CrPsInCmdMonDisFuncMonCmd.h"
#include "Mon/CrPsInCmdMonEnbFuncMonDefCmd.h"
#include "Mon/CrPsInCmdMonDisFuncMonDefCmd.h"
#include "Mon/CrPsInCmdMonProtFuncMonDefCmd.h"
#include "Mon/CrPsInCmdMonUnprotFuncMonDefCmd.h"
#include "Mon/CrPsInCmdMonAddFuncMonDefCmd.h"
#include "Mon/CrPsInCmdMonDelFuncMonDefCmd.h"
#include "Mon/CrPsInCmdMonRepFuncMonDefCmd.h"
#include "Mon/CrPsInCmdMonRepFuncMonStatCmd.h"
#include "Lpt/CrPsInCmdLptUpFirstCmd.h"
#include "Lpt/CrPsInCmdLptUpInterCmd.h"
#include "Lpt/CrPsInCmdLptUpLastCmd.h"
#include "Lpt/CrPsInCmdLptStartDownCmd.h"
#include "Lpt/CrPsInCmdLptAbortDownCmd.h"
#include "Tst/CrPsInCmdTstAreYouAliveCmd.h"
#include "Tst/CrPsInCmdTstConnectCmd.h"
#include "Dum/CrPsInCmdDumSample1.h"

#include "Tst/CrPsInRepTstAreYouAliveRep.h"

/**
 * The maximum number of InCommands which may be allocated at any one time.
 */
#define CR_FW_INFACTORY_MAX_NOF_INCMD (63)

/**
 * The maximum number of InReports which may be allocated at any one time.
 */
#define CR_FW_INFACTORY_MAX_NOF_INREP (63)

/**
 * The total number of kinds of incoming commands supported by the
 * application.
 */
#define CR_FW_INCMD_NKINDS (57)

/**
 * The total number of kinds of incoming reports supported by the application.
 */
#define CR_FW_INREP_NKINDS (1)

/**
 * Definition of the incoming command kinds supported by an application.
 */
#define CR_FW_INCMD_INIT_KIND_DESC {\
   {3, 1, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdHkCreHkCmdStartAction, \
      &CrPsInCmdHkCreHkCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {3, 2, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdHkCreDiagCmdStartAction, \
      &CrPsInCmdHkCreDiagCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {3, 3, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdHkDelHkCmdStartAction, \
      &CrPsInCmdHkDelHkCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {3, 4, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdHkDelDiagCmdStartAction, \
      &CrPsInCmdHkDelDiagCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {3, 5, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdHkEnbHkCmdStartAction, \
      &CrPsInCmdHkEnbHkCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {3, 6, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdHkDisHkCmdStartAction, \
      &CrPsInCmdHkDisHkCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {3, 7, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdHkEnbDiagCmdStartAction, \
      &CrPsInCmdHkEnbDiagCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {3, 8, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdHkDisDiagCmdStartAction, \
      &CrPsInCmdHkDisDiagCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {3, 9, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdHkRepStructHkCmdStartAction, \
      &CrPsInCmdHkRepStructHkCmdProgressAction, &CrPsInCmdHkRepStructHkCmdTerminationAction, &CrFwSmEmptyAction}, \
   {3, 11, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdHkRepStructDiagCmdStartAction, \
      &CrPsInCmdHkRepStructDiagCmdProgressAction, &CrPsInCmdHkRepStructDiagCmdTerminationAction, &CrFwSmEmptyAction}, \
   {3, 27, 0, &CrFwPrCheckAlwaysTrue, &CrPsInCmdHkOneShotHkCmdReadyCheck, &CrPsInCmdHkOneShotHkCmdStartAction, \
      &CrPsInCmdHkOneShotHkCmdProgressAction, &CrPsInCmdHkOneShotHkCmdTerminationAction, &CrPsInCmdHkOneShotHkCmdAbortAction}, \
   {3, 28, 0, &CrFwPrCheckAlwaysTrue, &CrPsInCmdHkOneShotDiagCmdReadyCheck, &CrPsInCmdHkOneShotDiagCmdStartAction, \
      &CrPsInCmdHkOneShotDiagCmdProgressAction, &CrPsInCmdHkOneShotDiagCmdTerminationAction, &CrPsInCmdHkOneShotDiagCmdAbortAction}, \
   {5, 5, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdEvtEnbCmdStartAction, \
      &CrPsInCmdEvtEnbCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {5, 6, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdEvtDisCmdStartAction, \
      &CrPsInCmdEvtDisCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {5, 7, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdEvtRepDisCmdStartAction, \
      &CrPsInCmdEvtRepDisCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 1, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrFwSmEmptyAction, \
      &CrPsInCmdScdEnbTbsCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 2, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrFwSmEmptyAction, \
      &CrPsInCmdScdDisTbsCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 3, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrFwSmEmptyAction, \
      &CrPsInCmdScdResTbsCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 4, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdScdInsTbaCmdStartAction, \
      &CrPsInCmdScdInsTbaCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 5, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdScdDelTbaCmdStartAction, \
      &CrPsInCmdScdDelTbaCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 20, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdScdEnbSubSchedCmdStartAction, \
      &CrPsInCmdScdEnbSubSchedCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 21, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdScdDisSubSchedCmdStartAction, \
      &CrPsInCmdScdDisSubSchedCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 22, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdScdCreGrpCmdStartAction, \
      &CrPsInCmdScdCreGrpCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 23, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdScdDelGrpCmdStartAction, \
      &CrPsInCmdScdDelGrpCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 24, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdScdEnbGrpCmdStartAction, \
      &CrPsInCmdScdEnbGrpCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 25, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdScdDisGrpCmdStartAction, \
      &CrPsInCmdScdDisGrpCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 26, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdScdRepGrpCmdStartAction, \
      &CrPsInCmdScdRepGrpCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 1, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdMonEnbParMonDefCmdStartAction, \
      &CrPsInCmdMonEnbParMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 2, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdMonDisParMonDefCmdStartAction, \
      &CrPsInCmdMonDisParMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 3, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdMonChgTransDelCmdStartAction, \
      &CrPsInCmdMonChgTransDelCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 4, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdMonDelAllParMonCmdStartAction, \
      &CrPsInCmdMonDelAllParMonCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 5, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdMonAddParMonDefCmdStartAction, \
      &CrPsInCmdMonAddParMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 6, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdMonDelParMonDefCmdStartAction, \
      &CrPsInCmdMonDelParMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 7, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdMonModParMonDefCmdStartAction, \
      &CrPsInCmdMonModParMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 8, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdMonRepParMonDefCmdStartAction, \
      &CrPsInCmdMonRepParMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 10, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdMonRepOutOfLimitsCmdStartAction, \
      &CrPsInCmdMonRepOutOfLimitsCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 13, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdMonRepParMonStatCmdStartAction, \
      &CrPsInCmdMonRepParMonStatCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 15, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdMonEnbParMonFuncCmdStartAction, \
      &CrPsInCmdMonEnbParMonFuncCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 16, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdMonDisParMonFuncCmdStartAction, \
      &CrPsInCmdMonDisParMonFuncCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 17, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdMonEnbFuncMonCmdStartAction, \
      &CrPsInCmdMonEnbFuncMonCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 18, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrFwSmEmptyAction, \
      &CrPsInCmdMonDisFuncMonCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 19, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdMonEnbFuncMonDefCmdStartAction, \
      &CrPsInCmdMonEnbFuncMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 20, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdMonDisFuncMonDefCmdStartAction, \
      &CrPsInCmdMonDisFuncMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 21, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdMonProtFuncMonDefCmdStartAction, \
      &CrPsInCmdMonProtFuncMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 22, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdMonUnprotFuncMonDefCmdStartAction, \
      &CrPsInCmdMonUnprotFuncMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 23, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdMonAddFuncMonDefCmdStartAction, \
      &CrPsInCmdMonAddFuncMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 24, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdMonDelFuncMonDefCmdStartAction, \
      &CrPsInCmdMonDelFuncMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 25, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdMonRepFuncMonDefCmdStartAction, \
      &CrPsInCmdMonRepFuncMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 27, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdMonRepFuncMonStatCmdStartAction, \
      &CrPsInCmdMonRepFuncMonStatCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {13, 9, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdLptUpFirstCmdStartAction, \
      &CrPsInCmdLptUpFirstCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {13, 10, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdLptUpInterCmdStartAction, \
      &CrPsInCmdLptUpInterCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {13, 11, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdLptUpLastCmdStartAction, \
      &CrPsInCmdLptUpLastCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {13, 129, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdLptStartDownCmdStartAction, \
      &CrPsInCmdLptStartDownCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {13, 130, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdLptAbortDownCmdStartAction, \
      &CrPsInCmdLptAbortDownCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {17, 1, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdTstAreYouAliveCmdStartAction, \
      &CrPsInCmdTstAreYouAliveCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {17, 3, 0, &CrFwPrCheckAlwaysTrue, &CrFwSmCheckAlwaysTrue, &CrPsInCmdTstConnectCmdStartAction, \
      &CrPsInCmdTstConnectCmdProgressAction, &CrPsInCmdTstConnectCmdTerminationAction, &CrFwSmEmptyAction}, \
   {255, 1, 0, &CrPsInCmdDumSample1ValidityCheck, &CrPsInCmdDumSample1ReadyCheck, &CrPsInCmdDumSample1StartAction, \
      &CrPsInCmdDumSample1ProgressAction, &CrPsInCmdDumSample1TerminationAction, &CrPsInCmdDumSample1AbortAction} \
}

/**
 * Definition of the incoming report kinds supported by an application.
 */
#define CR_FW_INREP_INIT_KIND_DESC {\
   {17, 2, 0, &CrPsInRepTstAreYouAliveRepUpdateAction, &CrFwPrCheckAlwaysTrue} \
}

/*----------------------------------------------------------------------------*/
#endif /* CRFWINFACTORYUSERPAR_H */
