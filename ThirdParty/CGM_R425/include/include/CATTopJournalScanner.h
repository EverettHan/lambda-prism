#ifndef CATTopJournalScanner_h
#define CATTopJournalScanner_h

//************************************************************************************************************************
// CATTopJournalScanner
//-------------------------------------------------------------------------------------------------------------------
// Tool to retrieve all elements inside a journal.
// Create it with CreateTopJournalScanner.
// Use GetAllGeometriesInJournal method to scan a journal.
//-------------------------------------------------------------------------------------------------------------------
// 2011 WEEK 44    Creation                                                                              LD2
// 2017 WEEK 3     Add capability to retrieve Cells with their Info in the Journal                       KY1 
//************************************************************************************************************************

#include "CATBoolean.h"
#include "CATCGMJournal.h"
#include "CATDataType.h"
#include "ExportedByCATTopologicalObjects.h"

class CATGeometry;
class CATCGMJournalList;
class CATCGMHashTable;
class CATAdaptiveHashTable;
class CATCGMHashTableWithAssoc;

class ExportedByCATTopologicalObjects CATTopJournalScanner
{
public:
  virtual ~CATTopJournalScanner();
  void GetAllGeometriesInJournal(CATCGMJournalList * iJournal);
  void SetKeepTilde(CATBoolean iKeepTilde);

  enum Type
  {
    OnlyParents = 1,
    OnlyChildren = 0,
    ParentsAndChildren = 2
  };

protected:
  CATTopJournalScanner(CATTopJournalScanner::Type iType,
                       CATBoolean iGetFaces,
                       CATBoolean iGetEdges,
                       CATBoolean iGetVertices,
                       CATBoolean iWithTass);
  virtual void Insert(CATGeometry * iGeometry) = 0;
  virtual void InsertInfo(CATGeometry * iGeometry,CATLONG32 iInfo) = 0;
  virtual CATBoolean ItemTypeIsAsked(CATCGMJournal::Type iType) = 0;

protected:
   CATBoolean _WithInfo;
private:
  CATTopJournalScanner::Type _Type;
  CATBoolean _GetFaces;
  CATBoolean _GetEdges;
  CATBoolean _GetVertices;
  CATBoolean _WithTass;
  CATBoolean _KeepTilde;  
};

/** @nodoc @nocgmitf */
ExportedByCATTopologicalObjects CATTopJournalScanner *
CreateTopJournalScanner(CATTopJournalScanner::Type   iType,                // OnlyParents, OnlyChildren or ParentsAndChildren
                        CATBoolean                   iGetFaces,            // TRUE if you want faces
                        CATBoolean                   iGetEdges,            // TRUE if you want edges
                        CATBoolean                   iGetVertices,         // TRUE if you want vertices
                        CATBoolean                   iWithTass,            // TRUE if you want to duplicate and tass a non tassed Journal
                        CATCGMHashTable            * iCreation,            // the output hashtable to store Creation elements; leave NULL if you don't want them.
                        CATCGMHashTable            * iModification,        // the output hashtable to store Modification elements; leave NULL if you don't want them.
                        CATCGMHashTable            * iSubdivision,         // the output hashtable to store Subdivision elements; leave NULL if you don't want them.
                        CATCGMHashTable            * iAbsorption,          // the output hashtable to store Absorption elements; leave NULL if you don't want them.
                        CATCGMHashTable            * iDeletion,            // the output hashtable to store Deletion elements; leave NULL if you don't want them.
                        CATCGMHashTable            * iKeep,                // the output hashtable to store Keep elements; leave NULL if you don't want them.
                        CATCGMHashTableWithAssoc   * iOutputCellWithInfo); // the output hashtable to store output elements with info; leave NULL if you don't want them.

/** @nodoc @nocgmitf */
ExportedByCATTopologicalObjects CATTopJournalScanner *
CreateTopJournalScanner(CATTopJournalScanner::Type iType,      // OnlyParents, OnlyChildren or ParentsAndChildren
                        CATBoolean iGetFaces,                  // TRUE if you want faces
                        CATBoolean iGetEdges,                  // TRUE if you want edges
                        CATBoolean iGetVertices,               // TRUE if you want vertices
                        CATBoolean iWithTass,                  // TRUE if you want to duplicate and tass a non tassed Journal
                        CATAdaptiveHashTable * iCreation,      // the output hashtable to store Creation elements; leave NULL if you don't want them.
                        CATAdaptiveHashTable * iModification,  // the output hashtable to store Modification elements; leave NULL if you don't want them.
                        CATAdaptiveHashTable * iSubdivision,   // the output hashtable to store Subdivision elements; leave NULL if you don't want them.
                        CATAdaptiveHashTable * iAbsorption,    // the output hashtable to store Absorption elements; leave NULL if you don't want them.
                        CATAdaptiveHashTable * iDeletion,      // the output hashtable to store Deletion elements; leave NULL if you don't want them.
                        CATAdaptiveHashTable * iKeep);         // the output hashtable to store Keep elements; leave NULL if you don't want them.

#endif

