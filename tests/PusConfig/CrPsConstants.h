/**
 * @file
 * @ingroup gen_cfw
 *
 * Constant definitions.
 *
 * @note This file was generated on 2018-07-10 23:14:14
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRPSCONSTANTS_H_
#define CRPSCONSTANTS_H_

/**
 * Definition of constant "MON_PER".
 * Minimum monitoring period
 */
#define MON_PER (1)
/**
 * Definition of constant "HK_MAX_N_ITEMS".
 * Maximum number of data items in a housekeeping/diagnostic report
 */
#define HK_MAX_N_ITEMS (1)
/**
 * Definition of constant "SCD_N_GROUP".
 * Number of time-based schedule groups
 */
#define SCD_N_GROUP (1)
/**
 * Definition of constant "MON_N_FMON".
 * Maximum number of entries in the Functional Monitoring Definition List FMDL
 * (maximum number of functional monitors in the application)
 */
#define MON_N_FMON (1)
/**
 * Definition of constant "MON_N_PMON".
 * Maximum number of entries in the Parameter Monitoring Definition List PMDL
 * (maximum number of parameter monitors in the application)
 */
#define MON_N_PMON (1)
/**
 * Definition of constant "HK_N_SAMP_BUF".
 * Number of service 3 Sampling Buffers
 */
#define HK_N_SAMP_BUF (1)
/**
 * Definition of constant "MON_N_EXP".
 * Maximum number of parameter monitors with an expected value check
 */
#define MON_N_EXP (1)
/**
 * Definition of constant "HK_MAX_SID".
 * Maximum value of a service 3 Structure Identifier (SID)
 */
#define HK_MAX_SID (1)
/**
 * Definition of constant "MON_N_LIM".
 * Maximum number of parameter monitors with a limit check
 */
#define MON_N_LIM (1)
/**
 * Definition of constant "LPT_N_BUF".
 * Number of Large Packet Transfer Buffers available for down-or up-transfer
 * of large packets
 */
#define LPT_N_BUF (1)
/**
 * Definition of constant "HK_MAX_N_REP".
 * Maximum number of data items in a super-commutated groups in a
 * housekeeping/diagnostic report
 */
#define HK_MAX_N_REP (1)
/**
 * Definition of constant "HK_N_DEBUG_VAR".
 * Number of debug variables
 */
#define HK_N_DEBUG_VAR (1)
/**
 * Definition of constant "HK_N_REP_DEF".
 * Number of Report Definitions in the Report Definition List (maximum number
 * of housekeeping/diagnostic reports)
 */
#define HK_N_REP_DEF (1)
/**
 * Definition of constant "MON_N_CLST".
 * Maximum number of entries in the Check Transition List
 */
#define MON_N_CLST (1)
/**
 * Definition of constant "MON_NFPMON".
 * Maximum number of functional monitors to which the same parameter monitor
 * may belong
 */
#define MON_NFPMON (1)
/**
 * Definition of constant "HK_MAX_ID".
 * Maximum value of a data pool item identifier
 */
#define HK_MAX_ID (1)
/**
 * Definition of constant "SCD_N_TBA".
 * Number of time-based scheduled activities
 */
#define SCD_N_TBA (1)
/**
 * Definition of constant "TST_N_DEST".
 * Number of destinations managed by test service
 */
#define TST_N_DEST (4)
/**
 * Definition of constant "EVT_N_ID".
 * Number of event identifiers supported by the application
 */
#define EVT_N_ID (1)
/**
 * Definition of constant "HK_MAX_N_GR".
 * Maximum number of super-commutated groups in a housekeeping/diagnostic
 * report
 */
#define HK_MAX_N_GR (1)
/**
 * Definition of constant "HK_COLLECT_PER".
 * Minimum collection period for service 3 reports
 */
#define HK_COLLECT_PER (1)
/**
 * Definition of constant "MON_N_DEL".
 * Maximum number of parameter monitors with a delta value check
 */
#define MON_N_DEL (1)
/**
 * Definition of constant "MON_N_PFMON".
 * Maximum number of parameter monitors in a functional monitor
 */
#define MON_N_PFMON (1)
/**
 * Definition of constant "HK_MAX_REP".
 * Maximum value of the repetition number of a super-commutated group in a
 * housekeeping/diagnostic report
 */
#define HK_MAX_REP (1)
/**
 * Definition of constant "SCD_N_SUB_TBS".
 * Number of time-based sub-schedules
 */
#define SCD_N_SUB_TBS (1)
/**
 * Definition of constant "HK_MAX_N_SIMPLE".
 * Maximum number of simply-commutated parameters in a housekeeping or
 * diagnostic report
 */
#define HK_MAX_N_SIMPLE (1)
/**
 * Definition of constant "MON_FPER".
 * Period of execution of the Functional Monitoring Procedure expressed as a
 * multiple of MON_PER
 */
#define MON_FPER (1)

/*----------------------------------------------------------------------------*/
#endif /* CRPSCONSTANTS_H */
