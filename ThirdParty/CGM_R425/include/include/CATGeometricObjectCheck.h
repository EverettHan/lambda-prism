#ifndef CATGeometricObjectCheck_H
#define CATGeometricObjectCheck_H

// COPYRIGHT DASSAULT SYSTEMES 2008

// oct 7, 2008 RR Creation

#include "YP00IMPL.h"
#include "CATBoolean.h"
class CATSurface;

// Check InternalMaxBoundingBoxes of a CATSurface
extern "C" CATBoolean ExportedByYP00IMPL CheckSurfaceInternalMaxBoundingBoxes(CATSurface* iSurface); // return 0 if KO

// Check InternalMaxBoundingBoxes of a CATCurve
extern "C" CATBoolean ExportedByYP00IMPL CheckCurveInternalMaxBoundingBoxes(CATCurve* iCurve); // return 0 if KO

#endif








