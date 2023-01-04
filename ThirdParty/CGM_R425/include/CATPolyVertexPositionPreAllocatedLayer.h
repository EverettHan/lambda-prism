// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyVertexPositionPreAllocatedLayer.h
//
//===================================================================
// September 2011  Creation: ZFI
//===================================================================

#ifndef CATPolyVertexPositionPreAllocatedLayer_H
#define CATPolyVertexPositionPreAllocatedLayer_H

#include "PolyLayers.h"
#include "CATMapOfPtrToPtr.h"
#include "CATIPolySurfaceVertexPositionLayer.h"

class ExportedByPolyLayers CATPolyVertexPositionPreAllocatedLayer : public CATIPolySurfaceVertexPositionLayer
{
public:
  CATPolyVertexPositionPreAllocatedLayer(int iNbVerticesToAllocate);
  virtual ~CATPolyVertexPositionPreAllocatedLayer ();

public:
  HRESULT Get (int v, double &x, double &y, double &z) const;
  HRESULT Get (int v, CATMathPoint &oPosition) const;
  HRESULT Set(int v, double x, double y, double z);

private:
  HRESULT ReallocatePositions(int iNbVerticesToAllocate);

private:
  int _NbVertices;
  int _NbAllocatedVertices;
  float* _Positions;
};

#endif
