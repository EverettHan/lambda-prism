// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyVertexFloatNormalConstLayer
//
//===================================================================/
// January 2011 - Creation NDO
//===================================================================
#ifndef CATIPolyVertexFloatNormalConstLayer_H
#define CATIPolyVertexFloatNormalConstLayer_H

#include "PolyhedralAttributes.h"
#include "CATErrorDef.h"
#include "CATIPolyFloatsLayer.h"


/**
* Interface to a vertex normal const layer in float precision.
* 
* Given a vertex, this interface returns its the x, y, z components of its normal in float precision.
*/
class ExportedByPolyhedralAttributes CATIPolyVertexFloatNormalConstLayer : public CATIPolyFloatsLayer
{

public:

  unsigned int GetDimension () const { return 3; }

  virtual HRESULT Set (int v, const float* a) { return S_FALSE; }
  virtual HRESULT Get (int v, float* a) const;

public:

  /**
   * Returns the components of the normal at the vertex.
   * @param v
   *   The index of the vertex.
   * @param x, y, z
   *   The components of the vertex normal in float precision.
   */
  virtual HRESULT Get (int v, float& x, float& y, float& z) const = 0;

  /**
   * Returns <tt>S_OK</tt> if the layer has a unique normal (case of a planar surface) and 
   * <tt>S_FALSE</tt> otherwise.
   * @param x, y, z
   *   The three components of the unique normal in float precision.
   */
  virtual HRESULT HasUniqueNormal (float& x, float& y, float& z) const = 0;

public:

  static const CATIPolyVertexFloatNormalConstLayer* Cast (const CATIPolyLayer*);
  static CATIPolyVertexFloatNormalConstLayer* Cast (CATIPolyLayer*);

  static const CLSID& ClassID ();
  const CLSID& GetClassID () const;

  /**
  * Casts as a non-const layer.
  */
  //virtual CATIPolyVertexFloatNormalConstLayer* NonConstCast ();

};

#endif // !CATIPolyVertexFloatNormalConstLayer_H
