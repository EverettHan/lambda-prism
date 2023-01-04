//=============================================================================
// COPYRIGHT Dassault Systemes 2017
//=============================================================================
//
// CATPolyDebugServices.h
//
//=============================================================================
// 2017-09-26   JXO
//      * New
//=============================================================================
#ifndef CATPolyDebugServices_H
#define CATPolyDebugServices_H

// Exported by
#include "PolyMathUtils.h"

// System
#include "CATUnicodeString.h"

class CATMathPoint;
class CATPolyDebugObserver;

namespace Poly
{
  /**
  * Debug a point, given its 3D coordinates, its index, an optional label and an optional group (for coloring)
  */
  ExportedByPolyMathUtils void CapturePoint(const CATMathPoint & iPoint, int index, const char * iLabel = "", int iGroup = 0);

  /**
  * Debug a segment, given the 3D coordinates of its extremities, its index, an optional label and an optional group (for coloring)
  */
  ExportedByPolyMathUtils void CaptureSegment(const CATMathPoint & iPoint1, const CATMathPoint & iPoint2, int index, const char * iLabel = "", int iGroup = 0);

  /**
  * Debug a triangle, given the 3D coordinates of its vertices, its index, an optional label and an optional group (for coloring)
  */
  ExportedByPolyMathUtils void CaptureTriangle(const CATMathPoint & iPoint1, const CATMathPoint & iPoint2, const CATMathPoint & iPoint3, int index, const char * iLabel = "", int iGroup = 0);


  ExportedByPolyMathUtils void RegisterDebugObserver(CATPolyDebugObserver * io);
  ExportedByPolyMathUtils void UnregisterDebugObserver(CATPolyDebugObserver * io);

};
#endif

