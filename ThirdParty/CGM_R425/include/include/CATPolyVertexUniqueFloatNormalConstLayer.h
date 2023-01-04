// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyVertexUniqueFloatNormalConstLayer.cpp
//
//===================================================================/
// January 2011 - Creation NDO
//===================================================================
#ifndef CATPolyVertexUniqueFloatNormalConstLayer_H
#define CATPolyVertexUniqueFloatNormalConstLayer_H

#include "PolyMeshImpl.h"
#include "CATErrorDef.h"
#include "CATIPolyVertexFloatNormalConstLayer.h"


class ExportedByPolyMeshImpl CATPolyVertexUniqueFloatNormalConstLayer : public CATIPolyVertexFloatNormalConstLayer
{
public:
  CATPolyVertexUniqueFloatNormalConstLayer (float Nx, float Ny, float Nz);
  virtual ~CATPolyVertexUniqueFloatNormalConstLayer ();

public:

  HRESULT Get (int v, float& nx, float& ny, float& nz) const;

  HRESULT HasUniqueNormal (float& x, float& y, float& z) const;

protected:

  float _Nx;
  float _Ny;
  float _Nz;

};

#endif // !CATPolyVertexUniqueFloatNormalConstLayer_H
