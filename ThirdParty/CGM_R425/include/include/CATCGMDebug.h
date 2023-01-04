/* -*-c++-*- */
#ifndef CATCGMDebug_H_
#define CATCGMDebug_H_
// COPYRIGHT DASSAULT SYSTEMES  1999
//=============================================================================
//  Dedicated to NCGM debug FOR INTERNAL CGM USE
// To Debug Implementation NCGM on CGM Interfaces,
//  You must point to this API rather than address GeometricObjectsCGM Implementation 
//=============================================================================
// Jui. 02  Portage 64 bits                                               HCN
// Sep. 03  Parametre iCleanerLike pour GetUselessComponent(...)          HCN
// Oct. 03  PurgeNonPersistent(...)
// Oct. 03  GetMaxTag(...)                                                HCN
//          DumpStatsGeometricTypes(...)                                  HCN
// Nov. 03  GetLockCount(...)
//          DumpStaticSharpnessDataGeom(...)                              HCN
// Jan. 04  DelKnotVectorOptData(...)                                     HCN
// Jan. 04  Macros pour passer des bodies autorises au fat edge completed FDN
// Feb. 04  UnlinkUselessGeometry(...)                                    HCN
// Mar. 04  CompareFactories (...)                                        MNA
// Apr. 04  Ajout d'un argument (CATLISTP(CATICGMObject) oAllDifferentObj)
//          dans la methode CompareFactories (...)                        MNA
// Avr. 04  struct CATGeoClnCheckParameter devient une classe             FDN
// May  04  CompactSubd(...)                                              HCN
// May  04  SimplifyEdgeCurve(...) equivalent de CATGeoClean              HCN
// Jun. 04  CompareExactAndApproxNurbs (...)                              MNA
// Jul. 04  CompareExactAndApproxPNurbs (...)                             MNA
// Jul. 04  POECStreamCompact(...), POECUnstreamCompact(...)              HCN
// Mar. 05  Stream ordonne des objets pointes : StreamObject(...)         HCN
// Jun. 05  Methode IncDecUseCount                                        FDN
// Jui. 05  Methode SetRemovable                                          FDN
// Jul. 05  Statistiques parcours UpDown :
//            SetFactoryCurrentOperator(...)                              HCN
// Aug. 05  GetCATGeometricType(...),
//          SetFactoryCurrentBnddCellIter(...),
//          SetFactoryCurrentUpDownCallingMethod(...)                     HCN
// Jui. 07  Permettre Performance de contexte                             TCX
// Jul. 09  Suppression du StreamCompact                                  VUC
// Oct. 09  IncrementalStream : IsActivated,Load,Save,...                 VUC
//=============================================================================

#include "ExportedByGeometricObjects.h"
#include "CATCGMOutput.h"
#include "CATCGMBOAObject.h"
#include "CATCGMScaleCategoryDef.h"
#include "CATMathDef.h"
#include "CATErrorDef.h"
#include "CATCGMStreamVersion.h"
#include "CATGeometryType.h"
#include "CATCGMFederatorsFilter.h"

#include "CATListOfCATICGMObjects.h"
#include "CATListOfCATCGMLimOfParm.h"
#include "CATListOfCATPoints.h"
#include "CATListOfCATCurves.h"
#include "CATCGMFactoryStatus.h"
#include "CATGeoClnIDs.h"
#include "CATCGMEventType.h"

// For macro fat edge detection
#include "CATCGMCleanerActivation.h"
#include "CATGeoClnCheckParameter.h"

#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATMathInline.h"
#include "CATCGMStreamVersion.h"
#include "CATMathStreamDef.h"

//incremental stream
#include "CATListOfCATCGMStream.h"
#include "CATIACGMLevel.h"


class CATCGMPeriodicityInfo;



/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class istream;
#endif
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
class CATCGMStream;
class CATICGMUnknown;
class CATICGMObject;
class CATICGMContainer;
class CATCell;
class CATGeoFactory;
class CATCGMOperator;
class CATCGMObject;
class CATCGMVersionDefinition;
class CATCGMDebugLocal;
class CATExtCGMReplay;
class CATCGMTempoULONGPTR;
class CATGeometry;
class CATGeoTemporary;
class CATListPtrCATCGMObject;
class CATGeoClnCheckParameter;
class CATTopology;
struct CATCGMHeaderObjectStream;
class CATPointOnEdgeCurve;
class CATCGMGeometryOfFatAble;
class CATEdgeCurve;
class CATBoundedCellsIterator;
class CATCGMGraph;
class CATGeoFactoryProtected;
class CATMapVoidToVoid ;
class CATStream ;
class CATCGMStreamImpl ;
class CATCGMChain;

class CATGeometry ;
class CATCurve ;
class CATSurface ;
class CATPCurve ;
class CATPoint ;
class CATMacroPoint ;
class CATBaseUnknown ;
#ifndef NULL
#define NULL 0
#endif

// Macro for fat edge detection before completed
#ifndef FAT_EDGE_BEFORE_COMPLETED_WITH_AUTORIZED_BODIES
#define FAT_EDGE_BEFORE_COMPLETED_WITH_AUTORIZED_BODIES(pBodyToCheck, pListOfAutorized, IdentityBuildOperator) { \
  if (CATCGMCleanerIsActive())\
  {\
    CATGeoClnCheckParameter chkruleParam;\
    chkruleParam._pRuleID   = CATGeoClnIDs::FatEdgesForBodyCompleted;\
    chkruleParam._DataSize  = sizeof(pListOfAutorized);\
    chkruleParam._pData     = (void*) pListOfAutorized;\
    CATCGMDebug::CGMCleanerCheckSelectRuleBegin(CATGeoClnIDs::FatEdgesForBodyCompleted, &chkruleParam);\
  }\
}
#endif
 


// UsageContext  
enum CATCGMUnknown_UsageContext 
{
  CatCGMUnknown_NCGM,
  CatCGMUnknown_CATSpecDocument,
  CatCGMUnknown_CGMReplay,
  CatCGMUnknown_Unidentified
};
 

class CATICGMUnknown;
class CATCGMContainer;
class CATListPtrCATEdgeCurve;
class CATCompareContext;
class CATCompareGeometry;
class CATCGMDirtify;


//-------------------------------------------------------------------------
// CATCGMDebug
//-------------------------------------------------------------------------
class ExportedByGeometricObjects CATCGMDebug
{
public:
  
  //---------------------------------------------------------------------------------
  // GetUsageContext
  //---------------------------------------------------------------------------------
  INLINE static CATCGMUnknown_UsageContext   GetUsageContext(CATICGMUnknown *iCGMObject);

  //=================================================================
  // const char* to CATGeometricType conversion
  //=================================================================
  INLINE static CATGeometricType GetCATGeometricType(const char* ipGeometricTypeName);

  //=================================================================
  // From GeoFactory To Federators of modelisation
  //=================================================================
  static void GetFederators(CATGeoFactory*            iFactory,
                            CATLISTP(CATICGMObject) & ioFederators, 
                            CATCGMFederatorsFilter    iFilterSpec = CATCGMFederatorsFilter_SpecifiedByDocument,
                            CATGeometricType          iFilterType = CATBodyType );



  //=================================================================
  //  New GeoFactory
  //=================================================================
  static CATGeoFactory* CATCreateCGMContainer (const CATCGMScaleCategory iScale,
                                               const CATPositiveLength iUnitInMeter=.001);//@NumValidated 

  static CATGeoFactory* CATCreateCGMContainer (const CATPositiveLength iUnitInMeter=.001);//@NumValidated 

  //=================================================================
  //  Load GeoFactory
  //=================================================================
  static void Load(const char iFilename[],
                   CATGeoFactory* &oFactory,
                   const CATBoolean      avoidAnyRattrap = FALSE,
                   CATCGMStreamVersion  *iWantingVersion = NULL);



  static CATGeoFactory* CATLoadCGMContainer(  istream& iStreamArea,
                                              const CATCGMVersionDefinition **ptrUnstreamVersion = NULL);

  static CATGeoFactory* CGMLoadRootContainer( CATCGMStream             & streamarea,
                                              const CATCGMVersionDefinition ** ptrUnstreamVersion = NULL,
                                              const CATBoolean                 avoidAnyRattrap = FALSE );

  
  //=================================================================
  // Integration CATCGMPeriodicityManager Procedural 
  //   gestion implementative sans impact Interface 
  //=================================================================
  INLINE static CATBoolean CATCGMPeriodicityManager_GetInfo( CATCurve * iCurve, CATCGMPeriodicityInfo & oInfo );
  INLINE static CATBoolean CATCGMPeriodicityManager_GetInfo( CATSurface * iSurface, CATBoolean iUorV, CATCGMPeriodicityInfo & oInfo );

  //=================================================================
  //   integration Native sans impact Exposition Interface  
  //=================================================================
  INLINE static void CATCGMPeriodicityManager_SetInfo( CATSurface * iSurface, CATBoolean iUorV, const CATCGMPeriodicityInfo & iInfo );
  INLINE static void CATCGMPeriodicityManager_SetInfo( CATCurve * iCurve, const CATCGMPeriodicityInfo & iInfo );

  //=================================================================
  //  Save GeoFactory
  //=================================================================
  static void Save(const CATGeoFactory* iFactory, 
                   const char iFilename[],
                   const int iWithTass=1,
                   const CATCGMStreamVersion iWantingVersion = CatCGMStream_UnknownVersion);

  static void CATSaveCGMContainer(const CATGeoFactory* iFact, 
                                  ostream& ioStreamArea,
                                  const CATCGMStreamVersion iWantingVersion = CatCGMStream_UnknownVersion);

  static HRESULT CATSaveCGMContainer(const CATGeoFactory* iFact, 
                                  CATCGMStream & ioStreamArea);

  //=================================================================
  // VUC : 16-10-09 Incremental Stream
  //=================================================================

  //if forceactivation > 0 --> activate incrementalstream
  //if forceactivation < 0 --> deactivate incrementalstream
  //the environnement variable is still of higher priority(if set, you can't unset the incremental stream)
  static int IsIncrementalStreamActivated();
  static int IsIncrementalStreamTraceActivated();
  static int IsIncrementalStreamTest();
  static int GetIncrementalStreamTestMode(CATBoolean iSwitchMode);
	
	static void SetIncrementalStreamActivated();


  static CATGeoFactory* CGMIncrementalLoadRootContainer(CATLISTP(CATCGMStream )          &streamarea,
                                              const CATCGMVersionDefinition             **ptrUnstreamVersion = NULL,
                                              const CATBoolean                            avoidAnyRattrap = FALSE);

  static HRESULT CGMIncrementalSaveContainer(const CATGeoFactory* iFactory,   
                                               CATCGMStream & TheStream, 
                                               const CATCGMStreamVersion iWantingVersion = CatCGMStream_UnknownVersion ); 

  //check if the current state of the factory can be recovered with incremental Stream
  //for that purpose the increments streams are stored on the container
  static HRESULT CheckIncrementalStream( const CATGeoFactory* FactorytoCheck, CATCGMOperator *iOperator);

  /**
  * VUC 2009-10-28
  * Mark an object as Dirty : modified but not saved
  * @param iObject 
  *  The input interface on the object to mark.
  * @return
  * <br><b>Legal values</b>:
  * <dl><dt>S_OK</dt><dd>when marking was done correctly.
  * <dt>E_FAIL</dt><dd>otherwise
  *</dl>
  */
  INLINE static HRESULT SetWasModified(CATICGMObject* iObject);

  //=================================================================
  //  Duplicate
  //=================================================================
  static void Duplicate(CATGeoFactory* iFactory, CATGeoFactory*& oFactory);

  //=================================================================
  //  Close GeoFactory
  //=================================================================
  static void CATCloseCGMContainer  (CATGeoFactory* iFact);

  //=================================================================
  // Pour Fusion
  //=================================================================
  INLINE static void NewFactory(CATGeoFactory* & itf, CATCGMContainer * & impl
                               ,const CATCGMScaleCategory iScaleCategory=ScaleNotSet);
  INLINE static CATICGMUnknown *CreateTIECATGeoFactoryCATGeoFactoryCGM(CATCGMContainer* impl);
  INLINE static CATPCurve *GetProtectedPCurve(CATSurface* impl,CATLONG32 i);
  INLINE static long       GetNumberOfProtectedPCurves(CATSurface* impl);
  INLINE static CATPoint * GetBestPoint(CATMacroPoint* impl);

  //=================================================================
  // Pour modele compacte
  //=================================================================

  INLINE static CATBoolean AddParamToPOEC(CATPointOnEdgeCurve* ipPOEC,
                                          const CATLONG32      iSpecCount, 
                                          const CATCurve**     ippCurves,
                                          const double*        ipLocalParamValues,
                                          const CATLONG32*     ipArcValues);


  //=================================================================
  // Stream ordonne des objets pointes 
  //=================================================================
  INLINE static void StreamObject(CATICGMObject* ipObject, CATCGMStream& Str);
  
  //=================================================================
  //   Test d'acces au debug interactif
  //=================================================================
  static CATBoolean CATCGMDebugUI(CATICGMObject* iObject);

  //=================================================================
  //   CGM Factory Management Detection of Useless Geometry
  //    for any document and Unit Tests of CGM organization
  //    return a TRUE value if Object Leaks are detected ...
  //   You must know and specify the geometrical federators Objects 
  //     that are expected in the CATGeoFactory
  //=================================================================
  static CATBoolean GetNewObjectLeaks(CATGeoFactory* iFact,
    const CATLISTP(CATICGMObject) &iExpectedNewObjects, 
    CATLISTP(CATICGMObject) &ioFederators, CATLISTP(CATICGMObject) &ioAlls);
  

  //=================================================================
  // for CATPart document, CGM Factory Management Detection of Useless Geometry
  //=================================================================
  static CATBoolean GetNotPersistent(CATGeoFactory* iFact,
    CATLISTP(CATICGMObject) &ioFederators, CATLISTP(CATICGMObject) &ioAlls);
  
  static CATBoolean GetUselessComponent(CATGeoFactory* iFact,
    CATLISTP(CATICGMObject) &ioInMacroPoint, CATLISTP(CATICGMObject) &ioInEdgeCurve, CATBoolean iCleanerLike);

  static INLINE void PurgeNonPersistent(int WithPrecaution=0);
  
  //=================================================================================
  // Controle du type de la Factory (distinction Factory V5 et autres types (V4,..)
  //   une valeur de retour non nulle signifie qu'il s'agit bien d'une Factory V5
  //   et dans ce cas, on renvoie l'interface native de la Factory ....
  //=================================================================================
  static CATGeoFactory* IsFactoryCNEXT(CATGeoFactory *iFact); 


  //=================================================================================
  // Passage transparent TIEBOA  CATGeoFactory -> CATGeoFactoryProtected
  //=================================================================================
   static INLINE CATGeoFactoryProtected* GetProtectedInterface(CATGeoFactory *iFact) ;
#if defined ( CATCGMBOAObject )
   static INLINE void InitRootContainer(CATGeoFactoryProtected *iFactoryProtected) ;
#endif


  //==================================================================================
  //  Recuperation du tag maximal dans une factory pour les checks differentiels
  //  (par exemple CATCXFactoryTransaction::Snapshot_FatEdges(...))
  //==================================================================================
  INLINE static CATULONG32 GetMaxTag(CATGeoFactory *iFact);
  
  //==================================================================================
  //  Comparaison du contenu de deux factory sauvegardees sur 2 cgmlevel differents
  //==================================================================================

  INLINE static CATBoolean CompareFactories(CATGeoFactory * iFacto1,CATGeoFactory * iFacto2,CATLISTP(CATICGMObject) &oAllDifferentObj);

  //==================================================================================
  //  Comparaison des surfaces nurbs contenues dans 2 factories differentes (nurbs exacte dans l'une et Nurbs approchee dans l'autre)
  //==================================================================================

  INLINE static CATBoolean CompareExactAndApproxNurbs(CATGeoFactory * iFacto1,CATGeoFactory * iFacto2,CATLISTP(CATICGMObject) &oAllDifferentsNurbs);

  //==================================================================================
  //  Comparaison des PNurbs contenues dans 2 factories differentes (nurbs exacte dans l'une et Nurbs approchee dans l'autre)
  //==================================================================================
  
  INLINE static CATBoolean CompareExactAndApproxPNurbs(CATGeoFactory * iFacto1,CATGeoFactory * iFacto2,CATLISTP(CATICGMObject) &oAllDifferentsPNurbs);
 
  INLINE static CATCGMOperator* SetFactoryCurrentOperator(CATCGMOperator* ipCGMOperator, CATGeoFactory* ipFactory);
  INLINE static CATBoundedCellsIterator* SetFactoryCurrentBnddCellIter(CATBoundedCellsIterator* ipBnddCellIter, CATGeoFactory* ipFactory);
  INLINE static int SetFactoryCurrentUpDownCallingMethod(int iUpDownCallingMethod, CATGeoFactory* ipFactory);

  //=================================================================
  //   GetContents : provide contents as HT of CATCGMObjects
  //=================================================================
  INLINE static void GetContents(CATGeoFactory* iFactory, CATMapVoidToVoid  * & ioContents);
  
  //=================================================================
  //   GetDump : provide Dump (For ODT)
  //=================================================================
  INLINE static void GetDump(CATICGMObject* iCGMObject, CATUnicodeString & oDumpDefinition );
  
#if defined ( CATCGMBOAObject )
  INLINE static CATBaseUnknown* CATRootContainerCGM_CreationCGM(CATCGMContainer * iContainer);
  INLINE static CATCGMObject *  CATRootContainerCGM_NewSameType(CATCGMContainer * iContainer);
#endif

  //=================================================================
  //  DEBUG dedicated to CGM implementation
  //=================================================================

  static void PutColor(CATICGMObject* obj,int red,int green, int blue);
  static int GetColor(const CATICGMObject* obj,int &red,int &green, int &blue);
  
  static void Show(CATICGMObject* obj) ;
  static void NoShow(CATICGMObject* obj) ;
  static int  IsNoShow(const CATICGMObject* obj) ; 

  static void Dump(const CATICGMObject* obj, CATCGMOutput& os ) ;
  
  INLINE static void SynchroShow(CATGeoFactory* iFactory, const CATLISTP(CATICGMObject) & ioVisuPart);

  static CATBoolean GetLockCount(CATICGMObject* ipObject, int& ioLockCount);

  static CATBoolean DelKnotVectorOptData(CATICGMObject* ipObject);

  //------------------------------------------------------------------
  // Try to remove the Subd data
  //------------------------------------------------------------------
  INLINE static CATBoolean CompactSubd(CATGeoFactory* ipFactory);

  //-----------------------------------------------------------------------------
  // GetSize pour estimation en octets de la taille memoire de l'implementation 
  //  ne tient pas compte de la taille des objets aggreges
  //-----------------------------------------------------------------------------
  static size_t  GetSize(const CATICGMObject* obj) ;   
  static size_t  GetStaticMemoryBytes(const CATICGMObject* obj) ;
  static size_t  GetDynamicMemoryBytes(const CATICGMObject* obj) ;

  //-----------------------------------------------------------------------------
  // GetCumulatedStreamSize pour estimation en octets de la taille fichier de l'object 
  //   tient compte de la taille des objets aggreges
  //-----------------------------------------------------------------------------
  static size_t  GetCumulatedStreamSize(const CATICGMObject* obj) ;   
  static size_t  GetCumulatedStreamSize(const CATLISTP(CATICGMObject) &iObjects) ;   

  //---------------------------------------------------------------------------------
  // Pour parametrage du Checker
  //  CheckPOEC        // CheckUp at Creation/Modification of POEC
  //  CheckEdgeCurve   // CheckUp at Creation/Modification of POEC
  //  CATCheckCurve    // Deeper CheckUp with CATCheckCurve analysis
  //---------------------------------------------------------------------------------
  static int CheckPOECActive();         // CheckUp at Creation/Modification of POEC
  static int CheckEdgeCurveActive();    // CheckUp at Creation/Modification of POEC
  static int CheckCurveActive();        // Deeper CheckUp with CATCheckCurve analysis

  //=================================================================
  //  Gestion des liens inverses de modelisation
  //=================================================================
  static int CheckUpwardLinksIsOn();    // Detection du checker actif
  // permettre de desactiver sur une transaction (Container Clear())
  //   -1 lecture    0 desactiver 1 reactiver
  static int CheckUpwardLinksTemporaryChange(int action);

  //=================================================================
  //  Divers services de gestion des objects
  //=================================================================
  
  static void WriteContainer(CATICGMContainer* obj, const char* filename);
  static void WriteContainer(CATICGMObject   * obj, const char* filename);
 
  static CATICGMObject* catcxitf(CATICGMObject *itf);

  static void SynchronizeExplicitWithNullUseCount(CATGeoFactory* iFact);
  
  static void SynchronizeTags(CATGeoFactory* iFact , CATMapVoidToVoid * iTagToCATICGMObject );

  //=================================================================
  //   EVENTS ON IMPLICIT
  //
  //    NB : use it with no arguments , please 
  //=================================================================
  static void ActivateImplicitEvents    ();
  static void DesactivateImplicitEvents ();
  static int EventsOnImplicit;
  
  //=================================================================
  //   SERVICE TEMPORAIRE 
  //=================================================================
  static void  CATTopRibNupletCell(CATCell *, int Add1_Remove0); // deprecated, utiliser CATCGMSpecialAccess::IncUseCount et DecUseCount

  static void  DetachFactoryFromReplay(CATGeoFactory* iFact, CATExtCGMReplay *iReplay);
  static void  DetachFactoryFromChain (CATGeoFactory* iFact, CATCGMChain *ichain);
 
  static CATULONG32  GetCGMBuildVersion(CATICGMContainer * iFactory);

  //=================================================================
  //   SERVICES INTERNES (utiliser CATCGMSpecialAccess !)
  //=================================================================
  static void IncDecUseCount(CATICGMObject *iObject, int iInc1_Dec0, CATULONG32 & oUseCount, 
                             CATBoolean iRemoveIfPossible = FALSE, CATBoolean * oHasBeenRemoved = 0);

  static void SetRemovable(CATICGMObject *iObject, CATBoolean iYesNo, CATBoolean * oWasRemovable = 0);
 
  //------------------------------------------------------------------
  // INTERNAL USE ONLY  For CATCXVertex::UnlinkUselessGeometry
  //------------------------------------------------------------------
  INLINE static void UnlinkUselessGeometry(CATTopology* ipTopology, CATCGMEventType iEventType, CATPoint* ipSpecificPoint = NULL, CATBoolean iRemoveFromFactory = TRUE);
  
  //---------------------------------------------------------------------------------
  // Pour gestion interne  GetSessionIdNumber
  //---------------------------------------------------------------------------------
  INLINE static CATULONG32   GetSessionIdNumber(CATGeoFactory *iFactory);
  INLINE static CATCGMStreamVersion GetLastStreamVersion(CATGeoFactory* iFactory);

 
 
  //---------------------------------------------------------------------------------
  // Tools  (CATGeoControl pour plus tard CATCGMDebug.h)
  //---------------------------------------------------------------------------------
  static INLINE void GetAllDependancies(const  CATLISTP(CATICGMObject) & iStarter,
                                        CATLISTP(CATICGMObject)        & ioEveryone);

  static INLINE void GetMaxLimOfParms(const CATLISTP(CATICGMObject)  & iStarter, 
                                      const CATBoolean                 iOnlyHoldingKnotVector,
                                      CATLISTP(CATCGMLimOfParm)      & ioParm);

  //-------------------------------------------------------------------------
  // Pour Analyse Topologie
  //-------------------------------------------------------------------------
  static INLINE void GetAllGeometricRep(CATCurve *iCurve, CATLISTP(CATCurve) &ioReps);
  static INLINE void GetAllGeometricRep(CATPoint *iCurve, CATLISTP(CATPoint) &ioReps);


  //-------------------------------------------------------------------------
  // Pour Detection d'operation specifique sur la Factory 
  //    (Sauvegarde a partir du format V5R11)
  //-------------------------------------------------------------------------
  static INLINE void        DefineIsDoing(CATGeoFactory *iFactory, const CATCGMFactoryStatus iSpecificOperation);
  static INLINE CATBoolean  HasBeenDone(CATGeoFactory *iFactory,   const CATCGMFactoryStatus iSpecificOperation);

  //-------------------------------------------------------------------------
  // Pour analyse du modele dans CATGem
  //-------------------------------------------------------------------------
  static INLINE void DumpStatsGeometricTypes(CATListPtrCATCGMObject& iListOfObjects, CATCGMOutput& iOutput);

  static INLINE void DumpStaticSharpnessDataGeom(CATGeometry* ipGeometry, char* ipAlignMSG, CATCGMOutput& iOutput);  


  static int TraceOn;

  //-------------------------------------------------------------------------
  //  CGMCleaner interfaces
  //-------------------------------------------------------------------------
  static void CGMCleanerCheckSelectRuleBegin(CATGeoClnIDs::RuleID ipSpecificRuleID, CATGeoClnCheckParameter* ipRuleCheckParameter=NULL);
  
  static void CGMCleanerCheckSelectRuleAdd(CATGeoClnIDs::RuleID ipSpecificRuleID, CATGeoClnCheckParameter* ipRuleCheckParameter=NULL);

  static void CGMCleanerSpecificCheck(CATICGMObject* ipSpecificToCheck, const char IdentityBuildOperator[]);
 
  //------------------------------------------------------------
  // Pour cleaning des FatEdgeCurve dans CATCGMGeometryOfFatAble
  //------------------------------------------------------------
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


   INLINE static void BuildGraph(CATCGMGraph * iGraph, CATICGMUnknown *iRoot);



   //---------------------------------------------------------------------------------
   // CreateCATCGMStreamImpl
   //---------------------------------------------------------------------------------

   INLINE static CATCGMStreamImpl* CreateCATCGMStreamImpl(CATCGMStream* ipItf);

   INLINE static CATCGMStreamImpl* CreateCATCGMStreamImpl(void*         iBuffer,
     size_t        iSizeBuffer,
     CATCGMStream* ipItf);

   INLINE static CATCGMStreamImpl* CreateCATCGMStreamImpl(ostream&         ioFile,
     size_t           iInitialNumberOfBytes,
     const CATBoolean iEnableByAddress,
     CATCGMStream*    ipItf);

   INLINE static CATCGMStreamImpl* CreateCATCGMStreamImpl(istream&      ioFile,
     CATCGMStream* ipItf);

   INLINE static CATCGMStreamImpl* CreateCATCGMStreamImpl(const char*            iFilename,
     const CATCGMStreamType iAcces,
     const CATBoolean       iEnableByAddress,
     CATCGMStream*          ipItf);

   INLINE static CATCGMStreamImpl* CreateCATCGMStreamImpl(size_t                 iInitialNumberOfBytes,
     const CATCGMStreamType iAcces,
     const CATBoolean       iEnableByAddress,
     CATCGMStream*          ipItf);

   INLINE static CATCGMStreamImpl* CreateCATCGMStreamImpl(CATStream&             iDirectStreaming,
     const CATCGMStreamType iAcces,
     const CATBoolean       iEnableByAddress,
     CATCGMStream*          ipItf);

   INLINE static CATCGMStreamImpl* CreateCATCGMStreamImpl(CATStream&    iDirectStreaming,
     size_t        iSizeStream,
     CATCGMStream* ipItf);

   /**
   * Transfer sharpness data
   * - FROM CATEdgeCurves of iSources, or CATEdgeCurves contained in CATEdgeCurves of iSources
   * - TO iTarget
   * The transfer is done only if the 2 PCurves referenced by the sharpness data are present in iTarget.
   */
   INLINE static void TransferSharpness(CATListPtrCATEdgeCurve & iSources, CATEdgeCurve & iTarget);

   /**
   * Create a CATCompareGeometry.
   */
   INLINE static CATCompareGeometry * CreateCompareGeometry(CATCompareContext * ioContext);

#ifdef CATIACGMR419CAA
   //-------------------------------------------------------------------------
   // Pour Analyse Topologie (Internal Use)
   //-------------------------------------------------------------------------
   INLINE static CATBoolean IsGMPolyObject(CATICGMObject *piICGMObject);

   //-------------------------------------------------------------------------
   // Pour Analyse Topologie (Internal Use)
   //-------------------------------------------------------------------------
   INLINE static CATBoolean Is_MixedPolyExactInputs_Allowed(CATCGMOperator *piCGMOperator);

   //-------------------------------------------------------------------------
   // Pour Analyse Topologie (Internal Use)
   //-------------------------------------------------------------------------
   INLINE static CATBoolean IsGMImplicitSurfaceObject(CATICGMObject *piICGMObject);
#endif

protected :
  
  static CATCGMDebug *GetCGMImplement();

    
  //=================================================================
  // Integration CATCGMPeriodicityManager Procedural 
  //   gestion implementative sans impact Interface 
  //=================================================================
  virtual CATBoolean _CATCGMPeriodicityManager_GetInfo( CATCurve * iCurve, CATCGMPeriodicityInfo & oInfo )= 0;
  virtual CATBoolean _CATCGMPeriodicityManager_GetInfo( CATSurface * iSurface, CATBoolean iUorV, CATCGMPeriodicityInfo & oInfo )= 0;

  //=================================================================
  //   integration Native sans impact Exposition Interface  
  //=================================================================
  virtual void _CATCGMPeriodicityManager_SetInfo( CATSurface * iSurface, CATBoolean iUorV, const CATCGMPeriodicityInfo & iInfo )= 0;
  virtual void _CATCGMPeriodicityManager_SetInfo( CATCurve * iCurve, const CATCGMPeriodicityInfo & iInfo )= 0;

  //---------------------------------------------------------------------------------
  // Pour Fusion
  //---------------------------------------------------------------------------------
  virtual void _NewFactory(CATGeoFactory* & itf, CATCGMContainer * & impl
                          , const CATCGMScaleCategory iScaleCategory)= 0;
  virtual CATICGMUnknown *_CreateTIECATGeoFactoryCATGeoFactoryCGM(CATCGMContainer* impl)= 0;
  virtual CATPCurve *_GetProtectedPCurve(CATSurface* impl,CATLONG32 i)= 0;
  virtual long       _GetNumberOfProtectedPCurves(CATSurface* impl)= 0;
  virtual CATPoint * _GetBestPoint(CATMacroPoint* impl)= 0;

  //---------------------------------------------------------------------------------
  // GetUsageContext
  //---------------------------------------------------------------------------------
  virtual CATCGMUnknown_UsageContext    _GetUsageContext(CATICGMUnknown *iCGMObject) = 0;

  //---------------------------------------------------------------------------------
  virtual CATGeometricType _GetCATGeometricType(const char* ipGeometricTypeName) = 0;

  //---------------------------------------------------------------------------------
  virtual void _PutColor(CATICGMObject* obj,int red,int green, int blue) = 0;
  virtual void _Show(CATICGMObject* obj) = 0;
  virtual void _NoShow(CATICGMObject* obj) = 0;
  virtual int  _IsNoShow(const CATICGMObject* obj)  = 0;

  virtual void _SynchroShow(CATGeoFactory* iFactory, const CATLISTP(CATICGMObject) & ioVisuPart)  = 0;

  virtual CATBoolean _GetLockCount(CATICGMObject* ipObject, int& ioLockCount) = 0;

  virtual CATBoolean _DelKnotVectorOptData(CATICGMObject* ipObject) = 0;

  virtual CATBoolean _CompactSubd(CATGeoFactory* ipFactory) = 0;

  virtual void _Dump(const CATICGMObject* obj, CATCGMOutput& os ) = 0;
  
  virtual size_t _GetSize(const CATICGMObject* obj) = 0 ;   
  virtual size_t _GetStaticMemoryBytes(const CATICGMObject* obj) = 0 ;
  virtual size_t _GetDynamicMemoryBytes(const CATICGMObject* obj) = 0 ;

  virtual size_t _GetCumulatedStreamSize(const CATLISTP(CATICGMObject) &iObjects) = 0 ;   
  
  virtual int _GetColor(const CATICGMObject* obj,int &red,int &green, int &blue) = 0;
  
  virtual CATBoolean _CATCGMDebugUI(CATICGMObject* iObject)= 0;


  //=================================================================
  //  Duplicate
  //=================================================================
  virtual void _Duplicate(CATGeoFactory* iFactory, CATGeoFactory*& oFactory)= 0;

  
  //=================================================================================
  // Passage transparent TIEBOA  CATGeoFactory -> CATGeoFactoryProtected
  //=================================================================================
   virtual CATGeoFactoryProtected* _GetProtectedInterface(CATGeoFactory *iFact) = 0;
#if defined ( CATCGMBOAObject )
   virtual void _InitRootContainer(CATGeoFactoryProtected *iFactoryProtected) = 0;
#endif


  //---------------------------------------------------------------------------------
  virtual CATCGMOperator* _SetFactoryCurrentOperator(CATCGMOperator* ipCGMOperator, CATGeoFactory* ipFactory) = 0;
  virtual CATBoundedCellsIterator* _SetFactoryCurrentBnddCellIter(CATBoundedCellsIterator* ipBnddCellIter, CATGeoFactory* ipFactory) = 0;
  virtual int _SetFactoryCurrentUpDownCallingMethod(int iUpDownCallingMethod, CATGeoFactory* ipFactory) = 0;

  virtual CATGeoFactory* _IsFactoryCNEXT(CATGeoFactory *iFact) = 0;
  virtual CATULONG32 _GetMaxTag(CATGeoFactory *iFact) = 0;
  virtual CATBoolean _CompareFactories(CATGeoFactory * iFacto1,CATGeoFactory * iFacto2,CATLISTP(CATICGMObject) &oAllDifferentObj) = 0;
  virtual CATBoolean _CompareExactAndApproxNurbs(CATGeoFactory * iFacto1,CATGeoFactory * iFacto2,CATLISTP(CATICGMObject) &oAllDifferentsNurbs) =0;
  virtual CATBoolean _CompareExactAndApproxPNurbs(CATGeoFactory * iFacto1,CATGeoFactory * iFacto2,CATLISTP(CATICGMObject) &oAllDifferentsPNurbs) =0;
  //---------------------------------------------------------------------------------
  virtual void _Save(const CATGeoFactory* iFactory, 
                     const char iFilename[],
                     const int iWithTass=1,
                     const CATCGMStreamVersion iWantingVersion = CatCGMStream_UnknownVersion) = 0;

  virtual void _Load(const char iFilename[],
                     CATGeoFactory* &oFactory,
                     const CATBoolean      avoidAnyRattrap = FALSE,
                     CATCGMStreamVersion  *iWantingVersion = NULL) = 0;

  virtual CATGeoFactory* _CATCreateCGMContainer (const CATCGMScaleCategory iScale,
                                                 const CATPositiveLength iUnitInMeter=.001) = 0;  //@NumValidated 
  virtual CATGeoFactory* _CATLoadCGMContainer   (istream& iStreamArea,
                                                 const CATCGMVersionDefinition **ptrUnstreamVersion = NULL) = 0;

  virtual CATGeoFactory* _CGMLoadRootContainer(      CATCGMStream             & streamarea,
                                               const CATCGMVersionDefinition ** ptrUnstreamVersion = NULL,
                                               const CATBoolean                 avoidAnyRattrap = FALSE ) = 0;

  virtual void _CATSaveCGMContainer   (const CATGeoFactory* iFact,  ostream& ioStreamArea,
                                       const CATCGMStreamVersion iWantingVersion = CatCGMStream_UnknownVersion) = 0;

  virtual HRESULT _CATSaveCGMContainer   (const CATGeoFactory* iFact, 
                                       CATCGMStream & ioStreamArea) = 0;

  // VUC : 16-10-09 Incremental Stream

  virtual int _IsIncrementalStreamActivated() = 0;
  virtual int _IsIncrementalStreamTraceActivated() = 0;
  virtual int _IsIncrementalStreamTest() = 0;
  virtual int _GetIncrementalStreamTestMode(CATBoolean iSwitchMode) = 0;
	virtual void _SetIncrementalStreamActivated() = 0;

  virtual CATGeoFactory* _CGMIncrementalLoadRootContainer(CATLISTP(CATCGMStream )          &ListOfCGMStream, 
                                                          const CATCGMVersionDefinition ** ptrUnstreamVersion,
                                                          const CATBoolean                 avoidAnyRattrap) = 0;

  virtual HRESULT _CGMIncrementalSaveContainer(const CATGeoFactory* iFactory,   
                                               CATCGMStream & TheStream,
                                               const CATCGMStreamVersion iWantingVersion = CatCGMStream_UnknownVersion, 
                                               CATBoolean iWithTass = FALSE) = 0;

  virtual HRESULT _CheckIncrementalStream(const CATGeoFactory* iFactory, CATCGMOperator *iOperator) = 0;

  virtual HRESULT _SetWasModified(CATICGMObject* iObject) = 0;


  virtual void _CATCloseCGMContainer  (CATGeoFactory* iFact) = 0;

  virtual CATBoolean _AddParamToPOEC(CATPointOnEdgeCurve* ipPOEC,
                                     const CATLONG32      iSpecCount, 
                                     const CATCurve**     ippCurves,
                                     const double*        ipLocalParamValues,
                                     const CATLONG32*     ipArcValues) = 0;

  //=================================================================
  // Stream ordonne des objets pointes
  //=================================================================
  virtual void _StreamObject(CATICGMObject* ipObject, CATCGMStream& Str) = 0;

  //=================================================================
  // From GeoFactory To Federators of modelisation
  //=================================================================
  virtual void _GetFederators(CATGeoFactory*            iFactory,
                              CATLISTP(CATICGMObject) & ioFederators, 
                              CATCGMFederatorsFilter    iFilterSpec,
                              CATGeometricType          iFilterType)= 0;


  //---------------------------------------------------------------------------------
  virtual CATBoolean _GetNewObjectLeaks(CATGeoFactory* iFact,
    const CATLISTP(CATICGMObject) &iExpectedNewObjects, 
    CATLISTP(CATICGMObject) &ioFederators, CATLISTP(CATICGMObject) &ioAlls) = 0;

  virtual CATBoolean _GetNotPersistent(CATGeoFactory* iFact,
    CATLISTP(CATICGMObject) &oFederators, CATLISTP(CATICGMObject) &oAlls) = 0;
  
  virtual CATBoolean _GetUselessComponent(CATGeoFactory* iFact,
    CATLISTP(CATICGMObject) &oInMacroPoint, CATLISTP(CATICGMObject) &oInEdgeCurve, CATBoolean iCleanerLike) = 0;

  virtual void _PurgeNonPersistent(int WithPrecaution=0) = 0;

  //---------------------------------------------------------------------------------
  virtual CATULONG32  _GetCGMBuildVersion(CATICGMContainer * iFactory) = 0;
 
  //---------------------------------------------------------------------------------
  virtual void _UnlinkUselessGeometry(CATTopology* ipTopology, CATCGMEventType iEventType, CATPoint* ipSpecificPoint, CATBoolean iRemoveFromFactory) = 0;

  //---------------------------------------------------------------------------------
  virtual int _CheckUpwardLinksIsOn()= 0;
  virtual int _CheckUpwardLinksTemporaryChange(int action)= 0;
  //---------------------------------------------------------------------------------
  virtual void _WriteContainer(CATICGMContainer* obj, const char* filename) = 0;
  virtual void _WriteContainer(CATICGMObject   * obj, const char* filename) = 0;
  virtual void _CATTopRibNupletCell(CATCell *, int Add1_Remove0) = 0; // deprecated, utiliser CATCGMSpecialAccess::IncUseCount et DecUseCount
  virtual void _IncDecUseCount(CATICGMObject *iObject, int iInc1_Dec0, CATULONG32 & oUseCount, 
                               CATBoolean iRemoveIfPossible = FALSE, CATBoolean * oHasBeenRemoved = 0) = 0;
  virtual void _SetRemovable(CATICGMObject *iObject, CATBoolean iYesNo, CATBoolean * oWasRemovable = 0) = 0;
  virtual CATICGMObject* _catcxitf(CATICGMObject *itf) = 0;
  virtual void _SynchronizeExplicitWithNullUseCount(CATGeoFactory* iFact) = 0;
  virtual void _SynchronizeTags(CATGeoFactory* iFact , CATMapVoidToVoid * iTagToCATICGMObject )= 0;
  virtual void _DetachFactoryFromReplay(CATGeoFactory* iFact, CATExtCGMReplay *iReplay)= 0;
  virtual void _DetachFactoryFromChain(CATGeoFactory* iFact, CATCGMChain *iChain)= 0;

  //---------------------------------------------------------------------------------
  virtual int _CheckCurveActive()= 0;        // deeper CheckUp analysis for Curve Analysis
  virtual int _CheckEdgeCurveActive()= 0;    // check OnFly of EdgeCurve Analysis
  virtual int _CheckPOECActive()= 0;         // check OnFly of POEC Analysis

  //=================================================================
  //  Pour CATCGMTempoULONGPTR
  //=================================================================
  virtual CATCGMTempoULONGPTR * _CreateTempoULONGPTR( CATGeoFactory* iFactory ) = 0;

  //=================================================================
  //  Pour GetSessionIdNumber
  //=================================================================
  virtual CATULONG32   _GetSessionIdNumber(CATGeoFactory *iFactory) = 0 ;
  virtual CATCGMStreamVersion _GetLastStreamVersion(CATGeoFactory* iFactory)= 0;

  //---------------------------------------------------------------------------------
  // Tools  (CATGeoControl pour plus tard CATCGMDebug.h)
  //---------------------------------------------------------------------------------
  virtual void _GetAllDependancies(const  CATLISTP(CATICGMObject) & iStarter, CATLISTP(CATICGMObject)   & ioEveryone) = 0;
  virtual void _GetMaxLimOfParms(const CATLISTP(CATICGMObject)  & iStarter, 
                                 const CATBoolean                 iOnlyHoldingKnotVector,
                                 CATLISTP(CATCGMLimOfParm)      & ioParm) = 0;

  //-------------------------------------------------------------------------
  // Pour Analyse Topologie
  //-------------------------------------------------------------------------
  virtual void _GetAllGeometricRep(CATCurve *iCurve, CATLISTP(CATCurve) &ioReps) = 0;
  virtual void _GetAllGeometricRep(CATPoint *iCurve, CATLISTP(CATPoint) &ioReps) = 0;


  //-------------------------------------------------------------------------
  // Pour Detection d'operation specifique sur la Factory 
  //    (Sauvegarde a partir du format V5R11)
  //-------------------------------------------------------------------------
  virtual void        _DefineIsDoing(CATGeoFactory *iFactory, const CATCGMFactoryStatus iSpecificOperation) = 0;
  virtual CATBoolean  _HasBeenDone(CATGeoFactory *iFactory,   const CATCGMFactoryStatus iSpecificOperation) = 0;
 
  //-------------------------------------------------------------------------
  // Pour analyse du modele dans CATGem
  //-------------------------------------------------------------------------
  virtual void _DumpStatsGeometricTypes(CATListPtrCATCGMObject& iListOfObjects, CATCGMOutput& iOutput) = 0;

  virtual void _DumpStaticSharpnessDataGeom(CATGeometry* ipGeometry, char* ipAlignMSG, CATCGMOutput& iOutput) = 0;


  //-------------------------------------------------------------------------
  //  CGMCleaner interfaces
  //-------------------------------------------------------------------------
  virtual void _CGMCleanerCheckSelectRuleBegin(CATGeoClnIDs::RuleID ipSpecificRuleID, 
                                               CATGeoClnCheckParameter* ipRuleCheckParameter = NULL) = 0;
  
  virtual void _CGMCleanerCheckSelectRuleAdd(CATGeoClnIDs::RuleID ipSpecificRuleID, 
                                             CATGeoClnCheckParameter* ipRuleCheckParameter = NULL) = 0;

  virtual void _CGMCleanerSpecificCheck(CATICGMObject* ipSpecificToCheck, const char IdentityBuildOperator[]) = 0;

 
  //------------------------------------------------------------
  // Pour cleaning des FatEdgeCurve dans CATCGMGeometryOfFatAble
  //------------------------------------------------------------
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

  virtual void _BuildGraph(CATCGMGraph * iGraph, CATICGMUnknown *iRoot) = 0;

  
  //=================================================================
  //   GetContents : provide contents as HT of CATCGMObjects
  //=================================================================
  virtual void _GetContents(CATGeoFactory* iFactory, CATMapVoidToVoid  * & ioContents)= 0;
  
  //=================================================================
  //   GetDump : provide Dump (For ODT)
  //=================================================================
  virtual void _GetDump(CATICGMObject* iCGMObject, CATUnicodeString & oDumpDefinition)= 0;
 
#if defined ( CATCGMBOAObject )
  virtual CATBaseUnknown * _CATRootContainerCGM_CreationCGM(CATCGMContainer * iContainer) = 0;
  virtual CATCGMObject   * _CATRootContainerCGM_NewSameType(CATCGMContainer * iContainer) = 0;
#endif


   //---------------------------------------------------------------------------------
   // CreateCATCGMStreamImpl
   //---------------------------------------------------------------------------------

   virtual CATCGMStreamImpl* _CreateCATCGMStreamImpl(CATCGMStream* ipItf)= 0;

   virtual CATCGMStreamImpl* _CreateCATCGMStreamImpl(void*         iBuffer,
     size_t        iSizeBuffer,
     CATCGMStream* ipItf)= 0;

   virtual CATCGMStreamImpl* _CreateCATCGMStreamImpl(ostream&         ioFile,
     size_t           iInitialNumberOfBytes,
     const CATBoolean iEnableByAddress,
     CATCGMStream*    ipItf)= 0;

   virtual CATCGMStreamImpl* _CreateCATCGMStreamImpl(istream&      ioFile,
     CATCGMStream* ipItf)= 0;

   virtual CATCGMStreamImpl* _CreateCATCGMStreamImpl(const char*            iFilename,
     const CATCGMStreamType iAcces,
     const CATBoolean       iEnableByAddress,
     CATCGMStream*          ipItf)= 0;

   virtual CATCGMStreamImpl* _CreateCATCGMStreamImpl(size_t                 iInitialNumberOfBytes,
     const CATCGMStreamType iAcces,
     const CATBoolean       iEnableByAddress,
     CATCGMStream*          ipItf)= 0;

   virtual CATCGMStreamImpl* _CreateCATCGMStreamImpl(CATStream&             iDirectStreaming,
     const CATCGMStreamType iAcces,
     const CATBoolean       iEnableByAddress,
     CATCGMStream*          ipItf)= 0;

   virtual CATCGMStreamImpl* _CreateCATCGMStreamImpl(CATStream&    iDirectStreaming,
     size_t        iSizeStream,
     CATCGMStream* ipItf)= 0;

   virtual void _TransferSharpness(CATListPtrCATEdgeCurve & iSources, CATEdgeCurve & iTarget) = 0;

   virtual CATCompareGeometry * _CreateCompareGeometry(CATCompareContext * ioContext) = 0;
 
#ifdef CATIACGMR419CAA
   virtual CATBoolean _IsGMPolyObject(CATICGMObject *piICGMObject) = 0;

   virtual CATBoolean _Is_MixedPolyExactInputs_Allowed(CATCGMOperator *piCGMOperator) = 0;

   virtual CATBoolean _IsGMImplicitSurfaceObject(CATICGMObject *piICGMObject) = 0;
#endif

  //---------------------------------------------------------------------------------
  // Pour parametre de debug Local au Framwork GeometricObjects
  //---------------------------------------------------------------------------------
  static CATCGMDebug *_NCGM;
  static int          _alreadyInitialised;

  CATCGMDebug();
  virtual ~CATCGMDebug();  

  CATCGMDebugLocal *_LocalDebug;

  friend class CATCGMTempoULONGPTR;

};

//=================================================================
// Integration CATCGMPeriodicityManager Procedural 
//   gestion implementative sans impact Interface 
//=================================================================

INLINE CATBoolean CATCGMDebug::CATCGMPeriodicityManager_GetInfo( CATCurve * iCurve, CATCGMPeriodicityInfo & oInfo ) 
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ? bridge->_CATCGMPeriodicityManager_GetInfo(iCurve,oInfo) : FALSE ;
}

INLINE CATBoolean CATCGMDebug::CATCGMPeriodicityManager_GetInfo( CATSurface * iSurface, CATBoolean iUorV, CATCGMPeriodicityInfo & oInfo ) 
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ? bridge->_CATCGMPeriodicityManager_GetInfo(iSurface,iUorV,oInfo) : FALSE ;
}

//=================================================================
//   Pour Fusion 
//=================================================================
INLINE void CATCGMDebug::NewFactory(CATGeoFactory* & itf, CATCGMContainer * & impl
                                   , const CATCGMScaleCategory iScaleCategory) 
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if (bridge) bridge->_NewFactory(itf,impl,iScaleCategory);
}

INLINE CATICGMUnknown *CATCGMDebug::CreateTIECATGeoFactoryCATGeoFactoryCGM(CATCGMContainer* impl) 
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ? bridge->_CreateTIECATGeoFactoryCATGeoFactoryCGM(impl) : NULL;
}


INLINE CATPCurve *CATCGMDebug::GetProtectedPCurve(CATSurface* impl,CATLONG32 i) 
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ? bridge->_GetProtectedPCurve(impl,i) : NULL;
}


INLINE long CATCGMDebug::GetNumberOfProtectedPCurves(CATSurface* impl) 
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ? bridge->_GetNumberOfProtectedPCurves(impl) : 0;
}


INLINE CATPoint *CATCGMDebug::GetBestPoint(CATMacroPoint* impl) 
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ? bridge->_GetBestPoint(impl) : NULL;
}
  

//=================================================================
//   integration Native sans impact Exposition Interface  
//=================================================================
INLINE void CATCGMDebug::CATCGMPeriodicityManager_SetInfo( CATSurface * iSurface, CATBoolean iUorV, const CATCGMPeriodicityInfo & iInfo )
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if (bridge) {
    return bridge->_CATCGMPeriodicityManager_SetInfo(iSurface,iUorV,iInfo);
  }
  return ;
}

INLINE void CATCGMDebug::CATCGMPeriodicityManager_SetInfo( CATCurve * iCurve, const CATCGMPeriodicityInfo & iInfo )
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if (bridge) {
    return bridge->_CATCGMPeriodicityManager_SetInfo(iCurve,iInfo);
  }
  return ;
}


  //---------------------------------------------------------------------------------
  // GetUsageContext
  //---------------------------------------------------------------------------------
INLINE CATCGMUnknown_UsageContext  CATCGMDebug::GetUsageContext(CATICGMUnknown *iCGMObject) 
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ? bridge->_GetUsageContext(iCGMObject) : CatCGMUnknown_Unidentified ;
}
 

//---------------------------------------------------------------------------------
// GetCATGeometricType
//---------------------------------------------------------------------------------
INLINE CATGeometricType CATCGMDebug::GetCATGeometricType(const char* ipGeometricTypeName)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ? bridge->_GetCATGeometricType(ipGeometricTypeName) : CATUnknownGeometryType;
}

//---------------------------------------------------------------------------------
// AddParamToPOEC
//---------------------------------------------------------------------------------
INLINE CATBoolean CATCGMDebug::AddParamToPOEC(CATPointOnEdgeCurve* ipPOEC,
                                              const CATLONG32      iSpecCount, 
                                              const CATCurve**     ippCurves,
                                              const double*        ipLocalParamValues,
                                              const CATLONG32*     ipArcValues)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ? bridge->_AddParamToPOEC(ipPOEC, iSpecCount, ippCurves, ipLocalParamValues, ipArcValues) : FALSE;
}

//---------------------------------------------------------------------------------
// StreamObject
//---------------------------------------------------------------------------------
INLINE void CATCGMDebug::StreamObject(CATICGMObject* ipObject, CATCGMStream& Str)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge ) 
    bridge->_StreamObject(ipObject, Str);
}

//---------------------------------------------------------------------------------
// GetSessionIdNumber
//---------------------------------------------------------------------------------
INLINE CATULONG32  CATCGMDebug::GetSessionIdNumber(CATGeoFactory *iFactory) 
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ? bridge->_GetSessionIdNumber(iFactory) : 0 ;
}
 
//---------------------------------------------------------------------------------
// GetLastStreamVersion
//---------------------------------------------------------------------------------
INLINE CATCGMStreamVersion  CATCGMDebug::GetLastStreamVersion(CATGeoFactory *iFactory) 
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ? bridge->_GetLastStreamVersion(iFactory) : CatCGMStream_UnknownVersion ;
}

//---------------------------------------------------------------------------------
// PurgeNonPersistent
//---------------------------------------------------------------------------------
INLINE void CATCGMDebug::PurgeNonPersistent(int WithPrecaution) 
{
   CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
   if ( bridge ) 
      bridge->_PurgeNonPersistent(WithPrecaution) ;
}

//------------------------------------------------------------------
// INTERNAL USE ONLY  For CATCXVertex::UnlinkUselessGeometry
//------------------------------------------------------------------
INLINE void CATCGMDebug::UnlinkUselessGeometry(CATTopology* ipTopology, CATCGMEventType iEventType, CATPoint* ipSpecificPoint, CATBoolean iRemoveFromFactory)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge ) 
    bridge->_UnlinkUselessGeometry(ipTopology, iEventType, ipSpecificPoint, iRemoveFromFactory);
}

//---------------------------------------------------------------------------------
// Tools  (CATGeoControl)
//---------------------------------------------------------------------------------
INLINE void CATCGMDebug::GetAllDependancies(const  CATLISTP(CATICGMObject) & iStarter,
                                           CATLISTP(CATICGMObject)        & ioEveryone)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge ) 
    bridge->_GetAllDependancies(iStarter,ioEveryone);
}

INLINE void CATCGMDebug::GetMaxLimOfParms(const CATLISTP(CATICGMObject)  & iStarter, 
                                         const CATBoolean                 iOnlyHoldingKnotVector,
                                         CATLISTP(CATCGMLimOfParm)      & ioParm)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge ) 
    bridge->_GetMaxLimOfParms(iStarter,iOnlyHoldingKnotVector,ioParm);
}



  //=================================================================================
  // Passage transparent TIEBOA  CATGeoFactory -> CATGeoFactoryProtected
  //=================================================================================
INLINE CATGeoFactoryProtected* CATCGMDebug::GetProtectedInterface(CATGeoFactory *iFact) 
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ?  bridge->_GetProtectedInterface(iFact) : NULL;
}

#if defined ( CATCGMBOAObject )
INLINE void CATCGMDebug::InitRootContainer(CATGeoFactoryProtected *iFactoryProtected) 
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge )
	bridge->_InitRootContainer(iFactoryProtected);
}
#endif

//-------------------------------------------------------------------------
// Pour Analyse Topologie
//-------------------------------------------------------------------------
INLINE void CATCGMDebug::GetAllGeometricRep(CATCurve *iCurve, CATLISTP(CATCurve) &ioReps)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge ) 
    bridge->_GetAllGeometricRep(iCurve,ioReps);
}

INLINE void CATCGMDebug::GetAllGeometricRep(CATPoint *iPoint, CATLISTP(CATPoint) &ioReps)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge ) 
    bridge->_GetAllGeometricRep(iPoint,ioReps);
}


//-------------------------------------------------------------------------
// Pour Detection d'operation specifique sur la Factory 
//    (Sauvegarde a partir du format V5R11)
//-------------------------------------------------------------------------
INLINE void       CATCGMDebug::DefineIsDoing(CATGeoFactory *iFactory, const CATCGMFactoryStatus iSpecificOperation)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge ) 
    bridge->_DefineIsDoing(iFactory,iSpecificOperation);
}

INLINE CATBoolean  CATCGMDebug::HasBeenDone(CATGeoFactory *iFactory,   const CATCGMFactoryStatus iSpecificOperation)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ? bridge->_HasBeenDone(iFactory,iSpecificOperation) : TRUE;
}

INLINE void CATCGMDebug::SynchroShow(CATGeoFactory* iFactory, const CATLISTP(CATICGMObject) & ioVisuPart)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge ) bridge->_SynchroShow(iFactory,ioVisuPart);
}

INLINE CATBoolean CATCGMDebug::GetLockCount(CATICGMObject* ipObject, int& ioLockCount)
{
  CATBoolean Result = FALSE;

  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge )
    Result = bridge->_GetLockCount(ipObject, ioLockCount);

  return Result;
}

INLINE CATBoolean CATCGMDebug::DelKnotVectorOptData(CATICGMObject* ipObject)
{
  CATBoolean Result = FALSE;

  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge )
    Result = bridge->_DelKnotVectorOptData(ipObject);

  return Result;
}


//------------------------------------------------------------------
// Try to remove the Subd data
//------------------------------------------------------------------
INLINE CATBoolean CATCGMDebug::CompactSubd(CATGeoFactory* ipFactory)
{
  CATBoolean Result = FALSE;

  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge )
    Result = bridge->_CompactSubd(ipFactory);

  return Result;
}
 

//==================================================================================
//  GetMaxTag
//==================================================================================
INLINE CATULONG32 CATCGMDebug::GetMaxTag(CATGeoFactory *iFact)
{
  CATULONG32 Result = 0;

  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge )
    Result = bridge->_GetMaxTag(iFact);

  return Result;
}

//==================================================================================
//  CompareFactories
//==================================================================================

INLINE CATBoolean CATCGMDebug::CompareFactories(CATGeoFactory *iFacto1, CATGeoFactory *iFacto2,CATLISTP(CATICGMObject) &oAllDifferentObj)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  CATBoolean FactoriesOK=FALSE;

  if ( bridge )
     FactoriesOK=bridge->_CompareFactories(iFacto1,iFacto2,oAllDifferentObj);
  return FactoriesOK;
}


//==================================================================================
//  CompareExactAndApproxNurbs
//==================================================================================

INLINE CATBoolean CATCGMDebug::CompareExactAndApproxNurbs(CATGeoFactory * iFacto1,CATGeoFactory * iFacto2,CATLISTP(CATICGMObject) &oAllDifferentsNurbs)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  CATBoolean AllNurbsOK=FALSE;
  
  if ( bridge )
    AllNurbsOK=bridge->_CompareExactAndApproxNurbs(iFacto1,iFacto2,oAllDifferentsNurbs);
  return AllNurbsOK;

}

//==================================================================================
//  CompareExactAndApproxPNurbs
//==================================================================================

INLINE CATBoolean CATCGMDebug::CompareExactAndApproxPNurbs(CATGeoFactory * iFacto1,CATGeoFactory * iFacto2,CATLISTP(CATICGMObject) &oAllDifferentsPNurbs)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  CATBoolean AllPNurbsOK=FALSE;
  
  if ( bridge )
    AllPNurbsOK=bridge->_CompareExactAndApproxPNurbs(iFacto1,iFacto2,oAllDifferentsPNurbs);
  return AllPNurbsOK;

}


//==================================================================================
//  DumpStatsGeometricTypes
//==================================================================================
INLINE void CATCGMDebug::DumpStatsGeometricTypes(CATListPtrCATCGMObject& iListOfObjects, CATCGMOutput& iOutput)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge ) bridge->_DumpStatsGeometricTypes(iListOfObjects, iOutput);
}

//==================================================================================
//  DumpStatsGeometricTypes
//==================================================================================
INLINE void CATCGMDebug::DumpStaticSharpnessDataGeom(CATGeometry* ipGeometry, char* ipAlignMSG, CATCGMOutput& iOutput)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge ) bridge->_DumpStaticSharpnessDataGeom(ipGeometry, ipAlignMSG, iOutput);
}


//==================================================================================
// SimplifyEdgeCurve
//==================================================================================
INLINE CATBoolean CATCGMDebug::SimplifyEdgeCurve(CATSoftwareConfiguration * iConfig,
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
  CATBoolean Result = FALSE;

  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge )
    Result = bridge->_SimplifyEdgeCurve(iConfig,
                                        ipCGMGeometryOfFatAble,
                                        ioppNewEdgeCurve,
                                        ioOriEdgeCurve,
                                        ioNewEdgeCurve,
                                        ioppNewStartPOEC,
                                        ioppNewEndPOEC,
                                        ioNewPOECs,
                                        ioReversedOrientations,
                                        iopIsSimplifiable);

  return Result;
}



//==================================================================================
// BuildGraph
//==================================================================================
INLINE void CATCGMDebug::BuildGraph(CATCGMGraph * iGraph, CATICGMUnknown *iRoot)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge )
    bridge->_BuildGraph(iGraph,iRoot);
}

//=================================================================
//   GetContents : provide contents as HT of CATCGMObjects
//=================================================================
INLINE void CATCGMDebug::GetContents(CATGeoFactory* iFactory, CATMapVoidToVoid  * & ioContents) 
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge )
    bridge->_GetContents(iFactory,ioContents);
}

//=================================================================
  //   GetDump : provide Dump (For ODT)
//=================================================================
INLINE void CATCGMDebug::GetDump(CATICGMObject* iCGMObject, CATUnicodeString & oDumpDefinition) 
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge )
    bridge->_GetDump(iCGMObject,oDumpDefinition);
}

//=================================================================
//  Duplicate
//=================================================================
INLINE void CATCGMDebug::Duplicate(CATGeoFactory* iFactory, CATGeoFactory*& oFactory) 
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge )
    bridge->_Duplicate(iFactory,oFactory);
}


//==================================================================================
// SetFactoryCurrentOperator
//==================================================================================
INLINE CATCGMOperator* CATCGMDebug::SetFactoryCurrentOperator(CATCGMOperator* ipCGMOperator, CATGeoFactory* ipFactory)
{
  CATCGMOperator* pResult = NULL;

  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge )
    pResult = bridge->_SetFactoryCurrentOperator(ipCGMOperator, ipFactory);

  return pResult;
}

//==================================================================================
// SetFactoryCurrentBnddCellIter
//==================================================================================
INLINE CATBoundedCellsIterator* CATCGMDebug::SetFactoryCurrentBnddCellIter(CATBoundedCellsIterator* ipBnddCellIter, CATGeoFactory* ipFactory)
{
  CATBoundedCellsIterator* pResult = NULL;

  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge )
    pResult = bridge->_SetFactoryCurrentBnddCellIter(ipBnddCellIter, ipFactory);

  return pResult;
}

//==================================================================================
// SetFactoryCurrentUpDownCallingMethod
//==================================================================================
INLINE int CATCGMDebug::SetFactoryCurrentUpDownCallingMethod(int iUpDownCallingMethod, CATGeoFactory* ipFactory)
{
  int Result = -1;

  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  if ( bridge )
    Result = bridge->_SetFactoryCurrentUpDownCallingMethod(iUpDownCallingMethod, ipFactory);

  return Result;
}

//==================================================================================
// TransferSharpness
//==================================================================================
INLINE void CATCGMDebug::TransferSharpness(CATListPtrCATEdgeCurve & iSources, CATEdgeCurve & iTarget)
{
  CATCGMDebug * ncgm = CATCGMDebug::GetCGMImplement();
  if (ncgm)
    ncgm->_TransferSharpness(iSources, iTarget);
}

//==================================================================================
// CreateCompareGeometry
//==================================================================================
INLINE CATCompareGeometry * CATCGMDebug::CreateCompareGeometry(CATCompareContext * ioContext)
{
  CATCGMDebug * ncgm = CATCGMDebug::GetCGMImplement();
  return (ncgm ? ncgm->_CreateCompareGeometry(ioContext) : NULL);
}

//==================================================================================
// SetWasModified
//==================================================================================
INLINE HRESULT CATCGMDebug::SetWasModified(CATICGMObject* iObject)
{
  CATCGMDebug * ncgm = CATCGMDebug::GetCGMImplement();
  return (ncgm ? ncgm->_SetWasModified(iObject) : NULL);
}

#ifdef CATIACGMR419CAA
//==================================================================================
// Pour Analyse Topologie (Internal Use)
//==================================================================================
INLINE CATBoolean CATCGMDebug::IsGMPolyObject(CATICGMObject *piICGMObject)
{
  CATCGMDebug * ncgm = CATCGMDebug::GetCGMImplement();
  return (ncgm ? ncgm->_IsGMPolyObject(piICGMObject) : NULL);
}

//==================================================================================
// Pour Analyse Topologie (Internal Use)
//==================================================================================
INLINE CATBoolean CATCGMDebug::Is_MixedPolyExactInputs_Allowed(CATCGMOperator *piCGMOperator)
{
  CATCGMDebug * ncgm = CATCGMDebug::GetCGMImplement();
  return (ncgm ? ncgm->_Is_MixedPolyExactInputs_Allowed(piCGMOperator) : NULL);
}

//==================================================================================
// Pour Analyse Topologie (Internal Use)
//==================================================================================
INLINE CATBoolean CATCGMDebug::IsGMImplicitSurfaceObject(CATICGMObject *piICGMObject)
{
  CATCGMDebug * ncgm = CATCGMDebug::GetCGMImplement();
  return (ncgm ? ncgm->_IsGMImplicitSurfaceObject(piICGMObject) : NULL);
}
#endif
  
//==================================================================================

//---------------------------------------------------------------------------------
// CreateCATCGMStreamImpl
//---------------------------------------------------------------------------------

INLINE CATCGMStreamImpl* CATCGMDebug::CreateCATCGMStreamImpl(CATCGMStream* ipItf) 
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ? bridge->_CreateCATCGMStreamImpl(ipItf) : NULL;
}
INLINE CATCGMStreamImpl* CATCGMDebug::CreateCATCGMStreamImpl(void*         iBuffer,
                                                                size_t        iSizeBuffer,
                                                                CATCGMStream* ipItf)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ? bridge->_CreateCATCGMStreamImpl(iBuffer,iSizeBuffer,ipItf) : NULL;
}

INLINE CATCGMStreamImpl* CATCGMDebug::CreateCATCGMStreamImpl(ostream&         ioFile,
                                                                size_t           iInitialNumberOfBytes,
                                                                const CATBoolean iEnableByAddress,
                                                                CATCGMStream*    ipItf)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ? bridge->_CreateCATCGMStreamImpl(ioFile,iInitialNumberOfBytes,iEnableByAddress,ipItf) : NULL;
}

INLINE CATCGMStreamImpl* CATCGMDebug::CreateCATCGMStreamImpl(istream&      ioFile,
                                                                CATCGMStream* ipItf)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ? bridge->_CreateCATCGMStreamImpl(ioFile,ipItf) : NULL;
}

INLINE CATCGMStreamImpl* CATCGMDebug::CreateCATCGMStreamImpl(const char*            iFilename,
                                                                const CATCGMStreamType iAcces,
                                                                const CATBoolean       iEnableByAddress,
                                                                CATCGMStream*          ipItf)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ? bridge->_CreateCATCGMStreamImpl(iFilename,iAcces,iEnableByAddress,ipItf) : NULL;
}

INLINE CATCGMStreamImpl* CATCGMDebug::CreateCATCGMStreamImpl(size_t                 iInitialNumberOfBytes,
                                                                const CATCGMStreamType iAcces,
                                                                const CATBoolean       iEnableByAddress,
                                                                CATCGMStream*          ipItf)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ? bridge->_CreateCATCGMStreamImpl(iInitialNumberOfBytes,iAcces,iEnableByAddress,ipItf) : NULL;
}

INLINE CATCGMStreamImpl* CATCGMDebug::CreateCATCGMStreamImpl(CATStream&             iDirectStreaming,
                                                                const CATCGMStreamType iAcces,
                                                                const CATBoolean       iEnableByAddress,
                                                                CATCGMStream*          ipItf)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ? bridge->_CreateCATCGMStreamImpl(iDirectStreaming,iAcces,iEnableByAddress,ipItf) : NULL;
}

INLINE CATCGMStreamImpl* CATCGMDebug::CreateCATCGMStreamImpl(CATStream&    iDirectStreaming,
                                                                size_t        iSizeStream,
                                                                CATCGMStream* ipItf)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ? bridge->_CreateCATCGMStreamImpl(iDirectStreaming,iSizeStream,ipItf) : NULL;
}

#if defined ( CATCGMBOAObject )
INLINE CATBaseUnknown* CATCGMDebug::CATRootContainerCGM_CreationCGM(CATCGMContainer * iContainer)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ? bridge->_CATRootContainerCGM_CreationCGM(iContainer) : NULL;
}

INLINE CATCGMObject * CATCGMDebug::_CATRootContainerCGM_NewSameType(CATCGMContainer * iContainer)
{
  CATCGMDebug *bridge = _alreadyInitialised ? CATCGMDebug::_NCGM : GetCGMImplement();
  return bridge ? bridge->_CATRootContainerCGM_NewSameType(iContainer) : NULL;
}
#endif
 

#endif
