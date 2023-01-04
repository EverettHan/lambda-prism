//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATPolyMeshTriangleSetSerializer
//
//=============================================================================
// 2008-03-03   BPG: New
// 2012-01-17   JXO: Unary operator on indices
//=============================================================================
#ifndef CATPolyMeshTriangleSetSerializer_H
#define CATPolyMeshTriangleSetSerializer_H

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

// ExportedBy
#include "PolyhedralUtilities.h"

// System
#include "CATErrorDef.h"
#include "CATBoolean.h"

class CATIPolyMesh;
class CATPolySurfaceCompactVertexIndexMapper;


/**
Serializes the triangle vertices from a CATIPolyMesh into an integer buffer.  

The buffer must be allocated before a call to the serialize method and it must be sufficiently large to 
contain three times the number of triangles (3 * CATIPolyMesh::GetNbTriangles ()).

The triangles are serialized in sequence: <tt>t0v0 t0v1 t0v2 t1v0 t1v1 t1v2 ... tnv0 tnv1 tnv2</tt>.
 */
class ExportedByPolyhedralUtilities CATPolyMeshTriangleSetSerializer
{

public:

  /**
   * For operation on indices.
   * Derive this class to perform operations on indices just before they are stored to the buffer.
   */
  class ExportedByPolyhedralUtilities UnaryOperator
  {
  public:
    virtual int Operator(int i){return i;}
  };
  static UnaryOperator Identity;

  //with offset
  class UnaryOperatorOffset : public UnaryOperator
  {
  public:
    UnaryOperatorOffset(int offset):m_offset(offset){}
    ~UnaryOperatorOffset(){}
    int Operator(int i){return i+m_offset;}
  private:
    int m_offset;
  };

  /**
   * Serializes the triangle vertices into an integer buffer.
   * The buffer must be pre-allocated and its size should be at least 3 * CATIPolySurface::GetNbTriangles ().
   * The buffer is filled with the triangle vertex indices.
   * @param inverse
   */
  HRESULT Serialize (const CATIPolyMesh& iMesh, int* ioTriangleVertices, UnaryOperator & Op = Identity, CATBoolean inverse = FALSE) const;

  /**
   * Serializes the triangle vertices into an integer buffer.
   *
   * The buffer must be pre-allocated and its size should be at least 3 * CATIPolySurface::GetNbTriangles ().
   * The buffer is filled with the vertex indices after their mapping into a compact vertex array
   * ranging from 0 to CATIPolyMesh::GetNbVertices () - 1 inclusive.
   */
  HRESULT Serialize (const CATIPolyMesh& iMesh, const CATPolySurfaceCompactVertexIndexMapper* iMapper,
                     int* ioTriangleVertices, UnaryOperator & Op = Identity, CATBoolean inverse = FALSE) const;

};

#endif // !CATPolyMeshTriangleSetSerializer_H
