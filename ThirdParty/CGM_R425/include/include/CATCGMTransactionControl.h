#ifndef CATCGMTransactionControl_H
#define CATCGMTransactionControl_H
//---------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2002
//---------------------------------------------------
#include "ExportedByGeometricObjects.h"
#include "CATHashDicoOfCATCGMTransactionControl.h"
#include "CATCGMNewArray.h"
#include "CATBoolean.h"
#include "CATCGMTransactionControlStatus.h"
#include "CATMathInline.h"

class CATCGMOutput;
class CATSoftwareConfiguration;

//---------------------------------------------------
// Specification en attente de Controle sur ODT N
//---------------------------------------------------
class  ExportedByGeometricObjects CATCGMTransactionControl
{
public:
  
  //---------------------------------------------------------------------------------------------
  // En Contexte d'une transaction ODT N1 (CATCGMFactoryTransaction), 
  //  Obtention des contraintes du Scenario en cours d'execution
  //---------------------------------------------------------------------------------------------
  static CATBoolean IsScenarioUnderControl(CATCGMTransactionControl & ioExpected);
  
  //---------------------------------------------------------------------------------------------
  // En Contexte d'une transaction ODT N1 (CATCGMFactoryTransaction), 
  //  Obtention des contraintes du Scenario en cours d'execution
  //---------------------------------------------------------------------------------------------
  static void  EndScenarioControl(const CATCGMTransactionControl & iComputed, short i1After_2Error);

  //---------------------------------------------------------------------------------------------
  // Life Cycle ...
  //---------------------------------------------------------------------------------------------
  CATCGMTransactionControl();
  ~CATCGMTransactionControl();
  CATCGMTransactionControl(const CATCGMTransactionControl& iOneOf); 
  CATCGMTransactionControl& operator =(const CATCGMTransactionControl& iOneOf);

  CATCGMNewClassArrayDeclare;  
  
  INLINE const CATCGMTransactionControlStatus & Expected() const;
  CATBoolean HasExpectation() const;
  CATBoolean AddExpectation(const CATCGMTransactionControlStatus & iRefControl, CATBoolean iReplace);
  void       ResetExpectation();

  INLINE const CATCGMTransactionControlStatus & Computed() const;
  CATBoolean   AddComputed(const CATCGMTransactionControlStatus & iRefControl, CATBoolean iReplace);
  CATBoolean   HasComputed() const;
  
  INLINE void  GetExpected(CATCGMTransactionControlStatus &ioStatus) const;
  INLINE void  GetComputed(CATCGMTransactionControlStatus &ioStatus) const;
  

  void SetSoftwareConfiguration(CATSoftwareConfiguration* iConfig);
  INLINE CATSoftwareConfiguration* GetSoftwareConfiguration() const;
  
  CATBoolean   DetermineSuccess(CATCGMOutput &ioDump, short i1After_2Error) const;
  
  //---------------------------------------------------------------------------------------------
  // Gestion des controles systematiques
  //---------------------------------------------------------------------------------------------
  static CATBoolean HasDefaultExpectation(CATCGMTransactionControl       & ioDefControl);
  static void       SetDefaultExpectation(const CATCGMTransactionControl & iDefControl);

  //---------------------------------------------------------------------------------------------
  // Internal Use
  //---------------------------------------------------------------------------------------------
  static void CleanForExit();

private:

  //---------------------------------------------------------------------------------------------
  // Description des champs d'activation :
  //---------------------------------------------------------------------------------------------
  static void InitDico();

  CATCGMTransactionControlStatus   _Expected;
  CATCGMTransactionControlStatus   _Computed;
  CATSoftwareConfiguration        *_Config;


  static CATHDICO(CATCGMTransactionControl) *_AllScenarios;
  static CATCGMTransactionControl           *_DefaultControl;
  static CATBoolean                          _initDone;

  friend class CATCGMFactoryTransaction;
  friend class CATCXControl;
};

//------------------------------------------------------------------------
// Expected 
//-----------------------------------------------------------------------
INLINE const CATCGMTransactionControlStatus & CATCGMTransactionControl::Expected() const
{
  return _Expected;
}

//------------------------------------------------------------------------
// Computed 
//-----------------------------------------------------------------------
INLINE const CATCGMTransactionControlStatus & CATCGMTransactionControl::Computed() const
{
  return _Computed;
}

//------------------------------------------------------------------------
// GetExpected 
//-----------------------------------------------------------------------
INLINE void  CATCGMTransactionControl::GetExpected(CATCGMTransactionControlStatus &ioStatus) const
{
  memcpy( &ioStatus, &_Expected , sizeof(CATCGMTransactionControlStatus) );
}

//------------------------------------------------------------------------
// GetComputed 
//-----------------------------------------------------------------------
INLINE void  CATCGMTransactionControl::GetComputed(CATCGMTransactionControlStatus &ioStatus) const  
{
  memcpy( &ioStatus, &_Computed , sizeof(CATCGMTransactionControlStatus) );
}

//------------------------------------------------------------------------------
// GetSoftwareConfiguration
//------------------------------------------------------------------------------
INLINE CATSoftwareConfiguration* CATCGMTransactionControl::GetSoftwareConfiguration() const
{
  return _Config;
}

#endif
