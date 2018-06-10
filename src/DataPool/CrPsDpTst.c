/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2018-06-10 22:43:42
 * \author Automatically Generated by CORDET Editor
 * \copyright P&P Software GmbH
 */

#include "CrPsDpTst.h"

DpTstParams_t dpTstParams ;
DpTstVars_t dpTstVars ;

/**
 * Initialises Tst
 */
void initDpTst(void)
{
   static const CrFwDestSrc_t initOnBoardConnectDestLst[TST_N_DEST] = 0;

   dpTstParams.AreYouAliveTimeOut = 0;
   memcpy(dpTstParams.OnBoardConnectDestLst, initOnBoardConnectDestLst, sizeof(dpTstParams.OnBoardConnectDestLst));
   dpTstVars.AreYouAliveSrc = 0;
   dpTstVars.AreYouAliveStart = 0;
   dpTstVars.OnBoardConnectDest = 0;
}
