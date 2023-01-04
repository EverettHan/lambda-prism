// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyVertexPseudoManifoldVertexIterator
//
//=============================================================================
// 2009-11-03   NDO: Revisited implementation.
// 2007-01-03   BPG: New
//=============================================================================
#pragma once

#include "CATPolyVertex.h"
#include "CATPolyVertexOrbit.h"
#include "CATPolyCellOrbitIterator.h"


/**
 * Iterator through all the vertex-orbits (0-orbits) of a CATPolyVertex.
 */
class CATPolyVertexOrbitIterator : public CATPolyCellOrbitIterator
{
public:

  inline CATPolyVertexOrbitIterator (CATPolyVertex* iVertex = 0) :
    CATPolyCellOrbitIterator ((CATPolyCell*) iVertex) {}

public:

  /**
   * Returns the current CATPolyVertexOrbit.
   */
  inline CATPolyVertexOrbit Get ()
  {
    return CATPolyVertexOrbit (CATPolyCellOrbitIterator::Get ());
  }
};


// CATPolyVertexPseudoManifoldVertexIterator
#ifndef _AIX_SOURCE
using CATPolyVertexPseudoManifoldVertexIterator = CATPolyVertexOrbitIterator;
#else
typedef CATPolyVertexOrbitIterator CATPolyVertexPseudoManifoldVertexIterator;
#endif
