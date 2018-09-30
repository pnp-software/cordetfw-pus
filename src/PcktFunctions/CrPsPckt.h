/**
 * @file
 * @ingroup gen_pck
 *
 * Packet header definitions.
 *
 * @note This file was generated on 2018-09-30 23:01:15
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSPCKT_H_
#define CRPSPCKT_H_

#include "CrPsTypes.h"

/**
 * Structure for TcHeader
 */
typedef struct __attribute__((packed)) _TcHeader_t {
   /**
    * Spacer block.
    */
   uint8_t block_5[2];

   /**
    * Spacer block.
    */
   uint8_t block_18[2];

   /**
    * Packet Data Length
    */
   CrPsSixteenBit_t PcktDataLen;
   
   /**
    * Spacer block.
    */
   uint8_t block_55[1];

   /**
    * PUS Service Type
    */
   CrPsEightBit_t ServType;
   
   /**
    * PUS Service Sub Type
    */
   CrPsEightBit_t ServSubType;
   
   /**
    * Identifier of telecommand source
    */
   CrPsEightBit_t SrcId;
   
} TcHeader_t ;

/**
 * Structure for TmHeader
 */
typedef struct __attribute__((packed)) _TmHeader_t {
   /**
    * Spacer block.
    */
   uint8_t block_5[2];

   /**
    * Spacer block.
    */
   uint8_t block_18[2];

   /**
    * Packet Data Length
    */
   CrPsSixteenBit_t PcktDataLen;
   
   /**
    * Spacer block.
    */
   uint8_t block_52[1];

   /**
    * PUS Service Type
    */
   CrPsEightBit_t ServType;
   
   /**
    * PUS Service Sub Type
    */
   CrPsEightBit_t ServSubType;
   
   /**
    * Destination Identifier
    */
   CrPsEightBit_t DestId;
   
   /**
    * CUC Time (6 bytes)
    */
   CrPsEightBit_t Time[6];
   
} TmHeader_t ;

/**
 * Get "PcktVersionNmb" from "TcHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "PcktVersionNmb".
 */
static inline CrPsThreeBit_t getTcHeaderPcktVersionNmb(void* p) {
   uint16_t t;
   (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
   t = __builtin_bswap16(t);
   t >>= 13;
   t &= 0x7;
   return (CrPsThreeBit_t)t;
}

/**
 * Set "PcktVersionNmb" in "TcHeader" packet.
 * @param p Pointer to the packet.
 * @param PcktVersionNmb Value of "PcktVersionNmb" to be set in packet.
 */
static inline void setTcHeaderPcktVersionNmb(void* p, CrPsThreeBit_t PcktVersionNmb) {
   uint16_t s;
   uint16_t t;
   s = ((uint16_t)PcktVersionNmb << 13);
   s &= (uint16_t)0xe000ull;
   (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
   t = __builtin_bswap16(t);
   t &= (uint16_t)~0xe000ull;
   t |= s;
   t = __builtin_bswap16(t);
   (void)memcpy(&((uint8_t*)p)[0], &t, sizeof(t));
}

/**
 * Get "PcktType" from "TcHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "PcktType".
 */
static inline CrPsOneBit_t getTcHeaderPcktType(void* p) {
   uint16_t t;
   (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
   t = __builtin_bswap16(t);
   t >>= 12;
   t &= 0x1;
   return (CrPsOneBit_t)t;
}

/**
 * Set "PcktType" in "TcHeader" packet.
 * @param p Pointer to the packet.
 * @param PcktType Value of "PcktType" to be set in packet.
 */
static inline void setTcHeaderPcktType(void* p, CrPsOneBit_t PcktType) {
   uint16_t s;
   uint16_t t;
   s = ((uint16_t)PcktType << 12);
   s &= (uint16_t)0x1000ull;
   (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
   t = __builtin_bswap16(t);
   t &= (uint16_t)~0x1000ull;
   t |= s;
   t = __builtin_bswap16(t);
   (void)memcpy(&((uint8_t*)p)[0], &t, sizeof(t));
}

/**
 * Get "SecHeaderFlag" from "TcHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "SecHeaderFlag".
 */
static inline CrPsOneBit_t getTcHeaderSecHeaderFlag(void* p) {
   uint16_t t;
   (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
   t = __builtin_bswap16(t);
   t >>= 11;
   t &= 0x1;
   return (CrPsOneBit_t)t;
}

/**
 * Set "SecHeaderFlag" in "TcHeader" packet.
 * @param p Pointer to the packet.
 * @param SecHeaderFlag Value of "SecHeaderFlag" to be set in packet.
 */
static inline void setTcHeaderSecHeaderFlag(void* p, CrPsOneBit_t SecHeaderFlag) {
   uint16_t s;
   uint16_t t;
   s = ((uint16_t)SecHeaderFlag << 11);
   s &= (uint16_t)0x800ull;
   (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
   t = __builtin_bswap16(t);
   t &= (uint16_t)~0x800ull;
   t |= s;
   t = __builtin_bswap16(t);
   (void)memcpy(&((uint8_t*)p)[0], &t, sizeof(t));
}

/**
 * Get "APID" from "TcHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "APID".
 */
static inline CrPsElevenBit_t getTcHeaderAPID(void* p) {
   uint32_t t;
   (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
   t = __builtin_bswap32(t);
   t >>= 16;
   t &= 0x7ff;
   return (CrPsElevenBit_t)t;
}

/**
 * Set "APID" in "TcHeader" packet.
 * @param p Pointer to the packet.
 * @param APID Value of "APID" to be set in packet.
 */
static inline void setTcHeaderAPID(void* p, CrPsElevenBit_t APID) {
   uint32_t s;
   uint32_t t;
   s = ((uint32_t)APID << 16);
   s &= (uint32_t)0x7ff0000ull;
   (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
   t = __builtin_bswap32(t);
   t &= (uint32_t)~0x7ff0000ull;
   t |= s;
   t = __builtin_bswap32(t);
   (void)memcpy(&((uint8_t*)p)[0], &t, sizeof(t));
}

/**
 * Get "SeqFlags" from "TcHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "SeqFlags".
 */
static inline CrPsTwoBit_t getTcHeaderSeqFlags(void* p) {
   uint16_t t;
   (void)memcpy(&t, &((uint8_t*)p)[2], sizeof(t));
   t = __builtin_bswap16(t);
   t >>= 14;
   t &= 0x3;
   return (CrPsTwoBit_t)t;
}

/**
 * Set "SeqFlags" in "TcHeader" packet.
 * @param p Pointer to the packet.
 * @param SeqFlags Value of "SeqFlags" to be set in packet.
 */
static inline void setTcHeaderSeqFlags(void* p, CrPsTwoBit_t SeqFlags) {
   uint16_t s;
   uint16_t t;
   s = ((uint16_t)SeqFlags << 14);
   s &= (uint16_t)0xc000ull;
   (void)memcpy(&t, &((uint8_t*)p)[2], sizeof(t));
   t = __builtin_bswap16(t);
   t &= (uint16_t)~0xc000ull;
   t |= s;
   t = __builtin_bswap16(t);
   (void)memcpy(&((uint8_t*)p)[2], &t, sizeof(t));
}

/**
 * Get "SeqCount" from "TcHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "SeqCount".
 */
static inline CrPsFourteenBit_t getTcHeaderSeqCount(void* p) {
   uint32_t t;
   (void)memcpy(&t, &((uint8_t*)p)[2], sizeof(t));
   t = __builtin_bswap32(t);
   t >>= 16;
   t &= 0x3fff;
   return (CrPsFourteenBit_t)t;
}

/**
 * Set "SeqCount" in "TcHeader" packet.
 * @param p Pointer to the packet.
 * @param SeqCount Value of "SeqCount" to be set in packet.
 */
static inline void setTcHeaderSeqCount(void* p, CrPsFourteenBit_t SeqCount) {
   uint32_t s;
   uint32_t t;
   s = ((uint32_t)SeqCount << 16);
   s &= (uint32_t)0x3fff0000ull;
   (void)memcpy(&t, &((uint8_t*)p)[2], sizeof(t));
   t = __builtin_bswap32(t);
   t &= (uint32_t)~0x3fff0000ull;
   t |= s;
   t = __builtin_bswap32(t);
   (void)memcpy(&((uint8_t*)p)[2], &t, sizeof(t));
}

/**
 * Get "PcktDataLen" from "TcHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "PcktDataLen".
 */
static inline CrPsSixteenBit_t getTcHeaderPcktDataLen(void* p) {
   TcHeader_t* t;
   t = (TcHeader_t*)p;
   return __builtin_bswap16(t->PcktDataLen);
}

/**
 * Set "PcktDataLen" in "TcHeader" packet.
 * @param p Pointer to the packet.
 * @param PcktDataLen Value of "PcktDataLen" to be set in packet.
 */
static inline void setTcHeaderPcktDataLen(void* p, CrPsSixteenBit_t PcktDataLen) {
   TcHeader_t* t;
   t = (TcHeader_t*)p;
   t->PcktDataLen = __builtin_bswap16(PcktDataLen);
}

/**
 * Get "PUSVersion" from "TcHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "PUSVersion".
 */
static inline CrPsFourBit_t getTcHeaderPUSVersion(void* p) {
   uint16_t t;
   (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
   t = __builtin_bswap16(t);
   t >>= 12;
   t &= 0xf;
   return (CrPsFourBit_t)t;
}

/**
 * Set "PUSVersion" in "TcHeader" packet.
 * @param p Pointer to the packet.
 * @param PUSVersion Value of "PUSVersion" to be set in packet.
 */
static inline void setTcHeaderPUSVersion(void* p, CrPsFourBit_t PUSVersion) {
   uint16_t s;
   uint16_t t;
   s = ((uint16_t)PUSVersion << 12);
   s &= (uint16_t)0xf000ull;
   (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
   t = __builtin_bswap16(t);
   t &= (uint16_t)~0xf000ull;
   t |= s;
   t = __builtin_bswap16(t);
   (void)memcpy(&((uint8_t*)p)[6], &t, sizeof(t));
}

/**
 * Get "AckAccFlag" from "TcHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "AckAccFlag".
 */
static inline CrPsAckFlag_t getTcHeaderAckAccFlag(void* p) {
   uint16_t t;
   (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
   t = __builtin_bswap16(t);
   t >>= 11;
   t &= 0x1;
   return (CrPsAckFlag_t)t;
}

/**
 * Set "AckAccFlag" in "TcHeader" packet.
 * @param p Pointer to the packet.
 * @param AckAccFlag Value of "AckAccFlag" to be set in packet.
 */
static inline void setTcHeaderAckAccFlag(void* p, CrPsAckFlag_t AckAccFlag) {
   uint16_t s;
   uint16_t t;
   s = ((uint16_t)AckAccFlag << 11);
   s &= (uint16_t)0x800ull;
   (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
   t = __builtin_bswap16(t);
   t &= (uint16_t)~0x800ull;
   t |= s;
   t = __builtin_bswap16(t);
   (void)memcpy(&((uint8_t*)p)[6], &t, sizeof(t));
}

/**
 * Get "AckStartFlag" from "TcHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "AckStartFlag".
 */
static inline CrPsAckFlag_t getTcHeaderAckStartFlag(void* p) {
   uint16_t t;
   (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
   t = __builtin_bswap16(t);
   t >>= 10;
   t &= 0x1;
   return (CrPsAckFlag_t)t;
}

/**
 * Set "AckStartFlag" in "TcHeader" packet.
 * @param p Pointer to the packet.
 * @param AckStartFlag Value of "AckStartFlag" to be set in packet.
 */
static inline void setTcHeaderAckStartFlag(void* p, CrPsAckFlag_t AckStartFlag) {
   uint16_t s;
   uint16_t t;
   s = ((uint16_t)AckStartFlag << 10);
   s &= (uint16_t)0x400ull;
   (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
   t = __builtin_bswap16(t);
   t &= (uint16_t)~0x400ull;
   t |= s;
   t = __builtin_bswap16(t);
   (void)memcpy(&((uint8_t*)p)[6], &t, sizeof(t));
}

/**
 * Get "AckProgFlag" from "TcHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "AckProgFlag".
 */
static inline CrPsAckFlag_t getTcHeaderAckProgFlag(void* p) {
   uint16_t t;
   (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
   t = __builtin_bswap16(t);
   t >>= 9;
   t &= 0x1;
   return (CrPsAckFlag_t)t;
}

/**
 * Set "AckProgFlag" in "TcHeader" packet.
 * @param p Pointer to the packet.
 * @param AckProgFlag Value of "AckProgFlag" to be set in packet.
 */
static inline void setTcHeaderAckProgFlag(void* p, CrPsAckFlag_t AckProgFlag) {
   uint16_t s;
   uint16_t t;
   s = ((uint16_t)AckProgFlag << 9);
   s &= (uint16_t)0x200ull;
   (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
   t = __builtin_bswap16(t);
   t &= (uint16_t)~0x200ull;
   t |= s;
   t = __builtin_bswap16(t);
   (void)memcpy(&((uint8_t*)p)[6], &t, sizeof(t));
}

/**
 * Get "AckTermFlag" from "TcHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "AckTermFlag".
 */
static inline CrPsAckFlag_t getTcHeaderAckTermFlag(void* p) {
   uint16_t t;
   (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
   t = __builtin_bswap16(t);
   t >>= 8;
   t &= 0x1;
   return (CrPsAckFlag_t)t;
}

/**
 * Set "AckTermFlag" in "TcHeader" packet.
 * @param p Pointer to the packet.
 * @param AckTermFlag Value of "AckTermFlag" to be set in packet.
 */
static inline void setTcHeaderAckTermFlag(void* p, CrPsAckFlag_t AckTermFlag) {
   uint16_t s;
   uint16_t t;
   s = ((uint16_t)AckTermFlag << 8);
   s &= (uint16_t)0x100ull;
   (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
   t = __builtin_bswap16(t);
   t &= (uint16_t)~0x100ull;
   t |= s;
   t = __builtin_bswap16(t);
   (void)memcpy(&((uint8_t*)p)[6], &t, sizeof(t));
}

/**
 * Get "ServType" from "TcHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "ServType".
 */
static inline CrPsEightBit_t getTcHeaderServType(void* p) {
   TcHeader_t* t;
   t = (TcHeader_t*)p;
   return t->ServType;
}

/**
 * Set "ServType" in "TcHeader" packet.
 * @param p Pointer to the packet.
 * @param ServType Value of "ServType" to be set in packet.
 */
static inline void setTcHeaderServType(void* p, CrPsEightBit_t ServType) {
   TcHeader_t* t;
   t = (TcHeader_t*)p;
   t->ServType = ServType;
}

/**
 * Get "ServSubType" from "TcHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "ServSubType".
 */
static inline CrPsEightBit_t getTcHeaderServSubType(void* p) {
   TcHeader_t* t;
   t = (TcHeader_t*)p;
   return t->ServSubType;
}

/**
 * Set "ServSubType" in "TcHeader" packet.
 * @param p Pointer to the packet.
 * @param ServSubType Value of "ServSubType" to be set in packet.
 */
static inline void setTcHeaderServSubType(void* p, CrPsEightBit_t ServSubType) {
   TcHeader_t* t;
   t = (TcHeader_t*)p;
   t->ServSubType = ServSubType;
}

/**
 * Get "SrcId" from "TcHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "SrcId".
 */
static inline CrPsEightBit_t getTcHeaderSrcId(void* p) {
   TcHeader_t* t;
   t = (TcHeader_t*)p;
   return t->SrcId;
}

/**
 * Set "SrcId" in "TcHeader" packet.
 * @param p Pointer to the packet.
 * @param SrcId Value of "SrcId" to be set in packet.
 */
static inline void setTcHeaderSrcId(void* p, CrPsEightBit_t SrcId) {
   TcHeader_t* t;
   t = (TcHeader_t*)p;
   t->SrcId = SrcId;
}

/**
 * Get "PcktVersionNmb" from "TmHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "PcktVersionNmb".
 */
static inline CrPsThreeBit_t getTmHeaderPcktVersionNmb(void* p) {
   uint16_t t;
   (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
   t = __builtin_bswap16(t);
   t >>= 13;
   t &= 0x7;
   return (CrPsThreeBit_t)t;
}

/**
 * Set "PcktVersionNmb" in "TmHeader" packet.
 * @param p Pointer to the packet.
 * @param PcktVersionNmb Value of "PcktVersionNmb" to be set in packet.
 */
static inline void setTmHeaderPcktVersionNmb(void* p, CrPsThreeBit_t PcktVersionNmb) {
   uint16_t s;
   uint16_t t;
   s = ((uint16_t)PcktVersionNmb << 13);
   s &= (uint16_t)0xe000ull;
   (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
   t = __builtin_bswap16(t);
   t &= (uint16_t)~0xe000ull;
   t |= s;
   t = __builtin_bswap16(t);
   (void)memcpy(&((uint8_t*)p)[0], &t, sizeof(t));
}

/**
 * Get "PcktType" from "TmHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "PcktType".
 */
static inline CrPsOneBit_t getTmHeaderPcktType(void* p) {
   uint16_t t;
   (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
   t = __builtin_bswap16(t);
   t >>= 12;
   t &= 0x1;
   return (CrPsOneBit_t)t;
}

/**
 * Set "PcktType" in "TmHeader" packet.
 * @param p Pointer to the packet.
 * @param PcktType Value of "PcktType" to be set in packet.
 */
static inline void setTmHeaderPcktType(void* p, CrPsOneBit_t PcktType) {
   uint16_t s;
   uint16_t t;
   s = ((uint16_t)PcktType << 12);
   s &= (uint16_t)0x1000ull;
   (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
   t = __builtin_bswap16(t);
   t &= (uint16_t)~0x1000ull;
   t |= s;
   t = __builtin_bswap16(t);
   (void)memcpy(&((uint8_t*)p)[0], &t, sizeof(t));
}

/**
 * Get "SecHeaderFlag" from "TmHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "SecHeaderFlag".
 */
static inline CrPsOneBit_t getTmHeaderSecHeaderFlag(void* p) {
   uint16_t t;
   (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
   t = __builtin_bswap16(t);
   t >>= 11;
   t &= 0x1;
   return (CrPsOneBit_t)t;
}

/**
 * Set "SecHeaderFlag" in "TmHeader" packet.
 * @param p Pointer to the packet.
 * @param SecHeaderFlag Value of "SecHeaderFlag" to be set in packet.
 */
static inline void setTmHeaderSecHeaderFlag(void* p, CrPsOneBit_t SecHeaderFlag) {
   uint16_t s;
   uint16_t t;
   s = ((uint16_t)SecHeaderFlag << 11);
   s &= (uint16_t)0x800ull;
   (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
   t = __builtin_bswap16(t);
   t &= (uint16_t)~0x800ull;
   t |= s;
   t = __builtin_bswap16(t);
   (void)memcpy(&((uint8_t*)p)[0], &t, sizeof(t));
}

/**
 * Get "APID" from "TmHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "APID".
 */
static inline CrPsElevenBit_t getTmHeaderAPID(void* p) {
   uint32_t t;
   (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
   t = __builtin_bswap32(t);
   t >>= 16;
   t &= 0x7ff;
   return (CrPsElevenBit_t)t;
}

/**
 * Set "APID" in "TmHeader" packet.
 * @param p Pointer to the packet.
 * @param APID Value of "APID" to be set in packet.
 */
static inline void setTmHeaderAPID(void* p, CrPsElevenBit_t APID) {
   uint32_t s;
   uint32_t t;
   s = ((uint32_t)APID << 16);
   s &= (uint32_t)0x7ff0000ull;
   (void)memcpy(&t, &((uint8_t*)p)[0], sizeof(t));
   t = __builtin_bswap32(t);
   t &= (uint32_t)~0x7ff0000ull;
   t |= s;
   t = __builtin_bswap32(t);
   (void)memcpy(&((uint8_t*)p)[0], &t, sizeof(t));
}

/**
 * Get "SeqFlags" from "TmHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "SeqFlags".
 */
static inline CrPsTwoBit_t getTmHeaderSeqFlags(void* p) {
   uint16_t t;
   (void)memcpy(&t, &((uint8_t*)p)[2], sizeof(t));
   t = __builtin_bswap16(t);
   t >>= 14;
   t &= 0x3;
   return (CrPsTwoBit_t)t;
}

/**
 * Set "SeqFlags" in "TmHeader" packet.
 * @param p Pointer to the packet.
 * @param SeqFlags Value of "SeqFlags" to be set in packet.
 */
static inline void setTmHeaderSeqFlags(void* p, CrPsTwoBit_t SeqFlags) {
   uint16_t s;
   uint16_t t;
   s = ((uint16_t)SeqFlags << 14);
   s &= (uint16_t)0xc000ull;
   (void)memcpy(&t, &((uint8_t*)p)[2], sizeof(t));
   t = __builtin_bswap16(t);
   t &= (uint16_t)~0xc000ull;
   t |= s;
   t = __builtin_bswap16(t);
   (void)memcpy(&((uint8_t*)p)[2], &t, sizeof(t));
}

/**
 * Get "SeqCount" from "TmHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "SeqCount".
 */
static inline CrPsFourteenBit_t getTmHeaderSeqCount(void* p) {
   uint32_t t;
   (void)memcpy(&t, &((uint8_t*)p)[2], sizeof(t));
   t = __builtin_bswap32(t);
   t >>= 16;
   t &= 0x3fff;
   return (CrPsFourteenBit_t)t;
}

/**
 * Set "SeqCount" in "TmHeader" packet.
 * @param p Pointer to the packet.
 * @param SeqCount Value of "SeqCount" to be set in packet.
 */
static inline void setTmHeaderSeqCount(void* p, CrPsFourteenBit_t SeqCount) {
   uint32_t s;
   uint32_t t;
   s = ((uint32_t)SeqCount << 16);
   s &= (uint32_t)0x3fff0000ull;
   (void)memcpy(&t, &((uint8_t*)p)[2], sizeof(t));
   t = __builtin_bswap32(t);
   t &= (uint32_t)~0x3fff0000ull;
   t |= s;
   t = __builtin_bswap32(t);
   (void)memcpy(&((uint8_t*)p)[2], &t, sizeof(t));
}

/**
 * Get "PcktDataLen" from "TmHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "PcktDataLen".
 */
static inline CrPsSixteenBit_t getTmHeaderPcktDataLen(void* p) {
   TmHeader_t* t;
   t = (TmHeader_t*)p;
   return __builtin_bswap16(t->PcktDataLen);
}

/**
 * Set "PcktDataLen" in "TmHeader" packet.
 * @param p Pointer to the packet.
 * @param PcktDataLen Value of "PcktDataLen" to be set in packet.
 */
static inline void setTmHeaderPcktDataLen(void* p, CrPsSixteenBit_t PcktDataLen) {
   TmHeader_t* t;
   t = (TmHeader_t*)p;
   t->PcktDataLen = __builtin_bswap16(PcktDataLen);
}

/**
 * Get "PUSVersion" from "TmHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "PUSVersion".
 */
static inline CrPsFourBit_t getTmHeaderPUSVersion(void* p) {
   uint16_t t;
   (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
   t = __builtin_bswap16(t);
   t >>= 12;
   t &= 0xf;
   return (CrPsFourBit_t)t;
}

/**
 * Set "PUSVersion" in "TmHeader" packet.
 * @param p Pointer to the packet.
 * @param PUSVersion Value of "PUSVersion" to be set in packet.
 */
static inline void setTmHeaderPUSVersion(void* p, CrPsFourBit_t PUSVersion) {
   uint16_t s;
   uint16_t t;
   s = ((uint16_t)PUSVersion << 12);
   s &= (uint16_t)0xf000ull;
   (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
   t = __builtin_bswap16(t);
   t &= (uint16_t)~0xf000ull;
   t |= s;
   t = __builtin_bswap16(t);
   (void)memcpy(&((uint8_t*)p)[6], &t, sizeof(t));
}

/**
 * Get "SpaceTimeRefStatus" from "TmHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "SpaceTimeRefStatus".
 */
static inline CrPsFourBit_t getTmHeaderSpaceTimeRefStatus(void* p) {
   uint16_t t;
   (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
   t = __builtin_bswap16(t);
   t >>= 8;
   t &= 0xf;
   return (CrPsFourBit_t)t;
}

/**
 * Set "SpaceTimeRefStatus" in "TmHeader" packet.
 * @param p Pointer to the packet.
 * @param SpaceTimeRefStatus Value of "SpaceTimeRefStatus" to be set in
 * packet.
 */
static inline void setTmHeaderSpaceTimeRefStatus(void* p, CrPsFourBit_t SpaceTimeRefStatus) {
   uint16_t s;
   uint16_t t;
   s = ((uint16_t)SpaceTimeRefStatus << 8);
   s &= (uint16_t)0xf00ull;
   (void)memcpy(&t, &((uint8_t*)p)[6], sizeof(t));
   t = __builtin_bswap16(t);
   t &= (uint16_t)~0xf00ull;
   t |= s;
   t = __builtin_bswap16(t);
   (void)memcpy(&((uint8_t*)p)[6], &t, sizeof(t));
}

/**
 * Get "ServType" from "TmHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "ServType".
 */
static inline CrPsEightBit_t getTmHeaderServType(void* p) {
   TmHeader_t* t;
   t = (TmHeader_t*)p;
   return t->ServType;
}

/**
 * Set "ServType" in "TmHeader" packet.
 * @param p Pointer to the packet.
 * @param ServType Value of "ServType" to be set in packet.
 */
static inline void setTmHeaderServType(void* p, CrPsEightBit_t ServType) {
   TmHeader_t* t;
   t = (TmHeader_t*)p;
   t->ServType = ServType;
}

/**
 * Get "ServSubType" from "TmHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "ServSubType".
 */
static inline CrPsEightBit_t getTmHeaderServSubType(void* p) {
   TmHeader_t* t;
   t = (TmHeader_t*)p;
   return t->ServSubType;
}

/**
 * Set "ServSubType" in "TmHeader" packet.
 * @param p Pointer to the packet.
 * @param ServSubType Value of "ServSubType" to be set in packet.
 */
static inline void setTmHeaderServSubType(void* p, CrPsEightBit_t ServSubType) {
   TmHeader_t* t;
   t = (TmHeader_t*)p;
   t->ServSubType = ServSubType;
}

/**
 * Get "DestId" from "TmHeader" packet.
 * @param p Pointer to the packet.
 * @return Value of "DestId".
 */
static inline CrPsEightBit_t getTmHeaderDestId(void* p) {
   TmHeader_t* t;
   t = (TmHeader_t*)p;
   return t->DestId;
}

/**
 * Set "DestId" in "TmHeader" packet.
 * @param p Pointer to the packet.
 * @param DestId Value of "DestId" to be set in packet.
 */
static inline void setTmHeaderDestId(void* p, CrPsEightBit_t DestId) {
   TmHeader_t* t;
   t = (TmHeader_t*)p;
   t->DestId = DestId;
}

/**
 * Get pointer to "Time" array from "TmHeader" packet.
 * @param p Pointer to the packet.
 * @return Pointer to the start of the Time array.
 */
static inline CrPsEightBit_t* getTmHeaderTimeArray(void* p) {
   TmHeader_t* t;
   t = (TmHeader_t*)p;
   return &t->Time[0];
}

/**
 * Get "Time" array from "TmHeader" packet.
 * @param p Pointer to the packet.
 * @param dest Pointer to memory location where array data are copied to.
 */
static inline void getTmHeaderTime(void* p, void* dest) {
   TmHeader_t* t;
   t = (TmHeader_t*)p;
   memcpy(dest, &t->Time[0], sizeof(t->Time));
}

/**
 * Set "Time" array in "TmHeader" packet.
 * @param p Pointer to the packet.
 * @param src Pointer to memory location from where array data are copied.
 */
static inline void setTmHeaderTime(void* p, const void* src) {
   TmHeader_t* t;
   t = (TmHeader_t*)p;
   memcpy(&t->Time[0], src, sizeof(t->Time));
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSPCKT_H */
