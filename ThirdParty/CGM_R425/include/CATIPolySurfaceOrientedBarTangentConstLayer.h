// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolySurfaceOrientedBarTangentConstLayer.h
//
//===================================================================
// May 2010  Creation: NDO
//===================================================================
#ifndef CATIPolySurfaceOrientedBarTangentConstLayer_H
#define CATIPolySurfaceOrientedBarTangentConstLayer_H

#include "PolyhedralAttributes.h"
#include "CATIPolyLayer.h"
#include "CATErrorDef.h"

class CATMathVector;
class CATIPolySurfaceOrientedBarTangentLayer;


class ExportedByPolyhedralAttributes CATIPolySurfaceOrientedBarTangentConstLayer : public CATIPolyLayer
{

public:

  /**
   * Returns the tangent associated to an oriented bar defined by the pair (v0, v1).  (From v0 to v1.)
   * @param v0
   *   The start vertex of the bar.
   * @param v1
   *   The end vertex of the bar.
   * @param oTangent
   *   The returned tangent vector.
   * @return
   *   S_OK if a valid tangent is returned in oTangent.
   *   S_FALSE if no tangent is associated to the bar defined by (v0, v1).
   *   E_FAIL if the pair (v0, v1) does not define a bar or any other error.
   */
  virtual HRESULT Get(int v0, int v1, CATMathVector &oTangent) const = 0;

public:

  static const CATIPolySurfaceOrientedBarTangentConstLayer* Cast (const CATIPolyLayer*);
  static CATIPolySurfaceOrientedBarTangentConstLayer* Cast (CATIPolyLayer*);

  static const CLSID& ClassID ();
  const CLSID& GetClassID () const;

  /**
   * Casts as a non-const layer.
   */
  virtual CATIPolySurfaceOrientedBarTangentLayer* NonConstCast ();

  unsigned int GetDimension () const;

private:

  static const CLSID _ClassID;

protected:

  virtual ~CATIPolySurfaceOrientedBarTangentConstLayer () {}

};

#endif // !CATIPolySurfaceOrientedBarTangentConstLayer_H
