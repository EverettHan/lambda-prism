// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyVertexFloatPositionConstLayer
//
//===================================================================/
// January 2011 - Creation NDO
//===================================================================
#ifndef CATIPolyVertexFloatPositionConstLayer_H
#define CATIPolyVertexFloatPositionConstLayer_H

#include "PolyhedralAttributes.h"
#include "CATErrorDef.h"
#include "CATIPolyFloatsLayer.h"


/**
* Interface to a vertex position const layer in float precision.
* 
* Given a vertex, this interface returns its three coordinates in float precision.
*/
class ExportedByPolyhedralAttributes CATIPolyVertexFloatPositionConstLayer : public CATIPolyFloatsLayer
{

public:

  unsigned int GetDimension () const { return 3; }

  virtual HRESULT Set (int v, const float* a) { return S_FALSE; }
  virtual HRESULT Get (int v, float* a) const;

public:

  /**
   * Returns the vertex coordinates.
   * @param v
   *   The index of the vertex.
   * @param x, y, z
   *   The position of the vertex in float precision.
   */
  virtual HRESULT Get (int v, float& x, float& y, float& z) const = 0;

public:

  static const CATIPolyVertexFloatPositionConstLayer* Cast (const CATIPolyLayer*);
  static CATIPolyVertexFloatPositionConstLayer* Cast (CATIPolyLayer*);

  static const CLSID& ClassID ();
  const CLSID& GetClassID () const;

  /**
  * Casts as a non-const layer.
  */
  //virtual CATIPolyVertexFloatPositionConstLayer* NonConstCast ();

};

#endif // !CATIPolyVertexFloatPositionConstLayer_H
