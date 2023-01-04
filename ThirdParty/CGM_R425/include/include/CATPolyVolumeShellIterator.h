// COPYRIGHT DASSAULT SYSTEMES 2022, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyVolumeShellIterator
//
//=============================================================================
// 2022-06-23   NDO
//=============================================================================
#pragma once

#include "CATPolyVolume.h"
#include "CATPolyVolumeOrbit.h"
#include "CATPolyCellOrbitIterator.h"


/**
 * Iterator through all the volume-orbits (3-orbits) of a CATPolyVolume.
 */
class CATPolyVolumeOrbitIterator : public CATPolyCellOrbitIterator
{

public:

  inline CATPolyVolumeOrbitIterator (CATPolyVolume* iVolume = 0) :
    CATPolyCellOrbitIterator (iVolume) {}

public:

  /**
   * Returns the current CATPolyVolumeOrbit.
   */
  inline CATPolyVolumeOrbit Get ()
  {
    return CATPolyVolumeOrbit (CATPolyCellOrbitIterator::Get ());
  }
};


// CATPolyVolumeShellIterator
#ifndef _AIX_SOURCE
using CATPolyVolumeShellIterator = CATPolyVolumeOrbitIterator;
#else
typedef CATPolyVolumeOrbitIterator CATPolyVolumeShellIterator;
#endif
