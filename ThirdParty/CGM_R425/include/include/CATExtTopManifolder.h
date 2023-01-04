#ifndef CATExtTopManifolder_h_
#define CATExtTopManifolder_h_

// #define  _UseOldManifolder // Retour arrière sur modifs manifolder 

#include "CATIACGMLevel.h" // automatic treatment EB_2014_04_16
#include "ExportedByCATTopologicalObjects.h"
#include "CATExtTopMultiResult.h"
#include "CATTopManifolder.h"
#include "CATListOfCATCGMJournals.h"
#include "CATBoolean.h"
#include "CATString.h"

class CATTopology;
class CATTopObject;
class CATCell;
class CATDomain;
class CATLISTP(CATCell);
class CATLISTP(CATDomain);
class CATVertex;
class CATFace;
class CATLump;
class CATShell;
class CATTopBooleanOperator;
class CATVolume;

class CATCXLump;
class CATCXShell;
class CATCXDomain;
class CATCXVolume;
class CATCXBody;
class CATSubdBoundingFace;
class CATTopData;
class CATGeoFactory;
class CATFullLoopData;
class CATSubdArrayVertexP;
class CATSubdArrayCXDomainP;
class CATSubdArrayFullDomDataP;

class ExportedByCATTopologicalObjects CATExtTopManifolder : public CATExtTopMultiResult
{
   
   friend class CATTopManifolderCGM;
   
   
public:
   
   //-------------------------------------------------------------------------------------------------------
   // Constructeur 
   //   iOperateur peut etre NULL,  mais ca doit etre reserver au cas tres particuliers sous constructeur
   //   il faut dans ce cas s'empresser de retablir la definition avec la methode SetOperator
   //-------------------------------------------------------------------------------------------------------
   CATExtTopManifolder(CATGeoFactory* iFactory, CATTopData* iData, CATBody* iBody, CATTopManifolder* iOperateur = NULL);
   
   // Destructor
   virtual ~CATExtTopManifolder();

   //-------------------------------------------------------------------------------------------------------
   // Surcharge du new/delete
   //-------------------------------------------------------------------------------------------------------
   CATCGMNewClassArrayDeclare;
  
   //=========================================================
   //    Methods  
   //=========================================================
   int  Run();         //  Execution  of  the  operator

   CATBoolean IsInputManifold();

   // Renvoie le nombre de cellules Full dans iObject
   CATLONG32  RetrieveFullCells( CATTopology * iTopo, CATLISTP(CATCell) * oFullCells, CATLISTP(CATCell) * oIsolatedFull = NULL );

   //========================================================
   // GetResult: returns the resulting body
   //========================================================
   // virtual CATLISTP(CATBody) GetResult();
	
	 // virtual CATBody * GetMainBodyResult();

   // virtual CATBody * GetWireBody();

   /**  @nodoc  CATCGMReplay  ...*/  
   static  const  CATString  *  GetDefaultOperatorId()  {  return  &  _OperatorId;  };  

   /**  @nodoc  Journal Complet  ...*/  
   //=================================
   void SetAllCellsJournalExpected(int iAllCellsExpected=0 );
   // 1 = journal complet
   // 0 = fonctionnement normal
   //=================================

   void SetVolumeJournalling(int iVolumeJournalling) { _VolumeJournalling = iVolumeJournalling; };
   int GetVolumeJournalling() { return _VolumeJournalling; };
   
protected :

   /**  @nodoc  CATCGMReplay  ...*/  
   const  CATString  *  GetOperatorId()  const;  

   /**  @nodoc  CATCGMReplay  ...*/  
   // CATExtCGMReplay  *   IsRecordable(short  &  LevelOfRuntime,  short  &VersionOfStream);  

   /**  @nodoc  CATCGMReplay  ...*/  
   int  RunOperator();

   void RequireDefinitionOfInputAndOutputObjects();
  //================================================================================
   //                      Données membres protégées
   //================================================================================
   // InputData
   CATBody                 * _InputBody;    // the Original Body

   // OutputDatas
   CATLISTP(CATBody)       * _ResultBodies;    // list of the bodies created to isolate non-manifold items
   CATCGMJournalList      ** _ResultReportsTab;   // table of the Reports linked to each of the created bodies

   CATLISTP(CATCell)       * _FullCells;       // Liste des cellules Full.

   
    int   _AllCellsExpected; 
#ifdef CATIACGMV5R20
  CATCGMJournalList * _CompletedJournal; //celltrack
#endif

private:

  static  CATString  _OperatorId;

  ///////////////////////////////////////////////////////////////////////////////
  /////
  /////     Old manifolder methods
  /////

  CATLONG32  FillFullCells(CATLISTP(CATCell)* iOD1DFullFreeCells);
  CATBoolean IsVertexBoardingFace( CATVertex * iVertex, CATFace * iFace);
  void       RetrieveInternsVerticesAndFullCuttingEdges( CATFace * iFace, CATLISTP(CATCell) & oVerticesAndCuttingEdges );
  void       RetrieveHLCellsLinkedByFull( CATTopObject * iObject, CATLISTP(CATCell) * oHLCells);
  void       RetrieveHLCellsContainingCell( CATCell * iCell, CATLISTP(CATCell) * oCells, short iDimension = -1);
  void       ClassifyHLDomains(CATBoolean iHasFull);
  void       ClassifyLump   (CATLump  * iLump);
  void       ClassifyHLShell(CATShell * iShell);

  void       BuildReports(CATCGMJournalList * iReferenceReport);
  void       FillResultReports_Old(CATCGMJournalList * iReferenceReport);

  void        AddCellsToIsolate(CATDomain * iContainingShell, CATLISTP(CATCell) * iCellsToAdd);
  CATVolume * ManifoldiseVolume( CATVolume * iVolume, CATBody * iBodyCreation, CATTopBooleanOperator * iOperator);
  void        Manifoldise_OldAlgo(CATCGMJournalList * OpJournal, CATLISTP(CATCell)* iOD1DFullFreeCells);
  
  /////
  /////     Old manifolder methods
  /////
  ///////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////
  /////
  /////     New manifolder methods
  /////

  void                  DeclareInvaliditiesToExpect();

  void                  Manifoldise_NewAlgo(CATCGMJournalList * OpJournal);
  void                  SmartDupliAndUpdateFullDomData(CATTopData* ipTopData);

  void                  FillResultReports_New(CATCGMJournalList * iReferenceReport);
  void                  ComputeOriginCells(
                          CATCell               * ipCellToComputeCreate,        CATListPtrCATGeometry  &ioOriginGeoms,
                    const CATListPtrCATGeometry  &iInputTrackedFreeCells, const CATListPtrCATCell      &iResultAllTrackedCells,
                          CATCGMJournalList     * ipJournalSmartif);
  static CATCell*       SearchCellDupliItem_AndWriteItInJournal(
                          CATCell                 * ipNewCell,        CATBoolean                iSearchOrigin,    // if !iSearchOrigin, we'll search for result
                          CATCGMJournalList       * ipSmartifReport,  CATCGMJournalList       * ipNewReportToUpdate,
                          CATListPtrCATGeometry    &oBeforeList,      CATListPtrCATGeometry    &oAfterList);

  static void           TopToolsRebuildDomains(CATBody* iopBody, CATTopData* ipData, CATGeoFactory* ipFactory);
  static CATBody*       CreateOneBodyForCells(CATGeoFactory* ipFactory, CATTopData* ipTopData, const CATListPtrCATCell &iListOfCells, int iOriForFirstCell = 2);
  void                  FindOwnerCellsAndDoms(CATBody* ipBody, CATCell * iCell, CATListPtrCATCell* opCells, CATListPtrCATDomain* opDoms, short iStopDimension);
  
  /*
   * Breaks the link between a Face and its Shell (it should only be called on surfacic faces that have only one shell)
   * and returns the orientation of the face vs. that shell
   */
  static int            UnlinkFaceFromSrcShell(CATGeoFactory* ipFactory, CATSubdBoundingFace* ipFaceToMove, CATCXBody* ipSrcBody);

  // Scans a body searching for full domains
  // And record their complete data (FullDomData) in _pDuplicatedFullShells, _pDuplicatedFullEdgeDoms, _pDuplicatedFullVerticesDoms
  void                  RegisterFullDomains(CATCXBody* ipCXBody);
  void                  RegisterFullDomains_InLump(CATCXLump* ipCXLump);
  void                  RegisterFullDomains_InShell(CATCXShell* ipCXShell, CATCXVolume* ipCXVolOwner = NULL, CATCXLump* ipCXLumpOfVol = NULL);

  /////
  /////     New manifolder methods
  /////
  ///////////////////////////////////////////////////////////////////////////////

//================================================================================
//                      Données membres privées
//================================================================================

  // WorkingDatas
   CATBody                 * _MainBody;         // Body principal portant les domaines manifolds
   
   CATBoolean                _IsInputManifold; // 0 si InputBody est non manifold
                                               // 1 si InputBody déjà manifold


  ///////////////////////////////////////////////////////////////////////////////
  /////
  /////     Old manifolder data
  /////

   CATLISTP(CATCell)       * _OD1DFreeCells;    // Liste des cellules Full liées à une unique face et à reporter dans un nouveau body.
   CATListOfInt              _OD1DFreeCellsOri; // Liste des orientations des cellules 0D1D

   CATLISTP(CATDomain)     * _DomainsToTreat;   // Liste des Domains à traiter sans isolation.
   CATLISTP(CATDomain)     * _DomainsToIsolate; // Liste des Domains à isoler
   // CATLISTP(CATVolume)     * _VolumesToIsolate;
   // CATLISTP(CATLump)       * _LumpsToIsolate;

   CATLISTP(CATDomain)     * _DomainsWithCellsToIsolate; // Shells contenant des faces à isoler
   CATLISTP(CATCell)      ** _CellsListOfLists;          // Liste de listes de faces à isoler: 
                                                        //   _FacesListOfLists[i] contient les faces de _ShellsWithFacesToIsolate à isoler
   CATLONG32                 _NbListsOfCells;
   CATLONG32                 _maxNbOfLists;

  /////
  /////     Old manifolder data
  /////
  ///////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////
  /////
  /////     New manifolder data
  /////

  CATSubdArrayVertexP         * _pArraySubdOfInputVIFs;

  CATSubdArrayFullDomDataP    * _pDuplicatedFullShells;
  CATSubdArrayFullDomDataP    * _pDuplicatedFullEdgeDoms;
  CATSubdArrayFullDomDataP    * _pDuplicatedFullVerticesDoms;

  int _VolumeJournalling;

  /////
  /////     New manifolder data
  /////
  ///////////////////////////////////////////////////////////////////////////////

};

#endif
