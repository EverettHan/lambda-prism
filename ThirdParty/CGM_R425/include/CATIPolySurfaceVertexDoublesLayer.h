// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolySurfaceVertexDoublesLayer.h
//
//===================================================================
// October 2021  Creation: NDO
//===================================================================
#pragma once

#include "PolyhedralAttributes.h"
#include "CATIPolyDoublesLayer.h"


/**
 * A surface-vertex layer associating float data to each vertex of a CATIPolySurface.
 */
class ExportedByPolyhedralAttributes CATIPolySurfaceVertexDoublesLayer : public CATIPolyDoublesLayer
{

public:

  inline static const CATIPolySurfaceVertexDoublesLayer* Cast (const CATIPolyLayer&);
  inline static const CATIPolySurfaceVertexDoublesLayer* Cast (const CATIPolyLayer*);

  inline static CATIPolySurfaceVertexDoublesLayer* Cast (CATIPolyLayer&);
  inline static CATIPolySurfaceVertexDoublesLayer* Cast (CATIPolyLayer*);

  static const CLSID& ClassID ();
  virtual const CLSID& GetClassID () const { return ClassID (); }

protected:

  virtual ~CATIPolySurfaceVertexDoublesLayer () {}

};

inline const CATIPolySurfaceVertexDoublesLayer* CATIPolySurfaceVertexDoublesLayer::Cast (const CATIPolyLayer& layer)
{
  if (CATIPolyLayer::CompareClassID (layer.GetClassID (), CATIPolySurfaceVertexDoublesLayer::ClassID ()) == 0)
    return (const CATIPolySurfaceVertexDoublesLayer*) &layer;
  else
    return 0;
}

inline const CATIPolySurfaceVertexDoublesLayer* CATIPolySurfaceVertexDoublesLayer::Cast (const CATIPolyLayer* layer)
{
  return layer ? Cast (*layer) : 0;
}

inline CATIPolySurfaceVertexDoublesLayer* CATIPolySurfaceVertexDoublesLayer::Cast (CATIPolyLayer& layer)
{
  return (CATIPolySurfaceVertexDoublesLayer*) Cast ((const CATIPolyLayer&) layer);
}

inline CATIPolySurfaceVertexDoublesLayer* CATIPolySurfaceVertexDoublesLayer::Cast (CATIPolyLayer* layer)
{
  return layer ? Cast (*layer) : 0;
}
