// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyEdgeOrbit
//
//=============================================================================
// 2009-11-03   NDO: Revisited implementation, optimizations
// 2007-01-03   BPG: New
//=============================================================================
#pragma once

#include "CATPolyMacroTopologyFwd.h"
#include "CATPolyCellOrbit.h"
#include "CATPolyEdge.h"


// Orbit of darts around a CATPolyEdge (or manifold edge).
// An edge can have one or several orbits (manifold edges).
// The CATPolyEdge data can be edited through the use of a transient CATPolyEdgeOrbit.
// All the methods are inline.
class CATPolyEdgeOrbit : public CATPolyCellOrbit
{

public:

  inline CATPolyEdgeOrbit () {}
  inline CATPolyEdgeOrbit (const CATPolyEdgeOrbit& iRHS);

  inline ~CATPolyEdgeOrbit () {}

protected:

  // Reserved for friend classes.
  inline CATPolyEdgeOrbit (CATPolyEdge* iEdge);
  inline CATPolyEdgeOrbit (CATPolyEdge* iEdge, CATPolyDartLink<CATPolyDart2>* iDartLink);
  inline CATPolyEdgeOrbit (CATPolyEdge* iEdge, CATPolyDartLink<CATPolyDart3>* iDartLink);
  inline CATPolyEdgeOrbit (const CATPolyCellOrbit& iRHS);

  //friend class CATPolyBody;
  friend class CATPolyDartHelpers;
  friend class CATPolyEdgeOrbitIterator;
  template<class DART> friend class CATPolyEdgeDartIterator;

};


inline CATPolyEdgeOrbit::CATPolyEdgeOrbit (CATPolyEdge* iEdge) :
  CATPolyCellOrbit (iEdge)
{
}

inline CATPolyEdgeOrbit::CATPolyEdgeOrbit (CATPolyEdge* iEdge, CATPolyDartLink<CATPolyDart2>* iDartLink) :
  CATPolyCellOrbit (iEdge, iDartLink)
{
}

inline CATPolyEdgeOrbit::CATPolyEdgeOrbit (CATPolyEdge* iEdge, CATPolyDartLink<CATPolyDart3>* iDartLink) :
  CATPolyCellOrbit (iEdge, iDartLink)
{
}

inline CATPolyEdgeOrbit::CATPolyEdgeOrbit (const CATPolyEdgeOrbit& iRHS) :
  CATPolyCellOrbit (iRHS)
{
}

inline CATPolyEdgeOrbit::CATPolyEdgeOrbit (const CATPolyCellOrbit& iRHS)
{
  if (CATPolyEdge::Cast (iRHS.GetCell ()))
    (CATPolyCellOrbit&)*this = iRHS;
}
