// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATBucketsOfPoints.h
//
//===================================================================
//
// 2010-01-20 NDO
// 2013-12-03 JXO Now as doubles
//===================================================================
#ifndef CATBucketsOfPoints_h
#define CATBucketsOfPoints_h

#include "PolyMathContainers.h"
#include "CATPolyBuckets_T.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

#include "CATMathPoint.h"


class ExportedByPolyMathContainers CATBucketsOfPoints
{

public:

  CATBucketsOfPoints () {}
  ~CATBucketsOfPoints () {}

public:

  /*
   * Add a point to the set of points and return its index.
   * Indices of the point start at 1.
   */
  HRESULT Add (const CATMathPoint& iPoint, int& oIndex);
  HRESULT Add (const double x, const double y, const double z, int& oIndex);

  /*
   * Get the point given an index.
   * Indices range from 1 to GetNbPoints () inclusive.
   */
  HRESULT Get (const int iIndex, CATMathPoint& oPoint) const;
  HRESULT Get (const int iIndex, double& x, double& y, double& z) const;

  /*
   * Return a pointer to the three coordinates of the point.
   */
  inline const double* GetCoordinates (const int iIndex) const;

public:

  /*
   * Return the number of points.
   */
  inline int GetNbPoints () const;

  inline HRESULT RemoveAll ();

private:

  struct Coordinates
  {
    double _D[3];
  };

  class Specialize_CATPolyBuckets_T (CATBucketsPoints, Coordinates);

private:

  CATBucketsPoints _Points;

};

inline const double* CATBucketsOfPoints::GetCoordinates (const int iIndex) const
{
  return _Points[iIndex]._D;
}

inline int CATBucketsOfPoints::GetNbPoints () const
{
  return _Points.Size ();
}

inline HRESULT CATBucketsOfPoints::RemoveAll ()
{
  _Points.Clear ();
  return S_OK;
}

#endif
