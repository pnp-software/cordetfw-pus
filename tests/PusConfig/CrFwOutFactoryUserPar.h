/**
 * \file
 *
 * This file is part of CORDET Framework.
 *
 * \note This file was generated on 2018-06-15 19:20:43
 * \author Automatically Generated by CORDET Editor
 * \copyright P&P Software
 */
#ifndef CRFWOUTFACTORYUSERPAR_H_
#define CRFWOUTFACTORYUSERPAR_H_

#include "CrPsConstants.h"

/**
 * The total number of kinds of OutComponents supported by the application.
 */
#define CR_FW_OUTCMP_NKINDS (31)

/**
 * Definition of the OutComponent kinds supported by an application.
 */
#define CR_FW_OUTCMP_INIT_KIND_DESC {\
   {1, 1, 0, 2, 20, &CrPsVerSuccAccRepEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrFwSmEmptyAction, &CrFwOutCmpDefSerialize}, \
   {1, 2, 0, 2, 30, &CrPsVerFailedAccRepEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrFwSmEmptyAction, &CrFwOutCmpDefSerialize}, \
   {1, 3, 0, 2, 20, &CrPsVerSuccStartRepEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrFwSmEmptyAction, &CrFwOutCmpDefSerialize}, \
   {1, 4, 0, 2, 30, &CrPsVerFailedStartRepEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrFwSmEmptyAction, &CrFwOutCmpDefSerialize}, \
   {1, 5, 0, 2, 19, &CrPsVerSuccPrgrRepEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrFwSmEmptyAction, &CrFwOutCmpDefSerialize}, \
   {1, 6, 0, 2, 31, &CrPsVerFailedPrgrRepEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrFwSmEmptyAction, &CrFwOutCmpDefSerialize}, \
   {1, 7, 0, 2, 19, &CrPsVerSuccTermRepEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrFwSmEmptyAction, &CrFwOutCmpDefSerialize}, \
   {1, 8, 0, 2, 30, &CrPsVerFailedTermRepEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrFwSmEmptyAction, &CrFwOutCmpDefSerialize}, \
   {1, 10, 0, 2, 27, &CrPsVerFailedRoutingRepEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrFwSmEmptyAction, &CrFwOutCmpDefSerialize}, \
   {3, 10, 0, 2, 16, &CrPsHkRepStructHkRepEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrPsHkRepStructHkRepUpdateAction, &CrFwOutCmpDefSerialize}, \
   {3, 12, 0, 2, 16, &CrPsHkRepStructDiagRepEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrPsHkRepStructDiagRepUpdateAction, &CrFwOutCmpDefSerialize}, \
   {3, 25, 0, 2, 18, &CrPsHkRepEnableCheck, &CrPsHkRepReadyCheck, \
      &CrPsHkRepRepeatCheck, &CrPsHkRepUpdateAction, &CrFwOutCmpDefSerialize}, \
   {3, 26, 0, 2, 18, &CrPsHkDiagRepEnableCheck, &CrPsHkDiagRepReadyCheck, \
      &CrPsHkDiagRepRepeatCheck, &CrPsHkDiagRepUpdateAction, &CrFwOutCmpDefSerialize}, \
   {5, 1, 0, 2, 18, &CrPsEvtRep1EnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrPsEvtRep1UpdateAction, &CrFwOutCmpDefSerialize}, \
   {5, 2, 0, 2, 18, &CrPsEvtRep2EnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrPsEvtRep2UpdateAction, &CrFwOutCmpDefSerialize}, \
   {5, 3, 0, 2, 18, &CrPsEvtRep3EnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrPsEvtRep3UpdateAction, &CrFwOutCmpDefSerialize}, \
   {5, 4, 0, 2, 18, &CrPsEvtRep4EnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrPsEvtRep4UpdateAction, &CrFwOutCmpDefSerialize}, \
   {5, 8, 0, 2, 16, &CrFwOutCmpDefEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrPsEvtDisIdRepUpdateAction, &CrFwOutCmpDefSerialize}, \
   {11, 27, 0, 2, 16, &CrFwOutCmpDefEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrPsScdGrpRepUpdateAction, &CrFwOutCmpDefSerialize}, \
   {12, 9, 0, 2, 16, &CrFwOutCmpDefEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrFwSmEmptyAction, &CrFwOutCmpDefSerialize}, \
   {12, 11, 0, 2, 16, &CrFwOutCmpDefEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrFwSmEmptyAction, &CrFwOutCmpDefSerialize}, \
   {12, 12, 0, 2, 16, &CrFwOutCmpDefEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrFwSmEmptyAction, &CrFwOutCmpDefSerialize}, \
   {12, 14, 0, 2, 16, &CrFwOutCmpDefEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrFwSmEmptyAction, &CrFwOutCmpDefSerialize}, \
   {12, 26, 0, 2, 16, &CrFwOutCmpDefEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrFwSmEmptyAction, &CrFwOutCmpDefSerialize}, \
   {12, 28, 0, 2, 16, &CrFwOutCmpDefEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrFwSmEmptyAction, &CrFwOutCmpDefSerialize}, \
   {13, 1, 0, 2, 22, &CrPsLptDownFirstRepEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrPsLptDownFirstRepUpdateAction, &CrFwOutCmpDefSerialize}, \
   {13, 2, 0, 2, 22, &CrPsLptDownInterRepEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrPsLptDownInterRepUpdateAction, &CrFwOutCmpDefSerialize}, \
   {13, 3, 0, 2, 22, &CrPsLptDownLastRepEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrPsLptDownLastRepUpdateAction, &CrFwOutCmpDefSerialize}, \
   {13, 16, 0, 2, 20, &CrFwOutCmpDefEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrPsLptUpAbortRepUpdateAction, &CrFwOutCmpDefSerialize}, \
   {17, 2, 0, 2, 16, &CrFwOutCmpDefEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrFwSmEmptyAction, &CrFwOutCmpDefSerialize}, \
   {17, 4, 0, 2, 17, &CrFwOutCmpDefEnableCheck, &CrFwSmCheckAlwaysTrue, \
      &CrFwSmCheckAlwaysFalse, &CrFwSmEmptyAction, &CrFwOutCmpDefSerialize} \
}

/*----------------------------------------------------------------------------*/
#endif /* CRFWOUTFACTORYUSERPAR_H */
