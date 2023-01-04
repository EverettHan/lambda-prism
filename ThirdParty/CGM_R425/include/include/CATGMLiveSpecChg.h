#ifndef  CATGMLiveSpecChg_H
#define  CATGMLiveSpecChg_H
//===================================================================
// COPYRIGHT Dassault Systemes 2011
//===================================================================
//
//  CATGMLiveSpecChg.h
// 		
//===================================================================
//  July 2011  Creation: IZE
//===================================================================

#include "PersistentCell.h"
#include "CATManifoldBaseParameter.h"

#include "CATCGMAttribute.h"
#include "ListPOfCATGMLiveSpecChg.h"

class CATICGMObject;
class CATManifoldParameter;

class  ExportedByPersistentCell CATGMLiveSpecChg : public CATCGMAttribute
{
public:
  CATCGMDeclareAttribute(CATGMLiveSpecChg, CATCGMAttribute);

  static CATGMLiveSpecChg* GetSpecChg(CATICGMObject* iObject);
  static void GetSpecChg(CATICGMObject* iObject, ListPOfCATGMLiveSpecChg& oSpecChgList);

  CATGMLiveSpecChg(CATManifoldBaseParameter* iTargetParam);
  CATGMLiveSpecChg();
  virtual ~CATGMLiveSpecChg();

  // New official
  CATManifoldBaseParameter * GetTargetBaseParam() const;
  // New official
  void SetTargetBaseParam(CATManifoldBaseParameter* iTargetBaseParam);


  // Deprecated - W48-2015
  CATManifoldParameter * GetTargetParam() const;
  // Deprecated - W48-2015
  void SetTargetParam(CATManifoldParameter* iTargetParam);


  virtual CATCGMAttribute * ReportClonableAttributes(CATExtClonableManager* iClonableManager, 
    CATICGMObject *iOrigin, 
    CATICGMObject *iDestination);

private:

  CATManifoldBaseParameter * _TargetBaseParam;

};

#endif // CATGMLiveSpecChg_H 

