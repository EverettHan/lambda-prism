// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBarsBarIterator.h
// Header definition of CATPolyBarsBarIterator
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// November 2007  Creation: NDO
//===================================================================
#ifndef CATPolyBarsBarIterator_H
#define CATPolyBarsBarIterator_H

#include "PolyMeshImpl.h"
#include "CATPolyBars.h"
#include "CATBoolean.h"


/**
 * Iterate through the bars of a CATPolyBars container.
 */
class ExportedByPolyMeshImpl CATPolyBarsBarIterator
{

public:

  CATPolyBarsBarIterator (const CATPolyBars& iBars);
  ~CATPolyBarsBarIterator ();

public:

  inline CATPolyBarsBarIterator& Begin ();
  inline CATPolyBarsBarIterator& Begin (const CATPolyBars& iBars);
  inline CATBoolean End () const;

public:

  CATPolyBarsBarIterator& operator++ ();

public:

  inline int Get ();
  inline int operator* ();
  inline int operator-> ();

private:

  CATPolyBarsBarIterator& Reset ();

private:

  const CATPolyBars* _Bars;
  int _Index;

};


inline CATPolyBarsBarIterator::CATPolyBarsBarIterator (const CATPolyBars& iBars) :
  _Bars (&iBars)
{
  Reset ();
}

inline CATPolyBarsBarIterator::~CATPolyBarsBarIterator ()
{
  _Bars = 0;
}

inline CATPolyBarsBarIterator& CATPolyBarsBarIterator::Begin ()
{
  return Reset ();
}

inline CATPolyBarsBarIterator& CATPolyBarsBarIterator::Begin (const CATPolyBars& iBars)
{
  _Bars = &iBars;
  return Reset ();
}

inline CATBoolean CATPolyBarsBarIterator::End () const
{
  return _Index == 0;
}

inline int CATPolyBarsBarIterator::Get ()
{
  return _Index;
}

inline int CATPolyBarsBarIterator::operator* ()
{
  return _Index;
}

inline int CATPolyBarsBarIterator::operator-> ()
{
  return _Index;
}

#endif
