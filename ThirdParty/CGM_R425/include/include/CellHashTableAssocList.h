#ifndef CellHashTableAssocList_h
#define CellHashTableAssocList_h

//**********************************************************************************************************************
// class CellHashTableAssocList
//---------------------------------------------------------------------------------------------------------------------
// Class implementing an hash table where each element is a CATCell, and associating each element to a list of CATCell.
// This class inherits from HashTableAssocList, so refer to it for a description of methods.
//
// Additional funcionalities:
//
// 1) Use it to get upward links Vertex->Edge and Edge->Face in a CATBody
//
//      CellHashTableAssocList * Table = CellHashTableAssocList::CreateFromTopology(Body);
//
//    Example: retrieve all faces of Body bounding an edge E1
//      HashTableAssocList_AssocBegin(*Table, E1, CurrentFace, CATFace *)
//      {
// 	      CurrentFace->...
//      } HashTableAssocList_AssocEnd;
//
//    Example: retrieve all elements to follow for journaling (CATFace, CATEdge of the boundary of a CATShell,
//    extremity CATVertex of a CATWire, CATEdge of a CATWire, CATVertex of a CATVertexInVolume):
//
//      CATListPtrCATCell CellsToFollow;
//      Table->RetrieveCellsToFollow(FALSE, CellsToFollow);
//
// 2) Use it to analyse a journal
//
//      CellHashTableAssocList Forward;
//      CellHashTableAssocList Backward;
//      CellHashTableAssocList::FillFromJournal(Journal, &Forward, &Backward);
//
//    If Journal contains:
//    Face 1         -- Modification -> Face 2
//    Face 1, Edge 1 -- Creation -> Edge 2, Edge 3
//    Edge 1         -> Delete
//    Face 3         -- Modification -> Face 3
//    Forward will contain couples (Face 1, Face 2), (Face 1, Edge 2), (Face 1, Edge 3), (Edge 1, Edge 2), (Edge 1, Edge 3), (Face 3, Face 4)
//    Backward will contain couples (Face 2, Face 1), (Edge 2, Face 1), (Edge 3, Face 1), (Edge 2, Edge 1), (Edge 3, Edge 1), (Face 4, Face 3)
//    Delete and Keep orders are ignored.
//---------------------------------------------------------------------------------------------------------------------
// 2010 WEEK 27      Creation                                                                                      LD2
//**********************************************************************************************************************

#include "HashTableAssocList.h"
#include "ExportedByCATTopologicalObjects.h"
#include "ListPOfCATTopology.h"
class CATCell;
class CATListPtrCATCell;
class CATListPtrCATGeometry;
class CATCellHashTable;
class CATBody;
class CATCGMJournalList;
class CATTopology;
class CATAdaptiveHashTable;
class CATCGMOutput;
class CATListPtrCATCGMJournal;

class ExportedByCATTopologicalObjects CellHashTableAssocList : public HashTableAssocList
{
public:
  CellHashTableAssocList(int iEstimatedSize = 31);
  virtual ~CellHashTableAssocList();

  INLINE CATBoolean IsInside(CATCell * iElem) {return HashTableAssocList::IsInside(iElem);}
  INLINE void AddAssoc(CATCell * iElem, CATCell * iAssoc) {HashTableAssocList::AddAssoc(iElem, iAssoc);}
  INLINE int GetNbAssoc(CATCell * iElem) {return HashTableAssocList::GetNbAssoc(iElem);}
  INLINE CATCell * GetItem(int iPos) const {return (CATCell *)HashTableAssocList::GetItem(iPos);}
  INLINE int Size() const {return HashTableAssocList::Size();}
  INLINE int Remove(CATCell * iElem) {return HashTableAssocList::Remove(iElem);}
	
  void GetAllAssocCells(CATCell * iElem, CATListPtrCATCell & List, int iDimension = -1);
  void GetAllAssocCells(CATCell * iElem, CATAdaptiveHashTable & List, int iDimension = -1);

  void GetAdjacentCellsOfSameDimension(CATCell * iElem, CATAdaptiveHashTable & oTable);

  void Dump(CATCGMOutput & os);

  //Methods to treat journals
  CATBoolean IsCellToFollow(CATCell * iCell);
  void RetrieveValidCells(CATCell * iInvalidCell, CATListPtrCATGeometry & oValidCells);
  void RetrieveCellsToFollow(CATBoolean iFullJournal, CATListPtrCATCell & oCellsToFollow, CATBoolean iImprintContext = FALSE, CATBoolean iFollowVolumes   = FALSE);
  void RetrieveCellsWithNoAssoc(CATListPtrCATCell & oCellsWithNoAssoc, short * oMinDim = NULL, short * oMaxDim = NULL);
  void AddUpwardLinksToHashTable(CATCell * iCell,
    CATBoolean iVertices = TRUE,
    CATBoolean iEdges = TRUE,
    CATBoolean iFaces = TRUE,
    CATBoolean iVolumes = TRUE);

  //static methods

  /**
  * Retrieves cells for reporting without activating the body.
  */
  static void GetCellsForReporting(CATBody * iBody, CATListPtrCATCell & oCellsToFollow);

  static CellHashTableAssocList * CreateFromTopology(ListPOfCATTopology & iTopologyList,
    CATBoolean iVertices = TRUE,
    CATBoolean iEdges = TRUE,
    CATBoolean iFaces = TRUE,
    CATBoolean iVolumes = TRUE,
    CATBoolean iDuplicataAutorized = FALSE);

  static CellHashTableAssocList * CreateFromTopology(CATTopology * iTopology,
    CATBoolean iVertices = TRUE,
    CATBoolean iEdges = TRUE,
    CATBoolean iFaces = TRUE,
    CATBoolean iVolumes = TRUE,
    CATBoolean iDuplicataAutorized = FALSE);

  static void FillFromJournal(CATCGMJournalList * iJournal,
    CellHashTableAssocList ** ioForward,
    CellHashTableAssocList ** ioBackward,
    CATBoolean iConsiderDeletionAndOrphanCreation = FALSE);

  static void FillFromJournal_NoTass(CATCGMJournalList * iJournal,
    CellHashTableAssocList ** ioForward,
    CellHashTableAssocList ** ioBackward,
    CATBoolean iConsiderDeletionAndOrphanCreation);

  static void FillFromJournalItems(CATListPtrCATCGMJournal & iItemList,
    CellHashTableAssocList ** ioForward,
    CellHashTableAssocList ** ioBackward,
    CATBoolean iConsiderOrphanCreation,
    CATBoolean iConsiderDeletion,
    CATBoolean iConsiderElementsWithoutFactory,
    CATBoolean iThrowIfNonCellItems = TRUE); // Throw if journal items contain things other than cells, e.g. planes.
};

ExportedByCATTopologicalObjects CellHashTableAssocList * CreateCellHashTableAssocListFromBody(CATBody * iBody,
                                                                                              CATBoolean iVertices = TRUE,
                                                                                              CATBoolean iEdges = TRUE,
                                                                                              CATBoolean iFaces = TRUE,
                                                                                              CATBoolean iVolumes = TRUE);

#endif
