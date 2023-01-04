// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyPointUnstreamer.h
//
//===================================================================
// June 2010 Creation: NDO
//===================================================================
#ifndef CATIPolyPointUnstreamer_H
#define CATIPolyPointUnstreamer_H

#include "CATPolyStreamOptions.h"
#include "CATErrorDef.h"

class CATMathStream;
class CATIPolyPoint;
class CATPolyStreamerRegistry;
class CATPolyUnstreamRecord;


/**
 * Interface for unstreaming a CATIPolyPoint from a CATMathStream.
 */
class CATIPolyPointUnstreamer
{

public:

  virtual ~CATIPolyPointUnstreamer () {}

public:

  /**
   * Unstreams a CATIPolyPoint from a CATMathStream.
   * @param iStream
   *   The stream.
   * @param oPolyPoint
   *   The CATIPolyPoint that is unstreamed.
   *   The returned instance must be released.
   * @param iRegistry
   *   A registry of streamers/unstreamers (layers).
   *   If the unstreamer is not avaiable in the registry, the object is not unstreamed.
   * @param ioStreamRecord
   *   An optional argument that records the unstreamed CATIPolyPoint.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity has been successfully unstreamed.
   *   <li> <code> S_FALSE </code> if the entity cannot be unstreamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  virtual HRESULT Unstream (CATMathStream& iStream, CATIPolyPoint*& oPolyPoint,
    const CATPolyStreamerRegistry& iRegistry, CATPolyUnstreamRecord* ioUnstreamRecord = 0) = 0;

protected:

  CATIPolyPointUnstreamer () {}

};


#endif
