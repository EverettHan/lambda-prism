//===================================================================
// COPYRIGHT [!output company] 2010/03/12
//===================================================================
// Header definition of class CATGMPublication
//===================================================================

// Interface on a CDMPublication, dedicated for applications that may not require CDMModel framework
// These objects are twins of CDMPublication, their lifecycles are identical

//===================================================================
//  2014/09/19 Creation: juz
//===================================================================
#ifndef CATGMPublication_H
#define CATGMPublication_H

#include "CATErrorDef.h"
#include "CATSysBoolean.h"
#include "CATCDMRelationEnum.h"
#include "CATCDMPublicationEnum.h"
#include "CATCDMBaseInterfaces.h" // export

class CDMPublication;
class CATGMSupport;
class CATGMRelation;
class CATGMFunction;

class ExportedByCATCDMBaseInterfaces CATGMPublication
{
public:

  // Lifecycle
  virtual ~CATGMPublication();

  // Investigate the publication
  virtual CATCDMRelationEnum::RelStatus GetRelStatus(CATBoolean iNewest = TRUE) = 0;
  virtual HRESULT SetRelStatus(CATCDMRelationEnum::RelStatus  iStatus) = 0;

  virtual CATCDMPublicationEnum::PublishMode GetPublishMode() = 0;

  // Get the published object if this a a publication of DRep 
  // oSupport must be deleted by caller
  virtual HRESULT GetPublishedSupport(CATGMSupport*& oSupport) = 0;
  // Get the published object if this a a publication of DRep 
  // oRelation must not be deleted by caller
  virtual HRESULT GetPublishedRelation(CATGMRelation*& oRelation) = 0;
  
  // oFunction must not be deleted by caller
  virtual HRESULT GetPublishedFunction(CATGMFunction*& oFunction) = 0;

  // Internal Use
  virtual CDMPublication & GetAssociatedPublication() = 0;

  // Get an Id for the GMRelation which is stable when streaming/unstreaming
  virtual CATULONG32 GetStableId() = 0;

  // Get the current state of the constraint
  virtual CATCDMRelationEnum::RelState GetRelState() = 0;

 
protected:
  CATGMPublication();

private:

  // The copy constructor and the equal operator must not be implemented
  CATGMPublication (CATGMPublication &);
  CATGMPublication& operator=(CATGMPublication&);

};

//-----------------------------------------------------------------------
#endif
