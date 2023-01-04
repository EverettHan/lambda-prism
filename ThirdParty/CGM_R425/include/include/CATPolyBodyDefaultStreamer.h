// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyDefaultStreamer.h
//
//===================================================================
// February 2010 Creation: NDO
//===================================================================
#ifndef CATPolyBodyDefaultStreamer_H
#define CATPolyBodyDefaultStreamer_H

#include "PolyStream.h"
#include "CATIPolyBodyStreamer.h"
#include "CATPolyStreamOptions.h"
#include "CATErrorDef.h"

#include "CATPolySurfaceList.h"
#include "CATPolyCurveList.h"
#include "CATPolyPointList.h"

class CATMathStream;
class CATPolyBody;
class CATPolyStreamerRegistry;
class CATPolyStreamRecord;
class CATPolySurfaceCompactVertexIndexMapper;
class CATPolySurfaceCompactFacetIndexMapper;
class CATMapOfPolySurfaceToVertexMapper;
class CATMapOfPolySurfaceToFacetMapper;


/*
 * Default implementation of CATIPolyBodyStreamer.
 * This is a plain streaming of the geometrical entities (CATIPolySurface, CATIPolyCurve and CATIPolyPoint)
 * and of the CATPolyBody topology.
 */
class ExportedByPolyStream CATPolyBodyDefaultStreamer : public CATIPolyBodyStreamer
{

public:

  CATPolyBodyDefaultStreamer ();
  ~CATPolyBodyDefaultStreamer ();

public:

  const char* GetLibraryName () const;

public:

  /**
   * Default is no compression.
   * @see CATIPolyBodyStreamer
   */
  void SetCompression (CATPolyStreamOptions::Compression c);

  /**
   * Default is all layers.
   * @see CATIPolyBodyStreamer
   */
  void SetLayerFilter (unsigned int f);

public:

  HRESULT Stream (CATMathStream& iStream, const CATPolyBody& iPolyBody,
    CATPolyStreamRecord* ioStreamRecord);

  HRESULT Stream (CATMathStream& iStream, const CATPolyBody& iPolyBody,
    const CATPolyStreamerRegistry& iRegistry, CATPolyStreamRecord* ioStreamRecord);

  HRESULT Stream (CATMathStream& iStream, const CATPolyBody& iPolyBody,
    CATIPolySurfaceStreamer* iSurfaceStreamer, CATIPolyCurveStreamer* iCurveStreamer, CATIPolyPointStreamer* iPointStreamer,
    CATPolyStreamRecord* ioStreamRecord);

public:

  /**
   * Returns the vertex map associated to a CATIPolySurface.
   * @param iPolySurface
   *    The CATIPolySurface.
   * @return
   *    The vertex map.
   */
  const CATPolySurfaceCompactVertexIndexMapper* GetVertexMapper (const CATIPolySurface& iPolySurface) const;

  /**
   * Returns the facet map associated to a CATIPolySurface.
   * @param iPolySurface
   *    The CATIPolySurface.
   * @return
   *    The facet map.
   */
  const CATPolySurfaceCompactFacetIndexMapper* GetFacetMapper (const CATIPolySurface &iPolySurface) const;

private:

  CATPolyStreamOptions::Compression _CompressionFlags;
  unsigned int _LayerFilter;

  CATMapOfPolySurfaceToVertexMapper* _MapSurfaceToVertexMap;
  CATMapOfPolySurfaceToFacetMapper *_MapSurfaceToFacetMap;

private:

  HRESULT GetPolySurfaceStreamer (CATIPolySurfaceStreamer*& oSurfaceStreamer) const;

  HRESULT GetPolyCurveStreamer (CATIPolyCurveStreamer*& oCurveStreamer) const;

  HRESULT GetPolyPointStreamer (CATIPolyPointStreamer*& oPointStreamer) const;

protected:

  friend class CATPolyBodyDefaultUnstreamer;

  enum Attributes
  {
    /** No attributes streamed. */                                eNoAttributes = 0x0000,
    /** Basic attributes streamed. */                             eBasicAttributes = 0x0001
  };

private:

  HRESULT StreamPrivate (CATMathStream& iStream, const CATPolyBody& iPolyBody,
    CATIPolySurfaceStreamer* iSurfaceStreamer, CATIPolyCurveStreamer* iCurveStreamer, CATIPolyPointStreamer* iPointStreamer,
    const CATPolyStreamerRegistry& iRegistry, CATPolyStreamRecord& ioStreamRecord);

  HRESULT StreamPolySurfaces (CATMathStream& iStream, const CATPolySurfaceList& iSurfaces,
    CATIPolySurfaceStreamer* iSurfaceStreamer,
    const CATPolyStreamerRegistry& iRegistry, CATPolyStreamRecord& ioStreamRecord);

  HRESULT StreamPolyCurves (CATMathStream& iStream, const CATPolyCurveList& iCurves,
    CATIPolyCurveStreamer* iCurveStreamer,
    const CATPolyStreamerRegistry& iRegistry, CATPolyStreamRecord& ioStreamRecord);

  HRESULT StreamPolyPoints (CATMathStream& iStream, const CATPolyPointList& iPoints,
    CATIPolyPointStreamer* iPointStreamer,
    const CATPolyStreamerRegistry& iRegistry, CATPolyStreamRecord& ioStreamRecord);

  HRESULT StreamPolyBody (CATMathStream& iStream, const CATPolyBody& iPolyBody,
    CATPolyStreamRecord& ioStreamRecord);

  HRESULT StreamAttributes (CATMathStream& iStream, const CATPolyBody& iPolyBody);

};

#endif
