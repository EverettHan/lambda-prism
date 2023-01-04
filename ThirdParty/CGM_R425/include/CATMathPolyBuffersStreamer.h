// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
//===================================================================
//
// CATMathPolyBuffersStreamer.h
//
//===================================================================
// Sep 2016  Creation: TPG
//===================================================================
#ifndef CATMathPolyBuffersStreamer_H
#define CATMathPolyBuffersStreamer_H

#include "ExportedByCATMathStream.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

class CATMathPolyBuffers;
class CATMathStream;

/*
 * Streamer for CATMathPolyBuffers
 */
class ExportedByCATMathStream CATMathPolyBuffersStreamer
{

public :

  /**
   * @param iStreamRecord
   *   The optional records of the polyhedral objects that have been streamed.
   *   The streamer adds to the records each polyhedral object that it streams.
   */
  CATMathPolyBuffersStreamer (CATMathStream& iStream);

  ~CATMathPolyBuffersStreamer ();

public:

  /**
   * Streams a CATMathPolyBuffers onto a CATMathStream.
   * @param iPolyBuffers
   *   The object to stream.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity has been successfully streamed.
   *   <li> <code> S_FALSE </code> if the entity cannot be streamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  HRESULT Stream (const CATMathPolyBuffers& iPolyBuffers);

  /**
   * Unstreams a CATMathPolyBuffers from a CATMathStream.
   * @param oPolyBuffers
   *   The object to be created and unstreamed.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity has been successfully unstreamed.
   *   <li> <code> S_FALSE </code> if the entity cannot be unstreamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  HRESULT Unstream (CATMathPolyBuffers*& oPolyBuffers);

private:

  CATMathStream& _Stream;

};

#endif
