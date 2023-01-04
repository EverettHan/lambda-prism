// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyVertexNormalPreAllocatedLayer.h
//
//===================================================================
// September 2011  Creation: ZFI
//===================================================================

#ifndef CATPolyVertexNormalPreAllocatedLayer_H
#define CATPolyVertexNormalPreAllocatedLayer_H

#include "PolyLayers.h"
#include "CATIPolySurfaceVertexNormalLayer.h"

class ExportedByPolyLayers CATPolyVertexNormalPreAllocatedLayer : public CATIPolySurfaceVertexNormalLayer
{
public:
  CATPolyVertexNormalPreAllocatedLayer(int iNbVerticesToAllocate);
  virtual ~CATPolyVertexNormalPreAllocatedLayer ();

public:
  HRESULT Get (int v, double& nx, double& ny, double& nz) const;
  HRESULT Get (int v, CATMathVector &oNormal) const;
  HRESULT Set(int v, const CATMathVector &iNormal);

private:
  HRESULT ReallocateNormals(int iNbVerticesToAllocate);

private:
  int _NbVertices;
  int _NbAllocatedVertices;
  float* _Normals;
};

#endif
