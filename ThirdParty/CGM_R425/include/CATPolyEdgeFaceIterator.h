// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyEdgeFaceIterator
//
//=============================================================================
// 2009-11-03   NDO: Revisited implementation.
// 2007-01-03   BPG: New
//=============================================================================
#pragma once

#include "CATPolyEdgeCurveIterator.h"

// Before removing the following two lines check the frameworks: GeometryVisualization and SMAHvsEngine
#include "CATPolyFace.h"  // Check CATPolyBodyToUVConverter.cpp and SMAHvsVwrDecimateTools.cpp before removing this line.
#include "CATPolyEdge.h"  // Check CATPolyBodyToUVConverter.cpp and SMAHvsVwrDecimateTools.cpp before removing this line.


/**
* Iterator through all the faces incident to a CATPolyEdge.
*
* Example:
* \code
* CATPolyEdgeFaceIterator it;
* for (it.Begin (MyEdge); !it.End (); ++it)
* {
*   CATPolyFace* face = it.GetFace ();  // Incident face.
*   CATPolyCurve* curve = it.GetCurve ();
* }
* \endcode
*
*/
class CATPolyEdgeFaceIterator : public CATPolyEdgeCurveIterator
{

public:

  inline CATPolyEdgeFaceIterator (CATPolyEdge* iEdge = 0);
  inline CATPolyEdgeFaceIterator (const CATPolyEdgeFaceIterator& iRHS);
  inline ~CATPolyEdgeFaceIterator () {}

public:

  inline CATPolyEdgeFaceIterator& Begin (CATPolyEdge* iEdge);
  inline CATPolyEdgeFaceIterator& Begin (CATPolyEdge& iEdge);
  inline CATPolyEdgeFaceIterator& operator++ ();

};


inline CATPolyEdgeFaceIterator::CATPolyEdgeFaceIterator (CATPolyEdge* iEdge)
{
  Begin (iEdge);
}

inline CATPolyEdgeFaceIterator::CATPolyEdgeFaceIterator (const CATPolyEdgeFaceIterator& iRHS) :
  CATPolyEdgeCurveIterator (iRHS)
{
}

inline CATPolyEdgeFaceIterator& CATPolyEdgeFaceIterator::Begin (CATPolyEdge* iEdge)
{
  CATPolyEdgeCurveIterator::Begin (iEdge);
  if (!End () && !GetFace ())
    operator++ ();  // No face.
  return *this;
}

inline CATPolyEdgeFaceIterator& CATPolyEdgeFaceIterator::Begin (CATPolyEdge& iEdge)
{
  CATPolyEdgeCurveIterator::Begin (iEdge);
  if (!End () && !GetFace ())
    operator++ ();  // No face.
  return *this;
}

inline CATPolyEdgeFaceIterator& CATPolyEdgeFaceIterator::operator++ ()
{
  CATPolyEdgeCurveIterator::operator++ ();
  while (!End () && !GetFace ())
    CATPolyEdgeCurveIterator::operator++ ();  // No face.
  return *this;
}
