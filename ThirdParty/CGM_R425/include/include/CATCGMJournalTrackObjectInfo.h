/* -*-c++-*- */
#ifndef CATCGMJournalTrackObjectInfo_h_
#define CATCGMJournalTrackObjectInfo_h_
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 1997
//-----------------------------------------------------------------------------
// method CATCGMJournalTrackObjectInfo :
//
//  Geometrical Report 
//
// temporaire pour ASE
// a remettre dans CATCGMJournalList
//-----------------------------------------------------------------------------
// Usage Notes:
//
//   
//-----------------------------------------------------------------------------
// Creation 30/09/99                                                  rad
//-----------------------------------------------------------------------------

#include "YP00IMPL.h"
class CATCGMJournalList;
class CATCGMJournalInfo;
class CATGeometry;

// temporaire pour ASE
//  a remettre dans CATCGMJournalList

// ExportedByYP00IMPL const CATCGMJournalInfo*  CATCGMJournalTrackObjectInfo(CATCGMJournalList* journal , CATGeometry* obj);

// pour SRO
// pour extraction d un sous-journal 
ExportedByYP00IMPL CATCGMJournalList* CATCGMExtractJournal(CATCGMJournalList* journal , const CATLISTP(CATGeometry)& objs);

#endif
