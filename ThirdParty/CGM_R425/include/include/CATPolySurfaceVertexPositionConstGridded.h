//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// Filter that sets and gets gridded vertex positions.
//
//=============================================================================
// 2008-07-21   NDO: New
//=============================================================================
#ifndef CATPolySurfaceVertexPositionConstGridded_H
#define CATPolySurfaceVertexPositionConstGridded_H

#include "PolyBodyTools.h"
#include "CATPolyGriddedPositionsConst.h"
#include "CATErrorDef.h"

class CATPolyExactArithmetic;
class CATIPolySurfaceVertexPositionConstLayer;
class CATIPolySurface;


class ExportedByPolyBodyTools CATPolySurfaceVertexPositionConstGridded : 
  public CATPolyGriddedPositionsConst
{

public:

  // Construct an instance of the filter with a layer of vertex positions that have already been gridded.
  CATPolySurfaceVertexPositionConstGridded (const CATPolyExactArithmetic& iExactArithmetic,
                                            CATIPolySurfaceVertexPositionConstLayer& iPositionLayer);

  // Construct an instance of the filter with CATIPolySurface whose vertices have already been gridded.
  CATPolySurfaceVertexPositionConstGridded (const CATPolyExactArithmetic& iExactArithmetic,
                                            const CATIPolySurface& iPolySurface);

  virtual ~CATPolySurfaceVertexPositionConstGridded ();

public:

  // Get the coordinates of a vertex.
  HRESULT Get (int v, double &x, double &y, double &z) const;

private:

  CATIPolySurfaceVertexPositionConstLayer* _PositionLayer;

};

#endif // !CATPolySurfaceVertexPositionConstGridded_H
