/* -*-c++-*- */
#ifndef CATCGMTopoCXMODEL_H_
#define CATCGMTopoCXMODEL_H_
// COPYRIGHT DASSAULT SYSTEMES  2000
//=============================================================================
//  Dynamic invokation of Topology framework
//=============================================================================
//  * @quickReview 666 13:04:01  2013 Week15 / Assembly Design Scalability / Functions =(Product Filtering-Import CCP)  / Customer = Toyota + Exchanges / Modeler CGM
// Oct. 02 Parametre iRemoveFromFactory pour SplitEdge(...)               HCN
//         Passage de iObjectsWithLyingOn / iObjectsWithLyingOnUnStreamed
//         dans _StreamLyingOnData / _UnStreamLyingOnData                 HCN
// Apr. 03 Parametre iNbLyingOnDataToRead pour UnStreamLyingOnData(...)   HCN 
// Apr. 03 _CheckLyingOnAfterUnStream(...),
//         _StreamSharpnessData(...), _UnStreamSharpnessData(...)         HCN
// Jun. 03 _CreateCGMQueryNegativeOffsets(...)
//         pour GeometricObjectsCGM pour CATBack                          HCN
// Jul. 03 UpdateEdgeSimplifiedSupport                                    HCN
// Aug. 03 _GetLyingOnLinks(...)                                          HCN
// Oct. 03 _DumpFatDetailedDiagnosis(...),
//         CreateArrayBoundingEdgeHashTable(),
//         DeleteArrayBoundingEdgeHashTable(...),
//         Optimisation perfo : parametre CATArrayBoundingEdgeHashTable
//                              pour UpdateEdgeSimplifiedSupport(...)     HCN
// Nov. 03 CreateListDbgPoseSurHashTable(...),
//         DeleteListDbgPoseSurHashTable(...),
//         parametre CATArrayBoundingEdgeHashTable
//         pour CATCGMTopoCXMODEL::UpdateEdgeSimplifiedSupport(...)       HCN
//         _GetStaticSharpnessData(...)
//         _DumpStaticSharpnessDataTopo(...)
//         _CompactSubd(...)                                              HCN
// Dec. 03 _DumpLyingOnLinks(...)                                         HCN
// Feb. 04 _GetCellNumbers(...), _GetLatestBodyWithMostCells(...),
//         _DumpSubdStats,
//         _UnlinkUselessGeometry(...)                                    HCN
// Apr. 04 Parametre iSortedBy pour _DumpSubdStats(...)                   HCN
// May  04 _SimplifyEdgeCurve(...)                                        HCN
// Jun. 04 RI 0454807 : _SetCleanerReplaceModeDefinition(...)             HCN
// Jan. 05 _Activate                                                      HCN
// Jan. 05 _CATCreateCanonicalGeometry(...)																BOM
// Feb. 05 Migration de CATHashTabCATCGMObject vers CATCGMObjectHashTable HCN
// Feb. 05 _CATCXTopology_UpDown_Traces                                   HCN
// May  05 _DumpFatDetailedDiagnosis(...CATLISTP(CATCGMLimOfParm)*...)    HCN
// Jun. 05 _NewGetBoundedTopObjects(...)                                  HCN
// Jul. 05 _DumpUpDownStats(...)                                          HCN
// Aug. 05 Statistiques parcours UpDown :
//         CATCGMOptUDStatCommonGetScanParam(...)                         HCN
// Jun. 05 Suppresssion de _NewGetBoundedTopObjects(...)                  HCN
//=============================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMTopo.h"
#include "CATTopGeometricalMapping.h"
#include "CATCGMQueryManager.h" 
#include "CATBodyDatumiser.h" 
#include "CATTopInsertClosureVertex.h" 
#include "CATTopSplitEdge.h" 
#include "CATMathInline.h"
#include "CATListOfCATCGMObjects.h"
#include "CATCGMObjectConvert.h"

class CATDomain;

class CATBodiesMapping;
class CATBody;
class CATJournalsMapping;
class CATJournalMatcher;
class CATCGMJournal;
class CATLISTP(CATBody);
class CATLISTP(CATCGMJournal);
class CATLISTP(CATBody);
class CATMultiBodiesMapping;
class CATCGMOutput;
class CATEdgeCurveTransientExtrapolManager;
class CATCGMGeometryOfFatAble;
class CATArrayBoundingEdgeHashTable;
class CATListDbgPoseSurHashTable;
class CATCGMSharpnessData;
class CATCXShell;

struct CATCGMOptUDStatCommon;

CATULONG32 CATCGMOptUDStatCommonGetScanParam(CATCGMOptUDStatCommon& ioStatCommon,
                                             int                    iScanParamType,
                                             int                    iScanParamValue);

class ExportedByCATTopologicalObjects CATCGMTopoCXMODEL : public CATCGMTopo
{
public:
  CATCGMTopoCXMODEL();
  ~CATCGMTopoCXMODEL();
  
  static int CXMODELDebugAtExit();

  //-------------------------------------------------------------------------------------
  //  Mapping Body et Journal
  //---------------------------- ---------------------------------------------------------

  INLINE static CATBodiesMapping *CATCreateBodiesMapping(CATTopData * iTopData ,
    const CATBody *iReferenceBody , 
    const CATBody *iResultBody, const int     iSilentMode);
  
  INLINE static CATBodiesMapping *CreateBodiesMapping(const CATBody *iReferenceBody , 
    const CATBody *iResultBody, const int     iSilentMode);

  INLINE static CATMultiBodiesMapping *CreateMultiBodiesMapping(
    CATLISTP(CATBody)* iReferenceBodiesList , 
    CATLISTP(CATBody)* iResultBodiesList    );

  INLINE static  CATJournalsMapping * CreateJournalsMapping(const CATBody * iReferenceBody,
    const CATCGMJournal * iReferenceJournal,
    const CATBody * iResultBody,
    const CATCGMJournal * iResultJournal,
    CATCGMOutput& os) ; // CATCGMReplay


  INLINE static CATJournalsMapping * CreateJournalsMapping(const CATBody * iReferenceBody,
    const char * iReferenceJournalFile,
    const CATBody * iResultBody,
    const CATCGMJournal * iResultJournal,
    int iForceWrite);
  
  INLINE static CATJournalsMapping * CreateJournalsMappingMulti(const CATLISTP(CATBody)*		ipListReferenceBodies,
    const CATListOfCATString*		ipListReferenceJournalFiles,
    const CATLISTP(CATBody)*		ipListResultBodies,
    const CATLISTP(CATCGMJournal)*	ipListResultJournals,
    const CATMultiBodiesMapping*	ipMultiBodiesMapping,
    int iForceWrite);
  
  INLINE static CATJournalsMapping * CreateJournalsMappingMulti(const CATLISTP(CATBody)*		ipListReferenceBodies,
    const char * iReferenceJournalFile,
    const CATLISTP(CATBody)*		ipListResultBodies,
    const CATLISTP(CATCGMJournal)*	ipListResultJournals,
    const CATMultiBodiesMapping*	ipMultiBodiesMapping,
    int iForceWrite);
  
  
  INLINE static CATJournalMatcher * CreateJournalMatcher(const char * iReferenceFile,
    int iForceWrite);


  //---------------------------
  // CATTopGeometricalMapping
  //---------------------------
  INLINE static CATTopGeometricalMapping * CreateMapping( 
    const CATTopData                 & iTopData, 
    const CATLISTP(CATICGMUnknown)   & iInputs,  
    const CATTopGeometricalMapType   iStrategy,
    const CATTopGeoMapping_QueryType iQueries,
    CATGeometricType                 iFilter );
  
  INLINE static CATTopGeometricalMapping * CreateMapping ( 
    const CATTopData                & iTopData,
    CATBody                         * iBody,
    const CATTopGeometricalMapType    iStrategy,
    const CATTopGeoMapping_QueryType  iQueries,
    CATGeometricType                  iFilter  );

  INLINE static CATTopGeometricalMapping * CreateMapping ( 
     const CATTopData                & iTopData,
     CATGeoFactory                   * iGeoFactory,
     const CATTopGeometricalMapType    iStrategy,
     const CATTopGeoMapping_QueryType  iQueries,
     CATGeometricType                  iFilter  );
  //---------------------------
  // CATCGMQueryManager
  //---------------------------
  INLINE static CATCGMQueryManager * CreateQuery(
    CATCGMQueryManager::TypeOfQuery  iType, 
    CATSoftwareConfiguration * iConfig,
    const CATLISTP(CATICGMUnknown)   & inputs);

  //---------------------------
  // EdgeCurveTransientExtrapolManager
  //---------------------------

  INLINE static CATEdgeCurveTransientExtrapolManager *
  CreateEdgeCurveTransientExtrapolManager
    (CATGeoFactory * iFactory,
     CATSoftwareConfiguration * iConfig,
     CATBody * iBody);

  //---------------------------
  // CATBodyDatumiser
  //---------------------------
  INLINE static CATBodyDatumiser *CreateDatumiser(
    CATGeoFactory * iFactory,
    CATBody *iInputBody,
    const CATTopData & iTopData,
    const CATLISTP(CATICGMObject) * iInputMapping);
  
  INLINE static CATBodyDatumiser *CreateDatumiser(
    CATGeoFactory * iFactory,
    const CATLISTP(CATBody) & iInputBodies,
    const CATTopData & iTopData,
    const CATLISTP(CATICGMObject) * iInputMapping);
  
  INLINE static CATBodyDatumiser *CreateFactoryDatumiser(
    CATGeoFactory * iFactory,
    const CATTopData & iTopData);
  
  //---------------------------
  // CATCGMObjectConvert
  //---------------------------
  INLINE static CATCGMObjectConvert *CreateCGMObjectConvert(
	  CATGeoFactory * iFactory,
	  CATSoftwareConfiguration* iConfig);
  
  //---------------------------
  // CATTopInsertClosureVertex
  //---------------------------
  INLINE static int InsertClosureVertex(CATGeoFactory       *  iFactory,
                      CATBody            *   iClosedWireBody,
                      CATBody            *   iVertexBody,
                      CATBody            * & oBody,
                       const CATTopData   &   iTopData  );
  
  //---------------------------
  // CATTopSplitEdge
  //---------------------------
  INLINE static void SplitEdge(CATGeoFactory*            iFactory,
                               CATBody*                  iBody, 
                               CATEdge*                  iEdge,
                               const CATSetOfCrvParams&  iSetOfBreaks, 
                               CATBody*&                 oBody,
                               const CATTopData&         iTopData,
                               CATBoolean                iFreezeOn,
                               CATVertex**               ioCreatedVtx,
                               CATEdge**                 ioCreatedEdges,
                               CATBoolean                iRemoveFromFactory = FALSE);

  //---------------------------
  // CreateArrayBoundingEdgeHashTable / DeleteArrayBoundingEdgeHashTable
  //---------------------------
  static CATArrayBoundingEdgeHashTable* CreateArrayBoundingEdgeHashTable(CATLISTP(CATCGMObject)    * iLimitedScope, CATGeoFactory* ipFactoryToScan);

  static void CheckForArrayBoundingEdgeHashTable(CATCGMObject * iObject, CATArrayBoundingEdgeHashTable*  iTable);

  static void DeleteArrayBoundingEdgeHashTable(CATArrayBoundingEdgeHashTable* ipArrayBoundingEdgeHashTable);





  //---------------------------
  // CreateListDbgPoseSurHashTable / DeleteListDbgPoseSurHashTable
  //---------------------------
  static CATListDbgPoseSurHashTable* CreateListDbgPoseSurHashTable(CATLISTP(CATCGMObject)    * iLimitedScope, CATGeoFactory* ipFactoryToScan,
	  CATGeometricType iCellFromType,
	  CATGeometricType iSupportType);

  static void CheckForListDbgPoseSurHashTable(CATCGMObject * iObject, CATListDbgPoseSurHashTable*  iTable,  CATGeometricType iCellFromType,  CATGeometricType iSupportType);
 
  static void DeleteListDbgPoseSurHashTable(CATListDbgPoseSurHashTable* ipListDbgPoseSurHashTable);

  //---------------------------
  // CATCreateCanonicalGeometry
  //---------------------------
  INLINE static CATGeometry* CreateCanonicalGeometry(CATTopData*							 ipTopData,
                                                     const CATLISTP(CATCell)& iListInputCells,
                                                     CATGeometricType         iRequestedType);

  static  void  EstimateBaryCenter(CATVertex *iVertex, CATMathPoint& oResult, CATSoftwareConfiguration* pConfig);

  
  //-------------------------------------------------------------------------------------
  //  Mark Reordered Shells
  //---------------------------- ---------------------------------------------------------
  static void MarkReorderedShell(CATCXShell *piShell, CATBoolean iUnDo = FALSE);

  //-------------------------------------------------------------------------------------
  //  Is Reordered Shells
  //---------------------------- ---------------------------------------------------------
  static CATBoolean IsReorderedShell(CATCXShell *piShell);

  //-------------------------------------------------------------------------------------
  //  Is Reordered Body
  //---------------------------- ---------------------------------------------------------
  static CATBoolean IsReorderedBody(CATBody* piBody);

protected :
  //---------------------------
  // Pour implementation 
  //---------------------------
  void _CheckActivation();
  
  //---------------------------
  // Debug pour verifier la non regression sur lien pose-sur
  //---------------------------
  void _DbgPoseSur(CATCGMContainer *iContainer, short iEnding=0);
  void _DbgPoseSurOnlyOne(CATCGMContainer *iContainer, short iEnding);

  void _DumpDbgPoseSur(CATCGMOutput& os, CATCGMContainer *iContainer);

  //---------------------------------------------------------------------------------
  //  for Light Brep Mode
  //---------------------------------------------------------------------------------
  CATBoolean _FullLoading(CATGeoFactory* iFactory);

  short  _IsOutsideAnySubdSession();

  //=================================================================
  //  for CATGeoFactoryCGM() with Topology Needed
  //=================================================================
  void     _Remove(CATGeoFactoryCGM *iFactory, CATBody* iBody, CATTopData &iTopData);
  void     _CommonRemove( CATGeoFactoryCGM *iFactory, 
                     CATTopology *iObject,
                     const CATICGMContainer::CATRemovingDependancies how,
                     CATCGMJournalList* iInReport,
                     CATSoftwareConfiguration* iConfig); 

  //=================================================================
  //  _CreateBody
  //=================================================================
  virtual CATBody* _CreateBody(CATGeoFactoryCGM     * iFactory , 
                               CATBodyMode            iMode        = CatBodyMode_Working ,
                               const char             iRole[]      = "Unknown",
                               const char           * iTracability = __FILE__ ,
                               const int              iLine        = __LINE__)  ;    


  //=================================================================
  //  detection des POEC et PCurve non utiles
  //=================================================================
  CATBoolean _GetUselessPoecPCurve(CATGeoFactory*           iFact,
                                   CATLISTP(CATICGMObject)& oInMacroPoint,
                                   CATLISTP(CATICGMObject)& oInEdgeCurve,
                                   CATBoolean               iCleanerLike); 

  void _DumpFatDetailedDiagnosis(CATCGMOutput& iOutput, CATLISTP(CATCGMGeometryOfFatAble)* ipListFatAbles, CATGeometricType iGeomTargetType);

  void _DumpFatDetailedDiagnosis(CATCGMOutput& iOutput, CATLISTP(CATCGMLimOfParm)* ipListLimOfParms);

  //=================================================================
  // Pour cleaning des FatEdgeCurve dans CATCGMGeometryOfFatAble
  //=================================================================
  virtual CATBoolean _SimplifyEdgeCurve(CATSoftwareConfiguration * iConfig,
                                        CATCGMGeometryOfFatAble* ipCGMGeometryOfFatAble,
                                        CATEdgeCurve**           ioppNewEdgeCurve,
                                        short*                   ioOriEdgeCurve,
                                        CATBoolean*              ioNewEdgeCurve,
                                        CATPointOnEdgeCurve**    ioppNewStartPOEC,
                                        CATPointOnEdgeCurve**    ioppNewEndPOEC,
                                        CATBoolean*              ioNewPOECs,
                                        CATBoolean*              ioReversedOrientations,
                                        CATBoolean*              iopIsSimplifiable);

  //=================================================================
  // Pour coherence de la modelisation subd apres clean
  //=================================================================
  virtual void _SetCleanerReplaceModeDefinition(CATCGMObject* ipCGMObject, const short iReplaceMode);

  //=================================================================
  //  for CATRootContainerCGM() with Topology Needed
  //=================================================================
  void _RemoveRootContents(CATRootContainerCGM *iContainer, const CATBoolean iUserClose);

  void _CheckLyingOnAfterUnStream(CATRootContainerCGM    * iContainer,
                                  CATCGMObjectHashTable  * iObjectsWithLyingOn,
                                  CATCGMStream           & Str);

  void _StreamLyingOnData(CATRootContainerCGM    * iContainer,
                          CATCGMObjectHashTable  * iObjectsWithLyingOn,
                          CATCGMStream           & Str);

  void _UnStreamLyingOnData(CATRootContainerCGM    * iContainer,
                            CATCGMObjectHashTable  * iObjectsWithLyingOnUnStreamed,
                            CATCGMStream           & Str,
                            CATULONG32             iNbLyingOnDataToRead,
                            const CATBoolean         iTryPartialLoad);  

  void _StreamSharpnessData(CATRootContainerCGM    * iContainer,
                            CATCGMObjectHashTable  * iObjectsWithSharpnessData,
                            CATCGMStream           & Str); 

  void _UnStreamSharpnessData(CATRootContainerCGM    *  iContainer,
                              CATCGMObjectHashTable  *  iObjectsWithSharpnessDataUnStreamed,
                              CATCGMHashTable        ** ippSharpnessDataUnStreamed,
                              CATCGMStream           &  Str,
                              CATULONG32              iNbSharpnessDataToRead,
                              const CATBoolean          iTryPartialLoad); 

  void _BetweenStreamAndMemory(CATCGMContainer *iContainer, CATCGMObject  *FirstAdded, CATCGMStream &Str, CATCGMEventType iSpecificContext) ;

  //---------------------------------------------------------------------------------
  //  for CATGem/Debug : * * * DON'T FORGET TO DELETE the CATCGMDbgPoseSur(s) returned * * *
  //---------------------------------------------------------------------------------
  void _GetLyingOnLinks(CATCell* ipCell, CATLISTP(CATCGMDbgPoseSur)* iopListOfLyingOnLinks);

  virtual CATULONG32 _DumpLyingOnLinks(CATCell*                    ipCell,
                                       CATCGMOutput&               iOutput,
                                       CATLISTP(CATCGMDbgPoseSur)* ipListOfLyingOnLinks,
                                       CATULONG32*                 iopNbBadLinks,
                                       CATULONG32*                 iopNumCellToDisplay);

  CATCGMSharpnessData* _GetStaticSharpnessData(CATCell* ipCell, int& ioNbTopoData, int& ioNbGeomData, CATCGMOutput* ipOutput);

  void _DumpStaticSharpnessDataTopo(CATCell* ipCell, char* ipAlignMSG, CATCGMOutput& iOutput);   

  //---------------------------------------------------------------------------------
  //  for CATGem/Debug : traces for CATCXTopology Up/Down operaions
  //---------------------------------------------------------------------------------
  void _CATCXTopology_UpDown_Traces(int iTraceType, int iActivated);

  void _DumpUpDownStats(CATCGMContainer* ipContainer, CATCGMOutput& iOutput);

  //---------------------------------------------------------------------------------
  // For CATBack
  //---------------------------------------------------------------------------------
  CATCGMQueryManager* _CreateCGMQueryNegativeOffsets(CATSoftwareConfiguration* ipConfig,  const CATLISTP(CATICGMUnknown)& iInputs);
  CATCGMQueryManager* _CreateCGMQueryUsefulLimits(CATSoftwareConfiguration*    ipConfig,  const CATLISTP(CATICGMUnknown)& iInputs);

  //---------------------------------------------------------------------------------
  //  for CATCXDebug shared-lib
  //---------------------------------------------------------------------------------
  CATBoolean _IsActive(CATTopology *iTopology, CATBody *iBody); 

  //-------------------------------------------------------------------------------------
  //  Gestion :   NewTopologicalObjects  --> CGMV5Interoperability
  //---------------------------- ---------------------------------------------------------

  virtual CATBodiesMapping *_CATCreateBodiesMapping(CATTopData * iTopData,
    const CATBody *iReferenceBody , 
    const CATBody *iResultBody    ,
    const int     iSilentMode)  = 0 ;

  virtual CATBodiesMapping *_CreateBodiesMapping(const CATBody *iReferenceBody , 
    const CATBody *iResultBody    ,
    const int     iSilentMode)  = 0 ;


  virtual CATJournalsMapping * _CreateJournalsMapping(const CATBody * iReferenceBody,
    const CATCGMJournal * iReferenceJournal,
    const CATBody * iResultBody,
    const CATCGMJournal * iResultJournal,
    CATCGMOutput& os)  = 0 ; // CATCGMReplay


  virtual CATJournalsMapping * _CreateJournalsMapping(const CATBody * iReferenceBody,
    const char * iReferenceJournalFile,
    const CATBody * iResultBody,
    const CATCGMJournal * iResultJournal,
    int iForceWrite) = 0 ;
  
  virtual CATJournalsMapping * _CreateJournalsMappingMulti(const CATLISTP(CATBody)*		ipListReferenceBodies,
    const CATListOfCATString*		ipListReferenceJournalFiles,
    const CATLISTP(CATBody)*		ipListResultBodies,
    const CATLISTP(CATCGMJournal)*	ipListResultJournals,
    const CATMultiBodiesMapping*	ipMultiBodiesMapping,
    int iForceWrite) = 0 ;
  
  virtual CATJournalsMapping * _CreateJournalsMappingMulti(const CATLISTP(CATBody)*		ipListReferenceBodies,
    const char * iReferenceJournalFile,
    const CATLISTP(CATBody)*		ipListResultBodies,
    const CATLISTP(CATCGMJournal)*	ipListResultJournals,
    const CATMultiBodiesMapping*	ipMultiBodiesMapping,
    int iForceWrite) = 0 ;

  
  virtual CATJournalMatcher * _CreateJournalMatcher(const char * iReferenceFile,
    int iForceWrite) = 0 ;
  
  //---------------------------
  // CATTopGeometricalMapping
  //---------------------------
  virtual CATTopGeometricalMapping * _CreateMapping( 
    const CATTopData                 & iTopData, 
    const CATLISTP(CATICGMUnknown)   & iInputs,  
    const CATTopGeometricalMapType   iStrategy,
    const CATTopGeoMapping_QueryType iQueries,
    CATGeometricType                 iFilter ) = 0;
  
  virtual CATTopGeometricalMapping * _CreateMapping ( 
    const CATTopData                & iTopData,
    CATBody                         * iBody,
    const CATTopGeometricalMapType    iStrategy,
    const CATTopGeoMapping_QueryType  iQueries,
    CATGeometricType                  iFilter  ) = 0;

  virtual CATTopGeometricalMapping * _CreateMapping ( 
    const CATTopData                & iTopData,
    CATGeoFactory                   * iGeoFactory,
    const CATTopGeometricalMapType    iStrategy,
    const CATTopGeoMapping_QueryType  iQueries,
    CATGeometricType                  iFilter  ) = 0;


  //---------------------------
  // CATCGMQueryManager
  //---------------------------
  virtual CATCGMQueryManager * _CreateQuery(
    CATCGMQueryManager::TypeOfQuery  iType, 
    CATSoftwareConfiguration * iConfig,
    const CATLISTP(CATICGMUnknown)   & inputs) = 0;

  //---------------------------
  // EdgeCurveTransientExtrapolManager
  //---------------------------

  virtual CATEdgeCurveTransientExtrapolManager *
  _CreateEdgeCurveTransientExtrapolManager
    (CATGeoFactory * iFactory,
     CATSoftwareConfiguration * iConfig,
     CATBody * iBody) = 0;

  //---------------------------
  // CATBodyDatumiser
  //---------------------------
  virtual CATBodyDatumiser *_CreateDatumiser(
    CATGeoFactory * iFactory,
    CATBody *iInputBody,
    const CATTopData & iTopData,
    const CATLISTP(CATICGMObject) * iInputMapping) = 0;

  virtual CATBodyDatumiser *_CreateDatumiser(
    CATGeoFactory * iFactory,
    const CATLISTP(CATBody) & iInputBodies,
    const CATTopData & iTopData,
    const CATLISTP(CATICGMObject) * iInputMapping)= 0;

  virtual CATBodyDatumiser *_CreateFactoryDatumiser(
    CATGeoFactory * iFactory,
    const CATTopData & iTopData)= 0;

  //---------------------------
  // CATCGMObjectConvert
  //---------------------------
  virtual CATCGMObjectConvert *_CreateCGMObjectConvert(
	  CATGeoFactory * iFactory,
	  CATSoftwareConfiguration* iConfig) = 0;

  //---------------------------
  // CATTopInsertClosureVertex
  //---------------------------
  virtual int _InsertClosureVertex(CATGeoFactory       *  iFactory,
    CATBody            *   iClosedWireBody,
    CATBody            *   iVertexBody,
    CATBody            * & oBody,
    const CATTopData   &   iTopData  )= 0;

  //---------------------------
  // CATTopSplitEdge
  //---------------------------
  virtual void _SplitEdge(CATGeoFactory*            iFactory,
                          CATBody*                  iBody, 
                          CATEdge*                  iEdge,
                          const CATSetOfCrvParams&  iSetOfBreaks, 
                          CATBody*&                 oBody,
                          const CATTopData&         iTopData,
                          CATBoolean                iFreezeOn,
                          CATVertex**               ioCreatedVtx,
                          CATEdge**                 ioCreatedEdges,
                          CATBoolean                iRemoveFromFactory = FALSE)= 0;
  
	//---------------------------
  // CATCreateCanonicalGeometry
  //---------------------------
  virtual CATGeometry* _CreateCanonicalGeometry(CATTopData*							ipTopData,
                                                const CATLISTP(CATCell)& iListInputCells,
                                                CATGeometricType         iRequestedType)= 0;
  //---------------------------
  // Pour implementation 
  //---------------------------
  void ResetTouched(CATDomain *iDomain);

  //--------------------------------------------
  // Pour CATCXBodyDatumiser en mode Cleaner 
  //--------------------------------------------
  static void SetCleanerReplaceMode(CATGeoFactory* iFactory, const short iReplaceMode);

  static void UpdateEdgeSimplifiedSupport(CATCGMGeometryOfFatAble*       ipCGMGeometryOfFatAble,
                                          CATEdge*                       ipEdge,
                                          CATEdgeCurve*                  ipNewEdgeCurve,
                                          short                          iOriEdgeCurve,
                                          CATPointOnEdgeCurve*           ipNewStartPOEC,
                                          CATPointOnEdgeCurve*           ipNewEndPOEC,
                                          CATArrayBoundingEdgeHashTable* ipTabArrayBoundingEdges,
                                          CATListDbgPoseSurHashTable*    ipTabListDbgPoseSur);

  //------------------------------------------------------------------
  // INTERNAL USE ONLY  For CATCXVertex::UnlinkUselessGeometry
  //------------------------------------------------------------------
  virtual void _UnlinkUselessGeometry(CATTopology* ipTopology, CATCGMEventType iEventType, CATPoint* ipSpecificPoint, CATBoolean iRemoveFromFactory);

  //------------------------------------------------------------------
  // Remove the Subd data associated with the object
  //------------------------------------------------------------------
  virtual CATBoolean _CompactSubd(CATCGMObject* ipCGMObject);

  //------------------------------------------------------------------
  // Dumps Subd statistics
  //------------------------------------------------------------------
  virtual void _DumpSubdStats(CATCGMOutput& iOutput, int iSortedBy);

  //------------------------------------------------------------------
  // To be able to call CATTopology::GetCellNumbers(...) before CXR14
  //------------------------------------------------------------------
  virtual void _GetCellNumbers(CATTopology* ipTopology, int* iopNbVertices, int* iopNbEdges, int* iopNbFaces, int* iopNbVolumes);

  virtual CATBody* _GetLatestBodyWithMostCells(CATGeoFactory*   ipFactory,
                                               CATGeometricType iCellFilterType,
                                               int*             iopNbVertices,
                                               int*             iopNbEdges,
                                               int*             iopNbFaces,
                                               int*             iopNbVolumes);

  //------------------------------------------------------------------
  // To activate a body
  //------------------------------------------------------------------
  virtual void _Activate(CATBody* ipBody);

 
  virtual CATBoolean _IsLyingOn(CATICGMObject* iObject,CATICGMObject* iSupport);
  
  friend class CATCXBodyCleaner;
};

//---------------------------------------------------------------------------------
// CATCreateBodiesMapping
//---------------------------------------------------------------------------------
INLINE  CATBodiesMapping * CATCGMTopoCXMODEL::CATCreateBodiesMapping(CATTopData * iTopData,
                                                                     const CATBody *iReferenceBody , 
                                                                     const CATBody *iResultBody, const int iSilentMode) 
{
  CATCGMTopoCXMODEL *bridge =  (CATCGMTopoCXMODEL *) (_alreadyInitialised ? _CATCX : FindCGMImplement());
  return bridge ? bridge->_CATCreateBodiesMapping(iTopData,iReferenceBody,iResultBody,iSilentMode) : NULL ;
}

//---------------------------------------------------------------------------------
// CreateBodiesMapping
//---------------------------------------------------------------------------------
INLINE  CATBodiesMapping * CATCGMTopoCXMODEL::CreateBodiesMapping(const CATBody *iReferenceBody , 
                                                                    const CATBody *iResultBody, const int iSilentMode) 
{
  CATCGMTopoCXMODEL *bridge =  (CATCGMTopoCXMODEL *) (_alreadyInitialised ? _CATCX : FindCGMImplement());
  return bridge ? bridge->_CreateBodiesMapping(iReferenceBody,iResultBody,iSilentMode) : NULL ;
}

//---------------------------------------------------------------------------------
// CreateJournalsMapping
//---------------------------------------------------------------------------------
INLINE CATJournalsMapping * CATCGMTopoCXMODEL::CreateJournalsMapping(const CATBody * iReferenceBody,
                                                          const CATCGMJournal * iReferenceJournal,
                                                          const CATBody * iResultBody,
                                                          const CATCGMJournal * iResultJournal,
                                                          CATCGMOutput& os) 
{
  CATCGMTopoCXMODEL *bridge =  (CATCGMTopoCXMODEL *) (_alreadyInitialised ? _CATCX : FindCGMImplement());
  return bridge ? bridge->_CreateJournalsMapping(iReferenceBody,iReferenceJournal,iResultBody,iResultJournal,os) : NULL ;
}


//---------------------------------------------------------------------------------
// CreateJournalsMapping
//---------------------------------------------------------------------------------
INLINE  CATJournalsMapping * CATCGMTopoCXMODEL::CreateJournalsMapping(const CATBody * iReferenceBody,
                                                                     const char * iReferenceJournalFile,
                                                                     const CATBody * iResultBody,
                                                                     const CATCGMJournal * iResultJournal,
                                                                     int iForceWrite)
{
  CATCGMTopoCXMODEL *bridge =  (CATCGMTopoCXMODEL *) (_alreadyInitialised ? _CATCX : FindCGMImplement());
  return bridge ? bridge->_CreateJournalsMapping(iReferenceBody,iReferenceJournalFile,iResultBody,iResultJournal,iForceWrite) : NULL ;
}


//---------------------------------------------------------------------------------
// CreateJournalsMappingMulti
//---------------------------------------------------------------------------------
INLINE CATJournalsMapping * CATCGMTopoCXMODEL::CreateJournalsMappingMulti(const CATLISTP(CATBody)*		ipListReferenceBodies,
                                                                         const CATListOfCATString*		ipListReferenceJournalFiles,
                                                                         const CATLISTP(CATBody)*		ipListResultBodies,
                                                                         const CATLISTP(CATCGMJournal)*	ipListResultJournals,
                                                                         const CATMultiBodiesMapping*	ipMultiBodiesMapping,
                                                                         int iForceWrite)
{
  CATCGMTopoCXMODEL *bridge =  (CATCGMTopoCXMODEL *) (_alreadyInitialised ? _CATCX : FindCGMImplement());
  return bridge ? bridge->_CreateJournalsMappingMulti(ipListReferenceBodies,ipListReferenceJournalFiles,ipListResultBodies,
    ipListResultJournals,ipMultiBodiesMapping,iForceWrite) : NULL ;
}

//---------------------------------------------------------------------------------
// CreateJournalsMappingMulti
//---------------------------------------------------------------------------------
INLINE CATJournalsMapping * CATCGMTopoCXMODEL::CreateJournalsMappingMulti(const CATLISTP(CATBody)*		ipListReferenceBodies,
    const char * iReferenceJournalFile,
                                                                         const CATLISTP(CATBody)*		ipListResultBodies,
                                                                         const CATLISTP(CATCGMJournal)*	ipListResultJournals,
                                                                         const CATMultiBodiesMapping*	ipMultiBodiesMapping,
                                                                         int iForceWrite)
{
  CATCGMTopoCXMODEL *bridge =  (CATCGMTopoCXMODEL *) (_alreadyInitialised ? _CATCX : FindCGMImplement());
  return bridge ? bridge->_CreateJournalsMappingMulti(ipListReferenceBodies,iReferenceJournalFile,ipListResultBodies,
    ipListResultJournals,ipMultiBodiesMapping,iForceWrite) : NULL ;
}




//---------------------------------------------------------------------------------
// CreateJournalMatcher
//---------------------------------------------------------------------------------
INLINE CATJournalMatcher * CATCGMTopoCXMODEL::CreateJournalMatcher(const char * iReferenceFile,
                                                                  int iForceWrite)
{
  CATCGMTopoCXMODEL *bridge =  (CATCGMTopoCXMODEL *) (_alreadyInitialised ? _CATCX : FindCGMImplement());
  return bridge ? bridge->_CreateJournalMatcher(iReferenceFile,iForceWrite) : NULL ;
}



  
//---------------------------------------------------------------------------------
// CATTopGeometricalMapping
//---------------------------------------------------------------------------------
INLINE CATTopGeometricalMapping * CATCGMTopoCXMODEL::CreateMapping( 
    const CATTopData                 & iTopData, 
    const CATLISTP(CATICGMUnknown)   & iInputs,  
    const CATTopGeometricalMapType   iStrategy,
    const CATTopGeoMapping_QueryType iQueries,
    CATGeometricType                 iFilter )
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX )
    return ((CATCGMTopoCXMODEL *)_CATCX)->_CreateMapping(iTopData,iInputs,iStrategy,iQueries,iFilter);
  return NULL;
}

//---------------------------------------------------------------------------------
// CATTopGeometricalMapping
//---------------------------------------------------------------------------------
INLINE CATTopGeometricalMapping * CATCGMTopoCXMODEL::CreateMapping( 
    const CATTopData                & iTopData,
    CATBody                         * iBody,
    const CATTopGeometricalMapType    iStrategy,
    const CATTopGeoMapping_QueryType  iQueries,
    CATGeometricType                  iFilter  )
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX )
    return ((CATCGMTopoCXMODEL *)_CATCX)->_CreateMapping(iTopData,iBody,iStrategy,iQueries,iFilter);
  return NULL;
}

//---------------------------------------------------------------------------------
// CATTopGeometricalMapping
//---------------------------------------------------------------------------------
INLINE CATTopGeometricalMapping * CATCGMTopoCXMODEL::CreateMapping( 
    const CATTopData                & iTopData,
    CATGeoFactory                   * iGeoFactory,
    const CATTopGeometricalMapType    iStrategy,
    const CATTopGeoMapping_QueryType  iQueries,
    CATGeometricType                  iFilter  )
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX )
    return ((CATCGMTopoCXMODEL *)_CATCX)->_CreateMapping(iTopData,iGeoFactory,iStrategy,iQueries,iFilter);
  return NULL;
}

//---------------------------------------------------------------------------------
// CATCGMQueryManager
//---------------------------------------------------------------------------------
INLINE CATCGMQueryManager * CATCGMTopoCXMODEL::CreateQuery(CATCGMQueryManager::TypeOfQuery  iType, 
                                                           CATSoftwareConfiguration * iConfig,
                                                           const CATLISTP(CATICGMUnknown)   & inputs)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX )
    return ((CATCGMTopoCXMODEL *)_CATCX)->_CreateQuery(iType,iConfig,inputs);
  return NULL;
}

//---------------------------
// EdgeCurveTransientExtrapolManager
//---------------------------

INLINE CATEdgeCurveTransientExtrapolManager *
CATCGMTopoCXMODEL::CreateEdgeCurveTransientExtrapolManager
    (CATGeoFactory * iFactory,
     CATSoftwareConfiguration * iConfig,
     CATBody * iBody)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX )
    return 
      ((CATCGMTopoCXMODEL *)_CATCX)->_CreateEdgeCurveTransientExtrapolManager
        (iFactory,iConfig,iBody);
  return NULL;
}

//---------------------------
// CATBodyDatumiser
//---------------------------
INLINE CATBodyDatumiser *CATCGMTopoCXMODEL::CreateDatumiser(CATGeoFactory * iFactory,
                                                            CATBody *iInputBody,
                                                            const CATTopData & iTopData,
                                                            const CATLISTP(CATICGMObject) * iInputMapping)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX )
    return ((CATCGMTopoCXMODEL *)_CATCX)->_CreateDatumiser(iFactory,iInputBody,iTopData,iInputMapping);
  return NULL;
}

INLINE CATBodyDatumiser *CATCGMTopoCXMODEL::CreateDatumiser(CATGeoFactory * iFactory,
                                                            const CATLISTP(CATBody) & iInputBodies,
                                                            const CATTopData & iTopData,
                                                            const CATLISTP(CATICGMObject) * iInputMapping)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX )
    return ((CATCGMTopoCXMODEL *)_CATCX)->_CreateDatumiser(iFactory,iInputBodies,iTopData,iInputMapping);
  return NULL;
}


INLINE CATBodyDatumiser *CATCGMTopoCXMODEL::CreateFactoryDatumiser(CATGeoFactory * iFactory,
                                                            const CATTopData & iTopData)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX )
    return ((CATCGMTopoCXMODEL *)_CATCX)->_CreateFactoryDatumiser(iFactory,iTopData);
  return NULL;
}

INLINE CATCGMObjectConvert * CATCGMTopoCXMODEL::CreateCGMObjectConvert(CATGeoFactory * iFactory,
	                                                   CATSoftwareConfiguration* iConfig)
{
	if ((_alreadyInitialised || FindCGMImplement()) && _CATCX)
		return ((CATCGMTopoCXMODEL *)_CATCX)->_CreateCGMObjectConvert(iFactory, iConfig);
	return NULL;
}

//---------------------------
// InsertClosureVertex
//---------------------------
INLINE int CATCGMTopoCXMODEL::InsertClosureVertex(CATGeoFactory      *   iFactory,
                                           CATBody            *   iClosedWireBody,
                                           CATBody            *   iVertexBody,
                                           CATBody            * & oBody,
                                           const CATTopData   &   iTopData )
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX )
    return ((CATCGMTopoCXMODEL *)_CATCX)->_InsertClosureVertex(iFactory,iClosedWireBody,iVertexBody,oBody,iTopData);
  return -1;
}

//---------------------------
// SplitEdge
//---------------------------
INLINE void CATCGMTopoCXMODEL::SplitEdge(CATGeoFactory*            iFactory,
                                         CATBody*                  iBody, 
                                         CATEdge*                  iEdge,
                                         const CATSetOfCrvParams&  iSetOfBreaks, 
                                         CATBody*&                 oBody,
                                         const CATTopData&         iTopData,
                                         CATBoolean                iFreezeOn,
                                         CATVertex**               ioCreatedVtx,
                                         CATEdge**                 ioCreatedEdges,
                                         CATBoolean                iRemoveFromFactory)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX )
    ((CATCGMTopoCXMODEL *)_CATCX)->_SplitEdge(iFactory,iBody,iEdge,iSetOfBreaks,oBody,iTopData,iFreezeOn,ioCreatedVtx,ioCreatedEdges,iRemoveFromFactory);
}

//---------------------------
// CATCreateCanonicalGeometry
//---------------------------
INLINE CATGeometry* CATCGMTopoCXMODEL::CreateCanonicalGeometry(CATTopData*							 ipTopData,
																																			const CATLISTP(CATCell)& iListInputCells,
																																			CATGeometricType         iRequestedType)
{
 if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX )
    return ((CATCGMTopoCXMODEL *)_CATCX)->_CreateCanonicalGeometry(ipTopData, iListInputCells, iRequestedType);
  return NULL;
}

#endif
