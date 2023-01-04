// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyhedralObjectsUnstreamer.h
//
//===================================================================
// September 2015 Creation: NDO
//===================================================================
#ifndef CATPolyhedralObjectsUnstreamer_H
#define CATPolyhedralObjectsUnstreamer_H

#include "PolyStream.h"
#include "CATErrorDef.h"

class CATIPolyObject;
class CATIPolySurface;
class CATIPolyCurve;
class CATIPolyPoint;
class CATPolyBody;

class CATMathStream;
class CATPolyStreamerRegistry; 
class CATPolyUnstreamRecord;


/*
 * Unstreamer for native polyhedral objects implementing the following interfaces:
 * <ul>
 *   <li> CATIPolyObject
 *   <li> CATIPolyPoint
 *   <li> CATIPolyCurve
 *   <li> CATIPolySurface
 * </ul>
 * This unstreamer only supports the implementations found in PolyhedralObjects.
 */
class ExportedByPolyStream CATPolyhedralObjectsUnstreamer
{

public :

  /**
   * @param iUnstreamRecord
   *   The optional records of the polyhedral objects that have been unstreamed.
   *   The unstreamer adds to the records each polyhedral object that it unstreams.
   */
  CATPolyhedralObjectsUnstreamer (CATMathStream& iStream, CATPolyUnstreamRecord* iUnstreamRecord = 0);

  ~CATPolyhedralObjectsUnstreamer ();

public:

  /**
   * Sets the filtering options for the various layers.
   * By default all layers are streamed.
   * @param f
   *   The filter.  This argument is a CATPolyStreamOptions::LayerFilter enumerator or 
   *   any valid combinations of the enumerators.
   * @see CATPolyStreamOptions::LayerFilter
   */
  inline void SetLayerFilter (unsigned int f);

public:

  /**
   * Unstreams a polyhedral object (native to PolyhedralObjects) from a CATMathStream.
   * The unstreaming of a polyhedral object depending on a parent polyhedral object will 
   * trigger the unstreaming of the parent if it has not been found in the records.
   * @param iPolyObject
   *   The object to stream.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity has been successfully unstreamed.
   *   <li> <code> S_FALSE </code> if the entity cannot be unstreamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  HRESULT Unstream (CATIPolyObject*& oPolyObject);

  /**
   * Unstreams a polyhedral body (native to PolyhedralObjects) from a CATMathStream.
   * @param oPolyBody
   *   The CATPolyBody to stream.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity has been successfully unstreamed.
   *   <li> <code> S_FALSE </code> if the entity cannot be unstreamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  HRESULT Unstream (CATPolyBody*& oPolyBody);

public:

  /**
   * Unstreams all the polyhedral objects before the pull.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> if the entity has been successfully unstreamed.
   *   <li> <code> S_FALSE </code> if the entity cannot be unstreamed.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   * NOT YET IMPLEMENTED.
   */
  HRESULT Unstream ();

  /**
   * Pulls an object from the stream and returns its tag.
   * Given its tag, an object can be pulled several times.
   * The objet returned must be released.
   * NOT YET IMPLEMENTED.
   */
  HRESULT Pull (unsigned int& tag, CATIPolyObject*& oPolyObject);

private:

  unsigned int _LayerFilter;
  bool _DeleteRecords;

  CATMathStream& _Stream;
  CATPolyStreamerRegistry& _StreamerRegistry;
  CATPolyUnstreamRecord* _Records;

};

inline void CATPolyhedralObjectsUnstreamer::SetLayerFilter (unsigned int f)
{
  _LayerFilter = f;
}

#endif
