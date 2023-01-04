//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATPolySurfaceVertexPositionLayerCopier
//
//=============================================================================
// 2011-04-10   ZFI, copy method with layers as input
// 2008-05-12   BPG: New.
//=============================================================================
#ifndef CATPolySurfaceVertexPositionLayerCopier_H
#define CATPolySurfaceVertexPositionLayerCopier_H

#include "CATErrorDef.h"

#include "CATMapOfIntToInt.h"

//
class CATIPolySurface;
class CATIPolySurfaceVertexPositionConstLayer;
class CATIPolySurfaceVertexPositionLayer;
//
#include "PolyMeshImpl.h"

class ExportedByPolyMeshImpl CATPolySurfaceVertexPositionLayerCopier
{
public:
  HRESULT Copy(const CATIPolySurface &iSrcSurface, CATIPolySurface &ioDstSurface,
               CATMapOfIntToInt::Iterator &ioSrcVertexDstVertexIterator) const;
    
  HRESULT Copy(const CATIPolySurfaceVertexPositionConstLayer &iSrcVertexPositionLayer, CATIPolySurfaceVertexPositionLayer& ioDstVertexPositionLayer,
               CATMapOfIntToInt::Iterator &ioSrcVertexDstVertexIterator) const;
};

#endif // !CATPolySurfaceVertexPositionLayerCopier_H
