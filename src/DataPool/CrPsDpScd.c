/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2018-06-22 17:45:58
 * \author Automatically Generated by CORDET Editor
 * \copyright P&P Software GmbH
 */

#include "CrPsDpScd.h"

DpScdParams_t dpScdParams ;
DpScdVars_t dpScdVars ;

/**
 * Initialises Scd
 */
void initDpScd(void)
{
   static const CrFwBool_t initisSubSchedEnabled[SCD_N_SUB_TBS] = 0;
   static const CrPsNTba_t initnOfTbaInGroup[SCD_N_GROUP] = 0;
   static const CrPsNTba_t initnOfTbaInSubSched[SCD_N_SUB_TBS] = 0;
   static const CrFwBool_t initisGroupEnabled[SCD_N_GROUP] = 1;
   static const CrFwBool_t initisGroupInUse[SCD_N_GROUP] = 0;

   memcpy(dpScdParams.isSubSchedEnabled, initisSubSchedEnabled, sizeof(dpScdParams.isSubSchedEnabled));
   dpScdParams.isTbsEnabled = 0;
   memcpy(dpScdParams.nOfTbaInGroup, initnOfTbaInGroup, sizeof(dpScdParams.nOfTbaInGroup));
   memcpy(dpScdParams.nOfTbaInSubSched, initnOfTbaInSubSched, sizeof(dpScdParams.nOfTbaInSubSched));
   dpScdParams.timeMargin = 0;
   dpScdVars.firstTba = 0;
   memcpy(dpScdVars.isGroupEnabled, initisGroupEnabled, sizeof(dpScdVars.isGroupEnabled));
   memcpy(dpScdVars.isGroupInUse, initisGroupInUse, sizeof(dpScdVars.isGroupInUse));
   dpScdVars.nOfGroup = ;
   dpScdVars.nOfSubSched = 0;
   dpScdVars.nOfTba = 0;
}
