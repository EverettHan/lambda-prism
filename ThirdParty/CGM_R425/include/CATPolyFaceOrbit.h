// COPYRIGHT DASSAULT SYSTEMES 2018, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyFaceOrbit
//
//=============================================================================
// 2018-12-03   NDO
//=============================================================================
#pragma once

#include "CATPolyMacroTopologyFwd.h"
#include "CATPolyCellOrbit.h"
#include "CATPolyFace.h"


// Orbit of darts around a CATPolyFace (or loop).
// A face can have one or several orbits (loops).
// The CATPolyFace data can be edited through the use of a transient CATPolyFaceOrbit.
// All the methods are inline.
class CATPolyFaceOrbit : public CATPolyCellOrbit
{

public:

  inline CATPolyFaceOrbit () {}
  inline CATPolyFaceOrbit (const CATPolyFaceOrbit& iRHS);

  inline ~CATPolyFaceOrbit () {}

public:

  // Returns true if the face-orbit is open.
  // Its first dart is 0-free or 1-free.
  inline bool IsOpen () const;

protected:

  // Reserved for friend classes.
  inline CATPolyFaceOrbit (CATPolyFace* iFace);
  inline CATPolyFaceOrbit (CATPolyFace* iFace, CATPolyDartLink<CATPolyDart2>* iDartLink);
  inline CATPolyFaceOrbit (CATPolyFace* iFace, CATPolyDartLink<CATPolyDart3>* iDartLink);
  inline CATPolyFaceOrbit (const CATPolyCellOrbit& iRHS);

  //friend class CATPolyBody;
  friend class CATPolyDartHelpers;
  friend class CATPolyFaceOrbitIterator;
  template<class DART> friend class CATPolyFaceDartIterator;

};


inline CATPolyFaceOrbit::CATPolyFaceOrbit (CATPolyFace* iFace) :
  CATPolyCellOrbit (iFace)
{
}

inline CATPolyFaceOrbit::CATPolyFaceOrbit (CATPolyFace* iFace, CATPolyDartLink<CATPolyDart2>* iDartLink) :
  CATPolyCellOrbit (iFace, iDartLink)
{
}

inline CATPolyFaceOrbit::CATPolyFaceOrbit (CATPolyFace* iFace, CATPolyDartLink<CATPolyDart3>* iDartLink) :
  CATPolyCellOrbit (iFace, iDartLink)
{
}

inline CATPolyFaceOrbit::CATPolyFaceOrbit (const CATPolyFaceOrbit& iRHS) :
  CATPolyCellOrbit (iRHS)
{
}

inline CATPolyFaceOrbit::CATPolyFaceOrbit (const CATPolyCellOrbit& iRHS)
{
  if (CATPolyFace::Cast (iRHS.GetCell ()))
    (CATPolyCellOrbit&)*this = iRHS;
}

inline bool CATPolyFaceOrbit::IsOpen () const
{
  return Poly::IsOpen (*this);
}
