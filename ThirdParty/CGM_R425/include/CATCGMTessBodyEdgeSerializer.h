#ifndef CATCGMTessBodyEdgeSerializer_h_
#define CATCGMTessBodyEdgeSerializer_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

/**
/** @_C_A_A_2_Level L1 */ // To be activated when moved to PublicInterfaces.(Remove the underscores '_' to activate)
/** @_C_A_A_2_Usage U3 
*/

#include "CATGMModelInterfaces.h"
#include "CATErrorDef.h"

class CATCGMTessBody;
class CATBody;
class CATEdge;
class CATCGMTessID;
class CATCGMTessellateID;
class CATTessDataCache;

/**
Serializes the tessellation data into compact arrays of floats, doubles and integers.  
The buffers must be allocated before calls to the serialize methods and their sizes should be sufficiently large to 
contain the data.
 */
class ExportedByCATGMModelInterfaces CATCGMTessBodyEdgeSerializer
{
public:
  /**
   * Constructor
   */
  CATCGMTessBodyEdgeSerializer();

  /**
   * Destructor
   */
  virtual ~CATCGMTessBodyEdgeSerializer();

  /**
   * Returns the tessellation ID associated to the CATEdge.
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

  /** @name Queries about the size of the buffers for serialization.
    @{ */
  /**
   * Returns the number of vertices to be serialized.
   */
  virtual int GetNbVertices() const = 0;

  /**
   * Returns the required size of the buffer for serialization of the vertex position layer.
   */
  virtual int GetSizeOfVertexPositionBuffer() const = 0;

  /**
   * Returns the required size of the buffer for serialization of the vertex W (parameter) layer.
   * The method may return 0 if no W layer is available.
   */
  virtual int GetSizeOfVertexWBuffer() const = 0;

  /** @name Serialization to float buffers.
    @{ */
  /**
   * Serializes the vertex coordinate layer into a float buffer.
   *
   * The buffer must be pre-allocated and its size should be at least GetSizeOfVertexPositionBuffer ().
   */
  virtual HRESULT SerializeVertexPositionLayer(float *ioVertexPositionBuffer) const = 0;

  /**
   * Serializes the vertex W layer into a float buffer.
   *
   * The buffer must be pre-allocated and its size should be at least GetSizeOfVertexWBuffer ().
   */
  virtual HRESULT SerializeVertexWLayer(float *ioVertexWBuffer) const = 0;

  /** @name Serialization to double buffers
    @{ */
  /**
   * Serializes the vertex coordinate layer into a double buffer.
   *
   * The buffer must be pre-allocated and its size should be at least GetSizeOfVertexPositionBuffer ().
   */
  virtual HRESULT SerializeVertexPositionLayer(double *ioVertexPositionBuffer) const = 0;

  /**
   * Serializes the vertex W layer into a double buffer.
   *
   * The buffer must be pre-allocated and its size should be at least GetSizeOfVertexWBuffer ().
   */
  virtual HRESULT SerializeVertexWLayer(double *ioVertexWBuffer) const = 0;

  /** @} */
  /**
	* WARNING : only use this with the new implemenation of CATCGMTessBody (that is created with CATCGMTessellateParam)
	* Direct access to the tessellation cache (local mesh) 
	* returns oCellDataCache=NULL if there is delta mesh in the body context
  */
  virtual HRESULT GetCellDataCache(const CATTessDataCache *&oCellDataCache) = 0;

};

/** @file 
 */
/**
 * Creates an instance of CATCGMTessBodyEdgeSerializer for serialization of the tessellation data for a CATEdge.
 *
 * @param iTessBody
 *   The input CATCGMTessBody.
 * @param iEdge
 *   The input CATEdge whose tessellation data is to be serialized.
 * @return
 *   An instance of a CATCGMTessBodyEdgeSerializer.
 */
ExportedByCATGMModelInterfaces CATCGMTessBodyEdgeSerializer *CATCGMCreateTessBodyEdgeSerializer(
  CATCGMTessBody &iTessBody,
  CATEdge &iEdge);

#endif /* CATCGMTessBodyEdgeSerializer_h_ */
