/**
 * @file
 * @ingroup gen_dp
 *
 * Interface for accessing data pool items.
 *
 * @note This file was generated on 2018-07-10 22:24:45
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */

#include "CrPsDp.h"

#include "CrPsDpFct.h"
#include "CrPsDpScd.h"
#include "CrPsDpLpt.h"
#include "CrPsDpHk.h"
#include "CrPsDpMon.h"
#include "CrPsDpVer.h"
#include "CrPsDpTst.h"
#include "CrPsDpEvt.h"

/**
 * Structure to hold the location and size information of a datapool entry.
 */
typedef struct _DpMetaInfoEntry_t {
   /**
    * The address of the datapool entry.
    */
   void* addr;
   /**
    * The length in bytes of the datapool entry.
    */
   size_t length;
   /**
    * The number of array elements.
    */
   unsigned int nElements;
   /**
    * The length of a single array element.
    */
   size_t elementLength;
} DpMetaInfoEntry_t;

/**
 *
 * Array of @ref _DpMetaInfoEntry_t to hold the meta information of all
 * datapool entries.
 */
static DpMetaInfoEntry_t dpMetaInfoParams[] = {
   {(void*)&dpHkParams.debugVarAddr, sizeof(dpHkParams.debugVarAddr), HK_N_DEBUG_VAR, sizeof(dpHkParams.debugVarAddr[0])},
   {(void*)&dpHkParams.dest, sizeof(dpHkParams.dest), HK_N_REP_DEF, sizeof(dpHkParams.dest[0])},
   {(void*)&dpHkParams.isEnabled, sizeof(dpHkParams.isEnabled), HK_N_REP_DEF, sizeof(dpHkParams.isEnabled[0])},
   {(void*)&dpHkParams.period, sizeof(dpHkParams.period), HK_N_REP_DEF, sizeof(dpHkParams.period[0])},
   {(void*)&dpHkParams.sid, sizeof(dpHkParams.sid), HK_N_REP_DEF, sizeof(dpHkParams.sid[0])},
   {(void*)&dpLptParams.lptDest, sizeof(dpLptParams.lptDest), LPT_N_BUF, sizeof(dpLptParams.lptDest[0])},
   {(void*)&dpLptParams.lptTimeOut, sizeof(dpLptParams.lptTimeOut), LPT_N_BUF, sizeof(dpLptParams.lptTimeOut[0])},
   {(void*)&dpLptParams.partSize, sizeof(dpLptParams.partSize), LPT_N_BUF, sizeof(dpLptParams.partSize[0])},
   {(void*)&dpMonParams.maxRepDelay, sizeof(dpMonParams.maxRepDelay), 1, sizeof(dpMonParams.maxRepDelay)},
   {(void*)&dpMonParams.servUser, sizeof(dpMonParams.servUser), 1, sizeof(dpMonParams.servUser)},
   {(void*)&dpScdParams.isSubSchedEnabled, sizeof(dpScdParams.isSubSchedEnabled), SCD_N_SUB_TBS, sizeof(dpScdParams.isSubSchedEnabled[0])},
   {(void*)&dpScdParams.isTbsEnabled, sizeof(dpScdParams.isTbsEnabled), 1, sizeof(dpScdParams.isTbsEnabled)},
   {(void*)&dpScdParams.nOfTbaInGroup, sizeof(dpScdParams.nOfTbaInGroup), SCD_N_GROUP, sizeof(dpScdParams.nOfTbaInGroup[0])},
   {(void*)&dpScdParams.nOfTbaInSubSched, sizeof(dpScdParams.nOfTbaInSubSched), SCD_N_SUB_TBS, sizeof(dpScdParams.nOfTbaInSubSched[0])},
   {(void*)&dpScdParams.timeMargin, sizeof(dpScdParams.timeMargin), 1, sizeof(dpScdParams.timeMargin)},
   {(void*)&dpTstParams.AreYouAliveTimeOut, sizeof(dpTstParams.AreYouAliveTimeOut), 1, sizeof(dpTstParams.AreYouAliveTimeOut)},
   {(void*)&dpTstParams.OnBoardConnectDestLst, sizeof(dpTstParams.OnBoardConnectDestLst), TST_N_DEST, sizeof(dpTstParams.OnBoardConnectDestLst[0])}
};

static DpMetaInfoEntry_t dpMetaInfoVars[] = {
   {(void*)&dpEvtVars.isEidEnabled, sizeof(dpEvtVars.isEidEnabled), EVT_N_ID, sizeof(dpEvtVars.isEidEnabled[0])},
   {(void*)&dpEvtVars.lastEvtEid_1, sizeof(dpEvtVars.lastEvtEid_1), 1, sizeof(dpEvtVars.lastEvtEid_1)},
   {(void*)&dpEvtVars.lastEvtEid_2, sizeof(dpEvtVars.lastEvtEid_2), 1, sizeof(dpEvtVars.lastEvtEid_2)},
   {(void*)&dpEvtVars.lastEvtEid_3, sizeof(dpEvtVars.lastEvtEid_3), 1, sizeof(dpEvtVars.lastEvtEid_3)},
   {(void*)&dpEvtVars.lastEvtEid_4, sizeof(dpEvtVars.lastEvtEid_4), 1, sizeof(dpEvtVars.lastEvtEid_4)},
   {(void*)&dpEvtVars.lastEvtTime_1, sizeof(dpEvtVars.lastEvtTime_1), 1, sizeof(dpEvtVars.lastEvtTime_1)},
   {(void*)&dpEvtVars.lastEvtTime_2, sizeof(dpEvtVars.lastEvtTime_2), 1, sizeof(dpEvtVars.lastEvtTime_2)},
   {(void*)&dpEvtVars.lastEvtTime_3, sizeof(dpEvtVars.lastEvtTime_3), 1, sizeof(dpEvtVars.lastEvtTime_3)},
   {(void*)&dpEvtVars.lastEvtTime_4, sizeof(dpEvtVars.lastEvtTime_4), 1, sizeof(dpEvtVars.lastEvtTime_4)},
   {(void*)&dpEvtVars.nOfDetectedEvts_1, sizeof(dpEvtVars.nOfDetectedEvts_1), 1, sizeof(dpEvtVars.nOfDetectedEvts_1)},
   {(void*)&dpEvtVars.nOfDetectedEvts_2, sizeof(dpEvtVars.nOfDetectedEvts_2), 1, sizeof(dpEvtVars.nOfDetectedEvts_2)},
   {(void*)&dpEvtVars.nOfDetectedEvts_3, sizeof(dpEvtVars.nOfDetectedEvts_3), 1, sizeof(dpEvtVars.nOfDetectedEvts_3)},
   {(void*)&dpEvtVars.nOfDetectedEvts_4, sizeof(dpEvtVars.nOfDetectedEvts_4), 1, sizeof(dpEvtVars.nOfDetectedEvts_4)},
   {(void*)&dpEvtVars.nOfDisabledEid_1, sizeof(dpEvtVars.nOfDisabledEid_1), 1, sizeof(dpEvtVars.nOfDisabledEid_1)},
   {(void*)&dpEvtVars.nOfDisabledEid_2, sizeof(dpEvtVars.nOfDisabledEid_2), 1, sizeof(dpEvtVars.nOfDisabledEid_2)},
   {(void*)&dpEvtVars.nOfDisabledEid_3, sizeof(dpEvtVars.nOfDisabledEid_3), 1, sizeof(dpEvtVars.nOfDisabledEid_3)},
   {(void*)&dpEvtVars.nOfDisabledEid_4, sizeof(dpEvtVars.nOfDisabledEid_4), 1, sizeof(dpEvtVars.nOfDisabledEid_4)},
   {(void*)&dpEvtVars.nOfGenEvtRep_1, sizeof(dpEvtVars.nOfGenEvtRep_1), 1, sizeof(dpEvtVars.nOfGenEvtRep_1)},
   {(void*)&dpEvtVars.nOfGenEvtRep_2, sizeof(dpEvtVars.nOfGenEvtRep_2), 1, sizeof(dpEvtVars.nOfGenEvtRep_2)},
   {(void*)&dpEvtVars.nOfGenEvtRep_3, sizeof(dpEvtVars.nOfGenEvtRep_3), 1, sizeof(dpEvtVars.nOfGenEvtRep_3)},
   {(void*)&dpEvtVars.nOfGenEvtRep_4, sizeof(dpEvtVars.nOfGenEvtRep_4), 1, sizeof(dpEvtVars.nOfGenEvtRep_4)},
   {(void*)&dpFctVars.nOfAllocatedInCmd, sizeof(dpFctVars.nOfAllocatedInCmd), 1, sizeof(dpFctVars.nOfAllocatedInCmd)},
   {(void*)&dpFctVars.nOfAllocatedInRep, sizeof(dpFctVars.nOfAllocatedInRep), 1, sizeof(dpFctVars.nOfAllocatedInRep)},
   {(void*)&dpFctVars.nOfAllocatedOutCmp, sizeof(dpFctVars.nOfAllocatedOutCmp), 1, sizeof(dpFctVars.nOfAllocatedOutCmp)},
   {(void*)&dpFctVars.nOfFailedInCmd, sizeof(dpFctVars.nOfFailedInCmd), 1, sizeof(dpFctVars.nOfFailedInCmd)},
   {(void*)&dpFctVars.nOfFailedInRep, sizeof(dpFctVars.nOfFailedInRep), 1, sizeof(dpFctVars.nOfFailedInRep)},
   {(void*)&dpFctVars.nOfFailedOutCmp, sizeof(dpFctVars.nOfFailedOutCmp), 1, sizeof(dpFctVars.nOfFailedOutCmp)},
   {(void*)&dpFctVars.nOfTotAllocatedInCmd, sizeof(dpFctVars.nOfTotAllocatedInCmd), 1, sizeof(dpFctVars.nOfTotAllocatedInCmd)},
   {(void*)&dpFctVars.nOfTotAllocatedInRep, sizeof(dpFctVars.nOfTotAllocatedInRep), 1, sizeof(dpFctVars.nOfTotAllocatedInRep)},
   {(void*)&dpFctVars.nOfTotAllocatedOutCmp, sizeof(dpFctVars.nOfTotAllocatedOutCmp), 1, sizeof(dpFctVars.nOfTotAllocatedOutCmp)},
   {(void*)&dpHkVars.cycleCnt, sizeof(dpHkVars.cycleCnt), HK_N_REP_DEF, sizeof(dpHkVars.cycleCnt[0])},
   {(void*)&dpHkVars.debugVar, sizeof(dpHkVars.debugVar), HK_N_DEBUG_VAR, sizeof(dpHkVars.debugVar[0])},
   {(void*)&dpHkVars.sampleBufId, sizeof(dpHkVars.sampleBufId), HK_N_REP_DEF, sizeof(dpHkVars.sampleBufId[0])},
   {(void*)&dpLptVars.lptRemSize, sizeof(dpLptVars.lptRemSize), LPT_N_BUF, sizeof(dpLptVars.lptRemSize[0])},
   {(void*)&dpLptVars.lptSize, sizeof(dpLptVars.lptSize), LPT_N_BUF, sizeof(dpLptVars.lptSize[0])},
   {(void*)&dpLptVars.lptSrc, sizeof(dpLptVars.lptSrc), LPT_N_BUF, sizeof(dpLptVars.lptSrc[0])},
   {(void*)&dpLptVars.lptTime, sizeof(dpLptVars.lptTime), LPT_N_BUF, sizeof(dpLptVars.lptTime[0])},
   {(void*)&dpLptVars.nOfDownlinks, sizeof(dpLptVars.nOfDownlinks), 1, sizeof(dpLptVars.nOfDownlinks)},
   {(void*)&dpLptVars.nOfUplinks, sizeof(dpLptVars.nOfUplinks), 1, sizeof(dpLptVars.nOfUplinks)},
   {(void*)&dpLptVars.partSeqNmb, sizeof(dpLptVars.partSeqNmb), LPT_N_BUF, sizeof(dpLptVars.partSeqNmb[0])},
   {(void*)&dpMonVars.ctlRepDelay, sizeof(dpMonVars.ctlRepDelay), 1, sizeof(dpMonVars.ctlRepDelay)},
   {(void*)&dpMonVars.ctlTimeFirstEntry, sizeof(dpMonVars.ctlTimeFirstEntry), 1, sizeof(dpMonVars.ctlTimeFirstEntry)},
   {(void*)&dpMonVars.funcMonEnbStatus, sizeof(dpMonVars.funcMonEnbStatus), 1, sizeof(dpMonVars.funcMonEnbStatus)},
   {(void*)&dpMonVars.nmbAvailFuncMon, sizeof(dpMonVars.nmbAvailFuncMon), 1, sizeof(dpMonVars.nmbAvailFuncMon)},
   {(void*)&dpMonVars.nmbAvailParMon, sizeof(dpMonVars.nmbAvailParMon), 1, sizeof(dpMonVars.nmbAvailParMon)},
   {(void*)&dpMonVars.nmbEnbFuncMon, sizeof(dpMonVars.nmbEnbFuncMon), 1, sizeof(dpMonVars.nmbEnbFuncMon)},
   {(void*)&dpMonVars.nmbEnbParMon, sizeof(dpMonVars.nmbEnbParMon), 1, sizeof(dpMonVars.nmbEnbParMon)},
   {(void*)&dpMonVars.parMonEnbStatus, sizeof(dpMonVars.parMonEnbStatus), 1, sizeof(dpMonVars.parMonEnbStatus)},
   {(void*)&dpScdVars.firstTba, sizeof(dpScdVars.firstTba), 1, sizeof(dpScdVars.firstTba)},
   {(void*)&dpScdVars.isGroupEnabled, sizeof(dpScdVars.isGroupEnabled), SCD_N_GROUP, sizeof(dpScdVars.isGroupEnabled[0])},
   {(void*)&dpScdVars.isGroupInUse, sizeof(dpScdVars.isGroupInUse), SCD_N_GROUP, sizeof(dpScdVars.isGroupInUse[0])},
   {(void*)&dpScdVars.nOfGroup, sizeof(dpScdVars.nOfGroup), 1, sizeof(dpScdVars.nOfGroup)},
   {(void*)&dpScdVars.nOfSubSched, sizeof(dpScdVars.nOfSubSched), 1, sizeof(dpScdVars.nOfSubSched)},
   {(void*)&dpScdVars.nOfTba, sizeof(dpScdVars.nOfTba), 1, sizeof(dpScdVars.nOfTba)},
   {(void*)&dpTstVars.AreYouAliveSrc, sizeof(dpTstVars.AreYouAliveSrc), 1, sizeof(dpTstVars.AreYouAliveSrc)},
   {(void*)&dpTstVars.AreYouAliveStart, sizeof(dpTstVars.AreYouAliveStart), 1, sizeof(dpTstVars.AreYouAliveStart)},
   {(void*)&dpTstVars.OnBoardConnectDest, sizeof(dpTstVars.OnBoardConnectDest), 1, sizeof(dpTstVars.OnBoardConnectDest)},
   {(void*)&dpVerVars.failCodeAccFailed, sizeof(dpVerVars.failCodeAccFailed), 1, sizeof(dpVerVars.failCodeAccFailed)},
   {(void*)&dpVerVars.failCodePrgrFailed, sizeof(dpVerVars.failCodePrgrFailed), 1, sizeof(dpVerVars.failCodePrgrFailed)},
   {(void*)&dpVerVars.failCodeStartFailed, sizeof(dpVerVars.failCodeStartFailed), 1, sizeof(dpVerVars.failCodeStartFailed)},
   {(void*)&dpVerVars.failCodeTermFailed, sizeof(dpVerVars.failCodeTermFailed), 1, sizeof(dpVerVars.failCodeTermFailed)},
   {(void*)&dpVerVars.invDestRerouting, sizeof(dpVerVars.invDestRerouting), 1, sizeof(dpVerVars.invDestRerouting)},
   {(void*)&dpVerVars.nOfAccFailed, sizeof(dpVerVars.nOfAccFailed), 1, sizeof(dpVerVars.nOfAccFailed)},
   {(void*)&dpVerVars.nOfPrgrFailed, sizeof(dpVerVars.nOfPrgrFailed), 1, sizeof(dpVerVars.nOfPrgrFailed)},
   {(void*)&dpVerVars.nOfReroutingFailed, sizeof(dpVerVars.nOfReroutingFailed), 1, sizeof(dpVerVars.nOfReroutingFailed)},
   {(void*)&dpVerVars.nOfStartFailed, sizeof(dpVerVars.nOfStartFailed), 1, sizeof(dpVerVars.nOfStartFailed)},
   {(void*)&dpVerVars.nOfTermFailed, sizeof(dpVerVars.nOfTermFailed), 1, sizeof(dpVerVars.nOfTermFailed)},
   {(void*)&dpVerVars.pcktIdAccFailed, sizeof(dpVerVars.pcktIdAccFailed), 1, sizeof(dpVerVars.pcktIdAccFailed)},
   {(void*)&dpVerVars.pcktIdPrgrFailed, sizeof(dpVerVars.pcktIdPrgrFailed), 1, sizeof(dpVerVars.pcktIdPrgrFailed)},
   {(void*)&dpVerVars.pcktIdReroutingFailed, sizeof(dpVerVars.pcktIdReroutingFailed), 1, sizeof(dpVerVars.pcktIdReroutingFailed)},
   {(void*)&dpVerVars.pcktIdStartFailed, sizeof(dpVerVars.pcktIdStartFailed), 1, sizeof(dpVerVars.pcktIdStartFailed)},
   {(void*)&dpVerVars.pcktIdTermFailed, sizeof(dpVerVars.pcktIdTermFailed), 1, sizeof(dpVerVars.pcktIdTermFailed)},
   {(void*)&dpVerVars.stepPrgrFailed, sizeof(dpVerVars.stepPrgrFailed), 1, sizeof(dpVerVars.stepPrgrFailed)},
   {(void*)&dpVerVars.verFailCode, sizeof(dpVerVars.verFailCode), 1, sizeof(dpVerVars.verFailCode)},
   {(void*)&dpVerVars.verFailData, sizeof(dpVerVars.verFailData), 1, sizeof(dpVerVars.verFailData)}
};

static DpMetaInfoEntry_t* getMetaInfoParam(CrPsParId_t id)
{
   DpMetaInfoEntry_t* p;
   p = NULL;
   if (id >= DpIdParamsLowest && id <= DpIdParamsHighest)
   {
      p = &dpMetaInfoParams[id-DpIdParamsLowest];
   }
   return p;
}

static DpMetaInfoEntry_t* getMetaInfoVar(CrPsParId_t id)
{
   DpMetaInfoEntry_t* p;
   p = NULL;
   if (id >= DpIdVarsLowest && id <= DpIdVarsHighest)
   {
      p = &dpMetaInfoVars[id-DpIdVarsLowest];
   }
   return p;
}

static DpMetaInfoEntry_t* getMetaInfo(CrPsParId_t id)
{
   DpMetaInfoEntry_t* p;
   p = getMetaInfoParam(id);
   if (p == NULL)
   {
      p = getMetaInfoVar(id);
   }
   return p;
}

/**
 * Get the value of a datapool item by identifier.
 * @param id The datapool item identifier
 * @param dest The address of the target variable where the value gets copied
 * to.
 * @return Number of bytes copied. 0 if id is invalid.
 */
size_t getDpValue(CrPsParId_t id, void* dest)
{
   DpMetaInfoEntry_t* entry;
   entry = getMetaInfo(id);
   if (entry == NULL)
   {
      return 0;
   }
   (void)memcpy(dest, entry->addr, entry->length);
   return entry->length;
}

/**
 * Get the value of a datapool item plus meta information by identifier.
 * @param id The datapool item identifier
 * @param dest The address of the target variable where the value gets copied
 * to.
 * @param pElementLength Pointer to where the element size is copied to.
 * @param pNElements Pointer to where the number of elements is copied
 * to.@return Number of bytes copied. 0 if id is invalid.
 */
size_t getDpValueEx(CrPsParId_t id, void* dest, size_t* pElementLength, unsigned int* pNElements)
{
   DpMetaInfoEntry_t* entry;
   entry = getMetaInfo(id);
   if (entry == NULL)
   {
      return 0;
   }
   (void)memcpy(dest, entry->addr, entry->length);
   *pElementLength = entry->elementLength;
   *pNElements = entry->nElements;
   return entry->length;
}

/**
 * Set the value of a datapool item by identifier
 * @param id The datapool item identifier
 * @param src The address of the source variable where the value gets copied
 * from.
 * @return Number of bytes copied. 0 if id is invalid.
 */
int setDpValue(CrPsParId_t id, const void* src)
{
   DpMetaInfoEntry_t* entry;
   entry = getMetaInfo(id);
   if (entry == NULL)
   {
      return 0;
   }
   (void)memcpy(entry->addr, src, entry->length);
   return entry->length;
}

/**
 * Set the value of a datapool item by identifier and get meta information
 * @param id The datapool item identifier
 * @param src The address of the source variable where the value gets copied
 * from.
 * @param dest Pointer to pointer to where the element address is copied
 * to.@param pElementLength Pointer to where the element size is copied to.
 * @param pNElements Pointer to where the number of elements is copied
 * to.@return Number of bytes copied. 0 if id is invalid.
 */
int setDpValueEx(CrPsParId_t id, const void* src, void** dest, size_t* pElementLength, unsigned int* pNElements)
{
   DpMetaInfoEntry_t* entry;
   entry = getMetaInfo(id);
   if (entry == NULL)
   {
      return 0;
   }
   (void)memcpy(entry->addr, src, entry->length);
   *dest = entry->addr;
   *pElementLength = entry->elementLength;
   *pNElements = entry->nElements;
   return entry->length;
}

/**
 * Get the size of a datapool item by identifier.
 * @param id The datapool item identifier
 * @return The size of the datapool parameter. 0 if id is invalid.
 */
size_t getDpSize(CrPsParId_t id)
{
   DpMetaInfoEntry_t* entry;
   entry = getMetaInfo(id);
   if (entry == NULL)
   {
      return 0;
   }
   return entry->length;
}

/**
 * Get the size of a datapool parameter by identifier.
 * @param id The datapool parameter identifier
 * @return The size of the datapool parameter. 0 if id is invalid.
 */
size_t getDpParamSize(CrPsParId_t id)
{
   DpMetaInfoEntry_t* entry;
   entry = getMetaInfoParam(id);
   if (entry == NULL)
   {
      return 0;
   }
   return entry->length;
}

/**
 * Get the size of a datapool variable by identifier.
 * @param id The datapool variable identifier
 * @return The size of the datapool variable. 0 if id is invalid.
 */
size_t getDpVarSize(CrPsParId_t id)
{
   DpMetaInfoEntry_t* entry;
   entry = getMetaInfoVar(id);
   if (entry == NULL)
   {
      return 0;
   }
   return entry->length;
}
