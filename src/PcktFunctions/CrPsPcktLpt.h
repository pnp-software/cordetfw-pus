/**
 * @file
 * @ingroup gen_pck
 *
 * Interface for accessing fields in packets of service "Lpt".
 *
 * @note This file was generated on 2018-07-10 22:24:46
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSPCKTLPT_H_
#define CRPSPCKTLPT_H_

#include "CrPsTypes.h"

#include "CrPsPckt.h"
/**
 * Structure for LptDownFirstRep
 */
typedef struct __attribute__((packed)) _LptDownFirstRep_t {
   /**
    * Packet header.
    */
   TmHeader_t Header;

   /**
    * Large Message Trans. Identifier
    */
   CrPsTransId_t Transid;
   
   /**
    * Part Sequence Number
    */
   CrPsPartSeqNmb_t PartSeqNmb;
   
   /**
    * Down-transfer data (repetition value to be set to fill the packet)
    */
   CrPsSixteenBit_t Part;
   
} LptDownFirstRep_t ;

/**
 * Structure for LptDownInterRep
 */
typedef struct __attribute__((packed)) _LptDownInterRep_t {
   /**
    * Packet header.
    */
   TmHeader_t Header;

   /**
    * Large Message Trans. Identifier
    */
   CrPsTransId_t Transid;
   
   /**
    * Part Sequence Number
    */
   CrPsPartSeqNmb_t PartSeqNmb;
   
   /**
    * Down-transfer data (repetition value to be set to fill the packet)
    */
   CrPsSixteenBit_t Part;
   
} LptDownInterRep_t ;

/**
 * Structure for LptDownLastRep
 */
typedef struct __attribute__((packed)) _LptDownLastRep_t {
   /**
    * Packet header.
    */
   TmHeader_t Header;

   /**
    * Large Message Trans. Identifier
    */
   CrPsTransId_t Transid;
   
   /**
    * Part Sequence Number
    */
   CrPsPartSeqNmb_t PartSeqNmb;
   
   /**
    * Down-transfer data (repetition value is set dynamically by the host
    * application based on the amount of data to be down-transferred)
    */
   CrPsSixteenBit_t Part;
   
} LptDownLastRep_t ;

/**
 * Structure for LptUpFirstCmd
 */
typedef struct __attribute__((packed)) _LptUpFirstCmd_t {
   /**
    * Packet header.
    */
   TcHeader_t Header;

   /**
    * Large Message Trans. Identifier
    */
   CrPsTransId_t Transid;
   
   /**
    * Part Sequence Number
    */
   CrPsPartSeqNmb_t PartSeqNmb;
   
   /**
    * Up-transfer data (repetition value to be set to fill the packet)
    */
   CrPsSixteenBit_t Part;
   
} LptUpFirstCmd_t ;

/**
 * Structure for LptUpInterCmd
 */
typedef struct __attribute__((packed)) _LptUpInterCmd_t {
   /**
    * Packet header.
    */
   TcHeader_t Header;

   /**
    * Large Message Trans. Identifier
    */
   CrPsTransId_t Transid;
   
   /**
    * Part Sequence Number
    */
   CrPsPartSeqNmb_t PartSeqNmb;
   
   /**
    * Up-transfer data (repetition value to be set to fill the packet)
    */
   CrPsSixteenBit_t Part;
   
} LptUpInterCmd_t ;

/**
 * Structure for LptUpLastCmd
 */
typedef struct __attribute__((packed)) _LptUpLastCmd_t {
   /**
    * Packet header.
    */
   TcHeader_t Header;

   /**
    * Large Message Trans. Identifier
    */
   CrPsTransId_t Transid;
   
   /**
    * Part Sequence Number
    */
   CrPsPartSeqNmb_t PartSeqNmb;
   
   /**
    * Up-transfer data (repetition value is set dynamically)
    */
   CrPsSixteenBit_t Part;
   
} LptUpLastCmd_t ;

/**
 * Structure for LptUpAbortRep
 */
typedef struct __attribute__((packed)) _LptUpAbortRep_t {
   /**
    * Packet header.
    */
   TmHeader_t Header;

   /**
    * Large Message Trans. Identifier
    */
   CrPsTransId_t Transid;
   
   /**
    * Transfer Failure Reason
    */
   CrPsFailReason_t FailReason;
   
} LptUpAbortRep_t ;

/**
 * Structure for LptStartDownCmd
 */
typedef struct __attribute__((packed)) _LptStartDownCmd_t {
   /**
    * Packet header.
    */
   TcHeader_t Header;

   /**
    * Large Message Trans. Identifier
    */
   CrPsTransId_t Transid;
   
} LptStartDownCmd_t ;

/**
 * Structure for LptAbortDownCmd
 */
typedef struct __attribute__((packed)) _LptAbortDownCmd_t {
   /**
    * Packet header.
    */
   TcHeader_t Header;

   /**
    * Large Message Trans. Identifier
    */
   CrPsTransId_t Transid;
   
} LptAbortDownCmd_t ;

/**
 * Get "Transid" from "LptDownFirstRep" packet.
 * @param p Pointer to the packet.
 * @return Value of "Transid".
 */
static inline CrPsTransId_t getLptDownFirstRepTransid(void* p)
{
   LptDownFirstRep_t* t;
   t = (LptDownFirstRep_t*)p;
   return t->Transid;
}

/**
 * Set "Transid" in "LptDownFirstRep" packet.
 * @param p Pointer to the packet.
 * @param Transid Value of "Transid" to be set in packet.
 */
static inline void setLptDownFirstRepTransid(void* p, CrPsTransId_t Transid)
{
   LptDownFirstRep_t* t;
   t = (LptDownFirstRep_t*)p;
   t->Transid = Transid;
}

/**
 * Get "PartSeqNmb" from "LptDownFirstRep" packet.
 * @param p Pointer to the packet.
 * @return Value of "PartSeqNmb".
 */
static inline CrPsPartSeqNmb_t getLptDownFirstRepPartSeqNmb(void* p)
{
   LptDownFirstRep_t* t;
   t = (LptDownFirstRep_t*)p;
   return t->PartSeqNmb;
}

/**
 * Set "PartSeqNmb" in "LptDownFirstRep" packet.
 * @param p Pointer to the packet.
 * @param PartSeqNmb Value of "PartSeqNmb" to be set in packet.
 */
static inline void setLptDownFirstRepPartSeqNmb(void* p, CrPsPartSeqNmb_t PartSeqNmb)
{
   LptDownFirstRep_t* t;
   t = (LptDownFirstRep_t*)p;
   t->PartSeqNmb = PartSeqNmb;
}

/**
 * Get "Part" from "LptDownFirstRep" packet.
 * @param p Pointer to the packet.
 * @return Value of "Part".
 */
static inline CrPsSixteenBit_t getLptDownFirstRepPart(void* p)
{
   LptDownFirstRep_t* t;
   t = (LptDownFirstRep_t*)p;
   return t->Part;
}

/**
 * Set "Part" in "LptDownFirstRep" packet.
 * @param p Pointer to the packet.
 * @param Part Value of "Part" to be set in packet.
 */
static inline void setLptDownFirstRepPart(void* p, CrPsSixteenBit_t Part)
{
   LptDownFirstRep_t* t;
   t = (LptDownFirstRep_t*)p;
   t->Part = Part;
}

/**
 * Get "Transid" from "LptDownInterRep" packet.
 * @param p Pointer to the packet.
 * @return Value of "Transid".
 */
static inline CrPsTransId_t getLptDownInterRepTransid(void* p)
{
   LptDownInterRep_t* t;
   t = (LptDownInterRep_t*)p;
   return t->Transid;
}

/**
 * Set "Transid" in "LptDownInterRep" packet.
 * @param p Pointer to the packet.
 * @param Transid Value of "Transid" to be set in packet.
 */
static inline void setLptDownInterRepTransid(void* p, CrPsTransId_t Transid)
{
   LptDownInterRep_t* t;
   t = (LptDownInterRep_t*)p;
   t->Transid = Transid;
}

/**
 * Get "PartSeqNmb" from "LptDownInterRep" packet.
 * @param p Pointer to the packet.
 * @return Value of "PartSeqNmb".
 */
static inline CrPsPartSeqNmb_t getLptDownInterRepPartSeqNmb(void* p)
{
   LptDownInterRep_t* t;
   t = (LptDownInterRep_t*)p;
   return t->PartSeqNmb;
}

/**
 * Set "PartSeqNmb" in "LptDownInterRep" packet.
 * @param p Pointer to the packet.
 * @param PartSeqNmb Value of "PartSeqNmb" to be set in packet.
 */
static inline void setLptDownInterRepPartSeqNmb(void* p, CrPsPartSeqNmb_t PartSeqNmb)
{
   LptDownInterRep_t* t;
   t = (LptDownInterRep_t*)p;
   t->PartSeqNmb = PartSeqNmb;
}

/**
 * Get "Part" from "LptDownInterRep" packet.
 * @param p Pointer to the packet.
 * @return Value of "Part".
 */
static inline CrPsSixteenBit_t getLptDownInterRepPart(void* p)
{
   LptDownInterRep_t* t;
   t = (LptDownInterRep_t*)p;
   return t->Part;
}

/**
 * Set "Part" in "LptDownInterRep" packet.
 * @param p Pointer to the packet.
 * @param Part Value of "Part" to be set in packet.
 */
static inline void setLptDownInterRepPart(void* p, CrPsSixteenBit_t Part)
{
   LptDownInterRep_t* t;
   t = (LptDownInterRep_t*)p;
   t->Part = Part;
}

/**
 * Get "Transid" from "LptDownLastRep" packet.
 * @param p Pointer to the packet.
 * @return Value of "Transid".
 */
static inline CrPsTransId_t getLptDownLastRepTransid(void* p)
{
   LptDownLastRep_t* t;
   t = (LptDownLastRep_t*)p;
   return t->Transid;
}

/**
 * Set "Transid" in "LptDownLastRep" packet.
 * @param p Pointer to the packet.
 * @param Transid Value of "Transid" to be set in packet.
 */
static inline void setLptDownLastRepTransid(void* p, CrPsTransId_t Transid)
{
   LptDownLastRep_t* t;
   t = (LptDownLastRep_t*)p;
   t->Transid = Transid;
}

/**
 * Get "PartSeqNmb" from "LptDownLastRep" packet.
 * @param p Pointer to the packet.
 * @return Value of "PartSeqNmb".
 */
static inline CrPsPartSeqNmb_t getLptDownLastRepPartSeqNmb(void* p)
{
   LptDownLastRep_t* t;
   t = (LptDownLastRep_t*)p;
   return t->PartSeqNmb;
}

/**
 * Set "PartSeqNmb" in "LptDownLastRep" packet.
 * @param p Pointer to the packet.
 * @param PartSeqNmb Value of "PartSeqNmb" to be set in packet.
 */
static inline void setLptDownLastRepPartSeqNmb(void* p, CrPsPartSeqNmb_t PartSeqNmb)
{
   LptDownLastRep_t* t;
   t = (LptDownLastRep_t*)p;
   t->PartSeqNmb = PartSeqNmb;
}

/**
 * Get "Part" from "LptDownLastRep" packet.
 * @param p Pointer to the packet.
 * @return Value of "Part".
 */
static inline CrPsSixteenBit_t getLptDownLastRepPart(void* p)
{
   LptDownLastRep_t* t;
   t = (LptDownLastRep_t*)p;
   return t->Part;
}

/**
 * Set "Part" in "LptDownLastRep" packet.
 * @param p Pointer to the packet.
 * @param Part Value of "Part" to be set in packet.
 */
static inline void setLptDownLastRepPart(void* p, CrPsSixteenBit_t Part)
{
   LptDownLastRep_t* t;
   t = (LptDownLastRep_t*)p;
   t->Part = Part;
}

/**
 * Get "Transid" from "LptUpFirstCmd" packet.
 * @param p Pointer to the packet.
 * @return Value of "Transid".
 */
static inline CrPsTransId_t getLptUpFirstCmdTransid(void* p)
{
   LptUpFirstCmd_t* t;
   t = (LptUpFirstCmd_t*)p;
   return t->Transid;
}

/**
 * Set "Transid" in "LptUpFirstCmd" packet.
 * @param p Pointer to the packet.
 * @param Transid Value of "Transid" to be set in packet.
 */
static inline void setLptUpFirstCmdTransid(void* p, CrPsTransId_t Transid)
{
   LptUpFirstCmd_t* t;
   t = (LptUpFirstCmd_t*)p;
   t->Transid = Transid;
}

/**
 * Get "PartSeqNmb" from "LptUpFirstCmd" packet.
 * @param p Pointer to the packet.
 * @return Value of "PartSeqNmb".
 */
static inline CrPsPartSeqNmb_t getLptUpFirstCmdPartSeqNmb(void* p)
{
   LptUpFirstCmd_t* t;
   t = (LptUpFirstCmd_t*)p;
   return t->PartSeqNmb;
}

/**
 * Set "PartSeqNmb" in "LptUpFirstCmd" packet.
 * @param p Pointer to the packet.
 * @param PartSeqNmb Value of "PartSeqNmb" to be set in packet.
 */
static inline void setLptUpFirstCmdPartSeqNmb(void* p, CrPsPartSeqNmb_t PartSeqNmb)
{
   LptUpFirstCmd_t* t;
   t = (LptUpFirstCmd_t*)p;
   t->PartSeqNmb = PartSeqNmb;
}

/**
 * Get "Part" from "LptUpFirstCmd" packet.
 * @param p Pointer to the packet.
 * @return Value of "Part".
 */
static inline CrPsSixteenBit_t getLptUpFirstCmdPart(void* p)
{
   LptUpFirstCmd_t* t;
   t = (LptUpFirstCmd_t*)p;
   return t->Part;
}

/**
 * Set "Part" in "LptUpFirstCmd" packet.
 * @param p Pointer to the packet.
 * @param Part Value of "Part" to be set in packet.
 */
static inline void setLptUpFirstCmdPart(void* p, CrPsSixteenBit_t Part)
{
   LptUpFirstCmd_t* t;
   t = (LptUpFirstCmd_t*)p;
   t->Part = Part;
}

/**
 * Get "Transid" from "LptUpInterCmd" packet.
 * @param p Pointer to the packet.
 * @return Value of "Transid".
 */
static inline CrPsTransId_t getLptUpInterCmdTransid(void* p)
{
   LptUpInterCmd_t* t;
   t = (LptUpInterCmd_t*)p;
   return t->Transid;
}

/**
 * Set "Transid" in "LptUpInterCmd" packet.
 * @param p Pointer to the packet.
 * @param Transid Value of "Transid" to be set in packet.
 */
static inline void setLptUpInterCmdTransid(void* p, CrPsTransId_t Transid)
{
   LptUpInterCmd_t* t;
   t = (LptUpInterCmd_t*)p;
   t->Transid = Transid;
}

/**
 * Get "PartSeqNmb" from "LptUpInterCmd" packet.
 * @param p Pointer to the packet.
 * @return Value of "PartSeqNmb".
 */
static inline CrPsPartSeqNmb_t getLptUpInterCmdPartSeqNmb(void* p)
{
   LptUpInterCmd_t* t;
   t = (LptUpInterCmd_t*)p;
   return t->PartSeqNmb;
}

/**
 * Set "PartSeqNmb" in "LptUpInterCmd" packet.
 * @param p Pointer to the packet.
 * @param PartSeqNmb Value of "PartSeqNmb" to be set in packet.
 */
static inline void setLptUpInterCmdPartSeqNmb(void* p, CrPsPartSeqNmb_t PartSeqNmb)
{
   LptUpInterCmd_t* t;
   t = (LptUpInterCmd_t*)p;
   t->PartSeqNmb = PartSeqNmb;
}

/**
 * Get "Part" from "LptUpInterCmd" packet.
 * @param p Pointer to the packet.
 * @return Value of "Part".
 */
static inline CrPsSixteenBit_t getLptUpInterCmdPart(void* p)
{
   LptUpInterCmd_t* t;
   t = (LptUpInterCmd_t*)p;
   return t->Part;
}

/**
 * Set "Part" in "LptUpInterCmd" packet.
 * @param p Pointer to the packet.
 * @param Part Value of "Part" to be set in packet.
 */
static inline void setLptUpInterCmdPart(void* p, CrPsSixteenBit_t Part)
{
   LptUpInterCmd_t* t;
   t = (LptUpInterCmd_t*)p;
   t->Part = Part;
}

/**
 * Get "Transid" from "LptUpLastCmd" packet.
 * @param p Pointer to the packet.
 * @return Value of "Transid".
 */
static inline CrPsTransId_t getLptUpLastCmdTransid(void* p)
{
   LptUpLastCmd_t* t;
   t = (LptUpLastCmd_t*)p;
   return t->Transid;
}

/**
 * Set "Transid" in "LptUpLastCmd" packet.
 * @param p Pointer to the packet.
 * @param Transid Value of "Transid" to be set in packet.
 */
static inline void setLptUpLastCmdTransid(void* p, CrPsTransId_t Transid)
{
   LptUpLastCmd_t* t;
   t = (LptUpLastCmd_t*)p;
   t->Transid = Transid;
}

/**
 * Get "PartSeqNmb" from "LptUpLastCmd" packet.
 * @param p Pointer to the packet.
 * @return Value of "PartSeqNmb".
 */
static inline CrPsPartSeqNmb_t getLptUpLastCmdPartSeqNmb(void* p)
{
   LptUpLastCmd_t* t;
   t = (LptUpLastCmd_t*)p;
   return t->PartSeqNmb;
}

/**
 * Set "PartSeqNmb" in "LptUpLastCmd" packet.
 * @param p Pointer to the packet.
 * @param PartSeqNmb Value of "PartSeqNmb" to be set in packet.
 */
static inline void setLptUpLastCmdPartSeqNmb(void* p, CrPsPartSeqNmb_t PartSeqNmb)
{
   LptUpLastCmd_t* t;
   t = (LptUpLastCmd_t*)p;
   t->PartSeqNmb = PartSeqNmb;
}

/**
 * Get "Part" from "LptUpLastCmd" packet.
 * @param p Pointer to the packet.
 * @return Value of "Part".
 */
static inline CrPsSixteenBit_t getLptUpLastCmdPart(void* p)
{
   LptUpLastCmd_t* t;
   t = (LptUpLastCmd_t*)p;
   return t->Part;
}

/**
 * Set "Part" in "LptUpLastCmd" packet.
 * @param p Pointer to the packet.
 * @param Part Value of "Part" to be set in packet.
 */
static inline void setLptUpLastCmdPart(void* p, CrPsSixteenBit_t Part)
{
   LptUpLastCmd_t* t;
   t = (LptUpLastCmd_t*)p;
   t->Part = Part;
}

/**
 * Get "Transid" from "LptUpAbortRep" packet.
 * @param p Pointer to the packet.
 * @return Value of "Transid".
 */
static inline CrPsTransId_t getLptUpAbortRepTransid(void* p)
{
   LptUpAbortRep_t* t;
   t = (LptUpAbortRep_t*)p;
   return t->Transid;
}

/**
 * Set "Transid" in "LptUpAbortRep" packet.
 * @param p Pointer to the packet.
 * @param Transid Value of "Transid" to be set in packet.
 */
static inline void setLptUpAbortRepTransid(void* p, CrPsTransId_t Transid)
{
   LptUpAbortRep_t* t;
   t = (LptUpAbortRep_t*)p;
   t->Transid = Transid;
}

/**
 * Get "FailReason" from "LptUpAbortRep" packet.
 * @param p Pointer to the packet.
 * @return Value of "FailReason".
 */
static inline CrPsFailReason_t getLptUpAbortRepFailReason(void* p)
{
   LptUpAbortRep_t* t;
   t = (LptUpAbortRep_t*)p;
   return t->FailReason;
}

/**
 * Set "FailReason" in "LptUpAbortRep" packet.
 * @param p Pointer to the packet.
 * @param FailReason Value of "FailReason" to be set in packet.
 */
static inline void setLptUpAbortRepFailReason(void* p, CrPsFailReason_t FailReason)
{
   LptUpAbortRep_t* t;
   t = (LptUpAbortRep_t*)p;
   t->FailReason = FailReason;
}

/**
 * Get "Transid" from "LptStartDownCmd" packet.
 * @param p Pointer to the packet.
 * @return Value of "Transid".
 */
static inline CrPsTransId_t getLptStartDownCmdTransid(void* p)
{
   LptStartDownCmd_t* t;
   t = (LptStartDownCmd_t*)p;
   return t->Transid;
}

/**
 * Set "Transid" in "LptStartDownCmd" packet.
 * @param p Pointer to the packet.
 * @param Transid Value of "Transid" to be set in packet.
 */
static inline void setLptStartDownCmdTransid(void* p, CrPsTransId_t Transid)
{
   LptStartDownCmd_t* t;
   t = (LptStartDownCmd_t*)p;
   t->Transid = Transid;
}

/**
 * Get "Transid" from "LptAbortDownCmd" packet.
 * @param p Pointer to the packet.
 * @return Value of "Transid".
 */
static inline CrPsTransId_t getLptAbortDownCmdTransid(void* p)
{
   LptAbortDownCmd_t* t;
   t = (LptAbortDownCmd_t*)p;
   return t->Transid;
}

/**
 * Set "Transid" in "LptAbortDownCmd" packet.
 * @param p Pointer to the packet.
 * @param Transid Value of "Transid" to be set in packet.
 */
static inline void setLptAbortDownCmdTransid(void* p, CrPsTransId_t Transid)
{
   LptAbortDownCmd_t* t;
   t = (LptAbortDownCmd_t*)p;
   t->Transid = Transid;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSPCKTLPT_H */
