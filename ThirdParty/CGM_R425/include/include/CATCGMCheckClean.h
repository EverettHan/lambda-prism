/* -*-c++-*- */
#ifndef CATCGMCheckClean_h
#define CATCGMCheckClean_h

//============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//============================================================================
// 
// interface CATCGMCheckClean :
// 
// 
// This interface is an adaptation for CGM of the following interfaces :
//    - CATICheckObject
//    - CATICleanObject
//
//============================================================================
//
// Usage Notes : all CATCGMObject (CATICGMUnknown if CATCGMBOAObject is
//               defined) objects implement this interface throught a
//               CATCGMCleaner data extension.
//
//============================================================================
// Jul. 02  Creation                                                    HCN
// Oct. 02  DetectUserActivatedRules(...)                               HCN
// Nov. 02  CallMethod                                                  HCN
// May. 03  SpecificCheckCall                                           HCN
//============================================================================

#include "ExportedByCATGMGeometricInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATListOfCATUnicodeString.h"
#include "CATBoolean.h"

class CATSoftwareConfiguration;
class CATCheckReport;
class CATCX_CHECKUP;
class CATCGMCheckBehavior;
class CATUnicodeString;
class CATICGMUnknown;

extern ExportedByCATGMGeometricInterfaces IID IID_CATCGMCheckClean ;

class ExportedByCATGMGeometricInterfaces CATCGMCheckClean : public CATBaseUnknown
{
  CATDeclareInterface;

  public:

  enum CallMethod {DetectAllRulesCall, BodyCompletedCall, BRepLinkCall, SpecificCheckCall};

  // equivalent to CATICheckObject
  virtual HRESULT GetCheckRules(CATListOfCATUnicodeString & ioRuleCodeList) = 0;

  virtual HRESULT DetectAllRules(CATCheckReport* CheckReport) = 0;

  virtual HRESULT DetectSpecificRules(CATListOfCATUnicodeString & RuleCodeList, CATCheckReport* CheckReport) = 0;

  // equivalent to CATICleanObject
  virtual HRESULT GetCleanRules(CATListOfCATUnicodeString & ioRuleCodeList) = 0;

  virtual HRESULT Clean(CATCheckReport* CheckReport) = 0;

  // for CGM use
  virtual void* GetCGMCleaner() = 0;

  virtual int DetectUserActivatedRules(CATSoftwareConfiguration*    ipSoftConf,
                                       CATICGMUnknown*              ipSpecificToCheck,
                                       CATListOfInt*                ipSpecificRuleIDs,
                                       CATCX_CHECKUP*               iopCATCX_Report,
                                       CATCGMCheckBehavior*         ipCheckBehavior,
                                       CATUnicodeString*            ipFeatureName = NULL,
                                       CATCGMCheckClean::CallMethod iCallMethod = BodyCompletedCall,
                                       CATUnicodeString*            ipErrorDialogMsg = NULL) = 0;
};

CATDeclareHandler(CATCGMCheckClean,CATBaseUnknown);

#endif 
