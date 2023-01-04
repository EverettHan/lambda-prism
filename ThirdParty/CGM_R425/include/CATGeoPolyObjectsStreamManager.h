#ifndef CATGeoPolyObjectsStreamManager_H
#define CATGeoPolyObjectsStreamManager_H

//=============================================================================
// COPYRIGHT Dassault Systemes 2015
//=============================================================================
//
// CATGeoPolyObjectsStreamManager.h
//
//  Stream management for all polyhedral objects wrapped under CATGeoPolyGeometry objects 
//
//
//=============================================================================
// Usage Notes:
//
//  This manager allows the recursive stream of dependencies with an updated map to not stream twice the same object
//
//=============================================================================
// Creation:      DPS, October. 2015
// Modification:  DPS, March    2021       Add CATPolyBody LifeCycle Management
//=============================================================================

#include "CATIACGMLevel.h"
#include "YP00IMPL.h" 
#include "CATBaseUnknown.h"

#include "CATBoolean.h"
#include "CATSysBoolean.h"
#include "CATErrorDef.h"


class CATGeometry;
class CATCGMStream;
class CATIPolyObject;
class CATIPolyPoint;
class CATIPolyCurve;
class CATIPolySurface;
class CATPolyBody;


class ExportedByYP00IMPL CATGeoPolyObjectsStreamManager : public CATBaseUnknown
{
	//CATDeclareInterface;

public:


  /**
  * Records all the polyhedral objects (native to PolyhedralObjects) on which a polyhedral CATGeometry depends
  * @param iPolyGeometryCGM
  *   The polyhedral CATGeometry which potentially depends on polyhedral objects to record.
  * @return
  * <ul>
  *   <li> <code> S_OK </code> if the dependencies have been successfully recorded.
  *   <li> <code> S_FALSE </code> if there is no dependency to record
  *   <li> <code> E_FAIL </code> if at least one dependency cannot be recorded (nto found or not native to PolyhedralObjects then not streamable).
  * </ul>
  */
  virtual HRESULT RecordPolyObjectDependencies(const CATGeometry &iPolyGeometryCGM)=0;
  

  /**
  * Streams all the polyhedral objects (recorded objects + all their dependencies)
  * @return
  * <ul>
  *   <li> <code> S_OK </code> if the entity has been successfully streamed.
  *   <li> <code> S_FALSE </code> if the entity cannot be streamed.
  *   <li> <code> E_FAIL </code> or any other error if an error occurs.
  * </ul>
  */
  virtual HRESULT StreamAll(CATBoolean iThrowInCaseOfFailure = FALSE)=0;


  /**
  * Retrieves the ID associated to a polyhedral object to stream (native to PolyhedralObjects) 
  * @param iPolyObject / iPolyPoint / iPolyCurve / iPolySurface / iPolyBody
  *   The object to stream.
  * @param oStreamObjectID
  *   The unique identifier associated to the PolyObject instance
  *   a null value means that the object hasn't be recorded (because not native to PolyhedralObjects)
  *   Returns always the same identifier for a same PolyObject (already recorded)
  * @return
  * <ul>
  *   <li> <code> S_OK </code> if the object has been successfully recorded with a positive ID
  *   <li> <code> E_FAIL </code> if any ID has been found by the StreamManager for this object
  * </ul>
  */
  virtual HRESULT RetrieveIDFromPolyObject(const CATIPolyPoint & iPolyPoint, unsigned int & oStreamObjectID)=0;
  virtual HRESULT RetrieveIDFromPolyObject(const CATIPolyCurve & iPolyCurve, unsigned int & oStreamObjectID)=0;
  virtual HRESULT RetrieveIDFromPolyObject(const CATIPolySurface & iPolySurface, unsigned int & oStreamObjectID)=0;

  virtual HRESULT RetrieveIDFromPolyBody(const CATPolyBody & iPolyBody, unsigned int & oStreamObjectID)=0;


  // ---------------------------------------------------
  // No destructor, use Release() instead

};


// *******************************************************
// Global Create method dedicated to the CATCGMStreamCGMImpl class.
// Please, consider this as a private service reserved for friend classes.
// *******************************************************
ExportedByYP00IMPL CATGeoPolyObjectsStreamManager * CATCreateGeoPolyObjectsStreamManager(CATCGMStream & iCGMStr);

// CATDeclareHandler(CATGeoPolyObjectsStreamManager,CATBaseUnknown);

#endif
