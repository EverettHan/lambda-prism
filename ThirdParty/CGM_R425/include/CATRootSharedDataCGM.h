/* -*-c++-*- */
#ifndef CATRootSharedDataCGM_H
#define CATRootSharedDataCGM_H
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
// jul. 02  Portage 64 bits :                                             HCN
//          - remplacement de CATUuid* _identifier par CATUuid* _cgmidentifier 
// Mar. 03 _HasEverBeenPartiallyLoaded / _HasBeenPartiallyLoaded
// Apr. 03 _ObjectsWithSharpnessDataForStream
// Mar. 04 Stream/UnStreamCompact(...),
//         Stream/UnStreamCompactLossAllowed(...)                         HCN
// Feb. 05 Migration de CATHashTabCATCGMObject vers CATCGMObjectHashTable HCN
// Jul. 05 Statistiques parcours UpDown :
//           struct CATCGMOptUDStatCommon,
//           struct CATCGMOptUDStatCGMObjEntry,
//           struct CATCGMOptUDStatEntry,      
//           struct CATCGMOptUDStatScanParamEntry
//           struct CATCGMUpDownStats,
//           CATCGMOptUDStatCompareFunction(...),
//           CATCGMOptUDStatHDCompareFunction(...),
//           CATCGMOptUDStatSPCompareFunction(...),
//           CATCGMOptUDStatObjCompareFunction(...),
//           _CATCGMUpDownStats,
//          CATCGMBnddCellIterUDStats                                     HCN
// Dec. 05 Integration de CATCGMGetVisuData_Vertex                        FDN
// Jul. 09 Suppression du StreamCompact                                   VUC
// Oct. 09  IncrementalStream : GlobalData                                VUC
//=============================================================================
#include "ExportedByCATCGMFusion.h"
#include "CATICGMObject.h"
#include "CATListOfInt.h"
#include "CATListOfDouble.h"
#include "CATListPV.h"
#include "CATListOfCATICGMObjects.h"

#include "CATTime.h"
#include "CATCGMMutex.h"
#include "CATCGMObject.h"
#include "CATCartesianPoint.h"
#include "CATLine.h"
#include "CATPlane.h"
#include "CATCGMOutput.h"
#include "CATGeoFactory.h"

#include "CATMathStreamDef.h"

#include "CATCGMNewArray.h"
#include "CATCGMBOAObject.h"
#include "CATICGMUnknown.h"
#include "CATMathStreamDef.h"
#include "CATSysSimpleHashTable.h"
#include "CATCGMFactoryStatus.h"
#include "CATCGMScaleCategoryDef.h"
#include "CATDataType.h"
#include "CATListOfULONG32.h"
#include "CATOGMCoreSet.h"
#include "Data_GeometricObjectsCGM.h"
#include "CATCGMListOfCATULONGPTR.h"
#include "CATCGMStreamControl.h"
#include "CATCGMHashTableWithAssoc.h"

#include "CATCGMIdleState.h"
#include "CATCGMOwner.h"
#include "CATOGMCore.h"

#include "CATCGMObjectHashTable.h"

 
 
class CATSysSimpleHashTable;
class CATCGMObjectWithIndexHashTable;
class CATGemDoc;
class CATCGMDocument;
class CATCGMObjectHashTable;
class CATCGMTouchedGarbageCollector;
class CATExtCGMGeom;
class CATExtCGMObject;
class CATExtCGMReplay;
class CATCGMChain;
class CATCGMOperator;
class CATCGMWeakLink;
class CATUuid;
class CATCGMMapTagToObject;
class CATHashTabCATCGMDbgPoseSur;
class CATMetaClass;
class CATCGMTempoULONGPTR;
class CATCGMHashTable;
class CATCGMHashTableWithAssoc;
class CATCGMHashDico;
class CATBoundedCellsIterator;
class CATTolerance;  
class CATCGMIncrementalStreamGlobalData;
class CATCGMCompatibilityData;

class CATOGMCoreAtom;
class CATCGMObject;
struct CATRootSharedDataCGMScaleData;
//-----------------------------------------------------------------------------
// Greatest TAG that can be stocked
//-----------------------------------------------------------------------------
// max des long, et pair
//#define GREATEST_TAG 0x7FFFFFFE
// pseudo max des ULONG, et pair
#define GREATEST_TAG 0xFFFFFFF0

//-----------------------------------------------------------------------------
// CATCGMBnddCellIterUDStats
//-----------------------------------------------------------------------------
struct CATCGMBnddCellIterUDStats
{
  CATULONG32 Tab_Nb_Iters[4];
  CATULONG32 Tab_Nb_UD_Scans_U[4];
  CATULONG32 Tab_Nb_UD_Scans_D[4];
  CATULONG32 Tab_Nb_UD_Scans_Exclusive_U[4];
  CATULONG32 Tab_Nb_UD_Scans_Exclusive_D[4];
};

//-----------------------------------------------------------------------------
// CATCGMOptUDStatCommon
//-----------------------------------------------------------------------------
struct CATCGMOptUDStatCommon
{
  // CATCXTopology::CATCXUpDownCallingMethod
  CATULONG32 Method_Body_NewCommonEdges;
  CATULONG32 Method_Cell_IsOnBorder;
  CATULONG32 Method_Cell_GetNbBoundedCells;
  CATULONG32 Method_Domain_GetCellOrientation;
  CATULONG32 Method_EdgeBnddIter_SetEdge;
  CATULONG32 Method_Edge_SetCurve;
  CATULONG32 Method_FaceBnddIter_SetFace;
  CATULONG32 Method_CATSubdAdjacentLink_Build;
  CATULONG32 Method_TopObject_GetBoundedTopObjects;
  CATULONG32 Method_TopObject_IsBoundaryOfTopObject;
  CATULONG32 Method_Topology_GetAllCells;
  CATULONG32 Method_Topology_GetAllTouchedCells;
  CATULONG32 Method_Topology_IsInside;
  CATULONG32 Method_Topology_IsSharingTopology;
  CATULONG32 Method_Topology_Activate;
  CATULONG32 Method_Topology_Inactivate;
  CATULONG32 Method_Topology_NoUpwardLinksDepthInactivate;
  CATULONG32 Method_Topology_HasUpwardPathToBody;
  CATULONG32 Method_Topology_AddedInto;
  CATULONG32 Method_Topology_Completed;
  CATULONG32 Method_Topology_Touch;
  CATULONG32 Method_VertexBnddIter_SetVertex;
  CATULONG32 Method_A_Debug_Run;
  CATULONG32 Method_CATTopTools_GetShell;
  CATULONG32 Method_CATTopTools_GetBnddFacesOnShell;
  CATULONG32 Method_CATTopTools_GetBorderedFaces;
  CATULONG32 Method_ConnectedCells_NeighboursOfEdges;
  CATULONG32 Method_ConnectedCells_NewNeighboursForFaces;
  CATULONG32 Method_ConnectedCells_SearchReferenceDomain;
  CATULONG32 Method_ScanCommonCells_statistics;

  CATULONG32 Method_CGMContainer_ReadFile;
  CATULONG32 Method_Body_Clear;
  CATULONG32 Method_Body_AddDomain;
  CATULONG32 Method_Body_CATFacePropagate;
  CATULONG32 Method_Body_GroupCells;
  CATULONG32 Method_Body_NewCellNeighbours;
  CATULONG32 Method_Edge_GetGlobalSharpness;
  CATULONG32 Method_Cell_IsCandidateForReporting;
  CATULONG32 Method_CATCGMGetVisuData_Edge;
  CATULONG32 Method_CATCGMGetVisuData_Face;
  CATULONG32 Method_CATCGMGetVisuData_Vertex;
  
  // CATCXTopology::CATCXScan
  CATULONG32 Scan_OneLevelAllLinks;
  CATULONG32 Scan_OnceObject;
  CATULONG32 Scan_OnceLink;
  CATULONG32 Scan_Every;
  CATULONG32 Scan_OnePathOrManyOnCustomizedAction;
  CATULONG32 Scan_FrozenCompletedUnTouched;
  CATULONG32 Scan_ResetCachedBoundingBox;
  CATULONG32 Scan_FrozenOnly;
  CATULONG32 Scan_CleanTouched;

  // CATCXTopology::CATCXAction
  CATULONG32 Action_ResetBox;
  CATULONG32 Action_SpawnTouch;
  CATULONG32 Action_UpwardLinksGeneration;
  CATULONG32 Action_UpwardLinksDeletion;
  CATULONG32 Action_None;
  CATULONG32 Action_Customized;
  CATULONG32 Action_GetPath;
  CATULONG32 Action_Statistics;
  CATULONG32 Action_FindSharedTopology;
  CATULONG32 Action_GetHiddenOccurences;
};

//-----------------------------------------------------------------------------
// CATCGMOptUDStatCGMObjEntry
//-----------------------------------------------------------------------------
struct CATCGMOptUDStatCGMObjEntry
{
  const char*           pObjName;
  CATULONG32            ObjTag;
  int                   Dimension;
  CATULONG32            Nb_UD_Scans;
  CATCGMOptUDStatCommon Details;
};

//-----------------------------------------------------------------------------
// CATCGMOptUDStatEntry
//-----------------------------------------------------------------------------
struct CATCGMOptUDStatEntry
{
  const CATString*          pOperatorId;
  CATULONG32                SessionIdentifier;
  CATULONG32                Nb_UD_Scans_U;
  CATULONG32                Nb_UD_Scans_D;
  CATULONG32                Nb_UD_Scans_Exclusive_U;
  CATULONG32                Nb_UD_Scans_Exclusive_D;
  CATCGMHashTableWithAssoc* pHashTableCGMObjectEntries;
  CATCGMOptUDStatCommon     Details;
};

//-----------------------------------------------------------------------------
// CATCGMOptUDStatScanParamEntry
//-----------------------------------------------------------------------------
struct CATCGMOptUDStatScanParamEntry
{
  int         Parameter;
  CATULONG32  Nb_UD_Scans;
};

//-----------------------------------------------------------------------------
// CATCGMTypeFlags
//-----------------------------------------------------------------------------
# define CATCGMTypeFlagsULONG64 3 
struct ExportedByCATCGMFusion CATCGMTypeFlags
{
  static CATBoolean _ToCollect;
  CATULONG64        _Types[CATCGMTypeFlagsULONG64];
};

//-----------------------------------------------------------------------------
// CATCGMOptUDStatHashDicoEntry
//-----------------------------------------------------------------------------
struct CATCGMOptUDStatHashDicoEntry
{
  const char*           pOperatorId;
  CATULONG32            Nb_Operators;
  CATULONG64            Total_Nb_UD_Scans_U;
  CATULONG64            Total_Nb_UD_Scans_D;
  CATCGMOptUDStatCommon Details;
};

//-----------------------------------------------------------------------------
// CATCGMUpDownStats
//-----------------------------------------------------------------------------
struct CATCGMUpDownStats
{
  CATULONG64                Nb_UD_Scans_U;
  CATULONG64                Nb_UD_Scans_D;

  CATCGMOptUDStatCommon     CallUDStats_U;
  CATCGMOptUDStatCommon     CallUDStats_D;

  CATBoundedCellsIterator*  pCurrentBnddCellIter;
  CATCGMBnddCellIterUDStats BnddCellIterUDStats;

  CATCGMOperator*           pCurrentOperator;
  CATListPV*                pListOptUDStatEntries;

  int                       CurrentHigherUpDownCallingMethod;
  CATCGMOptUDStatCommon     HigherCallUDStats_U;
  CATCGMOptUDStatCommon     HigherCallUDStats_D;
};

//-----------------------------------------------------------------------------
// TagBlockChain
//-----------------------------------------------------------------------------
struct TagBlockChain
{
  CATULONG32 First;
  CATULONG32 Last;
  void *     Next;
};


//-----------------------------------------------------------------------------
// TagBlockChain
//-----------------------------------------------------------------------------
// Stack Node
class ExportedByCATCGMFusion CATCGMTransientGEOMPendingFull
{
public :
 
 INLINE CATCGMTransientGEOMPendingFull() 
  {  
    _AttributesUnStreamed = NULL;
	  _ObjectsWithLyingOnUnStreamed = NULL;
	  _SharpnessDataUnStreamed = NULL;
  }


 INLINE ~CATCGMTransientGEOMPendingFull()
 {
	 if ( _AttributesUnStreamed         ) {  delete _AttributesUnStreamed;  _AttributesUnStreamed = NULL;  }
	 if ( _SharpnessDataUnStreamed      ) {  delete _SharpnessDataUnStreamed;   _SharpnessDataUnStreamed = NULL;  }
	 if ( _ObjectsWithLyingOnUnStreamed ) {  delete _ObjectsWithLyingOnUnStreamed;    _ObjectsWithLyingOnUnStreamed = NULL;  }
 }

  CATCGMHashTable          * _AttributesUnStreamed;
  CATCGMObjectHashTable    * _ObjectsWithLyingOnUnStreamed;
  CATCGMHashTable          * _SharpnessDataUnStreamed;
};
 
  //---------------------------------------------------------------------------
  // Sauvegarder temporairement limit courant pour LimitCompact, 
  // Seulement en Light mode load
  //---------------------------------------------------------------------------
struct LimitsParamList
{
  CATCGMHashTableWithAssoc      HashTableObjectIndex;
  CATListOfDouble               CurveLimits;
  CATListOfDouble               SurfaceLimits;
  CATListOfULONG32              PartNumber; 
};

//------------------------------------------------------
// Authenticated mode
//------------------------------------------------------
#define  CGMAuthenticatedMode   unsigned char
#define  AuthenticatedOriginTRUE       0x01  // value by default
#define  AuthenticatedOriginOLD        0x02  // the container has been saved in an older version than CXR26
#define  AuthenticatedOriginFALSE      0x04  // the container has been detected as NonAuthenticated
#define  NonAuthenticated              0x80  // authentication check failed


extern "C"                                                                                \
{
//-----------------------------------------------------------------------------
// CATCGMOptUDStatCompareFunction
//-----------------------------------------------------------------------------
ExportedByCATCGMFusion int CATCGMOptUDStatCompareFunction(const void* ipEntry1, const void* ipEntry2);

//-----------------------------------------------------------------------------
// CATCGMOptUDStatHDCompareFunction
//-----------------------------------------------------------------------------
ExportedByCATCGMFusion int CATCGMOptUDStatHDCompareFunction(const void* ipEntry1, const void* ipEntry2);

//-----------------------------------------------------------------------------
// CATCGMOptUDStatSPCompareFunction
//-----------------------------------------------------------------------------
ExportedByCATCGMFusion int CATCGMOptUDStatSPCompareFunction(const void* ipEntry1, const void* ipEntry2);

//-----------------------------------------------------------------------------
// CATCGMOptUDStatObjCompareFunction
//-----------------------------------------------------------------------------
ExportedByCATCGMFusion int CATCGMOptUDStatObjCompareFunction(const void* ipEntry1, const void* ipEntry2);
}


class ExportedByCATCGMFusion CATRootSharedDataCGM : public CATCGMOwner
{
public:
  CATCGMNewClassArrayDeclare;
  CATRootSharedDataCGM(const CATCGMContainer *master, const CATCGMScaleCategory iScaleCategory);

  //-------------------------------------------------------------------------
  // For Peristency ChangeSet Management
  //-------------------------------------------------------------------------
  static  CATRootSharedDataCGM * GetSharedData(CATGeoFactory *iFactory);
          CATGeoFactory        * GetFactory(CATCGMMode iMode = CatCGMImplicit);
  static CATOGMCoreAtom        * CreateAtom( CATCGMObject *iObject, CATOGMCORE_INTENTSTATE  iTodo ) ;

  //-------------------------------------------------------------------------
  // Pour Detection d'operation specifique sur la Factory 
  //    (Sauvegarde a partir du format V5R11)
  //-------------------------------------------------------------------------
  void        DefineIsDoing(const CATCGMFactoryStatus iSpecificOperation);
  CATBoolean  HasBeenDone(const CATCGMFactoryStatus iSpecificOperation);

  //------------------------------------------------------------------------
  // MLC management
  //------------------------------------------------------------------------
  CATCGMStreamVersion GetMLCLevel ();
  void SetMLCLevel (CATCGMStreamVersion iMLCLevel);

  //----------------------------------------------------------------------------------
  // Version du niveau de build CGAOFF    (cf CGMBuildVersion.h)
  //  une version nulle correspond a un niveau de code CGAOFF anterieur au 06/01/00
  //-----------------------------------------------------------------------------------
  CATULONG32                 _OldestData_CGMBuildVersion;
  CATULONG32                 _LastStream_CGMBuildVersion;
  CATULONG32                 _HighestStream_GetBSFCGMLevel;

  //---------------------------------------------------------------------------
  // Identificateur de Debug (numero relatif de creation dans la Factory)
  //---------------------------------------------------------------------------
  CATULONG32           _SessionId ;
  static CATULONG32    _SessionBorn ;

  //---------------------------------------------------------------------------
  // proprietaires (le CATRootContainerCGM implicite)
  //---------------------------------------------------------------------------
  CATCGMContainer *_master;

  //---------------------------------------------------------------------------
  // FileName
  //---------------------------------------------------------------------------
  char            *_FileName;
  
  CATLONG32          _Differential_Iteration ; // Compteur iteration de sauvegarde

  // La presence d'une liste (meme vide) est indicateur d'une gestion differentielle
  CATListOfULONG32  * _Differential_ToDelete;

  // VUC : 16-10-09 Incremental Stream
  //Globals data necessary to perform an incremental stream /unstream
  CATCGMIncrementalStreamGlobalData* _IncrementalGlobalData;

  //---------------------------------------------------------------------------
  // Identifier persistent
  //---------------------------------------------------------------------------
  CATUuid         *_cgmidentifier;

  //---------------------------------------------------------------------------
  // donnees partagees par CATCGMContainer
  //---------------------------------------------------------------------------
  CATULONG32                  _ObjectsCount ;
  CATULONG32                  _TopologyCount ;
  CATULONG32                  _MaxTag ;
  size_t                      _LastStreamBytes;

  CATListOfInt              * _ListOfTypesOfObjectsToCorrect ;
  CATListPV                 * _ListOfListOfObjectsToCorrect ;

  CATTime                            _LastModificationTime ;

  CATCGMObjectWithIndexHashTable  *  _ObjectHashTable;
  CATCGMObjectHashTable           *  _QuickDynamicObjectHashTable;
  CATCGMMapTagToObject            *  _ForUnstreamByInjection;

  CATCGMObjectHashTable           *  _CorruptedUnstreamedAllowed; // Gestion des objets verreux 

  CATCGMObjectHashTable           *  _ObjectsWithLyingOn; 

  CATCGMTempoULONGPTR             *  _TempoULONGPTR;
  CATLONG32                          _MaximumAliveSetTempoULONGPTR ;

  CATCGMTypeFlags                 *  _TypeFlags;

  // Persistent objects , DynObjects
  CATCGMObjectHashTable           *  _PersistentObjects;
  CATCGMObjectHashTable           *  _ObjectsWithDynObject;

  CATULONG32                         _PersistentObjectsCount ;
  CATULONG32                         _LightObjectsCount ;
  CATULONG32                         _ToSaveObjectsCount ;
  //---------------------------------------------------------------------------
  // Gestion de la reutilisation des TAG
  //---------------------------------------------------------------------------
  CATULONG32      _InitialMaxTag; // Max Tag avant toute creation de nouveau TAG
  TagBlockChain * _FirstTagBlock; // Premier element de la chaine des TAG libres
  CATULONG32      _IndexInTagBlock; // Index en cours dans le bloc de TAGs courant

  //---------------------------------------------------------------------------
  // Gestion des objets avec LyingOn au Stream/UnStream
  //---------------------------------------------------------------------------


  CATCGMWeakLink             * _ManagerOfWeakLinks;
  CATHashTabCATCGMDbgPoseSur * _LastSnapShot;          // Debug pour verifier la non regression sur lien pose-sur

  //---------------------------------------------------------------------------
  // Gestion AddRef "sauvages" CGMGlobalAddRef
  //---------------------------------------------------------------------------

  CATCGMHashTableWithAssoc   * _CGMGlobalAddRefHashTable; 

  //-----------------------------------------------------------------------
  // _ChangeSetState explicit management: 
   //-----------------------------------------------------------------------
  CatCGM_IdleState             _ChangeSetState;
  CATUnicodeString             _ChangeSetStateInitURL;
  CATBaseUnknown *             _CATDocument;
  void SetCATDocument(CATBaseUnknown *iDocument);

 //---------------------------------------------------------------------------
  //  Initial Root of persistency (First Open and 
  //---------------------------------------------------------------------------
  CATOGMCoreSet          * _PersistencySelection_Initial;
  CATOGMCoreSet          * _PersistencySelection_LastSave;
  CATULONG32               _SessionRootPersistencyStamp;

  //---------------------------------------------------------------------------
  // Liste des cles d'attributs a faire suivre dans toutes les operations
  // (split/merge/copy/transfo/...). Le comportement des attributs lors de 
  // ces operations peut etre specifie par un numero de type d'attribut.
  //---------------------------------------------------------------------------
  int                      _NbKernelAttributeKeys;
  int                      _MaxKernelAttributeKeys;
  int*                     _KernelAttributeKeys;
  int*                     _KernelAttributeTypes; 

  CATCGMMutex              _mutex;
  //---------------------------------------------------------------------------
  // gestion du nombre d'objets touche au sens CATIGenericNamed
  //---------------------------------------------------------------------------
  CATLONG32              _NumberOfGenericNamed;
  CATExtCGMObject     *  _FirstExtCGMObj;
  CATExtCGMGeom       *  _CATExtCGMGeom;
  CATLONG32              _NumberOfNeededToSave;

  //---------------------------------------------------------------------------
  // Identificateur de TouchedGarbageCollector
  //---------------------------------------------------------------------------
  short  _NumberOfTouchedGC;
  short  _SizeOfTouchedGC;
  struct TouchedGarbageCollectors  
  {
     CATCGMTouchedGarbageCollector*  _Garbage;
     CATCGMObjectHashTable        *  _Touched;
  };
  TouchedGarbageCollectors * _TouchedGC;

  //---------------------------------------------------------------------------
  // donnees partagees par CATRootContainerCGM
  //---------------------------------------------------------------------------
  
/*  CATPositiveLength _ResolutionC0 ;
  double            _ResolutionC1 ;
  double            _ResolutionC2 ;*///--AAD20120724 These variables are replaced by the equivalent ones in _Tolerance
  CATPositiveLength _Infinite ;
  CATPositiveLength _ModelSize ;
  CATPositiveLength _Unit ;
  CATTolerance      * _GMTolerance;
  
  CATGemDoc         * _CATGemDoc;
  CATCGMDocument    * _CATCGMDocument;
  CATExtCGMReplay   * _CATExtCGMReplay;
  CATCGMChain       * _myCATCGMChain;

  struct Datums  
  {
     const CATCartesianPoint * _O   ;
     const CATLine           * _OI  ;
     const CATLine           * _OJ  ;
     const CATLine           * _OK  ;
     const CATPlane          * _OIJ ;
     const CATPlane          * _OJK ;
     const CATPlane          * _OKI ;
  };

  Datums * _datums;

#define CATRootSharedDataCGM_NumberOfReplayName   6 

  struct LastReplayName  
  {
     CATULONG32                _Tags[2];
     CATUnicodeString          _CGMReplay;
     CATCGMOperator        *   _Check;
  };

  LastReplayName * _LastReplayName[ CATRootSharedDataCGM_NumberOfReplayName ];
  int              _LastReplayIndex;
  int              _LastReplayCounter;



  //---------------------------------------------------------------------------
  // For DirtyForMeasure -> CATCGAMeasure (
  //---------------------------------------------------------------------------
  INLINE int  IsDirtyForMeasure() const; 
  INLINE void ResetDirtyForMeasure();
  INLINE void SetDirtyForMeasure();

  //---------------------------------------------------------------------------
  // Statistiques parcours UpDown
  //---------------------------------------------------------------------------
  CATCGMUpDownStats *_CATCGMUpDownStats;
  
  //--------------------------------------------------------------------
  // Petites informations
  //-------------------------------------------------------------------- 
  struct CATCGMRootFlags
  {
    //-------------------------------------------------------------------------
    // Control validite de la sauvegarde  (Debug)
    //-------------------------------------------------------------------------
    unsigned _CheckStream          : 2;      
    
    //-------------------------------------------------------------------------
    // Gestion TimeStamp 
    //-------------------------------------------------------------------------
    unsigned _CopyNeeded           : 1;      

    //-------------------------------------------------------------------------
    // Micro AddRef/Release sur les usage de this 
    //-------------------------------------------------------------------------
    signed  _ContainerCount        : 4;   
    
    //-------------------------------------------------------------------------
    // Transaction "CleanNewerUnused"
    //-------------------------------------------------------------------------
    unsigned _CleanNewerUnused     : 1;      
    
    //-------------------------------------------------------------------------
    // Etat de Chargement de la Factory
    //-------------------------------------------------------------------------
    unsigned _IsUnstreamed         : 2;
    
    //-------------------------------------------------------------------------
    // Light Design Mode (IsPartiallyLoaded)
    //-------------------------------------------------------------------------
    unsigned _IsPartiallyLoaded       : 1;

	//-------------------------------------------------------------------------
    // Load Mode For Unstream ()
    //-------------------------------------------------------------------------
    unsigned _HowToLoad      : 2;  //1 Partially, 2 Full (default value)

    //-------------------------------------------------------------------------
    // Light Design Mode (Manipulation)
    //-------------------------------------------------------------------------
    unsigned _HasEverBeenPartiallyLoaded  : 1;
    unsigned _HasBeenPartiallyLoaded  : 1;

    //-------------------------------------------------------------------------
    // Mode C1 (Manipulation) ..
    //-------------------------------------------------------------------------
    unsigned _HasBeenC1               : 1;

    //-------------------------------------------------------------------------
    // Cleaner (FatVertex et FatExtrapol)
    //-------------------------------------------------------------------------
    unsigned _HasBeenCleaned_FatVertex    : 1;
    unsigned _HasBeenCleaned_FatEdge      : 1;
    unsigned _HasBeenCleaned_FatExtrapol  : 1;

    //-------------------------------------------------------------------------
    // Injection de Geometrie avec decalage de Tag (Warm Start Toyota)
    //-------------------------------------------------------------------------
    unsigned _WithGeometryInjection   : 1;

    //-------------------------------------------------------------------------
    // Hidden Seam Management (Streamable Flag)
    //-------------------------------------------------------------------------
    unsigned _TopologicalPropagateHiddenSeam : 1;

    //-------------------------------------------------------------------------
    // _AvoidNewGreyBoxManagement
    //-------------------------------------------------------------------------
    unsigned _AvoidNewGreyBoxManagement   : 1;

    //-------------------------------------------------------------------------
    // Imprint Attribute Management (Allows toggling Imprint Attr Propagation /Non Streamable Flag)
    //-------------------------------------------------------------------------
    unsigned _TopologicalPropagateImprintAttribute   : 1;
       
    //-------------------------------------------------------------------------
    // Detection d un attribut Clonable  HasUsedClonableAttribute()
    //-------------------------------------------------------------------------
    unsigned _HasUsedClonableAttribute : 1;

     //-------------------------------------------------------------------------
    // For Measure 
    //-------------------------------------------------------------------------
    unsigned _DirtyForMeasure : 1;
	unsigned _CGMComponentInUse : 1;

    //-------------------------------------------------------------------------
    // Libre
    //-------------------------------------------------------------------------
    unsigned _RFU              : 6;

  } 
  _RootFlags;

  CATULONG32   _MaxTagBeenLoaded ;

  //-----------------------------------------------------------------------
  // Keep original binary
  //-----------------------------------------------------------------------
  void GenerateHistoricalBinary(CATCGMStream & Str,size_t InitialSize);

  static CATBoolean     _HistoricalBinary;
  static void           SetHistoricalBinary(CATBoolean iHistoricalBinary);
  unsigned char   *     _HistoricalBinaryBuffer ;
  size_t                _HistoricalBinarySize;
  unsigned char         _HistoricalBinaryConversion;
  CATULONG32            _HistoricalBinaryObjectsCount ;

  CATULONG32            _HistoricalBinaryNbLightObjects ;
  CATULONG32      *     _HistoricalBinaryLightObjects ;
 

  CATCGMStreamVersion _LastUnstreamVersion;
  CATCGMStreamControl _LastUnstreamControl;
  CATCGMStreamVersion _LastStreamVersion;


  CGMAuthenticatedMode  _AuthenticatedMode;
  // if _CreationVersion >= CXR26, it is creation version
  // if _CreationVersion < CXR26,  it is the last old convert version
  CATCGMStreamVersion   _CreationVersion;


  //-----------------------------------------------------------------------------
  // CATBack
  //-----------------------------------------------------------------------------
  CATCGMCompatibilityData * _CompatibilityData;

  //-----------------------------------------------------------------------
  // CATCGMContainer :: List of attribute keys that are necessary within topological operators
  //-----------------------------------------------------------------------
  void AddKernelAttributeKey( int iAttributeKey, int iAttributeType );
  void RemoveKernelAttributeKey( int iAttributeKey );
  CATLONG32 GetNbKernelAttributeKeys();
  int  GetKernelAttributeKey( CATLONG32 iIndex, int & oAttributeType );

  //---------------------------------------------------------------------------
  // CATRootContainerCGM : gestion Standard de Tolerances
  //---------------------------------------------------------------------------
  void SetModelSize(const CATPositiveLength &iTolerance) ;
  void SetModelSizeAndResolution(double iModelSizeInUnit,
                                 CATBoolean iKeepPreviousResolution,
                                 double iResolutionC0FromModelSize);

  CATCGMTolerancesCompatibility CompareTolerances(const CATRootSharedDataCGM *iOtherFactory, CATBoolean  iThrowIfComparableButNotIdentical) const;

  CATBoolean HasCompatibleWith(const CATRootSharedDataCGM *iOtherFactory) const;

  void SetUnit(const CATPositiveLength iUnitInMeter) ;

  //-----------------------------------------------------------------------
  // Objet CATTolerance
  //-----------------------------------------------------------------------
  void CheckSessionCompatibility(double iScale, CATBoolean iRiskyTry);
  void SetScaleCategory(CATCGMScaleCategory iScaleCategory);  
  const CATTolerance & GetTolerance() const;
  
  //-----------------------------------------------------------------------
  // StartOperation / EndOperation 
  //-----------------------------------------------------------------------
  void StartOperation(CATCGMOperator* Operator); 
  void EndOperation(CATCGMOperator* Operator);

  //---------------------------------------------------------------------------
  // TouchedGarbageCollector :  Registration & Notification Management
  //---------------------------------------------------------------------------
  void AddTouchedGC(CATCGMTouchedGarbageCollector* iGC) ;                
  void RemoveTouchedGC(CATCGMTouchedGarbageCollector* iGC) ;                

  //---------------------------------------------------------------------------
  // CATRootContainerCGM : Datum access
  //---------------------------------------------------------------------------
  const CATGeometry* GetDatum( const CATGeoFactory::CATDatumId DatumId ) ;
  void SetDatum( const CATGeoFactory::CATDatumId DatumId, const CATGeometry* GeoDatum) ;
  void UnStream(const CATLISTP(CATICGMObject)    LinkedObjects);
  void RemoveDatum() ;

  //---------------------------------------------------------------------------
  // CATRootContainerCGM : Dump
  //---------------------------------------------------------------------------
  void Dump( CATCGMOutput& os );

  //---------------------------------------------------------------------------
  // Clear()
  //---------------------------------------------------------------------------
  void Clear();

  //---------------------------------------------------------------------------
  // CATRootContainerCGM : Stream
  //---------------------------------------------------------------------------
  void StreamV2R0   ( CATCGMStream& Str ) ;
  void UnStreamV2R0 ( CATCGMStream& Str , CATLISTP(CATICGMObject)& ListDependencies) ;

  Data_GeometricObjectsCGM_Stream;

  //---------------------------------------------------------------------------
  //  PendingFull (without MProc impact)
  //---------------------------------------------------------------------------
	CATCGMTransientGEOMPendingFull *_PendingFull;

  //---------------------------------------------------------------------------
  // Sauvegarder temporairement limit courant pour LimitCompact, 
  // Seulement en Light mode load
  //---------------------------------------------------------------------------
  LimitsParamList     *            _LimitsParamList;
  //---------------------------------------------------------------------------
  // Read/WriteHeader
  //---------------------------------------------------------------------------
  void ReadHeader( CATCGMStream& Str );
  void WriteHeader( CATCGMStream& Str );

  //---------------------------------------------------------------------------
  // Pour gestion adhesion ambigue sur CATIContainer *
  //---------------------------------------------------------------------------
  static const char   * _ClassNameCATIContainer;
  static IID            _IIDCATIContainer;
 
  static const char   * _ClassNameLifeCycleObject;
  static IID            _IIDLifeCycleObject;
 
protected  :
  ~CATRootSharedDataCGM();

private:

  CATCGMStreamVersion _MLCVersion;
  void UnStreamFactoryStatus(CATCGMStreamVersion & iStreamVersion, unsigned short iFlagStatus);
  void UnstreamData(CATCGMStream& Str, CATLISTP(CATICGMObject)& LinkedObjects, CATRootSharedDataCGMScaleData & oScaleData);
  void SetScaleData(CATRootSharedDataCGMScaleData & iScaleData);

  CATLONG32             _LoadedLastModificationTime ;

  void InitDatum() ;
};


//--------------------------------------------------------------------------
// DirtyForMeasure ... Pour une gestion efficace d une evolution dans le LifeCycle d un Factory
//    --> Variation du nombre d objets
//    --> Variation sur le nombre d'elements persistants (Cf GenericNaming)
//    --> Variation sur l introduction des attributs (externes)
//-------------------------------------------------------------------------
INLINE int CATRootSharedDataCGM::IsDirtyForMeasure() const  
{ return (_RootFlags._DirtyForMeasure ? 1 : 0); }

INLINE void CATRootSharedDataCGM::ResetDirtyForMeasure()    
{ _RootFlags._DirtyForMeasure = 0; }

INLINE void CATRootSharedDataCGM::SetDirtyForMeasure()    
{ if ( !  _RootFlags._DirtyForMeasure )  _RootFlags._DirtyForMeasure = 1; }

#endif


