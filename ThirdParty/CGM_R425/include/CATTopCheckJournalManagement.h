/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 * @fullreview  HCN TYCX 02:10:30
 */

/* -*-c++-*- */
#ifndef CATTopCheckJournalManagement_H_
#define CATTopCheckJournalManagement_H_

//=============================================================================
// Class for managing CATTopCheckJournal and
//                    CATTopOperator::BasicCheckJournal(...)
//
//                    and
//
//                    CATJournalsMapping
//
//                    behaviors
//
//=============================================================================
// Oct. 02  Creation                                                      HCN
// Dec. 02  CATTCJDefaultCheckLevel et CATTCJCAACheckLevel                HCN
// Jan. 03 _CATCGMJMDumpJournals, CATCJTopCheckDump                       HCN
//=============================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATBoolean.h"
#include "CATTrace.h"

#define CATTCJ_KO 1
#define CATTCJ_OK 0

#define CATTCJDefaultCheckLevel 10
#define CATTCJCAACheckLevel -9999

#define CATCJTopCheckDump        "TopCheckDump"
#define CATCJTopCheckDumpComment "Dump CATTopCheckJournal() traces"

class ExportedByCATTopologicalObjects CATTopCheckJournalManagement
{
  friend class CATTopCheckJournal;
  friend class CATTopOperator;
  friend class CATJournalsMappingImpl;
  friend class CATTopCAACompliantJournalChecker;
  friend class CATTopCheckTopologicalJournal;

protected :

  CATTopCheckJournalManagement();
  virtual ~CATTopCheckJournalManagement();

//=========================
// Pour le Check de journal
//=========================

  static int _CATCGMJCRuleNameDimension;
  static int _CATCGMJCRuleValidCellTypes;
  static int _CATCGMJCRuleOnlyExistingBorderCells;
  //static int _CATCGMCheckJournalNewAlgo;
  static int _CATCGMJCRuleVerifCellsInBody;

  static int _CATTopCheckJournalLevel;

  static int _CATTCJCAACompliant;
  static int _CATTCJCAACompliantCompare;
  static int _CATTCJCAACompliantComparePerfo;

  static int _CATTCJFullCheck;    //for cvm (all cells are followed and checked)

  static CATTrace _TopCheckDump;

  static int _CAACheckLevel;

//===========================
// Pour le Mapping de journal
//===========================

  static int _CATCGMJMDumpJournals;
};

#endif
