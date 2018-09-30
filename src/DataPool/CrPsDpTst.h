/**
 * @file
 * @ingroup gen_dp
 *
 * Interface for accessing data pool items.
 *
 * @note This file was generated on 2018-09-30 23:01:15
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSDPTST_H_
#define CRPSDPTST_H_

#include "CrPsTypes.h"
#include "CrPsConstants.h"
#include "CrFwUserConstants.h"
#include "CrFwConstants.h"


/**
 * Type description
 */
typedef struct {
   /**
    * Time-out for the Are-You-Alive Test initiated in response to an On-Board
    * Connection Test
    */
   CrFwTime_t AreYouAliveTimeOut;
   /**
    * Identifiers of target applications for an On-Board-Connection Test
    */
   CrFwDestSrc_t OnBoardConnectDestLst[TST_N_DEST];
} DpTstParams_t;

/**
 * Type description
 */
typedef struct {
   /**
    * Source of the latest (17,2) report received in response to a (17,1)
    * command triggered by a (17,3) command
    */
   CrFwDestSrc_t AreYouAliveSrc;
   /**
    * Time when the Are-You-Alive Test is started in response to an On-Board
    * Connection Test
    */
   CrFwTime_t AreYouAliveStart;
   /**
    * Destination of the (17,1) triggered by a (17,3) command
    */
   CrFwDestSrc_t OnBoardConnectDest;
} DpTstVars_t;

extern DpTstParams_t dpTstParams;
extern DpTstVars_t dpTstVars;

/**
 * Get the value of the data pool item AreYouAliveTimeOut (Time-out for the
 * Are-You-Alive Test initiated in response to an On-Board Connection Test)
 * @return The value of data pool item AreYouAliveTimeOut
 */
static inline CrFwTime_t getDpTstAreYouAliveTimeOut() {
   return dpTstParams.AreYouAliveTimeOut;
}

/**
 * Set the value of the data pool item AreYouAliveTimeOut (Time-out for the
 * Are-You-Alive Test initiated in response to an On-Board Connection Test)
 * @param AreYouAliveTimeOut The value to be stored into the data pool item
 * AreYouAliveTimeOut.
 */
static inline void setDpTstAreYouAliveTimeOut(CrFwTime_t AreYouAliveTimeOut) {
   dpTstParams.AreYouAliveTimeOut = AreYouAliveTimeOut;
}

/**
 * Get the data pool array OnBoardConnectDestLst (Identifiers of target
 * applications for an On-Board-Connection Test)
 * @return The data pool array OnBoardConnectDestLst
 */
static inline CrFwDestSrc_t* getDpTstOnBoardConnectDestLstArray() {
   return &dpTstParams.OnBoardConnectDestLst[0];
}

/**
 * Get the value of the i-th element in the data pool array
 * OnBoardConnectDestLst (Identifiers of target applications for an
 * On-Board-Connection Test)
 * @param i Index variable
 * @return The i-th element in the data pool array OnBoardConnectDestLst
 */
static inline CrFwDestSrc_t getDpTstOnBoardConnectDestLstItem(int i) {
   return dpTstParams.OnBoardConnectDestLst[i];
}

/**
 * Set the value of the i-th element in the data pool array
 * OnBoardConnectDestLst (Identifiers of target applications for an
 * On-Board-Connection Test)
 * @param i Index variable
 * @param OnBoardConnectDestLst The value to be stored into the i-th element
 * of data pool array OnBoardConnectDestLst.
 */
static inline void setDpTstOnBoardConnectDestLstItem(int i, CrFwDestSrc_t OnBoardConnectDestLst) {
   dpTstParams.OnBoardConnectDestLst[i] = OnBoardConnectDestLst;
}

/**
 * Get the value of the data pool item AreYouAliveSrc (Source of the latest
 * (17,2) report received in response to a (17,1) command triggered by a
 * (17,3) command)
 * @return The value of data pool item AreYouAliveSrc
 */
static inline CrFwDestSrc_t getDpTstAreYouAliveSrc() {
   return dpTstVars.AreYouAliveSrc;
}

/**
 * Set the value of the data pool item AreYouAliveSrc (Source of the latest
 * (17,2) report received in response to a (17,1) command triggered by a
 * (17,3) command)
 * @param AreYouAliveSrc The value to be stored into the data pool item
 * AreYouAliveSrc.
 */
static inline void setDpTstAreYouAliveSrc(CrFwDestSrc_t AreYouAliveSrc) {
   dpTstVars.AreYouAliveSrc = AreYouAliveSrc;
}

/**
 * Get the value of the data pool item AreYouAliveStart (Time when the
 * Are-You-Alive Test is started in response to an On-Board Connection Test)
 * @return The value of data pool item AreYouAliveStart
 */
static inline CrFwTime_t getDpTstAreYouAliveStart() {
   return dpTstVars.AreYouAliveStart;
}

/**
 * Set the value of the data pool item AreYouAliveStart (Time when the
 * Are-You-Alive Test is started in response to an On-Board Connection Test)
 * @param AreYouAliveStart The value to be stored into the data pool item
 * AreYouAliveStart.
 */
static inline void setDpTstAreYouAliveStart(CrFwTime_t AreYouAliveStart) {
   dpTstVars.AreYouAliveStart = AreYouAliveStart;
}

/**
 * Get the value of the data pool item OnBoardConnectDest (Destination of the
 * (17,1) triggered by a (17,3) command)
 * @return The value of data pool item OnBoardConnectDest
 */
static inline CrFwDestSrc_t getDpTstOnBoardConnectDest() {
   return dpTstVars.OnBoardConnectDest;
}

/**
 * Set the value of the data pool item OnBoardConnectDest (Destination of the
 * (17,1) triggered by a (17,3) command)
 * @param OnBoardConnectDest The value to be stored into the data pool item
 * OnBoardConnectDest.
 */
static inline void setDpTstOnBoardConnectDest(CrFwDestSrc_t OnBoardConnectDest) {
   dpTstVars.OnBoardConnectDest = OnBoardConnectDest;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSDPTST_H */
