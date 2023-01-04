// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyDoublesLayer.h
//
//===================================================================
// October 2021  Creation: NDO
//===================================================================
#pragma once

#include "PolyhedralAttributes.h"
#include "CATIPolyLayer.h"

class CATUnicodeString;


/**
 * A layer associating an array/vector of double data to each vertex of a CATIPolyCurve or CATIPolySurface.
 */
class ExportedByPolyhedralAttributes CATIPolyDoublesLayer : public CATIPolyLayer
{

public:

  /**
   * Returns the dimension of the data layer.
   */
  virtual unsigned int GetDimension () const = 0;

  /**
   * Returns a string identifier of the data layer.
   */
  virtual const CATUnicodeString& GetIdentifier () const;

public:

  /**
   * Sets the data for a curve or surface vertex.
   * @param v
   *   The curve or surface vertex.
   * @param a
   *   An array of values of dimension GetDimension ().
   */
  virtual HRESULT Set (int v, const double* a) = 0;

  /**
   * Gets the data for a surface vertex.
   * @param v
   *   The surface vertex.
   * @param a
   *   An array of values of dimension GetDimension ().
   */
  virtual HRESULT Get (int v, double* a) const = 0;

public:

  inline static const CATIPolyDoublesLayer* Cast (const CATIPolyLayer&);
  inline static const CATIPolyDoublesLayer* Cast (const CATIPolyLayer*);

  inline static CATIPolyDoublesLayer* Cast (CATIPolyLayer&);
  inline static CATIPolyDoublesLayer* Cast (CATIPolyLayer*);

protected:

  virtual ~CATIPolyDoublesLayer () {}

private:

  CATIPolyDoublesLayer* CastAsDoublesLayer () { return this; }

};

inline const CATIPolyDoublesLayer* CATIPolyDoublesLayer::Cast (const CATIPolyLayer& layer)
{
  return ((CATIPolyLayer&) layer).CastAsDoublesLayer ();
}

inline const CATIPolyDoublesLayer* CATIPolyDoublesLayer::Cast (const CATIPolyLayer* layer)
{
  return layer ? Cast (*layer) : 0;
}

inline CATIPolyDoublesLayer* CATIPolyDoublesLayer::Cast (CATIPolyLayer& layer)
{
  return layer.CastAsDoublesLayer ();
}

inline CATIPolyDoublesLayer* CATIPolyDoublesLayer::Cast (CATIPolyLayer* layer)
{
  return layer ? Cast (*layer) : 0;
}
