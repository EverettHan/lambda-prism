#ifndef CATCGMTessBodyVertexSerializer_h_
#define CATCGMTessBodyVertexSerializer_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

/**
/** @_C_A_A_2_Level L1 */ // To be activated when moved to PublicInterfaces.(Remove the underscores '_' to activate)
/** @_C_A_A_2_Usage U3  
*/

#include "CATGMModelInterfaces.h"
#include "CATErrorDef.h"

class CATCGMTessBody;
class CATBody;
class CATVertex;
class CATCGMTessID;
class CATCGMTessellateID;

/**
Serializes the tessellation data into compact arrays of floats and doubles.  
The buffers must be allocated before calls to the serialize methods and their sizes should be sufficiently large to 
contain the data.
 */
class ExportedByCATGMModelInterfaces CATCGMTessBodyVertexSerializer
{
public:
  /**
   * Constructor
   */
  CATCGMTessBodyVertexSerializer();

  /**
   * Destructor
   */
  virtual ~CATCGMTessBodyVertexSerializer();

  /**
   * Returns the tessellation ID associated to the CATVertex.
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
   * Returns the required size of the buffer for serialization of the vertex position layer.
   */
  virtual int GetSizeOfVertexPositionBuffer() const = 0;

  /** @name Serialization to float buffers.
    @{ */
  /**
   * Serializes the vertex coordinate layer into a float buffer.
   *
   * The buffer must be pre-allocated and its size should be at least GetSizeOfVertexPositionBuffer ().
   */
  virtual HRESULT SerializeVertexPositionLayer(float *ioVertexPositionBuffer) const = 0;

  /** @name Serialization to double buffers
    @{ */
  /**
   * Serializes the vertex coordinate layer into a double buffer.
   *
   * The buffer must be pre-allocated and its size should be at least GetSizeOfVertexPositionBuffer ().
   */
  virtual HRESULT SerializeVertexPositionLayer(double *ioVertexPositionBuffer) const = 0;

};

/** @file 
 */
/**
 * Creates an instance of CATCGMTessBodyVertexSerializer for serialization of the tessellation data for a CATVertex.
 *
 * @param iTessBody
 *   The input CATCGMTessBody.
 * @param iEdge
 *   The input CATVertex whose tessellation data is to be serialized.
 * @return
 *   An instance of a CATCGMTessBodyVertexSerializer.
 */
ExportedByCATGMModelInterfaces CATCGMTessBodyVertexSerializer *CATCGMCreateTessBodyVertexSerializer(
  CATCGMTessBody &iTessBody,
  CATVertex &iVertex);

#endif /* CATCGMTessBodyVertexSerializer_h_ */
