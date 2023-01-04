/* -*-c++-*- */
#ifndef CATTopBooleanTrim_H_
#define CATTopBooleanTrim_H_

// COPYRIGHT DASSAULT SYSTEMES  2001

#include "CATTopOperator.h"

#include <iostream.h>
#include "ListPOfCATCell.h"

class    CATBody;
class    CATCGMJournalList;
class    CATTopData;

class ExportedByCATTopologicalObjects CATTopBooleanTrim : public CATTopOperator
{

   //===========================================================================
   //      Constructeurs et destructeurs
   //===========================================================================

protected:
   
   CATTopBooleanTrim(CATGeoFactory* iFactory, CATTopData* iData);

public:

   virtual ~CATTopBooleanTrim();  

   //===========================================================================
   //      Specification des parties a conserver et a retirer a partir de
   //      liste de faces appartenant au body GetCutBody
   //===========================================================================

   virtual void SetSelectedCells(CATLISTP(CATCell) & iCellsToRemove, 
                                 CATLISTP(CATCell) & iCellsToKeep,
                                 CATLISTP(CATCell) & iCellsToRemoveByAdjacent, CATLISTP(CATCell) & iCellsAdjacentForRemove,
                                 CATLISTP(CATCell) & iCellsToKeepByAdjacent,   CATLISTP(CATCell) & iCellsAdjacentForKeep) = 0;

   virtual void SetSelectedCells(CATLISTP(CATCell) & iCellsToRemove, 
                                 CATLISTP(CATCell) & iCellsToKeep,
                                 CATLISTP(CATCell) & iCellsToRemoveByAdjacent,  // Remove avec adjacence
                                 CATLISTP(CATCell) & iCellsAdjacentForRemove,
                                 CATListOfInt      & iCellsForRemoveSelection,
                                 CATLISTP(CATCell) & iCellsToKeepByAdjacent,    // Keep avec adjacence
                                 CATLISTP(CATCell) & iCellsAdjacentForKeep,
                                 CATListOfInt      & iCellsForKeepSelection) = 0;
   // Result will be the expected deleted part.
   virtual void  SetComplementaryResult(CATLONG32 iComplementary)=0;

   // CATCGMReplay
   //virtual int       Run() = 0;
   
   virtual CATBody * GetResult(CATCGMJournalList * ioJournal = NULL) = 0;

   virtual int       RemoveLump() = 0;   
  
   virtual CATBody * GetCutBody(CATCGMJournalList * iCutBodyJournal = (CATCGMJournalList*)0) = 0;
   virtual void      GetVolumesAttributes(CATLISTP(CATCell)& ioVolumesToKeep, CATLISTP(CATCell)& ioVolumesToRemove) = 0;
};

/**
 * Creates a CATTopBooleanTrim operator which allows multiple runs.
 * @param iFactory
 * The factory of the geometry. 
 * @param iData
 * The pointer to the data containing the configuration and the journal.
 * @param iBody1
 * The pointer to the first body for trim.
 * @param iBody2
 * The pointer to the second body for trim.
 */

ExportedByCATTopologicalObjects CATTopBooleanTrim* CATCreateTopBooleanTrim(CATGeoFactory *iContainer,
                                                                           CATTopData    *iData,
                                                                           CATBody       *iBody1,
                                                                           CATBody       *iBody2);

#endif
