// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyIntersectionPointBuckets.h
// Header definition of CATPolyIntersectionPointBuckets
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// March 2008 Creation: ndo
//===================================================================
#ifndef CATPolyIntersectionPointBuckets_H
#define CATPolyIntersectionPointBuckets_H

#include "PolyMathIntersectors.h"
#include "CATPolyBuckets_T.h"
#include "CATPolyIntersectionPoint.h"
#include "CATErrorDef.h"


class ExportedByPolyMathIntersectors CATPolyIntersectionPointBuckets
{

public:

  CATPolyIntersectionPointBuckets () {}
  ~CATPolyIntersectionPointBuckets () {}

public:

  inline unsigned int PushBack (const CATPolyIntersectionPoint& I);

public:

  inline HRESULT Clear ();
  inline unsigned int Size () const;

  inline const CATPolyIntersectionPoint& operator [] (const unsigned int i) const;
  inline CATPolyIntersectionPoint& operator [] (const unsigned int i);

protected:

  // Buckets of CATPolyIntersectionPoint's.
  class Specialize_CATPolyBuckets_T (IntersectionPointBuckets, CATPolyIntersectionPoint);

protected:

  IntersectionPointBuckets _IntersectionPoints;

private :

  // Forbidden.
  CATPolyIntersectionPointBuckets (const CATPolyIntersectionPointBuckets& iOther) ;
  CATPolyIntersectionPointBuckets& operator= (const CATPolyIntersectionPointBuckets& iOther) ;

};

unsigned int CATPolyIntersectionPointBuckets::PushBack (const CATPolyIntersectionPoint& I)
{
  return _IntersectionPoints.PushBack (I);
}

inline HRESULT CATPolyIntersectionPointBuckets::Clear ()
{
  return _IntersectionPoints.Clear ();
}

inline unsigned int CATPolyIntersectionPointBuckets::Size () const
{
  return _IntersectionPoints.Size ();
}

inline const CATPolyIntersectionPoint& CATPolyIntersectionPointBuckets::operator [] (const unsigned int i) const
{
  return _IntersectionPoints[i];
}

inline CATPolyIntersectionPoint& CATPolyIntersectionPointBuckets::operator [] (const unsigned int i)
{
  return _IntersectionPoints[i];
}

#endif
