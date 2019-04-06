/**
 * @file CrPsDataPoolFunc.c
 * @ingroup man_config
 *
 * Default implementation of the Data Pool Adaptation Points covering the
 * behaviour associated to the Data Pool State Machine.
 * This implementation is intended for use in the Test Suite of the
 * PUS Extension of the CORDET Framework.
 * Its chief characteristics are:
 * - No data pool refresh mechanism
 * - No data pool load mechanism
 * .
 * The functions in this module are called by the Data Pool State Machine
 * implemented in module CrPsDataPool.h.
 */

/** CrPsDataPool function definitions */
#include "DataPool/CrPsDataPool.h"

/** FW Profile function definitions */
#include "FwSmConstants.h"
#include "FwSmDCreate.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"


/* ----------------------------------------------------------------------------------------------------------------- */
/**
 *  Entry Action for the state LOADING.
 *  This function would normally start the Data Pool Loading Procedure which
 *  is responsible for loading new data in the data pool.
 *  This default implementation returns without doing anything.
 *  @param smDesc the data pool state machine descriptor
 */
void CrPsDataPoolStartLoading(FwSmDesc_t smDesc) {
  (void)smDesc;
  return;
}

/* ----------------------------------------------------------------------------------------------------------------- */
/**
 * Do Action for the state LOADING.
 * This function would normally execute the Data Pool Loading Procedure which
 * is responsible for loading new data in the data pool.
 * This default implementation returns without doing anything.
 * @param smDesc the data pool state machine descriptor
 */
void CrPsDataPoolContLoading(FwSmDesc_t smDesc) {
  (void)smDesc;
  return;
}

/* ----------------------------------------------------------------------------------------------------------------- */
/**
 * Action on the transition from READY to READY.
 * This function would normally refresh the data pool data items.
 * This default implementation returns without doing anything.
 *  @param smDesc the data pool state machine descriptor
 */
void CrPsDataPoolRefresh(FwSmDesc_t smDesc) {
  (void)smDesc;
  return;
}

/* ----------------------------------------------------------------------------------------------------------------- */
/**
 * Guard on the transition from LOADING to READY.
 * This function would normally return true if the Data Pool Loading Procedure
 * has terminated execution.
 * This default implementation returns true unconditionally.
 * @param smDesc the data pool state machine descriptor
 * @return true if the Data Pool Loading Procedure has terminated; false otherwise
 */
FwSmBool_t CrPsDataPoolHasLoadingTerm(FwSmDesc_t smDesc) {
  return 1;
}
