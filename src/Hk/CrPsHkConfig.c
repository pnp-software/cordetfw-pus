/**
 * @file
 *
 * Implementation of the configuration interface for the Housekeeping Service.
 *
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 *
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

#include "Hk/CrPsHkConfig.h"
#include "Pckt/CrPsPcktHk.h"
#include "CrPsTypes.h"
#include "CrPsServTypeId.h"
#include "CrFwUserConstants.h"
#include "CrPsConstants.h"

#include <assert.h>

/* The number of simply-commutated data items in the report */
static CrPsNPar_t nSimple[HK_N_REP_DEF];
/* List of super-commutated sample repetition numbers (rep[1] .. rep[nGroup]) */
static unsigned int lstSampleRep[HK_MAX_N_GR];
/* List of numbers nRep[1] .. nRep[nGroup] of data items in each super-commutated group */
static CrPsNPar_t lstNSampRep[HK_MAX_N_GR];
/* List of identifiers of data items in the report */
static CrPsNPar_t lstId[HK_N_REP_DEF][HK_MAX_N_ITEMS];



