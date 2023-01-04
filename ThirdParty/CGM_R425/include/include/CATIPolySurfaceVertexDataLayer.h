// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolySurfaceVertexDataLayer.h
//
//===================================================================
// January 2013  Creation: NDO
//===================================================================
#pragma once

#include "PolyhedralAttributes.h"
#include "CATIPolyLayer.h"


/**
 * A surface-vertex layer associating data to each vertex of a CATIPolySurface.
 */
class ExportedByPolyhedralAttributes CATIPolySurfaceVertexDataLayer : public CATIPolyLayer
{

protected:

  virtual ~CATIPolySurfaceVertexDataLayer () {}

public:

  inline static const CATIPolySurfaceVertexDataLayer* Cast (const CATIPolyLayer&);
  inline static const CATIPolySurfaceVertexDataLayer* Cast (const CATIPolyLayer*);

  inline static CATIPolySurfaceVertexDataLayer* Cast (CATIPolyLayer&);
  inline static CATIPolySurfaceVertexDataLayer* Cast (CATIPolyLayer*);

public:

  /**
   * Returns the dimension of the data layer.
   */
  virtual unsigned int GetDimension () const = 0;

private:

  CATIPolySurfaceVertexDataLayer* CastAsSurfaceVertexDataLayer () { return this; }

};

inline const CATIPolySurfaceVertexDataLayer* CATIPolySurfaceVertexDataLayer::Cast (const CATIPolyLayer& layer)
{
  return ((CATIPolyLayer&) layer).CastAsSurfaceVertexDataLayer ();
}

inline const CATIPolySurfaceVertexDataLayer* CATIPolySurfaceVertexDataLayer::Cast (const CATIPolyLayer* layer)
{
  return layer ? Cast (*layer) : 0;
}

inline CATIPolySurfaceVertexDataLayer* CATIPolySurfaceVertexDataLayer::Cast (CATIPolyLayer& layer)
{
  return layer.CastAsSurfaceVertexDataLayer ();
}

inline CATIPolySurfaceVertexDataLayer* CATIPolySurfaceVertexDataLayer::Cast (CATIPolyLayer* layer)
{
  return layer ? Cast (*layer) : 0;
}
