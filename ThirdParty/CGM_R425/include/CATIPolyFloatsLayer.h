// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyFloatsLayer.h
//
//===================================================================
// October 2021  Creation: NDO
//===================================================================
#pragma once

#include "PolyhedralAttributes.h"
#include "CATIPolyDoublesLayer.h"


/**
 * A layer associating an array/vector of float data to each vertex of a CATIPolyCurve or CATIPolySurface.
 */
class ExportedByPolyhedralAttributes CATIPolyFloatsLayer : public CATIPolyDoublesLayer
{

protected:

  virtual ~CATIPolyFloatsLayer () {}

public:

  inline static const CATIPolyFloatsLayer* Cast (const CATIPolyLayer&);
  inline static const CATIPolyFloatsLayer* Cast (const CATIPolyLayer*);

  inline static CATIPolyFloatsLayer* Cast (CATIPolyLayer&);
  inline static CATIPolyFloatsLayer* Cast (CATIPolyLayer*);

public:

  /**
   * Sets the data for a curve or surface vertex.
   * @param v
   *   The curve or surface vertex.
   * @param a
   *   An array of values of dimension GetDimension ().
   */
  virtual HRESULT Set (int v, const float* a) = 0;

  /**
   * Gets the data for a surface vertex.
   * @param v
   *   The surface vertex.
   * @param a
   *   An array of values of dimension GetDimension ().
   */
  virtual HRESULT Get (int v, float* a) const = 0;

public:

  HRESULT Set (int v, const double* a);

  HRESULT Get (int v, double* a) const;

private:

  CATIPolyFloatsLayer* CastAsFloatsLayer () { return this; }

};

inline const CATIPolyFloatsLayer* CATIPolyFloatsLayer::Cast (const CATIPolyLayer& layer)
{
  return ((CATIPolyLayer&) layer).CastAsFloatsLayer ();
}

inline const CATIPolyFloatsLayer* CATIPolyFloatsLayer::Cast (const CATIPolyLayer* layer)
{
  return layer ? Cast (*layer) : 0;
}

inline CATIPolyFloatsLayer* CATIPolyFloatsLayer::Cast (CATIPolyLayer& layer)
{
  return layer.CastAsFloatsLayer ();
}

inline CATIPolyFloatsLayer* CATIPolyFloatsLayer::Cast (CATIPolyLayer* layer)
{
  return layer ? Cast (*layer) : 0;
}
