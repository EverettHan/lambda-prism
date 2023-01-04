//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATPolySurfaceVertexCoordLayerCopier.h
//
//=============================================================================
// 2011-04-10   ZFI, copy method with layers as input
// 2008-09-02    BPG: New
//=============================================================================

#ifndef CATPolySurfaceVertexCoordLayerCopier_H
#define CATPolySurfaceVertexCoordLayerCopier_H

#include "CATErrorDef.h"

#include "CATMapOfIntToInt.h"

class CATIPolySurface;
class CATIPolySurfaceVertexTextureCoordConstLayer;
class CATIPolySurfaceVertexTextureCoordLayer;

#include "PolyMeshImpl.h"

class ExportedByPolyMeshImpl CATPolySurfaceVertexCoordLayerCopier
{
public:
  HRESULT Copy(CATIPolySurface &iSrcSurface, CATIPolySurface &ioDstSurface,
               CATMapOfIntToInt::Iterator &ioSrcVertexDstVertexIterator) const;
    
  HRESULT Copy(const CATIPolySurfaceVertexTextureCoordLayer& iSrcVertexTexLayer, CATIPolySurfaceVertexTextureCoordLayer& ioDstVertexTexLayer,
               CATMapOfIntToInt::Iterator &ioSrcVertexDstVertexIterator) const;
};

#endif // !CATPolySurfaceVertexCoordLayerCopier_H
