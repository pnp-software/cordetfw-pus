/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2018-06-22 17:45:58
 * \author Automatically Generated by CORDET Editor
 * \copyright P&P Software GmbH
 */
#ifndef CRPSDPFCT_H_
#define CRPSDPFCT_H_

#include "CrPsDpTypes.h"
#include "CrPsConstants.h"

/**
 * Type description
 */
typedef struct {
   /**
    * Number of currently allocated InCommands (i.e. successfully created by
    * the InFactory and not yet released)
    */
   CrPsNCmdRep_t nOfAllocatedInCmd;
   /**
    * Number of currently allocated InReports (i.e. successfully created by
    * the InFactory and not yet released)
    */
   CrPsNCmdRep_t nOfAllocatedInRep;
   /**
    * Number of currently allocated OutComponents (i.e. successfully created
    * by the OutFactory and not yet released)
    */
   CrPsNCmdRep_t nOfAllocatedOutCmp;
   /**
    * Number of InCommands whose creation by the InFactory failed
    */
   CrPsNCmdRep_t nOfFailedInCmd;
   /**
    * Number of InReports whose creation by the InFactory failed
    */
   CrPsNCmdRep_t nOfFailedInRep;
   /**
    * Number of OutComponents whose creation by the OutFactory failed
    */
   CrPsNCmdRep_t nOfFailedOutCmp;
   /**
    * Number of InCommands successfully created by the InFactory since
    * application start
    */
   CrPsNCmdRep_t nOfTotAllocatedInCmd;
   /**
    * Number of InReports successfully created by the InFactory since
    * application start
    */
   CrPsNCmdRep_t nOfTotAllocatedInRep;
   /**
    * Number of OutComponents successfully created by the InFac- tory since
    * application start
    */
   CrPsNCmdRep_t nOfTotAllocatedOutCmp;
} DpFctVars_t;

extern DpFctVars_t dpFctVars;

/**
 * Initialises Fct
 */
void initDpFct(void);

/**
 * Gets the value of the datapool item nOfAllocatedInCmd
 * \return The value of datapool item nOfAllocatedInCmd
 */
static inline CrPsNCmdRep_t getDpnOfAllocatedInCmd()
{
   return dpFctVars.nOfAllocatedInCmd;
}

/**
 * Sets the value of the datapool item nOfAllocatedInCmd
 * \param nOfAllocatedInCmd The value to be stored into the datapool item
 * nOfAllocatedInCmd.
 */
static inline void setDpnOfAllocatedInCmd(CrPsNCmdRep_t nOfAllocatedInCmd)
{
   dpFctVars.nOfAllocatedInCmd = nOfAllocatedInCmd;
}

/**
 * Gets the value of the datapool item nOfAllocatedInRep
 * \return The value of datapool item nOfAllocatedInRep
 */
static inline CrPsNCmdRep_t getDpnOfAllocatedInRep()
{
   return dpFctVars.nOfAllocatedInRep;
}

/**
 * Sets the value of the datapool item nOfAllocatedInRep
 * \param nOfAllocatedInRep The value to be stored into the datapool item
 * nOfAllocatedInRep.
 */
static inline void setDpnOfAllocatedInRep(CrPsNCmdRep_t nOfAllocatedInRep)
{
   dpFctVars.nOfAllocatedInRep = nOfAllocatedInRep;
}

/**
 * Gets the value of the datapool item nOfAllocatedOutCmp
 * \return The value of datapool item nOfAllocatedOutCmp
 */
static inline CrPsNCmdRep_t getDpnOfAllocatedOutCmp()
{
   return dpFctVars.nOfAllocatedOutCmp;
}

/**
 * Sets the value of the datapool item nOfAllocatedOutCmp
 * \param nOfAllocatedOutCmp The value to be stored into the datapool item
 * nOfAllocatedOutCmp.
 */
static inline void setDpnOfAllocatedOutCmp(CrPsNCmdRep_t nOfAllocatedOutCmp)
{
   dpFctVars.nOfAllocatedOutCmp = nOfAllocatedOutCmp;
}

/**
 * Gets the value of the datapool item nOfFailedInCmd
 * \return The value of datapool item nOfFailedInCmd
 */
static inline CrPsNCmdRep_t getDpnOfFailedInCmd()
{
   return dpFctVars.nOfFailedInCmd;
}

/**
 * Sets the value of the datapool item nOfFailedInCmd
 * \param nOfFailedInCmd The value to be stored into the datapool item
 * nOfFailedInCmd.
 */
static inline void setDpnOfFailedInCmd(CrPsNCmdRep_t nOfFailedInCmd)
{
   dpFctVars.nOfFailedInCmd = nOfFailedInCmd;
}

/**
 * Gets the value of the datapool item nOfFailedInRep
 * \return The value of datapool item nOfFailedInRep
 */
static inline CrPsNCmdRep_t getDpnOfFailedInRep()
{
   return dpFctVars.nOfFailedInRep;
}

/**
 * Sets the value of the datapool item nOfFailedInRep
 * \param nOfFailedInRep The value to be stored into the datapool item
 * nOfFailedInRep.
 */
static inline void setDpnOfFailedInRep(CrPsNCmdRep_t nOfFailedInRep)
{
   dpFctVars.nOfFailedInRep = nOfFailedInRep;
}

/**
 * Gets the value of the datapool item nOfFailedOutCmp
 * \return The value of datapool item nOfFailedOutCmp
 */
static inline CrPsNCmdRep_t getDpnOfFailedOutCmp()
{
   return dpFctVars.nOfFailedOutCmp;
}

/**
 * Sets the value of the datapool item nOfFailedOutCmp
 * \param nOfFailedOutCmp The value to be stored into the datapool item
 * nOfFailedOutCmp.
 */
static inline void setDpnOfFailedOutCmp(CrPsNCmdRep_t nOfFailedOutCmp)
{
   dpFctVars.nOfFailedOutCmp = nOfFailedOutCmp;
}

/**
 * Gets the value of the datapool item nOfTotAllocatedInCmd
 * \return The value of datapool item nOfTotAllocatedInCmd
 */
static inline CrPsNCmdRep_t getDpnOfTotAllocatedInCmd()
{
   return dpFctVars.nOfTotAllocatedInCmd;
}

/**
 * Sets the value of the datapool item nOfTotAllocatedInCmd
 * \param nOfTotAllocatedInCmd The value to be stored into the datapool item
 * nOfTotAllocatedInCmd.
 */
static inline void setDpnOfTotAllocatedInCmd(CrPsNCmdRep_t nOfTotAllocatedInCmd)
{
   dpFctVars.nOfTotAllocatedInCmd = nOfTotAllocatedInCmd;
}

/**
 * Gets the value of the datapool item nOfTotAllocatedInRep
 * \return The value of datapool item nOfTotAllocatedInRep
 */
static inline CrPsNCmdRep_t getDpnOfTotAllocatedInRep()
{
   return dpFctVars.nOfTotAllocatedInRep;
}

/**
 * Sets the value of the datapool item nOfTotAllocatedInRep
 * \param nOfTotAllocatedInRep The value to be stored into the datapool item
 * nOfTotAllocatedInRep.
 */
static inline void setDpnOfTotAllocatedInRep(CrPsNCmdRep_t nOfTotAllocatedInRep)
{
   dpFctVars.nOfTotAllocatedInRep = nOfTotAllocatedInRep;
}

/**
 * Gets the value of the datapool item nOfTotAllocatedOutCmp
 * \return The value of datapool item nOfTotAllocatedOutCmp
 */
static inline CrPsNCmdRep_t getDpnOfTotAllocatedOutCmp()
{
   return dpFctVars.nOfTotAllocatedOutCmp;
}

/**
 * Sets the value of the datapool item nOfTotAllocatedOutCmp
 * \param nOfTotAllocatedOutCmp The value to be stored into the datapool item
 * nOfTotAllocatedOutCmp.
 */
static inline void setDpnOfTotAllocatedOutCmp(CrPsNCmdRep_t nOfTotAllocatedOutCmp)
{
   dpFctVars.nOfTotAllocatedOutCmp = nOfTotAllocatedOutCmp;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSDPFCT_H */