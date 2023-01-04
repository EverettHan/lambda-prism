#ifndef CATCGMDynamicTrackWithLeak_h
#define CATCGMDynamicTrackWithLeak_h
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2008
// 
// DESCRIPTION : (Debug purpose only) Internal utilities for dynamic track generating memory leak
//
// 29/05/08 NLD Creation
// 13/06/09 NLD Ajout argument iCreateLeakAtEachCall
//=============================================================================
#include "ExportedByCATMathStream.h"

// To be called for memory leak generation when odt using calling software 
// necessary declaration before odt replay:
// set CATCX_ShowAllLeaks=1
extern "C" ExportedByCATMathStream
void CATCGMDynamicTrackWithLeak(int iCreateLeakAtEachCall=0) ;
#endif
