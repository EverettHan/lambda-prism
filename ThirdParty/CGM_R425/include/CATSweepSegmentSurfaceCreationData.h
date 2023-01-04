/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATSweepSegmentSurfaceCreationData:
// Data for creation of SweepSegment surfaces.
//
//=============================================================================
// Usage notes:
//
//
//=============================================================================
// Aug. 99    Creation                                          CPL
// 11/11/19 S9L Streaming changes for support orientation
//              required for sweep extrapolation
//=============================================================================
#ifndef CATSweepSegmentSurfaceCreationData_H
#define CATSweepSegmentSurfaceCreationData_H

#include "YP00IMPL.h"
#include "CATCGMVirtual.h"

#include "CATDataType.h"
class CATGeometry;
class CATSurface;
class CATCurve;
class CATMathSetOfPointsND;

class ExportedByYP00IMPL CATSweepSegmentSurfaceCreationData  : public CATCGMVirtual
{
 public:  
  CATMathSetOfPointsND* Params;
  CATMathSetOfPointsND* Points;
	CATMathSetOfPointsND* Tangents;
	CATMathSetOfPointsND* SecondDerivatives;
	
  CATLONG32 FirstTraceIndex;
	CATLONG32 SecondTraceIndex;

  CATGeometry* Support1;
  CATGeometry* Support2;

  CATGeometry* ContactSupport1;
  CATGeometry* ContactSupport2;

  CATCurve * Spine;

  short Supp1Orient;
  short Supp2Orient;
};
#endif
