// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyCurveVertexPositionConstLayer.h
//
//===================================================================
// 2010-01-20 NDO
//===================================================================
#pragma once

class CATPolyRefCounted;  // Keep this line to prevent generation of spurious comments with the CAA tags.

#include "PolyhedralAttributes.h"
#include "CATIPolyVertexPositionConstLayer.h"


/**
* Interface to a curve vertex position const layer.
* 
* Given a curve vertex, this interface returns its three coordinates.
*
* @see CATIPolyCurve
*/
class ExportedByPolyhedralAttributes CATIPolyCurveVertexPositionConstLayer : public CATIPolyVertexPositionConstLayer
{

protected:

  CATIPolyCurveVertexPositionConstLayer () {}
  virtual ~CATIPolyCurveVertexPositionConstLayer () {}

};
