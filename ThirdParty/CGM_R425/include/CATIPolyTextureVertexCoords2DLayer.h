// COPYRIGHT DASSAULT SYSTEMES 2018, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyTextureVertexCoords2DLayer.h
//
//===================================================================
// September 2018  Creation: Q8M, NDO
//===================================================================
// 2018-10-26 Q8M: Added a method to the interface for returning the identifier of the layer

#ifndef CATIPolyTextureVertexCoords2DLayer_H
#define CATIPolyTextureVertexCoords2DLayer_H

#include "PolyhedralAttributes.h"
#include "CATIPolyLayer.h"

class CATIPolyMeshTriangleVertexIterator;
class CATUnicodeString;

/**
 * A layer that associates two coordinates to a texture-vertex.
 */
class ExportedByPolyhedralAttributes CATIPolyTextureVertexCoords2DLayer : public CATIPolyLayer
{

public:

  /**
   * Returns an iterator through the texture-vertices of the triangle.
   * The texture-vertex values may differ from the surface-vertex values.
   */
  virtual HRESULT GetIterator (CATIPolyMeshTriangleVertexIterator*& it) const = 0;

  /**
   * Returns the three texture-vertices given a triangle index.
   */
  virtual HRESULT GetTriangle (int t, int vt[3]) const = 0;

  /**
   * Returns the double values associated to the texture-vertex.
   */
  virtual HRESULT Get (int v, double& a, double& b) const = 0;

  /**
   * Sets the double values associated to the texture-vertex.
   */
  virtual HRESULT Set (int v, double a, double b) const = 0;

  /**
  * Returns identifier of layer
  */
  virtual const CATUnicodeString& GetIdentifier() const = 0;

public:

  static const CATIPolyTextureVertexCoords2DLayer* Cast (const CATIPolyLayer*);
  static CATIPolyTextureVertexCoords2DLayer* Cast (CATIPolyLayer*);

  static const CLSID& ClassID ();
  const CLSID& GetClassID () const;

private:

  static const CLSID _ClassID;

protected:

  virtual ~CATIPolyTextureVertexCoords2DLayer () {}

};

#endif // !CATIPolyTextureVertexCoords2DLayer_H
