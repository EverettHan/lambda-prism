// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolySurfaceVertexUVConstLayer.h
//
//===================================================================
// May 2010  Creation: NDO
//===================================================================
#ifndef CATIPolySurfaceVertexUVConstLayer_H
#define CATIPolySurfaceVertexUVConstLayer_H

#include "PolyhedralAttributes.h"

#include "CATErrorDef.h"
#include "CATIPolyDoublesLayer.h"


class CATIPolySurfaceVertexUVLayer;


/**
* Interface to a surface vertex UV const layer.
*
* Given a surface vertex, this interface returns its UV.
*/
class ExportedByPolyhedralAttributes CATIPolySurfaceVertexUVConstLayer : public CATIPolyDoublesLayer
{

public:

  unsigned int GetDimension () const { return 2; }

  virtual HRESULT Set (int v, const double* a) { return S_FALSE; }
  virtual HRESULT Get (int v, double* a) const;

public:

  virtual HRESULT Get (int iVertex, double& u, double& v) const = 0;

public:

  static const CATIPolySurfaceVertexUVConstLayer* Cast (const CATIPolyLayer*);
  static CATIPolySurfaceVertexUVConstLayer* Cast (CATIPolyLayer*);

  static const CLSID& ClassID ();
  const CLSID& GetClassID () const;

  /**
   * Casts as a non-const layer.
   */
  virtual CATIPolySurfaceVertexUVLayer* NonConstCast ();

private:

  static const CLSID _ClassID;

};

#endif // !CATIPolySurfaceVertexUVConstLayer_H
