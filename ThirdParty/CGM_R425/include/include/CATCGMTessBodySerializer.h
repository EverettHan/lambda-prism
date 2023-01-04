#ifndef CATCGMTessBodySerializer_h_
#define CATCGMTessBodySerializer_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

/**
/** @_C_A_A_2_Level L1 */ // To be activated when moved to PublicInterfaces.(Remove the underscores '_' to activate)
/** @_C_A_A_2_Usage U3  
*/

#include "CATGMModelInterfaces.h"
#include "CATErrorDef.h"

class CATCGMTessBody;
class CATBody;

/**
Serializes the tessellation data, specifically the vertices and the triangles, from a whole CATBody into compact arrays.  
The buffers must be allocated before calls to the serialize methods and their sizes should be sufficiently large to 
contain the data.
 */
class ExportedByCATGMModelInterfaces CATCGMTessBodySerializer
{
public:
  /**
   * Constructor
   */
  CATCGMTessBodySerializer();

  /**
   * Destructor
   */
  virtual ~CATCGMTessBodySerializer();

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
   * Returns the number of triangles to be serialized.
   */
  virtual int GetNbTriangles() const = 0;

  /**
   * Returns the required size of the buffer for serialization of the vertex position layer.
   */
  virtual int GetSizeOfVertexPositionBuffer() const = 0;

  /**
   * Returns the required size of the buffer for serialization of the triangles.
   * The size of the buffer is equal to 3 * CATIPolySurface::GetNbTriangles ().
   */
  virtual int GetSizeOfTriangleBuffer() const = 0;

  /** @name Serialization to float buffers.
    @{ */
  /**
   * Serializes the vertex coordinate layer into a float buffer and the triangle indices.
   *
   * The buffers must be pre-allocated.
   */
  virtual HRESULT Serialize(float *ioVertexPositionBuffer, int *ioTriangleVertices) const = 0;

  /** @name Serialization to double buffers
    @{ */
  /**
   * Serializes the vertex coordinate layer into a double buffer and the triangle indices.
   *
   * The buffers must be pre-allocated.
   */
  virtual HRESULT Serialize(double *ioVertexPositionBuffer, int *ioTriangleVertices) const = 0;

};

/** @file 
 */
/**
 * Creates an instance of CATCGMTessBodySerializer for serialization of the tessellation data of a whole CATBody.
 *
 * @param iTessBody
 *   The input CATCGMTessBody.
 * @return
 *   An instance of a CATCGMTessBodySerializer.
 */
ExportedByCATGMModelInterfaces CATCGMTessBodySerializer *CATCGMCreateTessBodySerializer(CATCGMTessBody &iTessBody);

#endif /* CATCGMTessBodySerializer_h_ */
