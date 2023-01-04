// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation EDS-ICE-XDT  29/11/2000
// 24/07/2015  G5S  CGMReplay functionality inserted.
//
// Interface de l'operateur de check (classe de base).
//=============================================================================

#ifndef __CATChecker_h__
#define __CATChecker_h__

#include "CheckOperators.h"
#include "CATTopOperator.h"
#include "CATListPOfCATCheckDiagnoses.h"
#include "CATThrowForNullPointer.h"

class CATCXChecker;
class CATCheckDiagnosisList;


class ExportedByCheckOperators CATChecker: public CATTopOperator
{
   CATCGMVirtualDeclareClass(CATChecker);
public: // Methodes a usage externe

   //============================
   // Constucteur et destructeurs
   //============================

   CATChecker(CATGeoFactory * iFactory,
      CATTopData    * iData,
      CATCXChecker  * iExtensible);

   virtual ~CATChecker();


   //======================================
   // Methodes specifiques a CATTopOperator
   //======================================

   virtual int       Run();
   virtual int       RunOperator();
   virtual CATBody * GetResult();

   //====================================
   // Acces aux parametres de l'operateur
   //====================================

   CATBody *      GetBodyToCheck() const;
   CATBoolean     GetFullCheckMode() const;                                      
   CATBoolean     GetDiagnosisMode() const;
   double         GetTolerance() const;

   //===========================================
   // Methodes de parametrisation de l'operateur
   //===========================================

   void SetFullCheckMode(CATBoolean iFullCheckMode);
   void SetDiagnosisMode(CATBoolean iDiagnosisMode);
   void SetStabilizeConfusion(CATBoolean iStabilize);

   //==============================================
   // Methodes d'acces aux resultats de l'operateur
   //==============================================

   CATBoolean                    GetLogicalResult() const;

   CATLONG32                     GetNbDiagnoses() const;
   const CATCheckDiagnosis     * GetDiagnosis(CATLONG32 iDiagnosisIndex) const;

   CATCheckDiagnosisList       * GetCheckDiagnosisList() const;     

   virtual void                  Dump(ostream& iOutput) const;

   /** @nodoc  */
  inline CATCXChecker          * GetCheckerExtensible() const;

protected:

     /** @nodoc @nocgmitf */
    virtual const CATString * GetOperatorId();

   /** @nodoc @nocgmitf */
   virtual CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);

   /** @nodoc @nocgmitf */
   virtual void              WriteInput(CATCGMStream  & ioStream);

   /** @nodoc @nocgmitf */
   virtual void              RequireDefinitionOfInputAndOutputObjects();

   /** @nodoc @nocgmitf */
   virtual void              Dump(CATCGMOutput& os);

   /** @nodoc @nocgmitf */
   virtual void              WriteOutput(CATCGMStream &ioStream);

   /** @nodoc @nocgmitf */
   virtual CATBoolean        ValidateOutput(CATCGMStream &Str, CATCGMOutput &os, int VersionNumber = 1);

   /** @nodoc @nocgmitf */
   virtual void              DumpOutput(CATCGMOutput& os);

   /** @nodoc @nocgmitf */
   virtual void              DumpOutput(CATCGMStream &Str, CATCGMOutput &os, int VersionNumber=1);

protected: // Donnees membres

   // CATCXChecker * _Implementation;
};

/** @nodoc  */
inline CATCXChecker * CATChecker::GetCheckerExtensible() const
{
   if (!GetExtensible()) CATThrowForNullPointerReturnValue(NULL);
   return (CATCXChecker*) GetExtensible();   
}

#endif
