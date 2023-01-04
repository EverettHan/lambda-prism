// COPYRIGHT DASSAULT SYSTEMES 2022, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyCellOrbitIterator
//
//=============================================================================
// 2022-03-02   NDO: New
//=============================================================================
#pragma once

#include "PolyMODEL.h"
#include "CATPolyDartLink.h"
#include "CATPolyCellOrbit.h"
#include "CATPolyCell.h"


/**
 * Iterator through all the distinct orbits associated to a CATPolyCell.
 * See also CATPolyCellOrbit.
 * For example:
 *   * 0-orbits around a vertex;
 *   * 1-orbits around an edge;
 *   * 2-orbits around a face;
 *   * 3-orbits around a volume.
 * All methods are inline.
 */
class ExportedByPolyMODEL CATPolyCellOrbitIterator
{

public:

  inline CATPolyCellOrbitIterator (CATPolyCell* iCell = 0);
  inline CATPolyCellOrbitIterator (const CATPolyCellOrbitIterator& iRHS);
  inline ~CATPolyCellOrbitIterator ();

public:

  CATPolyCellOrbitIterator& Begin (CATPolyCell* iCell);
  inline bool End () const;
  inline CATPolyCellOrbitIterator& operator++ ();

public:

  /**
   * Returns the current cell-orbit.  
   */
  inline CATPolyCellOrbit Get () const;

  /**
   * Returns the cell.
   */
  inline CATPolyCell* GetCell () const;

  /**
   * Returns a dart (starting dart) of the current orbit.
   */
  template<class DART>
  inline DART* GetFirstDart () const;

protected:

  enum Flag
  {
    /* Unset */                  Unset = 0x0000,  // Bit 2
    /* Map to Dart2 */           BitDart2 = 0x0002,  // Bit 2
    /* Map to Dart3 */           BitDart3 = 0x0004  // Bit 3
  };

  Flag _Flag;
  CATPolyCell* _Cell;
  CATPolyCellOrbit::DartLink _DartLink;

};

inline CATPolyCellOrbitIterator::CATPolyCellOrbitIterator (CATPolyCell* iCell) :
  _Flag (Unset)
{
  _Cell = 0;
  _DartLink._Dart2Link = 0;
  Begin (iCell);
}

inline CATPolyCellOrbitIterator::CATPolyCellOrbitIterator (const CATPolyCellOrbitIterator& iRHS)
{
  _Flag = iRHS._Flag;
  _Cell = iRHS._Cell;
  _DartLink = iRHS._DartLink;
}

inline CATPolyCellOrbitIterator::~CATPolyCellOrbitIterator ()
{
  _Cell = 0;
  _DartLink._Dart2Link = 0;
}

inline bool CATPolyCellOrbitIterator::End () const
{
  return _Cell == 0;
}

inline CATPolyCellOrbitIterator& CATPolyCellOrbitIterator::operator++ ()
{
  switch (_Flag)
  {
  case BitDart2:
  {
    if (_DartLink._Dart2Link)
      _DartLink._Dart2Link = _DartLink._Dart2Link->GetNext ();
    if (!_DartLink._Dart2Link)
      _Cell = 0;
    break;
  }
  case BitDart3:
  {
    if (_DartLink._Dart3Link)
      _DartLink._Dart3Link = _DartLink._Dart3Link->GetNext ();
    if (!_DartLink._Dart3Link)
      _Cell = 0;
    break;
  }
  default:
    _Cell = 0;
  }
  return *this;
}

inline CATPolyCellOrbit CATPolyCellOrbitIterator::Get () const
{
  return CATPolyCellOrbit (_Cell, _DartLink);
}

inline CATPolyCell* CATPolyCellOrbitIterator::GetCell () const
{
  return _Cell;
}

template<>
inline CATPolyDart2* CATPolyCellOrbitIterator::GetFirstDart<CATPolyDart2> () const
{
  return _DartLink._Dart2Link ? _DartLink._Dart2Link->GetDart () : (_Cell ? _Cell->GetVeryFirstDart<CATPolyDart2> () : 0);
}

template<>
inline CATPolyDart3* CATPolyCellOrbitIterator::GetFirstDart<CATPolyDart3> () const
{
  return _DartLink._Dart3Link ? _DartLink._Dart3Link->GetDart () : (_Cell ? _Cell->GetVeryFirstDart<CATPolyDart3> () : 0);
}
