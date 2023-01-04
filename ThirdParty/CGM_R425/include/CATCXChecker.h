// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation EDS-ICE-XDT  29/11/2000
//
// Operateur de check (classe de base pour les implementations).
//=============================================================================
//    03/2010  OID  Chgt archi: CATCXChecker hérite de CATExtTopOperator           
// 24/07/2015  G5S  CGMReplay functionality inserted.
//=============================================================================
#ifndef __CATCXChecker_h__
#define __CATCXChecker_h__

#include "CATExtTopOperator.h"

#include "CheckOperators.h"

#include "CATSubdBoolean.h"
#include "CATSubdCheckParameters.h"
#include "CATListPOfCATCheckDiagnoses.h"

#include "CATListOfInt.h"
#include "ListPOfCATListOfInt.h"

class CATTopOperator;
class CATGeoFactory;
class CATBody;
class CATCheckDiagnosis;
class CATCheckDiagnosisList;


class ExportedByCheckOperators CATCXChecker  : public CATExtTopOperator
{
   friend class CATChecker;

   // CATCGMVirtualDeclareClass(CATChecker);
public: // Methodes a usage externe

   //============================
   // Constucteur et destructeurs
   //============================

   //-------------------------------------------------------------------------------------------------------
   // Surcharge du new/delete
   //-------------------------------------------------------------------------------------------------------
   CATCGMNewClassArrayDeclare;

   CATCXChecker(CATGeoFactory * iFactory,
                CATBody       * iBodyToCheck);

   virtual ~CATCXChecker();

   virtual int         Run();    
   virtual void        Dump(ostream& iOutput);
   virtual CATCXBody * GetTopologicalResult();

   void SetTopOperator(CATTopOperator * iOperator) { this -> SetOperator(iOperator); }

   //====================================
   // Acces aux parametres de l'operateur
   //====================================

   CATBody *      GetBodyToCheck()   const;
   CATSubdBoolean GetFullCheckMode() const;                                      
   CATSubdBoolean GetDiagnosisMode() const;

   //===========================================
   // Methodes de parametrisation de l'operateur
   //===========================================

   void SetFullCheckMode(CATSubdBoolean iFullCheckMode);
   void SetDiagnosisMode(CATSubdBoolean iDiagnosisMode);
   void SetStabilizeConfusion(CATSubdBoolean iStabilize);

   //==============================================
   // Methodes d'acces aux resultats de l'operateur
   //==============================================

   CATSubdBoolean                GetLogicalResult() const;

   CATLONG32                     GetNbDiagnoses() const;
   const CATCheckDiagnosis     * GetDiagnosis(CATLONG32 iDiagnosisIndex) const;

   CATCheckDiagnosisList       * GetCheckDiagnosisList() const;      

   static void LoadInOutput(CATCGMStream            & ioStream,
                            CATGeoFactory*          & iFactory,
                            CATTopData              & ioTopData,
                            CATBodyFreezeMode       & iFreezeMode,
                            CATSubdBoolean          & ioDiagnosisMode,
                            CATSubdBoolean          & ioStabilizeConfusion,
                            CATSubdBoolean          & ioFullCheckMode,
                            CATLISTP(CATICGMObject) & ioInputCopy,
                            CATLISTP(CATICGMObject) & ioInputNoCopy,
                            CATBody*                & ioOutputBody,
                            CATCGMODTScaleManager   * iODTScaleManager);

protected: // Methodes a usage interne

   double                        GetTolerance() const;
   void                          SetTolerance(double iTolerance);

   // CATTopOperator              * GetTopOperator() const { return this->GetOperator(); }

   CATSubdCheckParameters      * GetCheckParameters() const;

   CATSubdBoolean                IsRunDone() const { return _IsRunDone; }

   CATLISTP(CATCheckDiagnosis) * GetDiagnosisList() const;

   CATCXBody                   * GetResultBody() const { return _CheckParameters.GetResultBody(); }

   void                          SetLogicalResult(CATSubdBoolean iResult) { _LogicalResult = iResult; }

   CATSubdBoolean                IsFullCheckMode() const { return _CheckParameters.GetFullCheckMode(); }

   CATSubdBoolean                GetReferenceResult() const { return _ReferenceResult; };
   void                          SetReferenceResult(CATSubdBoolean iRefResult){ _ReferenceResult = iRefResult; };

   // CGMReplay
   virtual CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
   virtual void WriteInput(CATCGMStream  & ioStream);
   virtual void RequireDefinitionOfInputAndOutputObjects();
   virtual void Dump(CATCGMOutput& os);
   
   virtual void        WriteOutput(CATCGMStream &ioStream);
   virtual CATBoolean  ReadReferenceOutput(CATCGMStream & Str);
   virtual CATBoolean  ValidateOutput(CATCGMStream &Str, CATCGMOutput &os, int VersionNumber=1);
   virtual void        DumpOutput(CATCGMOutput& os);
   virtual void        DumpOutput(CATCGMStream &Str, CATCGMOutput &os, int VersionNumber=1);

   CATBoolean CheckSelfIntersectionShell();
   CATBoolean CheckSelfIntersectionWire();
   virtual CATBoolean GetEffectiveCheckCells(CATLISTP(CATCell) &olsCheckCells, const unsigned short iCellDimension);
   CATBody * GetBodyToCheckItf();

protected: // Donnees membres

   virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);

   // CATTopOperator         * _TopOperator;
   virtual const CATString * GetOperatorId();
   CATSubdCheckParameters   _CheckParameters;

   CATSubdBoolean           _DiagnosisMode;         // Indique si un diagnostic doit etre genere correspondant
   // a chacune des intersections invalides

   CATCXBody              * _ResultBody;            // Body passe a _CheckParameters
   CATCXBody              * _RefResultBody;         // Reference result body for CGMReplay.

   CATLISTP(CATCheckDiagnosis) _RefDiagnosisList;   // Reference diagnosis list for CGMReplay.
   ListPOfCATListOfInt         _RefDiagnosisStreamVersionListList; // Versions of stream for each reference diagnosis list.

   CATSubdBoolean           _ResultIsReturned;      // Indique si le body resultat a ete retourne via GetResult()

   CATCXBody              * _BodyToCheck;           // Body contenant les elements topologiques sur lesquels
   // portent le check

   CATSubdBoolean           _LogicalResult;         // Resultat logique global du check

   CATSubdBoolean           _ReferenceResult;       // Resultat logique reference pour CGMReplay

   CATSubdBoolean           _IsRunDone;             // Indique si la methode run a ete executee

   CATSubdBoolean           _StabilizeConfusion;    // Stabilisation des zones de confusions dans le PCrv/PCrv

};

void DumpCATSubdBoolean (CATString & iVarName, CATSubdBoolean iVar, CATCGMOutput & os);

#endif
