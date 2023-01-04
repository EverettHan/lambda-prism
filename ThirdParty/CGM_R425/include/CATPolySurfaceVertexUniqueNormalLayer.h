//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATPolySurfaceVertexUniqueNormalLayer
//
//=============================================================================
// 2008-05-13   BPG: New.
//=============================================================================
#ifndef CATPolySurfaceVertexUniqueNormalLayer_H
#define CATPolySurfaceVertexUniqueNormalLayer_H

#include "PolyMeshImpl.h"
#include "CATErrorDef.h"
#include "CATIPolySurfaceVertexNormalLayer.h"


//
class ExportedByPolyMeshImpl CATPolySurfaceVertexUniqueNormalLayer : public CATIPolySurfaceVertexNormalLayer
{
public:
  CATPolySurfaceVertexUniqueNormalLayer(double Nx, double Ny, double Nz);
  virtual ~CATPolySurfaceVertexUniqueNormalLayer();

public:

  HRESULT Get (int v, double& nx, double& ny, double& nz) const;
  HRESULT Get(int v, CATMathVector &oNormal) const;

  HRESULT HasUniqueNormal (CATMathVector& oNormal) const;

public:

  virtual HRESULT Set(int v, const CATMathVector &iNormal);

protected:

  double _Nx;
  double _Ny;
  double _Nz;

};

#endif // !CATPolySurfaceVertexUniqueNormalLayer_H
