//==================================================================-*- C++ -*-
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// Layer of per-vertex normal interface
//
//=============================================================================
// 2008-05-28   BPG: New.
//=============================================================================
#ifndef CATIPolySurfaceVertexNormalConstLayer_H
#define CATIPolySurfaceVertexNormalConstLayer_H

#include "PolyhedralAttributes.h"
#include "CATErrorDef.h"
#include "CATIPolyDoublesLayer.h"
#include "Poly/Precision.h"

class CATMathVector;
class CATIPolySurfaceVertexNormalLayer;


/**
* Interface to a surface vertex normal const layer.
* 
* Given a surface vertex, this interface returns its normal.
*/
class ExportedByPolyhedralAttributes CATIPolySurfaceVertexNormalConstLayer : public CATIPolyDoublesLayer
{

public:

  unsigned int GetDimension () const { return 3; }

  virtual HRESULT Set (int v, const double* a) { return S_FALSE; }
  virtual HRESULT Get (int v, double* a) const;

public:
  /**
   * Returns the components of the normal.
   * @param v
   *   The index of a valid vertex.
   * @param nx, ny, nz
   *   The three components of the normal.
   */
  virtual HRESULT Get (int v, double& nx, double& ny, double& nz) const;  // To DO: Replace by pure virtual.
  //virtual HRESULT Get (int v, double& nx, double& ny, double& nz) const = 0; 

  /**
   * Returns the normal defined at a vertex.
   * @param v
   *   The index of the vertex.
   * @param oNormal
   *   The normal at the vertex.
   */
  virtual HRESULT Get (int v, CATMathVector &oNormal) const = 0;

  /**
   * Returns <tt>S_OK</tt> if the layer has a unique normal (case of a planar surface) and 
   * <tt>S_FALSE</tt> otherwise.
   * @param oNormal
   *   The unique normal to the surface.
   */
  virtual HRESULT HasUniqueNormal (CATMathVector& oNormal) const;  // To DO: Replace by pure virtual.
  //virtual HRESULT HasUniqueNormal (CATMathVector& oNormal) const = 0; 

public:
  virtual PolyPrecision GetPrecision() const;

public:

  static const CATIPolySurfaceVertexNormalConstLayer* Cast (const CATIPolyLayer*);
  static CATIPolySurfaceVertexNormalConstLayer* Cast (CATIPolyLayer*);

  static const CLSID& ClassID ();
  const CLSID& GetClassID () const;

  /**
   * Casts as a non-const layer.
   */
  virtual CATIPolySurfaceVertexNormalLayer* NonConstCast ();

private:

  static const CLSID _ClassID;

protected:

  virtual ~CATIPolySurfaceVertexNormalConstLayer () {}

};

#endif // !CATIPolySurfaceVertexNormalConstLayer_H
