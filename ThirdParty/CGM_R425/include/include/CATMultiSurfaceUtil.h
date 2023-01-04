//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2016
//=============================================================================
//
// CATMultiSurfaceUtil:
//    Header file for multi-surface utility functions.
//
//=============================================================================
// Usage notes:
//=============================================================================
// 26/01/16 R1Y Creation (moved CATCheckMultiSurface() from CATUtilLayDownCrvSur.h).
// 27/01/16 R1Y Added CATPlotMultiSurfaces() (from CATIntersectionMultiSurfaceCx1.cpp).
//=============================================================================

#ifndef CATMultiSurfaceUtil_H 
#define CATMultiSurfaceUtil_H 

#include "CATBoolean.h"

class CATMultiSurface;
class CATGeoFactory;

// Function to check the borders and surfaces of a multi-surface.
// Remark: As CATCheckSurface.h cannot be included in CATMultiSurface.cpp,
//         CATCheckMultiSurface() cannot be moved to the CATMultiSurface class.
CATBoolean CATCheckMultiSurface(const CATMultiSurface          * const iMultiSurface,
                                      CATGeoFactory            * const iFactory,
                                      CATSoftwareConfiguration * const iConfig);

#endif
