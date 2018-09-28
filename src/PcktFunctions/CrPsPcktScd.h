/**
 * @file
 * @ingroup gen_pck
 *
 * Interface for accessing fields in packets of service "Scd".
 *
 * @note This file was generated on 2018-09-28 23:45:49
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSPCKTSCD_H_
#define CRPSPCKTSCD_H_

#include "CrPsTypes.h"

#include "CrPsPckt.h"
/**
 * Structure for EnbTbsCmd
 */
typedef struct __attribute__((packed)) _EnbTbsCmd_t {
   /**
    * Packet header.
    */
   TcHeader_t Header;

} EnbTbsCmd_t ;

/**
 * Structure for DisTbsCmd
 */
typedef struct __attribute__((packed)) _DisTbsCmd_t {
   /**
    * Packet header.
    */
   TcHeader_t Header;

} DisTbsCmd_t ;

/**
 * Structure for ResTbsCmd
 */
typedef struct __attribute__((packed)) _ResTbsCmd_t {
   /**
    * Packet header.
    */
   TcHeader_t Header;

} ResTbsCmd_t ;

/**
 * Structure for DelTbaCmd
 */
typedef struct __attribute__((packed)) _DelTbaCmd_t {
   /**
    * Packet header.
    */
   TcHeader_t Header;

   /**
    * Number of activities to be inserted in the time-based schedule
    */
   CrPsNTba_t N;
   
   struct __attribute__((packed)) {
      /**
       * Source of command embedded in activity to be deleted
       */
      CrFwDestSrc_t AppId;
      
   } N_[0];
} DelTbaCmd_t ;

/**
 * Structure for EnbSubSchedCmd
 */
typedef struct __attribute__((packed)) _EnbSubSchedCmd_t {
   /**
    * Packet header.
    */
   TcHeader_t Header;

   /**
    * The number of sub-schedule identifiers to be enabled
    */
   CrPsNTba_t N;
   
   struct __attribute__((packed)) {
      /**
       * The identifier of a sub-schedule to be enabled
       */
      CrPsNSubSchedGroup_t SubSchedId;
      
   } N_[0];
} EnbSubSchedCmd_t ;

/**
 * Structure for DisSubSchedCmd
 */
typedef struct __attribute__((packed)) _DisSubSchedCmd_t {
   /**
    * Packet header.
    */
   TcHeader_t Header;

   /**
    * The number of sub-schedule identifiers to be disabled
    */
   CrPsNTba_t N;
   
   struct __attribute__((packed)) {
      /**
       * The identifier of a sub-schedule to be disabled
       */
      CrPsNSubSchedGroup_t SubSchedId;
      
   } N_[0];
} DisSubSchedCmd_t ;

/**
 * Structure for CreGrpCmd
 */
typedef struct __attribute__((packed)) _CreGrpCmd_t {
   /**
    * Packet header.
    */
   TcHeader_t Header;

   /**
    * The number of groups to be created
    */
   CrPsNTba_t N;
   
   struct __attribute__((packed)) {
      /**
       * The identifier of a group to be created
       */
      CrPsNSubSchedGroup_t GroupId;
      
      /**
       * The initial enable status of the group
       */
      CrFwBool_t isGroupEnabled;
      
   } N_[0];
} CreGrpCmd_t ;

/**
 * Structure for DelGrpCmd
 */
typedef struct __attribute__((packed)) _DelGrpCmd_t {
   /**
    * Packet header.
    */
   TcHeader_t Header;

   /**
    * The number of groups to be deleted
    */
   CrPsNTba_t N;
   
   struct __attribute__((packed)) {
      /**
       * The identifier of a group to be deleted
       */
      CrPsNSubSchedGroup_t GroupId;
      
   } N_[0];
} DelGrpCmd_t ;

/**
 * Structure for EnbGrpCmd
 */
typedef struct __attribute__((packed)) _EnbGrpCmd_t {
   /**
    * Packet header.
    */
   TcHeader_t Header;

   /**
    * The number of groups to be enabled (if this is zero, then all groups are
    * enabled)
    */
   CrPsNTba_t N;
   
   struct __attribute__((packed)) {
      /**
       * The identifier of a group to be enabled
       */
      CrPsNSubSchedGroup_t GroupId;
      
   } N_[0];
} EnbGrpCmd_t ;

/**
 * Structure for DisGrpCmd
 */
typedef struct __attribute__((packed)) _DisGrpCmd_t {
   /**
    * Packet header.
    */
   TcHeader_t Header;

   /**
    * The number of groups to be enabled (if this is zero, then all groups
    * currently in use are disabled)
    */
   CrPsNTba_t N;
   
   struct __attribute__((packed)) {
      /**
       * The identifier of a group to be enabled
       */
      CrPsNSubSchedGroup_t GroupId;
      
   } N_[0];
} DisGrpCmd_t ;

/**
 * Structure for RepGrpCmd
 */
typedef struct __attribute__((packed)) _RepGrpCmd_t {
   /**
    * Packet header.
    */
   TcHeader_t Header;

} RepGrpCmd_t ;

/**
 * Structure for GrpRep
 */
typedef struct __attribute__((packed)) _GrpRep_t {
   /**
    * Packet header.
    */
   TmHeader_t Header;

   /**
    * Number of groups being reported
    */
   CrPsNTba_t N;
   
   struct __attribute__((packed)) {
      /**
       * The identifier of a group being reported
       */
      CrPsNSubSchedGroup_t GroupId;
      
      /**
       * The enable status of a group being reported
       */
      CrFwBool_t isGroupEnabled;
      
   } N_[0];
} GrpRep_t ;

/**
 * Get "N" from "DelTbaCmd" packet.
 * @param p Pointer to the packet.
 * @return Value of "N".
 */
static inline CrPsNTba_t getScdDelTbaCmdN(void* p) {
   DelTbaCmd_t* t;
   t = (DelTbaCmd_t*)p;
   return __builtin_bswap16(t->N);
}

/**
 * Set "N" in "DelTbaCmd" packet.
 * @param p Pointer to the packet.
 * @param N Value of "N" to be set in packet.
 */
static inline void setScdDelTbaCmdN(void* p, CrPsNTba_t N) {
   DelTbaCmd_t* t;
   t = (DelTbaCmd_t*)p;
   t->N = __builtin_bswap16(N);
}

/**
 * Get "AppId" from "DelTbaCmd" packet.
 * @param p Pointer to the packet.
 * @param N
 * @return Value of "AppId".
 */
static inline CrFwDestSrc_t getScdDelTbaCmdAppId(void* p, CrPsNTba_t N) {
   DelTbaCmd_t* t;
   t = (DelTbaCmd_t*)p;
   return t->N_[N].AppId;
}

/**
 * Set "AppId" in "DelTbaCmd" packet.
 * @param p Pointer to the packet.
 * @param N
 * @param AppId Value of "AppId" to be set in packet.
 */
static inline void setScdDelTbaCmdAppId(void* p, CrPsNTba_t N, CrFwDestSrc_t AppId) {
   DelTbaCmd_t* t;
   t = (DelTbaCmd_t*)p;
   t->N_[N].AppId = AppId;
}

/**
 * Get "APID" from "DelTbaCmd" packet.
 * @param p Pointer to the packet.
 * @param N
 * @return Value of "APID".
 */
static inline CrPsElevenBit_t getScdDelTbaCmdAPID(void* p, CrPsNTba_t N) {
   uint32_t t;
   (void)memcpy(&t, &((uint8_t*)p, CrPsNTba_t N)[3], sizeof(t));
   t = __builtin_bswap32(t);
   t >>= 21;
   t &= 0x7ff;
   return (CrPsElevenBit_t)t;
}

/**
 * Set "APID" in "DelTbaCmd" packet.
 * @param p Pointer to the packet.
 * @param N
 * @param APID Value of "APID" to be set in packet.
 */
static inline void setScdDelTbaCmdAPID(void* p, CrPsNTba_t N, CrPsElevenBit_t APID) {
   uint32_t s;
   uint32_t t;
   s = ((uint32_t)APID << 21);
   s &= (uint32_t)0xffe00000ull;
   (void)memcpy(&t, &((uint8_t*)p, CrPsNTba_t N)[3], sizeof(t));
   t = __builtin_bswap32(t);
   t &= (uint32_t)~0xffe00000ull;
   t |= s;
   t = __builtin_bswap32(t);
   (void)memcpy(&((uint8_t*)p, CrPsNTba_t N)[3], &t, sizeof(t));
}

/**
 * Get "SrcSeqCnt" from "DelTbaCmd" packet.
 * @param p Pointer to the packet.
 * @param N
 * @return Value of "SrcSeqCnt".
 */
static inline CrPsFourteenBit_t getScdDelTbaCmdSrcSeqCnt(void* p, CrPsNTba_t N) {
   uint32_t t;
   (void)memcpy(&t, &((uint8_t*)p, CrPsNTba_t N)[4], sizeof(t));
   t = __builtin_bswap32(t);
   t >>= 15;
   t &= 0x3fff;
   return (CrPsFourteenBit_t)t;
}

/**
 * Set "SrcSeqCnt" in "DelTbaCmd" packet.
 * @param p Pointer to the packet.
 * @param N
 * @param SrcSeqCnt Value of "SrcSeqCnt" to be set in packet.
 */
static inline void setScdDelTbaCmdSrcSeqCnt(void* p, CrPsNTba_t N, CrPsFourteenBit_t SrcSeqCnt) {
   uint32_t s;
   uint32_t t;
   s = ((uint32_t)SrcSeqCnt << 15);
   s &= (uint32_t)0x1fff8000ull;
   (void)memcpy(&t, &((uint8_t*)p, CrPsNTba_t N)[4], sizeof(t));
   t = __builtin_bswap32(t);
   t &= (uint32_t)~0x1fff8000ull;
   t |= s;
   t = __builtin_bswap32(t);
   (void)memcpy(&((uint8_t*)p, CrPsNTba_t N)[4], &t, sizeof(t));
}

/**
 * Get "N" from "EnbSubSchedCmd" packet.
 * @param p Pointer to the packet.
 * @return Value of "N".
 */
static inline CrPsNTba_t getScdEnbSubSchedCmdN(void* p) {
   EnbSubSchedCmd_t* t;
   t = (EnbSubSchedCmd_t*)p;
   return __builtin_bswap16(t->N);
}

/**
 * Set "N" in "EnbSubSchedCmd" packet.
 * @param p Pointer to the packet.
 * @param N Value of "N" to be set in packet.
 */
static inline void setScdEnbSubSchedCmdN(void* p, CrPsNTba_t N) {
   EnbSubSchedCmd_t* t;
   t = (EnbSubSchedCmd_t*)p;
   t->N = __builtin_bswap16(N);
}

/**
 * Get pointer to "SubSchedId" array from "EnbSubSchedCmd" packet.
 * @param p Pointer to the packet.
 * @return Pointer to the start of the SubSchedId array.
 */
static inline CrPsNSubSchedGroup_t* getScdEnbSubSchedCmdSubSchedIdArray(void* p) {
   EnbSubSchedCmd_t* t;
   t = (EnbSubSchedCmd_t*)p;
   return &t->N_[0].SubSchedId;
}

/**
 * Get "SubSchedId" array from "EnbSubSchedCmd" packet.
 * @param p Pointer to the packet.
 * @param dest Pointer to memory location where array data are copied to.
 */
static inline void readScdEnbSubSchedCmdSubSchedIdArray(void* p, void* dest) {
   EnbSubSchedCmd_t* t;
   t = (EnbSubSchedCmd_t*)p;
   memcpy(dest, &t->N_[0].SubSchedId, t->N*sizeof(t->N_[0].SubSchedId));
}

/**
 * Set "SubSchedId" array in "EnbSubSchedCmd" packet.
 * @param p Pointer to the packet.
 * @param src Pointer to memory location from where array data are copied.
 */
static inline void writeScdEnbSubSchedCmdSubSchedIdArray(void* p, const void* src) {
   EnbSubSchedCmd_t* t;
   t = (EnbSubSchedCmd_t*)p;
   memcpy(&t->N_[0].SubSchedId, src, t->N*sizeof(t->N_[0].SubSchedId));
}

/**
 * Get "SubSchedId" from "EnbSubSchedCmd" packet.
 * @param p Pointer to the packet.
 * @param N
 * @return Value of "SubSchedId".
 */
static inline CrPsNSubSchedGroup_t getScdEnbSubSchedCmdSubSchedId(void* p, CrPsNTba_t N) {
   EnbSubSchedCmd_t* t;
   t = (EnbSubSchedCmd_t*)p;
   return t->N_[N].SubSchedId;
}

/**
 * Set "SubSchedId" in "EnbSubSchedCmd" packet.
 * @param p Pointer to the packet.
 * @param N
 * @param SubSchedId Value of "SubSchedId" to be set in packet.
 */
static inline void setScdEnbSubSchedCmdSubSchedId(void* p, CrPsNTba_t N, CrPsNSubSchedGroup_t SubSchedId) {
   EnbSubSchedCmd_t* t;
   t = (EnbSubSchedCmd_t*)p;
   t->N_[N].SubSchedId = SubSchedId;
}

/**
 * Get "N" from "DisSubSchedCmd" packet.
 * @param p Pointer to the packet.
 * @return Value of "N".
 */
static inline CrPsNTba_t getScdDisSubSchedCmdN(void* p) {
   DisSubSchedCmd_t* t;
   t = (DisSubSchedCmd_t*)p;
   return __builtin_bswap16(t->N);
}

/**
 * Set "N" in "DisSubSchedCmd" packet.
 * @param p Pointer to the packet.
 * @param N Value of "N" to be set in packet.
 */
static inline void setScdDisSubSchedCmdN(void* p, CrPsNTba_t N) {
   DisSubSchedCmd_t* t;
   t = (DisSubSchedCmd_t*)p;
   t->N = __builtin_bswap16(N);
}

/**
 * Get pointer to "SubSchedId" array from "DisSubSchedCmd" packet.
 * @param p Pointer to the packet.
 * @return Pointer to the start of the SubSchedId array.
 */
static inline CrPsNSubSchedGroup_t* getScdDisSubSchedCmdSubSchedIdArray(void* p) {
   DisSubSchedCmd_t* t;
   t = (DisSubSchedCmd_t*)p;
   return &t->N_[0].SubSchedId;
}

/**
 * Get "SubSchedId" array from "DisSubSchedCmd" packet.
 * @param p Pointer to the packet.
 * @param dest Pointer to memory location where array data are copied to.
 */
static inline void readScdDisSubSchedCmdSubSchedIdArray(void* p, void* dest) {
   DisSubSchedCmd_t* t;
   t = (DisSubSchedCmd_t*)p;
   memcpy(dest, &t->N_[0].SubSchedId, t->N*sizeof(t->N_[0].SubSchedId));
}

/**
 * Set "SubSchedId" array in "DisSubSchedCmd" packet.
 * @param p Pointer to the packet.
 * @param src Pointer to memory location from where array data are copied.
 */
static inline void writeScdDisSubSchedCmdSubSchedIdArray(void* p, const void* src) {
   DisSubSchedCmd_t* t;
   t = (DisSubSchedCmd_t*)p;
   memcpy(&t->N_[0].SubSchedId, src, t->N*sizeof(t->N_[0].SubSchedId));
}

/**
 * Get "SubSchedId" from "DisSubSchedCmd" packet.
 * @param p Pointer to the packet.
 * @param N
 * @return Value of "SubSchedId".
 */
static inline CrPsNSubSchedGroup_t getScdDisSubSchedCmdSubSchedId(void* p, CrPsNTba_t N) {
   DisSubSchedCmd_t* t;
   t = (DisSubSchedCmd_t*)p;
   return t->N_[N].SubSchedId;
}

/**
 * Set "SubSchedId" in "DisSubSchedCmd" packet.
 * @param p Pointer to the packet.
 * @param N
 * @param SubSchedId Value of "SubSchedId" to be set in packet.
 */
static inline void setScdDisSubSchedCmdSubSchedId(void* p, CrPsNTba_t N, CrPsNSubSchedGroup_t SubSchedId) {
   DisSubSchedCmd_t* t;
   t = (DisSubSchedCmd_t*)p;
   t->N_[N].SubSchedId = SubSchedId;
}

/**
 * Get "N" from "CreGrpCmd" packet.
 * @param p Pointer to the packet.
 * @return Value of "N".
 */
static inline CrPsNTba_t getScdCreGrpCmdN(void* p) {
   CreGrpCmd_t* t;
   t = (CreGrpCmd_t*)p;
   return __builtin_bswap16(t->N);
}

/**
 * Set "N" in "CreGrpCmd" packet.
 * @param p Pointer to the packet.
 * @param N Value of "N" to be set in packet.
 */
static inline void setScdCreGrpCmdN(void* p, CrPsNTba_t N) {
   CreGrpCmd_t* t;
   t = (CreGrpCmd_t*)p;
   t->N = __builtin_bswap16(N);
}

/**
 * Get "GroupId" from "CreGrpCmd" packet.
 * @param p Pointer to the packet.
 * @param N
 * @return Value of "GroupId".
 */
static inline CrPsNSubSchedGroup_t getScdCreGrpCmdGroupId(void* p, CrPsNTba_t N) {
   CreGrpCmd_t* t;
   t = (CreGrpCmd_t*)p;
   return t->N_[N].GroupId;
}

/**
 * Set "GroupId" in "CreGrpCmd" packet.
 * @param p Pointer to the packet.
 * @param N
 * @param GroupId Value of "GroupId" to be set in packet.
 */
static inline void setScdCreGrpCmdGroupId(void* p, CrPsNTba_t N, CrPsNSubSchedGroup_t GroupId) {
   CreGrpCmd_t* t;
   t = (CreGrpCmd_t*)p;
   t->N_[N].GroupId = GroupId;
}

/**
 * Get "isGroupEnabled" from "CreGrpCmd" packet.
 * @param p Pointer to the packet.
 * @param N
 * @return Value of "isGroupEnabled".
 */
static inline CrFwBool_t getScdCreGrpCmdisGroupEnabled(void* p, CrPsNTba_t N) {
   CreGrpCmd_t* t;
   t = (CreGrpCmd_t*)p;
   return t->N_[N].isGroupEnabled;
}

/**
 * Set "isGroupEnabled" in "CreGrpCmd" packet.
 * @param p Pointer to the packet.
 * @param N
 * @param isGroupEnabled Value of "isGroupEnabled" to be set in packet.
 */
static inline void setScdCreGrpCmdisGroupEnabled(void* p, CrPsNTba_t N, CrFwBool_t isGroupEnabled) {
   CreGrpCmd_t* t;
   t = (CreGrpCmd_t*)p;
   t->N_[N].isGroupEnabled = isGroupEnabled;
}

/**
 * Get "N" from "DelGrpCmd" packet.
 * @param p Pointer to the packet.
 * @return Value of "N".
 */
static inline CrPsNTba_t getScdDelGrpCmdN(void* p) {
   DelGrpCmd_t* t;
   t = (DelGrpCmd_t*)p;
   return __builtin_bswap16(t->N);
}

/**
 * Set "N" in "DelGrpCmd" packet.
 * @param p Pointer to the packet.
 * @param N Value of "N" to be set in packet.
 */
static inline void setScdDelGrpCmdN(void* p, CrPsNTba_t N) {
   DelGrpCmd_t* t;
   t = (DelGrpCmd_t*)p;
   t->N = __builtin_bswap16(N);
}

/**
 * Get pointer to "GroupId" array from "DelGrpCmd" packet.
 * @param p Pointer to the packet.
 * @return Pointer to the start of the GroupId array.
 */
static inline CrPsNSubSchedGroup_t* getScdDelGrpCmdGroupIdArray(void* p) {
   DelGrpCmd_t* t;
   t = (DelGrpCmd_t*)p;
   return &t->N_[0].GroupId;
}

/**
 * Get "GroupId" array from "DelGrpCmd" packet.
 * @param p Pointer to the packet.
 * @param dest Pointer to memory location where array data are copied to.
 */
static inline void readScdDelGrpCmdGroupIdArray(void* p, void* dest) {
   DelGrpCmd_t* t;
   t = (DelGrpCmd_t*)p;
   memcpy(dest, &t->N_[0].GroupId, t->N*sizeof(t->N_[0].GroupId));
}

/**
 * Set "GroupId" array in "DelGrpCmd" packet.
 * @param p Pointer to the packet.
 * @param src Pointer to memory location from where array data are copied.
 */
static inline void writeScdDelGrpCmdGroupIdArray(void* p, const void* src) {
   DelGrpCmd_t* t;
   t = (DelGrpCmd_t*)p;
   memcpy(&t->N_[0].GroupId, src, t->N*sizeof(t->N_[0].GroupId));
}

/**
 * Get "GroupId" from "DelGrpCmd" packet.
 * @param p Pointer to the packet.
 * @param N
 * @return Value of "GroupId".
 */
static inline CrPsNSubSchedGroup_t getScdDelGrpCmdGroupId(void* p, CrPsNTba_t N) {
   DelGrpCmd_t* t;
   t = (DelGrpCmd_t*)p;
   return t->N_[N].GroupId;
}

/**
 * Set "GroupId" in "DelGrpCmd" packet.
 * @param p Pointer to the packet.
 * @param N
 * @param GroupId Value of "GroupId" to be set in packet.
 */
static inline void setScdDelGrpCmdGroupId(void* p, CrPsNTba_t N, CrPsNSubSchedGroup_t GroupId) {
   DelGrpCmd_t* t;
   t = (DelGrpCmd_t*)p;
   t->N_[N].GroupId = GroupId;
}

/**
 * Get "N" from "EnbGrpCmd" packet.
 * @param p Pointer to the packet.
 * @return Value of "N".
 */
static inline CrPsNTba_t getScdEnbGrpCmdN(void* p) {
   EnbGrpCmd_t* t;
   t = (EnbGrpCmd_t*)p;
   return __builtin_bswap16(t->N);
}

/**
 * Set "N" in "EnbGrpCmd" packet.
 * @param p Pointer to the packet.
 * @param N Value of "N" to be set in packet.
 */
static inline void setScdEnbGrpCmdN(void* p, CrPsNTba_t N) {
   EnbGrpCmd_t* t;
   t = (EnbGrpCmd_t*)p;
   t->N = __builtin_bswap16(N);
}

/**
 * Get pointer to "GroupId" array from "EnbGrpCmd" packet.
 * @param p Pointer to the packet.
 * @return Pointer to the start of the GroupId array.
 */
static inline CrPsNSubSchedGroup_t* getScdEnbGrpCmdGroupIdArray(void* p) {
   EnbGrpCmd_t* t;
   t = (EnbGrpCmd_t*)p;
   return &t->N_[0].GroupId;
}

/**
 * Get "GroupId" array from "EnbGrpCmd" packet.
 * @param p Pointer to the packet.
 * @param dest Pointer to memory location where array data are copied to.
 */
static inline void readScdEnbGrpCmdGroupIdArray(void* p, void* dest) {
   EnbGrpCmd_t* t;
   t = (EnbGrpCmd_t*)p;
   memcpy(dest, &t->N_[0].GroupId, t->N*sizeof(t->N_[0].GroupId));
}

/**
 * Set "GroupId" array in "EnbGrpCmd" packet.
 * @param p Pointer to the packet.
 * @param src Pointer to memory location from where array data are copied.
 */
static inline void writeScdEnbGrpCmdGroupIdArray(void* p, const void* src) {
   EnbGrpCmd_t* t;
   t = (EnbGrpCmd_t*)p;
   memcpy(&t->N_[0].GroupId, src, t->N*sizeof(t->N_[0].GroupId));
}

/**
 * Get "GroupId" from "EnbGrpCmd" packet.
 * @param p Pointer to the packet.
 * @param N
 * @return Value of "GroupId".
 */
static inline CrPsNSubSchedGroup_t getScdEnbGrpCmdGroupId(void* p, CrPsNTba_t N) {
   EnbGrpCmd_t* t;
   t = (EnbGrpCmd_t*)p;
   return t->N_[N].GroupId;
}

/**
 * Set "GroupId" in "EnbGrpCmd" packet.
 * @param p Pointer to the packet.
 * @param N
 * @param GroupId Value of "GroupId" to be set in packet.
 */
static inline void setScdEnbGrpCmdGroupId(void* p, CrPsNTba_t N, CrPsNSubSchedGroup_t GroupId) {
   EnbGrpCmd_t* t;
   t = (EnbGrpCmd_t*)p;
   t->N_[N].GroupId = GroupId;
}

/**
 * Get "N" from "DisGrpCmd" packet.
 * @param p Pointer to the packet.
 * @return Value of "N".
 */
static inline CrPsNTba_t getScdDisGrpCmdN(void* p) {
   DisGrpCmd_t* t;
   t = (DisGrpCmd_t*)p;
   return __builtin_bswap16(t->N);
}

/**
 * Set "N" in "DisGrpCmd" packet.
 * @param p Pointer to the packet.
 * @param N Value of "N" to be set in packet.
 */
static inline void setScdDisGrpCmdN(void* p, CrPsNTba_t N) {
   DisGrpCmd_t* t;
   t = (DisGrpCmd_t*)p;
   t->N = __builtin_bswap16(N);
}

/**
 * Get pointer to "GroupId" array from "DisGrpCmd" packet.
 * @param p Pointer to the packet.
 * @return Pointer to the start of the GroupId array.
 */
static inline CrPsNSubSchedGroup_t* getScdDisGrpCmdGroupIdArray(void* p) {
   DisGrpCmd_t* t;
   t = (DisGrpCmd_t*)p;
   return &t->N_[0].GroupId;
}

/**
 * Get "GroupId" array from "DisGrpCmd" packet.
 * @param p Pointer to the packet.
 * @param dest Pointer to memory location where array data are copied to.
 */
static inline void readScdDisGrpCmdGroupIdArray(void* p, void* dest) {
   DisGrpCmd_t* t;
   t = (DisGrpCmd_t*)p;
   memcpy(dest, &t->N_[0].GroupId, t->N*sizeof(t->N_[0].GroupId));
}

/**
 * Set "GroupId" array in "DisGrpCmd" packet.
 * @param p Pointer to the packet.
 * @param src Pointer to memory location from where array data are copied.
 */
static inline void writeScdDisGrpCmdGroupIdArray(void* p, const void* src) {
   DisGrpCmd_t* t;
   t = (DisGrpCmd_t*)p;
   memcpy(&t->N_[0].GroupId, src, t->N*sizeof(t->N_[0].GroupId));
}

/**
 * Get "GroupId" from "DisGrpCmd" packet.
 * @param p Pointer to the packet.
 * @param N
 * @return Value of "GroupId".
 */
static inline CrPsNSubSchedGroup_t getScdDisGrpCmdGroupId(void* p, CrPsNTba_t N) {
   DisGrpCmd_t* t;
   t = (DisGrpCmd_t*)p;
   return t->N_[N].GroupId;
}

/**
 * Set "GroupId" in "DisGrpCmd" packet.
 * @param p Pointer to the packet.
 * @param N
 * @param GroupId Value of "GroupId" to be set in packet.
 */
static inline void setScdDisGrpCmdGroupId(void* p, CrPsNTba_t N, CrPsNSubSchedGroup_t GroupId) {
   DisGrpCmd_t* t;
   t = (DisGrpCmd_t*)p;
   t->N_[N].GroupId = GroupId;
}

/**
 * Get "N" from "GrpRep" packet.
 * @param p Pointer to the packet.
 * @return Value of "N".
 */
static inline CrPsNTba_t getScdGrpRepN(void* p) {
   GrpRep_t* t;
   t = (GrpRep_t*)p;
   return __builtin_bswap16(t->N);
}

/**
 * Set "N" in "GrpRep" packet.
 * @param p Pointer to the packet.
 * @param N Value of "N" to be set in packet.
 */
static inline void setScdGrpRepN(void* p, CrPsNTba_t N) {
   GrpRep_t* t;
   t = (GrpRep_t*)p;
   t->N = __builtin_bswap16(N);
}

/**
 * Get "GroupId" from "GrpRep" packet.
 * @param p Pointer to the packet.
 * @param N
 * @return Value of "GroupId".
 */
static inline CrPsNSubSchedGroup_t getScdGrpRepGroupId(void* p, CrPsNTba_t N) {
   GrpRep_t* t;
   t = (GrpRep_t*)p;
   return t->N_[N].GroupId;
}

/**
 * Set "GroupId" in "GrpRep" packet.
 * @param p Pointer to the packet.
 * @param N
 * @param GroupId Value of "GroupId" to be set in packet.
 */
static inline void setScdGrpRepGroupId(void* p, CrPsNTba_t N, CrPsNSubSchedGroup_t GroupId) {
   GrpRep_t* t;
   t = (GrpRep_t*)p;
   t->N_[N].GroupId = GroupId;
}

/**
 * Get "isGroupEnabled" from "GrpRep" packet.
 * @param p Pointer to the packet.
 * @param N
 * @return Value of "isGroupEnabled".
 */
static inline CrFwBool_t getScdGrpRepisGroupEnabled(void* p, CrPsNTba_t N) {
   GrpRep_t* t;
   t = (GrpRep_t*)p;
   return t->N_[N].isGroupEnabled;
}

/**
 * Set "isGroupEnabled" in "GrpRep" packet.
 * @param p Pointer to the packet.
 * @param N
 * @param isGroupEnabled Value of "isGroupEnabled" to be set in packet.
 */
static inline void setScdGrpRepisGroupEnabled(void* p, CrPsNTba_t N, CrFwBool_t isGroupEnabled) {
   GrpRep_t* t;
   t = (GrpRep_t*)p;
   t->N_[N].isGroupEnabled = isGroupEnabled;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSPCKTSCD_H */
