#ifndef CATManifold_h
#define CATManifold_h

// COPYRIGHT DASSAULT SYSTEMES  2013

#include "CATGeometry.h"
#include "ListPOfCATManifoldParameter.h"

#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATManifold ;
#else
extern "C" const IID IID_CATManifold ;
#endif

#include "ListPOfCATCellManifold.h"
#include "ListPOfCATManifoldParamId.h"

class CATUuid;
class CATDRepLabel;
class CATLiveBody;
class CATDeclarativeManifold;
class CATCellManifoldGroup;

class ExportedByCATGMModelInterfaces CATManifold : public CATGeometry
{
  CATDeclareInterface;

public:

  virtual void    GetCellManifoldRep(ListPOfCATCellManifold &oReps) const = 0; 
  virtual HRESULT GenerateParameters (CATTopData * iTopData, ListPOfCATManifoldParameter &oManifoldParameters) = 0;

  virtual CATDeclarativeManifold  * GetAsDeclarativeManifold() const = 0;
  virtual CATCellManifoldGroup    * GetAsCellManifoldGroup() const = 0;

//===========================================================================
// Naming Acces
//===========================================================================
/**  
  * @return 
  *   Return TRUE if this kind of manifold is a publishable object (static).  
  *   It doesnt check dynamically if the manifold is already published by the application in any way.
  */
  virtual CATBoolean     IsPublishable()   = 0;

  /**
  * Check if this Manifold has a label.
  */
  virtual CATBoolean     DRepNameExists()  = 0;

  /**
  * Retrieve existing Label, or create a new one if this
  * manifold has none.
  * To free after use.
  */
  virtual CATDRepLabel * CreateDRepLabel(CATLiveBody * ipLiveBody) = 0;

  /**
  * Retrieve existing Label only.
  * If this Manifold has no label, it will return NULL.
  * To free after use.
  */
  virtual CATDRepLabel * GetExistingDRepLabel() = 0;

  /**
  * Force creation of a new label for this manifold.
  * To call with caution, CGM/CDM internal use only.
  * To free after use.
  */
  virtual CATDRepLabel * CreateNewLabel(CATLiveBody * ipLiveBody) = 0;


  // -----------------------------------------------------------------------------------
  // CDM - Publishable ParamID
  // -----------------------------------------------------------------------------------
  virtual HRESULT GetPublishableManifoldParamId (ListPOfCATManifoldParamId & oManifoldParamIdList) const = 0;

};
  
CATDeclareHandler(CATManifold,CATGeometry);

#endif
