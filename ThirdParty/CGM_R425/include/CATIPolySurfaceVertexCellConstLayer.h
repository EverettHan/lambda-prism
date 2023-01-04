// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolySurfaceVertexCellConstLayer.h
//
//===================================================================
// May 2010  Creation: NDO
//===================================================================
#ifndef CATIPolySurfaceVertexCellConstLayer_H
#define CATIPolySurfaceVertexCellConstLayer_H

#include "PolyhedralAttributes.h"

#include "CATErrorDef.h"
#include "CATPolyRefCounted.h"

class CATPolyCell;
class CATIPolySurfaceVertexCellLayer;


class ExportedByPolyhedralAttributes CATIPolySurfaceVertexCellConstLayer : public CATPolyRefCounted
{

protected:

  CATIPolySurfaceVertexCellConstLayer ();
  virtual ~CATIPolySurfaceVertexCellConstLayer ();

public:

  virtual HRESULT Get (int iVertex, CATPolyCell *&oCell, int &oCellVertex) const = 0;

public:

  /**
   * Casts a CATIPolySurfaceVertexCellConstLayer as a CATIPolySurfaceVertexCellLayer.
   */
  virtual CATIPolySurfaceVertexCellLayer* NonConstCast ();

};

#endif // !CATIPolySurfaceVertexCellConstLayer_H
