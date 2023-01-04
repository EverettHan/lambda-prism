//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
// CATIsPointedSurface : compute, if a surface is degenerated, the new Surlimits
//
//=============================================================================
// Usage Notes:
// iSurf : Surface to analyze
// ioSurLimits : Limits that could be restricted if return TRUE
// iTolerance : 
// ioPointSurPar : SurParam of the point of the Surface
// IsEvalNormal : can the normal be evaluated on this point ? (for a sphere, for example)
// Normal : double[3] the coordinates of the normal if IsEvalNormal
//=============================================================================

#ifndef CATIsPointedSurface_H
#define CATIsPointedSurface_H

#include "CATBoolean.h"
#include "CATSurLimits.h"
#include "CATGeometricOperators.h"
#include "CATSoftwareConfiguration.h"

class CATSurface;

// !!! ioNormal has to be initialized to double[3] !!!
// prefer the one with arrays to this one (because there can be two points)
ExportedByCATGeometricOperators CATBoolean CATIsPointedSurface(CATSoftwareConfiguration * iConfig,
                               CATSurface *iSurf, CATSurLimits &ioSurLimits, double iTolerance,
                               CATSurParam &ioPointSurPar, CATBoolean &ioIsEvalNormal, double *ioNormal);

// !!! ioNormal has to be initialized to double[6] !!!
ExportedByCATGeometricOperators CATBoolean CATIsPointedSurface(CATSoftwareConfiguration * iConfig,
                               CATSurface *iSurf, CATSurLimits &ioSurLimits, double iTolerance,
                               CATSurParam ioPointSurPar[2], CATBoolean ioIsEvalNormal[2],
                               double *ioNormal, int &oPointNumber, short oPointPos[2]);


#endif
