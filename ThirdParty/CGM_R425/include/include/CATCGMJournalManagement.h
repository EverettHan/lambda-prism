/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 * @fullreview  HCN TCX 02:10:18
 */

/* -*-c++-*- */
#ifndef CATCGMJournalManagement_H_
#define CATCGMJournalManagement_H_

//=============================================================================
// Class for managing CATCGMJournal behaviour
//=============================================================================
// Oct. 02  Creation                                                      HCN
// Dec. 02  HTML_OUTPUT, DumpTracesDebug(...)                             HCN
// Jan. 03  Traces                                                        HCN
// Jun. 22  Add env-var to block the dump of the journal                  Q48
//=============================================================================

#include "ExportedByGeometricObjects.h"
#include "CATBoolean.h"
#include "CATCGMVirtual.h"
#include "CATTrace.h"


#define HTML_ENDL    CATCGMJournalManagement::_pHTML_endl << endl
#define HTML_CGMENDL CATCGMJournalManagement::_pHTML_endl << cgmendl

#define CATCGMJ_TRACES               "CATCGMJournalTraces"

#define CATCGMJ_TRACES_COMMENT       "Dump journal reporting and tass"

#define CATCGMJ_TRACES_NAME          "CATCGMJTraces"

#define CATCGMJ_GRAPH_TRACES         "CATCGMJournalGraphTraces"

#define CATCGMJ_GRAPH_TRACES_COMMENT "Dump journal graph during tass"

#define CATCGMJ_TASS_TRACES          "CATCGMJournalTassTraces"



class ExportedByGeometricObjects CATCGMJournalManagement : public CATCGMVirtual
{
  friend class CATCGMJournal;
  friend class CATCGMJournalItem;
  friend class CATCGMJournalList;
  friend class CATCGMJournalGraph;
  friend class CATTopCheckJournalData;
  friend class CATTopOperator;
  
public :

  CATCGMJournalManagement();
  virtual ~CATCGMJournalManagement();

  static void StartJournalMappingSession();
  static void EndJournalMappingSession();

  static void SetHTMLOutput(CATBoolean iMode);

  static void DumpTracesDebug(char* ipMsg, CATULONG32  iSessionId);

  static CATBoolean AllowJournalDump();
  static CATBoolean BlockJournalDump();

protected :

  static CATBoolean _HTML_OUTPUT;
  static char* _pHTML_endl;

  static CATBoolean _JournalMappingSession;

//===========================
// Traces
//===========================

  static CATTrace _CATCGMJournalTraceOn;

  static CATTrace _CATCGMJournalGraphTraceOn;

  static int _CATCGMJournalTassTraceOn;
};

#endif
