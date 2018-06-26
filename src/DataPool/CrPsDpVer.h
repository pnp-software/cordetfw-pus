/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2018-06-22 17:45:58
 * \author Automatically Generated by CORDET Editor
 * \copyright P&P Software GmbH
 */
#ifndef CRPSDPVER_H_
#define CRPSDPVER_H_

#include "CrPsTypes.h"
#include "CrPsConstants.h"

/**
 * Type description
 */
typedef struct {
   /**
    * Failure code of last command which failed its Acceptance
    */
   CrPsFailCode_t failCodeAccFailed;
   /**
    * Failure code of last command which failed its Progress Check
    */
   CrPsFailCode_t failCodePrgrFailed;
   /**
    * Failure code of last command which failed its Start Check
    */
   CrPsFailCode_t failCodeStartFailed;
   /**
    * Failure code of last command which failed its Termination
    */
   CrPsFailCode_t failCodeTermFailed;
   /**
    * Destination of last command for which re-routing failed
    */
   CrFwDestSrc_t invDestRerouting;
   /**
    * Number of commands which have failed their acceptance check
    */
   CrPsNOfCmd_t nOfAccFailed;
   /**
    * Number of commands which have failed their Progress Check
    */
   CrPsNOfCmd_t nOfPrgrFailed;
   /**
    * Number of commands for which re-routing failed
    */
   CrPsNOfCmd_t nOfReroutingFailed;
   /**
    * Number of commands which have failed their Start Check since
    */
   CrPsNOfCmd_t nOfStartFailed;
   /**
    * Number of commands which have failed their Termination
    */
   CrPsNOfCmd_t nOfTermFailed;
   /**
    * Packet identifier of last command which failed its Acceptance
    */
   CrPsThirteenBit_t pcktIdAccFailed;
   /**
    * Packet identifier of last command which failed its Progress
    */
   CrPsThirteenBit_t pcktIdPrgrFailed;
   /**
    * Packet identifier of last command for which re-routing failed
    */
   CrPsThirteenBit_t pcktIdReroutingFailed;
   /**
    * Packet identifier of last command which failed its Start Check
    */
   CrPsThirteenBit_t pcktIdStartFailed;
   /**
    * Packet identifier of last command which failed its Termination
    */
   CrPsThirteenBit_t pcktIdTermFailed;
   /**
    * Step identifier of last command which failed its Progress Check
    */
   CrPsPrgStep_t stepPrgrFailed;
   /**
    * Verification Failure Code
    */
   CrPsFailCode_t verFailCode;
   /**
    * Verification Failure Data (data item of fixed size but variable meaning)
    */
   CrPsFailData_t verFailData;
} DpVerVars_t;

extern DpVerVars_t dpVerVars;

/**
 * Initialises Ver
 */
void initDpVer(void);

/**
 * Gets the value of the datapool item failCodeAccFailed
 * \return The value of datapool item failCodeAccFailed
 */
static inline CrPsFailCode_t getDpfailCodeAccFailed()
{
   return dpVerVars.failCodeAccFailed;
}

/**
 * Sets the value of the datapool item failCodeAccFailed
 * \param failCodeAccFailed The value to be stored into the datapool item
 * failCodeAccFailed.
 */
static inline void setDpfailCodeAccFailed(CrPsFailCode_t failCodeAccFailed)
{
   dpVerVars.failCodeAccFailed = failCodeAccFailed;
}

/**
 * Gets the value of the datapool item failCodePrgrFailed
 * \return The value of datapool item failCodePrgrFailed
 */
static inline CrPsFailCode_t getDpfailCodePrgrFailed()
{
   return dpVerVars.failCodePrgrFailed;
}

/**
 * Sets the value of the datapool item failCodePrgrFailed
 * \param failCodePrgrFailed The value to be stored into the datapool item
 * failCodePrgrFailed.
 */
static inline void setDpfailCodePrgrFailed(CrPsFailCode_t failCodePrgrFailed)
{
   dpVerVars.failCodePrgrFailed = failCodePrgrFailed;
}

/**
 * Gets the value of the datapool item failCodeStartFailed
 * \return The value of datapool item failCodeStartFailed
 */
static inline CrPsFailCode_t getDpfailCodeStartFailed()
{
   return dpVerVars.failCodeStartFailed;
}

/**
 * Sets the value of the datapool item failCodeStartFailed
 * \param failCodeStartFailed The value to be stored into the datapool item
 * failCodeStartFailed.
 */
static inline void setDpfailCodeStartFailed(CrPsFailCode_t failCodeStartFailed)
{
   dpVerVars.failCodeStartFailed = failCodeStartFailed;
}

/**
 * Gets the value of the datapool item failCodeTermFailed
 * \return The value of datapool item failCodeTermFailed
 */
static inline CrPsFailCode_t getDpfailCodeTermFailed()
{
   return dpVerVars.failCodeTermFailed;
}

/**
 * Sets the value of the datapool item failCodeTermFailed
 * \param failCodeTermFailed The value to be stored into the datapool item
 * failCodeTermFailed.
 */
static inline void setDpfailCodeTermFailed(CrPsFailCode_t failCodeTermFailed)
{
   dpVerVars.failCodeTermFailed = failCodeTermFailed;
}

/**
 * Gets the value of the datapool item invDestRerouting
 * \return The value of datapool item invDestRerouting
 */
static inline CrFwDestSrc_t getDpinvDestRerouting()
{
   return dpVerVars.invDestRerouting;
}

/**
 * Sets the value of the datapool item invDestRerouting
 * \param invDestRerouting The value to be stored into the datapool item
 * invDestRerouting.
 */
static inline void setDpinvDestRerouting(CrFwDestSrc_t invDestRerouting)
{
   dpVerVars.invDestRerouting = invDestRerouting;
}

/**
 * Gets the value of the datapool item nOfAccFailed
 * \return The value of datapool item nOfAccFailed
 */
static inline CrPsNOfCmd_t getDpnOfAccFailed()
{
   return dpVerVars.nOfAccFailed;
}

/**
 * Sets the value of the datapool item nOfAccFailed
 * \param nOfAccFailed The value to be stored into the datapool item
 * nOfAccFailed.
 */
static inline void setDpnOfAccFailed(CrPsNOfCmd_t nOfAccFailed)
{
   dpVerVars.nOfAccFailed = nOfAccFailed;
}

/**
 * Gets the value of the datapool item nOfPrgrFailed
 * \return The value of datapool item nOfPrgrFailed
 */
static inline CrPsNOfCmd_t getDpnOfPrgrFailed()
{
   return dpVerVars.nOfPrgrFailed;
}

/**
 * Sets the value of the datapool item nOfPrgrFailed
 * \param nOfPrgrFailed The value to be stored into the datapool item
 * nOfPrgrFailed.
 */
static inline void setDpnOfPrgrFailed(CrPsNOfCmd_t nOfPrgrFailed)
{
   dpVerVars.nOfPrgrFailed = nOfPrgrFailed;
}

/**
 * Gets the value of the datapool item nOfReroutingFailed
 * \return The value of datapool item nOfReroutingFailed
 */
static inline CrPsNOfCmd_t getDpnOfReroutingFailed()
{
   return dpVerVars.nOfReroutingFailed;
}

/**
 * Sets the value of the datapool item nOfReroutingFailed
 * \param nOfReroutingFailed The value to be stored into the datapool item
 * nOfReroutingFailed.
 */
static inline void setDpnOfReroutingFailed(CrPsNOfCmd_t nOfReroutingFailed)
{
   dpVerVars.nOfReroutingFailed = nOfReroutingFailed;
}

/**
 * Gets the value of the datapool item nOfStartFailed
 * \return The value of datapool item nOfStartFailed
 */
static inline CrPsNOfCmd_t getDpnOfStartFailed()
{
   return dpVerVars.nOfStartFailed;
}

/**
 * Sets the value of the datapool item nOfStartFailed
 * \param nOfStartFailed The value to be stored into the datapool item
 * nOfStartFailed.
 */
static inline void setDpnOfStartFailed(CrPsNOfCmd_t nOfStartFailed)
{
   dpVerVars.nOfStartFailed = nOfStartFailed;
}

/**
 * Gets the value of the datapool item nOfTermFailed
 * \return The value of datapool item nOfTermFailed
 */
static inline CrPsNOfCmd_t getDpnOfTermFailed()
{
   return dpVerVars.nOfTermFailed;
}

/**
 * Sets the value of the datapool item nOfTermFailed
 * \param nOfTermFailed The value to be stored into the datapool item
 * nOfTermFailed.
 */
static inline void setDpnOfTermFailed(CrPsNOfCmd_t nOfTermFailed)
{
   dpVerVars.nOfTermFailed = nOfTermFailed;
}

/**
 * Gets the value of the datapool item pcktIdAccFailed
 * \return The value of datapool item pcktIdAccFailed
 */
static inline CrPsThirteenBit_t getDppcktIdAccFailed()
{
   return dpVerVars.pcktIdAccFailed;
}

/**
 * Sets the value of the datapool item pcktIdAccFailed
 * \param pcktIdAccFailed The value to be stored into the datapool item
 * pcktIdAccFailed.
 */
static inline void setDppcktIdAccFailed(CrPsThirteenBit_t pcktIdAccFailed)
{
   dpVerVars.pcktIdAccFailed = pcktIdAccFailed;
}

/**
 * Gets the value of the datapool item pcktIdPrgrFailed
 * \return The value of datapool item pcktIdPrgrFailed
 */
static inline CrPsThirteenBit_t getDppcktIdPrgrFailed()
{
   return dpVerVars.pcktIdPrgrFailed;
}

/**
 * Sets the value of the datapool item pcktIdPrgrFailed
 * \param pcktIdPrgrFailed The value to be stored into the datapool item
 * pcktIdPrgrFailed.
 */
static inline void setDppcktIdPrgrFailed(CrPsThirteenBit_t pcktIdPrgrFailed)
{
   dpVerVars.pcktIdPrgrFailed = pcktIdPrgrFailed;
}

/**
 * Gets the value of the datapool item pcktIdReroutingFailed
 * \return The value of datapool item pcktIdReroutingFailed
 */
static inline CrPsThirteenBit_t getDppcktIdReroutingFailed()
{
   return dpVerVars.pcktIdReroutingFailed;
}

/**
 * Sets the value of the datapool item pcktIdReroutingFailed
 * \param pcktIdReroutingFailed The value to be stored into the datapool item
 * pcktIdReroutingFailed.
 */
static inline void setDppcktIdReroutingFailed(CrPsThirteenBit_t pcktIdReroutingFailed)
{
   dpVerVars.pcktIdReroutingFailed = pcktIdReroutingFailed;
}

/**
 * Gets the value of the datapool item pcktIdStartFailed
 * \return The value of datapool item pcktIdStartFailed
 */
static inline CrPsThirteenBit_t getDppcktIdStartFailed()
{
   return dpVerVars.pcktIdStartFailed;
}

/**
 * Sets the value of the datapool item pcktIdStartFailed
 * \param pcktIdStartFailed The value to be stored into the datapool item
 * pcktIdStartFailed.
 */
static inline void setDppcktIdStartFailed(CrPsThirteenBit_t pcktIdStartFailed)
{
   dpVerVars.pcktIdStartFailed = pcktIdStartFailed;
}

/**
 * Gets the value of the datapool item pcktIdTermFailed
 * \return The value of datapool item pcktIdTermFailed
 */
static inline CrPsThirteenBit_t getDppcktIdTermFailed()
{
   return dpVerVars.pcktIdTermFailed;
}

/**
 * Sets the value of the datapool item pcktIdTermFailed
 * \param pcktIdTermFailed The value to be stored into the datapool item
 * pcktIdTermFailed.
 */
static inline void setDppcktIdTermFailed(CrPsThirteenBit_t pcktIdTermFailed)
{
   dpVerVars.pcktIdTermFailed = pcktIdTermFailed;
}

/**
 * Gets the value of the datapool item stepPrgrFailed
 * \return The value of datapool item stepPrgrFailed
 */
static inline CrPsPrgStep_t getDpstepPrgrFailed()
{
   return dpVerVars.stepPrgrFailed;
}

/**
 * Sets the value of the datapool item stepPrgrFailed
 * \param stepPrgrFailed The value to be stored into the datapool item
 * stepPrgrFailed.
 */
static inline void setDpstepPrgrFailed(CrPsPrgStep_t stepPrgrFailed)
{
   dpVerVars.stepPrgrFailed = stepPrgrFailed;
}

/**
 * Gets the value of the datapool item verFailCode
 * \return The value of datapool item verFailCode
 */
static inline CrPsFailCode_t getDpverFailCode()
{
   return dpVerVars.verFailCode;
}

/**
 * Sets the value of the datapool item verFailCode
 * \param verFailCode The value to be stored into the datapool item
 * verFailCode.
 */
static inline void setDpverFailCode(CrPsFailCode_t verFailCode)
{
   dpVerVars.verFailCode = verFailCode;
}

/**
 * Gets the value of the datapool item verFailData
 * \return The value of datapool item verFailData
 */
static inline CrPsFailData_t getDpverFailData()
{
   return dpVerVars.verFailData;
}

/**
 * Sets the value of the datapool item verFailData
 * \param verFailData The value to be stored into the datapool item
 * verFailData.
 */
static inline void setDpverFailData(CrPsFailData_t verFailData)
{
   dpVerVars.verFailData = verFailData;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSDPVER_H */
