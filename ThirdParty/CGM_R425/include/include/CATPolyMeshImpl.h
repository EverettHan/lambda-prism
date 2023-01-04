//=============================================================================
// COPYRIGHT Dassault Systemes 2004, 2007
//=============================================================================
//
// CATPolyMeshImpl.h
// Polyhedral triangle mesh (aka CATIPolyMesh) reference implementaion
//
//=============================================================================
// 2019-05-02   JXO: CATUnicodeString identifier for textures
// 2012-01-03   JXO: HasVertexNormalLayer & AddVertexNormalLayer
// 2007-07-23   NDO: Added helper function FindVertex.
// 2007-02-13   BPG: Move declarations upside down.
// 2006-01-04   NDO: Remove IsTriangleDirect.
// 2005-11-09   JLH: Add InvertTriangle method.
// 2005-05-02   NDO: Add the method IsTriangleDirect (),
// 2005-04-29   NDO: Add two new methods IsVertexManifold () and IsBarManifold ().
// 2005-04-21   NDO: Add support for vertex and triangle attributes.
// 2005-01-21   JLH: The methods "_Is***Defined" get a more canonical writing
// 2004-12-22   JLH: Add the method "Compact (ioIdxVertices, ioIdxTriangles)"
// 2004-09-14   JLH: Add the methods "AddVertices"
// 2004-08-03   NDO: Add the methods about the "Hole bars".
// 2004-07-13   JLH: Creation
//=============================================================================
#pragma once

#include "PolyMeshImpl.h"
#include "CATIPolyMesh.h"
#include "CATPolyMeshBase.h"
#include "CATPolyMeshImplVertices.h"
#include "CATPolyLayerObserverContainer.h"
#include "CATListOfInt.h"
#include "CATMathBox.h"
#include "CATBoolean.h"
#include "Poly/Precision.h"

#include "CATPolyBuckets_T.h"
#include "CATUnicodeString.h"

class CATPolyMeshImplVertexPositionLayer;
class CATPolyMeshImplVertexNormalLayer;
//class CATPolyMeshImplVertexUVLayer;
class CATPolySurfaceVertexNNormalsLayer;
class CATIPolyVertexFloatPositionConstLayer;
class CATIPolyVertexFloatNormalConstLayer;
class CATPolyMeshImpVertexFacetNeighborhood;
class CATMathPoint;
class CATMathVector;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Poly
{
  ExportedByPolyMeshImpl HRESULT AddNewLayer (CATIPolySurface&, const CATUnicodeString&, PolyPrecision, CATIPolySurfaceVertexPositionLayer*&);
}
#endif


/**
 * Implementation of a fully editable triangular mesh.
 */
class ExportedByPolyMeshImpl CATPolyMeshImpl : public CATPolyMeshBase
{

public:

/** @name Life Cycle
    @{ */

  /**
   * Creates an instance of a CATPolyMeshImpl without any layer.
   * This instance has no vertex position layer.
   */
  static CATPolyMeshImpl* New ();

  /**
   * Creates an instance of a CATPolyMeshImpl with the vertex-position layer in float or double precision.
   * The optional vertex-normal layer is in float precision.
   * The optional vertex-UV layer is in double precision.
   * @param iFloatOrDouble
   *   Precision of the vertex-position layer: Poly::Precision::eFloat or Poly::Precision::eDouble.
   * @param iWithVertexNormalLayer
   *   Optional vertex-normal layer.
   * @param iWithVertexUVLayer
   *   Optional vertex-UV layer.
   * @return
   *   A new CATIPolyMesh instance or 0 on memory allocation failure.
   */
#ifndef _AIX_SOURCE
  static CATPolyMeshImpl* New (Poly::Precision iFloatOrDouble,
    CATBoolean iWithVertexNormalLayer, CATBoolean iWithVertexUVLayer = FALSE);
#else
  static CATPolyMeshImpl* New (PrecisionVertexPosition iFloatOrDouble,
    CATBoolean iWithVertexNormalLayer, CATBoolean iWithVertexUVLayer = FALSE);
#endif

  /**
   * @deprecated
   */
  POLY_DEPRECATED ("Call New (Poly::Precision iFloatOrDouble, CATBoolean iWithVertexNormalLayer, CATBoolean iWithVertexUVLayer = FALSE);",
  static CATPolyMeshImpl* New (CATBoolean iWithVertexNormalLayer, CATBoolean iWithVertexUVLayer)
    {return New ((PrecisionVertexPosition) Poly::Precision::eFloat, iWithVertexNormalLayer, iWithVertexUVLayer);})

  /**
   * @deprecated
   */
  POLY_DEPRECATED ("Call New (Poly::Precision iFloatOrDouble, CATBoolean iWithVertexNormalLayer, CATBoolean iWithVertexUVLayer = FALSE);",
  static CATPolyMeshImpl* New (CATBoolean iWithVertexNormalLayer, CATBoolean iWithVertexUVLayer, PrecisionVertexPosition iFloatOrDouble)
    {return New (iFloatOrDouble, iWithVertexNormalLayer, iWithVertexUVLayer);})

  /**
   * @deprecated
   */
  POLY_DEPRECATED ("Call New (Poly::Precision iFloatOrDouble, CATBoolean iWithVertexNormalLayer, CATBoolean iWithVertexUVLayer = FALSE);",
  static CATPolyMeshImpl* New (CATBoolean iWithVertexNormalLayer, CATBoolean iWithVertexUVLayer, CATBoolean)
    {return New ((PrecisionVertexPosition) Poly::Precision::eFloat, iWithVertexNormalLayer, iWithVertexUVLayer);})

  virtual ~CATPolyMeshImpl ();

  /**
   * Returns <tt>TRUE</tt> if the mesh has vertex position and normal layers
   * in double precision and <tt>FALSE</tt> otherwise for float precision.
   */
  inline CATBoolean HasDoublePrecisionVertexLayers () const;

  /**
   * @see CATIPolyObject
   */
  typedef PrecisionVertexPosition LayerPrecision;

/** @} */

public:

/** @name Casting Methods.
    @{ */

  /**
   * Casts a const CATIPolySurface as a const CATPolyMeshImpl.
   */
  static const CATPolyMeshImpl* Cast (const CATIPolySurface* iSurface);

  /**
   * Casts a CATIPolySurface as a CATPolyMeshImpl.
   */
  static CATPolyMeshImpl* Cast (CATIPolySurface* iSurface);

/** @} */

public:

/** @name Vertices management
    @{ */

  int GetNbVertices () const;

  HRESULT AddVertex (int &v);
  HRESULT AddVertex (const CATMathPoint &P, int &v);

  HRESULT RemoveVertex (const int v);

/** @} */

public:

/** @name Triangles Management
    @{ */

  int GetNbFacets () const;
  int GetNbTriangles () const;

  int GetMaxFacetSize () const;

  HRESULT GetTriangle (const int t, int oVertices[3]) const;

  HRESULT AddTriangle (const int iVertices[3], int &t);
  HRESULT RemoveTriangle (const int t, const CATBoolean iRemoveUnreferencedVertices = FALSE);

/** @} */

public:

/** @name Iterators
    @{ */

  HRESULT GetVertexIterator (CATIPolySurfaceVertexIterator *&oIterator) const;

  HRESULT GetFacetIterator (CATIPolySurfaceFacetIterator *&oIterator) const;

  HRESULT GetTriangleIterator (CATIPolyMeshTriangleIterator *&oIterator) const;
  HRESULT GetTriangleIterator (CATIPolyMeshTriangleVertexIterator *&oIterator) const;

/** @} */

public:

/** @name Neighborhood
    @{ */

  HRESULT GetVertexFacetNeighborhood (CATIPolySurfaceVertexFacetNeighborhood *&oNeighborhood) const;

/** @} */

public:

/** @name Const Layers
    @{ */

  /**
   * @param oLayer [out, IUnknown#Release]
   */
  HRESULT GetVertexPositionLayer (CATIPolySurfaceVertexPositionConstLayer *&oLayer) const;
  /**
   * @param oLayer [out, IUnknown#Release]
   */
  HRESULT GetVertexNormalLayer (CATIPolySurfaceVertexNormalConstLayer *&oLayer) const;
  /**
   * @param oLayer [out, IUnknown#Release]
   */
  HRESULT GetVertexUVLayer (CATIPolySurfaceVertexUVConstLayer *&oLayer) const;
  /**
   * @param oLayer [out, IUnknown#Release]
   */
  HRESULT GetVertexTextureCoordLayer (CATIPolySurfaceVertexTextureCoordConstLayer *&oLayer) const;
  /**
   * @param oLayer [out, IUnknown#Release]
   */
  HRESULT GetOrientedBarTangentLayer (CATIPolySurfaceOrientedBarTangentConstLayer *&oLayer) const;

  HRESULT GetBoundingBox (CATMathBox &oBBox) const;

  /**
   * Returns the native vertex position layer.
   */
  HRESULT GetVertexPositionLayer (CATIPolyVertexFloatPositionConstLayer *&oLayer) const;

  /**
   * Returns the native vertex normal layer.
   */
  HRESULT GetVertexNormalLayer (CATIPolyVertexFloatNormalConstLayer *&oLayer) const;

/** @} */

public:

/** @name Layers
    @{ */

  /**
   * @param oLayer [out, IUnknown#Release]
   */
  HRESULT GetVertexPositionLayer (CATIPolySurfaceVertexPositionLayer *&oLayer);
  /**
   * @param oLayer [out, IUnknown#Release]
   */
  HRESULT GetVertexNormalLayer (CATIPolySurfaceVertexNormalLayer *&oLayer);
  /**
   * @param oLayer [out, IUnknown#Release]
   */
  HRESULT GetVertexUVLayer (CATIPolySurfaceVertexUVLayer *&oLayer);
  /**
   * @param oLayer [out, IUnknown#Release]
   */
  HRESULT GetVertexTextureCoordLayer (CATIPolySurfaceVertexTextureCoordLayer *&oLayer);
  /**
   * @param oLayer [out, IUnknown#Release]
   */
  HRESULT GetOrientedBarTangentLayer (CATIPolySurfaceOrientedBarTangentLayer *&oLayer);

/** @} */


public:

/** @name Data Layers
    @{ */

  HRESULT AddLayer (CATIPolyLayer& iLayer, CATIPolySurfaceObserver* obs = 0);

  HRESULT RemoveLayer (CATIPolyLayer& iLayer);

  /**
   * @param oLayer [out, IUnknown#Release]
   */
  HRESULT GetLayer (const CLSID& id, CATIPolyLayer*& oLayer) const;

  bool HasLayer (const CLSID& id) const;

  /**
   * @param oLayerIterator [out, IUnknown#Release]
   */
  HRESULT GetLayerIterator (const CLSID& id, CATIPolyLayerIterator*& oLayerIterator) const;

  /**
   * @param oLayerIterator [out, IUnknown#Release]
   */
  HRESULT GetLayerIterator (CATIPolyLayerIterator*& oLayerIterator) const;

  /**
  * @param oLayerIterator [out, IUnknown#Release]
  * Non-added layers are:
  *   * Layer returned by GetVertexPositionLayer ()
  *   * Layer returned by GetVertexNormalLayer ()
  *   * Layer returned by GetVertexUVLayer ()
  */
  HRESULT GetLayerIterator (CATIPolyLayerIterator*& oLayerIterator, bool excludeNonAddedLayers) const;

/** @} */

protected:

  inline bool HasVertexPositionLayer () const;

  // Reserved.
  HRESULT AddVertexPositionLayer (CATPolyMeshImplVertexPositionLayer* iLayer);

public:

/** @name Normal Layers
    @{ */

  /**
   * Returns TRUE if the mesh has a vertex normal layer.
   */
  inline CATBoolean HasVertexNormalLayer () const;

  /**
   * Adds a vertex normal layer if none is available.
   * This method does not initialize or compute the normals.
   * It is up to the caller to set the normals.
   */
  HRESULT AddVertexNormalLayer ();

/** @} */

public:

/** @name Adding Texture Layer
    @{ */

  /**
   * Returns TRUE if the mesh has a vertex texture coordinates layer.
   */
  CATBoolean HasVertexTextureCoordLayer () const;

  /**
   * Adds a vertex texture coordinates layer if none is available.
   * This method does not initialize the texture coordinates.
   * It is up to the caller to set the texture coordinates.
   */
  HRESULT AddVertexTextureCoordLayer (const CATUnicodeString & iTextureIdentifier = "DEFAULT_TC_SET");

/** @} */

public:

/** @name Topology services
    @{ */

  HRESULT FlipBar (const int v0, const int v1);
  HRESULT SplitBar (const int v0, const int v1, int &n);
  HRESULT MergeVertices (const int v0, const int v1);

/** @} */

public:

/** @name Event Listener
    @{ */

  HRESULT RegisterObserver (CATIPolySurfaceObserver& iObserver);

  HRESULT UnregisterObserver (CATIPolySurfaceObserver& iObserver);

/** @} */

public:

/** @name Visitors
    @{ */

  HRESULT Accept (const CATIPolySurface &iM, CATPolySurfaceConstVisitor &iV) const;

  HRESULT Accept (CATIPolySurface &iM, CATPolySurfaceVisitor &iV);

/** @} */

public:

/** @name Tools
    @{ */

  CATIPolySurfaceConstTools* GetConstTools () const;
  CATIPolySurfaceTools* GetTools ();

  CATBoolean IsEditable () const;

/** @} */

public:

/** @name Storage
    @{ */

  HRESULT Compact ();
  HRESULT Compact (CATMapOfIntToInt& ioVertexMap, CATMapOfIntToInt& ioTriangleMap);

  // This method is replaced by Compact (CATMapOfIntToInt& ioVertexMap, CATMapOfIntToInt& ioTriangleMap).
  // To get rid of.
  HRESULT Compact (int*& ioIdxVertices, int*& ioIdxTriangles); 

  HRESULT Reserve (int iNbVertices, int iNbTriangles);

/** @} */

public:

/** @name Internal Usage
    @{ */

  inline int FinalGetMaxVertexIndex () const;
  inline CATBoolean FinalIsVertexDefined (int v) const;

  inline int FinalGetMaxTriangleIndex () const;
  inline CATBoolean FinalIsTriangleDefined (int t) const;

  HRESULT ComputeBoundingBox(CATMathBox &oBBox) const;

/** @} */

public:

  // More methods with deprecated interfaces.
  // Ok to call these methods for a CATPolyMeshImpl implementation.
  // Not ok to call these methods from a CATIPolyMesh interface (deprecated.)

  HRESULT GetTriangleNeighborsOfVertex (const int v, CATListOfInt &oTriangles) const;

  /**
   * Retrieves the neighbor triangles of a given triangle (only works on active faces.)
   * @param iIdxTriangle
   * The index of the triangle.
   * @param oIdxNeighborTriangles
   * The index of the three neighbor triangles.
   * @return
   *   S_OK if the method runs successfully and E_FAIL otherwise. The method fails if there are non-manifold bars.
   */
  virtual HRESULT GetTriangleNeighborsOfTriangle (const int t, int oTriangles[3]) const;

  /**
   * Returns the two triangles adjacent to a manifold bar defined by two vertices.
   * If the manifold bar between the two vertices does not exist, the call returns E_FAIL and:
   *   o Both oIdxTriangle1 and oIdxTriangle2 are set to 0, if there are no triangles adjacent to the bar.
   *   o Both oIdxTriangle1 and oIdxTriangle2 are set to -1 if there are more than two triangles adjacent to the bar.
   * If the bar is adjacent to only one triangle, then one of the returned triangle is set to 0.
   */
  virtual HRESULT GetTriangleNeighborsOfBar (const int v0, const int v1, int &t0, int &t1) const;

  /**
   * Returns all the triangles sharing the bar defined by two vertices.
   * The two vertices must be on active faces otherwise the call fails.
   * The method will return only the triangles that are on active faces.
   */
  virtual HRESULT GetTriangleNeighborsOfBar (const int v0, const int v1, CATListOfInt &oTriangles) const;

public:

  //
  // Obsolete.
  // Should not be using these methods. Use instead layers, iterators, neighborhoods and services.
  //

  HRESULT GetVertexPosition(const int v, CATMathPoint &P) const;

  CATBoolean IsVertexDefined(const int v) const;
  CATBoolean IsVertexReferenced(const int v) const;
  int GetMinVertexIndex() const;  // See CATPolyGetVertexRange.
  int GetMaxVertexIndex() const;  // See CATPolyGetVertexRange.

  CATBoolean IsTriangleDefined(const int t) const;
  int GetMinTriangleIndex() const;
  int GetMaxTriangleIndex() const;

  HRESULT GetTriangle(const int t, int oVertices[3], int oNeighbors[3]) const;

  HRESULT GetFacet(const int f, CATListOfInt &oVertices) const;

  HRESULT GetTrianglePoints(const int t,
                            CATMathPoint &P1, CATMathPoint &P2, CATMathPoint &P3) const;

  HRESULT GetVertexNeighborsOfVertex(const int v, CATListOfInt &oVertices) const;

public:

  //
  // Obsolete.
  // Should not be using these methods. Use instead layers, iterators, neighborhoods and services.
  //

  // Do not use this method.
  HRESULT SetVertexPosition (const int v, const CATMathPoint &P);
  void ReactToSetVertexPosition (const int v, const CATMathPoint& P);  // Reserved.

  // Do not use this method.
  HRESULT UpdateTriangle(const int t, const int iVertices[3]);

  /**
   * Inverts the orientation of the <tt>iIdxTriangle</tt>'th triangle
   * by swapping its second and third vertices.<br>
   * @param iIdxTriangle
   * The index of the triangle to update.
   * @return
   *   S_OK if the triangle is successfully inversed and E_FAIL otherwise.
   */
  HRESULT InvertTriangle(const int t);

protected:

  /**
   * @param oLayer [out, IUnknown#Release]
   */
  HRESULT DummyGetVertexCellLayer (CATIPolySurfaceVertexCellConstLayer *&oLayer) const;

  /**
   * @param oLayer [out, IUnknown#Release]
   */
  HRESULT DummyGetVertexCellLayer (CATIPolySurfaceVertexCellLayer *&oLayer);

  HRESULT DummyAddVertices (const int iNbVertices, const float* iPoints, int &oFirstIndex);

  HRESULT DummyRemoveVertices (const CATListOfInt &iIdxVertices);

  HRESULT DummyGetVertices (CATListOfInt &oIdxVertices) const;

  HRESULT DummyAddTriangles (const int     iNbVertices,
                                const double* iCoords,
                                const int     iNbTriangles,
                                const int*    iIdxVertices,
                                const int     iIdxFace = 0) ;

  HRESULT DummyAddTriangles (const int           iNbVertices,
                                const CATMathPoint* iPoints,
                                const int           iNbTriangles,
                                const int*          iIdxVertices,
                                const int           iIdxFace = 0) ;

  HRESULT DummyGetTriangles (CATListOfInt &oIdxTriangles) const ;

  HRESULT DummyGetTriangles (int    &oNbVertices,
                                float* &ioCoords,
                                int    &oNbTriangles,
                                int*   &ioIdxVertices) const ;

  HRESULT DummyGetTriangles (int     &oNbVertices,
                                double* &ioCoords,
                                int     &oNbTriangles,
                                int*    &ioIdxVertices) const ;

  HRESULT DummyGetTriangles (int           &oNbVertices,
                                CATMathPoint* &ioPoints,
                                int           &oNbTriangles,
                                int*          &ioIdxVertices) const ;

  HRESULT DummyRemoveTriangles (const CATListOfInt &iIdxTriangles,
                                   const CATBoolean iRemoveUnreferencedVertices = FALSE);

private:

  // Triangle Data Structure

  class T_Triangle
  {
  public:
    inline T_Triangle();
    inline T_Triangle(int v0, int v1, int v2);

  public:
    inline void Recycle(int v0, int v1, int v2);
    void Absorb(T_Triangle &iRHS);

  public:
    inline CATBoolean IsDefined() const;

  public:
    inline int FindVertex(int v0) const;  // Return index of vertex in triangle: 0, 1 or 2 (or -1).
    inline int FindBar(int v0, int v1) const;  // Return index of bar in triangle: 0, 1 or 2 (or -1).
    inline int GetFirstAdjacentTriangle(int v0, int v1) const;

  public:
    unsigned int _Vertices[3];
    unsigned int _Neighbors[3];
    unsigned int _Defined :  1;

  public:
    unsigned int _Sens    :  2 ;
    unsigned int _Face    : 29 ;
  };

  class Specialize_CATPolyBuckets_T(TriangleBuckets, T_Triangle);

private:

  // Topology Helper Methods

  CATBoolean FindFirstAdjacentTriangle(int v0, int v1,
                                       int &t, int &b) const;

  void InsertTriangleInBarNeighborhood(int v0, int v1, int t, unsigned int &oTriangleNeighbor);

  HRESULT RemoveTriangleFromBarNeighborhood(int v0, int v1, int t, unsigned int iTriangleNeighbor);

private:

  CATPolyMeshImpl ();  // Private constructor.
  CATPolyMeshImpl (CATPolyMeshImpl &iOther);  // No copy constructor.

  CATPolyMeshImpl& operator= (CATPolyMeshImpl &iOther);  // No assignement operator.

private:

  // Recycling
  void PushUndefinedVertex(unsigned int v);
  unsigned int PopUndefinedVertex();

  void PushUndefinedTriangle(unsigned int t);
  unsigned int PopUndefinedTriangle();

private:

  inline int _Next(const int iTIndex) const;
  inline int _Prev(const int iTIndex) const;

  inline int _OppositeVertex(const int iITEdge) const;

  inline CATBoolean _IsAVertexOf(const int         iNoVertex,
                                 const T_Triangle &iTriangle,
                                 int              &oITVertex) const;

  inline CATBoolean _IsAnEdgeOf(const int         iNoVertex1,
                                const int         iNoVertex2,
                                const T_Triangle &iTriangle,
                                int              &oITEdge,
                                int              &oSens) const;

private:

  CATMathBox _BoundingBox;

  /**
   * Definition of various bit flags.
   */
  enum Masks
  {
    /** Bit 0: Bounding box ok. */                               MaskBoundingBoxOK           = 0x0001,
    /** Bit 1: Position and normal vertex layers in float. */    MaskVertexFloat             = 0x0002,
    /** Bit 2: Position and normal vertex layers in double. */   MaskVertexDouble            = 0x0004
  };

  unsigned int _Flags;  // Bit flags.

private:

  // Vertices.
  CATPolyMeshImplVertices _Vertices;
  int _NbVertices;
  unsigned int _FirstUndefinedVertex;

private:

  // Triangles.
  TriangleBuckets _Triangles;
  int _NbTriangles;
  unsigned int _FirstUndefinedTriangle;

private:

  // Data Layers.
  CATPolyMeshImplVertexPositionLayer* _VertexPositionLayer;
  CATPolyMeshImplVertexNormalLayer* _VertexNormalLayer;
  //CATPolyMeshImplVertexUVLayer* _VertexUVLayer;

  CATPolyLayerObserverContainer _LOL;  // List of (layer, observer) pairs.

private:

  HRESULT _GetTriangles (int           &oNbVertices,
                         float*        &ioCoordsF,
                         double*       &ioCoordsD,
                         CATMathPoint* &ioPoints,
                         int           &oNbTriangles,
                         int*          &ioNoVertices) const ;

private:

  HRESULT AddVertex(const float P[3], int &v);

  HRESULT AddVertex (const double  iPoint[3],
                     int          &oIdxVertex) ;


  HRESULT AddTriangle (const int  iIdxVertices[3],
                       int       &oIdxTriangle,
                       const int  iIdxFace) ;

  HRESULT GetTrianglesFromFace (const int     iIdxFace,
                                        CATListOfInt &oIdxTriangles) const ;

  HRESULT GetFaceFromTriangle (const int  iIdxTriangle,
                                       int       &oIdxFace) const ;

public:

  /**
   * Propagates the orientation of a triangle to all the triangles of the same connected set.
   * @param iIdxTriangle
   * The index of the triangle to which the orientation iOrientation is set.
   * The other triangles have their orientation set by propagation from this triangle.
   * If iIdxTriangle is equal to 0, then the whole mesh is processed.  The orientation of the triangles
   * of a connected set of triangles is set by propagation of the orientation of the first triangle of the set.
   * The first triangle of each connected set gets the orientation iOrientation.
   * @param iOrientation
   * Enum determining how the orientation of the triangles reached by propagation is set:
   *   O_Unset: The orientation of the triangles is set to O_Unset without any triangle inversion.
   *   O_Indirect: The orientation of iIdxTriangle (or the first triangle or each connected set if 0)
   *     is set to O_Indirect.  The orientation of the other triangles reached by propagation is set
   *     accordingly.
   *   O_Direct: The orientation of iIdxTriangle (or the first triangle or each connected set if 0)
   *     is set to O_Direct.  The orientation of the other triangles reached by propagation is set
   *     accordingly.
   *   O_Undecided: No specific choice is made regarding the orientation of the triangles.  Triangles from
   *     the same connected set have their orientation set according to the majority rule.  The largest
   *     number of triangles get the O_Direct orientation and the others the O_Indirect.
   *  @param iInvert
   *  If this argument is set to TRUE, triangles having the opposite of the desired orientation
   *  are inverted to get the same orientation.
   *  @return
   *    E_FAIL if the orientation cannot be set or is not consistent.
   *    S_OK if the orientation is properly set for the triangles.
   * @deprecated Use CATPolyMeshOrientationPropagator instead
   */
  virtual HRESULT PropagateOrientation (const int iIdxTriangle = 0,
                                        const CATIPolyMesh::Orientation iOrientation = O_Direct,
                                        const CATBoolean iInvert = FALSE) ;

private:

//--------------------------------------------------------------------------------------------------------------
// Topological services.
//--------------------------------------------------------------------------------------------------------------

   friend class CATPolyMeshImplVertexFloatPositionConstLayer;
   friend class CATPolyMeshImplVertexFloatNormalConstLayer;
   friend class CATPolyMeshImpVertexFacetNeighborhood;
   friend class CATPolySurfacePolyFaceConstVisitor;
   friend HRESULT Poly::AddNewLayer (CATIPolySurface&, const CATUnicodeString&, PolyPrecision, CATIPolySurfaceVertexPositionLayer*&);

  /**
   * Checks whether the bar composed of the two vertices is a valid bar of the mesh.
   * @param iIdxVertex1
   * The index of the first vertex in the bar.
   * @param iIdxVertex2
   * The index of the second vertex in the bar.
   * @return
   * TRUE if this is a valid bar and FALSE otherwise.
   */
  virtual CATBoolean IsBarValid (const int iIdxVertex1,
                                 const int iIdxVertex2) const ;

  /**
   * Given a vertex, returns the next vertex of the triangle.
   * @param iIdxTriangle
   * The index of the triangle.
   * @param iIdxVertex
   * The index of the vertex.
   * @return
   * The index of the next vertex.
   */
  virtual HRESULT GetNextVertex (const int  iIdxTriangle,
                                 const int  iIdxVertex,
                                 int       &oIdxNext) const ;

  /**
   * Given a vertex, returns the previous vertex of the triangle.
   * @param iIdxTriangle
   * The index of the triangle.
   * @param iIdxVertex
   * The index of the vertex.
   * @return
   * The index of the previous vertex.
   */
  virtual HRESULT GetPreviousVertex (const int  iIdxTriangle,
                                     const int  iIdxVertex,
                                     int       &oIdxPrevious) const ;

  /**
   * Returns the vertex in the triangle opposite to the bar defined by the two vertices.
   * @param iIdxTriangle
   * The index of the triangle.
   * @param iIdxVertex1
   * The index of the first vertex of the bar.
   * @param iIdxVertex2
   * The index of the second vertex of the bar.
   * @return
   * The index of the vertex opposite the bar.
   * Returns zero if the triangle is not valid or the specified vertices are not in the triangle.
   */
  virtual HRESULT GetOppositeVertex (const int  iIdxTriangle,
                                     const int  iIdxVertex1,
                                     const int  iIdxVertex2,
                                     int       &oIdxOpposite) const ;

  /**
   * Returns the vertices of a bar opposite to the specified vertex.
   * @param iIdxTriangle
   * The index of the triangle.
   * @param iIdxVertex
   * The index of a vertex in the triangle.
   * @param oIdxVertex1
   * The index of the first vertex of the opposite bar.
   * @param oIdxVertex2
   * The index of the second vertex of the opposite bar.
   * @return
   * S_OK if the method runs successfully and E_FAIL otherwise.
   */
  virtual HRESULT GetOppositeBar (const int  iIdxTriangle,
                                  const int  iIdxVertex,
                                  int       &oIdxVertex1,
                                  int       &oIdxVertex2) const ;

  /**
   * Given a triangle <tt>iIdxTriangle</tt> and a bar of the triangle <tt>(iIdxVertex1, iIdxVertex2)</tt>
   * get the third vertex <tt>iIdxVertex3</tt> and the triangle opposite the bar <tt>(iIdxVertex1, iIdxVertex3)</tt>.
   * This method gets the next triangle in the fan around <tt>iIdxVertex1</tt> and across the other bar
   * containing <tt>iIdxVertex1</tt>.
   * It can be called iteratively to fetch triangles and vertices around a vertex.
   * @param iIdxVertex1
   * The index of the vertex around which the search is performed.
   * It is the starting point of the input and output bars.
   * @param iIdxVertex2
   * The index of the vertex defining the ending point of the input bar.
   * When the method runs successfully, it is set to the ending point of the output bar.
   * @param iIdxTriangle
   * The index of the triangle.
   * If the method runs successfully, it is set to the next triangle in the fan.
   * @return
   * <tt>S_OK</tt> if the method runs successfully and the parameters are updated.
   * <tt>E_FAIL</tt> otherwise.
   *
   *           2       2       2
   *           +-------+-------+              For instance, a call to
   *          / \     / \     / \               GetNextVertexAndTriangle (vertex1, vertex2, triangle) ;
   *         /   \   /   \   /   \            with
   *       2/     \b/     \c/     \2            vertex1 = a, vertex2 = b, triangle = T1,
   *       +-------+-------+-------+          results in:
   *      / \     / \ T1  / \     / \           vertex1 = a, vertex2 = c, triangle = T2.
   *     /   \   /   \   /   \   /   \
   *   2/     \g/ T6  \a/  T2 \d/     \2
   *   +-------+-------+-------+-------+
   *    \     / \ T5  / \  T3 / \     /
   *     \   /   \   /   \   /   \   /
   *      \2/     \f/ T4  \e/     \2/
   *       +-------+-------+-------+
   *        \     / \     / \     /
   *         \   /   \   /   \   /
   *          \2/     \2/     \2/
   *           +-------+-------+
   */
  virtual HRESULT GetNextVertexAndTriangle (const int  iIdxVertex1,
                                            int       &ioIdxVertex2,
                                            int       &ioIdxTriangle) const ;


  /**
   * Tests if a vertex is on a hole.
   * @param iIdxVertex
   * The index of the vertex.
   * @return
   * TRUE if the vertex is on a hole. This will the case if the vertex
   * is shared by a bar which itself is referenced by only one triangle.
   * FALSE otherwise.
   */
  virtual CATBoolean IsHoleVertex (const int iIdxVertex) const ;

  /**
   * Tests if an bar is on a hole.
   * @param iIdxVertex1
   * The index of the first vertex of the bar.
   * @param iIdxVertex2
   * The index of the second vertex of the bar.
   * @return
   * TRUE if the bar is on a hole and FALSE otherwise..
   */
  virtual CATBoolean IsHoleBar (const int iIdxVertex1,
                                const int iIdxVertex2) const ;

  /**
   * Given a free bar defined by (iIdxVertex1, iIdxVertex2),
   * returns the vertex along the same hole that is a neighbor of iIdxVertex0
   * and different from iIdxVertex1.
   * @param iIdxVertex1
   * The first vertex of the bar.
   * @param iIdxVertex2
   * The second vertex of the bar.
   * @param oIdxNext
   * The neighbor of iIdxVertex0 along the same hole.
   * @return
   * Return E_FAIL if no such vertex can be found.
   */
  virtual HRESULT GetNextHoleVertex (const int  iIdxVertex1,
                                     const int  iIdxVertex2,
                                     int       &oIdxNext) const ;

  /**
   * Gets the next bar along the hole from a bar in a triangle.  The given bar must be
   * a hole bar of the triangle.
   * Returns <tt>S_OK<\tt> if the method runs successfully and <tt>E_FAIL<\tt> otherwise.
   * @param iIdxTriangle
   * The index of the triangle to which the current bar belongs.  This triangle
   * number is updated to point to the next triangle along the hole if the method
   * runs successfully.
   * @param iIdxVertex1
   * The index of the start vertex of the bar.  This vertex number is updated to
   * point to the start vertex of the next bar along the hole (that is iIdxVertex2).
   * @param iIdxVertex2
   * The index of the end vertex of the bar.  This vertex number is updated to
   * point to the end vertex of the next bar along the hole.
   * @return
   * <tt>S_OK<\tt> if the method runs succesfully and <tt>E_FAIL<\tt> otherwise.
   */
  virtual HRESULT GetNextHoleBar (int &ioIdxTriangle,
                                  int &ioIdxVertex1,
                                  int &ioIdxVertex2) const ;

  /**
   * Returns the bars (if any) of the triangle that lie on a hole.
   * @param iIdxTriangle
   * The index of the triangle.
   * @param oIdxVertices
   * The indices of the bar vertices that lie on a hole.
   * Each bar is defined by a pair of vertices:
   * (vrtx[0], vrtx[1]), (vrtx[2], vrtx[3]) and (vrtx[4], vrtx[5]).
   * This array fills in in the order in which free bars are found.
   * That is if only one hole is found then only (vrtx[0], vrtx[1]) is
   * defined.  The other vertices will be set to 0.
   * @param oNbBars
   * The number of free bars.
   * @return
   * S_OK if the method runs successfully and E_FAIL otherwise.
   */
  virtual HRESULT GetHoleBarsFromTriangle (const int  iIdxTriangle,
                                           int        oIdxVertices[6],
                                           int       &oNbBars) const ;

  /**
   * Given a vertex on a hole, the method returns the two vertex neighbors that lie
   * also on a hole.
   * @param iIdxVertex0
   * The index of a hole vertex.
   * @param oIdxVertex1
   * One neighbor of the vertex.
   * @param oIdxVertex2
   * A second neighbor of the vertex.
   * @return
   * S_OK if the method runs successfully and E_FAIL otherwise.
   */
  virtual HRESULT GetHoleVertexNeighbors (const int  iIdxVertex0,
                                          int       &oIdxVertex1,
                                          int       &oIdxVertex2) const ;

  /**
   * Retrieves the vertices of a bar of the triangle.
   * @param iIdxTriangle
   * The index of the triangle whose bar vertices are desired.
   * <b>Legal values</b>: 1 to the number of triangles, inclusive.
   * @param iIdxEdge
   * The bar index in the triangle.
   * <b>Legal values</b>: 0, 1, or 2.
   * @param oIdxVertex1
   * The first vertex of the bar.
   * @param oIdxVertex2
   * The second vertex of the bar.
   * @return
   * S_OK if the method runs successfully and E_FAIL otherwise.
   */
  virtual HRESULT GetVerticesFromBarIndex (const int  iIdxTriangle,
                                           const int  iIdxEdge,
                                           int       &oIdxVertex1,
                                           int       &oIdxVertex2) const ;

  /**
   * Retrieves the bar index in a given triangle.
   * @param iIdxTriangle
   * The index of the triangle.
   * <b>Legal values</b>: 1 to the number of triangles, inclusive.
   * @param iIdxVertex1
   * The first vertex of the bar.
   * @param iIdxVertex2
   * The second vertex of the bar.
   * @param oIdxEdge
   * The bar index in the triangle.
   * <b>Legal values</b>: 0, 1, or 2.
   * @return
   * S_OK if the method runs successfully and E_FAIL otherwise.
   */
  virtual HRESULT GetBarIndex (const int  iIdxTriangle,
                               const int  iIdxVertex1,
                               const int  iIdxVertex2,
                               int       &oIdxEdge) const ;

  /**
   * Returns the index of a vertex in the triangle.
   * @param iIdxTriangle.
   * The index of the triangle.
   * <b>Legal values</b>: 1 to the number of triangles, inclusive.
   * @param iIdxVertex
   * The index of the vertex.
   * @param oVertexIndex
   * The vertex index (0, 1, or 2) in the triangle.
   * @return
   * S_OK if the method runs successfully and E_FAIL otherwise.
   */
  virtual HRESULT GetVertexIndex (const int  iIdxTriangle,
                                  const int  iIdxVertex,
                                  int       &oVertexIndex) const ;

  /**
   * Finds the common bar <tt>(oIdxVertex1, oIdxVertex2)</tt> between two triangles.  If there is more than
   * one common bar (cones, back-to-back triangles), the method finds only one of the common bars.
   * However, it returns the number of bars shared by the two triangles (typically 0 or 1 except for
   * cones and back-to-back triangles and other topological anomalies.)
   * @param iIdxTriangle1
   * The index of the first triangle.
   * @param iIdxTriangle2
   * The index of the second triangle.
   * @param oIdxVertex1
   * The index of the first vertex of the common bar.
   * @param oIdxVertex2
   * The index of the second vertex of the common bar.
   * @param oNbBars
   * The number of bars shared by the triangles.
   * @return
   * S_OK if the method runs successfully and E_FAIL otherwise.
   */
  virtual HRESULT GetBar (const int  iIdxTriangle1,
                          const int  iIdxTriangle2,
                          int       &oIdxVertex1,
                          int       &oIdxVertex2,
                          int       &oNbBars) const ;

  /**
   * Returns the orientation of a bar in a triangle.
   * @param iIdxTriangle
   * The index of the triangle to which the bar belongs.
   * @param iIdxVertex1
   * The first vertex of the bar.
   * @param iIdxVertex2
   * The second vertex of the bar.
   * @param oBarOrientation
   * +1 if the bar (iIdxVertex1, iIdxVertex2) is a positive bar of the triangle;
   * -1 if the bar (iIdxVertex1, iIdxVertex2) is a negative bar of the triangle;
   *  0 if it's not a bar.
   * @return
   * S_OK if the method runs successfully and E_FAIL otherwise.
   */
  virtual HRESULT GetBarOrientation (const int  iIdxTriangle,
                                     const int  iIdxVertex1,
                                     const int  iIdxVertex2,
                                     int       &oBarOrientation) const ;


  /**
   * Returns TRUE if the vertex is manifold and FALSE otherwise.
   * @param iIdxVertex
   *   The index of the vertex.
   * @return
   *   TRUE if the vertex is manifold.
   *   FALSE otherwise.
   */
  virtual CATBoolean IsVertexManifold (const int iIdxVertex) const ;

  /**
   * Returns TRUE if the bar is manifold and FALSE otherwise.
   * @param iIdxVertex0
   *   The index of the start vertex of the bar.
   * @param iIdxVertex1
   *   The index of the end vertes of the bar.
   * @return
   *   TRUE if the bar is manifold.
   *   FALSE otherwise.
   */
  virtual CATBoolean IsBarManifold (const int iIdxVertex0, const int iIdxVertex1) const ;

//--------------------------------------------------------------------------------------------------------------
// Geometrical services.
//--------------------------------------------------------------------------------------------------------------

  virtual HRESULT GetVertexNormal (const int      iIdxVertex,
                                   CATMathVector &oNormal) const ;

  virtual HRESULT GetBarNormal (const int      iIdxVertex1,
                                const int      iIdxVertex2,
                                CATMathVector &oNormal) const ;

  virtual HRESULT GetTriangleNormal (const int      iIdxTriangle,
                                     CATMathVector &oNormal) const ;

  /**
   * Computes and returns the length of the bar defined by two vertices.
   * The two vertices must define a valid bar.
   * @param iIdxVertex1
   * The index of the first vertex of the bar.
   * @param iIdxVertex2
   * The index of the second vertex of the bar.
   * @param oLength
   * The distance between the two vertices.
   * @return
   * S_OK if the method runs successfully and E_FAIL otherwise.
   */
  virtual HRESULT GetBarLength (const int  iIdxVertex1,
                                const int  iIdxVertex2,
                                double    &oLength) const ;

  /**
   * Finds the index of the bar of maximum length in a triangle.
   * @param iIdxTriangle
   * The triangle.
   * <b>Legal values</b>: 1 to the number of triangles, inclusive.
   * @param oBarIndex
   * The index of the bar with maximum length (0, 1 or 2.)
   * @return
   * S_OK if the method runs successfully and E_FAIL otherwise.
   */
  virtual HRESULT GetMaximumBar (const int  iIdxTriangle,
                                 int       &oBarIndex) const ;

  /**
   * Finds the index of the bar of minimum length in a triangle.
   * @param iIdxTriangle
   * The triangle.
   * <b>Legal values</b>: 1 to the number of triangles, inclusive.
   * @param oBarIndex
   * The index of the bar with minimum length (0, 1 or 2.)
   * @return
   * S_OK if the method runs successfully and E_FAIL otherwise.
   */
  virtual HRESULT GetMinimumBar (const int  iIdxTriangle,
                                 int       &oBarIndex) const ;

  /**
   * Tests if the two vertices forms the bar of maximum length in the triangle.
   * @param iIdxTriangle
   * The triangle.
   * <b>Legal values</b>: 1 to the number of triangles, inclusive.
   * @param iIdxVertex1
   * The index of the first vertex of the bar.
   * @param iIdxVertex2
   * The index of the second vertex of the bar.
   * @return
   * TRUE if the vertices forms the bar of maximum length in the triangle
   * and FALSE otherwise.
   */
  virtual CATBoolean IsMaximumBar (const int iIdxTriangle,
                                   const int iIdxVertex1,
                                   const int iIdxVertex2) const ;

//--------------------------------------------------------------------------------------------------------------
// Attribute services.
//--------------------------------------------------------------------------------------------------------------

  //
  // VERTEX ATTRIBUTES
  //

  /**
   * Registers a new vertex attribute.  The attribute registered with the mesh must have a distinct ID from
   * the other vertex attributes registered.  If the ID of the attribute is already used, then the method
   * will fail to register the attribute.
   * @param iAttribute
   *   The attribute to register.
   * @return
   *   S_OK if the attribute is successfully registered.
   *   E_FAIL otherwise.
   */
  virtual HRESULT RegisterVertexAttribute (CATPolyAttribute* iAttribute) ;

  /**
   * Returns the vertex attribute that is registered with the given ID.
   * @param id
   *   The attribute ID.
   * @return
   *   The attribute registered with that ID.
   */
  virtual CATPolyAttribute* GetVertexAttribute (const CATPolyAttributeID id) const ;

public:

  //
  // Public methods that are not visible through the interface.
  // Reserved for visitors.
  //

  // Return the native surface support.  Do not delete the support that is returned.
  inline CATIPolySurfaceSupport* GetNativeSupport () const;

  /**
   * Adds the vertex N-Normals layer.   The method fails if a vertex normal layer is already defined.
   * @param oLayer [out, IUnknown#Release]
   *   The output argument must be released by the caller.
   */
  HRESULT AddNewVertexNNormalsLayer (CATPolySurfaceVertexNNormalsLayer*& oLayer);

  /**
   * Returns the vertex N-Normals layer.
   * @param oLayer [out, IUnknown#Release]
   *   The output argument must be released by the caller.
   */
  HRESULT GetVertexNNormalsLayer (CATPolySurfaceVertexNNormalsLayer*& oLayer) const;

private:

  HRESULT FinalAddVertex (const CATMathPoint &P, int &v);

  HRESULT FinalAddTriangle (const int iVertices[], int &t);

  HRESULT FinalRemoveTriangle (const int t, const CATBoolean iRemoveUnreferencedVertices = FALSE);

  HRESULT FinalUpdateTriangle (const int t, const int iVertices[]);

};

extern "C"
{
  ExportedByPolyMeshImpl HRESULT CATPolyMeshImplPropagateOrientation(CATPolyMeshImpl &iMesh,
                                                                     const int iIdxTriangle,
                                                                     const CATIPolyMesh::Orientation iOrientation,
                                                                     const CATBoolean iInvert);
}


// Internal triangle structure

inline
CATPolyMeshImpl::T_Triangle::T_Triangle():
  _Defined(0)
{}
inline
CATPolyMeshImpl::T_Triangle::T_Triangle(int v0, int v1, int v2)
{
  Recycle(v0, v1, v2);
}

inline void
CATPolyMeshImpl::T_Triangle::Recycle(int v0, int v1, int v2)
{
  _Vertices[0] = v0;
  _Vertices[1] = v1;
  _Vertices[2] = v2;
  _Neighbors[0] = 0;
  _Neighbors[1] = 0;
  _Neighbors[2] = 0;
  _Defined = 1;
}

inline int
CATPolyMeshImpl::T_Triangle::FindVertex(int v0) const
{
  if      (v0 == _Vertices[0]) return 0;
  else if (v0 == _Vertices[1]) return 1;
  else if (v0 == _Vertices[2]) return 2;
  return -1;
}

inline int
CATPolyMeshImpl::T_Triangle::FindBar(int v0, int v1) const
{
  int pi = 1, i = 2, ni = 0;
  if      (v0 == _Vertices[0]) {pi = 2; i = 0; ni = 1; }
  else if (v0 == _Vertices[1]) {pi = 0; i = 1; ni = 2; }
  else if (v0 != _Vertices[2]) return -1;

  if (v1 == _Vertices[ni]) return i;  //  i: (v0, v1)
  if (v1 == _Vertices[pi]) return pi; // pi: (v1, v0)
  return -1;
}

inline int
CATPolyMeshImpl::T_Triangle::GetFirstAdjacentTriangle(int v0, int v1) const
{
  const int b = FindBar(v0, v1);
  return (0 <= b) ? _Neighbors[b] : -1; // Should not return -1
}

inline CATBoolean CATPolyMeshImpl::T_Triangle::IsDefined () const
{
  return _Defined;
}

inline int CATPolyMeshImpl::FinalGetMaxVertexIndex () const
{
  return _Vertices.Size ();
}

inline CATBoolean CATPolyMeshImpl::FinalIsVertexDefined (int v) const
{
  return (0 < v && (unsigned int)v <= _Vertices.Size ()) ? _Vertices[v].IsDefined () : FALSE;
}

inline int CATPolyMeshImpl::FinalGetMaxTriangleIndex () const
{ 
  return _Triangles.Size (); 
}

inline CATBoolean CATPolyMeshImpl::FinalIsTriangleDefined(int t) const
{
  return (0 < t && (unsigned int) t <= _Triangles.Size()) ? _Triangles[t].IsDefined() : FALSE; 
}


//--------------------------------------------------------------------------------------------------------------
// Function : Next (CATPolyMeshImpl Implementation)
// Purpose  : Returns the next triangle-indice modulo 3.
//--------------------------------------------------------------------------------------------------------------

inline int CATPolyMeshImpl::_Next (const int iTIndex) const
{
  return (iTIndex + 1) % 3 ; // (I+1)%N
}

//--------------------------------------------------------------------------------------------------------------
// Function : Prev (CATPolyMeshImpl Implementation)
// Purpose  : Returns the previous triangle-indice modulo 3.
//--------------------------------------------------------------------------------------------------------------

inline int CATPolyMeshImpl::_Prev (const int iTIndex) const
{
  return (iTIndex + 2) % 3 ; // (I+N-1)%N
}

//--------------------------------------------------------------------------------------------------------------
// Function : OppositeVertex (CATPolyMeshImpl Implementation)
// Purpose  : Returns the opposite vertex triangle-indice of an edge given by its triangle-indice.
//--------------------------------------------------------------------------------------------------------------

inline int CATPolyMeshImpl::_OppositeVertex (const int iITEdge) const
{
  return (iITEdge + 2) % 3 ; // Dans le cas d'un triangle = Prev(iITEdge)
}

//--------------------------------------------------------------------------------------------------------------
// Function : IsAVertexOf (CATPolyMeshImpl Implementation)
// Purpose  : Tests if a point given by its relative indice belongs to a given triangle.
//--------------------------------------------------------------------------------------------------------------

inline CATBoolean CATPolyMeshImpl::_IsAVertexOf (const int         iNoVertex,
                                              const T_Triangle &iTriangle,
                                              int              &oITVertex) const
{
  unsigned int NoVertex = (unsigned int) iNoVertex ;
  for (oITVertex = 0 ; oITVertex < 3 ; oITVertex++) if (iTriangle._Vertices[oITVertex] == NoVertex) return TRUE ;
  return FALSE ;
}

//--------------------------------------------------------------------------------------------------------------
// Function : IsAnEdgeOf (CATPolyMeshImpl Implementation)
// Purpose  : Tests if an edge given by its vertices relative indices belongs to a given triangle.
//--------------------------------------------------------------------------------------------------------------

inline CATBoolean CATPolyMeshImpl::_IsAnEdgeOf (const int         iNoVertex1,
                                                const int         iNoVertex2,
                                                const T_Triangle &iTriangle,
                                                int              &oITEdge,
                                                int              &oSens) const
{
  unsigned int NoVertex1 = (unsigned int) iNoVertex1 ;
  unsigned int NoVertex2 = (unsigned int) iNoVertex2 ;
  int IVtx, JVtx ;
  for (IVtx = 0 ; IVtx < 3 ; IVtx++) if (iTriangle._Vertices[IVtx] == NoVertex1) break ;
  if (IVtx >= 3) return FALSE ;
  JVtx = _Next (IVtx) ;
  if (iTriangle._Vertices[JVtx] == NoVertex2) {
    oITEdge = IVtx ;
    oSens   = 1 ;
    return TRUE ;
  }
  JVtx = _Prev (IVtx) ;
  if (iTriangle._Vertices[JVtx] == NoVertex2) {
    oITEdge = JVtx ;
    oSens   = -1 ;
    return TRUE ;
  }
  return FALSE ;
}


inline CATIPolySurfaceSupport* CATPolyMeshImpl::GetNativeSupport () const
{
  return GetASupport ();
}


inline CATBoolean CATPolyMeshImpl::HasDoublePrecisionVertexLayers () const
{
  return _Flags & MaskVertexDouble ? TRUE : FALSE;
}

inline bool CATPolyMeshImpl::HasVertexPositionLayer () const
{
  return _VertexPositionLayer != 0;
}

inline CATBoolean CATPolyMeshImpl::HasVertexNormalLayer () const
{
  return _VertexNormalLayer ? TRUE : FALSE;
}
