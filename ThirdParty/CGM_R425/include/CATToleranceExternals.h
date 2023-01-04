#ifndef CATToleranceExternals_H
#define CATToleranceExternals_H

#include "YN000MAT.h"
// COPYRIGHT DASSAULT SYSTEMES  2007
//
// Special access to CATTolerance methods
// (a ne pas interfacer en R204)
//
// 04/05/2013 EB sert à circonscrire les usages sous caution dans les math de CATTolerance

// return 2 if CGMXScaleChecks activated
// return 1 if ptr->GetScaleCategory() does not return ScaleN
// return 0 otherwise
extern "C" ExportedByYN000MAT  int CATTolerance_IsScaleNeeded (const CATTolerance *ptr ) ;

// 04/05/2013 EB sert à centraliser l'acces aux CATTolerance scalées non reliées à des GeoFactory
extern "C" ExportedByYN000MAT  const CATTolerance & GetIsolatedScaledCATTolerance (const CATCGMScaleCategory iScaleCategory )  ;
#endif
