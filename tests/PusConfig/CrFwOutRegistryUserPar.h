/**
 * @file
 * @ingroup gen_cfw
 *
 * This file is part of the PUS Extension of the CORDET Framework.
 *
 * @note This file was generated on 2018-07-25 18:43:06
 * @author Automatically Generated by CORDET Editor
 * @copyright P&P Software GmbH
 */
#ifndef CRFWOUTREGISTRYUSERPAR_H_
#define CRFWOUTREGISTRYUSERPAR_H_

#include "CrPsConstants.h"

/**
 * The total number of service types/sub-types provided by the application.
 */
#define CR_FW_OUTREGISTRY_NSERV (31)

/**
 * The maximum number of out-going commands or reports which can be tracked by
 * the OutRegistry.
 */
#define CR_FW_OUTREGISTRY_N (60)

/**
 * Definition of the range of out-going services supported by an application.
 */
#define CR_FW_OUTREGISTRY_INIT_SERV_DESC { \
   {1, 1, 0, 0, 0, 0, 0}, \
   {1, 2, 0, 0, 0, 0, 0}, \
   {1, 3, 0, 0, 0, 0, 0}, \
   {1, 4, 0, 0, 0, 0, 0}, \
   {1, 5, 0, 0, 0, 0, 0}, \
   {1, 6, 0, 0, 0, 0, 0}, \
   {1, 7, 0, 0, 0, 0, 0}, \
   {1, 8, 0, 0, 0, 0, 0}, \
   {1, 10, 0, 0, 0, 0, 0}, \
   {3, 10, 0, 0, 0, 0, 0}, \
   {3, 12, 0, 0, 0, 0, 0}, \
   {3, 25, 0, 0, 0, 0, 0}, \
   {3, 26, 0, 0, 0, 0, 0}, \
   {5, 1, 0, 0, 0, 0, 0}, \
   {5, 2, 0, 0, 0, 0, 0}, \
   {5, 3, 0, 0, 0, 0, 0}, \
   {5, 4, 0, 0, 0, 0, 0}, \
   {5, 8, 0, 0, 0, 0, 0}, \
   {11, 27, 0, 0, 0, 0, 0}, \
   {12, 9, 0, 0, 0, 0, 0}, \
   {12, 11, 0, 0, 0, 0, 0}, \
   {12, 12, 0, 0, 0, 0, 0}, \
   {12, 14, 0, 0, 0, 0, 0}, \
   {12, 26, 0, 0, 0, 0, 0}, \
   {12, 28, 0, 0, 0, 0, 0}, \
   {13, 1, 0, 0, 0, 0, 0}, \
   {13, 2, 0, 0, 0, 0, 0}, \
   {13, 3, 0, 0, 0, 0, 0}, \
   {13, 16, 0, 0, 0, 0, 0}, \
   {17, 2, 0, 0, 0, 0, 0}, \
   {17, 4, 0, 0, 0, 0, 0} \
}

/*----------------------------------------------------------------------------*/
#endif /* CRFWOUTREGISTRYUSERPAR_H */
