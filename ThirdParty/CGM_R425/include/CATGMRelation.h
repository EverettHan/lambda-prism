//===================================================================
// COPYRIGHT [!output company] 2010/03/12
//===================================================================
// Header definition of class CATGMRelation
//===================================================================

// Interface on a CDMRelation, dedicated for applications that may not require CDMModel framework
// These objects are twins of CDMRelation, their lifecycles are identical
// A CATGMRelation is either a CATGMConstraint or a CATGMEquation

//===================================================================
//  2010/07/28 Creation: chu
//===================================================================
#ifndef CATGMRelation_H
#define CATGMRelation_H

#include "CATErrorDef.h"
#include "CATSysBoolean.h"
#include "CATCDMRelationEnum.h"
#include "ListPOfCATCellManifold.h" 
#include "CATListOfCATCells.h"
#include "ListPOfCATBody.h"
#include "CATCDMBaseInterfaces.h" // export

class CDMRelation;
class CATBody;
class CATGMConstraint;
class CATGMMatchConstraint;
class CATGMEquation;
class CATGMMirror;
class CATIProperty_var;
class CATCDMRelationCacheData;

class ExportedByCATCDMBaseInterfaces CATGMRelation
{
public:

  // Lifecycle
  virtual ~CATGMRelation();

  // Investigate the relation
  virtual CATCDMRelationEnum::RelType GetRelType() = 0;
  virtual CATCDMRelationEnum::RelStatus GetRelStatus(CATBoolean iNewest = TRUE) = 0;
  virtual CATCDMRelationEnum::RelOrientation GetRelOrientation() = 0;
  virtual CATBoolean IsInactive(CATBoolean iNewest = FALSE) = 0;

  // Change Status, Orientation, or activity
  virtual HRESULT SetRelStatus(CATCDMRelationEnum::RelStatus  iStatus) = 0;
  virtual HRESULT SetRelOrientation(CATCDMRelationEnum::RelOrientation  iOrientation) = 0;
  virtual HRESULT ActivateRelation() = 0;
  virtual HRESULT DeactivateRelation() = 0;

  // Cache management
  virtual HRESULT GetCache(CATCDMRelationCacheData& oCache) = 0;

  // Get Properties (create them if needed)
  virtual HRESULT GetProperty(CATIProperty_var & oProperty);

  // Cast to constraint or equation
  virtual CATGMEquation * SafeCastToGMEquation();
  virtual CATGMConstraint * SafeCastToGMConstraint();
  virtual CATGMMatchConstraint * SafeCastToGMMatchConstraint();
  virtual CATGMMirror * SafeCastToGMMirror();

  // Internal Use
  virtual CDMRelation & GetAssociatedRelation() = 0;

  // Get an Id for the GMRelation which is stable when streaming/unstreaming
  virtual CATULONG32 GetStableId() = 0;

  // Get the current state of the constraint
  virtual CATCDMRelationEnum::RelState GetRelState() = 0;

  

protected:

  CATGMRelation();

private:

  // The copy constructor and the equal operator must not be implemented
  CATGMRelation (CATGMRelation &);
  CATGMRelation& operator=(CATGMRelation&);

};

//-----------------------------------------------------------------------
#endif
