// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyVertexPositionConstLayer.h
// Interface of a const layer of vertex positions.
//
//===================================================================
// 2010-04-27 JXO from CATIPolyCurveVertexPositionConstLayer
//===================================================================
#ifndef CATIPolyVertexPositionConstLayer_H
#define CATIPolyVertexPositionConstLayer_H

#include "PolyhedralAttributes.h"
#include "CATErrorDef.h"
#include "CATIPolyDoublesLayer.h"
#include "CATIPolyObject.h"
#include "Poly/Precision.h"

class CATMathPoint;


/**
 * Interface to a vertex position const layer.
 * 
 * Given a vertex, this interface returns its three coordinates.
 */
class ExportedByPolyhedralAttributes CATIPolyVertexPositionConstLayer : public CATIPolyDoublesLayer
{

public:

  unsigned int GetDimension () const { return 3; }

  virtual HRESULT Set (int v, const double* a) { return S_FALSE; }
  virtual HRESULT Get (int v, double* a) const;

public:

  /**
   * Returns the vertex coordinates.
   * @param v
   *   The index of the vertex.
   * @param x, y, z
   *   The position of the vertex.
   */
  virtual HRESULT Get (int v, double &x, double &y, double &z) const = 0;

  /**
   * Returns the position of the vertex.
   * @param v
   *   The index of the vertex.
   * @param oPosition
   *   The position of the vertex.
   */
  virtual HRESULT Get (int v, CATMathPoint &oPosition) const;  // To DO: Replace by pure virtual.
  //virtual HRESULT Get (int v, CATMathPoint &oPosition) const = 0;

public:
  virtual PolyPrecision GetPrecision() const;

public:

  static const CATIPolyVertexPositionConstLayer* Cast (const CATIPolyLayer*);
  static CATIPolyVertexPositionConstLayer* Cast (CATIPolyLayer*);

  static const CLSID& ClassID ();
  const CLSID& GetClassID () const;

};

#endif // !CATIPolyVertexPositionConstLayer_H
