/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2018-06-22 17:45:58
 * \author Automatically Generated by CORDET Editor
 * \copyright P&P Software GmbH
 */
#ifndef CRPSDPLPT_H_
#define CRPSDPLPT_H_

#include "CrPsTypes.h"
#include "CrPsConstants.h"

/**
 * Type description
 */
typedef struct {
   /**
    * Destination of transfer from LPT Buffer
    */
   CrFwDestSrc_t lptDest[LPT_N_BUF];
   /**
    * Time-out for up-tramsfer to LPT Buffer
    */
   CrPsTimeSec_t lptTimeOut[LPT_N_BUF];
   /**
    * Part size for transfers to/from LPT Buffer
    */
   CrPsSize_t partSize[LPT_N_BUF];
} DpLptParams_t;

/**
 * Type description
 */
typedef struct {
   /**
    * Remaining size of a large packet in the LPT Buffer (part of the large
    * packet not yet down-transferred)
    */
   CrPsSize_t lptRemSize[LPT_N_BUF];
   /**
    * Size of large packet in the LPT Buffer
    */
   CrPsSize_t lptSize[LPT_N_BUF];
   /**
    * Source of the large packet up-transfer to the LPT Buffer
    */
   CrFwDestSrc_t lptSrc[LPT_N_BUF];
   /**
    * Time when last up-transfer command to the LPT Buffer was received
    */
   CrPsTimeSec_t lptTime[LPT_N_BUF];
   /**
    * Number of on-going down-transfers
    */
   CrPsNOfLinks_t nOfDownlinks;
   /**
    * Number of on-going up-transfers
    */
   CrPsNOfLinks_t nOfUplinks;
   /**
    * Part sequence number for the up/down/transfer to/from the LPT Buffer
    */
   CrPsPartSeqNmb_t partSeqNmb[LPT_N_BUF];
} DpLptVars_t;

extern DpLptParams_t dpLptParams;
extern DpLptVars_t dpLptVars;

/**
 * Initialises Lpt
 */
void initDpLpt(void);

/**
 * Gets the datapool array lptDest
 * \return The datapool array lptDest
 */
static inline CrFwDestSrc_t* getDplptDestArray()
{
   return &dpLptParams.lptDest[0];
}

/**
 * Gets the value of the i-th element in the datapool array lptDest
 * \param i Index variable
 * \return The i-th element in the datapool array lptDest
 */
static inline CrFwDestSrc_t getDplptDestItem(int i)
{
   return dpLptParams.lptDest[i];
}

/**
 * Sets the value of the i-th element in the datapool array lptDest
 * \param i Index variable
 * \param lptDest The value to be stored into the i-th element of datapool
 * array lptDest.
 */
static inline void setDplptDestItem(int i, CrFwDestSrc_t lptDest)
{
   dpLptParams.lptDest[i] = lptDest;
}

/**
 * Gets the datapool array lptTimeOut
 * \return The datapool array lptTimeOut
 */
static inline CrPsTimeSec_t* getDplptTimeOutArray()
{
   return &dpLptParams.lptTimeOut[0];
}

/**
 * Gets the value of the i-th element in the datapool array lptTimeOut
 * \param i Index variable
 * \return The i-th element in the datapool array lptTimeOut
 */
static inline CrPsTimeSec_t getDplptTimeOutItem(int i)
{
   return dpLptParams.lptTimeOut[i];
}

/**
 * Sets the value of the i-th element in the datapool array lptTimeOut
 * \param i Index variable
 * \param lptTimeOut The value to be stored into the i-th element of datapool
 * array lptTimeOut.
 */
static inline void setDplptTimeOutItem(int i, CrPsTimeSec_t lptTimeOut)
{
   dpLptParams.lptTimeOut[i] = lptTimeOut;
}

/**
 * Gets the datapool array partSize
 * \return The datapool array partSize
 */
static inline CrPsSize_t* getDppartSizeArray()
{
   return &dpLptParams.partSize[0];
}

/**
 * Gets the value of the i-th element in the datapool array partSize
 * \param i Index variable
 * \return The i-th element in the datapool array partSize
 */
static inline CrPsSize_t getDppartSizeItem(int i)
{
   return dpLptParams.partSize[i];
}

/**
 * Sets the value of the i-th element in the datapool array partSize
 * \param i Index variable
 * \param partSize The value to be stored into the i-th element of datapool
 * array partSize.
 */
static inline void setDppartSizeItem(int i, CrPsSize_t partSize)
{
   dpLptParams.partSize[i] = partSize;
}

/**
 * Gets the datapool array lptRemSize
 * \return The datapool array lptRemSize
 */
static inline CrPsSize_t* getDplptRemSizeArray()
{
   return &dpLptVars.lptRemSize[0];
}

/**
 * Gets the value of the i-th element in the datapool array lptRemSize
 * \param i Index variable
 * \return The i-th element in the datapool array lptRemSize
 */
static inline CrPsSize_t getDplptRemSizeItem(int i)
{
   return dpLptVars.lptRemSize[i];
}

/**
 * Sets the value of the i-th element in the datapool array lptRemSize
 * \param i Index variable
 * \param lptRemSize The value to be stored into the i-th element of datapool
 * array lptRemSize.
 */
static inline void setDplptRemSizeItem(int i, CrPsSize_t lptRemSize)
{
   dpLptVars.lptRemSize[i] = lptRemSize;
}

/**
 * Gets the datapool array lptSize
 * \return The datapool array lptSize
 */
static inline CrPsSize_t* getDplptSizeArray()
{
   return &dpLptVars.lptSize[0];
}

/**
 * Gets the value of the i-th element in the datapool array lptSize
 * \param i Index variable
 * \return The i-th element in the datapool array lptSize
 */
static inline CrPsSize_t getDplptSizeItem(int i)
{
   return dpLptVars.lptSize[i];
}

/**
 * Sets the value of the i-th element in the datapool array lptSize
 * \param i Index variable
 * \param lptSize The value to be stored into the i-th element of datapool
 * array lptSize.
 */
static inline void setDplptSizeItem(int i, CrPsSize_t lptSize)
{
   dpLptVars.lptSize[i] = lptSize;
}

/**
 * Gets the datapool array lptSrc
 * \return The datapool array lptSrc
 */
static inline CrFwDestSrc_t* getDplptSrcArray()
{
   return &dpLptVars.lptSrc[0];
}

/**
 * Gets the value of the i-th element in the datapool array lptSrc
 * \param i Index variable
 * \return The i-th element in the datapool array lptSrc
 */
static inline CrFwDestSrc_t getDplptSrcItem(int i)
{
   return dpLptVars.lptSrc[i];
}

/**
 * Sets the value of the i-th element in the datapool array lptSrc
 * \param i Index variable
 * \param lptSrc The value to be stored into the i-th element of datapool
 * array lptSrc.
 */
static inline void setDplptSrcItem(int i, CrFwDestSrc_t lptSrc)
{
   dpLptVars.lptSrc[i] = lptSrc;
}

/**
 * Gets the datapool array lptTime
 * \return The datapool array lptTime
 */
static inline CrPsTimeSec_t* getDplptTimeArray()
{
   return &dpLptVars.lptTime[0];
}

/**
 * Gets the value of the i-th element in the datapool array lptTime
 * \param i Index variable
 * \return The i-th element in the datapool array lptTime
 */
static inline CrPsTimeSec_t getDplptTimeItem(int i)
{
   return dpLptVars.lptTime[i];
}

/**
 * Sets the value of the i-th element in the datapool array lptTime
 * \param i Index variable
 * \param lptTime The value to be stored into the i-th element of datapool
 * array lptTime.
 */
static inline void setDplptTimeItem(int i, CrPsTimeSec_t lptTime)
{
   dpLptVars.lptTime[i] = lptTime;
}

/**
 * Gets the value of the datapool item nOfDownlinks
 * \return The value of datapool item nOfDownlinks
 */
static inline CrPsNOfLinks_t getDpnOfDownlinks()
{
   return dpLptVars.nOfDownlinks;
}

/**
 * Sets the value of the datapool item nOfDownlinks
 * \param nOfDownlinks The value to be stored into the datapool item
 * nOfDownlinks.
 */
static inline void setDpnOfDownlinks(CrPsNOfLinks_t nOfDownlinks)
{
   dpLptVars.nOfDownlinks = nOfDownlinks;
}

/**
 * Gets the value of the datapool item nOfUplinks
 * \return The value of datapool item nOfUplinks
 */
static inline CrPsNOfLinks_t getDpnOfUplinks()
{
   return dpLptVars.nOfUplinks;
}

/**
 * Sets the value of the datapool item nOfUplinks
 * \param nOfUplinks The value to be stored into the datapool item nOfUplinks.
 */
static inline void setDpnOfUplinks(CrPsNOfLinks_t nOfUplinks)
{
   dpLptVars.nOfUplinks = nOfUplinks;
}

/**
 * Gets the datapool array partSeqNmb
 * \return The datapool array partSeqNmb
 */
static inline CrPsPartSeqNmb_t* getDppartSeqNmbArray()
{
   return &dpLptVars.partSeqNmb[0];
}

/**
 * Gets the value of the i-th element in the datapool array partSeqNmb
 * \param i Index variable
 * \return The i-th element in the datapool array partSeqNmb
 */
static inline CrPsPartSeqNmb_t getDppartSeqNmbItem(int i)
{
   return dpLptVars.partSeqNmb[i];
}

/**
 * Sets the value of the i-th element in the datapool array partSeqNmb
 * \param i Index variable
 * \param partSeqNmb The value to be stored into the i-th element of datapool
 * array partSeqNmb.
 */
static inline void setDppartSeqNmbItem(int i, CrPsPartSeqNmb_t partSeqNmb)
{
   dpLptVars.partSeqNmb[i] = partSeqNmb;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSDPLPT_H */
