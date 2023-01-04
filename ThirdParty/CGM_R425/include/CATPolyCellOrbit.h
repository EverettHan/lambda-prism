// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyCellOrbit
//
//=============================================================================
// 2009-11-20   NDO
//=============================================================================
#pragma once

#include <stdlib.h>  // size_t

template<size_t N> class CATPolyDart;
template<class DART> class CATPolyDartLink;

#ifndef _AIX_SOURCE
using CATPolyDart2 = CATPolyDart<2>;
using CATPolyDart3 = CATPolyDart<3>;
#else
typedef CATPolyDart<2> CATPolyDart2;
typedef CATPolyDart<3> CATPolyDart3;
#endif

class CATPolyCell;


// A CATPolyCellOrbit is an orbit of darts around a cell.  It could be:
//   o CATPolyVertexOrbit or CATPolyPseudoManifoldVertex
//     This represents a dart-orbit around a vertex.  This is the definition of a pseudo-manifold vertex.
//   o CATPolyEdgeOrbit or CATPolyManifoldEdge
//     This represents a dart-orbit around an edge.  This is the definition of a manifold edge.
//   o CATPolyFaceOrbit of CATPolyFaceLoop
//     This represents a dart-orbit around a face.  It defines a loop.
//   o CATPolyVolumeOrbit
//     This represents a dart-orbit around a volume.  It defines a shell.
// 
// A CATPolyCellOrbit is characterized by a first dart.  If the orbit is open, the first dart is one
// of the extremities of the orbit. (The "smallest dart" is chosen.)
// The other darts around the orbit can be obtained using the various iterators including:
//   * CATPolyDartOrbit12
//   * CATPolyDartOrbit02
//   * CATPolyDartOrbit01
// iterators.
class CATPolyCellOrbit
{

public:

  // Copy constructor.
  inline CATPolyCellOrbit (const CATPolyCellOrbit& iRHS);
  inline CATPolyCellOrbit ();

  inline ~CATPolyCellOrbit ();

  // Assignment operator.
  inline CATPolyCellOrbit& operator = (const CATPolyCellOrbit& iRHS);

  inline bool operator == (const CATPolyCellOrbit& iRHS) const;

public:

  inline CATPolyCell* GetCell () const;

protected:

  union DartLink
  { // Different from null if there is more than one orbit associated to the cell.
    CATPolyDartLink<CATPolyDart2>* _Dart2Link;
    CATPolyDartLink<CATPolyDart3>* _Dart3Link;
  };

  // Constructors are protected.
  inline CATPolyCellOrbit (CATPolyCell* iCell);
  inline CATPolyCellOrbit (CATPolyCell* iCell, CATPolyDartLink<CATPolyDart2>* iDartLink);
  inline CATPolyCellOrbit (CATPolyCell* iCell, CATPolyDartLink<CATPolyDart3>* iDartLink);
  inline CATPolyCellOrbit (CATPolyCell* iCell, DartLink iDartLink);

  CATPolyCell* _Cell;  // The cell of the orbit.
  DartLink _DartLink;

  friend class CATPolyDartHelpers;
  friend class CATPolyCellOrbitIterator;

};


inline CATPolyCellOrbit::CATPolyCellOrbit (CATPolyCell* iCell)
{
  _Cell = iCell;
  _DartLink._Dart2Link = 0;
}

inline CATPolyCellOrbit::CATPolyCellOrbit (CATPolyCell* iCell, CATPolyDartLink<CATPolyDart2>* iDartLink)
{
  _Cell = iCell;
  _DartLink._Dart2Link = iDartLink;
}

inline CATPolyCellOrbit::CATPolyCellOrbit (CATPolyCell* iCell, CATPolyDartLink<CATPolyDart3>* iDartLink)
{
  _Cell = iCell;
  _DartLink._Dart3Link = iDartLink;
}

inline CATPolyCellOrbit::CATPolyCellOrbit (CATPolyCell* iCell, CATPolyCellOrbit::DartLink iDartLink)
{
  _Cell = iCell;
  _DartLink = iDartLink;
}

inline CATPolyCellOrbit::CATPolyCellOrbit (const CATPolyCellOrbit& iRHS)
{
  _Cell = iRHS._Cell;
  _DartLink = iRHS._DartLink;
}

inline CATPolyCellOrbit::CATPolyCellOrbit ()
{
  _Cell = 0;
  _DartLink._Dart2Link = 0;
}

inline CATPolyCellOrbit::~CATPolyCellOrbit ()
{
  _Cell = 0;
  _DartLink._Dart2Link = 0;
}

inline CATPolyCellOrbit& CATPolyCellOrbit::operator = (const CATPolyCellOrbit& iRHS)
{
  _Cell = iRHS._Cell;
  _DartLink = iRHS._DartLink;
  return *this;
}

inline bool CATPolyCellOrbit::operator == (const CATPolyCellOrbit& iRHS) const
{
  return _Cell == iRHS._Cell && _DartLink._Dart2Link == iRHS._DartLink._Dart2Link;
}

inline CATPolyCell* CATPolyCellOrbit::GetCell () const
{
  return _Cell;
}
