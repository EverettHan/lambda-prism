/* -*-C++-*-*/
//
// COPYRIGHT DASSAULT SYSTEMES 1998
//
//==========================================================================
/** @CAA2Required */
/**
 * For Object Test, for the best management of Regression Status 77 
 *  if you include this file, you must use the CATCX_MEMORY_MAIN macro
 *  -> just after the definition of your main and before the first bracket.
 */
#ifndef CATCX_MEMORY_MAIN_H
#define CATCX_MEMORY_MAIN_H

#include "YN000MAT.h"
#include "CATErrorMacros.h"
#include "CATCGAMEM_RC.h"
#include "CATPerformanceToolAdapter.h"

static int CATCX_MEMORY_MAIN_FUNCTION( int argc, char ** argv );

#define CATCX_MEMORY_MAIN(argc,argv)              \
  {                                               \
    int volatile rc=0;                            \
    CATCGAMEM_BEGIN();                            \
    CATMakeStartPoint(0, "CATCX_MEMORY_MAIN");    \
    CATTry                                        \
    {                                             \
      rc = CATCX_MEMORY_MAIN_FUNCTION(argc,argv); \
    }                                             \
    CATCatch(CATError,err)                        \
    {                                             \
       if ( rc == 0 ) rc = 68;                    \
       Flush(err);                                \
    }                                             \
    CATEndTry                                     \
    CATMakeStopPoint(0, "CATCX_MEMORY_MAIN");    \
    return CATCGAMEM_END(rc);                     \
  }                                               \
  int CATCX_MEMORY_MAIN_FUNCTION( int argc, char ** argv )

#endif

