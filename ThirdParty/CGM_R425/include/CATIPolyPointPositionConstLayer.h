// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyPointPositionConstLayer.h
//
//===================================================================
// October 2011  Creation NDO
//===================================================================
#ifndef CATIPolyPointPositionConstLayer_H
#define CATIPolyPointPositionConstLayer_H

class CATPolyRefCounted;  // Keep this line to prevent generation of spurious comments with the CAA tags.

#include "PolyhedralAttributes.h"
#include "CATIPolyVertexPositionConstLayer.h"


/**
* Interface to a vertex position layer.
* 
* Given a vertex, this interface sets its three coordinates.
*/
class ExportedByPolyhedralAttributes CATIPolyPointPositionConstLayer : public CATIPolyVertexPositionConstLayer
{

protected:

  CATIPolyPointPositionConstLayer () {}
  virtual ~CATIPolyPointPositionConstLayer ();

public:

  /**
   * Returns the vertex coordinates.
   * @param v
   *   The index of the vertex.
   * @param x, y, z
   *   The position of the vertex.
   */
  virtual HRESULT Get (double &x, double &y, double &z) const = 0;

public:

  virtual HRESULT Get (int v, double &x, double &y, double &z) const;
  virtual HRESULT Get (int v, CATMathPoint &oPosition) const;

};

#endif // !CATIPolyPointPositionConstLayer_H
