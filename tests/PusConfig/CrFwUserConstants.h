/**
 * @file CrFwUserConstants.h
 * @ingroup man_config
 *
 * Header file to define all user-configurable constants and types for the CORDET
 * Framework (the non-configurable constants and types are defined in
 * <code>CrFwConstants.h</code>).
 *
 * This header file was created by starting from the homonymous file provided by the
 * CORDET Framework and adding to it items required for its PUS Extension.
 * This version of the <code>CrFwUserConstants</code> is intended for the Test Suite
 * Application of the PUS Extension of the CORDET Framework.
 *
 * @author Christian Reimers <christian.reimers@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#ifndef CRFW_USERCONSTANTS_H_
#define CRFW_USERCONSTANTS_H_

#include "FwPrConstants.h"
#include <string.h>				/* Required for memcpy */

/** Macro required in generated code for command and report stubs */
#define DBG(x) (void)(x);

/** Type used for instance identifiers. */
typedef unsigned short CrFwInstanceId_t;

/** Type used for the identifier of a component type. */
typedef unsigned short int CrFwTypeId_t;

/** Type used for the outcome of a check (see <code>::CrFwCmpData</code>). */
typedef unsigned char CrFwOutcome_t;

/** Type used for the sequence counter of commands or reports. */
typedef unsigned int CrFwSeqCnt_t;

/** Type used for the service type of a command or report. */
typedef unsigned char CrFwServType_t;

/** Type used for the command or report sub-type. */
typedef unsigned char CrFwServSubType_t;

/** Type used for the destination or source group of a packet. */
typedef unsigned char CrFwGroup_t;

/** Type used for the command or report destination and source. */
typedef unsigned char CrFwDestSrc_t;

/** Type for the TM/TC crc. The length of the crc is 16bits. */
typedef unsigned short CrFwCrc_t;

/** Type used for the discriminant of a command or report. */
typedef unsigned short CrFwDiscriminant_t;

/** Type for the index used to track the state of a component. */
typedef unsigned short CrFwTrackingIndex_t;

/** Type for the index of a command or report kind. */
typedef unsigned short CrFwCmdRepKindIndex_t;

/** Type for the component kind key in <code>CrFwInFactory.c</code> and <code>CrFwOutFactory.c</code>. */
typedef unsigned int CrFwCmdRepKindKey_t;

/** Type for the Progress Step Identifier of an InCommand */
typedef unsigned short CrFwProgressStepId_t;

/** Type for the counter of execution progress steps */
typedef unsigned short CrFwExecStepId_t;

/**
 * Type for the index in the pool of pre-allocated OutComponents in
 * the OutFactory (see <code>CrFwOutFactory.h</code>).
 */
typedef unsigned char CrFwOutFactoryPoolIndex_t;

/**
 * Type for the index in the pool of pre-allocated incoming components in
 * the InFactory (see <code>CrFwInFactory.h</code>).
 */
typedef unsigned char CrFwInFactoryPoolIndex_t;

/** Type used for unsigned integers with a "short" range. */
typedef unsigned char CrFwCounterU1_t;

/** Type used for signed integers with a "short" range. */
typedef signed char CrFwCounterS1_t;

/** Type used for unsigned integers with a "medium" range. */
typedef unsigned short CrFwCounterU2_t;

/** Type for the packet length. */
typedef unsigned short int CrFwPcktLength_t;

/** Type for the TM/TC version number. The length of the version is 3 bits. */
typedef unsigned char CrFwPcktVersion_t;

/**
 * Type for the TC sequence flags and TM segmentation flags. The length of the
 * flags is 2 bits.
 */
typedef unsigned char CrFwPcktSeqFlags_t;

/** Type used for the application time. */
typedef float CrFwTime_t;

/** Type used for the number of elapsed cycles.
 * Many applications operate on a cyclical basis and this
 * type is used for the number of elapsed execution cycles. */
typedef unsigned int CrFwTimeCyc_t;

/** Type used for the time stamp of a command or report. */
typedef struct CrFwTimeStamp {
  /** The time stamp as a six-byte array */
  unsigned char t[6];
} CrFwTimeStamp_t;

/**
 * Type for the value of a generic data pool item of primitive type or of a generic
 * TM/TC parameter of primitive type.
 * This type is primarily aimed at service 12 which needs to manipulate generic
 * values of undefined type.
 * The type is defined as a union of float, signed and unsigned integer.
 * @constraint Only parameters fitting within one of the types encompassed by the
 * #CrFwGenericParVal_t union may be subjcted to service 12 monitoring
 */
typedef union CrFwGenericParVal {
  /** A float value */
  float floatVal;
  /** An unsigned integer value */
  unsigned int uintVal;
  /** A signed integer value */
  int intVal;
} CrFwGenericParVal_t;

/** Type used in the files generated by the CORDET Editor */
typedef unsigned char uint8_t;

/** Type used in the files generated by the CORDET Editor */
typedef unsigned short uint16_t;

/** Type used in the files generated by the CORDET Editor */
typedef unsigned int uint32_t;

/** Type used in the files generated by the CORDET Editor */
typedef int int32_t;

/**
 * Identifier for the errors reported through the error reporting interface of <code>CrFwRepErr.h</code>.
 * When a framework component encounters a non-nominal situation during its normal operation,
 * it reports it as an error using the services defined by the <code>CrFwRepErr.h</code>
 * interface.
 * Each error situation is characterized by an error code.
 * This enumerated type defines all the error codes.
 *
 * The error report codes starting with "cr" were defined at CORDET Framework Level.
 * The error report codes starting with "ps" have been defined for the PUS Extension of the CORDET Framework.
 */
typedef enum {
	/** The packet queue of an OutStream is full (see <code>CrFwOutStream.h</code>) */
	crOutStreamPQFull =2,
	/** The packet queue of an InStream is full (see <code>CrFwInStream.h</code>) */
	crInStreamPQFull =3,
	/** An InStream has encountered a sequence counter error (see <code>CrFwInStream.h</code>) */
	crInStreamSCErr =4,
	/** An OutComponent has an invalid destination (see <code>CrFwOutCmp.h</code>) */
	crOutCmpSendPcktInvDest =5,
	/** The Pending OutComponent List (POCL) of an OutManager is full (see <code>CrFwOutManager.h</code>) */
	crOutManagerPoclFull =6,
	/** The Pending Command/Report List (PCRL) of an InManager is full (see <code>CrFwInManager.h</code>) */
	crInManagerPcrlFull =7,
	/** The InLoader has retrieved a packet with an invalid destination (see <code>CrFwInLoader.h</code>) */
	crInLoaderInvDest = 8,
	/** An InReport or InCommand has failed its acceptance check */
	crInLoaderAccFail = 9,
	/** An OutComponent has an illegal group */
	crOutStreamIllGroup = 10,
	/** An incoming command or report has an illegal group */
	crInStreamIllGroup = 11,
	/** An OutStream cannot buffer an out-going packet because no more packets are available (see <code>CrFwOutStream.h</code>) */
	crOutStreamNoMorePckt =12,
	/** An InReport cannot be created **/
	crInLoaderCreFail = 13,
	/** An InReport cannot be loaded in its InManager **/
	crInLoaderLdFail = 14,
	/** An attempt to create an OutComponent failed */
	psOutFactoryFail = 202
} CrFwRepErrCode_t;

/**
 * Application error code for the framework components.
 * An application error is declared when a framework function has been called by the
 * application code with an illegal parameter values or in an illegal context and execution
 * of the function with the illegal values would cause an internal framework data structure
 * to be corrupted.
 *
 * Nominally, the application error code should be equal to: <code>::crNoAppErr</code>.
 * If the application error code has a different value, then an application error has been
 * encountered.
 * If multiple errors have been encountered, the application error code reflects the
 * most recent error.
 *
 * Users may need to extend this type with additional application error codes to cover
 * application-specific error situations.
 */
typedef enum {
	/** No application errors have been detected. */
	crNoAppErr = 0,
	/** An OutStream function was called on an object which is not an OutStream. */
	crNotOutStream = 1,
	/** A framework function has been called with an illegal OutStream identifier. */
	crOutStreamIllId = 2,
	/**
	 * A framework function has been called with a destination attribute which is not
	 * associated to any OutStream.
	 */
	crOutStreamUndefDest = 3,
	/**
	 * A framework function has been called with a source attribute which is not
	 * associated to any InStream.
	 */
	crInStreamUndefDest = 4,
	/** A packet allocation request has failed (see <code>::CrFwPcktMake</code>). */
	crPcktAllocationFail = 5,
	/** A packet release request has encountered an error (see <code>::CrFwPcktRelease</code>). */
	crPcktRelErr = 6,
	/** An InStream function was called on an object which is not an InStream. */
	crNotInStream = 7,
	/** A framework function has been called with an illegal InStream identifier. */
	crInStreamIllId = 8,
	/** An OutComponent function was called on an object which is not an OutComponent. */
	crNotOutCmp = 9,
	/** An OutComponent allocation request has failed (see <code>::CrFwOutFactoryMakeOutCmp</code>). */
	crOutCmpAllocationFail = 10,
	/** An OutComponent release request has encountered an error (see <code>::CrFwOutFactoryReleaseOutCmp</code>). */
	crOutCmpRelErr = 11,
	/** A framework function was called with an illegal service type */
	crIllServType = 12,
	/** A framework function was called with an illegal service sub-type */
	crIllServSubType = 13,
	/** A framework function was called with an illegal discriminant */
	crIllDiscriminant = 14,
	/** A framework function was called with an illegal type/sub-type pair for an OutComponent */
	crIllOutCmpType = 15,
	/** A framework function was called with an illegal type/sub-type/discriminant triplet for an OutComponent */
	crIllOutCmpKind = 16,
	/** A framework function has been called with an illegal OutManager identifier. */
	crOutManagerIllId = 17,
	/** A framework function was called with an illegal type/sub-type/discriminant triplet for an InCommand */
	crIllInCmdKind = 18,
	/** Allocation request for a packet for an InCommand has failed (see <code>::CrFwInFactoryMakeInCmd</code>). */
	crInCmdAllocationFail = 19,
	/** A framework function was called with an illegal type/sub-type/discriminant triplet for an InReport */
	crIllInRepKind = 20,
	/** Allocation request for an InReport has failed (see <code>::CrFwInFactoryMakeInRep</code>). */
	crInRepAllocationFail = 21,
	/** An InReport release request has encountered an error (see <code>::CrFwInFactoryReleaseInRep</code>). */
	crInRepRelErr = 22,
	/** An InCommand release request has encountered an error (see <code>::CrFwInFactoryReleaseInCmd</code>). */
	crInCmdRelErr = 23,
	/** A framework function has been called with an illegal InManager identifier. */
	crInManagerIllId = 24,
	/** An illegal event severity level has been encountered */
	CrPsEvtIllSevLevel = 128,
	/** An illegal event identifier has been encountered */
	crPsEvtIllEvtId = 130,
	/** The number of (5,8) reports triggered by a (5.7) command is larger than EVT_MAX_N5S8 */
	crPsIllNOf5s8 = 131,
	/** The range of data pool identifiers for data pool parameters and data pool variables overlap */
	crPsDpParVarIdOverlap = 132,
	/** Illegal size for real-valued monitored parameter (see <code>::CrPsMonConfigOutOfLimitCheckR</code>). */
	CrPsIllRMonParSize = 133,
    /** Illegal size for signed integer-valued monitored parameter (see <code>::CrPsMonConfigOutOfLimitCheckSI</code>). */
	CrPsIllSIMonParSize = 134,
    /** Illegal size for unsigned integer-valued monitored parameter (see <code>::CrPsMonConfigOutOfLimitCheckUI</code>). */
    CrPsIllUIMonParSize = 135
} CrFwAppErrCode_t;

/**
 * Maximum number of packets simultaneously supported by the packet factory */
#define CR_FW_MAX_NOF_PCKTS 255

/** The maximum length of a packet in bytes */
#define CR_FW_MAX_PCKT_LENGTH 128

/** The identifier of the host application */
#define CR_FW_HOST_APP_ID 10

/** The number of bits reserved for the application identifier in a command or report identifier */
#define CR_FW_NBITS_APP_ID 11

/** Maximum value of the service type attribute of InReports and InCommands */
#define CR_FW_MAX_SERV_TYPE 255

/** Maximum value of the service sub-type attribute of InReports and InCommands */
#define CR_FW_MAX_SERV_SUBTYPE 255

/** Maximum value of the discriminant attribute of InReports and InCommands */
#define CR_FW_MAX_DISCRIMINANT 255

#endif /* CRFW_USERCONSTANTS_H_ */
