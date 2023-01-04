/* -*-c++-*- */

/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 */
#ifndef CATGeoCln_H
#define CATGeoCln_H

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2002
// DESCRIPTION : Base abstract class for CGM check rules as used
//               by the CGM cleaner
//
// Feb. 02	Creation                                                      HCN
// Mar. 02  GetExtendedCheckErrorMsg(...)                                 HCN
// Avr. 02  SetFederator(...)                                             HCN
// Jul. 02  ICGMEntityIsA(), ICGMEntityID()                               HCN
// Oct. 02  _OnlyCheckOnBRepLink, _FirstTimeErrorOnly,
//          _pStaticTableChkCGMEntsKO, _pStaticTableChkCGMEntsKOWitns,
//          _pErrorDialogMsg, SetpErrorDialogMsg(...),
//          GetGeoFactory(),
//          _pTraceStream a la place de _pTrace,
//          SetpTraceStream(...)                                          HCN
// Nov. 02  _CheckLoadedEntity                                            HCN
// Jun. 03  Appel a CATCGMNewClassArray dans la macro
//          CATCGMCLEANER_RULE_IMPLEMENTHCN                               HCN
// Jul. 03  SetSoftwareConfiguration(...)                                 HCN
// Oct. 03  _pCheckParameter,
//          SetCheckParameter(...)/GetCheckParameter(...)                 HCN
// Nov. 03  Methode globale RuleName##CreateRule(...)
//          BuildRuleCreationFunctionName(...),
//          CATCGMCLEANER_RULE_CREATE_DECLARE,
//          CATCGMCLEANER_RULE_CREATE_IMPLEMENT,
//          On peut passer une CATSoftwareConfiguration NULL,
//          GetConfig() cree une config si necessaire                     HCN
// Dec. 03  Remplacement de CATUnicodeString _ExtendedCheck/CleanErrorMsg
//          par CATUnicodeString* _pExtendedClean/CleanErrorMsg,
//          GetpExtendedCheckErrorMsg(), GetpExtendedCleanErrorMsg()      HCN
// Jan. 04  _pCATCX_Report, SetpCATCX_CHECKUP(...), GetpCATCX_CHECKUP()   HCN
// Jan. 04  _pCheckTransacParamList,
//          SetCheckTransacParamList(...)/GetCheckTransacParamList(...)   FDN
//=============================================================================

#include "ExportedByGeometricObjects.h"
#include "CATGeoClnIDs.h"
#include "CATCGMRuleDef.h"
#include "CATBoolean.h"
#include "CATListOfCATICGMUnknowns.h"
#include "CATUnicodeString.h"
#include "CATCGMNewArray.h" // Pour eviter les #include dans .cpp les classes derivees
#include "CATCGMNewClassArray.h" // Pour eviter les #include dans .cpp les classes derivees
#include "CATTrace.h"       // Pour eviter les #include dans .cpp les classes derivees
#include "CATCGMVirtual.h"
#include "CATSoftwareConfiguration.h"
#include "CATGeoClnCheckParameter.h"
#include "CATCGMCheckDeclarations.h"
#include "CATMathInline.h"

class CATGeoFactory;
class CATICGMUnknown;
class CATUnicodeString;
class CATHashTabCATICGMUnknown;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
class CATString;
class CATCX_CHECKUP;
class CATCGMCheckRule;

// HCN a commenter
// #define TRACES_GEO_CLN

#ifdef TRACES_GEO_CLN
  #include <iostream.h>
#endif

#define CATGEOCLN_EXTENDED_MSG_MAX_LENGTH 65536

class ExportedByGeometricObjects CATGeoCln : public CATCGMVirtual
{

public:

  enum CATCGMCleanerAction {CATCGMCleanerCheck, CATCGMCleanerClean};

  CATGeoCln(CATSoftwareConfiguration* ipConfig,
            CATICGMUnknown*           ipICGMFederator,
            CATCGMRuleDef*            ipCGMRuleDef,
            CATBoolean                iVerbose);

  virtual ~CATGeoCln();

  enum CATGeoClnStatus {StatusUnset, StatusOK, StatusKO};

  static void BuildRuleCreationFunctionName(const char* ipRuleClassName, CATString& ioCreationFunctionName);
  
  // pure virtual methods to be implemented by children
  virtual int CheckCGMEntity() = 0;
  virtual int CleanCGMEntity() = 0;

  INLINE CATGeoClnIDs::RuleID        GetID() const;

  INLINE void                        SetICGMEntity(CATICGMUnknown* ipICGMEntity);
  INLINE CATICGMUnknown*             GetICGMEntity() const;

  virtual const char*                ICGMEntityIsA() const;
  virtual CATULONG32               ICGMEntityID() const;

  CATGeoFactory*                     GetGeoFactory() const;

  INLINE void                        SetFederator(CATICGMUnknown* ipICGMFederator);
  INLINE void                        SetSoftwareConfiguration(CATSoftwareConfiguration* ipConfig);

  INLINE void                        SetStatus(CATGeoCln::CATGeoClnStatus iStatus);
  INLINE CATGeoCln::CATGeoClnStatus  GetStatus() const;

  //void                               SetFixable(CATBoolean iFixable);
  INLINE CATBoolean                  IsFixable() const;

  INLINE CATBoolean                  IsVerbose() const;

  INLINE void                        SetFixIfKO(CATBoolean iFixIfKO);
  INLINE CATBoolean                  GetFixIfKO() const;

  INLINE void                        SetSeverity(short iSeverity);
  INLINE short                       GetSeverity() const;

  INLINE void                        SetCodeLevel(int iCodeLevel);
  INLINE int                         GetCodeLevel() const;

  INLINE void                        SetCheckLoadedEntity(CATBoolean iCheckLoadedEntity);
  INLINE CATBoolean                  GetCheckLoadedEntity() const;

  INLINE void                        SetOnlyCheckOnBRepLink(CATBoolean iOnlyCheckOnBRepLink);
  INLINE CATBoolean                  GetOnlyCheckOnBRepLink() const;

  INLINE void                        SetFirstTimeErrorOnly(CATBoolean iFirstTimeErrorOnly);
  INLINE CATBoolean                  GetFirstTimeErrorOnly() const;

  INLINE void                        SetCheckParameter(CATGeoClnCheckParameter* ipCheckParameter);
  INLINE CATGeoClnCheckParameter*    GetCheckParameter();
  
  INLINE void                        SetCheckTransacParamList(CATLISTP(CATGeoClnCheckParameter) * ipCheckTransacParamList);
  INLINE CATLISTP(CATGeoClnCheckParameter) * GetCheckTransacParamList();   

  CATSoftwareConfiguration*          GetConfig(); // Creates an open CATSoftwareConfiguration if needed

  INLINE void                        SetMsgCatalogName(char* ipMsgCatalogName);

  INLINE void                        SetpErrorDialogMsg(CATUnicodeString* ipErrorDialogMsg);

  INLINE void                        SetpTraceStream(ostream* ipTraceStream);

  INLINE void                        SetpCATCX_CHECKUP(CATCX_CHECKUP* iopCATCX_Report);
  INLINE CATCX_CHECKUP*              GetpCATCX_CHECKUP();

  void LoadErrorMsgChkFromCatalog(CATUnicodeString& ioErrorMessage,
                                  CATUnicodeString& ioShortMessage,
                                  const char* ipRuleCode);

  void LoadErrorMsgClnFromCatalog(CATUnicodeString& ioErrorMessage,
                                  CATUnicodeString& ioShortMessage,
                                  const char* ipRuleCode,
                                  CATBoolean Success);

  INLINE void ResetExtendedCheckErrorMsg();
  INLINE void ResetExtendedCleanErrorMsg();

  virtual void GetExtendedCheckErrorMsg(CATUnicodeString& ioErrorMessage);
  virtual void GetExtendedCleanErrorMsg(CATUnicodeString& ioErrorMessage);

  virtual int AuthorizationCheckFailure(const int& iCheckRC);

protected:
  CATGeoClnIDs::RuleID        _ID;

  CATICGMUnknown*             _pICGMEntity;
  CATICGMUnknown*             _pICGMFederator;
  CATSoftwareConfiguration*   _pConfig;

  CATGeoClnStatus             _Status;
  CATBoolean                  _Fixable;
  CATBoolean                  _FixIfKO;
  short                       _Severity;
  int                         _CodeLevel;

  CATBoolean                  _CheckLoadedEntity;
  CATBoolean                  _OnlyCheckOnBRepLink;
  CATBoolean                  _FirstTimeErrorOnly;

  CATBoolean                  _Verbose;

  const char*                 _pMsgCatalogName;

  CATGeoClnCheckParameter*    _pCheckParameter;

  CATLISTP(CATGeoClnCheckParameter) * _pCheckTransacParamList;

  ostream*                    _pTraceStream;

  CATUnicodeString*           _pErrorDialogMsg;

  CATULONG32                  _Tag;

  CATLISTP(CATICGMUnknown)    _ListOfKOWitnesses;

  CATHashTabCATICGMUnknown*   _pStaticTableChkCGMEntsKO;
  CATHashTabCATICGMUnknown*   _pStaticTableChkCGMEntsKOWitns;

  CATUnicodeString*           _pExtendedCheckErrorMsg;
  CATUnicodeString*           _pExtendedCleanErrorMsg;

  CATCX_CHECKUP*              _pCATCX_Report;

protected:
  CATUnicodeString* GetpExtendedCheckErrorMsg();

  CATUnicodeString* GetpExtendedCleanErrorMsg();

  void LoadErrorMsgFromCatalog(CATUnicodeString& ioErrorMessage,
                               CATUnicodeString& ioShortMessage,
                               const char* ipRuleCode,
                               const char* pChkOrClnKey,
                               CATICGMUnknown* ipFederator,
                               CATBoolean* pSuccess = 0);

  int UpdateLatestChkCGMEntsKOWitns();

  friend class CATCGMCheckRule;

};


//-----------------------------------------------------------------------------
// GetID
//-----------------------------------------------------------------------------
INLINE CATGeoClnIDs::RuleID CATGeoCln::GetID() const
{
  return _ID;
}

//-----------------------------------------------------------------------------
// SetICGMEntity
//-----------------------------------------------------------------------------
INLINE void CATGeoCln::SetICGMEntity(CATICGMUnknown* ipICGMEntity)
{
  _pICGMEntity = ipICGMEntity;
}

//-----------------------------------------------------------------------------
// GetICGMEntity
//-----------------------------------------------------------------------------
INLINE CATICGMUnknown* CATGeoCln::GetICGMEntity() const
{
  return _pICGMEntity;
}

//-----------------------------------------------------------------------------
// SetFederator
//-----------------------------------------------------------------------------
INLINE void CATGeoCln::SetFederator(CATICGMUnknown* ipICGMFederator)
{
  _pICGMFederator = ipICGMFederator;
}

//-----------------------------------------------------------------------------
// SetSoftwareConfiguration
//-----------------------------------------------------------------------------
INLINE void CATGeoCln::SetSoftwareConfiguration(CATSoftwareConfiguration* ipConfig)
{
  // ipConfig peut etre NULL
  if (ipConfig != _pConfig)
  {
    if (_pConfig)
      _pConfig->Release();

    _pConfig = ipConfig;

    if (_pConfig)
      _pConfig->AddRef();
  }
}

//-----------------------------------------------------------------------------
// SetStatus
//-----------------------------------------------------------------------------
INLINE void CATGeoCln::SetStatus(CATGeoCln::CATGeoClnStatus iStatus)
{
  _Status = iStatus;
}

//-----------------------------------------------------------------------------
// GetStatus
//-----------------------------------------------------------------------------
INLINE CATGeoCln::CATGeoClnStatus CATGeoCln::GetStatus() const
{
  return _Status;
}

//-----------------------------------------------------------------------------
// GetSeverity
//-----------------------------------------------------------------------------
INLINE short CATGeoCln::GetSeverity() const
{
  return _Severity;
}

//-----------------------------------------------------------------------------
// SetCodeLevel
//-----------------------------------------------------------------------------
INLINE void CATGeoCln::SetCodeLevel(int iCodeLevel)
{
  _CodeLevel = iCodeLevel;
}

//-----------------------------------------------------------------------------
// IsFixable
//-----------------------------------------------------------------------------
INLINE CATBoolean CATGeoCln::IsFixable() const
{
  return _Fixable;
}

//-----------------------------------------------------------------------------
// IsVerbose
//-----------------------------------------------------------------------------
INLINE CATBoolean CATGeoCln::IsVerbose() const
{
  return _Verbose;
}

//-----------------------------------------------------------------------------
// SetFixIfKO
//-----------------------------------------------------------------------------
INLINE void CATGeoCln::SetFixIfKO(CATBoolean iFixIfKO)
{
  _FixIfKO = iFixIfKO;
}

//-----------------------------------------------------------------------------
// GetFixIfKO
//-----------------------------------------------------------------------------
INLINE CATBoolean CATGeoCln::GetFixIfKO() const
{
  return _FixIfKO;
}

//-----------------------------------------------------------------------------
// SetSeverity
//-----------------------------------------------------------------------------
INLINE void CATGeoCln::SetSeverity(short iSeverity)
{
  _Severity = iSeverity;
}

//-----------------------------------------------------------------------------
// GetCodeLevel
//-----------------------------------------------------------------------------
INLINE int CATGeoCln::GetCodeLevel() const
{
  return _CodeLevel;
}

//-----------------------------------------------------------------------------
// SetCheckLoadedEntity
//-----------------------------------------------------------------------------
INLINE void CATGeoCln::SetCheckLoadedEntity(CATBoolean iCheckLoadedEntity)
{
 _CheckLoadedEntity = iCheckLoadedEntity;
}

//-----------------------------------------------------------------------------
// GetCheckLoadedEntity
//-----------------------------------------------------------------------------
INLINE CATBoolean CATGeoCln::GetCheckLoadedEntity() const
{
  return _CheckLoadedEntity;
}

//-----------------------------------------------------------------------------
// SetOnlyCheckOnBRepLink
//-----------------------------------------------------------------------------
INLINE void CATGeoCln::SetOnlyCheckOnBRepLink(CATBoolean iOnlyCheckOnBRepLink)
{
 _OnlyCheckOnBRepLink = iOnlyCheckOnBRepLink;
}

//-----------------------------------------------------------------------------
// GetOnlyCheckOnBRepLink
//-----------------------------------------------------------------------------
INLINE CATBoolean CATGeoCln::GetOnlyCheckOnBRepLink() const
{
  return _OnlyCheckOnBRepLink;
}

//-----------------------------------------------------------------------------
// SetFirstTimeErrorOnly
//-----------------------------------------------------------------------------
INLINE void CATGeoCln::SetFirstTimeErrorOnly(CATBoolean iFirstTimeErrorOnly)
{
  _FirstTimeErrorOnly = iFirstTimeErrorOnly;
}

//-----------------------------------------------------------------------------
// GetFirstTimeErrorOnly
//-----------------------------------------------------------------------------
INLINE CATBoolean CATGeoCln::GetFirstTimeErrorOnly() const
{
  return _FirstTimeErrorOnly;
}

//-----------------------------------------------------------------------------
// SetCheckParameter
//-----------------------------------------------------------------------------
INLINE void CATGeoCln::SetCheckParameter(CATGeoClnCheckParameter* ipCheckParameter)
{
  // ipCheckParameter PEUT etre NULL
  _pCheckParameter = ipCheckParameter;
  
  if ((_pCheckParameter) && (_pCheckParameter->_pRuleID != _ID))
    _pCheckParameter = NULL;
}

//-----------------------------------------------------------------------------
// GetCheckParameter
//-----------------------------------------------------------------------------
INLINE CATGeoClnCheckParameter* CATGeoCln::GetCheckParameter()
{
  return _pCheckParameter;
}

//-----------------------------------------------------------------------------
// SetCheckTransacParamList
//-----------------------------------------------------------------------------
INLINE void CATGeoCln::SetCheckTransacParamList(CATLISTP(CATGeoClnCheckParameter) * ipCheckTransacParamList)
{
  // ipCheckTransacParamList PEUT etre NULL
  _pCheckTransacParamList = ipCheckTransacParamList;
}

//-----------------------------------------------------------------------------
// GetCheckTransacParamList - Result can be NULL
//-----------------------------------------------------------------------------
INLINE CATLISTP(CATGeoClnCheckParameter) * CATGeoCln::GetCheckTransacParamList()
{
  return _pCheckTransacParamList;
}

//-----------------------------------------------------------------------------
// SetMsgCatalogName
//-----------------------------------------------------------------------------
INLINE void CATGeoCln::SetMsgCatalogName(char* ipMsgCatalogName)
{
  _pMsgCatalogName = ipMsgCatalogName;
}

//-----------------------------------------------------------------------------
// SetpErrorDialogMsg
//-----------------------------------------------------------------------------
INLINE void CATGeoCln::SetpErrorDialogMsg(CATUnicodeString* ipErrorDialogMsg)
{
  _pErrorDialogMsg = ipErrorDialogMsg;
}

//-----------------------------------------------------------------------------
// SetpTraceStream
//-----------------------------------------------------------------------------
INLINE void CATGeoCln::SetpTraceStream(ostream* ipTraceStream)
{
  _pTraceStream = ipTraceStream;
}

INLINE void CATGeoCln::SetpCATCX_CHECKUP(CATCX_CHECKUP* iopCATCX_Report)
{
  _pCATCX_Report = iopCATCX_Report;
}

INLINE CATCX_CHECKUP* CATGeoCln::GetpCATCX_CHECKUP()
{
  return _pCATCX_Report;
}

//-----------------------------------------------------------------------------
// ResetExtendedCheckErrorMsg
//-----------------------------------------------------------------------------
INLINE void CATGeoCln::ResetExtendedCheckErrorMsg()
{
  if (_pExtendedCheckErrorMsg)
    _pExtendedCheckErrorMsg->Resize(0, 0x0000, 1);
}

//-----------------------------------------------------------------------------
// ResetExtendedCleanErrorMsg
//-----------------------------------------------------------------------------
INLINE void CATGeoCln::ResetExtendedCleanErrorMsg()
{
  if (_pExtendedCleanErrorMsg)
    _pExtendedCleanErrorMsg->Resize(0, 0x0000, 1);
}


//--------------------------------------------------------------------
// Macros pour Definition simple de check rules
//
// CATCGMCLEANER_RULE_GEOM_DECLARE_? doit etre utilisee pour les regles
// "geometriques" definies dans GeometricObjectsCGM/CATCGMGeoClnGeom.m
//
// CATCGMCLEANER_RULE_TOPO_DECLARE_? doit etre utilisee pour les regles
// "topologiques" definies dans NewTopologicalObjects/CATCGMGeoClnTopo.m
//--------------------------------------------------------------------

#define CATCGMCLEANER_RULE_CREATE_RULE_STR "CreateRule"


#define CATCGMCLEANER_RULE_CREATE_DECLARE( RuleName, ExportedBy )                         \
                                                                                          \
extern "C"                                                                                \
{                                                                                         \
ExportedBy CATGeoCln* RuleName##CreateRule(CATSoftwareConfiguration* ipConfig,            \
                                           CATICGMUnknown*           ipICGMFederator,     \
                                           CATCGMRuleDef*            ipCGMRuleDef,        \
                                           CATBoolean                iVerbose);           \
}


#define CATCGMCLEANER_RULE_CREATE_IMPLEMENT( RuleName )                         \
                                                                                \
CATGeoCln* RuleName##CreateRule(CATSoftwareConfiguration* ipConfig,             \
                                CATICGMUnknown* ipICGMFederator,                \
                                CATCGMRuleDef* ipCGMRuleDef,                    \
                                CATBoolean iVerbose)                            \
{                                                                               \
  return RuleName::CreateRule(ipConfig,                                         \
                              ipICGMFederator,                                  \
                              ipCGMRuleDef,                                     \
                              iVerbose);                                        \
};                                                                              \


#define CATCGMCLEANER_RULE_GEOM_DECLARE( RuleName )  CATCGMCLEANER_RULE_GEOM_DECLARE_BEGIN(RuleName) \
                                                     CATCGMCLEANER_RULE_GEOM_DECLARE_END()

#define CATCGMCLEANER_RULE_GEOM_DECLARE_BEGIN( RuleName )  CATCGMCLEANER_RULE_DECLARE_BEGIN(RuleName, ExportedByCATCGMGeoClnGeom)
#define CATCGMCLEANER_RULE_GEOM_DECLARE_END()              CATCGMCLEANER_RULE_DECLARE_END()

#define CATCGMCLEANER_RULE_TOPO_DECLARE( RuleName )  CATCGMCLEANER_RULE_TOPO_DECLARE_BEGIN(RuleName) \
                                                     CATCGMCLEANER_RULE_TOPO_DECLARE_END()

#define CATCGMCLEANER_RULE_TOPO_DECLARE_BEGIN( RuleName )  CATCGMCLEANER_RULE_DECLARE_BEGIN(RuleName, ExportedByCATCGMGeoClnTopo)
#define CATCGMCLEANER_RULE_TOPO_DECLARE_END()              CATCGMCLEANER_RULE_DECLARE_END()

#define CATCGMCLEANER_RULE_DECLARE( RuleName, ExportedBy ) CATCGMCLEANER_RULE_DECLARE_BEGIN( RuleName, ExportedBy ) \
                                                           CATCGMCLEANER_RULE_DECLARE_END()



#define CATCGMCLEANER_RULE_DECLARE_BEGIN( RuleName, ExportedBy )                          \
                                                                                          \
CATCGMCLEANER_RULE_CREATE_DECLARE( RuleName, ExportedBy )                                 \
                                                                                          \
class ExportedBy RuleName : public CATGeoCln                                              \
{                                                                                         \
public:                                                                                   \
  RuleName(CATSoftwareConfiguration* ipConfig,                                            \
           CATICGMUnknown*           ipICGMFederator,                                     \
           CATCGMRuleDef*            ipCGMRuleDef,                                        \
           CATBoolean                iVerbose);                                           \
                                                                                          \
  ~RuleName();                                                                            \
  CATCGMNewClassArrayDeclare;                                                             \
                                                                                          \
  int CheckCGMEntity();                                                                   \
  int CleanCGMEntity();                                                                   \
                                                                                          \
  static CATGeoCln* CreateRule(CATSoftwareConfiguration* ipConfig,                        \
                               CATICGMUnknown*           ipICGMFederator,                 \
                               CATCGMRuleDef*            ipCGMRuleDef,                    \
                               CATBoolean                iVerbose);                     



#define CATCGMCLEANER_RULE_DECLARE_END()  };



//--------------------------------------------------------------------
// Macro pour Implementation simple de check rules
//
// Si vous desirez implementer une classe avec du traitement
// additionnel dans le constructeur/destructeur ou la methode
// CreateRule(...), n'utilisez pas cette macro.
//
// Vous DEVEZ implementer explicitement les methodes
//
//     int RuleName::CheckCGMEntity() et
//     int RuleName::CleanCGMEntity()
//--------------------------------------------------------------------
#define CATCGMCLEANER_RULE_IMPLEMENT( RuleName )                                \
                                                                                \
CATCGMCLEANER_RULE_CREATE_IMPLEMENT( RuleName )                                 \
                                                                                \
RuleName::RuleName(CATSoftwareConfiguration* ipConfig,                          \
                   CATICGMUnknown*           ipICGMFederator,                   \
                   CATCGMRuleDef*            ipCGMRuleDef,                      \
                   CATBoolean                iVerbose)                          \
: CATGeoCln(ipConfig,                                                           \
            ipICGMFederator,                                                    \
            ipCGMRuleDef,                                                       \
            iVerbose)                                                           \
{                                                                               \
}                                                                               \
                                                                                \
RuleName::~RuleName()                                                           \
{                                                                               \
}                                                                               \
                                                                                \
CATGeoCln* RuleName::CreateRule(CATSoftwareConfiguration* ipConfig,             \
                                CATICGMUnknown*           ipICGMFederator,      \
                                CATCGMRuleDef*            ipCGMRuleDef,         \
                                CATBoolean                iVerbose)             \
{                                                                               \
  CATGeoCln* pResult = new RuleName(ipConfig,                                   \
                                    ipICGMFederator,                            \
                                    ipCGMRuleDef,                               \
                                    iVerbose);                                  \
                                                                                \
  if (pResult == NULL)                                                          \
  {                                                                             \
    CATCGMNoMoreMemory(sizeof(RuleName));                                       \
    CATThrowForNullPointerReturnValue(NULL);                                    \
  }                                                                             \
                                                                                \
  return pResult;                                                               \
}                                                                               \
                                                                                \
CATCGMNewClassArray(RuleName, 10, catcgmPoolTEMP)                               \


//
// Some check and clean utility functions
//
class CATCurve;

ExportedByGeometricObjects CATBoolean IsCurveALineType(const CATCurve* ipCurveToCheck,
                                                       const CATBoolean ibCheckSupportType = TRUE);

#endif
