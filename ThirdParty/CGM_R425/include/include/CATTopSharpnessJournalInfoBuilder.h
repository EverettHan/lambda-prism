/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 * @fullreview  HCN TCX 02:10:18
 */

/* -*-C++-*- */

#ifndef __CATTopSharpnessJournalInfoBuilder_H__
#define __CATTopSharpnessJournalInfoBuilder_H__

// COPYRIGHT DASSAULT SYSTEMES 2002

//=============================================================================
// Operator for differenciating contiguous G1 cells in a topological journal
// by adding different journal informations to the creation orders.
//
// Use CATCreateSharpnessJournalInfoBuilder(...) to create such an operator.
//
// ...
//
// Oct. 02  Creation                                                      HCN
//=============================================================================


#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"
#include "CATCGMNewArray.h"
#include "CATTopDefine.h"


class ExportedByCATTopologicalObjects CATTopSharpnessJournalInfoBuilder : public CATTopOperator
{
public:

  enum CATJournalInfoInitMode {CATJournalInfo_Next, CATJournalInfo_Value};

protected:
  
  //============================
  // Constucteur et destructeurs
  //============================
  
  CATTopSharpnessJournalInfoBuilder(
    CATGeoFactory*                                            ipFactory,
    CATTopData*                                               ipTopData,
    CATBody*                                                  ipBody,
    CATJournalInfoInitMode                                    iJournalInfoInitMode = CATJournalInfo_Next,
    CATLONG32                                                      iJournalInfoInitValue = 0,
    CATLONG32                                                      iJournalInfoStep = 1,
    CATAngle                                                  iMinSharpAngle = CATTopSharpAngle);
  
public:

  virtual ~CATTopSharpnessJournalInfoBuilder();

  CATCGMNewClassArrayDeclare;
  
  //======================================
  // Methodes specifiques a CATTopOperator
  //======================================
  
  virtual int Run() = 0;
  
  //=========================================================
  // Methodes specifiques a CATTopSharpnessJournalInfoBuilder
  //=========================================================


  //==========================================================================
  // Methodes specifiques a CATTopSharpnessJournalInfoBuilder : pour debug CGM
  //==========================================================================
  virtual void BuildFakeJournal() = 0;
  virtual CATCGMJournalList* GetFakeJournal() = 0;
};

#endif
