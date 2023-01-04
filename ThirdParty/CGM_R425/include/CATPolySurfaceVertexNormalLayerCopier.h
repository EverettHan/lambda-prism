//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATPolySurfaceVertexNormalLayerCopier
//
//=============================================================================
// 2008-05-12   BPG: New.
//=============================================================================
#ifndef CATPolySurfaceVertexNormalLayerCopier_H
#define CATPolySurfaceVertexNormalLayerCopier_H

#include "CATErrorDef.h"

#include "CATMapOfIntToInt.h"

//
class CATIPolySurface;
class CATIPolySurfaceVertexNormalConstLayer;
class CATIPolySurfaceVertexNormalLayer;

//
#include "PolyMeshImpl.h"

class ExportedByPolyMeshImpl CATPolySurfaceVertexNormalLayerCopier
{
public:
  HRESULT Copy(const CATIPolySurfaceVertexNormalConstLayer &iSrcVertexNormalLayer,
               CATIPolySurfaceVertexNormalLayer &ioDstVertexNormalLayer,
               CATMapOfIntToInt::Iterator &ioSrcVertexDstVertexIterator) const;

public:
  HRESULT Copy(CATIPolySurface &iSrcSurface, CATIPolySurface &ioDstSurface,
               CATMapOfIntToInt::Iterator &ioSrcVertexDstVertexIterator) const;
};

#endif // !CATPolySurfaceVertexNormalLayerCopier_H
