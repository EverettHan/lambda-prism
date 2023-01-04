// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolySurfaceVertexFloatsLayer.h
//
//===================================================================
// October 2021  Creation: NDO
//===================================================================
#pragma once

#include "PolyhedralAttributes.h"
#include "CATIPolyFloatsLayer.h"


/**
 * A surface-vertex layer associating float data to each vertex of a CATIPolySurface.
 */
class ExportedByPolyhedralAttributes CATIPolySurfaceVertexFloatsLayer : public CATIPolyFloatsLayer
{

protected:

  virtual ~CATIPolySurfaceVertexFloatsLayer () {}

public:

  inline static const CATIPolySurfaceVertexFloatsLayer* Cast (const CATIPolyLayer&);
  inline static const CATIPolySurfaceVertexFloatsLayer* Cast (const CATIPolyLayer*);

  inline static CATIPolySurfaceVertexFloatsLayer* Cast (CATIPolyLayer&);
  inline static CATIPolySurfaceVertexFloatsLayer* Cast (CATIPolyLayer*);

  static const CLSID& ClassID ();
  virtual const CLSID& GetClassID () const { return ClassID (); }

};

inline const CATIPolySurfaceVertexFloatsLayer* CATIPolySurfaceVertexFloatsLayer::Cast (const CATIPolyLayer& layer)
{
  if (CATIPolyLayer::CompareClassID (layer.GetClassID (), CATIPolySurfaceVertexFloatsLayer::ClassID ()) == 0)
    return (const CATIPolySurfaceVertexFloatsLayer*) &layer;
  else
    return 0;
}

inline const CATIPolySurfaceVertexFloatsLayer* CATIPolySurfaceVertexFloatsLayer::Cast (const CATIPolyLayer* layer)
{
  return layer ? Cast (*layer) : 0;
}

inline CATIPolySurfaceVertexFloatsLayer* CATIPolySurfaceVertexFloatsLayer::Cast (CATIPolyLayer& layer)
{
  return (CATIPolySurfaceVertexFloatsLayer*) Cast ((const CATIPolyLayer&) layer);
}

inline CATIPolySurfaceVertexFloatsLayer* CATIPolySurfaceVertexFloatsLayer::Cast (CATIPolyLayer* layer)
{
  return layer ? Cast (*layer) : 0;
}
