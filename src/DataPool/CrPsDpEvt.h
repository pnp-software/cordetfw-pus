/**
 * @file
 * @ingroup gen_dp
 *
 * Interface for accessing data pool items.
 *
 * @note This file was generated on 2018-07-14 22:58:14
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSDPEVT_H_
#define CRPSDPEVT_H_

#include "CrPsTypes.h"
#include "CrPsConstants.h"
#include "CrFwUserConstants.h"
#include "CrFwConstants.h"


/**
 * Type description
 */
typedef struct {
   /**
    * Enable status of the event identifiers
    */
   CrFwBool_t isEidEnabled[EVT_N_ID];
   /**
    * Event identifier of the last generated level 1 event report
    */
   CrPsEvtId_t lastEvtEid_1;
   /**
    * Event identifier of the last generated level 2 event report
    */
   CrPsEvtId_t lastEvtEid_2;
   /**
    * Event identifier of the last generated level 3 event report
    */
   CrPsEvtId_t lastEvtEid_3;
   /**
    * Event identifier of the last generated level 4event report
    */
   CrPsEvtId_t lastEvtEid_4;
   /**
    * Time when the last level 1 event report was generated
    */
   CrFwTime_t lastEvtTime_1;
   /**
    * Time when the last level 2 event report was generated
    */
   CrFwTime_t lastEvtTime_2;
   /**
    * Time when the last level 3 event report was generated
    */
   CrFwTime_t lastEvtTime_3;
   /**
    * Time when the last level 4 event report was generated
    */
   CrFwTime_t lastEvtTime_4;
   /**
    * Number of detected occurrences of level 1 events
    */
   CrPsNEvtRep_t nOfDetectedEvts_1;
   /**
    * Number of detected occurrences of level 2 events
    */
   CrPsNEvtRep_t nOfDetectedEvts_2;
   /**
    * Number of detected occurrences of level 3 events
    */
   CrPsNEvtRep_t nOfDetectedEvts_3;
   /**
    * Number of detected occurrences of level 4 events
    */
   CrPsNEvtRep_t nOfDetectedEvts_4;
   /**
    * Number of event identifiers of level 1 which are disabled
    */
   CrPsNEvtId_t nOfDisabledEid_1;
   /**
    * Number of event identifiers of level 2 which are disabled
    */
   CrPsEvtId_t nOfDisabledEid_2;
   /**
    * Number of event identifiers of level 3 which are disabled
    */
   CrPsNEvtId_t nOfDisabledEid_3;
   /**
    * Number of event identifiers of level 4 which are disabled
    */
   CrPsEvtId_t nOfDisabledEid_4;
   /**
    * Number of generated level 1 event reports
    */
   CrPsNEvtRep_t nOfGenEvtRep_1;
   /**
    * Number of generated level 2 event reports
    */
   CrPsNEvtRep_t nOfGenEvtRep_2;
   /**
    * Number of generated level 3 event reports
    */
   CrPsNEvtRep_t nOfGenEvtRep_3;
   /**
    * Number of generated level 4 event reports
    */
   CrPsNEvtRep_t nOfGenEvtRep_4;
} DpEvtVars_t;

extern DpEvtVars_t dpEvtVars;

/**
 * Get the data pool array isEidEnabled (Enable status of the event
 * identifiers)
 * @return The data pool array isEidEnabled
 */
static inline CrFwBool_t* getDpEvtIsEidEnabledArray() {
   return &dpEvtVars.isEidEnabled[0];
}

/**
 * Get the value of the i-th element in the data pool array isEidEnabled
 * (Enable status of the event identifiers)
 * @param i Index variable
 * @return The i-th element in the data pool array isEidEnabled
 */
static inline CrFwBool_t getDpEvtIsEidEnabledItem(int i) {
   return dpEvtVars.isEidEnabled[i];
}

/**
 * Set the value of the i-th element in the data pool array isEidEnabled
 * (Enable status of the event identifiers)
 * @param i Index variable
 * @param isEidEnabled The value to be stored into the i-th element of data
 * pool array isEidEnabled.
 */
static inline void setDpEvtIsEidEnabledItem(int i, CrFwBool_t isEidEnabled) {
   dpEvtVars.isEidEnabled[i] = isEidEnabled;
}

/**
 * Get the value of the data pool item lastEvtEid_1 (Event identifier of the
 * last generated level 1 event report)
 * @return The value of data pool item lastEvtEid_1
 */
static inline CrPsEvtId_t getDpEvtLastEvtEid_1() {
   return dpEvtVars.lastEvtEid_1;
}

/**
 * Set the value of the data pool item lastEvtEid_1 (Event identifier of the
 * last generated level 1 event report)
 * @param lastEvtEid_1 The value to be stored into the data pool item
 * lastEvtEid_1.
 */
static inline void setDpEvtLastEvtEid_1(CrPsEvtId_t lastEvtEid_1) {
   dpEvtVars.lastEvtEid_1 = lastEvtEid_1;
}

/**
 * Get the value of the data pool item lastEvtEid_2 (Event identifier of the
 * last generated level 2 event report)
 * @return The value of data pool item lastEvtEid_2
 */
static inline CrPsEvtId_t getDpEvtLastEvtEid_2() {
   return dpEvtVars.lastEvtEid_2;
}

/**
 * Set the value of the data pool item lastEvtEid_2 (Event identifier of the
 * last generated level 2 event report)
 * @param lastEvtEid_2 The value to be stored into the data pool item
 * lastEvtEid_2.
 */
static inline void setDpEvtLastEvtEid_2(CrPsEvtId_t lastEvtEid_2) {
   dpEvtVars.lastEvtEid_2 = lastEvtEid_2;
}

/**
 * Get the value of the data pool item lastEvtEid_3 (Event identifier of the
 * last generated level 3 event report)
 * @return The value of data pool item lastEvtEid_3
 */
static inline CrPsEvtId_t getDpEvtLastEvtEid_3() {
   return dpEvtVars.lastEvtEid_3;
}

/**
 * Set the value of the data pool item lastEvtEid_3 (Event identifier of the
 * last generated level 3 event report)
 * @param lastEvtEid_3 The value to be stored into the data pool item
 * lastEvtEid_3.
 */
static inline void setDpEvtLastEvtEid_3(CrPsEvtId_t lastEvtEid_3) {
   dpEvtVars.lastEvtEid_3 = lastEvtEid_3;
}

/**
 * Get the value of the data pool item lastEvtEid_4 (Event identifier of the
 * last generated level 4event report)
 * @return The value of data pool item lastEvtEid_4
 */
static inline CrPsEvtId_t getDpEvtLastEvtEid_4() {
   return dpEvtVars.lastEvtEid_4;
}

/**
 * Set the value of the data pool item lastEvtEid_4 (Event identifier of the
 * last generated level 4event report)
 * @param lastEvtEid_4 The value to be stored into the data pool item
 * lastEvtEid_4.
 */
static inline void setDpEvtLastEvtEid_4(CrPsEvtId_t lastEvtEid_4) {
   dpEvtVars.lastEvtEid_4 = lastEvtEid_4;
}

/**
 * Get the value of the data pool item lastEvtTime_1 (Time when the last level
 * 1 event report was generated)
 * @return The value of data pool item lastEvtTime_1
 */
static inline CrFwTime_t getDpEvtLastEvtTime_1() {
   return dpEvtVars.lastEvtTime_1;
}

/**
 * Set the value of the data pool item lastEvtTime_1 (Time when the last level
 * 1 event report was generated)
 * @param lastEvtTime_1 The value to be stored into the data pool item
 * lastEvtTime_1.
 */
static inline void setDpEvtLastEvtTime_1(CrFwTime_t lastEvtTime_1) {
   dpEvtVars.lastEvtTime_1 = lastEvtTime_1;
}

/**
 * Get the value of the data pool item lastEvtTime_2 (Time when the last level
 * 2 event report was generated)
 * @return The value of data pool item lastEvtTime_2
 */
static inline CrFwTime_t getDpEvtLastEvtTime_2() {
   return dpEvtVars.lastEvtTime_2;
}

/**
 * Set the value of the data pool item lastEvtTime_2 (Time when the last level
 * 2 event report was generated)
 * @param lastEvtTime_2 The value to be stored into the data pool item
 * lastEvtTime_2.
 */
static inline void setDpEvtLastEvtTime_2(CrFwTime_t lastEvtTime_2) {
   dpEvtVars.lastEvtTime_2 = lastEvtTime_2;
}

/**
 * Get the value of the data pool item lastEvtTime_3 (Time when the last level
 * 3 event report was generated)
 * @return The value of data pool item lastEvtTime_3
 */
static inline CrFwTime_t getDpEvtLastEvtTime_3() {
   return dpEvtVars.lastEvtTime_3;
}

/**
 * Set the value of the data pool item lastEvtTime_3 (Time when the last level
 * 3 event report was generated)
 * @param lastEvtTime_3 The value to be stored into the data pool item
 * lastEvtTime_3.
 */
static inline void setDpEvtLastEvtTime_3(CrFwTime_t lastEvtTime_3) {
   dpEvtVars.lastEvtTime_3 = lastEvtTime_3;
}

/**
 * Get the value of the data pool item lastEvtTime_4 (Time when the last level
 * 4 event report was generated)
 * @return The value of data pool item lastEvtTime_4
 */
static inline CrFwTime_t getDpEvtLastEvtTime_4() {
   return dpEvtVars.lastEvtTime_4;
}

/**
 * Set the value of the data pool item lastEvtTime_4 (Time when the last level
 * 4 event report was generated)
 * @param lastEvtTime_4 The value to be stored into the data pool item
 * lastEvtTime_4.
 */
static inline void setDpEvtLastEvtTime_4(CrFwTime_t lastEvtTime_4) {
   dpEvtVars.lastEvtTime_4 = lastEvtTime_4;
}

/**
 * Get the value of the data pool item nOfDetectedEvts_1 (Number of detected
 * occurrences of level 1 events)
 * @return The value of data pool item nOfDetectedEvts_1
 */
static inline CrPsNEvtRep_t getDpEvtNOfDetectedEvts_1() {
   return dpEvtVars.nOfDetectedEvts_1;
}

/**
 * Set the value of the data pool item nOfDetectedEvts_1 (Number of detected
 * occurrences of level 1 events)
 * @param nOfDetectedEvts_1 The value to be stored into the data pool item
 * nOfDetectedEvts_1.
 */
static inline void setDpEvtNOfDetectedEvts_1(CrPsNEvtRep_t nOfDetectedEvts_1) {
   dpEvtVars.nOfDetectedEvts_1 = nOfDetectedEvts_1;
}

/**
 * Get the value of the data pool item nOfDetectedEvts_2 (Number of detected
 * occurrences of level 2 events)
 * @return The value of data pool item nOfDetectedEvts_2
 */
static inline CrPsNEvtRep_t getDpEvtNOfDetectedEvts_2() {
   return dpEvtVars.nOfDetectedEvts_2;
}

/**
 * Set the value of the data pool item nOfDetectedEvts_2 (Number of detected
 * occurrences of level 2 events)
 * @param nOfDetectedEvts_2 The value to be stored into the data pool item
 * nOfDetectedEvts_2.
 */
static inline void setDpEvtNOfDetectedEvts_2(CrPsNEvtRep_t nOfDetectedEvts_2) {
   dpEvtVars.nOfDetectedEvts_2 = nOfDetectedEvts_2;
}

/**
 * Get the value of the data pool item nOfDetectedEvts_3 (Number of detected
 * occurrences of level 3 events)
 * @return The value of data pool item nOfDetectedEvts_3
 */
static inline CrPsNEvtRep_t getDpEvtNOfDetectedEvts_3() {
   return dpEvtVars.nOfDetectedEvts_3;
}

/**
 * Set the value of the data pool item nOfDetectedEvts_3 (Number of detected
 * occurrences of level 3 events)
 * @param nOfDetectedEvts_3 The value to be stored into the data pool item
 * nOfDetectedEvts_3.
 */
static inline void setDpEvtNOfDetectedEvts_3(CrPsNEvtRep_t nOfDetectedEvts_3) {
   dpEvtVars.nOfDetectedEvts_3 = nOfDetectedEvts_3;
}

/**
 * Get the value of the data pool item nOfDetectedEvts_4 (Number of detected
 * occurrences of level 4 events)
 * @return The value of data pool item nOfDetectedEvts_4
 */
static inline CrPsNEvtRep_t getDpEvtNOfDetectedEvts_4() {
   return dpEvtVars.nOfDetectedEvts_4;
}

/**
 * Set the value of the data pool item nOfDetectedEvts_4 (Number of detected
 * occurrences of level 4 events)
 * @param nOfDetectedEvts_4 The value to be stored into the data pool item
 * nOfDetectedEvts_4.
 */
static inline void setDpEvtNOfDetectedEvts_4(CrPsNEvtRep_t nOfDetectedEvts_4) {
   dpEvtVars.nOfDetectedEvts_4 = nOfDetectedEvts_4;
}

/**
 * Get the value of the data pool item nOfDisabledEid_1 (Number of event
 * identifiers of level 1 which are disabled)
 * @return The value of data pool item nOfDisabledEid_1
 */
static inline CrPsNEvtId_t getDpEvtNOfDisabledEid_1() {
   return dpEvtVars.nOfDisabledEid_1;
}

/**
 * Set the value of the data pool item nOfDisabledEid_1 (Number of event
 * identifiers of level 1 which are disabled)
 * @param nOfDisabledEid_1 The value to be stored into the data pool item
 * nOfDisabledEid_1.
 */
static inline void setDpEvtNOfDisabledEid_1(CrPsNEvtId_t nOfDisabledEid_1) {
   dpEvtVars.nOfDisabledEid_1 = nOfDisabledEid_1;
}

/**
 * Get the value of the data pool item nOfDisabledEid_2 (Number of event
 * identifiers of level 2 which are disabled)
 * @return The value of data pool item nOfDisabledEid_2
 */
static inline CrPsEvtId_t getDpEvtNOfDisabledEid_2() {
   return dpEvtVars.nOfDisabledEid_2;
}

/**
 * Set the value of the data pool item nOfDisabledEid_2 (Number of event
 * identifiers of level 2 which are disabled)
 * @param nOfDisabledEid_2 The value to be stored into the data pool item
 * nOfDisabledEid_2.
 */
static inline void setDpEvtNOfDisabledEid_2(CrPsEvtId_t nOfDisabledEid_2) {
   dpEvtVars.nOfDisabledEid_2 = nOfDisabledEid_2;
}

/**
 * Get the value of the data pool item nOfDisabledEid_3 (Number of event
 * identifiers of level 3 which are disabled)
 * @return The value of data pool item nOfDisabledEid_3
 */
static inline CrPsNEvtId_t getDpEvtNOfDisabledEid_3() {
   return dpEvtVars.nOfDisabledEid_3;
}

/**
 * Set the value of the data pool item nOfDisabledEid_3 (Number of event
 * identifiers of level 3 which are disabled)
 * @param nOfDisabledEid_3 The value to be stored into the data pool item
 * nOfDisabledEid_3.
 */
static inline void setDpEvtNOfDisabledEid_3(CrPsNEvtId_t nOfDisabledEid_3) {
   dpEvtVars.nOfDisabledEid_3 = nOfDisabledEid_3;
}

/**
 * Get the value of the data pool item nOfDisabledEid_4 (Number of event
 * identifiers of level 4 which are disabled)
 * @return The value of data pool item nOfDisabledEid_4
 */
static inline CrPsEvtId_t getDpEvtNOfDisabledEid_4() {
   return dpEvtVars.nOfDisabledEid_4;
}

/**
 * Set the value of the data pool item nOfDisabledEid_4 (Number of event
 * identifiers of level 4 which are disabled)
 * @param nOfDisabledEid_4 The value to be stored into the data pool item
 * nOfDisabledEid_4.
 */
static inline void setDpEvtNOfDisabledEid_4(CrPsEvtId_t nOfDisabledEid_4) {
   dpEvtVars.nOfDisabledEid_4 = nOfDisabledEid_4;
}

/**
 * Get the value of the data pool item nOfGenEvtRep_1 (Number of generated
 * level 1 event reports)
 * @return The value of data pool item nOfGenEvtRep_1
 */
static inline CrPsNEvtRep_t getDpEvtNOfGenEvtRep_1() {
   return dpEvtVars.nOfGenEvtRep_1;
}

/**
 * Set the value of the data pool item nOfGenEvtRep_1 (Number of generated
 * level 1 event reports)
 * @param nOfGenEvtRep_1 The value to be stored into the data pool item
 * nOfGenEvtRep_1.
 */
static inline void setDpEvtNOfGenEvtRep_1(CrPsNEvtRep_t nOfGenEvtRep_1) {
   dpEvtVars.nOfGenEvtRep_1 = nOfGenEvtRep_1;
}

/**
 * Get the value of the data pool item nOfGenEvtRep_2 (Number of generated
 * level 2 event reports)
 * @return The value of data pool item nOfGenEvtRep_2
 */
static inline CrPsNEvtRep_t getDpEvtNOfGenEvtRep_2() {
   return dpEvtVars.nOfGenEvtRep_2;
}

/**
 * Set the value of the data pool item nOfGenEvtRep_2 (Number of generated
 * level 2 event reports)
 * @param nOfGenEvtRep_2 The value to be stored into the data pool item
 * nOfGenEvtRep_2.
 */
static inline void setDpEvtNOfGenEvtRep_2(CrPsNEvtRep_t nOfGenEvtRep_2) {
   dpEvtVars.nOfGenEvtRep_2 = nOfGenEvtRep_2;
}

/**
 * Get the value of the data pool item nOfGenEvtRep_3 (Number of generated
 * level 3 event reports)
 * @return The value of data pool item nOfGenEvtRep_3
 */
static inline CrPsNEvtRep_t getDpEvtNOfGenEvtRep_3() {
   return dpEvtVars.nOfGenEvtRep_3;
}

/**
 * Set the value of the data pool item nOfGenEvtRep_3 (Number of generated
 * level 3 event reports)
 * @param nOfGenEvtRep_3 The value to be stored into the data pool item
 * nOfGenEvtRep_3.
 */
static inline void setDpEvtNOfGenEvtRep_3(CrPsNEvtRep_t nOfGenEvtRep_3) {
   dpEvtVars.nOfGenEvtRep_3 = nOfGenEvtRep_3;
}

/**
 * Get the value of the data pool item nOfGenEvtRep_4 (Number of generated
 * level 4 event reports)
 * @return The value of data pool item nOfGenEvtRep_4
 */
static inline CrPsNEvtRep_t getDpEvtNOfGenEvtRep_4() {
   return dpEvtVars.nOfGenEvtRep_4;
}

/**
 * Set the value of the data pool item nOfGenEvtRep_4 (Number of generated
 * level 4 event reports)
 * @param nOfGenEvtRep_4 The value to be stored into the data pool item
 * nOfGenEvtRep_4.
 */
static inline void setDpEvtNOfGenEvtRep_4(CrPsNEvtRep_t nOfGenEvtRep_4) {
   dpEvtVars.nOfGenEvtRep_4 = nOfGenEvtRep_4;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSDPEVT_H */
