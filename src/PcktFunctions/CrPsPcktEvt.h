/**
 * @file
 * @ingroup gen_pck
 *
 * Interface for accessing fields in packets of service "Evt".
 *
 * @note This file was generated on 2018-09-29 16:05:17
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSPCKTEVT_H_
#define CRPSPCKTEVT_H_

#include "CrPsTypes.h"

#include "CrPsPckt.h"
/**
 * Structure for Rep1
 */
typedef struct __attribute__((packed)) _Rep1_t {
   /**
    * Packet header.
    */
   TmHeader_t Header;

   /**
    * Event Identifier
    */
   CrPsEvtId_t EventId;
   
} Rep1_t ;

/**
 * Structure for Rep2
 */
typedef struct __attribute__((packed)) _Rep2_t {
   /**
    * Packet header.
    */
   TmHeader_t Header;

   /**
    * Event Identifier
    */
   CrPsEvtId_t EventId;
   
} Rep2_t ;

/**
 * Structure for Rep3
 */
typedef struct __attribute__((packed)) _Rep3_t {
   /**
    * Packet header.
    */
   TmHeader_t Header;

   /**
    * Event Identifier
    */
   CrPsEvtId_t EventId;
   
} Rep3_t ;

/**
 * Structure for Rep4
 */
typedef struct __attribute__((packed)) _Rep4_t {
   /**
    * Packet header.
    */
   TmHeader_t Header;

   /**
    * Event Identifier
    */
   CrPsEvtId_t EventId;
   
} Rep4_t ;

/**
 * Structure for EnbId
 */
typedef struct __attribute__((packed)) _EnbId_t {
   /**
    * Packet header.
    */
   TcHeader_t Header;

   /**
    * The number of event identifiers to be enabled
    */
   CrPsNEvtId_t N;
   
   struct __attribute__((packed)) {
      /**
       * Event identifier to be enabled
       */
      CrPsEvtId_t EventId;
      
   } N_[0];
} EnbId_t ;

/**
 * Structure for DisIdCmd
 */
typedef struct __attribute__((packed)) _DisIdCmd_t {
   /**
    * Packet header.
    */
   TcHeader_t Header;

   /**
    * The number of event identifiers to be disabled
    */
   CrPsNEvtId_t N;
   
   struct __attribute__((packed)) {
      /**
       * Event identifier to be disabled
       */
      CrPsEvtId_t EventId;
      
   } N_[0];
} DisIdCmd_t ;

/**
 * Structure for RepDisIdCmd
 */
typedef struct __attribute__((packed)) _RepDisIdCmd_t {
   /**
    * Packet header.
    */
   TcHeader_t Header;

} RepDisIdCmd_t ;

/**
 * Structure for DisIdRep
 */
typedef struct __attribute__((packed)) _DisIdRep_t {
   /**
    * Packet header.
    */
   TmHeader_t Header;

   /**
    * The number of disabled event identifiers
    */
   CrPsNEvtId_t N;
   
   struct __attribute__((packed)) {
      /**
       * Event Identifier
       */
      CrPsEvtId_t EventId;
      
   } N_[0];
} DisIdRep_t ;

/**
 * Get "EventId" from "Rep1" packet.
 * @param p Pointer to the packet.
 * @return Value of "EventId".
 */
static inline CrPsEvtId_t getEvtRep1EventId(void* p) {
   Rep1_t* t;
   t = (Rep1_t*)p;
   return __builtin_bswap16(t->EventId);
}

/**
 * Set "EventId" in "Rep1" packet.
 * @param p Pointer to the packet.
 * @param EventId Value of "EventId" to be set in packet.
 */
static inline void setEvtRep1EventId(void* p, CrPsEvtId_t EventId) {
   Rep1_t* t;
   t = (Rep1_t*)p;
   t->EventId = __builtin_bswap16(EventId);
}

/**
 * Get "EventId" from "Rep2" packet.
 * @param p Pointer to the packet.
 * @return Value of "EventId".
 */
static inline CrPsEvtId_t getEvtRep2EventId(void* p) {
   Rep2_t* t;
   t = (Rep2_t*)p;
   return __builtin_bswap16(t->EventId);
}

/**
 * Set "EventId" in "Rep2" packet.
 * @param p Pointer to the packet.
 * @param EventId Value of "EventId" to be set in packet.
 */
static inline void setEvtRep2EventId(void* p, CrPsEvtId_t EventId) {
   Rep2_t* t;
   t = (Rep2_t*)p;
   t->EventId = __builtin_bswap16(EventId);
}

/**
 * Get "EventId" from "Rep3" packet.
 * @param p Pointer to the packet.
 * @return Value of "EventId".
 */
static inline CrPsEvtId_t getEvtRep3EventId(void* p) {
   Rep3_t* t;
   t = (Rep3_t*)p;
   return __builtin_bswap16(t->EventId);
}

/**
 * Set "EventId" in "Rep3" packet.
 * @param p Pointer to the packet.
 * @param EventId Value of "EventId" to be set in packet.
 */
static inline void setEvtRep3EventId(void* p, CrPsEvtId_t EventId) {
   Rep3_t* t;
   t = (Rep3_t*)p;
   t->EventId = __builtin_bswap16(EventId);
}

/**
 * Get "EventId" from "Rep4" packet.
 * @param p Pointer to the packet.
 * @return Value of "EventId".
 */
static inline CrPsEvtId_t getEvtRep4EventId(void* p) {
   Rep4_t* t;
   t = (Rep4_t*)p;
   return __builtin_bswap16(t->EventId);
}

/**
 * Set "EventId" in "Rep4" packet.
 * @param p Pointer to the packet.
 * @param EventId Value of "EventId" to be set in packet.
 */
static inline void setEvtRep4EventId(void* p, CrPsEvtId_t EventId) {
   Rep4_t* t;
   t = (Rep4_t*)p;
   t->EventId = __builtin_bswap16(EventId);
}

/**
 * Get "N" from "EnbId" packet.
 * @param p Pointer to the packet.
 * @return Value of "N".
 */
static inline CrPsNEvtId_t getEvtEnbIdN(void* p) {
   EnbId_t* t;
   t = (EnbId_t*)p;
   return t->N;
}

/**
 * Set "N" in "EnbId" packet.
 * @param p Pointer to the packet.
 * @param N Value of "N" to be set in packet.
 */
static inline void setEvtEnbIdN(void* p, CrPsNEvtId_t N) {
   EnbId_t* t;
   t = (EnbId_t*)p;
   t->N = N;
}

/**
 * Get pointer to "EventId" array from "EnbId" packet.
 * @param p Pointer to the packet.
 * @return Pointer to the start of the EventId array.
 */
static inline CrPsEvtId_t* getEvtEnbIdEventIdArray(void* p) {
   EnbId_t* t;
   t = (EnbId_t*)p;
   return &t->N_[0].EventId;
}

/**
 * Get "EventId" array from "EnbId" packet.
 * @param p Pointer to the packet.
 * @param dest Pointer to memory location where array data are copied to.
 */
static inline void readEvtEnbIdEventIdArray(void* p, void* dest) {
   EnbId_t* t;
   t = (EnbId_t*)p;
   memcpy(dest, &t->N_[0].EventId, t->N*sizeof(t->N_[0].EventId));
}

/**
 * Set "EventId" array in "EnbId" packet.
 * @param p Pointer to the packet.
 * @param src Pointer to memory location from where array data are copied.
 */
static inline void writeEvtEnbIdEventIdArray(void* p, const void* src) {
   EnbId_t* t;
   t = (EnbId_t*)p;
   memcpy(&t->N_[0].EventId, src, t->N*sizeof(t->N_[0].EventId));
}

/**
 * Get "EventId" from "EnbId" packet.
 * @param p Pointer to the packet.
 * @param N
 * @return Value of "EventId".
 */
static inline CrPsEvtId_t getEvtEnbIdEventId(void* p, CrPsNEvtId_t N) {
   EnbId_t* t;
   t = (EnbId_t*)p;
   return __builtin_bswap16(t->N_[N].EventId);
}

/**
 * Set "EventId" in "EnbId" packet.
 * @param p Pointer to the packet.
 * @param N
 * @param EventId Value of "EventId" to be set in packet.
 */
static inline void setEvtEnbIdEventId(void* p, CrPsNEvtId_t N, CrPsEvtId_t EventId) {
   EnbId_t* t;
   t = (EnbId_t*)p;
   t->N_[N].EventId = __builtin_bswap16(EventId);
}

/**
 * Get "N" from "DisIdCmd" packet.
 * @param p Pointer to the packet.
 * @return Value of "N".
 */
static inline CrPsNEvtId_t getEvtDisIdCmdN(void* p) {
   DisIdCmd_t* t;
   t = (DisIdCmd_t*)p;
   return t->N;
}

/**
 * Set "N" in "DisIdCmd" packet.
 * @param p Pointer to the packet.
 * @param N Value of "N" to be set in packet.
 */
static inline void setEvtDisIdCmdN(void* p, CrPsNEvtId_t N) {
   DisIdCmd_t* t;
   t = (DisIdCmd_t*)p;
   t->N = N;
}

/**
 * Get pointer to "EventId" array from "DisIdCmd" packet.
 * @param p Pointer to the packet.
 * @return Pointer to the start of the EventId array.
 */
static inline CrPsEvtId_t* getEvtDisIdCmdEventIdArray(void* p) {
   DisIdCmd_t* t;
   t = (DisIdCmd_t*)p;
   return &t->N_[0].EventId;
}

/**
 * Get "EventId" array from "DisIdCmd" packet.
 * @param p Pointer to the packet.
 * @param dest Pointer to memory location where array data are copied to.
 */
static inline void readEvtDisIdCmdEventIdArray(void* p, void* dest) {
   DisIdCmd_t* t;
   t = (DisIdCmd_t*)p;
   memcpy(dest, &t->N_[0].EventId, t->N*sizeof(t->N_[0].EventId));
}

/**
 * Set "EventId" array in "DisIdCmd" packet.
 * @param p Pointer to the packet.
 * @param src Pointer to memory location from where array data are copied.
 */
static inline void writeEvtDisIdCmdEventIdArray(void* p, const void* src) {
   DisIdCmd_t* t;
   t = (DisIdCmd_t*)p;
   memcpy(&t->N_[0].EventId, src, t->N*sizeof(t->N_[0].EventId));
}

/**
 * Get "EventId" from "DisIdCmd" packet.
 * @param p Pointer to the packet.
 * @param N
 * @return Value of "EventId".
 */
static inline CrPsEvtId_t getEvtDisIdCmdEventId(void* p, CrPsNEvtId_t N) {
   DisIdCmd_t* t;
   t = (DisIdCmd_t*)p;
   return __builtin_bswap16(t->N_[N].EventId);
}

/**
 * Set "EventId" in "DisIdCmd" packet.
 * @param p Pointer to the packet.
 * @param N
 * @param EventId Value of "EventId" to be set in packet.
 */
static inline void setEvtDisIdCmdEventId(void* p, CrPsNEvtId_t N, CrPsEvtId_t EventId) {
   DisIdCmd_t* t;
   t = (DisIdCmd_t*)p;
   t->N_[N].EventId = __builtin_bswap16(EventId);
}

/**
 * Get "N" from "DisIdRep" packet.
 * @param p Pointer to the packet.
 * @return Value of "N".
 */
static inline CrPsNEvtId_t getEvtDisIdRepN(void* p) {
   DisIdRep_t* t;
   t = (DisIdRep_t*)p;
   return t->N;
}

/**
 * Set "N" in "DisIdRep" packet.
 * @param p Pointer to the packet.
 * @param N Value of "N" to be set in packet.
 */
static inline void setEvtDisIdRepN(void* p, CrPsNEvtId_t N) {
   DisIdRep_t* t;
   t = (DisIdRep_t*)p;
   t->N = N;
}

/**
 * Get pointer to "EventId" array from "DisIdRep" packet.
 * @param p Pointer to the packet.
 * @return Pointer to the start of the EventId array.
 */
static inline CrPsEvtId_t* getEvtDisIdRepEventIdArray(void* p) {
   DisIdRep_t* t;
   t = (DisIdRep_t*)p;
   return &t->N_[0].EventId;
}

/**
 * Get "EventId" array from "DisIdRep" packet.
 * @param p Pointer to the packet.
 * @param dest Pointer to memory location where array data are copied to.
 */
static inline void readEvtDisIdRepEventIdArray(void* p, void* dest) {
   DisIdRep_t* t;
   t = (DisIdRep_t*)p;
   memcpy(dest, &t->N_[0].EventId, t->N*sizeof(t->N_[0].EventId));
}

/**
 * Set "EventId" array in "DisIdRep" packet.
 * @param p Pointer to the packet.
 * @param src Pointer to memory location from where array data are copied.
 */
static inline void writeEvtDisIdRepEventIdArray(void* p, const void* src) {
   DisIdRep_t* t;
   t = (DisIdRep_t*)p;
   memcpy(&t->N_[0].EventId, src, t->N*sizeof(t->N_[0].EventId));
}

/**
 * Get "EventId" from "DisIdRep" packet.
 * @param p Pointer to the packet.
 * @param N
 * @return Value of "EventId".
 */
static inline CrPsEvtId_t getEvtDisIdRepEventId(void* p, CrPsNEvtId_t N) {
   DisIdRep_t* t;
   t = (DisIdRep_t*)p;
   return __builtin_bswap16(t->N_[N].EventId);
}

/**
 * Set "EventId" in "DisIdRep" packet.
 * @param p Pointer to the packet.
 * @param N
 * @param EventId Value of "EventId" to be set in packet.
 */
static inline void setEvtDisIdRepEventId(void* p, CrPsNEvtId_t N, CrPsEvtId_t EventId) {
   DisIdRep_t* t;
   t = (DisIdRep_t*)p;
   t->N_[N].EventId = __builtin_bswap16(EventId);
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSPCKTEVT_H */
