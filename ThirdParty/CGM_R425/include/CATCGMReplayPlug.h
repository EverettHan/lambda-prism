//  #define CATCGMReplayPlug_H // pour shunt en attendant finalisation
#ifndef CATCGMReplayPlug_H
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES 2020
//
//=============================================================================
//
// Plug for CGMReplay filtering
//(Plug pour prise de controle sur l'execution des CGMReplays)
//
// Gives a programming callback for special handling of
// - CheckInput
// - Run
// - CheckOutput
// - ValidateOutput
//
// (le but est de faire des choses plus fines que ce que permettent les listes
//  ListValidateOutputKO, ...)
//
//=============================================================================
// Usage notes:
// - define a class inheriting from CATCGMReplayPlug
// - define a dynamic load function of type CATLoadCATCGMReplayPlug
//   creating an instance of this child class
// - declare name and sharedlib of this function in your test shell
//   set CGMTest_CATCGMReplayPlug
//   set CGMTest_CATCGMReplayPlugSharedLib
//=============================================================================
//
// prise de controle sous
// CATCGMOperator::CATCheckDiagnostic CATExtCGMReplay::CheckOutputOperator   (CATCGMOperator * iOperator,
//                                                                            CATCGMOutput   & os       )
// (entre CGMReplayScenario::CheckOutput et le CheckOutput de l'operateur)
// ainsi que
// CATCGMOperator::CATCheckDiagnostic CATExtCGMReplay::CheckInputOperator    (CATCGMOperator * iOperator,
//                                                                            CATCGMOutput   & os       )
// CATBoolean                         CATExtCGMReplay::ValidateOutputOperator(CATCGMOperator * iOperator,
//                                                                            CATCGMStream   & ioStream ,
//                                                                            CATCGMOutput   & os       ,
//                                                                            int              VersionNumber)
//=============================================================================
// 15/04/20 NLD Création avec
//              - classe CATCGMReplayPlug
//                - GetCurrentScenario
//                - CheckOutputOperator
//                - ValidateOutputOperator
//              - type CATLoadCATCGMReplayPlug
//              - méthode GetCATCGMReplayPlug
// 16/04/20 NLD Ajout RunOperator()
//=============================================================================
#define CATCGMReplayPlug_H
#define CATCGMReplayPlug_Active

#include "CATIACGMLevel.h"

#include "CATGeometricObjects.h"
#include "CATMathInline.h"
#include "CATCGMOperator.h"
#include "CATExtCGMReplay.h"
#include "CATMathODT.h"

//#include "IUnknown.h"

class ExportedByCATGeometricObjects CATCGMReplayPlug // : public CATCGMVirtual
  {
   //CATCGMVirtualDeclareClass(CATCGMReplayPlug);
   public:
   // OperatorName
   // ScenarioName : on peut utiliser plutot CATMathODT::GetCurrentScenario
   //                de manière à ne pas alourdir les initialisations faites par CGMReplayScenario::Exec
   CATExtCGMReplay *_CGMReplay;
   CATCGMReplayPlug()
   {
      _CGMReplay = NULL;
   }
   INLINE static const char *GetCurrentScenario(size_t *pLgrScenario = NULL)
   {
      return CATMathODT::GetCurrentScenario();
   }
           void                               SetCGMReplay          (CATExtCGMReplay* iCGMReplay)
   {
      _CGMReplay = iCGMReplay;
   }

   // to implement only if necessary in child class
   virtual CATCGMOperator::CATCheckDiagnostic CheckInputOperator    (CATCGMOperator * iOperator,
                                                                     CATCGMOutput   & os       );

   // to implement only if necessary in child class
   virtual int                                RunOperator           (CATCGMOperator * iOperator,
                                                                     CATCGMOutput   & os       );

   // to implement only if necessary in child class
   virtual CATCGMOperator::CATCheckDiagnostic CheckOutputOperator   (CATCGMOperator * iOperator,
                                                                     CATCGMOutput   & os       );

   // to implement only if necessary in child class
   virtual CATBoolean                         ValidateOutputOperator(CATCGMOperator * iOperator,
                                                                     CATCGMStream   & ioStream ,
                                                                     CATCGMOutput   & os       ,
                                                                     int              VersionNumber = 1);

  } ;

//-----------------------------------------------------------------------------
class CATCGMReplayPlugDefault : public CATCGMReplayPlug
  {
   public:
   CATCGMReplayPlugDefault()
   : CATCGMReplayPlug()
     {
     }

   CATCGMOperator::CATCheckDiagnostic CheckInputOperator    (CATCGMOperator * iOperator,
                                                             CATCGMOutput   & os       );

   int                                RunOperator           (CATCGMOperator * iOperator,
                                                             CATCGMOutput   & os       );

   CATCGMOperator::CATCheckDiagnostic CheckOutputOperator   (CATCGMOperator * iOperator,
                                                             CATCGMOutput   & os       );

   CATBoolean                         ValidateOutputOperator(CATCGMOperator * iOperator,
                                                             CATCGMStream   & ioStream ,
                                                             CATCGMOutput   & os       ,
                                                             int              VersionNumber = 1);

 
  };


//-----------------------------------------------------------------------------
// Creation du plug selon declaratifs CGMTest_CATCGMReplayPlug et CGMTest_CATCGMReplayPlugSharedLib
//-----------------------------------------------------------------------------
extern "C" ExportedByCATGeometricObjects CATCGMReplayPlug* GetCATCGMReplayPlugDefault();
extern "C" ExportedByCATGeometricObjects CATCGMReplayPlug* GetCATCGMReplayPlug();


//-----------------------------------------------------------------------------
// N.B distinction Windows comme pour CATCGMOperator
//-----------------------------------------------------------------------------
#ifdef  _WINDOWS_SOURCE
extern "C"  { typedef __declspec(dllexport) CATCGMReplayPlug * CATLoadCATCGMReplayPlug(); }
#else
extern "C"  { typedef                       CATCGMReplayPlug * CATLoadCATCGMReplayPlug(); }
#endif

#endif

