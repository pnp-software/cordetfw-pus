/**
 * @file
 * @ingroup gen_dp
 *
 * Interface for accessing data pool items.
 *
 * @note This file was generated on 2018-09-29 16:05:16
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSDPHK_H_
#define CRPSDPHK_H_

#include "CrPsTypes.h"
#include "CrPsConstants.h"
#include "CrFwUserConstants.h"
#include "CrFwConstants.h"


/**
 * Type description
 */
typedef struct {
   /**
    * Address of Debug Variables
    */
   CrPsThirtytwoBit_t debugVarAddr[HK_N_DEBUG_VAR];
   /**
    * Destination of report definitions in the RDL
    */
   CrFwDestSrc_t dest[HK_N_REP_DEF];
   /**
    * Enable status of report definitions in the RDL
    */
   CrFwBool_t isEnabled[HK_N_REP_DEF];
   /**
    * Periods of report definitions in the RDL
    */
   CrPsCycleCnt_t period[HK_N_REP_DEF];
   /**
    * SIDs of report definitions in the RDL
    */
   CrPsSID_t sid[HK_N_REP_DEF];
} DpHkParams_t;

/**
 * Type description
 */
typedef struct {
   /**
    * Cycle Counter for Reports in RDL
    */
   CrPsCycleCnt_t cycleCnt[HK_N_REP_DEF];
   /**
    * Value of Debug Variables
    */
   CrPsThirtytwoBit_t debugVar[HK_N_DEBUG_VAR];
   /**
    * The i-th element of this array is the identifier of the Sampling Buffer
    * for the i-th Report Definition in the RDL
    */
   CrPsSampleBufId_t sampleBufId[HK_N_REP_DEF];
} DpHkVars_t;

extern DpHkParams_t dpHkParams;
extern DpHkVars_t dpHkVars;

/**
 * Get the data pool array debugVarAddr (Address of Debug Variables)
 * @return The data pool array debugVarAddr
 */
static inline CrPsThirtytwoBit_t* getDpHkDebugVarAddrArray() {
   return &dpHkParams.debugVarAddr[0];
}

/**
 * Get the value of the i-th element in the data pool array debugVarAddr
 * (Address of Debug Variables)
 * @param i Index variable
 * @return The i-th element in the data pool array debugVarAddr
 */
static inline CrPsThirtytwoBit_t getDpHkDebugVarAddrItem(int i) {
   return dpHkParams.debugVarAddr[i];
}

/**
 * Set the value of the i-th element in the data pool array debugVarAddr
 * (Address of Debug Variables)
 * @param i Index variable
 * @param debugVarAddr The value to be stored into the i-th element of data
 * pool array debugVarAddr.
 */
static inline void setDpHkDebugVarAddrItem(int i, CrPsThirtytwoBit_t debugVarAddr) {
   dpHkParams.debugVarAddr[i] = debugVarAddr;
}

/**
 * Get the data pool array dest (Destination of report definitions in the RDL)
 * @return The data pool array dest
 */
static inline CrFwDestSrc_t* getDpHkDestArray() {
   return &dpHkParams.dest[0];
}

/**
 * Get the value of the i-th element in the data pool array dest (Destination
 * of report definitions in the RDL)
 * @param i Index variable
 * @return The i-th element in the data pool array dest
 */
static inline CrFwDestSrc_t getDpHkDestItem(int i) {
   return dpHkParams.dest[i];
}

/**
 * Set the value of the i-th element in the data pool array dest (Destination
 * of report definitions in the RDL)
 * @param i Index variable
 * @param dest The value to be stored into the i-th element of data pool array
 * dest.
 */
static inline void setDpHkDestItem(int i, CrFwDestSrc_t dest) {
   dpHkParams.dest[i] = dest;
}

/**
 * Get the data pool array isEnabled (Enable status of report definitions in
 * the RDL)
 * @return The data pool array isEnabled
 */
static inline CrFwBool_t* getDpHkIsEnabledArray() {
   return &dpHkParams.isEnabled[0];
}

/**
 * Get the value of the i-th element in the data pool array isEnabled (Enable
 * status of report definitions in the RDL)
 * @param i Index variable
 * @return The i-th element in the data pool array isEnabled
 */
static inline CrFwBool_t getDpHkIsEnabledItem(int i) {
   return dpHkParams.isEnabled[i];
}

/**
 * Set the value of the i-th element in the data pool array isEnabled (Enable
 * status of report definitions in the RDL)
 * @param i Index variable
 * @param isEnabled The value to be stored into the i-th element of data pool
 * array isEnabled.
 */
static inline void setDpHkIsEnabledItem(int i, CrFwBool_t isEnabled) {
   dpHkParams.isEnabled[i] = isEnabled;
}

/**
 * Get the data pool array period (Periods of report definitions in the RDL)
 * @return The data pool array period
 */
static inline CrPsCycleCnt_t* getDpHkPeriodArray() {
   return &dpHkParams.period[0];
}

/**
 * Get the value of the i-th element in the data pool array period (Periods of
 * report definitions in the RDL)
 * @param i Index variable
 * @return The i-th element in the data pool array period
 */
static inline CrPsCycleCnt_t getDpHkPeriodItem(int i) {
   return dpHkParams.period[i];
}

/**
 * Set the value of the i-th element in the data pool array period (Periods of
 * report definitions in the RDL)
 * @param i Index variable
 * @param period The value to be stored into the i-th element of data pool
 * array period.
 */
static inline void setDpHkPeriodItem(int i, CrPsCycleCnt_t period) {
   dpHkParams.period[i] = period;
}

/**
 * Get the data pool array sid (SIDs of report definitions in the RDL)
 * @return The data pool array sid
 */
static inline CrPsSID_t* getDpHkSidArray() {
   return &dpHkParams.sid[0];
}

/**
 * Get the value of the i-th element in the data pool array sid (SIDs of
 * report definitions in the RDL)
 * @param i Index variable
 * @return The i-th element in the data pool array sid
 */
static inline CrPsSID_t getDpHkSidItem(int i) {
   return dpHkParams.sid[i];
}

/**
 * Set the value of the i-th element in the data pool array sid (SIDs of
 * report definitions in the RDL)
 * @param i Index variable
 * @param sid The value to be stored into the i-th element of data pool array
 * sid.
 */
static inline void setDpHkSidItem(int i, CrPsSID_t sid) {
   dpHkParams.sid[i] = sid;
}

/**
 * Get the data pool array cycleCnt (Cycle Counter for Reports in RDL)
 * @return The data pool array cycleCnt
 */
static inline CrPsCycleCnt_t* getDpHkCycleCntArray() {
   return &dpHkVars.cycleCnt[0];
}

/**
 * Get the value of the i-th element in the data pool array cycleCnt (Cycle
 * Counter for Reports in RDL)
 * @param i Index variable
 * @return The i-th element in the data pool array cycleCnt
 */
static inline CrPsCycleCnt_t getDpHkCycleCntItem(int i) {
   return dpHkVars.cycleCnt[i];
}

/**
 * Set the value of the i-th element in the data pool array cycleCnt (Cycle
 * Counter for Reports in RDL)
 * @param i Index variable
 * @param cycleCnt The value to be stored into the i-th element of data pool
 * array cycleCnt.
 */
static inline void setDpHkCycleCntItem(int i, CrPsCycleCnt_t cycleCnt) {
   dpHkVars.cycleCnt[i] = cycleCnt;
}

/**
 * Get the data pool array debugVar (Value of Debug Variables)
 * @return The data pool array debugVar
 */
static inline CrPsThirtytwoBit_t* getDpHkDebugVarArray() {
   return &dpHkVars.debugVar[0];
}

/**
 * Get the value of the i-th element in the data pool array debugVar (Value of
 * Debug Variables)
 * @param i Index variable
 * @return The i-th element in the data pool array debugVar
 */
static inline CrPsThirtytwoBit_t getDpHkDebugVarItem(int i) {
   return dpHkVars.debugVar[i];
}

/**
 * Set the value of the i-th element in the data pool array debugVar (Value of
 * Debug Variables)
 * @param i Index variable
 * @param debugVar The value to be stored into the i-th element of data pool
 * array debugVar.
 */
static inline void setDpHkDebugVarItem(int i, CrPsThirtytwoBit_t debugVar) {
   dpHkVars.debugVar[i] = debugVar;
}

/**
 * Get the data pool array sampleBufId (The i-th element of this array is the
 * identifier of the Sampling Buffer for the i-th Report Definition in the
 * RDL)
 * @return The data pool array sampleBufId
 */
static inline CrPsSampleBufId_t* getDpHkSampleBufIdArray() {
   return &dpHkVars.sampleBufId[0];
}

/**
 * Get the value of the i-th element in the data pool array sampleBufId (The
 * i-th element of this array is the identifier of the Sampling Buffer for the
 * i-th Report Definition in the RDL)
 * @param i Index variable
 * @return The i-th element in the data pool array sampleBufId
 */
static inline CrPsSampleBufId_t getDpHkSampleBufIdItem(int i) {
   return dpHkVars.sampleBufId[i];
}

/**
 * Set the value of the i-th element in the data pool array sampleBufId (The
 * i-th element of this array is the identifier of the Sampling Buffer for the
 * i-th Report Definition in the RDL)
 * @param i Index variable
 * @param sampleBufId The value to be stored into the i-th element of data
 * pool array sampleBufId.
 */
static inline void setDpHkSampleBufIdItem(int i, CrPsSampleBufId_t sampleBufId) {
   dpHkVars.sampleBufId[i] = sampleBufId;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSDPHK_H */
