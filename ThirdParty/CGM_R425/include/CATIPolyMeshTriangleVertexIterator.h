// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.

#ifndef CATIPolyMeshTriangleVertexIterator_H
#define CATIPolyMeshTriangleVertexIterator_H

#include "PolyhedralModel.h"
#include "CATPolyRefCounted.h"
#include "CATBoolean.h"

/**
* Iterator through triangles defined as three vertices.
* Example:
* <pre>
* CATIPolyMeshTriangleVertexIterator *it = 0;
* if (SUCCEDED (Mesh.GetTriangleIterator (it) && it))
* {
* int vertices[3];
* for (it->Begin (); !it->End(); ++(*it))
*  {
*   it->Get (vertices);  // Also it->Get (vertices[0], vertices[1], vertices[2]);
*  }
*  it->Release();
* it = 0;
*  } // Next triangle
* </pre>
*/
class ExportedByPolyhedralModel CATIPolyMeshTriangleVertexIterator : public CATPolyRefCounted
{

protected:

  CATIPolyMeshTriangleVertexIterator ();
  virtual ~CATIPolyMeshTriangleVertexIterator ();

public:

  /**
   * Set the iterator to the beginning.
   */
  virtual CATIPolyMeshTriangleVertexIterator& Begin () = 0;

  /**
   * Return TRUE if the iterator has reached the end and FALSE otherwise.
   */
  virtual CATBoolean End () const = 0;

public:

  /** 
   * Increment the iterator to the next valid element.
   */
  virtual CATIPolyMeshTriangleVertexIterator& operator++ () = 0;

public:

  /**
   * Return the three vertex indices of the current triangle.
   */
  virtual void Get (int vertices[]) const = 0;

};

#endif // CATIPolyMeshTriangleVertexIterator_H
