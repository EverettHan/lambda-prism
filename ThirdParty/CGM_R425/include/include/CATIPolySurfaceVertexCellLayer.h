//==================================================================-*- C++ -*-
// COPYRIGHT Dassault Systemes 2007
//=============================================================================
//
// Layer of cell on vertex interface
//
//=============================================================================
// 2007-06-28   BPG: New.
//=============================================================================
#ifndef CATIPolySurfaceVertexCellLayer_H
#define CATIPolySurfaceVertexCellLayer_H

#include "PolyhedralAttributes.h"

#include "CATErrorDef.h"
#include "CATIPolySurfaceVertexCellConstLayer.h"

class CATPolyCell;


class ExportedByPolyhedralAttributes CATIPolySurfaceVertexCellLayer : public CATIPolySurfaceVertexCellConstLayer
{

protected:

  CATIPolySurfaceVertexCellLayer();
  virtual ~CATIPolySurfaceVertexCellLayer();

public:

  virtual HRESULT Set (int iVertex, CATPolyCell *iCell, int iCellVertex) = 0;

public:

  CATIPolySurfaceVertexCellLayer* NonConstCast () {return this;}

};

#endif // !CATIPolySurfaceVertexCellLayer_H
