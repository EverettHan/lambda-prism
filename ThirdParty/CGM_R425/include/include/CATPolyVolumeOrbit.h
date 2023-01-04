// COPYRIGHT DASSAULT SYSTEMES 2022, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyVolumeOrbit
//
//=============================================================================
// 2022-06-10   NDO
//=============================================================================
#pragma once

#include "CATPolyMacroTopologyFwd.h"
#include "CATPolyCellOrbit.h"
#include "CATPolyVolume.h"


// Orbit of darts around a CATPolyVolume (or manifold edge).
// An edge can have one or several orbits (manifold edges).
// The CATPolyVolume data can be edited through the use of a transient CATPolyVolumeOrbit.
// All the methods are inline.
class CATPolyVolumeOrbit : public CATPolyCellOrbit
{

public:

  inline CATPolyVolumeOrbit () {}
  inline CATPolyVolumeOrbit (const CATPolyVolumeOrbit& iRHS);

  inline ~CATPolyVolumeOrbit () {}

protected:

  // Reserved for friend classes.
  inline CATPolyVolumeOrbit (CATPolyVolume* iVolume);
  inline CATPolyVolumeOrbit (CATPolyVolume* iVolume, CATPolyDartLink<CATPolyDart2>* iDartLink);
  inline CATPolyVolumeOrbit (CATPolyVolume* iVolume, CATPolyDartLink<CATPolyDart3>* iDartLink);
  inline CATPolyVolumeOrbit (const CATPolyCellOrbit& iRHS);

  //friend class CATPolyBody;
  friend class CATPolyDartHelpers;
  friend class CATPolyVolumeOrbitIterator;
  template<class DART> friend class CATPolyVolumeDartIterator;

};


inline CATPolyVolumeOrbit::CATPolyVolumeOrbit (CATPolyVolume* iVolume) :
  CATPolyCellOrbit (iVolume)
{
}

inline CATPolyVolumeOrbit::CATPolyVolumeOrbit (CATPolyVolume* iVolume, CATPolyDartLink<CATPolyDart2>* iDartLink) :
  CATPolyCellOrbit (iVolume, iDartLink)
{
}

inline CATPolyVolumeOrbit::CATPolyVolumeOrbit (CATPolyVolume* iVolume, CATPolyDartLink<CATPolyDart3>* iDartLink) :
  CATPolyCellOrbit (iVolume, iDartLink)
{
}

inline CATPolyVolumeOrbit::CATPolyVolumeOrbit (const CATPolyVolumeOrbit& iRHS) :
  CATPolyCellOrbit (iRHS)
{
}

inline CATPolyVolumeOrbit::CATPolyVolumeOrbit (const CATPolyCellOrbit& iRHS)
{
  if (CATPolyVolume::Cast (iRHS.GetCell ()))
    (CATPolyCellOrbit&)*this = iRHS;
}
