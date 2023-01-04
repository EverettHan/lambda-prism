// COPYRIGHT DASSAULT SYSTEMES 2003-2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyUtil.h
//
//===================================================================
// Sep 2009 Move GetCurve and IsBarOnEdge from refiner tools : JS9
// Sep 2003 Creation: MNA
//===================================================================
#ifndef CATPolyBodyUtil_h
#define CATPolyBodyUtil_h

#include "PolyBodyTools.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

#include "CATPolyBodyServices.h"
#include "CATPolySurfaceBarServices.h"

// Polyhedral
class CATPolyBody;
class CATPolyEdge;
class CATPolyVertex;
class CATIPolySurfaceIterator;
class CATIPolySurfaceVertexCellConstLayer;
class CATIPolySurface;
class CATIPolyCurve;
class CATIPolyPoint;
class CATPolyStreamRecord;
class CATPolyUnstreamRecord;

// Other
class CATMathBox;
class CATMathTransformation;

class CATUnicodeString;

class CATIPolyBodyFrameLayers;


/**
* Class providing useful services operating on a CATPolyBody.
*/
class ExportedByPolyBodyTools CATPolyBodyUtil
{

public:

  /**
   * Returns an iterator to iterate through all the surfaces associated to the CATPolyFace of a CATPolyBody.
   * @param iPolyBody
   *   The input CATPolyBody.
   * @return
   *   A CATIPolySurface iterator.  The iterator must be deleted.
   */
  static CATIPolySurfaceIterator* GetSurfaceIterator (CATPolyBody& iPolyBody);

public:

  /**
   * Returns the poly curve lying on a surface given its poly edge.
   * @param iSurface
   *   The input CATIPolySurface.
   * @param iEdge
   *   The input CATPolyEdge.
   * @return
   *   The CATIPolyCurve lying on the CATIPolySurface.
   */
  static CATIPolyCurve* GetCurve (const CATIPolySurface& iSurface, const CATPolyEdge& iEdge);

  /**
   * @see CATPolyGetACurve.
   */
  static CATIPolyCurve* GetACurve (const CATPolyEdge& iEdge) {return CATPolyGetACurve ((CATPolyEdge*) &iEdge);}

public:

  /**
   * Returns the poly point lying on a surface given its poly vertex.
   * @param iSurface
   *   The input CATIPolySurface.
   * @param iVertex
   *   The input CATPolyVertex.
   * @return
   *   The CATIPolyPoint lying on the CATIPolySurface.
   */
  static CATIPolyPoint* GetPoint (const CATIPolySurface& iSurface, const CATPolyVertex& iVertex);

  /**
   * Returns the poly point associated to a CATPolyVertex that is not a surface vertex.
   * @param iVertex
   *   The input CATPolyVertex.
   * @return
   *   The CATIPolyPoint if there is a point that is not a surface vertex.
   */
  static CATIPolyPoint* GetPoint (const CATPolyVertex& iVertex);

  /**
   * @see CATPolyGetAPoint.
   */
  static CATIPolyPoint* GetAPoint (const CATPolyVertex& iVertex) {return CATPolyGetAPoint ((CATPolyVertex*) &iVertex);}

public:

  /**
   * @see CATPolyIsBarOnAnEdge.
   */
  static CATPolyEdge* IsBarOnAnEdge (const CATIPolySurface& iPolySurface,
                                     const CATIPolySurfaceVertexCellConstLayer& iCellLayer,
                                     const int iSurfaceVertex1, const int iSurfaceVertex2,
                                     int& oEdgePoint1, int& oEdgePoint2)
  {
    return CATPolyIsBarOnAnEdge (iPolySurface, iCellLayer, iSurfaceVertex1, iSurfaceVertex2, oEdgePoint1, oEdgePoint2);
  }

public:

  /**
   * Obsolete.
   * Call Poly::ComputeBoundingBox ().
   * See CATPolyBodyServices.h
   */
  static void ComputePolyBodyBoundingBox (const CATPolyBody& iPolyBody, CATMathBox& oBoundingBox, CATMathTransformation* iBodyPosition = 0);
  
  /**
   * Computes an approximation of the bounding box of the CATPolyBody with multi layer information
   * @param iPolyBody
   *   The input CATPolyBody.
   * @param CATIPolyBodyFrameLayers
   *   The input layers
   * @param oBoundingBox
   *   The computed bounding box.
   * @param iBodyPosition
   *   The position of the CATPolyBody.
   */
  static void ComputePolyBodyMultiLayerBoundingBox (const CATPolyBody& iPolyBody, const CATIPolyBodyFrameLayers& iFrameLayers, CATMathBox& oBoundingBox, CATMathTransformation* iBodyPosition = 0);


  /**
   * Returns the number of vertices and triangles of a CATPolyBody.
   * @param iPolyBody
   *   The input CATPolyBody.
   * @param oNbVertices
   *   The output number of vertices.
   * @param oNbTriangles
   *   The output number of triangles.
   * @return
   *   HRESULT
   */
  static HRESULT GetPolyBodyNbVerticesAndTriangles (const CATPolyBody& iPolyBody, int& oNbVertices, int& oNbTriangles);

   /**
   * For Refinable Mesh
   * Returns the number of vertices and triangles of a CATPolyBody basing on Base Mesh
   * @param iPolyBody
   *   The input CATPolyBody.
   * @param oNbVertices
   *   The output number of vertices in base mesh
   * @param oNbTriangles
   *   The output number of triangles in base mesh
   * @return
   *   HRESULT
   */
  static HRESULT GetPolyBodyNbVerticesAndTrianglesInBaseMesh (const CATPolyBody& iPolyBody, int& oNbVertices, int& oNbTriangles);

};


#endif
