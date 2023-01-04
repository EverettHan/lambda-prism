#ifndef CATGMBaseInfra_H
#define CATGMBaseInfra_H

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : LAP
//
// DESCRIPTION  : Class for manage a sequence of TopOperator
//                in order to create BRep Modeling Operator
//
//=============================================================================
// Creation QF2 April 2018
//
//=============================================================================
#include "CATCGMVirtual.h"
#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATMathInline.h"
#include "CATSysBoolean.h"
#include "ListPOfCATCell.h"
#include "CATUnicodeString.h"
#include "CATTopOpInError.h"
#include <memory>

// +++ Predeclaration +++
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATlsoContext;
class CATBody;
class CATTopOperator;
class CATExtTopOperator;
class CATPGMDRepBehavior;
class CATCGMDiagnosis;
class CATLISTP(CATCGMDiagnosis);
class CATError;
class CATPersistentCellInfra;
class CATGMLiveInfra;
class CATlsoPersistentContext;
class CATlsoDebugGraph;

// ou CATlsoInfra (a voir)
class ExportedByPersistentCell CATGMBaseInfra : public CATCGMVirtual
{
  // Access to BaseInfra
  friend class CATAdvancedExtTopOperator;

public :  

  enum LastErrorLevel {
    LastErrorLevel_Undefined = 0,
    LastErrorLevel_Low       = 1,
    LastErrorLevel_Normal    = 2,
    LastErrorLevel_High      = 3,
    LastErrorLevel_Critical  = 4,
    LastErrorLevel_Fatal     = 5
  };


  // Constructor
  CATGMBaseInfra(CATGeoFactory & iGeoFactory, CATSoftwareConfiguration* iConfig, const CATUnicodeString *iMainErrorMsgId=NULL);
  // Destructor
  virtual ~CATGMBaseInfra();
  // surcharge du new et du delete
  CATCGMNewClassArrayDeclare; 

  /*----------------------------------------------------------------------------------------------
   * Getters  
  /*----------------------------------------------------------------------------------------------*/
  CATGeoFactory & GetFactory(short iImpliciteFactory=1) const;
  INLINE CATSoftwareConfiguration * GetSoftwareConfiguration() const;
  INLINE CATBoolean GetLiveBodyAllowed() const;

  /*----------------------------------------------------------------------------------------------
   * Setters  
  /*----------------------------------------------------------------------------------------------*/
  INLINE void SetLiveBodyAllowed(CATBoolean iLiveBodyAllowed);


  // Common Public Methods 
  // ---------------------------------------------------------------------------------------------
  HRESULT RunTopOperator (CATTopOperator  * iTopOpToBeRun,    // for operator with result body
                          CATBody        *& oResultBody,
                          CATlsoContext   * iFatherContext,
                          CATBoolean        iLiveMode=FALSE,  // set TRUE to have liveResult
                          CATBoolean        iThrowIfError=FALSE);   

  HRESULT RunTopOperatorWithoutResult(CATTopOperator * iTopOpToBeRun,
                                      CATlsoContext  * iFatherContext,
                                      CATBoolean       iThrowIfError=FALSE);  // for operator without result body : like selectface

  static HRESULT RunTopOperatorWithoutCreatePersistentBodyStatic(CATTopOperator           * iTopOpToBeRun, // for operator with result body
                                                                  CATBody                *& oResultBody,
                                                                  CATlsoContext           * iFatherContext,
                                                                  const CATBoolean          iThrowIfError=FALSE,
                                                                  const CATBoolean          iResultBodyExpected=TRUE);

  void TransferLiveBodyAccessRights(CATTopOperator * iSonOpe);
  
  /* -----------------------------------------------------------------------------------------------------------
   *   ERRORS Management
   * -----------------------------------------------------------------------------------------------------------
   *   Public methods to set up current operator error.
   *    -> Each error set up this way will be encapsulated as Diagnosis in the Main Error ( 'TopOpInDirectEditLiveOpe_ERR_8420' by default).
   *   
   *   Example : 
   *       persistentInfra.SetLastError("TopOpInBlala_ERR_##", ImpactedCellList);
   *       CATlsoOperatorError(this);
   *
   *  Errors file : TopologicalOperators\TopologicalOperatorsRscCNext.m\src\CNext\resources\msgcatalog\CATTopologicalOperators.CATNls
   * ------------------------------------------------------------------------------------------------------------
   
   * To change it, use SetMainErrorMsgId("") or define it in the PersistentCellInfra constructor.
  /* By default, the MainErrorMsgId = "TopOpInDirectEditLiveOpe_ERR_8420" */
  void        SetMainErrorMsgId(const CATUnicodeString &iErrorMsgID);
  HRESULT     SetLastError(const char * iErrorMessageID, const ListPOfCATCell *ipCellLocationList=NULL, const char * iMessageCatalog=TopOpInFile, LastErrorLevel iCriticality=LastErrorLevel_High);
  HRESULT     SetLastError(const CATError *iError, const ListPOfCATCell *ipCellLocationList=NULL, LastErrorLevel iCriticality=LastErrorLevel_High);
#if !defined _AIX_SOURCE
  HRESULT     SetLastError(const std::unique_ptr<CATError> & iError, const ListPOfCATCell *ipCellLocationList=NULL, LastErrorLevel iCriticality=LastErrorLevel_High);
#endif

  CATBoolean  LastErrorContains(const char * iErrorMessageID);

  /* Create a copy of last Error. Free memory after use.*/
  CATTopOpInError * GetCopyOfLastError() const;

  // Error Public Utilities
  // --------------------------------------------------------------------
  static HRESULT SetLocationToError(CATSoftwareConfiguration    * iConfig, 
                                    CATGeoFactory               & iFactory,
                                    CATCGMDiagnosis            *& ioDiagnosisError, 
                                    const ListPOfCATCell        & iLocationCellList,
                                    const CATListOfInt          * iLocationOrientationsList=NULL,
                                    const ListPOfCATCell        * iContextCellList=NULL);

  /*------------------------------------------------------------------------------------------------------------
   *  Warnings Management
   *  Official Methods 
  /*------------------------------------------------------------------------------------------------------------*/  
  void    SetMainWarningMsgId(const CATUnicodeString &iWarningMsgID);
  HRESULT SetLastWarning(const CATExtTopOperator *iOpe, /*const*/ CATError * iWarning, ListPOfCATCell *ipCellLocationList=NULL, CATBoolean iComesFromError=FALSE);
  HRESULT SetLastWarning(const CATExtTopOperator *iOpe, const char *iErrorMsgID, ListPOfCATCell *ipCellLocationList=NULL, const char *iMsgCatalog=TopOpInFile);
   

  //--------------------------------------------------------------------------------------------------------------
  // DRepBehavior
  //--------------------------------------------------------------------------------------------------------------
  CATPGMDRepBehavior * GetDRepBehavior() const;
  void  SetDRepBehavior(CATPGMDRepBehavior * iDRepBehavior);
  void  TransfertDRepBehavior(CATTopOperator * iOpe) const;

  // GetAs...()
  // ----------------------------------------------------------------------------
  virtual CATPersistentCellInfra * GetAsPersistentInfra() const;
  virtual CATGMLiveInfra         * GetAsGMLiveInfra()     const;

  //VB7 Debug Graph W19 2019
  // ----------------------------------------------------------------------------
  CATlsoDebugGraph * GetDebugGraph();

protected :
  
  const CATUnicodeString & GetMainErrorMsgId() const;
  const CATUnicodeString & GetMainWarningMsgId() const;
  CATTopOpInError        * GetLastError() const;
  CATGMBaseInfra::LastErrorLevel  GetLastErrorLevel() const;

  // Internal Use only.
  void ForceLastError(CATTopOpInError * iError, const ListPOfCATCell *ipCellLocationList=NULL, LastErrorLevel iCriticality=LastErrorLevel_High);
  // Internal Use only.
  void RemoveLastError();

  // -----------------------------------------------------
  // Protected Warning management
  // -----------------------------------------------------
  CATTopOpInError * GetLastWarning() const;
  void GetWarningList(CATLISTP(CATCGMDiagnosis) & oWarningList) const;
  void ForceLastWarning(const CATExtTopOperator *iOperator, CATCGMInputError *& ioWarning, ListPOfCATCell *ipCellLocationList=NULL, CATBoolean iComesFromError=FALSE);
  void AppendPermanentWarningList(const CATLISTP(CATCGMDiagnosis) &iWarningList);
  void ReleaseLastWarning(/*short iKeepPermanent=0*/);

private :
  // Private LastWarning Management
  // ----------------------------------------------------- 
  void ReleasePermanentWarning();
  INLINE const CATLISTP(CATCGMDiagnosis) & GetPermanentWarningList() const;

  //------------------------------------------------------------------------------
  // Forbidden (Declared but not Defined) : Copy constructor & assignment operator
  //------------------------------------------------------------------------------
  CATGMBaseInfra (const CATGMBaseInfra &);            // Not Implemented
  CATGMBaseInfra & operator=(const CATGMBaseInfra &); // Not Implemented

protected :

//--------------------------------------------------------------------------------------------------------------
// Internal Data
//--------------------------------------------------------------------------------------------------------------

  CATGeoFactory   	         & _GeoFactory;
  CATSoftwareConfiguration   * _Config;

  // ListPOfCATBody          _InputBodies; // a voir
  CATBoolean                _LiveBodyAllowed;  
  CATTopOpInError         * _LastError;
  CATTopOpInError         * _LastWarning;   
  CATLISTP(CATCGMDiagnosis) _PermanentWarningList;
  LastErrorLevel            _LastErrorCriticality; // moyen cette archi...
  CATUnicodeString          _MainErrorMsgId;
  CATUnicodeString          _MainWarningMsgId;
  CATPGMDRepBehavior      * _DRepBehavior;

  //VB7 Debug W19 2019
  CATlsoDebugGraph        * _DebugGraph;

};

// --------------------------------------------------------------------------------------
// GetSoftwareConfiguration
// --------------------------------------------------------------------------------------
INLINE CATSoftwareConfiguration * CATGMBaseInfra::GetSoftwareConfiguration() const {
  return _Config; }

// --------------------------------------------------------------------------------------
// SetLiveBodyAllowed
// --------------------------------------------------------------------------------------
INLINE void CATGMBaseInfra::SetLiveBodyAllowed(CATBoolean iLiveBodyAllowed) {
  _LiveBodyAllowed = iLiveBodyAllowed; }

// --------------------------------------------------------------------------------------
// GetLiveBodyAllowed
// --------------------------------------------------------------------------------------
INLINE CATBoolean CATGMBaseInfra::GetLiveBodyAllowed() const {
  return _LiveBodyAllowed; }


#endif

