#ifndef CATMathOperator_H
#define CATMathOperator_H
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2005
//=============================================================================
//
// Classe generique utilitaire definissant un operateur mathematique enregistrable via CATCGMReplay
// via CallBack vers framework GeometricObjects
//
//=============================================================================
//
// Usage notes:
//
//=============================================================================
// 22/07/09 NLD Creation
//              - classe CATMathOperator
//              - utilitaires de CallBack vers GeometricObjects:
//                SetCreateOrRemoveDebugAutomaticCATCGMOperatorsCallBacks()
//                CreateOrRemoveDebugAutomaticCATCGMOperatorsCallBacks()
//                DebugAutomaticLoadGeometricObjects()
//              - classe CATCGMOperatorsCallBacks avec
//                CreateCATCGMOperator()
//                RemoveCATCGMOperator()
//                RunCATCGMOperator()
// 23/07/09 NLD Pour gestion correcte du cycle de vie dans le cadre de l'unstream de CGMReplay:
//              - virtual ~CATMathOperator() (pour que le destructeur de classe derivee soit appele)
//              - la classe CATMathOperator est exportee (sinon existe dans frameworks clients)
//              - CreateCATCGMOperator() recoit un argument optionnel int iDeleteMathOperator
// 30/07/09 NLD Ajout de WriteOutput() et ValidateOutput()
//              Ajout de GetReplayRecordFilter() dans CATCGMOperatorsCallBacks
// 06/08/09 NLD Ajout de Dump()
//=============================================================================
#include <CATMathStream.h>
#include <YN000FUN.h>
#include <CATCGMOutput.h>
class CATCGMOperator;
/**
   * @nodoc   internal use. 
   * @nocgmitf
   */
class ExportedByYN000FUN CATMathOperator
  {
   public:
   CATMathOperator()
     {
     }
   virtual ~CATMathOperator()
     {
     }
   virtual int RunOperator() ;
   virtual void WriteInput(CATMathStream&  ioStream);
   virtual void RequireDefinitionOfInputAndOutputObjects();
   virtual void Dump(CATCGMOutput &os);
   virtual void DumpOutput(CATCGMOutput &os);
   virtual int IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
   virtual const CATString * GetOperatorId();
   virtual void WriteOutput(CATMathStream & Str);
   virtual CATBoolean ValidateOutput(CATMathStream& Str, CATCGMOutput & os, int VersionNumber);
  } ;

/**
   * @nodoc   internal use. 
   * @nocgmitf
   */
class CATCGMOperatorsCallBacks
{
 public:
 
   CATCGMOperatorsCallBacks()
   {
   }

   ~CATCGMOperatorsCallBacks()
   {
   }
 

   // Creation d'un operateur CGM (de type CATCGMOperator)
   // permettant d'executer et enregistrer un operateur mathematique
   // l'operateur mathematique sera detruit a la destruction de l'operateur CGM
   // si cela est demande en mettant iDeleteMathOperator a 1
   virtual CATCGMOperator * CreateCATCGMOperator(CATMathOperator* iMathOperator, int iDeleteMathOperator=0) =0;

   // Destruction d'un operateur CGM
   virtual void RemoveCATCGMOperator(CATCGMOperator* iOperator) = 0;

   // Execution d'un operateur CGM
   virtual int RunCATCGMOperator(CATCGMOperator* iOperator) = 0;

   // Rend le filtre de replay/record en cours (CATCGMReplayRecord::GetKeepName())
   virtual const char* GetReplayRecordFilter() = 0;
} ;

//-----------------------------------------------------------------------------
// Definition de la methode statique de creation/destruction automatique de callback topologique
// (creation si pointeur nul en entree, destruction si pointeur non nul)
//-----------------------------------------------------------------------------
/**
   * @nodoc   internal use. 
   * @nocgmitf
   */
extern "C" ExportedByYN000FUN void SetCreateOrRemoveDebugAutomaticCATCGMOperatorsCallBacks(void (*iDebugAutomaticCATCGMOperatorsCallBacks)(CATCGMOperatorsCallBacks*&)) ;

//-----------------------------------------------------------------------------
// Creation ou destruction de callback topologique (si on dispose de l'adresse d'une methode
// adequate fournie au prealable par la topologie)
//-----------------------------------------------------------------------------
/**
   * @nodoc   internal use. 
   * @nocgmitf
   */
extern "C" ExportedByYN000FUN void CreateOrRemoveDebugAutomaticCATCGMOperatorsCallBacks(CATCGMOperatorsCallBacks*& ioCallBacks) ;

//-----------------------------------------------------------------------------
// Chargement dynamique de GeometricObjects via CATGeometricObjectsDummy()
// rend 1 si chargement OK, 0 sinon
//-----------------------------------------------------------------------------
// pas necessaire de l'exporter, mais bon, si quelqu'un en a besoin
/**
   * @nodoc   internal use. 
   * @nocgmitf
   */
extern "C" ExportedByYN000FUN int DebugAutomaticLoadGeometricObjects() ;

#endif
