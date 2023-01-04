// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
// Creation EDS  25/07/2001
//
//  Cf. CATCreateSplitBySkin.h
//
//=============================================================================

#ifndef __CATTopSplitBySkin_h__
#define __CATTopSplitBySkin_h__

#include "CATIACGMLevel.h" // automatic treatment EB_2014_04_16
#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"

#include "CATListOfCATLumps.h"
#include "CATTopSplitBySkinDef.h"

class CATExtTopOperator;
class CATVoBContactCheck;

class ExportedByCATTopologicalObjects CATTopSplitBySkin: public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATTopSplitBySkin);
   public:

      enum SelectionMode
      {
         Keep = CATTopSplitBySkinSelModeKeep,
         Remove = CATTopSplitBySkinSelModeRemove,
         PositionVsPlane = CATTopSplitBySkinSelModePositionVsPlane
      };
   
      enum SelectionSide
      {		
         OverSkin = CATTopSplitBySkinSelSideOverSkin,
         UnderSkin = CATTopSplitBySkinSelSideUnderSkin,
         UnSet = CATTopSplitBySkinSelSideUnSet,
         BothSides = CATTopSplitBySkinSelSideBoth
      };
     
     
   protected:

      //============================
      // Constucteur et destructeurs
      //============================

      CATTopSplitBySkin(CATGeoFactory * iFactory, CATTopData * iTopData, CATExtTopOperator *iExtensible = NULL);      

   public:

      virtual ~CATTopSplitBySkin();


      //===========================================
      // Methodes de parametrisation de l'operateur
      //===========================================

      virtual SelectionSide GetSelectionSide() const = 0;
      virtual SelectionMode GetSelectionMode() const = 0;
      virtual CATBoolean    GetCheckJournal() const = 0;
      virtual CATBoolean    GetSkinBodyIsInfinite() = 0;

      /** @nodoc @nocgmitf */
      virtual CATBoolean GetCreateComplementaryBody() = 0;

#ifdef CATIACGMV5R18
			/**
			* Sets or unsets the ‘Keep elements in half space’ mode.
			*   @param iMode
			*      Mode on (TRUE) or off (FALSE)
			*/
			virtual void  SetKeepHalfSpaceMode(CATBoolean iMode)= 0;

			/**
			* Queries whether ‘Keep elements in half space’ mode is activated or not.
			*   @param oMode
			*      Mode on (TRUE) or off (FALSE)
			*/
			virtual void GetKeepHalfSpaceMode(CATBoolean & oMode)= 0;
#endif

      virtual void SetCheckJournal(CATBoolean iCheckMode) = 0;
      virtual void SetSelectionSide(SelectionSide iSelectionSide) = 0;
      virtual void SetSelectionMode(SelectionMode iSelectionMode) = 0;
      virtual void SetSkinBodyIsInfinite(CATBoolean iIsInfinite) = 0;

      /** @nodoc @nocgmitf */
      virtual void SetCreateComplementaryBody(CATBoolean iCreateComplementaryBody) = 0;

      virtual void SetNoVolumicSimplif(CATBoolean iNoVolumicSimplif) = 0;

      virtual void SetLumpPropagation(CATBoolean iLumpPropagation) = 0;

      
      //======================================
      // Methodes specifiques a CATTopOperator
      //======================================

	    // CATCGMReplay
      //virtual int Run() = 0;
      
      /** @nodoc @nocgmitf */
      virtual CATBody * GetResult() = 0;

      virtual CATBody * GetResult(CATCGMJournalList * ioJournal) = 0;


      //=========================
      // Methodes sur le resultat
      //=========================

      /** @nodoc @nocgmitf */
      virtual void GetUncutVolumes(ListPOfCATCell & ioUncutVolumes) const = 0;

      /** @nodoc @nocgmitf */
      virtual CATBoolean GetMatterRemoved() const = 0;

      /** @nodoc @nocgmitf */
      virtual CATBody * GetComplementaryBody() = 0;

      /** @nodoc @nocgmitf */
      virtual void SetPostTreatJournal(CATBoolean iPostTreatJournal) = 0;

      //VoB contact check
      virtual void SetVoBContactCheck(CATVoBContactCheck * iContactCheck);
      virtual CATVoBContactCheck * GetVoBContactCheck() const;
};

#endif
