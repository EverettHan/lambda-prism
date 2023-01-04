// COPYRIGHT DASSAULT SYSTEMES 2014

#ifndef CGMVswpDebug_H
#define CGMVswpDebug_H

#include "CATGMModelInterfaces.h"
#include "CATLib.h"

#define VSWP_TRACE_LEVEL_0 0
#define VSWP_TRACE_LEVEL_1 1
#define VSWP_TRACE_LEVEL_2 2
#define VSWP_TRACE_LEVEL_3 3

ExportedByCATGMModelInterfaces int CurrVswpTraceLevel();    

#define VOL_SWEEP_TRACE_START( Level ) if ( Level <= CurrVswpTraceLevel() ) {
#define VOL_SWEEP_TRACE_END    fflush( stdout ); }

#define VOL_SWEEP_TRACE_END_WITH_INDEX                                   \
    char const * pMoveIndex =  CATGetEnv( "VSWP_MOVE_INDEX" );           \
    char const * pSweepIndex = CATGetEnv( "VSWP_SWEEP_INDEX" );          \
    if ( pMoveIndex != NULL && pSweepIndex != NULL )                     \
        printf( " ( Move %s Sweep %s ).\n", pMoveIndex, pSweepIndex );   \
    else printf( "\n" );                                                 \
    fflush( stdout );                                                    \
    }

#endif 
