#ifndef CATGeoPolyObjectsUnstreamManager_H
#define CATGeoPolyObjectsUnstreamManager_H

//=============================================================================
// COPYRIGHT Dassault Systemes 2015
//=============================================================================
//
// CATGeoPolyObjectsUnstreamManager.h
//
//  Unstream management for all polyhedral objects wrapped under CATGeoPolyGeometry objects 
//
//
//=============================================================================
// Usage Notes:
//
//  This manager allows the recursive Unstream of dependencies with an updated map to not unstream twice the same object
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


class CATCGMStream;
class CATIPolyObject;
class CATIPolyPoint;
class CATIPolyCurve;
class CATIPolySurface;
class CATPolyBody;


class ExportedByYP00IMPL CATGeoPolyObjectsUnstreamManager : public CATBaseUnknown
{
	//CATDeclareInterface;

public:


  /**
  * Unstreams all the polyhedral objects (recorded objects + all their dependencies)
  * @return
  * <ul>
  *   <li> <code> S_OK </code> if all the entities have been successfully unstreamed.
  *   <li> <code> E_FAIL </code> if one entity cannot be unstreamed.
  * </ul>
  */
  virtual HRESULT UnstreamAll(CATBoolean iThrowInCaseOfFailure = FALSE)=0;


  /**
  * Retrieves a polyhedral object (native to PolyhedralObjects) among a list of objects unstreamed from a CATMathStream.
  * @param iStreamObjectID
  *   The unique identifier associated to the PolyObject during the Stream transaction
  * @param oPolyObject / oPolyPoint / oPolyCurve / oPolySurface / oPolyBody
  *   The object to retrieve.
  *   Returns always the same PolyObject from the same ID in case of multiple calls
  * @return
  * <ul>
  *   <li> <code> S_OK </code> if the object has been successfully retrieved.
  *   <li> <code> E_FAIL </code> if the object cannot be retrieved.
  * </ul>
  */
  virtual HRESULT RetrievePolyObjectFromID(unsigned int & iStreamObjectID, CATIPolyPoint   * & oPolyPoint)=0;
  virtual HRESULT RetrievePolyObjectFromID(unsigned int & iStreamObjectID, CATIPolyCurve   * & oPolyCurve)=0;
  virtual HRESULT RetrievePolyObjectFromID(unsigned int & iStreamObjectID, CATIPolySurface * & oPolySurface)=0;

  virtual HRESULT RetrievePolyBodyFromID(unsigned int & iStreamObjectID, CATPolyBody * & oPolyBody)=0;


  // ---------------------------------------------------
  // No destructor, use Release() instead

};


// *******************************************************
// Global Create method dedicated to the CATCGMStreamCGMImpl class.
// Please, consider this as a private service reserved for friend classes.
// *******************************************************
ExportedByYP00IMPL CATGeoPolyObjectsUnstreamManager * CATCreateGeoPolyObjectsUnstreamManager(CATCGMStream & iCGMStr);

// CATDeclareHandler(CATGeoPolyObjectsUnstreamManager,CATBaseUnknown);

#endif

