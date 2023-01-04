// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyFaceLoopIterator
//
//=============================================================================
// 2009-11-19   NDO
//=============================================================================
#pragma once

#include "CATPolyFace.h"
#include "CATPolyFaceOrbit.h"
#include "CATPolyCellOrbitIterator.h"


/**
 * Iterator through all the face-orbits (2-orbits) of a CATPolyFace.
 */
class CATPolyFaceOrbitIterator : public CATPolyCellOrbitIterator
{

public:

  inline CATPolyFaceOrbitIterator (CATPolyFace* iFace = 0) :
    CATPolyCellOrbitIterator (iFace) {}

public:

  /**
   * Returns the current CATPolyFaceOrbit.
   */
  inline CATPolyFaceOrbit Get ()
  {
    return CATPolyFaceOrbit (CATPolyCellOrbitIterator::Get ());
  }
};


// CATPolyFaceLoopIterator
#ifndef _AIX_SOURCE
using CATPolyFaceLoopIterator = CATPolyFaceOrbitIterator;
#else
typedef CATPolyFaceOrbitIterator CATPolyFaceLoopIterator;
#endif
