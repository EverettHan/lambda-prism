//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATPolySurfaceVertexUVLayerCopier
//
//=============================================================================
// 2008-05-13   BPG: New.
//=============================================================================
#ifndef CATPolySurfaceVertexUVLayerCopier_H
#define CATPolySurfaceVertexUVLayerCopier_H

#include "CATErrorDef.h"

#include "CATMapOfIntToInt.h"

//
class CATIPolySurface;

//
#include "PolyMeshImpl.h"

class ExportedByPolyMeshImpl CATPolySurfaceVertexUVLayerCopier
{
public:
  HRESULT Copy(CATIPolySurface &iSrcSurface, CATIPolySurface &ioDstSurface,
               CATMapOfIntToInt::Iterator &ioSrcVertexDstVertexIterator) const;
};

#endif // !CATPolySurfaceVertexUVLayerCopier_H
