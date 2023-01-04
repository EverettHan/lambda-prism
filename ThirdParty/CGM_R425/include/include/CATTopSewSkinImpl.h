//=============================================================================
// 03 2009   Creation                                  LD2
//-----------------------------------------------------------------------------
//
// New implementing class for the CATTopSewSkin operator
//
// Toutes les operations sont effectuees par l'extensible (CATTopSewSkinCGM),
// et seulement les fonctions du CGMReplay restent dans la classe
// d'implementation (CATTopSewSkinImpl).
// Avant c'etait CATTopSewSkinCGM la classe d'implementation.
//
// Nouvelles fonctionalites Apr09 LD2 :
// SetTolerance, pour choisir la tolerance
// SetEdgeMapping, pour forcer le posage des edges a coudre
//
//=============================================================================

#ifndef __CATTopSewSkinImpl_h__
#define __CATTopSewSkinImpl_h__

#include "CATIACGMLevel.h" // automatic treatment EB_2014_04_16
#include "CATTopSewSkin.h"

class CATGeoFactory;
class CATTopData;
class CATCGMJournalList;
class CATCXBody;

class ExportedByCATTopologicalObjects CATTopSewSkinImpl: public CATTopSewSkin
{
   public:

      //========================================================
      // Constructeurs et destructeurs
      //========================================================

#ifdef CATIACGMV5R20
      // LD2, 4avr09, nouveau constructeur avec extensible
      CATTopSewSkinImpl(CATGeoFactory * iFactory, CATTopData * iTopData, CATExtTopOperator * iExtensible);
#else
      CATTopSewSkinImpl(CATGeoFactory * iFactory, CATTopData * iTopData, CATCXBody * iTrimmingBody, CATCXBody * iSkinBody); 
#endif

      ~CATTopSewSkinImpl();

      //========================================================
      // Methodes de parametrisation de l'operateur (INTERFACES)
      //========================================================

      void SetTolerance(double iTolerance);

      void SetEdgeMapping(CATEdge * iMappedFreeEdge, CATCell * iTargetCell);

      void SetLiveMode(CATBoolean iLiveMode);

   protected:

      void SetCheckJournal(CATBoolean iCheckMode);

      void SetSelectionSide(CATBoolean iSameSkinSide);

      void SetSimplificationMode(CATBoolean iSimplifMode);

      void LogDeletionOnImmersedEdges(CATBoolean iLogDeletion = FALSE);

      //========================================================
      // Methodes d'execution
      //========================================================

      int  Run();

      int  RunOperator();

      //========================================================
      // Methodes de resultats (INTERFACES)
      //========================================================

      CATBoolean GetCheckJournal() const;

      CATBoolean GetSelectionSide() const;

      CATBoolean ResultIsClosed(); 
                                    
      void GetEdgesAndGaps(CATLISTP(CATEdge)& ioEdges, CATListOfDouble& ioGaps);

      CATBody * GetResult(CATCGMJournalList * ioJournal);

      CATBody * GetResult();

      //========================================================
      // Methode Dump
      //========================================================

      void Dump(ostream & iOutStream) const;

      //=================================
      // Methodes pour le CGMReplay 
      //=================================

   public:

      static const CATString *GetDefaultOperatorId() { return &_OperatorId; }

   protected:

      const  CATString  *GetOperatorId();
      CATExtCGMReplay   *IsRecordable(short &LevelOfRuntime, short &VersionOfStream);
      void               RequireDefinitionOfInputAndOutputObjects();
      void               WriteInput(CATCGMStream &ioStream);
      void               WriteTopOutput(CATCGMStream &ioStream);
      CATBoolean         ValidateTopOutput(CATTopCheckJournal* iEquivalent,CATCGMOutput& os);
      CATCheckDiagnostic CheckOutput(CATCGMOutput &os);
      void  Dump( CATCGMOutput& os );
      static CATString   _OperatorId;
      
};

#endif
