//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATPolyBodyBuilder.h
//
//=============================================================================
// 2008-10-28 NDO
//=============================================================================
#ifndef CATPolyBodyBuilder_H
#define CATPolyBodyBuilder_H

#include "CATBoolean.h"
#include "CATErrorDef.h"

#include "PolyBodyTools.h"
#include "CATPolyBody.h"
#include "CATMapOfIntToPtr.h"
#include "CATPolyDeprecated.h"

class CATIPolySurface;
class CATIPolyCurve;
class CATPolyFace;
class CATPolyVertex;


/*
Build a CATPolyBody including its CATPolyVertex, CATPolyEdge and CATPolyFace from 
points, CATIPolyCurve's and CATIPolySurface's.
This class supports only CATIPolySurface's that can be casted as CATIPolyMesh's.
*/
class ExportedByPolyBodyTools CATPolyBodyBuilder
{

public:

  CATPolyBodyBuilder ();
  ~CATPolyBodyBuilder ();

public:

  POLY_DEPRECATED ("Use Poly::MakeVertex () from CATPolyNativeServices",
                   HRESULT MakeVertex (const CATMathPoint& iPosition, CATPolyVertex*& oPolyVertex));

  POLY_DEPRECATED ("Use Poly::MakeVertex () from CATPolyNativeServices",
                    HRESULT MakeVertex (CATIPolyCurve& iPolyCurve, const int iCurveVertex, CATPolyVertex*& oPolyVertex));

  POLY_DEPRECATED ("Use Poly::MakeVertex () from CATPolyNativeServices",
                   HRESULT MakeFaceVertex (CATPolyFace& iPolyFace, CATIPolyMesh& iPolyMesh, const int iMeshVertex, CATPolyVertex*& oPolyVertex));

public:

  /*
   * Create a CATPolyEdge given its two start vertex and a curve.
   */
  HRESULT MakeEdge (CATPolyVertex& iPolyVertexS, CATPolyVertex& iPolyVertexE, 
                    CATIPolyCurve& iPolyCurve, CATPolyEdge*& oPolyEdge);

  /*
   * Create a CATPolyEdge on a CATPolyFace.
   */
  HRESULT MakeFaceEdge (CATPolyFace& iPolyFace, 
                        CATPolyVertex& iPolyVertexS, CATPolyVertex& iPolyVertexE,
                        CATIPolySurfaceVertexLine& iPolyCurve,
                        CATPolyEdge*& oPolyEdge);

public:

  /*
   * Create a CATPolyFace given a CATIPolySurface.
   * This CATPolyFace is not bounded by any CATPolyEdge's.
   */
  HRESULT MakeFace (CATIPolySurface& iPolySurface, CATPolyFace*& oPolyFace);

public:

  /*
   * Add a CATPolyVertex on the boundary of the CATPolyFace.
   * This requires the index of the vertex on the underlying CATIPolySurface.
   * This method works only if the surface of the CATPolyFace, a CATIPolySurface, can be casted as a CATIPolyMesh.
   */
  HRESULT FaceAddVertex (CATPolyFace& iPolyFace, const int iMeshVertex,
                         CATPolyVertex& iPolyVertex);

  /*
   * Add a CATPolyEdge on the boundary of the CATPolyFace.
   * This method works only if the surface of the CATPolyFace, a CATIPolySurface, can be casted as a CATIPolyMesh.
   */
  HRESULT FaceAddEdge (CATPolyFace& iPolyFace, CATPolyEdge& iPolyEdge, CATIPolySurfaceVertexLine& iPolyCurve);

public:

  /*
   * Detach the CATPolyBody from the builder.  
   * The caller becomes responsible of the life cycle of the object.
   */
  inline CATPolyBody* DetachBody ();

private:

  CATPolyBody* _PolyBody;

};


inline CATPolyBody* CATPolyBodyBuilder::DetachBody ()
{
  CATPolyBody* polyBody = _PolyBody;
  _PolyBody = 0;
  return polyBody;
}

#endif // CATPolyBodyBuilder_H
