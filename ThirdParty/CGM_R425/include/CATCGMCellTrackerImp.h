//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//   Class      :      CATCGMCellTrackerImp
//   Creation   :      27/02/2009
//
//
//   Synopsis   :      Implementation class of CATCGMCellTracker. It allows cell tracking after applying an operator
//               
//   
//
//
//   Authors      :  AAD + KY1 +TCX
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 19/05/09 KY1 Add method SetTrackMultipleDimension
// 11/10/16 KY1 Remplacement de l'identifiant de l'enumération CATCGMJournalKind 
//              par CATCGMJournalMode 
// 14/01/20 NLD Detabulation et revue du colonnage
//              Ajout Init()
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CATCGMCellTrackerImp_H
#define   CATCGMCellTrackerImp_H


#include "CATIACGMLevel.h"
#include "ListPOfCATCell.h"
#include "CATListOfCATCGMJournals.h"
#include "ExportedByCATTopologicalObjects.h"

#include "CATListOfInt.h"
#include "CATCellHashTable.h"
#include "CATListPV.h"
#include "CATBoolean.h"

class CATCGMJournal;
//class CATLISTP(CATCGMJournal);
//class CATBoolean;
//class CATListOfInt;
//class CATCellHashTable;
//class CATListPV;
class CATCGMOutput;
class CATCell;
class CATBody;
class CATCGMJournalList;
class CATSoftwareConfiguration;
class CATCGMHashTableWithAssoc;
class CATString;


#include "CATCGMCellTracker.h"
#include "ListPOfCATBody.h"
#include "CATListPV.h"
//#include "CATLISTV_CATBoolean.h"
#include "ListVOfLong.h"
#include "CATCollec.h"

/**
* @nodoc
*/
enum CATCGMJournalOrientation 
{
   CATCGMBackward_Track, CATCGMForward_Track
};

/**
* @nodoc
*/
enum CATCGMJournalMode
{
   CATCGMJournalModeUnknown = -1, CATCGMUserJournal, CATCGMCompletJournal
};

/**
* @nodoc
*/
enum CATCGMKindOfCellList
{
   CATCGMUnknownKindOfList, CATCGMAllFaces, CATCGMAllEdges, CATCGMAllVertices, CATCGMFacesAndEdges,
   CATCGMFacesAndVertices, CATCGMEdgesAndVertices,CATCGMFacesEdgesAndVertices
};

/**
* @nodoc
*/
enum CATTopOperatorType
{   
   CATTopOperatorBooleanType,
   CATTopOperatorChamferType,
   CATTopOperatorFilletType,
   CATTopOperatorDisconnectShellType,
   CATTopOperatorUnknownType,
};

/**
* @nodoc
*/
class ExportedByCATTopologicalObjects CATCGMCellTrackerImp : public CATCGMCellTracker
{
   //==========================================================================================================================
   // Constructors  
   //==========================================================================================================================
public:

   /**
   * Creates a Cell Tracker which allows finding source or image cell of a given cell after
   * the execution of a topological operator  
   * @param iSC
   * The Software Configuration.
   * @return
   * The pointer to the created Cell Tracker. To delete with the usual C++ delete operator after use.
   */
   static CATCGMCellTracker *CATCreateCellTracker(CATSoftwareConfiguration * iSC);


   //==========================================================================================================================
   // Find the image cells of a cell belonging to an input body  
   //==========================================================================================================================
   /*
   * @iSourceCell   :   a cell belonging to an input body, can be a face, an edge or a vertex; can 
   *               not be NULL.
   * @iInputBody   :   an input body to which iSourceCell belongs, can not be NULL
   * @iOutputBody   :   an output body. oImageCells contains only the image cells that belong to iOutputBody
   *                if NULL, oImageCells contains only the image cells that belong to all output bodies.
   * @oImageCells  :   the list of image cells
   *
   * @pioList_IsCellImageWithInfoJournal   : List Of TRUE/FALSE values. 
   *                                If there is no info found then the list will be empty.
   *                                If there is at least one info found.
   *                                 Each value indicates if the retrieved cell at the same index of the list @oImageCellList
   *                                 has an info or not.
   *
   * @pioListOfInfoNumber               : List Of info number. 
   *                                If there is no info found then the list will be empty.
   *                                         If there is at least one info found.
   *                                         The info at a given index of the list corresponds to the retrieved cell at the same index 
   *                                in the list @oImageCellList.has an info or not.
   * BECARFULL : 
   *    - Refer to the list pioList_IsCellImageWithInfoJournal to know if the retrieved cell has an info or not.
   *    - To track info carried by Cells pioList_IsCellImageWithInfoJournal and pioListOfInfoNumber must be not NULL otherwise there is no info tracking
   *
   */
public:
#ifdef CATIACGMR417CAA
   HRESULT GetImage(CATCell *iSourceCell, CATBody *iInputBody,
                    CATBody *iOutBody, ListPOfCATCell &oImageCellList, CATListOfInt *pioList_IsCellImageWithInfoJournal = NULL,
                    CATListOfLong *pioListOfInfoNumber = NULL);
#else
   HRESULT GetImage(CATCell *iSourceCell, CATBody *iInputBody, CATBody *iOutBody, ListPOfCATCell &oImageCellList);
#endif

   //==========================================================================================================================
   // Find the source cells of a cell belonging to an output body  
   //==========================================================================================================================
   /*
   * @iImageCell   :   a cell belonging to an output body, can be a face, an edge or a vertex; can 
   *               not be NULL.
   * @iInputBody   :   an input body. oSourceCells contains only the source cells that belong to iInputBody
   *               if NULL, oSourceCells contains the source cells that belong to all input bodies.
   * @iOutput      :   an output body to which iImageCell belongs; can not be NULL. 
   * @oSourceCells :   the list of source cells.
   *
   * @pioList_IsCellSourceWithInfoJournal   : List Of TRUE/FALSE values.
   *                                If there is no info found then the list will be empty.
   *                                If there is at least one info found.
   *                                Each value indicates if the retrieved cell at the same index of the list @oSourceCellList
   *                                has an info or not.
   *
   * @pioListOfInfoNumber               : List Of info number. 
   *                                If there is no info found then the list will be empty.
   *                                         If there is at least one info found.
   *                                         The info at a given index of the list corresponds to the retrieved cell at the same index 
   *                                in the list @oSourceCellList.
   * BECARFULL : 
   *    - Refer to the list pioList_IsCellSourceWithInfoJournal to know if the retrieved cell has an info or not.
   *    - To track info carried by Cells pioList_IsCellSourceWithInfoJournal and pioListOfInfoNumber must be not NULL otherwise there is no info tracking
   *    - Particular Case : If Cell created from Scratch and wear an Info, then the C.T returtn a ListofCells containing NULL value
   *      and return the Info associated 
   *      to the Cell in  pioListOfInfoNumber. 
   */
public:
#ifdef CATIACGMR417CAA
   HRESULT GetSource(CATCell *iImageCell, CATBody *iInputBody, CATBody *iOutBody, ListPOfCATCell &oSourceCellList,
                     CATListOfInt *pioList_IsCellSourceWithInfoJournal = NULL, CATListOfLong *pioListOfInfoNumber = NULL);
#else
   HRESULT GetSource(CATCell *iImageCell, CATBody *iInputBody, CATBody *iOutBody, ListPOfCATCell &oSourceCellList);
#endif

   //==========================================================================================================================
   // Add an output body and its journal to the CellTracker 
   //==========================================================================================================================
public:
   void AddOutputBody(CATBody *iOutputBody, CATCGMJournal *iJournal);

   //==========================================================================================================================
   // Enable Multiple dimension Source 
   //==========================================================================================================================
public:
   void SetMultiDimensionTrack(CATBoolean iIsMultiDimTrack);

   /**
   * Get all geometries referenced in a JournalList, It could be the input geometries or the output geometries
   * @param ioReferencedInputCells 
   *  Hash table intended  to store all input geometries referenced by the journal.The hash table must be created by the applicant.
   * 
   * @param ioReferencedOutputCells 
   *  Hash table intended  to store all output geometries referenced by the journal.The hash table must be created by the applicant.
   * N.B : if you want only retrieve input (output)referenced geometries set the other argument to NULL
   */
public:
   void GetReferencedCellsInJournal(CATCGMHashTable* ioReferencedInputCells,CATCGMHashTable* ioReferencedOutputCells);

   CATCGMCellTrackerImp(CATSoftwareConfiguration * iSC, CATCGMJournalMode iJournalMode, const CATString *iOperatorName);

   CATCGMCellTrackerImp(CATSoftwareConfiguration * iSC);

private:
   CATCGMCellTrackerImp(const CATCGMCellTrackerImp& CellTrackerImp);

   //==========================================================================================================================
   // Destructor  
   //==========================================================================================================================
public:
   virtual ~CATCGMCellTrackerImp();



   //==========================================================================================================================
   // IsMultipleJournalList
   //==========================================================================================================================
   /**
   * @nodoc
   */
   CATBoolean IsMultipleJournalList(CATCGMJournalList *iJournal);

   //==========================================================================================================================
   // DumpListOfJournalList
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   void DumpListOfJournalList(CATCGMJournalList *iJournal, CATCGMOutput& os);

   //==========================================================================================================================
   // RetrieveLastJournalList
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   CATCGMJournal *RetrieveLastJournalList(CATCGMJournalList *iJournal);

   //==========================================================================================================================
   // SetUseLastJournalList
   //==========================================================================================================================
   /**
   * @nodoc
   */
   //public:
   //void SetUseLastJournalList(CATBoolean iUseLastJournalList);

   //==========================================================================================================================
   // IsUseLastJournalList
   //==========================================================================================================================
   /**
   * @nodoc
   */
   //public:
   //CATBoolean IsUseLastJournalList();

   //==========================================================================================================================
   // 
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   static CATBoolean DisableUseCompleteJournal();

   //==========================================================================================================================
   //  Find the cells that belong to the target body and which correspond to the origin cells 
   //==========================================================================================================================
   /**
   * @nodoc
   */
   /*
   *@iOriginCell             :   a cell belonging to the origin body.
   *@iOriginBody             :   the origin body, from which .....
   *@iTargetBody             :   the target body in which the equivalent cells of the origin cell belong.
   *@iJournal                :   A journal which contains the history that links the origin body and the target body
   *@iOrientJournal        :   takes its values in {backward, forward}
   *
   * oListOfEquivalentCell :   the method returns the list of cells that belong onlt to the target body and correspond
   *                               to the mirror (source or image)of the origin cells
   */
public://private:
   HRESULT OldGetEquivalentCells(CATCell *iOriginCell, CATBody *iOriginBody, CATBody *iTargetBody, 
      CATCGMJournal *iJournal, CATCGMJournalOrientation iOrientJournal, ListPOfCATCell& oListOfEquivalentCell,
      CATListOfInt *pioList_IsTargetCellWithInfoJournal = NULL, CATListOfLong *pioListOfInfoNumber = NULL);

      HRESULT GetEquivalentCells(CATCell *iOriginCell, CATBody *iOriginBody, CATBody *iTargetBody, 
      CATCGMJournal *iJournal, CATCGMJournalOrientation iOrientJournal, ListPOfCATCell& oListOfEquivalentCell,
      CATListOfInt *pioList_IsTargetCellWithInfoJournal = NULL, CATListOfLong *pioListOfInfoNumber = NULL);

   //==========================================================================================================================
   // Compute the image cells of the origin cell in the target body by using the CGM journal 
   // iOriginCells is a list of cell with the same dimension
   // oEquivalentCellList is a list of cell with the same dimension as the cells of iOriginCells 
   //==========================================================================================================================
   /**
   * @nodoc
   */
public://private:
   HRESULT GetCellsByJournal(ListPOfCATCell &iOriginCells, CATBody *iOriginBody, CATBody *iTargetBody, 
      CATCGMJournal *iJournal, CATCGMJournalOrientation iOrientJournal, 
      ListPOfCATCell& oEquivalentCellList);
public://private:
   HRESULT GetCellsByJournal(CATCell *iOriginCell, CATBody *iOriginBody, CATBody *iTargetBody, 
      CATCGMJournal *iJournal, CATCGMJournalOrientation iOrientJournal, 
      ListPOfCATCell& oEquivalentCellList, 
      CATListOfInt *pioList_IsTargetCellWithInfoJournal = NULL, CATListOfLong *pioListOfInfoNumber = NULL);
public://private:
   HRESULT GetCellsByJournalNew(CATCell *iOriginCell, CATBody *iOriginBody, CATBody *iTargetBody, 
      CATCGMJournal *iJournal, CATCGMJournalOrientation iOrientJournal, 
      ListPOfCATCell& oEquivalentCellList, 
      CATListOfInt *pioList_IsTargetCellWithInfoJournal = NULL, CATListOfLong *pioListOfInfoNumber = NULL);

   //==========================================================================================================================
   // Vérifie si le cell d'origine n'appartient pas au body traget: permet un filtrage natureldes cellules qui n'ont pas
   // été modifié par l'opérateur topologique
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   CATBoolean IsCellBelongToBody(CATCell *iOriginCell,CATBody *iTargetBody);

   //==========================================================================================================================
   // GetCellsOfTargetBodyStocked
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   HRESULT GetStoredCellsOfBody(CATBody *piBody, CATCellHashTable *&pioHashTabCellsOfBody);

   //==========================================================================================================================
   // Dump
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   void Dump(CATLISTP(CATBody)& iInputBodies,CATCGMOutput& os);

   //==========================================================================================================================
   // Dump Journal of Cell Tracker
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   void DumpJournalOfCellTracker(CATCGMOutput& os);


   //==========================================================================================================================
   // IsMultiDimensionTrack
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   CATBoolean IsMultiDimensionTrack();
   
   //==========================================================================================================================
   // KeepOnlySameDimension
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   void KeepOnlySameDimension(CATCell        * iOriginCell                         ,
                              ListPOfCATCell & ioListOfEquivalentCells             ,
                              CATBoolean       iIsQueryCellReferencedInJournal     = FALSE,
                              CATListOfInt   * pioList_IsTargetCellWithInfoJournal = NULL,
                              CATListOfLong  * pioListOfInfoNumber                 = NULL);


   //==========================================================================================================================
   // CheckOutput
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   CATBoolean CheckOutput(CATLISTP(CATBody)& iInputBodies, CATCGMOutput& os, int iVerboseLevel = 0);

   //==========================================================================================================================
   // SetStrictCorrespRequired
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   void SetStrictCorrespRequired(CATBoolean iStrictCorrespRequired);


   //==========================================================================================================================
   // IsStrictCheckOutputRequired
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   CATBoolean IsStrictCheckOutputRequired();
   
   //==========================================================================================================================
   // IsAllowTrackIfImageAdjFacesNotFaces
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   CATBoolean IsAllowTrackIfImageAdjFacesNotFaces();

   //==========================================================================================================================
   // SetAllowTrackIfImageAdjFacesNotFaces
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   void SetAllowTrackIfImageAdjFacesNotFaces(CATBoolean iActiveOption);

   //==========================================================================================================================
   // IsAllowTrackVertexByAdjEdges
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   CATBoolean IsAllowTrackVertexByAdjEdges();

   //==========================================================================================================================
   // SetAllowTrackVertexByAdjEdges
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   void SetAllowTrackVertexByAdjEdges(CATBoolean iActiveOption);


   //==========================================================================================================================
   // SetAllowTrackVertexByAdjEdgesIfNbAdjFacesEqualOne
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   void SetAllowTrackVertexByAdjEdgesIfNbAdjFacesEqualOne(CATBoolean iActiveOption);


   //==========================================================================================================================
   // SetAllowTrackVertexIfIntersectionOfEquivFacesIsEmpty
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   void SetAllowTrackVertexIfIntersectionOfEquivFacesIsEmpty(CATBoolean iActiveOption);

   //==========================================================================================================================
   // SetSingleRespIfCardEquivAdjacFacesEqualOne
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   void SetSingleRespIfCardEquivAdjacFacesEqualOne(CATBoolean iActiveOption);
      
   //==========================================================================================================================
   // SetAllowTrackByUsingGeometry
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   void SetAllowTrackByUsingGeometry(CATBoolean iActiveOption);
      
   //==========================================================================================================================
   // SetAllowMultipleRespIfAmbiguityPersist
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   void SetAllowMultipleRespIfAmbiguityPersist(short iActiveOption);
   
   //==========================================================================================================================
   // SetAllowMultipleRespIfAmbiguityPersistForVertex
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   void SetAllowMultipleRespIfAmbiguityPersistForVertex(CATBoolean iActiveOption);


   //==========================================================================================================================
   // SetAllowCardEquivAdjFacesInfThanCardAdjFaces
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   void SetAllowCardEquivAdjFacesInfThanCardAdjFaces(CATBoolean iActiveOption);

   //==========================================================================================================================
   // SetAllowIntersectAdjFacesToFindCommonVertexInCaseOfEdge
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   void SetAllowIntersectAdjFacesToFindCommonVertexInCaseOfEdge(CATBoolean iActiveOption);

   //==========================================================================================================================
   // SetSpecialOptionForHSManager
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   void SetSpecialOptionForHSManager(CATBoolean iActiveOption);


   //==========================================================================================================================
   // ArchiveCellAsItsBorderedCellsComputed
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   void ArchiveCellAsItsBorderedCellsComputed(CATCell *piCell);

   //==========================================================================================================================
   // SetCheckIfCellIsSmartInOutputBody
   //==========================================================================================================================
   /**
   * @nodoc
   */
public:
   void SetCheckIfCellIsSmartInOutputBody(CATBody *iBody,CATBoolean iActiveOption);


   //==========================================================================================================================
   //==========================================================================================================================
   //Tools: 
   //==========================================================================================================================
   //==========================================================================================================================
private: //public:
   /**
   * @nodoc
   */
   HRESULT GetCommonVertexOfFaces(ListPOfCATCell &iAdjacentFaceList, ListPOfCATCell &oCommonVertexList);
   /**
   * @nodoc
   */
   HRESULT GetCommonVertexOfCells(ListPOfCATCell &iAdjacentFaceList, CATListOfInt& iListOfSizesOfGroups, ListPOfCATCell &oCommonVertexList);

   //
   /**
   * @nodoc
   */
   HRESULT GetCommonVertexOfFacesAndEdges(ListPOfCATCell &iAdjacentCells, ListPOfCATCell &oCommonVertexList);
   //
   /**
   * @nodoc
   */
   HRESULT GetCommonEdgeOfFaces(ListPOfCATCell &iAdjacentFaceList, ListPOfCATCell &oCommonEdgeList);
   /**
   * @nodoc
   */
   HRESULT GetCommonEdgeOfFaces(ListPOfCATCell &iAdjacentFaceList,CATListOfInt& iListOfSizesOfGroups , ListPOfCATCell &oCommonEdgeList);
   //
   /**
   * @nodoc
   */
   HRESULT GetCommonFaceOfFaces(ListPOfCATCell &iAdjacentFaceList, CATListOfInt& iListOfSizesOfGroups, ListPOfCATCell &oCommonFaceList);
   //
   /**
   * @nodoc
   */
   HRESULT GetCommonEdgeOfFacesAndEdges(ListPOfCATCell &iAdjacentCells, ListPOfCATCell &oCommonEdgeList);
   //
   /**
   * @nodoc
   */
   HRESULT GetCommonVertexOfEdges(ListPOfCATCell &iAdjacentEdgeList, ListPOfCATCell &oCommonVertexList);
   //
   /**
   * @nodoc
   */
   HRESULT GetCommonVertexOfEdgesAndVertices(ListPOfCATCell &iAdjacentCells, ListPOfCATCell &oCommonVertexList);
   //
   /**
   * @nodoc
   */
   HRESULT GetCommonCellsOfSubListOfFaces(ListPOfCATCell &iAdjacentFaceList,ListPOfCATCell &oSubCommonEdgeList);
   //
   /**
   * @nodoc
   */
   HRESULT GetCommonEdgesOfGroupsOfFaces(CATBody * iContextBody,ListPOfCATCell &iAdjacentFaceList,ListPOfCATCell &oSubCommonEdgeList);
   //
   /**
   * @nodoc
   */
   CATCGMKindOfCellList GetKindOfCellList(ListPOfCATCell &iListOfCells);
   //
   /**
   * @nodoc
   */
   void GetVertexOfCell(CATCell *iCell,ListPOfCATCell &oListOfVertex);


   //==========================================================================================================================
   // Retrieve the adjacent faces of the origin cell (Activation implicite des liens remontants)
   //==========================================================================================================================
public:

   /**
   * @nodoc
   */
   HRESULT ComputeAdjacentCellList(CATCell *iCell, CATBody *iBody);
   //
   /**
   * @nodoc
   */
   HRESULT ComputeAdjacentCellListForHS(CATCell *iCell, CATBody *iBody, CATBoolean iWithFaces=TRUE);
   //
   /**
   * @nodoc
   */
   CATBoolean GetIncidentCellList(CATCell *iCell, CATBody *iBody,ListPOfCATCell &oListOfIncidCells, CATBoolean iWithFaces=TRUE);
   //
   /**
   * @nodoc
   */
   //CATBoolean GetPartialIncidentCellList(CATCell *iCell, ListPOfCATCell &oListOfIncidCells);
   //
   /**
   * @nodoc
   */
   CATCGMHashTableWithAssoc *GetHashTabOfEdgesWithItsIncidentFaces(CATBody *piOutputBody);

   //==========================================================================================================================
   // 
   //==========================================================================================================================
public:
   /**
   * @nodoc
   */
   void ClearOutputData();

   //==========================================================================================================================
   // SetTargetHashTableAndTargetBody
   //==========================================================================================================================
public:
   /**
   * @nodoc
   */
   void SetTargetHashTableAndTargetBody(CATBody *piTargetBody,CATCellHashTable *piTargetCellHashTable);

   //==========================================================================================================================
   // GetListOfBorderedCells
   //==========================================================================================================================
public:
   /**
   * @nodoc
   */
   void GetListOfBorderedCells(CATCell *piCell, CATLISTP(CATCell)*& poListOfBorderedCells);

   //==========================================================================================================================
   // StockListOfBorderedCells
   //==========================================================================================================================
public:
   /**
   * @nodoc
   */
   void StockListOfBorderedCells(CATCell *piCell, CATCellHashTable *piHashTableOfItsBorderedCell);

   //==========================================================================================================================
   // StockListOfBorderedCells
   //==========================================================================================================================
public:
   /**
   * @nodoc
   */
   void StockListOfBorderedCells(CATCell *piCell, CATLISTP(CATCell)* piListOfBorderedCells);

   //==========================================================================================================================
   // StockListOfVerticesOfFace
   //==========================================================================================================================
public:
   /**
   * @nodoc
   */
   void StockListOfVerticesOfCell(CATCell *piFace, CATLISTP(CATCell)* piListOfVertices);

   //==========================================================================================================================
   // GetListOfVerticesOfFace
   //==========================================================================================================================
public:
   /**
   * @nodoc
   */
   void GetListOfVerticesOfCell(CATCell *piCell, CATLISTP(CATCell)*& poListOfVertices);

   //==========================================================================================================================
   // SetPartialHashTabEdgesWithItsIncidFacesComputed
   //==========================================================================================================================
public:
   /**
   * @nodoc
   */
   void SetPartialHashTabEdgesWithItsIncidFacesComputed(CATBoolean iActiveOption);

public:
   /**
   * @nodoc
   */
   void SetOperatorType();


   //==========================================================================================================================
   // SetUseTassedJournal
   //==========================================================================================================================
public:
   /**
   * @nodoc
   */
   void SetUseTassedJournal(CATBoolean iUseTassedJournal);   

   //==========================================================================================================================
   // SetEnableTrackingByUsingGeometry
   //==========================================================================================================================
public:
   /**
   * @nodoc
   */
   void SetEnableTrackingByUsingGeometry(CATBoolean iActiveOption);

   //==========================================================================================================================
   // SetNoJournalBelongingCheck
   //==========================================================================================================================
public:
   /**
   * @nodoc
   */
   void SetOriginCellBelongToJournal(CATBoolean iOption);

   //==========================================================================================================================
   // GetCommonCells
   //==========================================================================================================================
private:
   /**
   * @nodoc
   */
   HRESULT GetCommonCells(ListPOfCATCell **TabOfGroupOfFaces, CATListOfInt &iListOfSizes, ListPOfCATCell& oListOfCommonCell);
   //==========================================================================================================================
   // GetCommonCells
   //==========================================================================================================================
private:
   /**
   * @nodoc
   */
   HRESULT GetCommonCells(ListPOfCATCell& iListOfCell1,ListPOfCATCell& iListOfCell2, ListPOfCATCell& oListOfCommonCell);
   //==========================================================================================================================
   // ComputeCommonCellsOfEquivAdjacentFacesForFillet
   //==========================================================================================================================
private:
   /**
   * @nodoc
   */
   CATBoolean ComputeCommonCellsOfEquivAdjacentFacesForFillet(CATCell *iOriginCell, CATBody *iOriginBody, CATBody *iTargetBody, 
                                                              CATCGMJournal *iJournal, CATCGMJournalOrientation iOrientJournal, 
                                                              ListPOfCATCell& iListOfEquivFacesOfFace, CATListOfInt &iListOfSizes, 
                                                              ListPOfCATCell& oCommonCellList);

   //==========================================================================================================================
   // GetAdjacentEdgeList
   //==========================================================================================================================
private:
   /**
   * @nodoc
   */
   HRESULT GetAdjacentEdgeList(CATCell *iCell, CATBody *iBody, ListPOfCATCell& oAdjacentEdgeList);

   //==========================================================================================================================
   // GetDimBody
   //==========================================================================================================================
private:
   /**
   * @nodoc
   */
   int GetDimBody(CATBody *piBody);


   //==========================================================================================================================
   // InsertHashTable
   //==========================================================================================================================
private:
   /**
   * @nodoc
   */
   void InsertHashTable(CATCellHashTable *& ioDestHashTableOfCells, CATCellHashTable *&iSourceHashTableOfCells);

   //==========================================================================================================================
   // HashTableToList
   //==========================================================================================================================
private:
   /**
   * @nodoc
   */
   void HashTableToList(CATCellHashTable *piHashTableOfCells, ListPOfCATCell &pioListOfCells);

   //==========================================================================================================================
   // IsCellReferencedInJournal
   //==========================================================================================================================
private:
   /**
   * @nodoc
   */
   CATBoolean IsCellReferencedInJournal(CATCell *iCell,CATCGMJournalOrientation iOrientJournal);

   //==========================================================================================================================
   // IsCellDeleted
   //==========================================================================================================================
   /**
   * @nodoc
   */
   CATBoolean IsCellDeletedInJournal(CATCell *piCell);

   //==========================================================================================================================
   // IsCellAbsorbedInJournal
   //==========================================================================================================================
   /**
   * @nodoc
   */
   CATBoolean IsCellAbsorbedInJournal(CATCell *piCell);

   //==========================================================================================================================
   // IsAllCellsDeletedInJournal
   //==========================================================================================================================
   /**
   * @nodoc
   */
   CATBoolean IsAllCellsDeletedInJournal(ListPOfCATCell &iListOfCells);

   //==========================================================================================================================
   // IsAllAdjCellsAbsorbed
   //==========================================================================================================================
   /**
   * @nodoc
   */
   CATBoolean IsAllAdjCellsAbsorbed(ListPOfCATCell &iListOfCells);   

   //==========================================================================================================================
   // InitHashTableOfReferencedCellsInJournal
   //==========================================================================================================================
private:
   /**
   * @nodoc
   */
   void InitHashTableOfReferencedCellsInJournal();

//==========================================================================================================================
   // MatchingByUsingGeometry
   //==========================================================================================================================
private:
   /**
   * @nodoc
   */
   void MatchingByUsingGeometry(CATCell *iOriginCell,ListPOfCATCell & iCommonCellList,ListPOfCATCell &ioNewCommonCellList);

   //==========================================================================================================================
   // FilterEquivalentCellsByUsingGeometry
   //==========================================================================================================================
private:
   /**
   * @nodoc
   */
   CATBoolean FilterEquivalentCellsByUsingGeometry(CATCell *iOriginCell,ListPOfCATCell& ioListOfEquivalentCells, CATBoolean iUseConfusion=FALSE);

   //==========================================================================================================================
   // GroupCellsBySupports
   //==========================================================================================================================
private:
   /**
   * @nodoc
   */
   void GroupCellsBySupports(ListPOfCATCell iListOfCells,ListPOfCATCell& oListOfGroupedCells,CATListOfInt& oListOfIndex);


   //==========================================================================================================================
   // EnableTrackingByUsingGeometry
   //==========================================================================================================================
private:
   /**
   * @nodoc
   */
   CATBoolean EnableTrackingByUsingGeometry();

   //==========================================================================================================================
   // Init
   //==========================================================================================================================
private:
   /**
   * @nodoc
   */
   void Init(CATSoftwareConfiguration * iSC          ,
             CATCGMJournalMode          iJournalMode ,
       const CATString                * iOperatorName);

   //==========================================================================================================================
   // DATA
   //==========================================================================================================================
private:

   CATLISTP(CATBody)             _ListOfOutputBody;
   CATLISTP(CATCGMJournal)       _ListOfCGMJournal;
   CATLISTP(CATCGMJournal)       _ListOfTassedCGMJournal;
   CATListOfInt                  _ListOfTassedCGMJournalToDelete;
   CATBoolean                    _TrackingWithTassedJournal;

   CATCGMHashTableWithAssoc    * _HashTableOfTargetBodiesWithItsCellHashTab;
   //CATListPV                   _ListOfCellTargetBodyWithHashTable; //_ListOfGetAllCellsOutputBody
   CATCGMHashTableWithAssoc    * _HashTabOfCellWithOriginCells;      // cellule et liste des cellules origines obtenu par FindFirst
   CATCGMHashTableWithAssoc    * _HashTabOfCellWithTargetCells;      // cellule et la liste des cellules origines obtenu par FindLast
   CATCGMHashTableWithAssoc    * _HashTabOfCellListOfNumberInfo;     // cellule et liste des valeurs des infos 
   CATCGMHashTableWithAssoc    * _HashTabOfCellListOfExistenceInfo;  // cellule et que la liste de présence ou nom des infos
   CATCellHashTable            * _HashTableOfCellsThatBorderedCellComputed;
   CATCGMHashTableWithAssoc   ** _TabOfHashTabOfEdgeWithItsIncidentFaces;


   //CATListPV                   _ListOfCellInputBodyWithHashTable;

   //CATListOfInt                _ListOfTargetBodyTag;
   //CATListOfInt                _ListIsLastJournalComputed;
   //CATListOfInt                _ListOfInputBodyTag;

   CATSoftwareConfiguration    * _SC;
   short                         _LevelToExecute;


   CATBoolean                    _IsMultiDimensionTrack;

   //Mode du journal utilisé (journal classique dit utilisateur CATCGMUserJournal ou journal complet CATCGMCompletJournal)
   CATCGMJournalMode             _JournalMode;
   const CATString             * _OperatorName; // Nom de l'opérateur appelant le cell tracker

   // if TRUE, Source_Cell --> List Image_Cell: ImageCell --> List Source Cell = Source_Cell de taille 1
   CATBoolean                    _IsStrictCorrespRequired; 
   // Used in CheckOutput
   //CATBoolean                  _UseLastJournalList;
      
    // 1 - Cas ou la cellule dont on cherche l'image ou la source est une edge et n'a pas de réponse par le journal alors
   // si les images des faces adjacentes sont toutes des edges => intersection entre les edges pour trouver le vertex origine de 
   // l'edge

   // 2 - Cas ou la cellule dont on cherche l'image ou la source est une edge et n'a pas de réponse par le journal alors
   // alors si les images des faces adjacentes sont un mélange d'edges et de face alors la relation d'adjacence 
   // entre deux faces devient une relation d'incidence entre une face et un edge si ces derniers sont leurs images par le CT
   CATBoolean                    _AllowTrackIfImageAdjFacesNotFaces; 

   // If a vertex have no image or source by computing his adj faces hence we allow search of the equivalent cell
   // by using its adjacent edges : This solution was proposed in the case of the extrusion. USe it carefully
   // It's a temporary solution.
   CATBoolean                    _AllowTrackVertexByAdjEdges; 
   CATBoolean                    _AllowTrackVertexByAdjEdgesIfNbAdjFacesEqualOne;

   CATBoolean                    _AllowTrackVertexIfIntersectionOfEquivFacesIsEmpty;

   // Particular option, to use with precaution: If it's value is true then in the case of computation of equivalent adjacent faces of 
   // a given cell (edge or vertex) this list own only one cell so we return this cell. Recall: before we compute the intersection between 
   // the equivalent adj faces to deduce the equiv cell but here there are no intersection because there are only one equiv cell
   // voir ODT CGMReplay_UnsmartGeometryChecker: CNEXT_004131_TopRevol.CGMReplay
   CATBoolean                    _SingleRespIfCardEquivAdjacFacesEqualOne;

   //Particular option, allow in case of looking for the equivalent cell of an edge to return a list of edges >1 if the passage
   // by vertices don't resolve ambiguity
   short                         _AllowMultipleRespIfAmbiguityPersist; // 0 : No, 1: Yes, 2: only when Geometry is shared
   
    //Particular option, allow to resolve ambiguity by using geometry pointed by cells  
   CATBoolean                   _AllowTrackByUsingGeometry;
   //Particular option, allow in case of looking for the equivalent cell of a vertex to return a list of vertices >1 when all 
   //equiv adj faces are faces. Exple intersection of a cylinder with a volumic ring generated when use the groove feature
   //In this case the resp of CT is 4 vertices. This exple is happened with the generated  boolean result and boolean report
   //after revol operation
   CATBoolean                   _AllowMultipleRespIfAmbiguityPersistForVertex;

   //Particular Option, allow to continue processing if the number of equiv adj faces are less the number of adj faces
   //It means that there one face which has not image or source by the journal. Possible interpretation the creation of 
   //this face has been reported in another journal for exple the boolean journal of a revol operator with a trim body.
   //As an example you can refer to the exemple refered in _AllowMultipleRespIfAmbiguityPersistForVertex option
   // 
   CATBoolean                  _AllowCardEquivAdjFacesInfThanCardAdjFaces;

   //Particular Option, to handle information lack in case of fillet and chmafer journal
   CATBoolean                  _AllowIntersectAdjFacesToFindCommonVertexInCaseOfEdge;

   // Ajout attributs pour perfo pour Hidden Seam
   CATCell                    * _pQueryCell; // cellule courante 
   ListPOfCATCell               _AdjacentFaceList; // liste des faces adjacentes à _pQueryCell dans le contexte d'un body
   ListPOfCATCell               _AdjacentEdgeList; // liste des faces adjacentes à _pQueryCell dans le contexte d'un body
   CATBody                    * _pQueryOriginBody; //Liste de 0 ou 1 qui indique dans quel body a été calculé _AdjacentFaceList
   CATBoolean                   _SpecialOptionForHSManager;
   // Option spéciale pour le HS Manager. Elle permet ds le cas particulier du HSManager pour
   //l'opération booléenne du prism ou du sweep de checker si une cellule de l'output body est restée smart 
   CATBoolean                   _CheckIfCellIsSmartInOutputBody;
   CATCellHashTable           * _HashTableOfOldCellsOfOutputBody;
   CATBody                    * _pCurrentTargetBody;
   CATCellHashTable           * _HashTableOfCellsOfCurrentTargetBody;
   CATLISTP(CATBody)            _ListOfAllBodies;
   CATListOfInt                 _ListOfDimOfAllBodies;
   CATCGMHashTableWithAssoc   * _HashTabOfAllBodies;
   CATCGMHashTableWithAssoc   * _HashTableOfCellsWithItsBorderedCells;
   CATCGMHashTableWithAssoc   * _HashTableOfFacesWithItsVertices;
   CATCGMHashTableWithAssoc   * _HashTableOfSmartCellsWithItsBody;
   CATBoolean                   _HasReferencedCellsInJournalComputed;
   //
   CATCellHashTable           * _HashTableOfReferencedInputCellsInJournal;
   CATCellHashTable           * _HTOfCreationInputCellsInJournal;
   CATCellHashTable           * _HTOfModificationInputCellsInJournal;
   CATCellHashTable           * _HTOfSubdivisionInputCellsInJournal;
   CATCellHashTable           * _HTOfAbsorptionInputCellsInJournal;
   CATCellHashTable           * _HTOfDeletionInputCellsInJournal;
   CATCellHashTable           * _HTOfKeepInputCellsInJournal;
   //
   CATCellHashTable           * _HashTableOfReferencedOutputCellsInJournal;
   //
   CATCellHashTable           * _HTOfCreationOutputCellsInJournal;
   CATCellHashTable           * _HTOfModificationOutputCellsInJournal;
   CATCellHashTable           * _HTOfSubdivisionOutputCellsInJournal;
   CATCellHashTable           * _HTOfAbsorptionOutputCellsInJournal;
   CATCellHashTable           * _HTOfDeletionOutputCellsInJournal;
   CATCellHashTable           * _HTOfKeepOutputCellsInJournal;
   CATCGMHashTableWithAssoc   * _HTOfOutputCellsInJournalWithInfo;
 //CATLISTP(CATBody)            _ListOfTargetBodies;

   //liste de hash table assoc pour chaque body.
   // Chaque hash tablestoque une cellule avec sa liste de cellule bords 
   //CATListPV                 _ListOfAssocHashTableOfCellsAndItsBorders;

   CATBoolean                  _PartialHashTabEdgesWithItsIncidFacesComputed;
   CATTopOperatorType          _KindOfOperator;
   short                       _RecursiveDepth;
   CATBoolean                  _IsQueryCellReferencedInJournal;
   CATBoolean                  _UseTassedJournal;
   //
   short                       _EnableTrackingByUsingGeometry;
   CATBoolean                  _OriginCellBelongToJournal;
};
#endif

