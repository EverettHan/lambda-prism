//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// Layer of per-vertex position interface
//
//=============================================================================
// 2008-05-14   BPG: New
//=============================================================================
#ifndef CATIPolySurfaceVertexPositionConstLayer_H
#define CATIPolySurfaceVertexPositionConstLayer_H

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/
class CATPolyRefCounted;  // Keep this line to prevent generation of spurious comments with the CAA tags.

#include "PolyhedralAttributes.h"
#include "CATIPolyVertexPositionConstLayer.h"


/**
* Interface to a surface vertex position const layer.
* 
* Given a surface vertex, this interface returns its three coordinates.
*
* @see CATIPolySurface
*/
class ExportedByPolyhedralAttributes CATIPolySurfaceVertexPositionConstLayer : public CATIPolyVertexPositionConstLayer
{

protected:

  CATIPolySurfaceVertexPositionConstLayer () {}
  virtual ~CATIPolySurfaceVertexPositionConstLayer ();

};

#endif // !CATIPolySurfaceVertexPositionConstLayer_H
