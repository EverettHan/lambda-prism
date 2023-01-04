/* -*-C++-*-*/
//
// COPYRIGHT DASSAULT SYSTEMES 1998
//
//==========================================================================
/** @CAA2Required */
/**
 * For Object Test with Status <> 0, it should be taken into account first
 *    before the CGA object leak regression process (exit = 77)
 */
#ifndef CATCGAMEM_RC_H
#define CATCGAMEM_RC_H


#include "YN000MAT.h"

// to override the atexit management of CATCGAMEM process
ExportedByYN000MAT void CATCGAMEM_BEGIN();
ExportedByYN000MAT int  CATCGAMEM_END(const int rc);

#endif

