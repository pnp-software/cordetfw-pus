/**
 * @file
 * @ingroup gen_dp
 *
 * Interface for accessing data pool items.
 *
 * @note This file was generated on 2018-07-14 04:04:39
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSDPFCT_H_
#define CRPSDPFCT_H_

#include "CrPsTypes.h"
#include "CrPsConstants.h"
#include "CrFwUserConstants.h"
#include "CrFwConstants.h"


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
 * Get the value of the data pool item nOfAllocatedInCmd (Number of currently
 * allocated InCommands (i.e. successfully created by the InFactory and not
 * yet released))
 * @return The value of data pool item nOfAllocatedInCmd
 */
static inline CrPsNCmdRep_t getDpnOfAllocatedInCmd() {
   return dpFctVars.nOfAllocatedInCmd;
}

/**
 * Set the value of the data pool item nOfAllocatedInCmd (Number of currently
 * allocated InCommands (i.e. successfully created by the InFactory and not
 * yet released))
 * @param nOfAllocatedInCmd The value to be stored into the data pool item
 * nOfAllocatedInCmd.
 */
static inline void setDpnOfAllocatedInCmd(CrPsNCmdRep_t nOfAllocatedInCmd) {
   dpFctVars.nOfAllocatedInCmd = nOfAllocatedInCmd;
}

/**
 * Get the value of the data pool item nOfAllocatedInRep (Number of currently
 * allocated InReports (i.e. successfully created by the InFactory and not yet
 * released))
 * @return The value of data pool item nOfAllocatedInRep
 */
static inline CrPsNCmdRep_t getDpnOfAllocatedInRep() {
   return dpFctVars.nOfAllocatedInRep;
}

/**
 * Set the value of the data pool item nOfAllocatedInRep (Number of currently
 * allocated InReports (i.e. successfully created by the InFactory and not yet
 * released))
 * @param nOfAllocatedInRep The value to be stored into the data pool item
 * nOfAllocatedInRep.
 */
static inline void setDpnOfAllocatedInRep(CrPsNCmdRep_t nOfAllocatedInRep) {
   dpFctVars.nOfAllocatedInRep = nOfAllocatedInRep;
}

/**
 * Get the value of the data pool item nOfAllocatedOutCmp (Number of currently
 * allocated OutComponents (i.e. successfully created by the OutFactory and
 * not yet released))
 * @return The value of data pool item nOfAllocatedOutCmp
 */
static inline CrPsNCmdRep_t getDpnOfAllocatedOutCmp() {
   return dpFctVars.nOfAllocatedOutCmp;
}

/**
 * Set the value of the data pool item nOfAllocatedOutCmp (Number of currently
 * allocated OutComponents (i.e. successfully created by the OutFactory and
 * not yet released))
 * @param nOfAllocatedOutCmp The value to be stored into the data pool item
 * nOfAllocatedOutCmp.
 */
static inline void setDpnOfAllocatedOutCmp(CrPsNCmdRep_t nOfAllocatedOutCmp) {
   dpFctVars.nOfAllocatedOutCmp = nOfAllocatedOutCmp;
}

/**
 * Get the value of the data pool item nOfFailedInCmd (Number of InCommands
 * whose creation by the InFactory failed)
 * @return The value of data pool item nOfFailedInCmd
 */
static inline CrPsNCmdRep_t getDpnOfFailedInCmd() {
   return dpFctVars.nOfFailedInCmd;
}

/**
 * Set the value of the data pool item nOfFailedInCmd (Number of InCommands
 * whose creation by the InFactory failed)
 * @param nOfFailedInCmd The value to be stored into the data pool item
 * nOfFailedInCmd.
 */
static inline void setDpnOfFailedInCmd(CrPsNCmdRep_t nOfFailedInCmd) {
   dpFctVars.nOfFailedInCmd = nOfFailedInCmd;
}

/**
 * Get the value of the data pool item nOfFailedInRep (Number of InReports
 * whose creation by the InFactory failed)
 * @return The value of data pool item nOfFailedInRep
 */
static inline CrPsNCmdRep_t getDpnOfFailedInRep() {
   return dpFctVars.nOfFailedInRep;
}

/**
 * Set the value of the data pool item nOfFailedInRep (Number of InReports
 * whose creation by the InFactory failed)
 * @param nOfFailedInRep The value to be stored into the data pool item
 * nOfFailedInRep.
 */
static inline void setDpnOfFailedInRep(CrPsNCmdRep_t nOfFailedInRep) {
   dpFctVars.nOfFailedInRep = nOfFailedInRep;
}

/**
 * Get the value of the data pool item nOfFailedOutCmp (Number of
 * OutComponents whose creation by the OutFactory failed)
 * @return The value of data pool item nOfFailedOutCmp
 */
static inline CrPsNCmdRep_t getDpnOfFailedOutCmp() {
   return dpFctVars.nOfFailedOutCmp;
}

/**
 * Set the value of the data pool item nOfFailedOutCmp (Number of
 * OutComponents whose creation by the OutFactory failed)
 * @param nOfFailedOutCmp The value to be stored into the data pool item
 * nOfFailedOutCmp.
 */
static inline void setDpnOfFailedOutCmp(CrPsNCmdRep_t nOfFailedOutCmp) {
   dpFctVars.nOfFailedOutCmp = nOfFailedOutCmp;
}

/**
 * Get the value of the data pool item nOfTotAllocatedInCmd (Number of
 * InCommands successfully created by the InFactory since application start)
 * @return The value of data pool item nOfTotAllocatedInCmd
 */
static inline CrPsNCmdRep_t getDpnOfTotAllocatedInCmd() {
   return dpFctVars.nOfTotAllocatedInCmd;
}

/**
 * Set the value of the data pool item nOfTotAllocatedInCmd (Number of
 * InCommands successfully created by the InFactory since application start)
 * @param nOfTotAllocatedInCmd The value to be stored into the data pool item
 * nOfTotAllocatedInCmd.
 */
static inline void setDpnOfTotAllocatedInCmd(CrPsNCmdRep_t nOfTotAllocatedInCmd) {
   dpFctVars.nOfTotAllocatedInCmd = nOfTotAllocatedInCmd;
}

/**
 * Get the value of the data pool item nOfTotAllocatedInRep (Number of
 * InReports successfully created by the InFactory since application start)
 * @return The value of data pool item nOfTotAllocatedInRep
 */
static inline CrPsNCmdRep_t getDpnOfTotAllocatedInRep() {
   return dpFctVars.nOfTotAllocatedInRep;
}

/**
 * Set the value of the data pool item nOfTotAllocatedInRep (Number of
 * InReports successfully created by the InFactory since application start)
 * @param nOfTotAllocatedInRep The value to be stored into the data pool item
 * nOfTotAllocatedInRep.
 */
static inline void setDpnOfTotAllocatedInRep(CrPsNCmdRep_t nOfTotAllocatedInRep) {
   dpFctVars.nOfTotAllocatedInRep = nOfTotAllocatedInRep;
}

/**
 * Get the value of the data pool item nOfTotAllocatedOutCmp (Number of
 * OutComponents successfully created by the InFac- tory since application
 * start)
 * @return The value of data pool item nOfTotAllocatedOutCmp
 */
static inline CrPsNCmdRep_t getDpnOfTotAllocatedOutCmp() {
   return dpFctVars.nOfTotAllocatedOutCmp;
}

/**
 * Set the value of the data pool item nOfTotAllocatedOutCmp (Number of
 * OutComponents successfully created by the InFac- tory since application
 * start)
 * @param nOfTotAllocatedOutCmp The value to be stored into the data pool item
 * nOfTotAllocatedOutCmp.
 */
static inline void setDpnOfTotAllocatedOutCmp(CrPsNCmdRep_t nOfTotAllocatedOutCmp) {
   dpFctVars.nOfTotAllocatedOutCmp = nOfTotAllocatedOutCmp;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSDPFCT_H */
