// COPYRIGHT DASSAULT SYSTEMES 2010
//=============================================================================
// Creation OID  10/05/2010
//
// Interface de l'operateur de check d'autointersection de body.
//=============================================================================

#ifndef __CATCheckerBody_h__
#define __CATCheckerBody_h__

#include "CheckOperators.h"
#include "CATChecker.h"
#include "ListPOfCATDomain.h"
// #include "CATListPOfCATCheckDiagnoses.h"
#include "CATThrowForNullPointer.h"
#include "CATCellHashTable.h"

class CATCheckerBodyImpl;
class CATCGMVoBOptionControl;
// class CATCheckDiagnosisList;


class ExportedByCheckOperators CATCheckerBody: public CATChecker
{
   CATCGMVirtualDeclareClass(CATCheckerBody);
public: // Methodes a usage externe

   //============================
   // Constucteur et destructeurs
   //============================

   CATCheckerBody(CATGeoFactory    * iFactory,
                  CATTopData       * iData,
                  CATCheckerBodyImpl * iExtensible);

   virtual ~CATCheckerBody();


   //======================================
   // Methodes specifiques a CATTopOperator
   //======================================

   int       Run();
   int       RunOperator();
   CATBody * GetResult();

   //=======================================
   //  Set spéciffiques
   //=======================================

   //==============================================================================================
   //                                  Use Case: Static check.
   //==============================================================================================
   //   We know which cells have to be checked, but we don't have a previous valid body
   //   The cells setted up here and only these cells will be checked, against the other cells of the body
   void SetCellsToCheck(CATLISTP(CATCell) * iCellsToCheck);
   //==============================================================================================


   //==============================================================================================
   //                                  Use Case: Dynamic Check
   //==============================================================================================
   //   We have a previous body known as being valid
   //   We have an historical knowledge of which ancient cells are replaced by which new cells
   //   If the cells are totally new => iOldCells is an empty list.
   void SetPreviousValidBody(CATBody * iPreviousValidBody);
   void AddCorrespondenceOldCellsNewCells(CATLISTP(CATCell) * iOldCells, CATLISTP(CATCell) * iNewCells);
   //==============================================================================================

   //   An invariant SolidBlock:
   //    => it implies that the internal validity of these cells as well as the validity relatively to the other cells of the block is not checked
   void AddInvariantSolidBlock(CATLISTP(CATCell) * iNewBlock);
   //   To keep the knowledge of the  cells identified as being invalid.
   void SetKeepInvalidCells(CATBoolean iKeepInvalidCells);

   //   To continue ofter the first invalidity found.
   void SetExhaustiveCheck(CATBoolean iExhaustiveCheck);

   // VoB
   void SetVoBOptionControl(CATCGMVoBOptionControl* iVoBOptionControl);
   void SetVoBModifiedEdges(CATCellHashTable * iVoBModifiedEdges);

   //==============================================
   // Methodes d'acces aux resultats de l'operateur
   //==============================================
   CATBoolean            GetExhaustiveCheck() const;
   CATBoolean            GetKeepInvalidCells() const;
   void                  GetInvalidCells(CATLISTP(CATCell) & iInvalidCells);
   CATBody             * GetPreviousValidBody() const;
   int                   GetNbOfCorrespondence() const;
   int                   GetNbOfSolidBlocks() const;
   CATLISTP(CATCell) *   GetNewCellsToCheck(int i) const;
   CATLISTP(CATCell) *   GetCorrespondingPreviouslyValidCells(int i) const;
   void                  GetCorrespondenceOldCellsNewCells(CATLISTP(CATCell) & oOldCells, CATLISTP(CATCell) & oNewCells, int i);
   CATLISTP(CATCell) *   GetInvariantSolidBlock(int i) const;
   void                  GetInvalidIntersections(CATLISTP(CATCell) & ioInvalidIntersections);
   void                  GetInterioritiesIssues  (CATLISTP(CATDomain) & iInterioritiesIssues);
   void                  GetDisconnectionsIssues (CATLISTP(CATCell) & iDisconnectionsIssues);

//   virtual void                  Dump(ostream& iOutput) const;

   /** @nodoc  */
  inline CATCheckerBodyImpl      * GetCheckerBodyExtensible() const;

protected:
   /** @nodoc @nocgmitf */
    const CATString * GetOperatorId();

   /** @nodoc @nocgmitf */
   CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);

   /** @nodoc @nocgmitf */
   void              WriteInput(CATCGMStream  & ioStream);

   /** @nodoc @nocgmitf */
   void              RequireDefinitionOfInputAndOutputObjects();

   /** @nodoc @nocgmitf */
   void              Dump(CATCGMOutput& os);

   /** @nodoc @nocgmitf */
   void              WriteOutput(CATCGMStream &ioStream);

   /** @nodoc @nocgmitf */
   CATBoolean        ValidateOutput(CATCGMStream &Str, CATCGMOutput &os, int VersionNumber=1);

   /** @nodoc   dedicated to CATTopOperator/CATCGMreplay : internal use, do not overload */
	CATBoolean        ValidateTopOutput(CATTopCheckJournal* iEquivalent,CATCGMOutput& os);

   /** @nodoc @nocgmitf */
   CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);

   /** @nodoc @nocgmitf */
   void              DumpOutput(CATCGMStream &Str, CATCGMOutput &os, int VersionNumber=1);

protected: // Donnees membres

   // CATCXChecker * _Implementation;
};

/** @nodoc  */
inline CATCheckerBodyImpl * CATCheckerBody::GetCheckerBodyExtensible() const
{
   if (!GetExtensible()) CATThrowForNullPointerReturnValue(NULL);
   return (CATCheckerBodyImpl*) GetExtensible();   
}

#endif
