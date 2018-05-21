/**
 * \file
 *
 * This file is part of CORDET Framework.
 *
 * \note This file was generated on 2018-05-19 23:24:04
 * \author Automatically Generated by CORDET Editor
 * \copyright P&P Software
 */
#ifndef CRFWINFACTORYUSERPAR_H_
#define CRFWINFACTORYUSERPAR_H_

#include "CrPsConstants.h"

/**
 * The total number of kinds of incoming commands supported by the
 * application.
 */
#define CR_FW_INCMD_NKINDS (56)

/**
 * The total number of kinds of incoming reports supported by the application.
 */
#define CR_FW_INREP_NKINDS (0)

/**
 * Definition of the incoming command kinds supported by an application.
 */
#define CR_FW_INCMD_INIT_KIND_DESC {\
   {3, 1, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsHkCreateHkCmdStartAction, \
      &CrPsHkCreateHkCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {3, 2, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsHkCreateDiagCmdStartAction, \
      &CrPsHkCreateDiagCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {3, 3, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsHkDelHkCmdStartAction, \
      &CrPsHkDelHkCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {3, 4, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsHkDelDiagCmdStartAction, \
      &CrPsHkDelDiagCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {3, 5, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsHkEnableHkCmdStartAction, \
      &CrPsHkEnableHkCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {3, 6, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsHkDisableHkCmdStartAction, \
      &CrPsHkDisableHkCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {3, 7, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsHkEnableDiagCmdStartAction, \
      &CrPsHkEnableDiagCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {3, 8, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsHkDisableDiagCmdStartAction, \
      &CrPsHkDisableDiagCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {3, 9, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsHkRepStructHkCmdStartAction, \
      &CrPsHkRepStructHkCmdProgressAction, &CrPsHkRepStructHkCmdTerminationAction, &CrFwSmEmptyAction}, \
   {3, 11, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsHkRepStructDiagCmdStartAction, \
      &CrPsHkRepStructDiagCmdProgressAction, &CrPsHkRepStructDiagCmdTerminationAction, &CrFwSmEmptyAction}, \
   {3, 27, 0, &CrPsHkOneShotHkCmdAcceptanceCheck, &CrPsHkOneShotHkCmdReadyCheck, &CrPsHkOneShotHkCmdStartAction, \
      &CrPsHkOneShotHkCmdProgressAction, &CrPsHkOneShotHkCmdTerminationAction, &CrPsHkOneShotHkCmdAbortAction}, \
   {3, 28, 0, &CrPsHkOneShotDiagCmdAcceptanceCheck, &CrPsHkOneShotDiagCmdReadyCheck, &CrPsHkOneShotDiagCmdStartAction, \
      &CrPsHkOneShotDiagCmdProgressAction, &CrPsHkOneShotDiagCmdTerminationAction, &CrPsHkOneShotDiagCmdAbortAction}, \
   {5, 5, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsEvtEnbIdStartAction, \
      &CrPsEvtEnbIdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {5, 6, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsEvtDisIdCmdStartAction, \
      &CrPsEvtDisIdCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {5, 7, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsEvtRepDisIdCmdStartAction, \
      &CrPsEvtRepDisIdCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 1, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrFwSmEmptyAction, \
      &CrPsScdEnbTbsCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 2, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrFwSmEmptyAction, \
      &CrPsScdDisTbsCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 3, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrFwSmEmptyAction, \
      &CrPsScdResTbsCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 4, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsScdInsTbaCmdStartAction, \
      &CrPsScdInsTbaCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 5, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsScdDelTbaCmdStartAction, \
      &CrPsScdDelTbaCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 20, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsScdEnbSubSchedCmdStartAction, \
      &CrPsScdEnbSubSchedCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 21, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsScdDisSubSchedCmdStartAction, \
      &CrPsScdDisSubSchedCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 22, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsScdCreGrpCmdStartAction, \
      &CrPsScdCreGrpCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 23, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsScdDelGrpCmdStartAction, \
      &CrPsScdDelGrpCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 24, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsScdEnbGrpCmdStartAction, \
      &CrPsScdEnbGrpCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 25, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsScdDisGrpCmdStartAction, \
      &CrPsScdDisGrpCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {11, 26, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsScdRepGrpCmdStartAction, \
      &CrPsScdRepGrpCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 1, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsMonEnbParMonDefCmdStartAction, \
      &CrPsMonEnbParMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 2, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsMonDisParMonDefCmdStartAction, \
      &CrPsMonDisParMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 3, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsMonChgTransDelCmdStartAction, \
      &CrPsMonChgTransDelCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 4, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsMonDelAllParMonCmdStartAction, \
      &CrPsMonDelAllParMonCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 5, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsMonAddParMonDefCmdStartAction, \
      &CrPsMonAddParMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 6, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsMonDelParMonDefCmdStartAction, \
      &CrPsMonDelParMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 7, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsMonModParMonDefCmdStartAction, \
      &CrPsMonModParMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 8, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsMonRepParMonDefCmdStartAction, \
      &CrPsMonRepParMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 10, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsMonRepOutOfLimitsCmdStartAction, \
      &CrPsMonRepOutOfLimitsCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 13, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsMonRepParMonStatCmdStartAction, \
      &CrPsMonRepParMonStatCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 15, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsMonEnbParMonFuncCmdStartAction, \
      &CrPsMonEnbParMonFuncCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 16, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsMonDisParMonFuncCmdStartAction, \
      &CrPsMonDisParMonFuncCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 17, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsMonEnbFuncMonCmdStartAction, \
      &CrPsMonEnbFuncMonCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 18, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrFwSmEmptyAction, \
      &CrPsMonDisFuncMonCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 19, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsMonEnbFuncMonDefCmdStartAction, \
      &CrPsMonEnbFuncMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 20, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsMonDisFuncMonDefCmdStartAction, \
      &CrPsMonDisFuncMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 21, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsMonProtFuncMonDefCmdStartAction, \
      &CrPsMonProtFuncMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 22, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsMonUnprotFuncMonDefCmdStartAction, \
      &CrPsMonUnprotFuncMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 23, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsMonAddFuncMonDefCmdStartAction, \
      &CrPsMonAddFuncMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 24, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsMonDelFuncMonDefCmdStartAction, \
      &CrPsMonDelFuncMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 25, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsMonRepFuncMonDefCmdStartAction, \
      &CrPsMonRepFuncMonDefCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {12, 27, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsMonRepFuncMonStatCmdStartAction, \
      &CrPsMonRepFuncMonStatCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {13, 9, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsLptUpFirstCmdStartAction, \
      &CrPsLptUpFirstCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {13, 10, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsLptUpInterCmdStartAction, \
      &CrPsLptUpInterCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {13, 11, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsLptUpLastCmdStartAction, \
      &CrPsLptUpLastCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {13, 129, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsLptStartDownCmdStartAction, \
      &CrPsLptStartDownCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {13, 130, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsLptAbortDownCmdStartAction, \
      &CrPsLptAbortDownCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {17, 1, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsTstAreYouAliveCmdStartAction, \
      &CrPsTstAreYouAliveCmdProgressAction, &CrFwSmEmptyAction, &CrFwSmEmptyAction}, \
   {17, 3, 0, &CrFwPrCheckAlwaysTrue, &CrFwPrCheckAlwaysTrue, &CrPsTstConnectCmdStartAction, \
      &CrPsTstConnectCmdProgressAction, &CrPsTstConnectCmdTerminationAction, &CrFwSmEmptyAction} \
}

/**
 * Definition of the incoming report kinds supported by an application.
 */
#define CR_FW_INREP_INIT_KIND_DESC {\
}

/*----------------------------------------------------------------------------*/
#endif /* CRFWINFACTORYUSERPAR_H */