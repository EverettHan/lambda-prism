#ifndef CATPAD_h
#define CATPAD_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
//
// PAD compares two bodies, or two sets of cells, to determine the 
// differences between them with the minimum of comparison.
// PAD means Persistent, Appeared, Disappeared.
// Thus, the comparison distinguishes the Topologies (pointers sense)
// (Cells or Domains) which are 
//  - Persistent  (in both inputs); 
//  - Appeared    (only in the second input, the New one);
//  - Disappeared (only in the first  input, the Old one);
//==========================================================================
// Nov. 09  Creation                                                     JJ3
// Oct. 11  Complete redesign                                            WQO
//==========================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATMathInline.h"
#include "CATBoolean.h"
#include "CATTopDefine.h"
#include "CATListOfCATCells.h"

class CATTopology;
class CATCell;
class CATFace;
class CATBody;
class CATAdaptiveHashTable;
class CATCGMHashTableWithAssoc;
class CATCXSmartBodyDuplicator;
class CATCXTopology;
class HashTableAssocList;

typedef enum
{
  Persistent  =  0, // in both inputs
  Appeared    =  1, // only in the second input, the New one
  Disappeared = -1  // only in the first  input, the Old one
} 
CATPAD_ComparisonType;

typedef enum
{
  Vertex         =  1, // cell
  VertexInFace   =  2, // domain
  VertexInVolume =  3, // domain
  Edge           =  4, // cell
  Loop           =  5, // domain
  Wire           =  6, // domain
  Face           =  7, // cell
  Shell          =  8, // domain
  Volume         =  9, // cell
  Lump           = 10, // domain
  Body           = 11, // body
  All            = 12  // all previous cells and domains
} 
CATPAD_TopologyType;

// Generic way to store informations
struct PAD_HTablesOfTopologies
{
  // Working tables
  CATAdaptiveHashTable * pOldTopolgies ;
  CATAdaptiveHashTable * pNewTopolgies ;
  // Resulting tables
  CATAdaptiveHashTable * pPersistent   ;
  CATAdaptiveHashTable * pAppeared     ;
  CATAdaptiveHashTable * pDisappeared  ;
  // Maximum size estimation used to allocate
  int EstimationOfSize;
  CATPAD_TopologyType MyType;
  CATBoolean IsDomain;
  // Constructor
  PAD_HTablesOfTopologies();
  // To put all the internal pointers to null (cleaning the table if needed)
  void InitOrReset(CATPAD_TopologyType iMyType = All);
  // To access to HTable according to type (P, A, or D)
  INLINE const CATAdaptiveHashTable * GetTopoTable(CATPAD_ComparisonType iComparisonType);
  // To insert the given topology in Old or New working HTable (creating it if needed)
  void InsertInWorkingHTable(CATPAD_ComparisonType iInputType, CATTopology * ipTopology);

  void IntegrateInResultHTable(PAD_HTablesOfTopologies *ipPAD_HTable);

  void AllocatingEstimation(CATTopology         * ipTopology     ,
                            CATPAD_TopologyType   iTopologyType  , 
                            CATBoolean            iIsDomainLevel );

  void AllocatingEstimation(const CATAdaptiveHashTable * ipTopologyTable, 
                            CATPAD_TopologyType    iTopologyType,
                            CATBoolean             iIsDomainLevel);

  void AllocatingEstimation(PAD_HTablesOfTopologies * ipPAD_HTablesOfTopologies);

  int ExpandTopology(CATTopology             * ipTopology, 
                     PAD_HTablesOfTopologies * iopExpandedPAD_HTable,
                     CATTopology             * ipTargetTopology = NULL);

  int ExpandTopology(const CATAdaptiveHashTable    * iHashTablePOfTopology, 
                     CATPAD_TopologyType       iTopologyType, 
                     PAD_HTablesOfTopologies * ioExpandedPAD_HTable,
                     CATTopology             * ipTargetTopology = NULL);

  int ExpandTopology(PAD_HTablesOfTopologies * ipPAD_HTables, 
                     PAD_HTablesOfTopologies * iopExpandedPAD_HTable,
                     CATTopology             * ipTargetTopology = NULL);

  void TreatWorkingHTable();
};

class ExportedByCATTopologicalObjects CATPAD
{
public:
  // Default constructor
  CATPAD();
  // To compare two Bodies
  CATPAD(CATBody * ipOldBody, CATBody * ipNewBody);
  // To compare two lists of cells
  CATPAD(CATLISTP(CATCell) & iOldCellsList, CATLISTP(CATCell) & iNewCellsList);
  // Destructor
  virtual ~CATPAD();

  //----------------------------------------------------------------------
  // To process comparison
  //----------------------------------------------------------------------
  // To give the inputs topology to compare
  void SetOldBody(CATBody * ipOldBody);
  void SetNewBody(CATBody * ipNewBody);
  void SetCellInOldCellsList(CATCell * iOldCell);
  void SetCellInNewCellsList(CATCell * iNewCell);
  void SetOldCellsList(CATLISTP(CATCell) & iOldCellsList);
  void SetNewCellsList(CATLISTP(CATCell) & iNewCellsList);
  // The Run can be called several times to complete the diagnostic
  // (for example if the DimToGo has changed)
  void Run();

  //----------------------------------------------------------------------
  // Options of the comparison
  //----------------------------------------------------------------------
  // Lowest dimension of cells which are compared (0-Vertex, 1-Edge, 2-Face, 3-Volume)
  void SetDimensionToGo(int iDimension);
  void SetTypeToGo(int iTypeToGo);
  // To not take into account the Face orientation in the shell (Persistent if same orientation)
  // (must be set before the first Run called with a dimension to go inferior or equal to 2/Face)
  void SetNoFaceOrientationsComparison();
  // To forbid automatic re-Run, when the comparison is insufficient, and multiple Run call
  void SetNoAutomaticReRun(CATBoolean iNoReRun = TRUE);
  // To not consider all duplicated topology as removed of the PAD 
  // (which means Is"P, A or D"() gives the same answer for Original and Duplicate)
  void SetNoConsiderDuplicatedAsRemoved(CATBoolean iNoConsider = TRUE);

  //----------------------------------------------------------------------
  // Diagnostics of the comparison 
  // /!\ Can apply a Re-Run if comparison with previous options are not 
  //     sufficient, or a default result (FALSE) in the NoAutomaticReRun mode
  // /!\ By default, the answer is always FALSE 
  //     (example: the given topology is not in the inputs of the PAD)
  //----------------------------------------------------------------------
  // Is it a persistent topology ?
  INLINE CATBoolean IsPersistent (CATTopology * ipTopoObj);
  // Is it a appeared topology ?
  INLINE CATBoolean IsAppeared   (CATTopology * ipTopoObj);
  // Is it a disappeared topology ?
  INLINE CATBoolean IsDisappeared(CATTopology * ipTopoObj);
  // Is it a persistent, appeared or disappeared topology ?
  INLINE CATBoolean IsAnything(CATTopology * ipTopoObj);
  // Is there a not persistent cell, of the given dimension, which has been found ?
  CATBoolean IsThereNotPersistentCell(int iDimension = 0);
  // Is there a not persistent domain, of the highest dimensions, which has been found ?
  CATBoolean IsThereNotPersistentDomainOfHighestDimensions();
  // Which is the orientation of the face in its shell ? +, - or ?
  // if the option to take into account the face orientation is not set, the default return is ?
  // if the face is + in one shell and - in anoter, the default return is +
  // the orientation is in the Old Body or the New Body's shell(s) according to iInOldBody value
  CATOrientation GetOrientationInShell(CATFace * ipFace, CATBoolean iInOldBody = TRUE);

  //----------------------------------------------------------------------
  // To look through the topologies which have been compared 
  // /!\ See also the corresponding macros below
  //----------------------------------------------------------------------
  // To access to the inputs topology
  INLINE const CATBody * GetOldBody() { return _pOldBody; };
  INLINE const CATBody * GetNewBody() { return _pNewBody; };
  INLINE const CATLISTP(CATCell) & GetOldCellsList() { return _OldCellsList; };
  INLINE const CATLISTP(CATCell) & GetNewCellsList() { return _NewCellsList; };
  // Which is the actual lowest level dimension of comparison ?
  INLINE int GetGoneDimension() { return this->ConvertTopologyTypeToDimension(_StoredTypeToGo); };
  // To know how many topology are P, A, or D (ComparisonType)
  // (No automatic Re-Run will be called, example: if DimToGo > iTopologyType, it returns 0)
  int GetNbElements( CATPAD_ComparisonType iComparisonType , 
                     CATPAD_TopologyType   iTopologyType   ); 
  // To access to the i-th topology ( 0 <= Index < NbElements )
  // (No automatic Re-Run will be called, example: if DimToGo > iTopologyType, it returns 0)
  CATTopology * GetIthElement( int                   iIndex             ,
                               CATPAD_ComparisonType iComparisonType    , 
                               CATPAD_TopologyType   iTopologyType      ,
                               CATBoolean            iDuplicate = TRUE ); 

  //----------------------------------------------------------------------
  // To integrate changes in the compared input topologies 
  //----------------------------------------------------------------------
  // To substitute topologies which have been duplicated
  void IntegrateDuplication(CATCXTopology* pCXOriginalObject, CATCXTopology* pCXDuplicateObject, int iEstimatedNbDuplications);

  void IntegrateDuplication(CATCXSmartBodyDuplicator * ipDuplicator);

  // To access to original topologies which have been duplicated with the duplicate as Assoc
  INLINE const CATCGMHashTableWithAssoc * GetTableOfOriginalTopologies ()
    { return _pTableOfOriginalTopologies ; };
  // To access to topologies resulting of a duplication with the original one as Assoc
  INLINE const CATCGMHashTableWithAssoc * GetTableOfDuplicateTopologies()
    { return _pTableOfDuplicateTopologies; };

  // To translate according to duplication
  CATTopology * GetDuplicate(CATTopology * ipOriginal );
  CATTopology * GetOriginal (CATTopology * ipDuplicate);

  CATBoolean IsOriginal(CATTopology * ipTopoObj);
  // for debug : stream of result
  void StreamResult(CATCGMOutput & CurStream);


  /**
  * @brief: 2020-01-15 QCN5
  *         Expand only the faces with support in ipSurfaces 
  *         Used in CATSubdContextForFastRunExt, ipSurfaces are calculated
  *         based on links(edges) and vertices from CATSubdFaceNavigator 
  *
  * @param: ipSurfaces - Support faces
  */
  void ExpandFacesAccordingToSurfaces(CATAdaptiveHashTable * ipSurfaces);

  INLINE int GetStoredTypeToGo();
private:
  //----------------------------------------------------------------------
  // Internal services 
  //----------------------------------------------------------------------
  // To put all the internal pointers to null 
  void InitPointers();
  // To clean the table if needed and to put the flags to their default values
  void InitOrResetData();
  // To treat one level of Working HTable in filling P, A and D HTable
  void TreatWorkingHTable(CATPAD_TopologyType iTopologyType);
  // To estimate the size of tables for lower dimensions which will be filled by expanding the given level
  void AllocatingEstimation(CATPAD_TopologyType iTopologyType);
  // To estimate the size of tables for lower dimensions which will be filled by expanding the given topology
  void AllocatingEstimation(CATPAD_ComparisonType iComparisonType,
                            CATPAD_TopologyType   iTopologyType  , 
                            CATTopology         * ipTopology     ,
                            CATBoolean            iIsDomainLevel );
  // To fill all the inferior Working HTables in expanding the given level
  void ExpandWorkingHTable(CATPAD_TopologyType iTopologyType);
  // To fill the inferior Working HTables in expanding the given topology
  void ExpandInWorkingHTable(CATPAD_ComparisonType iComparisonType,
                             CATPAD_TopologyType   iTopologyType  , 
                             CATTopology         * ipTopology     ,
                             CATBoolean            iIsDomainLevel );
  // To insert each cells of the list in the corresponding struct
  void InsertInWorkingHTable(CATPAD_ComparisonType iInputType, CATLISTP(CATCell) & CellsList);
  // To convert type and dimension according to:
  // | Type | Vtx  | ViF  | ViV  | Edge | Loop | Wire | Face | Shel | Volu | Lump | Body | All  |
  // | Lvl  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |  10  |  11  |  12  |
  // | LDim |   0  |   0  |   0  |   1  |   1  |   1  |   2  |   2  |   3  |   3  |   4  |   4  |
  // | HDim |   0  |   2  |   3  |   1  |   2  | 3-4  |   2  | 3-4  |   3  |   4  |   4  |   -  |
  INLINE int ConvertTopologyTypeToInt(int iTopologyType);
  INLINE int ConvertTopologyTypeToDimension(int iTopologyType);
  INLINE CATPAD_TopologyType ConvertIntToTopologyType(int iLevel);
  // Which type (P, A or D) of topology is it ?
  CATBoolean Is(CATPAD_ComparisonType iComparisonType, 
                CATTopology         * ipTopoObj      ,
                CATBoolean            ReRunIfNeeded = TRUE);
  CATBoolean IsOriginal(CATPAD_ComparisonType iComparisonType, 
                        CATTopology         * ipTopoObj      ,
                        CATBoolean            ReRunIfNeeded = TRUE);

  //----------------------------------------------------------------------
  // Initial input data
  //----------------------------------------------------------------------
  CATBody           * _pOldBody;
  CATBody           * _pNewBody;
  CATLISTP(CATCell)   _OldCellsList;
  CATLISTP(CATCell)   _NewCellsList;

  //----------------------------------------------------------------------
  // Internal HTable data
  //----------------------------------------------------------------------
  // One for each topological type
  PAD_HTablesOfTopologies
    _Vertices         ,
    _VerticesInFace   ,
    _VerticesInVolume ,
    _Edges            ,
    _Loops            ,
    _Wires            ,
    _Faces            ,
    _Shells           ,
    _Volumes          ,
    _Lumps            ,
    _Bodies           ;
  // Faces orientations, we stored which ones have a positive orientation in their shell
  CATAdaptiveHashTable * _pOldPositiveFaces;
  CATAdaptiveHashTable * _pNewPositiveFaces;
  // All topologies regrouped in one Table per type (P, A, or D)
  CATAdaptiveHashTable * _pAllPersistent   ;
  CATAdaptiveHashTable * _pAllAppeared     ;
  CATAdaptiveHashTable * _pAllDisappeared  ;
  // Table of original topologies which have been duplicated with the duplicate as Assoc
  CATCGMHashTableWithAssoc * _pTableOfOriginalTopologies ;
  // Table of topologies resulting of a duplication with the original one as Assoc
  CATCGMHashTableWithAssoc * _pTableOfDuplicateTopologies;
  HashTableAssocList *_pSurfaceToFaces;

  //----------------------------------------------------------------------
  // Internal access 
  //----------------------------------------------------------------------
  // Service to access to previous struct according to type
  INLINE PAD_HTablesOfTopologies & GetTopoStruct(CATPAD_TopologyType iTopologyType);
  // Service to access to the table regrouping all topologies contained in structs
  const CATAdaptiveHashTable * GetAll(CATPAD_ComparisonType iComparisonType);
  // Service to fill the table regrouping all topologies contained in structs
  void FillTableOfAll(CATPAD_ComparisonType iComparisonType);
  void FillTableOfAll(PAD_HTablesOfTopologies* StructTable);

  //----------------------------------------------------------------------
  // Flags and Dimension data
  //----------------------------------------------------------------------
  // Number of call of the Run
  unsigned int _NbRun                    ;
  // Minimum dimension which is necessary to diagnose if all first level cells are Persistent
  int _MinimumDimToDiagPersistency       ;
  // Minimum dimension, given by user, 0 by default, of cells which will be compared
  int _GivenTypeToGo                     ;
  // Minimum dimension, stored at the end of the run, of cells which have been compared
  int _StoredTypeToGo               ;
  // To take into account the Face orientation in the shell (Persistent if same orientation)
  CATBoolean _FaceOrientationsComparison ;
  // To automatically re-Run when the comparison is insufficient
  CATBoolean _AutomaticReRun             ;
  // To consider all duplicated topology as removed of the PAD (which means Is() always says FALSE)
  CATBoolean _ConsiderDuplicatedAsRemoved;
};

//----------------------------------------------------------------------
// Macros to look through the topologies table
//----------------------------------------------------------------------
// Arguments are the CATPAD object, the types and the current topology pointer of the loop
// ex: CATPAD_Table_Begin( PADobject, Persistent, Edge, pCurrTopoObject)
//       pCurrTopoObject->Action();
//     CATPAD_Table_End;
#define CATPAD_Table_Begin(CATPAD, ComparisonType, TopologyType, pCurrTopo)                           \
{                                                                                                     \
  int __##pCurrTopo##Index;                                                                           \
  int __##pCurrTopo##Size = (CATPAD).GetNbElements(ComparisonType, TopologyType);                     \
  for (__##pCurrTopo##Index = 0; __##pCurrTopo##Index < __##pCurrTopo##Size; __##pCurrTopo##Index ++) \
  {                                                                                                   \
    CATTopology * pCurrTopo =                                                                         \
      (CATPAD).GetIthElement(__##pCurrTopo##Index, ComparisonType, TopologyType, TRUE);               \
    if (pCurrTopo != NULL)                                                                            \
    {
// To make the cast of the returned topology
#define CATPAD_Table_Begin_WithCast(CATPAD, ComparisonType, TopologyType, pCurrTopo, CastType)        \
{                                                                                                     \
  int __##pCurrTopo##Index;                                                                           \
  int __##pCurrTopo##Size = (CATPAD).GetNbElements(ComparisonType, TopologyType);                     \
  for (__##pCurrTopo##Index = 0; __##pCurrTopo##Index < __##pCurrTopo##Size; __##pCurrTopo##Index ++) \
  {                                                                                                   \
    CastType pCurrTopo = (CastType)                                                                   \
      (CATPAD).GetIthElement(__##pCurrTopo##Index, ComparisonType, TopologyType, TRUE);               \
    if (pCurrTopo != NULL)                                                                            \
    {
// To look through the topologies table without translating in case of duplication
#define CATPAD_Table_Begin_WithoutDuplicate(CATPAD, ComparisonType, TopologyType, pCurrTopo)          \
{                                                                                                     \
  int __##pCurrTopo##Index;                                                                           \
  int __##pCurrTopo##Size = (CATPAD).GetNbElements(ComparisonType, TopologyType);                     \
  for (__##pCurrTopo##Index = 0; __##pCurrTopo##Index < __##pCurrTopo##Size; __##pCurrTopo##Index ++) \
  {                                                                                                   \
    CATTopology * pCurrTopo =                                                                         \
      (CATPAD).GetIthElement(__##pCurrTopo##Index, ComparisonType, TopologyType, FALSE);              \
    if (pCurrTopo != NULL)                                                                            \
    {

#define CATPAD_Table_End                                                                              \
    }                                                                                                 \
  }                                                                                                   \
}

//----------------------------------------------------------------------
// Service to access to struct according to topological type
//----------------------------------------------------------------------
INLINE PAD_HTablesOfTopologies & CATPAD::GetTopoStruct(CATPAD_TopologyType iTopologyType)
{
  switch (iTopologyType)
  {
  case Vertex        : return _Vertices        ;
  case VertexInFace  : return _VerticesInFace  ;
  case VertexInVolume: return _VerticesInVolume;
  case Edge          : return _Edges           ;
  case Loop          : return _Loops           ;
  case Wire          : return _Wires           ;
  case Face          : return _Faces           ;
  case Shell         : return _Shells          ;
  case Volume        : return _Volumes         ;
  case Lump          : return _Lumps           ;
  case Body          : return _Bodies          ;
  default            : break                   ;
  }
  //CATThrowForNullPointerReturnValue(_Bodies); // invalid type
  return _Bodies;
}
//----------------------------------------------------------------------
// To access to HTable according to type (P, A, or D)
//----------------------------------------------------------------------
INLINE const CATAdaptiveHashTable * PAD_HTablesOfTopologies::GetTopoTable(CATPAD_ComparisonType iComparisonType)
{
  const CATAdaptiveHashTable * pCurrTable = NULL;
  
  switch (iComparisonType)
  {
  case Persistent:  pCurrTable = pPersistent ; break;
  case Appeared:    pCurrTable = pAppeared   ; break;
  case Disappeared: pCurrTable = pDisappeared; break;
  default: //CATThrowForNullPointerReturnValue(pCurrTable); // invalid type
    break;
  }

  return pCurrTable;
}
//----------------------------------------------------------------------
// To convert type and dimension according to:
// | Type | Vtx  | ViF  | ViV  | Edge | Loop | Wire | Face | Shel | Volu | Lump | Body | All  |
// | Lvl  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |  10  |  11  |  12  |
// | LDim |   0  |   0  |   0  |   1  |   1  |   1  |   2  |   2  |   3  |   3  |   4  |   4  |
// | HDim |   0  |   2  |   3  |   1  |   2  | 3-4  |   2  | 3-4  |   3  |   4  |   4  |   -  |
//----------------------------------------------------------------------
INLINE int CATPAD::ConvertTopologyTypeToInt(int iTopologyType)
{
  int Level = -1;

  switch (iTopologyType)
  {
  case Vertex        : Level =  1; break;
  case VertexInFace  : Level =  2; break;
  case VertexInVolume: Level =  3; break;
  case Edge          : Level =  4; break;
  case Loop          : Level =  5; break;
  case Wire          : Level =  6; break;
  case Face          : Level =  7; break;
  case Shell         : Level =  8; break;
  case Volume        : Level =  9; break;
  case Lump          : Level = 10; break;
  case Body          : Level = 11; break;
  case All           : Level = 12; break;
  default: //CATThrowForNullPointerReturnValue(Level); // invalid type
    break;
  }

  return Level;
}
INLINE int CATPAD::ConvertTopologyTypeToDimension(int iTopologyType)
{
  int Dim = -1;

  switch (iTopologyType)
  {
  case Vertex        :
  case VertexInFace  :
  case VertexInVolume: Dim = 0; break;
  case Edge          :
  case Loop          :
  case Wire          : Dim = 1; break;
  case Face          :
  case Shell         : Dim = 2; break;
  case Volume        :
  case Lump          : Dim = 3; break;
  case Body          :
  case All           : Dim = 4; break;
  default: //CATThrowForNullPointerReturnValue(Dim); // invalid type
    break;
  }

  return Dim;
}
INLINE CATPAD_TopologyType CATPAD::ConvertIntToTopologyType(int iLevel)
{
  CATPAD_TopologyType Type = All;

  switch (iLevel)
  {
  case  1: Type = Vertex        ; break;
  case  2: Type = VertexInFace  ; break;
  case  3: Type = VertexInVolume; break;
  case  4: Type = Edge          ; break;
  case  5: Type = Loop          ; break;
  case  6: Type = Wire          ; break;
  case  7: Type = Face          ; break;
  case  8: Type = Shell         ; break;
  case  9: Type = Volume        ; break;
  case 10: Type = Lump          ; break;
  case 11: Type = Body          ; break;
  case 12: Type = All           ; break;
  default: //CATThrowForNullPointerReturnValue(Type); // invalid level
    break;
  }

  return Type;
}
INLINE CATPAD_TopologyType ConvertDimensionToTopologyType(int iLowDimension, int iHighDimension)
{
  CATPAD_TopologyType Type = All;

  switch (iLowDimension)
  {
  case 0:
    {
      switch (iHighDimension)
      {
      case 0: Type = Vertex        ; break;
      case 2: Type = VertexInFace  ; break;
      case 3: Type = VertexInVolume; break;
      }
    } break;
  case 1:
    {
      switch (iHighDimension)
      {
      case 1: Type = Edge          ; break;
      case 2: Type = Loop          ; break;
      case 3:
      case 4: Type = Wire          ; break;
      }
    } break;
  case 2:
    {
      switch (iHighDimension)
      {
      case 2: Type = Face          ; break;
      case 3:
      case 4: Type = Shell         ; break;
      }
    } break;
  case 3:
    {
      switch (iHighDimension)
      {
      case 3: Type = Volume        ; break;
      case 4: Type = Lump          ; break;
      }
    } break;
  case 4:
    {
      switch (iHighDimension)
      {
      case 4: Type = Body          ; break;
      }
    } break;
  }

//  if (Type == All)
//    CATThrowForNullPointerReturnValue(Type); // invalid dimensions (All being the default value)

  return Type;
}
//----------------------------------------------------------------------
// To know if it is a Domain type
//----------------------------------------------------------------------
INLINE CATBoolean IsDomainLevel(CATPAD_TopologyType iTopologyType)
{
  CATBoolean IsDomainLevel = FALSE;

  switch (iTopologyType)
  {
  case VertexInFace  :
  case VertexInVolume:
  case Loop          :
  case Wire          :
  case Shell         :
  case Lump          : IsDomainLevel = TRUE ; break;
  case Vertex        :
  case Edge          :
  case Face          :
  case Volume        :
  case Body          : //IsDomainLevel = FALSE; break;
  case All           : 
  default: //CATThrowForNullPointerReturnValue(IsDomainLevel); // invalid type
    break;
  }

  return IsDomainLevel;
}
//----------------------------------------------------------------------
// Is it a persistent topology ?
//----------------------------------------------------------------------
INLINE CATBoolean CATPAD::IsPersistent (CATTopology * ipTopoObj)
{
  return this->Is(Persistent , ipTopoObj, _AutomaticReRun);
}
//----------------------------------------------------------------------
// Is it a appeared topology ?
//----------------------------------------------------------------------
INLINE CATBoolean CATPAD::IsAppeared   (CATTopology * ipTopoObj)
{
  return this->Is(Appeared   , ipTopoObj, _AutomaticReRun);
}
//----------------------------------------------------------------------
// Is it a disappeared topology ?
//----------------------------------------------------------------------
INLINE CATBoolean CATPAD::IsDisappeared(CATTopology * ipTopoObj)
{
  return this->Is(Disappeared, ipTopoObj, _AutomaticReRun);
}

//----------------------------------------------------------------------
// Is it a persistent, appeared or disappeared topology ?
//----------------------------------------------------------------------

INLINE CATBoolean CATPAD::IsAnything(CATTopology * ipTopoObj)
{
  CATBoolean Result = FALSE;
  Result |= this->IsPersistent(ipTopoObj);
  Result |= this->IsAppeared(ipTopoObj);
  Result |= this->IsDisappeared(ipTopoObj);
  return Result;
}

INLINE int CATPAD::GetStoredTypeToGo()
{
  return _StoredTypeToGo;
}

#endif


