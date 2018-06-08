/**
 * @file CrFwTime.c
 * @ingroup PUSTestsuite
 * @ingroup PUSTestconfig 
 *
 * Default implementation of the time interface of <code>CrFwTime.h</code>.
 * The implementation of this interface is one of the adaptation points of the
 * CORDET Framework.
 * This file provides a default implementation which is primarily intended to
 * support testing of the PUS Extension of the CORDET Framework.
 * It is expected that applications will provide their own implementation.
 * Application will therefore normally replace this file with their own file
 * providing their application-specific implementation.
 *
 * This implementation maintains a float which is initialized to 0 and is incremented
 * by 0.5 every time function <code>::CrFwGetCurrentTime</code> is called.
 * The time functions treat this float as the current time.
 *
 * The function <code>::CrFwGetCurrentCycTime</code> is implemented to return
 * the current time divided by 2 (i.e. it assumes that one "cycle" has a duration
 * of 0.5 seconds);
 *
 * The time type conversion functions have dummy implementations which always return zero.
 *
 * @author Christian Reimers <christian.reimers@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 *
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

#include <stdlib.h>
#include "CrFwConstants.h"
#include "CrFwTime.h"

#include <time.h>   /* for time()   */
#include <string.h> /* for memcpy() */

/** The <code>::CrFwGetCurrentTime</code> increments this counter and then returns its value */
CrFwTime_t curTime = 0;


/*-----------------------------------------------------------------------------------------*/
CrFwTime_t CrFwGetCurrentTime() {
	curTime = curTime + 0.5;
	return curTime;
}

/*-----------------------------------------------------------------------------------------*/
CrFwTimeStamp_t CrFwGetCurrentTimeStamp() {
  CrFwTimeStamp_t ts;
  unsigned int* curTimeSec;
  unsigned short* curTimeFrac;

  curTimeSec = &ts.t[0];
  curTimeFrac = &ts.t[4];

  curTimeSec = (unsigned int)curTime;
  curTimeFrac = (unsigned short)((curTime-curTimeSec)*65535);

  return ts;
}

/*-----------------------------------------------------------------------------------------*/
CrFwTimeCyc_t CrFwGetCurrentCycTime() {
	return (CrFwTimeCyc_t)(curTime/2);
}

/*-----------------------------------------------------------------------------------------*/
CrFwTimeStamp_t CrFwStdTimeToTimeStamp(CrFwTime_t stdTime) {
	return 0;
}

/*-----------------------------------------------------------------------------------------*/
CrFwTime_t CrFwTimeStampToStdTime(CrFwTimeStamp_t timeStamp) {
	return 0;
}


