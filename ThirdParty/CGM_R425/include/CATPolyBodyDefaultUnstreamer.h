// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyDefaultUnstreamer.h
//
//===================================================================
// February 2010 Creation: NDO
//===================================================================
#ifndef CATPolyBodyDefaultUnstreamer_H
#define CATPolyBodyDefaultUnstreamer_H

#include "PolyStream.h"
#include "CATIPolyBodyUnstreamer.h"
#include "CATPolyStreamOptions.h"
#include "CATErrorDef.h"

class CATMathStream;
class CATPolyBody;
class CATPolyStreamerRegistry;
class CATPolyUnstreamRecord;


class ExportedByPolyStream CATPolyBodyDefaultUnstreamer : public CATIPolyBodyUnstreamer
{

public :

  CATPolyBodyDefaultUnstreamer ();
  ~CATPolyBodyDefaultUnstreamer () {}

public:

  void SetLayerFilter (unsigned int f);

public:

  HRESULT Unstream (CATMathStream& iStream, CATPolyBody*& oPolyBody,
    const CATPolyStreamerRegistry& iRegistry, CATPolyUnstreamRecord* ioUnstreamRecord);

  HRESULT Unstream (CATMathStream& iStream, CATPolyBody*& oPolyBody,
    CATPolyUnstreamRecord* ioUnstreamRecord);

  HRESULT Unstream (CATMathStream& iStream, CATPolyBody*& oPolyBody,
    CATIPolySurfaceUnstreamer* iSurfaceUnstreamer, CATIPolyCurveUnstreamer* iCurveUnstreamer, CATIPolyPointUnstreamer* iPointUnstreamer,
    CATPolyUnstreamRecord* ioUnstreamRecord);

private:

  CATPolyStreamOptions::Compression _Compression;
  unsigned int _LayerFilter;

private:

  HRESULT GetPolySurfaceUnstreamer (CATIPolySurfaceUnstreamer*& oSurfaceUnstreamer) const;

  HRESULT GetPolyCurveUnstreamer (CATIPolyCurveUnstreamer*& oCurveUnstreamer) const;

  HRESULT GetPolyPointUnstreamer (CATIPolyPointUnstreamer*& oPointUnstreamer) const;

private:

  HRESULT UnstreamPrivate (CATMathStream& iStream, CATPolyBody*& oPolyBody,
    CATIPolySurfaceUnstreamer* iSurfaceUnstreamer, CATIPolyCurveUnstreamer* iCurveUnstreamer, CATIPolyPointUnstreamer* iPointUnstreamer,
    const CATPolyStreamerRegistry& iRegistry, CATPolyUnstreamRecord& ioUnstreamRecord);

  HRESULT UnstreamPolySurfaces (CATMathStream& iStream,
    CATIPolySurfaceUnstreamer* iSurfaceUnstreamer,
    const CATPolyStreamerRegistry& iRegistry, CATPolyUnstreamRecord& ioUnstreamRecord);

  HRESULT UnstreamPolyCurves (CATMathStream& iStream,
    CATIPolyCurveUnstreamer* iCurveUnstreamer,
    const CATPolyStreamerRegistry& iRegistry, CATPolyUnstreamRecord& ioUnstreamRecord);

  HRESULT UnstreamPolyPoints (CATMathStream& iStream,
    CATIPolyPointUnstreamer* iPointUnstreamer,
    const CATPolyStreamerRegistry& iRegistry, CATPolyUnstreamRecord& ioUnstreamRecord);

  HRESULT UnstreamPolyBody (CATMathStream& iStream, CATPolyBody& oPolyBody,
    CATPolyUnstreamRecord& ioUnstreamRecord);

  HRESULT UnstreamAttributes (CATMathStream& iStream, CATPolyBody& iPolyBody);

};

#endif
