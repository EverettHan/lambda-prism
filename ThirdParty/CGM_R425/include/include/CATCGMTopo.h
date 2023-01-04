/* -*-c++-*- */
#ifndef CATCGMTopo_H_
#define CATCGMTopo_H_
// COPYRIGHT DASSAULT SYSTEMES  2000
//=============================================================================
//  Dynamic invokation of Topology framework
//=============================================================================
// Mar. 03 iObjectsWithLyingOn / iObjectsWithLyingOnUnStreamed pour
//         StreamLyingOnData / UnStreamLyingOnData
// Apr. 03 Parametre iNbLyingOnDataToRead pour UnStreamLyingOnData(...)   HCN 
// Apr. 03 CheckLyingOnAfterUnStream(...),
//         StreamSharpnessData(...), UnStreamSharpnessData(...)           HCN
// Jun. 03 CreateCGMQueryNegativeOffsets(...) pour CATBack                HCN
// Aug. 03 GetLyingOnLinks(...)                                           HCN
// Sep. 03 Parametre iCleanerLike pour GetUselessPoecPCurve(...)          HCN
// Oct. 03 DumpFatDetailedDiagnosis(...)                                  HCN
// Nov. 03 GetStaticSharpnessData(...)
//         DumpStaticSharpnessDataTopo(...)
//         CompactSubd(...)                                               HCN
// Dec. 03 DumpLyingOnLinks(...)                                          HCN
// Feb. 04 GetCellNumbers(...), GetLatestBodyWithMostCells(...),
//         DumpSubdStats(...),
//         UnlinkUselessGeometry(...)                                     HCN
// Apr. 04 Parametre iSortedBy pour DumpSubdStats(...)                    HCN
// May  04 SimplifyEdgeCurve(...) equivalent de CATGeoClean               HCN
// Jun. 04 RI 0454807 : SetCleanerReplaceModeDefinition(...)              HCN
// Jan. 05 Activate                                                       HCN
// Feb. 05 Migration de CATHashTabCATCGMObject vers CATCGMObjectHashTable HCN
// Feb. 05 CATCXTopology_UpDown_Traces                                    HCN
// May  05 DumpFatDetailedDiagnosis(...CATLISTP(CATCGMLimOfParm)*...)     HCN
// Jun. 05 NewGetBoundedTopObjects(...)                                   HCN
// Jul. 05 DumpUpDownStats(...)                                           HCN
// Feb. 06 Suppression de NewGetBoundedTopObjects(...)                    FDN
//=============================================================================
#include "CATIACGMLevel.h"

#include "ExportedByCATCGMFusion.h"
#include "CATICGMContainer.h"
#include "CATMathDef.h"
#include "CATListOfCATICGMUnknowns.h"
#include "CATListOfCATICGMObjects.h"
#include "CATListOfCATCGMLimOfParm.h"
#include "CATCGMOutput.h"
#include "CATCGMEventType.h"
#include "CATMathInline.h"
#include "CATGeoFactory.h"

class CATGeoFactoryCGM;
class CATBody;
class CATTopData;
class CATICGMObject;
class CATCGMJournalList;
class CATSoftwareConfiguration;
class CATTopology;
class CATRootContainerCGM;
class CATCGMObjectHashTable;
class CATCGMStream;
class CATGeoFactory;
class CATCGMContainer;
class CATCGMObject;
class CATPoint;
class CATMacroPoint;
class CATCGMHashTable;
class CATCGMQueryManager;
class CATCell;
class CATLISTP(CATCGMDbgPoseSur);
class CATLISTP(CATCGMGeometryOfFatAble);
class CATCGMSharpnessData;
class CATCGMGeometryOfFatAble;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATLISTP(CATCGMLimOfParm);
class CATTopObject;
class CATDomain;
#if defined ( CATIACGMR216CAA )
class CATTolerance;
#endif

#ifndef CATSide
#define CATSide short // On ne peut pas inclure CATTopDefine.h
#endif

class CATMathStream;
class CATMathFunctionGeneral;
class CATMathFunctionXY;
class CATMathFunctionX;
 
//=================================================================
//  La passerelle GeometricObjectsCGM / NewTopologicalObjectsCGM
//=================================================================
class ExportedByCATCGMFusion CATCGMTopo
{
public:
  //=================================================================
  //  RC=  -1:impossible  0:Already Loaded  1:Just Loaded
  //=================================================================
  static int TopologyIsNeeded();

  //=================================================================
  //  for CATCGMDebug::CheckUpwardLinksTemporaryChange()
  //=================================================================
  static void CheckActivation();
  virtual ~CATCGMTopo();  

  //=================================================================
  //  for CATGeoFactoryCGM() with Topology Needed
  //=================================================================
  static void     Remove(CATGeoFactoryCGM *iFactory, CATBody* iBody,   CATTopData &iTopData);
  static void     CommonRemove( CATGeoFactoryCGM *iFactory, 
                     CATTopology *iObject,
                     const CATICGMContainer::CATRemovingDependancies how,
                     CATCGMJournalList* iInReport,
                     CATSoftwareConfiguration* iConfig) ; 
  
   //=================================================================
  //  CreateBody
  //=================================================================
  static CATBody* CreateBody(CATGeoFactoryCGM     * iFactory , 
                             CATBodyMode            iMode        = CatBodyMode_Working ,
                             const char             iRole[]      = "Unknown",
                             const char           * iTracability = __FILE__ ,
                             const int              iLine        = __LINE__) ;   

  //===========================================================================
  //  detection des POEC et PCurve non utiles selon analyse OPTIMALE ou CLEANER
  //===========================================================================
  static CATBoolean GetUselessPoecPCurve(CATGeoFactory* iFact,
    CATLISTP(CATICGMObject) &oInMacroPoint,
    CATLISTP(CATICGMObject) &oInEdgeCurve,
    CATBoolean               iCleanerLike);

  //======================================================================================================================
  // Pour avoir le meme dump des FatEdges/FatVertices dans
  //   CATCGMTopoCXMODEL::_GetUselessPoecPCurve(...) et
  //   CATCXFactoryTransaction::Snapshot_FatEdges(...)
  //======================================================================================================================
  static void DumpFatDetailedDiagnosis(CATCGMOutput& iOutput, CATLISTP(CATCGMGeometryOfFatAble)* ipListFatAbles, CATGeometricType iGeomTargetType);

  //======================================================================================================================
  // Pour avoir le meme dump des FatEdges/FatVertices/FatExtrapol dans CATCXClean::Run_FatXXX
  //======================================================================================================================
  static void DumpFatDetailedDiagnosis(CATCGMOutput& iOutput, CATLISTP(CATCGMLimOfParm)* ipListLimOfParms);

  //=================================================================
  // Pour cleaning des FatEdgeCurve dans CATCGMGeometryOfFatAble
  //=================================================================
  INLINE static CATBoolean SimplifyEdgeCurve(CATSoftwareConfiguration * iConfig,
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
  INLINE static void SetCleanerReplaceModeDefinition(CATCGMObject* ipCGMObject, const short iReplaceMode);

  //=================================================================
  //  for CATRootContainerCGM() with Topology Needed
  //=================================================================
  static void RemoveRootContents(CATRootContainerCGM *iContainer, const CATBoolean iUserClose);

  static void CheckLyingOnAfterUnStream(CATRootContainerCGM   * iContainer,
                                        CATCGMObjectHashTable * iObjectsWithLyingOn,
                                        CATCGMStream          & Str);

  static void StreamLyingOnData(CATRootContainerCGM   * iContainer,
                                CATCGMObjectHashTable * iObjectsWithLyingOn,
                                CATCGMStream          & Str); 

  static void UnStreamLyingOnData(CATRootContainerCGM   * iContainer,
                                  CATCGMObjectHashTable * iObjectsWithLyingOnUnStreamed,
                                  CATCGMStream          & Str,
                                  CATULONG32            iNbLyingOnDataToRead,
                                  const CATBoolean      iTryPartialLoad); 
  
  // Debug pour verifier la non regression sur lien pose-sur
  INLINE static void DbgPoseSur(CATCGMContainer *iContainer, short iEnding=0); 
  INLINE static void DumpDbgPoseSur(CATCGMOutput& os, CATCGMContainer *iContainer);

  static void StreamSharpnessData(CATRootContainerCGM   * iContainer,
                                  CATCGMObjectHashTable * iObjectsWithSharpnessData,
                                  CATCGMStream          & Str); 

  static void UnStreamSharpnessData(CATRootContainerCGM   *  iContainer,
                                    CATCGMObjectHashTable *  iObjectsWithSharpnessDataUnStreamed,
                                    CATCGMHashTable       ** ippSharpnessDataUnStreamed,
                                    CATCGMStream          &  Str,
                                    CATULONG32            iNbSharpnessDataToRead,
                                    const CATBoolean      iTryPartialLoad); 

  //---------------------------------------------------------------------------------
  //  for CATGem/Debug : * * * DON'T FORGET TO DELETE the CATCGMDbgPoseSur(s) returned * * *
  //---------------------------------------------------------------------------------
  INLINE static void GetLyingOnLinks(CATCell* ipCell, CATLISTP(CATCGMDbgPoseSur)* iopListOfLyingOnLinks);

  INLINE static CATULONG32 DumpLyingOnLinks(CATCell*                    ipCell,
                                            CATCGMOutput&               iOutput,
                                            CATLISTP(CATCGMDbgPoseSur)* ipListOfLyingOnLinks = NULL,
                                            CATULONG32*                 iopNbBadLinks = NULL,
                                            CATULONG32*                 iopNumCellToDisplay = NULL);

  INLINE static CATCGMSharpnessData* GetStaticSharpnessData(CATCell* ipCell, int& ioNbTopoData, int& ioNbGeomData, CATCGMOutput* ipOutput);

  INLINE static void DumpStaticSharpnessDataTopo(CATCell* ipCell, char* ipAlignMSG, CATCGMOutput& iOutput);

  //---------------------------------------------------------------------------------
  //  for CATGem/Debug : traces for CATCXTopology Up/Down operaions
  //---------------------------------------------------------------------------------
  INLINE static void CATCXTopology_UpDown_Traces(int iTraceType, int iActivated);

  INLINE static void DumpUpDownStats(CATCGMContainer* ipContainer, CATCGMOutput& iOutput);

  //---------------------------------------------------------------------------------
  //  for Light Design Mode
  //---------------------------------------------------------------------------------
  INLINE static CATBoolean FullLoading(CATGeoFactory* iFactory);

  //=================================================================
  //  Pour nettoyage des composantes inutiles (de Macro-Point)
  //      2 : lors d'un Unstream (fonction correctrice)
  //      3 : lors du Stream (avec compactage)
  //=================================================================
  static void BetweenStreamAndMemory(CATCGMContainer *iContainer, CATCGMObject  *FirstAdded, CATCGMStream &Str, CATCGMEventType iSpecificContext);


  static CATBoolean IsActive(CATTopology *iTopology, CATBody *iBody); 

  //---------------------------------------------------------------------------------
  //  for CATBack
	//---------------------------------------------------------------------------------
	static CATCGMQueryManager* CreateCGMQueryNegativeOffsets(CATSoftwareConfiguration*       ipConfig, const CATLISTP(CATICGMUnknown)& iInputs);

	INLINE  static CATCGMQueryManager* CreateCGMQueryUsefulLimits(CATSoftwareConfiguration*       ipConfig,  const CATLISTP(CATICGMUnknown)& iInputs);

  //------------------------------------------------------------------
  //  CATMathFunctionGeneral_Stream 
  //------------------------------------------------------------------
  static void CATMathFunctionGeneral_Stream(CATMathStream& Str, CATMathFunctionGeneral *iFunction, const char iLabelReserved[] = ""  );
#if defined ( CATIACGMR216CAA )
  static void CATMathFunctionGeneral_UnStream( CATMathStream& Str, CATMathFunctionXY *&oFunctionXY,const CATTolerance &iTolObject, const char iLabelReserved[] = ""  );
  static void CATMathFunctionGeneral_UnStream( CATMathStream& Str, CATMathFunctionX  *&oFunctionX ,const CATTolerance &iTolObject, const char iLabelReserved[] = ""  );
#else
  static void CATMathFunctionGeneral_UnStream( CATMathStream& Str, CATMathFunctionXY *&oFunctionXY, const char iLabelReserved[] = ""  );
  static void CATMathFunctionGeneral_UnStream( CATMathStream& Str, CATMathFunctionX  *&oFunctionX , const char iLabelReserved[] = ""  );
#endif
  

  //------------------------------------------------------------------
  // INTERNAL USE ONLY  For controlling END Of SubdSession
  //------------------------------------------------------------------
  static  short IsOutsideAnySubdSession(); 

  //------------------------------------------------------------------
  // INTERNAL USE ONLY  For CATCXVertex::UnlinkUselessGeometry
  //------------------------------------------------------------------
  static CATPoint* GetBestPoint(CATMacroPoint *MyMacro);

  INLINE static void UnlinkUselessGeometry(CATTopology* ipTopology, CATCGMEventType iEventType, CATPoint* ipSpecificPoint, CATBoolean iRemoveFromFactory);

  //------------------------------------------------------------------
  // Remove the Subd data associated with the object
  //------------------------------------------------------------------
  INLINE static CATBoolean CompactSubd(CATCGMObject* ipCGMObject);

  //------------------------------------------------------------------
  // Dumps Subd statistics
  //------------------------------------------------------------------
  INLINE static void DumpSubdStats(CATCGMOutput& iOutput, int DumpSubdStats); // 0 = Nb instances, 1 = memory bytes, 2 = name

  //------------------------------------------------------------------
  // To be able to call CATTopology::GetCellNumbers(...) before CXR14
  //------------------------------------------------------------------
  INLINE static void GetCellNumbers(CATTopology* ipTopology, int* iopNbVertices, int* iopNbEdges, int* iopNbFaces, int* iopNbVolumes);

  INLINE static CATBody* GetLatestBodyWithMostCells(CATGeoFactory*   ipFactory,
                                                    CATGeometricType iCellFilterType,
                                                    int*             iopNbVertices,
                                                    int*             iopNbEdges,
                                                    int*             iopNbFaces,
                                                    int*             iopNbVolumes);

  //------------------------------------------------------------------
  // To activate a body
  //------------------------------------------------------------------
  INLINE static void Activate(CATBody* ipBody);

#ifdef NewGetBoundedTopObjects
  //------------------------------------------------------------------
  // GetBoundedTopObjects - Jamais utilise car pas assez efficace
  //------------------------------------------------------------------
  INLINE static int NewGetBoundedTopObjects(CATTopObject*  ipTopObject,
                                            CATBody*       ipBody,
                                            CATTopObject** ioTopObjects,
                                            CATSide*       ioSides,
                                            const int      iSizeOutput,
                                            CATDomain**    ioDomains,
                                            CATGeometry**  ioGeometries);
#endif

  //===========================================================================
  //  Detection Of LyingOn on an objectof the given type
  //===========================================================================
  INLINE static CATBoolean IsLyingOn(CATICGMObject* iObject,CATICGMObject* iSupport);


protected :

  //---------------------------------------------------------------------------------
  // Pure Coverage (mkodtimpact)
  //---------------------------------------------------------------------------------
  void LifeCycleOpen();
  void LifeCycleSave();
  void LifeCycleOthers();

   //=================================================================
  //  CreateBody
  //=================================================================
  virtual CATBody* _CreateBody(CATGeoFactoryCGM     * iFactory , 
                               CATBodyMode            iMode        = CatBodyMode_Working ,
                               const char             iRole[]      = "Unknown",
                               const char           * iTracability = __FILE__ ,
                               const int              iLine        = __LINE__) = 0;    

  //---------------------------------------------------------------------------------
  // Pour implementation CATGeoFactoryCGM
  //---------------------------------------------------------------------------------
  virtual void     _CheckActivation() = 0;
  virtual void     _Remove(CATGeoFactoryCGM *iFactory, CATBody* iBody, CATTopData &iTopData) = 0;
  virtual void     _CommonRemove( CATGeoFactoryCGM *iFactory, 
                     CATTopology *iObject,
                     const CATICGMContainer::CATRemovingDependancies how,
                     CATCGMJournalList* iInReport,
                     CATSoftwareConfiguration* iConfig) = 0; 

  virtual CATBoolean _GetUselessPoecPCurve(CATGeoFactory*           iFact,
                                           CATLISTP(CATICGMObject)& oInMacroPoint,
                                           CATLISTP(CATICGMObject)& oInEdgeCurve,
                                           CATBoolean               iCleanerLike) = 0; 

  virtual void _DumpFatDetailedDiagnosis(CATCGMOutput& iOutput, CATLISTP(CATCGMGeometryOfFatAble)* ipListFatAbles, CATGeometricType iGeomTargetType) = 0;

  virtual void _DumpFatDetailedDiagnosis(CATCGMOutput& iOutput, CATLISTP(CATCGMLimOfParm)* ipListLimOfParms) = 0;

  virtual CATBoolean _SimplifyEdgeCurve(CATSoftwareConfiguration * iConfig,
                                        CATCGMGeometryOfFatAble* ipCGMGeometryOfFatAble,
                                        CATEdgeCurve**           ioppNewEdgeCurve,
                                        short*                   ioOriEdgeCurve,
                                        CATBoolean*              ioNewEdgeCurve,
                                        CATPointOnEdgeCurve**    ioppNewStartPOEC,
                                        CATPointOnEdgeCurve**    ioppNewEndPOEC,
                                        CATBoolean*              ioNewPOECs,
                                        CATBoolean*              ioReversedOrientations,
                                        CATBoolean*              iopIsSimplifiable) = 0;

  virtual void _SetCleanerReplaceModeDefinition(CATCGMObject* ipCGMObject, const short iReplaceMode) = 0;

  //=================================================================
  //  for CATRootContainerCGM() with Topology Needed
  //=================================================================
  virtual void _RemoveRootContents(CATRootContainerCGM *iContainer, const CATBoolean iUserClose)= 0; 
  virtual void _BetweenStreamAndMemory(CATCGMContainer *iContainer, CATCGMObject  *FirstAdded, CATCGMStream &Str, CATCGMEventType iSpecificContext)= 0; 

  virtual void _CheckLyingOnAfterUnStream(CATRootContainerCGM   * iContainer,
                                          CATCGMObjectHashTable * iObjectsWithLyingOn,
                                          CATCGMStream          & Str) = 0;

  virtual void _StreamLyingOnData(CATRootContainerCGM   * iContainer,
                                  CATCGMObjectHashTable * iObjectsWithLyingOn,
                                  CATCGMStream          & Str) = 0;
 
  virtual void _UnStreamLyingOnData(CATRootContainerCGM   * iContainer,
                                    CATCGMObjectHashTable * iObjectsWithLyingOnUnStreamed,
                                    CATCGMStream          & Str,
                                    CATULONG32            iNbLyingOnDataToRead,
                                    const CATBoolean      iTryPartialLoad) = 0;

  virtual void _StreamSharpnessData(CATRootContainerCGM   * iContainer,
                                    CATCGMObjectHashTable * iObjectsWithSharpnessData,
                                    CATCGMStream          & Str) = 0; 

  virtual void _UnStreamSharpnessData(CATRootContainerCGM   *  iContainer,
                                      CATCGMObjectHashTable *  iObjectsWithSharpnessDataUnStreamed,
                                      CATCGMHashTable       ** ippSharpnessDataUnStreamed,
                                      CATCGMStream          &  Str,
                                      CATULONG32            iNbSharpnessDataToRead,
                                      const CATBoolean      iTryPartialLoad) = 0; 

  //---------------------------------------------------------------------------------
  //  for CATCXDebug shared-lib
  //---------------------------------------------------------------------------------
  virtual CATBoolean _IsActive(CATTopology *iTopology, CATBody *iBody ) = 0; 
  
  virtual short  _IsOutsideAnySubdSession() = 0;
  
  virtual void   _DbgPoseSur(CATCGMContainer *iContainer, short iEnding=0) = 0;
  virtual void   _DumpDbgPoseSur(CATCGMOutput& os, CATCGMContainer *iContainer) = 0;

  //---------------------------------------------------------------------------------
  //  for CATGem/Debug
  //---------------------------------------------------------------------------------
  virtual void   _GetLyingOnLinks(CATCell* ipCell, CATLISTP(CATCGMDbgPoseSur)* iopListOfLyingOnLinks) = 0;

  virtual CATULONG32    _DumpLyingOnLinks(CATCell*                    ipCell,
                                          CATCGMOutput&               iOutput,
                                          CATLISTP(CATCGMDbgPoseSur)* ipListOfLyingOnLinks,
                                          CATULONG32*                 iopNbBadLinks,
                                          CATULONG32*                 iopNumCellToDisplay) = 0;

  virtual CATCGMSharpnessData* _GetStaticSharpnessData(CATCell* ipCell, int& ioNbTopoData, int& ioNbGeomData, CATCGMOutput* ipOutput) = 0;

  virtual void _DumpStaticSharpnessDataTopo(CATCell* ipCell, char* ipAlignMSG, CATCGMOutput& iOutput) = 0;

  virtual void _CATCXTopology_UpDown_Traces(int iTraceType, int iActivated) = 0;

  virtual void _DumpUpDownStats(CATCGMContainer* ipContainer, CATCGMOutput& iOutput) = 0;
  
  //---------------------------------------------------------------------------------
  //  for Light Design Mode
  //---------------------------------------------------------------------------------
  virtual CATBoolean _FullLoading(CATGeoFactory* iFactory) = 0;

  //---------------------------------------------------------------------------------
  //  for CATBack
  //---------------------------------------------------------------------------------
  virtual CATCGMQueryManager* _CreateCGMQueryNegativeOffsets(CATSoftwareConfiguration*       ipConfig, const CATLISTP(CATICGMUnknown)& iInputs) = 0;

  virtual CATCGMQueryManager* _CreateCGMQueryUsefulLimits(CATSoftwareConfiguration*       ipConfig, const CATLISTP(CATICGMUnknown)& iInputs) = 0;

  //------------------------------------------------------------------
  // INTERNAL USE ONLY  For CATCXVertex::UnlinkUselessGeometry
  //------------------------------------------------------------------
  virtual void _UnlinkUselessGeometry(CATTopology* ipTopology, CATCGMEventType iEventType, CATPoint* ipSpecificPoint, CATBoolean iRemoveFromFactory) = 0;

  //------------------------------------------------------------------
  // Remove the Subd data associated with the object
  //------------------------------------------------------------------
  virtual CATBoolean _CompactSubd(CATCGMObject* ipCGMObject) = 0;

  //------------------------------------------------------------------
  // Dumps Subd statistics
  //------------------------------------------------------------------
  virtual void _DumpSubdStats(CATCGMOutput& iOutput, int DumpSubdStats) = 0;

  //------------------------------------------------------------------
  // To be able to call CATTopology::GetCellNumbers(...) before CXR14
  //------------------------------------------------------------------
  virtual void _GetCellNumbers(CATTopology* ipTopology, int* iopNbVertices, int* iopNbEdges, int* iopNbFaces, int* iopNbVolumes) = 0;

  virtual CATBody* _GetLatestBodyWithMostCells(CATGeoFactory*   ipFactory,
                                               CATGeometricType iCellFilterType,
                                               int*             iopNbVertices,
                                               int*             iopNbEdges,
                                               int*             iopNbFaces,
                                               int*             iopNbVolumes) = 0;

  //------------------------------------------------------------------
  // To activate a body
  //------------------------------------------------------------------
  virtual void _Activate(CATBody* ipBody) = 0;

#ifdef NewGetBoundedTopObjects
  //------------------------------------------------------------------
  // GetBoundedTopObjects - jamais utilise car pas assez efficace
  //------------------------------------------------------------------
  virtual int _NewGetBoundedTopObjects(CATTopObject*  ipTopObject,
                                       CATBody*       ipBody,
                                       CATTopObject** ioTopObjects,
                                       CATSide*       ioSides,
                                       const int      iSizeOutput,
                                       CATDomain**    ioDomains,
                                       CATGeometry**  ioGeometries) = 0;
#endif

  virtual CATBoolean _IsLyingOn(CATICGMObject* iObject,CATICGMObject* iSupport) = 0;
  //---------------------------------------------------------------------------------
  // Pour gestion Locale au Framwork GeometricObjectsCGM
  //---------------------------------------------------------------------------------
  CATCGMTopo();
  static INLINE CATCGMTopo *GetCGMImplement();
  static CATCGMTopo * FindCGMImplement();

  static CATCGMTopo *_CATCX;
  static int         _alreadyInitialised;
};




CATCGMQueryManager* CATCGMTopo::CreateCGMQueryUsefulLimits(CATSoftwareConfiguration*       ipConfig, const CATLISTP(CATICGMUnknown)& iInputs) 
{ return ( (_alreadyInitialised || FindCGMImplement()) && _CATCX ) ?  _CATCX->_CreateCGMQueryUsefulLimits(ipConfig,iInputs) : NULL ; }

//---------------------------------------------------------------------------------
// GetCGMImplement ...
//---------------------------------------------------------------------------------
INLINE CATCGMTopo * CATCGMTopo::GetCGMImplement()   
{
  if (_alreadyInitialised == 0)  FindCGMImplement();
  return CATCGMTopo::_CATCX;
}

//---------------------------------------------------------------------------------
// Debug pour verifier la non regression sur lien pose-sur
//---------------------------------------------------------------------------------
INLINE void CATCGMTopo::DbgPoseSur(CATCGMContainer *iContainer, short iEnding)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX ) _CATCX->_DbgPoseSur(iContainer,iEnding);
}

INLINE void CATCGMTopo::DumpDbgPoseSur(CATCGMOutput& os, CATCGMContainer *iContainer)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX ) _CATCX->_DumpDbgPoseSur(os,iContainer);
}

//---------------------------------------------------------------------------------
// Light Design Mode
//---------------------------------------------------------------------------------
INLINE CATBoolean CATCGMTopo::FullLoading(CATGeoFactory* iFactory)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX ) return _CATCX->_FullLoading(iFactory);
  return FALSE;
}

//---------------------------------------------------------------------------------
//  for CATGem/Debug
//---------------------------------------------------------------------------------
INLINE void CATCGMTopo::GetLyingOnLinks(CATCell* ipCell, CATLISTP(CATCGMDbgPoseSur)* iopListOfLyingOnLinks)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX ) _CATCX->_GetLyingOnLinks(ipCell, iopListOfLyingOnLinks);
}

INLINE CATULONG32 CATCGMTopo::DumpLyingOnLinks(CATCell*                    ipCell,
                                               CATCGMOutput&               iOutput,
                                               CATLISTP(CATCGMDbgPoseSur)* ipListOfLyingOnLinks,
                                               CATULONG32*                 iopNbBadLinks,
                                               CATULONG32*                 iopNumCellToDisplay)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX )
    return _CATCX->_DumpLyingOnLinks(ipCell, iOutput, ipListOfLyingOnLinks, iopNbBadLinks, iopNumCellToDisplay);
  else
    return 0;
}

INLINE CATCGMSharpnessData* CATCGMTopo::GetStaticSharpnessData(CATCell* ipCell, int& ioNbTopoData, int& ioNbGeomData, CATCGMOutput* ipOutput)
{
  ioNbTopoData = ioNbGeomData = 0;

  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX )
    return _CATCX->_GetStaticSharpnessData(ipCell, ioNbTopoData, ioNbGeomData, ipOutput);
  else
    return NULL;
}

INLINE void CATCGMTopo::DumpStaticSharpnessDataTopo(CATCell* ipCell, char* ipAlignMSG, CATCGMOutput& iOutput)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX ) _CATCX->_DumpStaticSharpnessDataTopo(ipCell, ipAlignMSG, iOutput);
}

INLINE void CATCGMTopo::CATCXTopology_UpDown_Traces(int iTraceType, int iActivated)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX ) _CATCX->_CATCXTopology_UpDown_Traces(iTraceType, iActivated);
}

INLINE void CATCGMTopo::DumpUpDownStats(CATCGMContainer* ipContainer, CATCGMOutput& iOutput)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX ) _CATCX->_DumpUpDownStats(ipContainer, iOutput);
}

//------------------------------------------------------------------
// INTERNAL USE ONLY  For CATCXVertex::UnlinkUselessGeometry
//------------------------------------------------------------------
INLINE void CATCGMTopo::UnlinkUselessGeometry(CATTopology* ipTopology, CATCGMEventType iEventType, CATPoint* ipSpecificPoint, CATBoolean iRemoveFromFactory)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX ) _CATCX->_UnlinkUselessGeometry(ipTopology, iEventType, ipSpecificPoint,iRemoveFromFactory );
}

//---------------------------------------------------------------------------------
// Remove the Subd data associated with the object
//---------------------------------------------------------------------------------
INLINE CATBoolean CATCGMTopo::CompactSubd(CATCGMObject* ipCGMObject)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX )
    return _CATCX->_CompactSubd(ipCGMObject);
  else
    return FALSE;
}

//------------------------------------------------------------------
// Dumps Subd statistics
//------------------------------------------------------------------
INLINE void CATCGMTopo::DumpSubdStats(CATCGMOutput& iOutput, int DumpSubdStats)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX ) _CATCX->_DumpSubdStats(iOutput, DumpSubdStats);
}

//------------------------------------------------------------------
// To be able to call CATTopology::GetCellNumbers(...) before CXR14
//------------------------------------------------------------------
INLINE void CATCGMTopo::GetCellNumbers(CATTopology* ipTopology, int* iopNbVertices, int* iopNbEdges, int* iopNbFaces, int* iopNbVolumes)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX ) _CATCX->_GetCellNumbers(ipTopology, iopNbVertices, iopNbEdges, iopNbFaces, iopNbVolumes);
}

INLINE CATBody* CATCGMTopo::GetLatestBodyWithMostCells(CATGeoFactory*   ipFactory,
                                                       CATGeometricType iCellFilterType,
                                                       int*             iopNbVertices,
                                                       int*             iopNbEdges,
                                                       int*             iopNbFaces,
                                                       int*             iopNbVolumes)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX )
    return _CATCX->_GetLatestBodyWithMostCells(ipFactory, iCellFilterType, iopNbVertices, iopNbEdges, iopNbFaces, iopNbVolumes);
  else
    return NULL;
}


INLINE CATBoolean CATCGMTopo::SimplifyEdgeCurve(CATSoftwareConfiguration * iConfig,
                                                CATCGMGeometryOfFatAble* ipCGMGeometryOfFatAble,
                                                CATEdgeCurve**           ioppNewEdgeCurve,
                                                short*                   ioOriEdgeCurve,
                                                CATBoolean*              ioNewEdgeCurve,
                                                CATPointOnEdgeCurve**    ioppNewStartPOEC,
                                                CATPointOnEdgeCurve**    ioppNewEndPOEC,
                                                CATBoolean*              ioNewPOECs,
                                                CATBoolean*              ioReversedOrientations,
                                                CATBoolean*              iopIsSimplifiable)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX )
    return _CATCX->_SimplifyEdgeCurve(iConfig,
                                      ipCGMGeometryOfFatAble,
                                      ioppNewEdgeCurve,
                                      ioOriEdgeCurve,
                                      ioNewEdgeCurve,
                                      ioppNewStartPOEC,
                                      ioppNewEndPOEC,
                                      ioNewPOECs,
                                      ioReversedOrientations,
                                      iopIsSimplifiable);
  else
    return FALSE;
}

//------------------------------------------------------------------
// SetCleanerReplaceModeDefinition
//------------------------------------------------------------------
INLINE void CATCGMTopo::SetCleanerReplaceModeDefinition(CATCGMObject* ipCGMObject, const short iReplaceMode)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX ) _CATCX->_SetCleanerReplaceModeDefinition(ipCGMObject, iReplaceMode);
}

//------------------------------------------------------------------
// Activate
//------------------------------------------------------------------
INLINE void CATCGMTopo::Activate(CATBody* ipBody)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX ) _CATCX->_Activate(ipBody);
}

#ifdef NewGetBoundedTopObjects
//------------------------------------------------------------------
// GetBoundedTopObjects - jamais utilise car pas assez efficace
//------------------------------------------------------------------
INLINE int CATCGMTopo::NewGetBoundedTopObjects(CATTopObject*  ipTopObject,
                                               CATBody*       ipBody,
                                               CATTopObject** ioTopObjects,
                                               CATSide*       ioSides,
                                               const int      iSizeOutput,
                                               CATDomain**    ioDomains,
                                               CATGeometry**  ioGeometries)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX )
    return _CATCX->_NewGetBoundedTopObjects(ipTopObject,
                                            ipBody,
                                            ioTopObjects,
                                            ioSides,
                                            iSizeOutput,
                                            ioDomains,
                                            ioGeometries);
  else
    return FALSE;
}
#endif

INLINE CATBoolean CATCGMTopo::IsLyingOn(CATICGMObject* iObject,CATICGMObject* iSupport)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _CATCX ) 
    return _CATCX->_IsLyingOn(iObject,iSupport);
  else
    return FALSE;
}


#endif
