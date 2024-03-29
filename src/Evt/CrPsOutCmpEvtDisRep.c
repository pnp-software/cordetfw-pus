/**
 * @file
 * @ingroup man_evt
 *
 * Implementation of TM(5,8) EvtDisRep as an out-going report.
 * The header file for this implementation file (CrPsOutCmpEvtDisRep.h) was
 * generated by the CORDET Editor.
 */

#include "CrPsOutCmpEvtDisRep.h"
#include "DataPool/CrPsDp.h"
#include "DataPool/CrPsDpEvt.h"
#include "Evt/CrPsEvtConfig.h"
#include "Pckt/CrPsPckt.h"
#include "Pckt/CrPsPcktEvt.h"
#include "CrPsConstants.h"
#include "CrPsServTypeId.h"

#include "CrFwUserConstants.h"
#include "OutCmp/CrFwOutCmp.h"
#include "InCmd/CrFwInCmd.h"
#include "OutFactory/CrFwOutFactory.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include <assert.h>

void CrPsOutCmpEvtDisRepUpdateAction(FwSmDesc_t smDesc) {
  unsigned int nEvtEid;
  CrPsEvtId_t eid;
  size_t sizeOfEvtId, sizeOfEvtN, sizeOfHeader, sizeOfCrc;
  CrFwPckt_t res5s8Pckt;
  CrPsNEvtId_t i;

  /* Compute the number of event identifiers to be stored in this report */
  sizeOfEvtId = getDpSize(DpIdlastEvtEid)/4;
  sizeOfEvtN = getDpSize(DpIdnOfDisabledEid)/4;
  sizeOfHeader = sizeof(TmHeader_t);
  sizeOfCrc = sizeof(CrFwCrc_t);
  nEvtEid = (CrFwOutCmpGetLength(smDesc) - sizeOfHeader - sizeOfEvtN - sizeOfCrc)/sizeOfEvtId;

  /* Populate the (5,8) report */
  res5s8Pckt = CrFwOutCmpGetPckt(smDesc);

  setEvtDisRepN(res5s8Pckt, nEvtEid);

  for (i=0; i<nEvtEid; i++) {
      CrPsEvtConfigIter(&eid);
      setEvtDisRepEventId(res5s8Pckt, i, eid);
      assert(eid != 0);
  }
}
