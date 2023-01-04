//===================================================================
// COPYRIGHT [!output company] 2010/03/12
//===================================================================
// Header definition of class CATCDMBaseServices
//===================================================================

// Investigate the CDM model
// An instance of this class is created to enable queries on the CDM model made by DRep and CGM
// The implementation is in CDMModel. Proxies are created to stand for CDM objects (e.g. constraints)

//===================================================================
//  2010/07/12 Creation: Creation: chu
//===================================================================
#ifndef CATCDMBaseServices_H
#define CATCDMBaseServices_H

#include "CATErrorDef.h"          // HRESULT definition
#include "CATCDMBaseInterfaces.h" // export
#include "ListPOfCATBody.h" 

class CATCell;
class CATBody;
class CATGMRelation;
class CATGMConstraint;
class CATGMGroup;
class CATGMRigidGroup;
class CATDeclarativeContext;
class CATMathStream;
class CATCGMOutput;
class CATBaseUnknown;
class CATUnicodeString;
class CATMathPlane;
class CATGMPublication;
class CATCGMBaseServices;
class CATGMVolatileSetOfObjects;

class ExportedByCATCDMBaseInterfaces CATCDMBaseServices
{
public:

  virtual ~CATCDMBaseServices();

  // Iterate on all relations (constraints or equations)
  virtual HRESULT  NextRelation ( CATGMRelation *& ioRelation) = 0;

  // Iterate on all rigid groups 
  virtual HRESULT  NextRigidGroup ( CATGMRigidGroup *& ioRigidGroup) = 0;

  // Iterate on all publication 
  virtual HRESULT  NextPublication ( CATGMPublication *& ioPublication) = 0;

  // Iterate on constraints involving a given cell: NOT YET IMPLEMENTED (MAYBE NOT REQUIRED) 
  virtual HRESULT  NextConstraintOnGivenCell ( CATBody * iBody, CATCell* iCell, CATGMConstraint *& ioConstraint) = 0;

  // Iterate on groups owning a given cell: NOT YET IMPLEMENTED (MAYBE NOT REQUIRED) 
  virtual HRESULT  NextGroupOwningCell ( CATBody * iBody, CATCell * iCell, CATGMGroup *& ioGroup) = 0; 

  // Get the SoftGroup   
  virtual HRESULT NextVolatileSetOfObject(CATGMVolatileSetOfObjects *&oVolSet) { return E_NOTIMPL; };

  // Stream CDM Model without using the GN graph (labels are streamed by CGMIds). This method is dedicated to debug or test-objects
  // Note that a symmetric method exists in the interface CATICDMUnstreamWithoutGN, which an empty CDMManager component (e.g. created by CATICreateInstance) may query
  virtual HRESULT StreamCDMModelWithoutGN( CATMathStream & oCDMStream) = 0;

  // Dump all constraints (for debug purposes). Note that returned HRESULT indicates an internal error in CDM model, these errors do not interrupt the dump
  virtual HRESULT DumpConstraints(CATCGMOutput & s) = 0;

  // Feed a CDM model with all XVM objects found in a given body's attributes
  virtual HRESULT FeedWithXVM(CATBody * iBodyWithXVM) = 0;

  // Read the declarative context
  virtual HRESULT  GetDeclarativeContext(CATDeclarativeContext *& oContext) = 0; 

  // Services to get objects seen by appli from objects seen by variationnal and the inverse.
  virtual HRESULT GetGMRelationFromCDMObject(CATBaseUnknown* iCDMObject, CATGMRelation*& oGMRelation);
  virtual HRESULT GetCDMObjectFromGMRelation(CATGMRelation* iGMRelation, CATBaseUnknown*& oCDMObject);

	// Get a constraint from its name
	virtual HRESULT GetConstraintFromName(CATUnicodeString & iName, CATGMConstraint* & oConstraint) = 0;
  
	// Get the fix bodies (bodies imported from the procedural world and that can't be moved by the variational)
	virtual HRESULT GetFixBodies(CATLISTP(CATBody) & oFixBodiesList) = 0;

  // Get all current bodies 
	virtual HRESULT GetAllCurrentBodies(CATLISTP(CATBody) & oFixBodiesList) = 0;

  // TO BE USED IN CGMREPLAY ONLY !! : Create a Mirror 
  virtual HRESULT CreateCDMNotStreamedMirror(const CATMathPlane& iPlane) = 0;

  // Get the Relation (constraint or equation) corresponding to the input Id. Fails if no one is found for this Id
  virtual HRESULT GetRelationFromID (CATULONG32 iID, CATGMRelation *& ioRelation) = 0;

  // Get the RigidGroup corresponding to the input Id. Fails if no one is found for this Id
  virtual HRESULT GetRigidGroupFromID (CATULONG32 iID, CATGMRigidGroup *& ioRigidGroup) = 0;

  // safe cast
  virtual CATCGMBaseServices * SafeCastToCGMBaseServices();

};
//-----------------------------------------------------------------------
#endif
