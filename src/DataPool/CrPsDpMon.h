/**
 * @file
 * @ingroup gen_dp
 *
 * Interface for accessing data pool items.
 *
 * @note This file was generated on 2018-09-29 16:05:17
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSDPMON_H_
#define CRPSDPMON_H_

#include "CrPsTypes.h"
#include "CrPsConstants.h"
#include "CrFwUserConstants.h"
#include "CrFwConstants.h"


/**
 * Type description
 */
typedef struct {
   /**
    * Maximum reporting delay
    */
   CrPsRepDelay_t maxRepDelay;
   /**
    * The default user of the service is the ground.
    */
   CrFwDestSrc_t servUser;
} DpMonParams_t;

/**
 * Type description
 */
typedef struct {
   /**
    * Maximum reporting delay for the CTL in multiples of MON_PER
    */
   CrPsRepDelay_t ctlRepDelay;
   /**
    * Time when first entry has been added to the CTL
    */
   CrFwTimeStamp_t ctlTimeFirstEntry;
   /**
    * Functional monitoring enable status
    */
   CrPsEnDis_t funcMonEnbStatus;
   /**
    * Number of available functional monitors in the FMDL
    */
   CrPsFuncMonId_t nmbAvailFuncMon;
   /**
    * Number of available parameter monitors in the PMDL
    */
   CrPsParMonId_t nmbAvailParMon;
   /**
    * Number of enabled functional monitors in the FMDL
    */
   CrPsFuncMonId_t nmbEnbFuncMon;
   /**
    * Number of enabled parameter monitors in the PMDL
    */
   CrPsParMonId_t nmbEnbParMon;
   /**
    * Enable state of parameter monitoring function
    */
   CrPsEnDis_t parMonEnbStatus;
} DpMonVars_t;

extern DpMonParams_t dpMonParams;
extern DpMonVars_t dpMonVars;

/**
 * Get the value of the data pool item maxRepDelay (Maximum reporting delay)
 * @return The value of data pool item maxRepDelay
 */
static inline CrPsRepDelay_t getDpMonMaxRepDelay() {
   return dpMonParams.maxRepDelay;
}

/**
 * Set the value of the data pool item maxRepDelay (Maximum reporting delay)
 * @param maxRepDelay The value to be stored into the data pool item
 * maxRepDelay.
 */
static inline void setDpMonMaxRepDelay(CrPsRepDelay_t maxRepDelay) {
   dpMonParams.maxRepDelay = maxRepDelay;
}

/**
 * Get the value of the data pool item servUser (The default user of the
 * service is the ground.)
 * @return The value of data pool item servUser
 */
static inline CrFwDestSrc_t getDpMonServUser() {
   return dpMonParams.servUser;
}

/**
 * Set the value of the data pool item servUser (The default user of the
 * service is the ground.)
 * @param servUser The value to be stored into the data pool item servUser.
 */
static inline void setDpMonServUser(CrFwDestSrc_t servUser) {
   dpMonParams.servUser = servUser;
}

/**
 * Get the value of the data pool item ctlRepDelay (Maximum reporting delay
 * for the CTL in multiples of MON_PER)
 * @return The value of data pool item ctlRepDelay
 */
static inline CrPsRepDelay_t getDpMonCtlRepDelay() {
   return dpMonVars.ctlRepDelay;
}

/**
 * Set the value of the data pool item ctlRepDelay (Maximum reporting delay
 * for the CTL in multiples of MON_PER)
 * @param ctlRepDelay The value to be stored into the data pool item
 * ctlRepDelay.
 */
static inline void setDpMonCtlRepDelay(CrPsRepDelay_t ctlRepDelay) {
   dpMonVars.ctlRepDelay = ctlRepDelay;
}

/**
 * Get the value of the data pool item ctlTimeFirstEntry (Time when first
 * entry has been added to the CTL)
 * @return The value of data pool item ctlTimeFirstEntry
 */
static inline CrFwTimeStamp_t getDpMonCtlTimeFirstEntry() {
   return dpMonVars.ctlTimeFirstEntry;
}

/**
 * Set the value of the data pool item ctlTimeFirstEntry (Time when first
 * entry has been added to the CTL)
 * @param ctlTimeFirstEntry The value to be stored into the data pool item
 * ctlTimeFirstEntry.
 */
static inline void setDpMonCtlTimeFirstEntry(CrFwTimeStamp_t ctlTimeFirstEntry) {
   dpMonVars.ctlTimeFirstEntry = ctlTimeFirstEntry;
}

/**
 * Get the value of the data pool item funcMonEnbStatus (Functional monitoring
 * enable status)
 * @return The value of data pool item funcMonEnbStatus
 */
static inline CrPsEnDis_t getDpMonFuncMonEnbStatus() {
   return dpMonVars.funcMonEnbStatus;
}

/**
 * Set the value of the data pool item funcMonEnbStatus (Functional monitoring
 * enable status)
 * @param funcMonEnbStatus The value to be stored into the data pool item
 * funcMonEnbStatus.
 */
static inline void setDpMonFuncMonEnbStatus(CrPsEnDis_t funcMonEnbStatus) {
   dpMonVars.funcMonEnbStatus = funcMonEnbStatus;
}

/**
 * Get the value of the data pool item nmbAvailFuncMon (Number of available
 * functional monitors in the FMDL)
 * @return The value of data pool item nmbAvailFuncMon
 */
static inline CrPsFuncMonId_t getDpMonNmbAvailFuncMon() {
   return dpMonVars.nmbAvailFuncMon;
}

/**
 * Set the value of the data pool item nmbAvailFuncMon (Number of available
 * functional monitors in the FMDL)
 * @param nmbAvailFuncMon The value to be stored into the data pool item
 * nmbAvailFuncMon.
 */
static inline void setDpMonNmbAvailFuncMon(CrPsFuncMonId_t nmbAvailFuncMon) {
   dpMonVars.nmbAvailFuncMon = nmbAvailFuncMon;
}

/**
 * Get the value of the data pool item nmbAvailParMon (Number of available
 * parameter monitors in the PMDL)
 * @return The value of data pool item nmbAvailParMon
 */
static inline CrPsParMonId_t getDpMonNmbAvailParMon() {
   return dpMonVars.nmbAvailParMon;
}

/**
 * Set the value of the data pool item nmbAvailParMon (Number of available
 * parameter monitors in the PMDL)
 * @param nmbAvailParMon The value to be stored into the data pool item
 * nmbAvailParMon.
 */
static inline void setDpMonNmbAvailParMon(CrPsParMonId_t nmbAvailParMon) {
   dpMonVars.nmbAvailParMon = nmbAvailParMon;
}

/**
 * Get the value of the data pool item nmbEnbFuncMon (Number of enabled
 * functional monitors in the FMDL)
 * @return The value of data pool item nmbEnbFuncMon
 */
static inline CrPsFuncMonId_t getDpMonNmbEnbFuncMon() {
   return dpMonVars.nmbEnbFuncMon;
}

/**
 * Set the value of the data pool item nmbEnbFuncMon (Number of enabled
 * functional monitors in the FMDL)
 * @param nmbEnbFuncMon The value to be stored into the data pool item
 * nmbEnbFuncMon.
 */
static inline void setDpMonNmbEnbFuncMon(CrPsFuncMonId_t nmbEnbFuncMon) {
   dpMonVars.nmbEnbFuncMon = nmbEnbFuncMon;
}

/**
 * Get the value of the data pool item nmbEnbParMon (Number of enabled
 * parameter monitors in the PMDL)
 * @return The value of data pool item nmbEnbParMon
 */
static inline CrPsParMonId_t getDpMonNmbEnbParMon() {
   return dpMonVars.nmbEnbParMon;
}

/**
 * Set the value of the data pool item nmbEnbParMon (Number of enabled
 * parameter monitors in the PMDL)
 * @param nmbEnbParMon The value to be stored into the data pool item
 * nmbEnbParMon.
 */
static inline void setDpMonNmbEnbParMon(CrPsParMonId_t nmbEnbParMon) {
   dpMonVars.nmbEnbParMon = nmbEnbParMon;
}

/**
 * Get the value of the data pool item parMonEnbStatus (Enable state of
 * parameter monitoring function)
 * @return The value of data pool item parMonEnbStatus
 */
static inline CrPsEnDis_t getDpMonParMonEnbStatus() {
   return dpMonVars.parMonEnbStatus;
}

/**
 * Set the value of the data pool item parMonEnbStatus (Enable state of
 * parameter monitoring function)
 * @param parMonEnbStatus The value to be stored into the data pool item
 * parMonEnbStatus.
 */
static inline void setDpMonParMonEnbStatus(CrPsEnDis_t parMonEnbStatus) {
   dpMonVars.parMonEnbStatus = parMonEnbStatus;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSDPMON_H */
