// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyEdgeManifoldEdgeIterator
//
//=============================================================================
// 2009-11-03   NDO: Revisited implementation.
// 2007-01-03   BPG: New
//=============================================================================
#pragma once

#include "CATPolyEdge.h"
#include "CATPolyEdgeOrbit.h"
#include "CATPolyCellOrbitIterator.h"


/**
 * Iterator through all the edge-orbits (1-orbits) of a CATPolyEdge.
 */
class CATPolyEdgeOrbitIterator : public CATPolyCellOrbitIterator
{
public:

  inline CATPolyEdgeOrbitIterator (CATPolyEdge* iEdge = 0) :
    CATPolyCellOrbitIterator ((CATPolyCell*) iEdge) {}

public:

  /**
   * Returns the current CATPolyManifoldEdge.
   */
  inline CATPolyEdgeOrbit Get ()
  {
    return CATPolyEdgeOrbit (CATPolyCellOrbitIterator::Get ());
  }
};


// CATPolyEdgeManifoldEdgeIterator
#ifndef _AIX_SOURCE
using CATPolyEdgeManifoldEdgeIterator = CATPolyEdgeOrbitIterator;
#else
typedef CATPolyEdgeOrbitIterator CATPolyEdgeManifoldEdgeIterator;
#endif
