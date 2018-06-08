/**
 * \file
 *
 * Type definitions.
 *
 * \note This file was generated on 2018-06-08 18:16:54
 * \author Automatically Generated by CORDET Editor
 * \copyright P&P Software GmbH
 */
#ifndef CRPSTYPES_H_
#define CRPSTYPES_H_

#include "CrPsUserConstants.h"

/**
 * Definition of type "FailData_t".
 */
typedef uint32_t FailData_t;

/**
 * Definition of type "OneBit_t".
 */
typedef uint8_t OneBit_t;

/**
 * Definition of type "TwoBit_t".
 */
typedef uint8_t TwoBit_t;

/**
 * Definition of type "ThreeBit_t".
 */
typedef uint8_t ThreeBit_t;

/**
 * Definition of type "FourBit_t".
 */
typedef uint8_t FourBit_t;

/**
 * Definition of type "FourteenBit_t".
 */
typedef uint16_t FourteenBit_t;

/**
 * Definition of type "ElevenBit_t".
 */
typedef uint16_t ElevenBit_t;

/**
 * Definition of type "DestSrc_t".
 */
typedef uint8_t DestSrc_t;

/**
 * Definition of type "TimeStamp_t".
 */
typedef uint48_t TimeStamp_t;

/**
 * Definition of type "CollectInterval_t".
 */
typedef uint16_t CollectInterval_t;

/**
 * Definition of type "PartSeqNmb_t".
 */
typedef uint16_t PartSeqNmb_t;

/**
 * Definition of type "TransId_t".
 */
typedef uint32_t TransId_t;

/**
 * Definition of type "SID_t".
 */
typedef uint8_t SID_t;

/**
 * Definition of type "RepNum_t".
 */
typedef uint8_t RepNum_t;

/**
 * Definition of type "FailReason_t".
 */
typedef uint16_t FailReason_t;

/**
 * Definition of type "NParMon_t".
 */
typedef uint8_t NParMon_t;

/**
 * Definition of type "NFuncMon_t".
 */
typedef uint8_t NFuncMon_t;

/**
 * Definition of type "FunctMonCheckStatus_t".
 */
typedef uint8_t FunctMonCheckStatus_t;
enum {
   MON_UNCHECKED = 1,
   MON_INVALID = 2,
   MON_RUNNING = 3,
   MON_FAILED = 4
};

/**
 * Definition of type "ParMonCheckStatus_t".
 */
typedef uint8_t ParMonCheckStatus_t;
enum {
   MON_VALID = 1,
   MON_NOT_EXP = 2,
   MON_ABOVE = 3,
   MON_BELOW = 4,
   MON_DEL_ABOVE = 5,
   MON_DEL_BELOW = 6
};

/**
 * Definition of type "MonCheckType_t".
 */
typedef uint8_t MonCheckType_t;
enum {
   EXP_VAL_CHECK = 1,
   LIM_CHECK = 2,
   DEL_CHECK = 3
};

/**
 * Definition of type "EvtId_t".
 */
typedef uint16_t EvtId_t;
enum {
   EVT_NULL = 0,
   EVT_DOWN_ABORT = 1,
   EVT_UP_ABORT = 2,
   EVT_MON_LIM_R = 3,
   EVT_MON_LIM_I = 4,
   EVT_MON_EXP = 5,
   EVT_MON_DEL_R = 6,
   EVT_MON_DEL_I = 7,
   EVT_FMON_FAIL = 8,
   EVT_CLST_FULL = 9
};

/**
 * Definition of type "ValCheckExpVal_t".
 */
typedef uint16_t ValCheckExpVal_t;

/**
 * Definition of type "RepNumber_t".
 */
typedef uint8_t RepNumber_t;

/**
 * Definition of type "MinFailNmb_t".
 */
typedef uint8_t MinFailNmb_t;

/**
 * Definition of type "ParMonId_t".
 */
typedef uint16_t ParMonId_t;

/**
 * Definition of type "FuncMonId_t".
 */
typedef uint8_t FuncMonId_t;

/**
 * Definition of type "EnableStatus_t".
 */
typedef uint8_t EnableStatus_t;
enum {
   DISABLED = 0,
   ENABLED = 1
};

/**
 * Definition of type "ProtStatus_t".
 */
typedef uint8_t ProtStatus_t;
enum {
   UNPROTECTED = 0,
   PROTECTED = 1
};

/**
 * Definition of type "RepDelay_t".
 */
typedef uint16_t RepDelay_t;

/**
 * Definition of type "AckFlag_t".
 */
typedef uint8_t AckFlag_t;
enum {
   NO_ACK = 0,
   ACK = 1
};

/**
 * Definition of type "ThirteenBit_t".
 */
typedef uint16_t ThirteenBit_t;

/**
 * Definition of type "SixteenBit_t".
 */
typedef uint16_t SixteenBit_t;

/**
 * Definition of type "ThirtytwoBit_t".
 */
typedef uint32_t ThirtytwoBit_t;

/**
 * Definition of type "PrgStep_t".
 */
typedef uint8_t PrgStep_t;

/**
 * Definition of type "NPar_t".
 */
typedef uint8_t NPar_t;

/**
 * Definition of type "ParId_t".
 */
typedef uint16_t ParId_t;

/**
 * Definition of type "NGroups_t".
 */
typedef uint8_t NGroups_t;

/**
 * Definition of type "NSID_t".
 */
typedef uint8_t NSID_t;

/**
 * Definition of type "EnDis_t".
 */
typedef uint8_t EnDis_t;
enum {
   DISABLED = 0,
   ENABLED = 1
};

/**
 * Definition of type "NEvtId_t".
 */
typedef uint8_t NEvtId_t;

/**
 * Definition of type "EightBit_t".
 */
typedef uint8_t EightBit_t;

/**
 * Definition of type "NEvtRep_t".
 */
typedef uint16_t NEvtRep_t;

/**
 * Definition of type "CycleCnt_t".
 */
typedef uint16_t CycleCnt_t;

/**
 * Definition of type "SampleBufId_t".
 */
typedef uint8_t SampleBufId_t;

/**
 * Definition of type "TimeSec_t".
 */
typedef uint32_t TimeSec_t;

/**
 * Definition of type "TimeCyc_t".
 */
typedef uint16_t TimeCyc_t;

/**
 * Definition of type "NOfCmd_t".
 */
typedef uint16_t NOfCmd_t;

/**
 * Definition of type "NOfLinks_t".
 */
typedef uint8_t NOfLinks_t;

/**
 * Definition of type "Size_t".
 */
typedef uint16_t Size_t;

/**
 * Definition of type "NCmdRep_t".
 */
typedef uint32_t NCmdRep_t;

/**
 * Definition of type "NTba_t".
 */
typedef uint16_t NTba_t;

/**
 * Definition of type "NSubSchedGroup_t".
 */
typedef uint8_t NSubSchedGroup_t;

/**
 * Definition of type "Bool_t".
 */
typedef uint8_t Bool_t;

/**
 * Definition of type "ErrRepCode_t".
 */
typedef uint8_t ErrRepCode_t;
enum {
   INLOADER_ACC_FAIL = 200,
   INLOADER_INV_DEST = 201,
   OUTFACTORY_FAIL = 202,
   SNDPCKT_INV_DEST = 203
};

/**
 * Definition of type "Time_t".
 */
typedef uint32_t Time_t;

/**
 * Definition of type "FailCode_t".
 */
typedef uint16_t FailCode_t;
enum {
   VER_CMD_INV_DEST = 1,
   VER_REP_CR_FD = 2,
   VER_OUTLOADER_FD = 3,
   VER_SID_IN_USE = 4,
   VER_FULL_RDL = 5,
   VER_RDL_CONSTR = 6,
   VER_DUPL_DI = 7,
   VER_ILL_SID = 8,
   VER_ENABLED_SID = 9,
   VER_SID_START_FD = 10,
   VER_FACT_PRGR_FD = 11,
   VER_ILL_EID = 12,
   VER_EID_ST_FD = 13,
   VER_ILL_MON = 14,
   VER_MON_START_FD = 15,
   VER_PMDL_FULL = 16,
   VER_MOD_ILL_DI = 17,
   VER_MON_PROT = 18,
   VER_MON_ENB = 19,
   VER_MON_USE = 20,
   VER_FMDL_FULL = 21,
   VER_MON_TMP = 22,
   VER_MON_MFN = 23,
   VER_SCD_ILL_SS = 30,
   VER_FULL_TBS = 31,
   VER_SCD_ILL_G = 32,
   VER_SCD_ILL_RT = 33,
   VER_SCD_ILL_DS = 34,
   VER_SCD_CRFAIL = 35,
   VER_SCD_ST_FD = 36,
   VER_ILL_ACT_ID = 37
};


/*----------------------------------------------------------------------------*/
#endif /* CRPSTYPES_H */
