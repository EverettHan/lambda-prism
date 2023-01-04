// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyVertexOrbit
//
//=============================================================================
// 2009-11-03   NDO: Revisited implementation, optimizations
// 2007-01-03   BPG: New
//=============================================================================
#pragma once

#include "CATPolyMacroTopologyFwd.h"
#include "CATPolyCellOrbit.h"
#include "CATPolyVertex.h"


// Orbit of darts around a CATPolyVertex (or pseudo-manifold vertex).
// A vertex can have one or several orbits (pseudo-manifold vertices).
// The CATPolyVertex data can be edited through the use of a transient CATPolyVertexOrbit.
// All the methods are inline.
class CATPolyVertexOrbit : public CATPolyCellOrbit
{

public:

  inline CATPolyVertexOrbit () {}
  inline CATPolyVertexOrbit (const CATPolyVertexOrbit& iRHS);

  inline ~CATPolyVertexOrbit () {}

protected:

  // Reserved for friend classes.
  inline CATPolyVertexOrbit (CATPolyVertex* iCell);
  inline CATPolyVertexOrbit (CATPolyVertex* iVertex, CATPolyDartLink<CATPolyDart2>* iDartLink);
  inline CATPolyVertexOrbit (CATPolyVertex* iVertex, CATPolyDartLink<CATPolyDart3>* iDartLink);
  inline CATPolyVertexOrbit (const CATPolyCellOrbit& iRHS);

  friend class CATPolyBody;
  friend class CATPolyDartHelpers;
  friend class CATPolyVertexOrbitIterator;
  template<class DART> friend class CATPolyVertexDartIterator;

};


inline CATPolyVertexOrbit::CATPolyVertexOrbit (CATPolyVertex* iVertex) :
  CATPolyCellOrbit (iVertex)
{
}

inline CATPolyVertexOrbit::CATPolyVertexOrbit (CATPolyVertex* iVertex, CATPolyDartLink<CATPolyDart2>* iDartLink) :
  CATPolyCellOrbit (iVertex, iDartLink)
{
}

inline CATPolyVertexOrbit::CATPolyVertexOrbit (CATPolyVertex* iVertex, CATPolyDartLink<CATPolyDart3>* iDartLink) :
  CATPolyCellOrbit (iVertex, iDartLink)
{
}

inline CATPolyVertexOrbit::CATPolyVertexOrbit (const CATPolyVertexOrbit& iRHS) :
  CATPolyCellOrbit (iRHS)
{
}

inline CATPolyVertexOrbit::CATPolyVertexOrbit (const CATPolyCellOrbit& iRHS)
{
  if (CATPolyVertex::Cast (iRHS.GetCell ()))
    (CATPolyCellOrbit&)*this = iRHS;
}
