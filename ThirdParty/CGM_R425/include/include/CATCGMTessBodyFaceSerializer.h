#ifndef CATCGMTessBodyFaceSerializer_h_
#define CATCGMTessBodyFaceSerializer_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

/**
/** @_C_A_A_2_Level L1 */ // To be activated when moved to PublicInterfaces.(Remove the underscores '_' to activate)
/** @_C_A_A_2_Usage U3  
*/

#include "CATGMModelInterfaces.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

class CATCGMTessBody;
class CATBody;
class CATEdge;
class CATFace;
class CATCGMTessID;
class CATCGMTessellateID;
//class CATTessDataCache;

/**
Serializes the tessellation data into compact arrays of floats, doubles and integers.  
The buffers must be allocated before calls to the serialize methods and their sizes should be sufficiently large to 
contain the data.
 */
class ExportedByCATGMModelInterfaces CATCGMTessBodyFaceSerializer
{
public:
  /**
   * Constructor
   */
  CATCGMTessBodyFaceSerializer();

  /**
   * Destructor
   */
  virtual ~CATCGMTessBodyFaceSerializer();

  /**
   * Returns the tessellation ID associated to the CATFace.
   * @param oTessID
   *   The output CATCGMTessellateID, to be deleted by the caller.
   * @return
   *   <ul>
   *     <li> S_OK if the CATCGMTessellateID has been set.
   *     <li> E_FAIL or any other error when a failure occurs and the CATCGMTessellateID has not been set.
   *   </ul>
   */
  virtual HRESULT GetTessellateID(CATCGMTessellateID *&oTessID) = 0;

  /**
   * Returns a reference to the CATBody that is tessellated.
   * @return
   *   The CATBody that is tessellated.
   */
  virtual CATBody& GetBody () = 0;

  /**
   * Sets a parameter to include the facet size (3 for a CATIPolyMesh) during the serialization of the triangles.
   *
   * When this flag is set to <tt>TRUE</tt>, the triangles are serialized as follows: 
   * <br>
   * <tt>3 t0v0 t0v1 t0v2 3 t1v0 t1v1 t1v2 ... 3 tnv0 tnv1 tnv2</tt>.
   * <br>
   * Otherwise, the triangles are serialized as follows:
   * <br>
   * <tt>t0v0 t0v1 t0v2 t1v0 t1v1 t1v2 ... tnv0 tnv1 tnv2</tt>.
   * <br>
   * By default this flag is set to <tt>FALSE</tt>.
   */
  virtual void DoIncludePolygonSize(CATBoolean iDoIncludeFacetSize) = 0;

  /** @name Queries about the size of the buffers for serialization.
    @{ */
  /**
   * Returns the number of vertices to be serialized.
   */
  virtual int GetNbVertices() const = 0;

  /**
   * Returns the number of triangles to be serialized.
   */
  virtual int GetNbTriangles() const = 0;

  /**
   * Returns the required size of the buffer for serialization of the vertex position layer.
   */
  virtual int GetSizeOfVertexPositionBuffer() const = 0;

  /**
   * Returns the required size of the buffer for serialization of the vertex normal layer.
   * The method may return 0 if no normal layer is available.
   */
  virtual int GetSizeOfVertexNormalBuffer() const = 0;

  /**
   * Returns the required size of the buffer for serialization of the vertex UV layer.
   * The method may return 0 if no UV layer is available.
   */
  virtual int GetSizeOfVertexUVBuffer() const = 0;

  /**
   * Returns the required size of the buffer for serialization of the triangles.
   * The size of the buffer is equal to 3 * CATIPolySurface::GetNbTriangles ().
   */
  virtual int GetSizeOfTriangleBuffer() const = 0;

  /**
   * Returns the required size of the buffer for serialization of the surface vertex line indices
   * for a given CATEdge.
   * See SerializeSurfaceVertices.
   */
  virtual int GetSizeOfSurfaceVertexBuffer (CATEdge& iEdge) const = 0;

  /** @name Serialization to float buffers.
    @{ */
  /**
   * Serializes the vertex coordinate layer into a float buffer.
   *
   * The buffer must be pre-allocated and its size should be at least GetSizeOfVertexPositionBuffer ().
   */
  virtual HRESULT SerializeVertexPositionLayer(float *ioVertexPositionBuffer) const = 0;

  /**
   * Serializes the vertex normal layer into a float buffer.
   *
   * The buffer must be pre-allocated and its size should be at least GetSizeOfVertexNormalBuffer ().
   */
  virtual HRESULT SerializeVertexNormalLayer(float *ioVertexNormalBuffer) const = 0;

  /**
   * Serializes the vertex UV layer into a float buffer.
   *
   * The buffer must be pre-allocated and its size should be at least GetSizeOfVertexUVBuffer ().
   */
  virtual HRESULT SerializeVertexUVLayer(float *ioVertexUVBuffer) const = 0;

  /** @name Serialization to double buffers
    @{ */
  /**
   * Serializes the vertex coordinate layer into a double buffer.
   *
   * The buffer must be pre-allocated and its size should be at least GetSizeOfVertexPositionBuffer ().
   */
  virtual HRESULT SerializeVertexPositionLayer(double *ioVertexPositionBuffer) const = 0;

  /**
   * Serializes the vertex normal layer into a double buffer.
   *
   * The buffer must be pre-allocated and its size should be at least GetSizeOfVertexNormalBuffer ().
   */
  virtual HRESULT SerializeVertexNormalLayer(double *ioVertexNormalBuffer) const = 0;

  /**
   * Serializes the vertex UV layer into a double buffer.
   *
   * The buffer must be pre-allocated and its size should be at least GetSizeOfVertexUVBuffer ().
   */
  virtual HRESULT SerializeVertexUVLayer(double *ioVertexUVBuffer) const = 0;

  /** @name Serialization of the facets.
    @{ */
  /**
   * Serializes the triangle vertices into an integer buffer.
   *
   * The buffer must be pre-allocated and its size should be at least GetSizeOfTriangleBuffer ().
   * The buffer is filled with the vertex indices after their mapping into a compact vertex array
   * ranging from 0 to CATIPolyMesh::GetNbVertices () - 1 inclusive.
   */
  virtual HRESULT SerializeTriangles(int *ioTriangleVertices) const = 0;

  /** @name Serialization of an edge bounding a face.
    @{ */
  /**
   * Serializes the surface vertices along a tessellated CATEdge bounding the CATFace.
   * 
   * The buffer must be pre-allocated and its size should be at least iSurfaceVertexLine.GetNbVertices ().
   *
   * @param iEdge
   *   The CATEdge bounding the CATFace and whose surface vertices are being serialized.
   * @param ioIndexBuffer
   *   The buffer for the surface vertices defining the tessellated CATEdge.
   *   The buffer is filled with the surface vertices after their mapping into a compact vertex array
   *   ranging from 0 to CATIPolyMesh::GetNbVertices () - 1 inclusive.
   */
  virtual HRESULT SerializeSurfaceVertices(CATEdge &iEdge, int *ioIndexBuffer) const = 0;

  /** @} */
  /**
	* WARNING : only use this with the new implemenation of CATCGMTessBody (that is created with CATCGMTessellateParam)
	* Direct access to the tessellation cache (local mesh) and orientation of the cell regarding data cache 
	* returns oCellDataCache=NULL if there is delta mesh in the body context
  */
  //virtual HRESULT GetCellDataCache(
  //  const CATTessDataCache *&oCellDataCache,
  //  int &oOrientation) = 0;

};

/** @file 
 */
/**
 * Creates an instance of CATCGMTessBodyFaceSerializer for serialization of the tessellation data for a CATFace.
 *
 * @param iTessBody
 *   The input CATCGMTessBody.
 * @param iFace
 *   The input CATFace whose tessellation data is to be serialized.
 * @return
 *   An instance of a CATCGMTessBodyFaceSerializer.
 */
ExportedByCATGMModelInterfaces CATCGMTessBodyFaceSerializer *CATCGMCreateTessBodyFaceSerializer(
  CATCGMTessBody &iTessBody,
  CATFace &iFace);

#endif /* CATCGMTessBodyFaceSerializer_h_ */
