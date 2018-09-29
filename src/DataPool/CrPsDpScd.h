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
#ifndef CRPSDPSCD_H_
#define CRPSDPSCD_H_

#include "CrPsTypes.h"
#include "CrPsConstants.h"
#include "CrFwUserConstants.h"
#include "CrFwConstants.h"


/**
 * Type description
 */
typedef struct {
   /**
    * Enable status of a sub-schedule
    */
   CrFwBool_t isSubSchedEnabled[SCD_N_SUB_TBS];
   /**
    * Enable status of time-based schedule
    */
   CrFwBool_t isTbsEnabled;
   /**
    * Number of TBAs in group
    */
   CrPsNTba_t nOfTbaInGroup[SCD_N_GROUP];
   /**
    * Number of TBAs in sub-schedule
    */
   CrPsNTba_t nOfTbaInSubSched[SCD_N_SUB_TBS];
   /**
    * Time margin for time-based scheduling service
    */
   CrFwTimeStamp_t timeMargin;
} DpScdParams_t;

/**
 * Type description
 */
typedef struct {
   /**
    * Identifier of next time-based activity due for release
    */
   CrPsNTba_t firstTba;
   /**
    * Enabled flag for time-based schedule group
    */
   CrFwBool_t isGroupEnabled[SCD_N_GROUP];
   /**
    * InUse flag for time-based schedule group
    */
   CrFwBool_t isGroupInUse[SCD_N_GROUP];
   /**
    * Number of non-empty groups
    */
   CrPsNSubSchedGroup_t nOfGroup;
   /**
    * Number of non-empty sub-schedules
    */
   CrPsNSubSchedGroup_t nOfSubSched;
   /**
    * Number of currently defined time-based activities (TBAs)
    */
   CrPsNTba_t nOfTba;
} DpScdVars_t;

extern DpScdParams_t dpScdParams;
extern DpScdVars_t dpScdVars;

/**
 * Get the data pool array isSubSchedEnabled (Enable status of a sub-schedule)
 * @return The data pool array isSubSchedEnabled
 */
static inline CrFwBool_t* getDpScdIsSubSchedEnabledArray() {
   return &dpScdParams.isSubSchedEnabled[0];
}

/**
 * Get the value of the i-th element in the data pool array isSubSchedEnabled
 * (Enable status of a sub-schedule)
 * @param i Index variable
 * @return The i-th element in the data pool array isSubSchedEnabled
 */
static inline CrFwBool_t getDpScdIsSubSchedEnabledItem(int i) {
   return dpScdParams.isSubSchedEnabled[i];
}

/**
 * Set the value of the i-th element in the data pool array isSubSchedEnabled
 * (Enable status of a sub-schedule)
 * @param i Index variable
 * @param isSubSchedEnabled The value to be stored into the i-th element of
 * data pool array isSubSchedEnabled.
 */
static inline void setDpScdIsSubSchedEnabledItem(int i, CrFwBool_t isSubSchedEnabled) {
   dpScdParams.isSubSchedEnabled[i] = isSubSchedEnabled;
}

/**
 * Get the value of the data pool item isTbsEnabled (Enable status of
 * time-based schedule)
 * @return The value of data pool item isTbsEnabled
 */
static inline CrFwBool_t getDpScdIsTbsEnabled() {
   return dpScdParams.isTbsEnabled;
}

/**
 * Set the value of the data pool item isTbsEnabled (Enable status of
 * time-based schedule)
 * @param isTbsEnabled The value to be stored into the data pool item
 * isTbsEnabled.
 */
static inline void setDpScdIsTbsEnabled(CrFwBool_t isTbsEnabled) {
   dpScdParams.isTbsEnabled = isTbsEnabled;
}

/**
 * Get the data pool array nOfTbaInGroup (Number of TBAs in group)
 * @return The data pool array nOfTbaInGroup
 */
static inline CrPsNTba_t* getDpScdNOfTbaInGroupArray() {
   return &dpScdParams.nOfTbaInGroup[0];
}

/**
 * Get the value of the i-th element in the data pool array nOfTbaInGroup
 * (Number of TBAs in group)
 * @param i Index variable
 * @return The i-th element in the data pool array nOfTbaInGroup
 */
static inline CrPsNTba_t getDpScdNOfTbaInGroupItem(int i) {
   return dpScdParams.nOfTbaInGroup[i];
}

/**
 * Set the value of the i-th element in the data pool array nOfTbaInGroup
 * (Number of TBAs in group)
 * @param i Index variable
 * @param nOfTbaInGroup The value to be stored into the i-th element of data
 * pool array nOfTbaInGroup.
 */
static inline void setDpScdNOfTbaInGroupItem(int i, CrPsNTba_t nOfTbaInGroup) {
   dpScdParams.nOfTbaInGroup[i] = nOfTbaInGroup;
}

/**
 * Get the data pool array nOfTbaInSubSched (Number of TBAs in sub-schedule)
 * @return The data pool array nOfTbaInSubSched
 */
static inline CrPsNTba_t* getDpScdNOfTbaInSubSchedArray() {
   return &dpScdParams.nOfTbaInSubSched[0];
}

/**
 * Get the value of the i-th element in the data pool array nOfTbaInSubSched
 * (Number of TBAs in sub-schedule)
 * @param i Index variable
 * @return The i-th element in the data pool array nOfTbaInSubSched
 */
static inline CrPsNTba_t getDpScdNOfTbaInSubSchedItem(int i) {
   return dpScdParams.nOfTbaInSubSched[i];
}

/**
 * Set the value of the i-th element in the data pool array nOfTbaInSubSched
 * (Number of TBAs in sub-schedule)
 * @param i Index variable
 * @param nOfTbaInSubSched The value to be stored into the i-th element of
 * data pool array nOfTbaInSubSched.
 */
static inline void setDpScdNOfTbaInSubSchedItem(int i, CrPsNTba_t nOfTbaInSubSched) {
   dpScdParams.nOfTbaInSubSched[i] = nOfTbaInSubSched;
}

/**
 * Get the value of the data pool item timeMargin (Time margin for time-based
 * scheduling service)
 * @return The value of data pool item timeMargin
 */
static inline CrFwTimeStamp_t getDpScdTimeMargin() {
   return dpScdParams.timeMargin;
}

/**
 * Set the value of the data pool item timeMargin (Time margin for time-based
 * scheduling service)
 * @param timeMargin The value to be stored into the data pool item
 * timeMargin.
 */
static inline void setDpScdTimeMargin(CrFwTimeStamp_t timeMargin) {
   dpScdParams.timeMargin = timeMargin;
}

/**
 * Get the value of the data pool item firstTba (Identifier of next time-based
 * activity due for release)
 * @return The value of data pool item firstTba
 */
static inline CrPsNTba_t getDpScdFirstTba() {
   return dpScdVars.firstTba;
}

/**
 * Set the value of the data pool item firstTba (Identifier of next time-based
 * activity due for release)
 * @param firstTba The value to be stored into the data pool item firstTba.
 */
static inline void setDpScdFirstTba(CrPsNTba_t firstTba) {
   dpScdVars.firstTba = firstTba;
}

/**
 * Get the data pool array isGroupEnabled (Enabled flag for time-based
 * schedule group)
 * @return The data pool array isGroupEnabled
 */
static inline CrFwBool_t* getDpScdIsGroupEnabledArray() {
   return &dpScdVars.isGroupEnabled[0];
}

/**
 * Get the value of the i-th element in the data pool array isGroupEnabled
 * (Enabled flag for time-based schedule group)
 * @param i Index variable
 * @return The i-th element in the data pool array isGroupEnabled
 */
static inline CrFwBool_t getDpScdIsGroupEnabledItem(int i) {
   return dpScdVars.isGroupEnabled[i];
}

/**
 * Set the value of the i-th element in the data pool array isGroupEnabled
 * (Enabled flag for time-based schedule group)
 * @param i Index variable
 * @param isGroupEnabled The value to be stored into the i-th element of data
 * pool array isGroupEnabled.
 */
static inline void setDpScdIsGroupEnabledItem(int i, CrFwBool_t isGroupEnabled) {
   dpScdVars.isGroupEnabled[i] = isGroupEnabled;
}

/**
 * Get the data pool array isGroupInUse (InUse flag for time-based schedule
 * group)
 * @return The data pool array isGroupInUse
 */
static inline CrFwBool_t* getDpScdIsGroupInUseArray() {
   return &dpScdVars.isGroupInUse[0];
}

/**
 * Get the value of the i-th element in the data pool array isGroupInUse
 * (InUse flag for time-based schedule group)
 * @param i Index variable
 * @return The i-th element in the data pool array isGroupInUse
 */
static inline CrFwBool_t getDpScdIsGroupInUseItem(int i) {
   return dpScdVars.isGroupInUse[i];
}

/**
 * Set the value of the i-th element in the data pool array isGroupInUse
 * (InUse flag for time-based schedule group)
 * @param i Index variable
 * @param isGroupInUse The value to be stored into the i-th element of data
 * pool array isGroupInUse.
 */
static inline void setDpScdIsGroupInUseItem(int i, CrFwBool_t isGroupInUse) {
   dpScdVars.isGroupInUse[i] = isGroupInUse;
}

/**
 * Get the value of the data pool item nOfGroup (Number of non-empty groups)
 * @return The value of data pool item nOfGroup
 */
static inline CrPsNSubSchedGroup_t getDpScdNOfGroup() {
   return dpScdVars.nOfGroup;
}

/**
 * Set the value of the data pool item nOfGroup (Number of non-empty groups)
 * @param nOfGroup The value to be stored into the data pool item nOfGroup.
 */
static inline void setDpScdNOfGroup(CrPsNSubSchedGroup_t nOfGroup) {
   dpScdVars.nOfGroup = nOfGroup;
}

/**
 * Get the value of the data pool item nOfSubSched (Number of non-empty
 * sub-schedules)
 * @return The value of data pool item nOfSubSched
 */
static inline CrPsNSubSchedGroup_t getDpScdNOfSubSched() {
   return dpScdVars.nOfSubSched;
}

/**
 * Set the value of the data pool item nOfSubSched (Number of non-empty
 * sub-schedules)
 * @param nOfSubSched The value to be stored into the data pool item
 * nOfSubSched.
 */
static inline void setDpScdNOfSubSched(CrPsNSubSchedGroup_t nOfSubSched) {
   dpScdVars.nOfSubSched = nOfSubSched;
}

/**
 * Get the value of the data pool item nOfTba (Number of currently defined
 * time-based activities (TBAs))
 * @return The value of data pool item nOfTba
 */
static inline CrPsNTba_t getDpScdNOfTba() {
   return dpScdVars.nOfTba;
}

/**
 * Set the value of the data pool item nOfTba (Number of currently defined
 * time-based activities (TBAs))
 * @param nOfTba The value to be stored into the data pool item nOfTba.
 */
static inline void setDpScdNOfTba(CrPsNTba_t nOfTba) {
   dpScdVars.nOfTba = nOfTba;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSDPSCD_H */
