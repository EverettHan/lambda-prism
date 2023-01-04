#ifndef CATContextForFastRunBoxSolutionExtInterface_h
#define CATContextForFastRunBoxSolutionExtInterface_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2010
//
//  Classe temporaire pour changement d'archi en attendant de resoudre le problem de distanceMin
//==========================================================================

#include "ExportedByCATTopologicalObjects.h"

#include "CATContextForFastRunExt.h"

class ExportedByCATTopologicalObjects CATContextForFastRunBoxSolutionExtInterface : public CATContextForFastRunExt
{
public :
 
  CATContextForFastRunBoxSolutionExtInterface();
  virtual ~CATContextForFastRunBoxSolutionExtInterface();

 
// Partie pour la Box, problem d'archi, a voire : 
public : 
  virtual CATFastRunSolution GetFastRunSolution();
  virtual CATFastRunStatus CheckContextForFastRun();
  virtual void ConstructPartialResult(CATBody *& oBody, CATCGMJournalList *& oJournal);
  virtual CATBoolean PartialRunNeeded();

  virtual int          GetScenarioType(); // pour ODT
  virtual void         SetScenarioMaxFastRunnable(int  iScenarioMaxFastRunnable); // pour ODT

};

#endif
