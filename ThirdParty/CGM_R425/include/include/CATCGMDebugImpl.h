/* -*-c++-*- */
#ifndef CATCGMDebugImpl_h_
#define CATCGMDebugImpl_h_
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2000
//-----------------------------------------------------------------------------
//Pour l'implementation de la pseudo-Interface CATCGMDebug
//-----------------------------------------------------------------------------
//=============================================================================
// Jui. 02  Portage 64 bits                                               HCN
// Sep. 03  Parametre iCleanerLike pour GetUselessComponent(...)          HCN
// Oct. 03  _PurgeNonPersistent()
// Oct. 03  _GetMaxTag(...)                                               HCN
// Oct. 03  _DumpStatsGeometricTypes(...)                                 HCN
// Nov. 03  _GetLockCount(...)
//          _DumpStaticSharpnessDataGeom(...)                             HCN
// Jan. 04  _DelKnotVectorOptData(...)                                    HCN
// Feb. 04  _UnlinkUselessGeometry(...)                                   HCN
// Mar. 04  _CompareFactories                                             MNA
// Apr. 04  Ajout d'un argument (CATLISTP(CATICGMObject) oAllDifferentObj)
//          dans la methode  _CompareFactories (...)                      MNA
// Avr. 04  struct CATGeoClnCheckParameter devient une classe             FDN
// May. 04  _CompactSubd(...)                                             HCN
// May  04  _SimplifyEdgeCurve(...)                                       HCN
// Jun. 04  _CompareExactAndApproxNurbs(...)                              MNA
// Jun. 04  _MaxSquareDistanceSurSur(...)   Version NDN                   MNA
// Jul. 04  _POECStreamCompact(...), _POECUnstreamCompact(...)            HCN 
// Jun. 04  _MaxSquareDistanceSurSur(...)   Version NDN                   MNA 
// Jun. 04  _CompareExactAndApproxPNurbs(...)                             MNA
// Jun. 04  _MaxSquareDistanceCrvCrv(...)   Version NDN                   MNA
// Mar. 05  Stream ordonne des objets pointes : _StreamObject(...)        HCN 
// Jun. 05  Methode _IncDecUsecount                                       FDN
// jul. 05  Methode _SetRemovable                                         FDN
// Jul. 05  Statistiques parcours UpDown :
//            _SetFactoryCurrentOperator(...)                             HCN
// Aug. 05  _GetCATGeometricType(...),
//          _SetFactoryCurrentBnddCellIter(...),
//          _SetFactoryCurrentUpDownCallingMethod(...)                    HCN
// Jul. 09 Suppression du StreamCompact                                   VUC
// Oct. 09  IncrementalStream : IsActivated,Load,Save,...                 VUC
//=============================================================================
#include "CATCGMDebug.h"
#include "ExportedByCATGeometricObjectsCGM.h"
#include "CATBaseUnknown.h"
#include "CATICGMObject.h"
#include "CATGeoClnIDs.h"
#include "CATMathInline.h"
#include "CATGeometryType.h"
#include "CATCGMScaleCategoryDef.h"
#include "CATIACGMLevel.h"


class CATTrace;
class CATCGMObject;

class CATGeoFactory;
class CATCGMContainer;
class CATListPtrCATCGMObject;
class CATGeoClnCheckParameter;
class CATSurface;
class CATBoundedCellsIterator;
class CATListPtrCATEdgeCurve;
class CATEdgeCurve;
class CATCompareGeometry;
class CATCompareContext;
class CATCGMDirtify;

//incremental stream
//#include "CATListOfCATCGMStream.h"

class ExportedByCATGeometricObjectsCGM CATCGMDebugImpl : public CATCGMDebug
{
public :
  CATCGMDebugImpl();
  ~CATCGMDebugImpl();
  
  //---------------------------------------------------------------------------------
  // Pour Gestion du representant du couplage GeometricObjets-NewTopologicalObjects
  //---------------------------------------------------------------------------------
  static CATCGMDebugImpl *_TheOne;

  //---------------------------------------------------------------------------------
  // Pour centralisation de la creation de CATGeoFacory
  //---------------------------------------------------------------------------------
  static void NewFactory(CATGeoFactory* & itf, CATCGMContainer * & impl
                        , const CATCGMScaleCategory iScaleCategory=ScaleNotSet);
 
  //---------------------------------------------------------------------------------
  // Pour Fusion
  //---------------------------------------------------------------------------------
  virtual void _NewFactory(CATGeoFactory* & itf, CATCGMContainer * & impl
                          , const CATCGMScaleCategory iScaleCategory);
  virtual CATICGMUnknown *_CreateTIECATGeoFactoryCATGeoFactoryCGM(CATCGMContainer* impl);
  virtual CATPCurve *_GetProtectedPCurve(CATSurface* impl,CATLONG32 i);
  virtual long       _GetNumberOfProtectedPCurves(CATSurface* impl);
  virtual CATPoint * _GetBestPoint(CATMacroPoint* impl);

  //---------------------------------------------------------------------------------
  // CATGeometricObjectsCGM
  //---------------------------------------------------------------------------------

  static void MakeInitPoint(); 
  static void MakeInitCurve(); 
  static void MakeInitSurface(); 
  static void MakeInitLaw(); 
  static void MakeInitCGMGeoTopo();

protected :
  
  
    
  //=================================================================
  // Integration CATCGMPeriodicityManager Procedural 
  //   gestion implementative sans impact Interface 
  //=================================================================
  virtual CATBoolean _CATCGMPeriodicityManager_GetInfo( CATCurve * iCurve, CATCGMPeriodicityInfo & oInfo ) ;
  virtual CATBoolean _CATCGMPeriodicityManager_GetInfo( CATSurface * iSurface, CATBoolean iUorV, CATCGMPeriodicityInfo & oInfo ) ;

  //=================================================================
  //   integration Native sans impact Exposition Interface  
  //=================================================================
  virtual void _CATCGMPeriodicityManager_SetInfo( CATSurface * iSurface, CATBoolean iUorV, const CATCGMPeriodicityInfo & iInfo );
  virtual void _CATCGMPeriodicityManager_SetInfo( CATCurve * iCurve, const CATCGMPeriodicityInfo & iInfo );

  //---------------------------------------------------------------------------------
  //  GetUsageContext
  //---------------------------------------------------------------------------------
  virtual CATCGMUnknown_UsageContext   _GetUsageContext(CATICGMUnknown *iCGMObject) ;
 

  virtual CATGeometricType _GetCATGeometricType(const char* ipGeometricTypeName);

  virtual void _PutColor(CATICGMObject* obj,int red,int green, int blue) ;
  virtual void _Show(CATICGMObject* obj);
  virtual void _NoShow(CATICGMObject* obj) ;
  virtual int  _IsNoShow(const CATICGMObject* obj);
  virtual void _Dump(const CATICGMObject* obj, CATCGMOutput& os );

  virtual void _SynchroShow(CATGeoFactory* iFactory, const CATLISTP(CATICGMObject) & ioVisuPart);

  virtual CATBoolean _GetLockCount(CATICGMObject* ipObject, int& ioLockCount);
  virtual CATBoolean _DelKnotVectorOptData(CATICGMObject* ipObject);

  virtual CATBoolean _CompactSubd(CATGeoFactory* ipFactory);

  virtual double _MaxSquareDistanceSurSur(CATSurface * Surf1, CATSurface * Surf2);
  
  virtual double _MaxSquareDistanceCrvCrv(CATCurve * Crv1, CATCurve * Crv2);

  virtual int _GetColor(const CATICGMObject* obj,int &red,int &green, int &blue);
  virtual size_t _GetSize(const CATICGMObject* obj) ;   
  virtual size_t _GetStaticMemoryBytes(const CATICGMObject* obj);
  virtual size_t _GetDynamicMemoryBytes(const CATICGMObject* obj);
  virtual size_t _GetCumulatedStreamSize(const CATLISTP(CATICGMObject) &iObjects) ;   

  //---------------------------------------------------------------------------------
  virtual CATCGMOperator* _SetFactoryCurrentOperator(CATCGMOperator* ipCGMOperator, CATGeoFactory* ipFactory);
  virtual CATBoundedCellsIterator* _SetFactoryCurrentBnddCellIter(CATBoundedCellsIterator* ipBnddCellIter, CATGeoFactory* ipFactory);
  virtual int _SetFactoryCurrentUpDownCallingMethod(int iUpDownCallingMethod, CATGeoFactory* ipFactory);

  virtual CATGeoFactory* _IsFactoryCNEXT(CATGeoFactory *iFact);
  virtual CATULONG32 _GetMaxTag(CATGeoFactory *iFact);
  virtual CATBoolean _CompareFactories(CATGeoFactory *iFacto1, CATGeoFactory *iFacto2,CATLISTP(CATICGMObject) &oAllDifferentObj);
  virtual CATBoolean _CompareExactAndApproxNurbs(CATGeoFactory *iFacto1, CATGeoFactory *iFacto2,CATLISTP(CATICGMObject) &oAllDifferentNurbs);
  virtual CATBoolean _CompareExactAndApproxPNurbs(CATGeoFactory *iFacto1, CATGeoFactory *iFacto2,CATLISTP(CATICGMObject) &oAllDifferentPNurbs);

  virtual CATBoolean _CATCGMDebugUI(CATICGMObject* iObject);

#if defined ( CATCGMBOAObject )
  virtual CATBaseUnknown * _CATRootContainerCGM_CreationCGM(CATCGMContainer * iContainer) ;
  virtual CATCGMObject   * _CATRootContainerCGM_NewSameType(CATCGMContainer * iContainer) ;
#endif

  //=================================================================================
  // Passage transparent TIEBOA  CATGeoFactory -> CATGeoFactoryProtected
  //=================================================================================
   virtual CATGeoFactoryProtected* _GetProtectedInterface(CATGeoFactory *iFact);
#if defined ( CATCGMBOAObject )
   virtual void _InitRootContainer(CATGeoFactoryProtected *iFactoryProtected);
#endif


  //=================================================================
  //  Duplicate
  //=================================================================
  virtual void _Duplicate(CATGeoFactory* iFactory, CATGeoFactory*& oFactory) ;

  //---------------------------------------------------------------------------------

  virtual void _Save(const CATGeoFactory* iFactory,
                     const char iFilename[],
                     const int iWithTass=1,
                     const CATCGMStreamVersion iWantingVersion = CatCGMStream_UnknownVersion);

  virtual void _Load(const char iFilename[],
                     CATGeoFactory* &oFactory,
                     const CATBoolean      avoidAnyRattrap = FALSE,
                     CATCGMStreamVersion  *iWantingVersion = NULL);

  virtual CATGeoFactory* _CATCreateCGMContainer (const CATCGMScaleCategory iScaleCategory, 
                                                 const CATPositiveLength iUnitInMeter); 
                                                 
  virtual CATGeoFactory* _CATLoadCGMContainer   (istream& iStreamArea,
                                                 const CATCGMVersionDefinition **ptrUnstreamVersion = NULL);

  virtual CATGeoFactory* _CGMLoadRootContainer(      CATCGMStream             & streamarea,
                                               const CATCGMVersionDefinition ** ptrUnstreamVersion = NULL,
                                               const CATBoolean                 avoidAnyRattrap = FALSE );
  
  

  virtual void           _CATSaveCGMContainer   (const CATGeoFactory       * iFact,
                                                 ostream                   & ioStreamArea,
                                                 const CATCGMStreamVersion   iWantingVersion = CatCGMStream_UnknownVersion);

  virtual HRESULT  _CATSaveCGMContainer   (const CATGeoFactory* iFact, 
                                       CATCGMStream & ioStreamArea) ;


  virtual void           _CATCloseCGMContainer  (CATGeoFactory* iFact);


  
  //=================================================================
  // Incremental Stream of the CGM Container
  //=================================================================

  virtual int _IsIncrementalStreamActivated();
  virtual int _IsIncrementalStreamTraceActivated();
  virtual int _IsIncrementalStreamTest();
  // Debug : only use in Incremental save test
  // iSwitchMode : 1 - Switch mode, 0 - Do NOT switch mode
  // return value
  // 0 : Standard save 
  // 1 : Incremental save
  virtual int _GetIncrementalStreamTestMode(CATBoolean iSwitchMode);
	virtual void _SetIncrementalStreamActivated();

  virtual CATGeoFactory* _CGMIncrementalLoadRootContainer(  CATLISTP(CATCGMStream )  &  ListOfCGMStream, 
                                                      const CATCGMVersionDefinition **  ptrUnstreamVersion,
                                                      const CATBoolean                  avoidAnyRattrap);

  virtual HRESULT _CGMIncrementalSaveContainer(const CATGeoFactory* iFactory,   
                                               CATCGMStream & TheStream,
                                               const CATCGMStreamVersion iWantingVersion = CatCGMStream_UnknownVersion, 
                                               CATBoolean iWithTass = FALSE);

  virtual HRESULT _CheckIncrementalStream(const CATGeoFactory* iFactory, CATCGMOperator *iOperator);

  //VUC 2009-10-28
  virtual HRESULT _SetWasModified(CATICGMObject* iObject);

  //=================================================================
  // Pour modele compacte
  //=================================================================

  virtual CATBoolean _AddParamToPOEC(CATPointOnEdgeCurve* ipPOEC,
                                     const CATLONG32      iSpecCount, 
                                     const CATCurve**     ippCurves,
                                     const double*        ipLocalParamValues,
                                     const CATLONG32*     ipArcValues);

  //=================================================================
  // Stream ordonne des objets pointes
  //=================================================================
  virtual void _StreamObject(CATICGMObject* ipObject, CATCGMStream& Str);

  //=================================================================
  // From GeoFactory To Federators of modelisation
  //=================================================================
  virtual void _GetFederators(CATGeoFactory*            iFactory,
                              CATLISTP(CATICGMObject) & ioFederators, 
                              CATCGMFederatorsFilter    iFilterSpec,
                              CATGeometricType          iFilterType);



  //---------------------------------------------------------------------------------
  virtual CATBoolean _GetNewObjectLeaks(CATGeoFactory* iFact,
    const CATLISTP(CATICGMObject) &iExpectedNewObjects, 
    CATLISTP(CATICGMObject) &ioFederators, CATLISTP(CATICGMObject) &ioAlls);

  virtual CATBoolean _GetNotPersistent(CATGeoFactory* iFact,
    CATLISTP(CATICGMObject) &oFederators, CATLISTP(CATICGMObject) &oAlls);
  
  virtual CATBoolean _GetUselessComponent(CATGeoFactory* iFact,
    CATLISTP(CATICGMObject) &oInMacroPoint, CATLISTP(CATICGMObject) &oInEdgeCurve, CATBoolean iCleanerLike);

  virtual void _PurgeNonPersistent(int WithPrecaution = 0);

  //---------------------------------------------------------------------------------
  virtual CATULONG32  _GetCGMBuildVersion(CATICGMContainer * iFactory) ;
 
  //---------------------------------------------------------------------------------
  virtual void _UnlinkUselessGeometry(CATTopology* ipTopology, CATCGMEventType iEventType, CATPoint* ipSpecificPoint, CATBoolean iRemoveFromFactory);

  //---------------------------------------------------------------------------------
  
  virtual void _IncDecUseCount(CATICGMObject * iObj, int Add1_Remove0, CATULONG32 & oUseCount,
                               CATBoolean iRemoveFactoryIfPossible = FALSE, CATBoolean * oRemovedFromFactory = 0);

  virtual void _SetRemovable(CATICGMObject * iObj, CATBoolean iYesNo, CATBoolean * oWasRemovable = 0);

  virtual void _CATTopRibNupletCell(CATCell *, int Add1_Remove0); // deprecated

  virtual CATICGMObject* _catcxitf(CATICGMObject *itf);

  virtual void _SynchronizeExplicitWithNullUseCount(CATGeoFactory* iFact);
  virtual void _SynchronizeTags(CATGeoFactory* iFact, CATMapVoidToVoid * iContents) ;
  virtual void _WriteContainer(CATICGMContainer* obj, const char* filename);
  virtual void _WriteContainer(CATICGMObject   * obj, const char* filename);

  INLINE CATCGMObject * GetCATCGMObject(const  CATICGMObject *itf );

  virtual void _DetachFactoryFromReplay(CATGeoFactory* iFact, CATExtCGMReplay *iReplay);
   virtual void _DetachFactoryFromChain(CATGeoFactory* iFact, CATCGMChain *iChain);

  virtual CATCGMTempoULONGPTR * _CreateTempoULONGPTR( CATGeoFactory* iFactory ) ;

  //---------------------------------------------------------------------------------
  // Pour parametrage du Checker
  //---------------------------------------------------------------------------------
  virtual int _CheckCurveActive();        // deeper CheckUp analysis
  virtual int _CheckEdgeCurveActive();
  virtual int _CheckPOECActive();
  virtual int _CheckUpwardLinksIsOn();
  virtual int _CheckUpwardLinksTemporaryChange(int action);
  
  //---------------------------------------------------------------------------------
  //  Pour GetSessionIdNumber
  //---------------------------------------------------------------------------------
  virtual CATULONG32   _GetSessionIdNumber(CATGeoFactory *iFactory) ;
  virtual CATCGMStreamVersion _GetLastStreamVersion(CATGeoFactory* iFactory) ;

  //---------------------------------------------------------------------------------
  // Tools  (CATGeoControl)
  //---------------------------------------------------------------------------------
  virtual void _GetAllDependancies(const  CATLISTP(CATICGMObject) & iStarter, CATLISTP(CATICGMObject)   & ioEveryone) ;
  virtual void _GetMaxLimOfParms(const CATLISTP(CATICGMObject)  & iStarter, 
                                 const CATBoolean                 iOnlyHoldingKnotVector,
                                 CATLISTP(CATCGMLimOfParm)      & ioParm) ;

  //-------------------------------------------------------------------------
  // Pour Analyse Topologie
  //-------------------------------------------------------------------------
  virtual void _GetAllGeometricRep(CATCurve *iCurve, CATLISTP(CATCurve) &ioReps);
  virtual void _GetAllGeometricRep(CATPoint *iPoint, CATLISTP(CATPoint) &ioReps);

  //-------------------------------------------------------------------------
  // Pour Detection d'operation specifique sur la Factory 
  //    (Sauvegarde a partir du format V5R11)
  //-------------------------------------------------------------------------
  virtual void        _DefineIsDoing(CATGeoFactory *iFactory, const CATCGMFactoryStatus iSpecificOperation);
  virtual CATBoolean  _HasBeenDone(CATGeoFactory *iFactory,   const CATCGMFactoryStatus iSpecificOperation);

  //-------------------------------------------------------------------------
  // Pour analyse du modele dans CATGem
  //-------------------------------------------------------------------------
  virtual void _DumpStatsGeometricTypes(CATListPtrCATCGMObject& iListOfObjects, CATCGMOutput& iOutput);

  virtual void _DumpStaticSharpnessDataGeom(CATGeometry* ipGeometry, char* ipAlignMSG, CATCGMOutput& iOutput);

  //-------------------------------------------------------------------------
  // Pour CGMCleaner
  //-------------------------------------------------------------------------

  virtual void _CGMCleanerCheckSelectRuleBegin(CATGeoClnIDs::RuleID ipSpecificRuleID, CATGeoClnCheckParameter* ipRuleCheckParameter = NULL);

  virtual void _CGMCleanerCheckSelectRuleAdd(CATGeoClnIDs::RuleID ipSpecificRuleID, CATGeoClnCheckParameter* ipRuleCheckParameter = NULL);

  virtual void _CGMCleanerSpecificCheck(CATICGMObject* ipSpecificToCheck, const char IdentityBuildOperator[]);

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
                                        CATBoolean*              iopIsSimplifiable);

  virtual void _BuildGraph(CATCGMGraph * iGraph, CATICGMUnknown *iRoot);

  
  //=================================================================
  //   GetContents : provide contents as HT of CATCGMObjects
  //=================================================================
  virtual void _GetContents(CATGeoFactory* iFactory, CATMapVoidToVoid * & ioContents) ;
  
  //=================================================================
  //   GetDump : provide Dump (For ODT)
  //=================================================================
  virtual void _GetDump(CATICGMObject* iCGMObject, CATUnicodeString & oDumpDefinition) ;

  //---------------------------------------------------------------------------------
  // CreateCATCGMStreamImpl
  //---------------------------------------------------------------------------------

  virtual CATCGMStreamImpl* _CreateCATCGMStreamImpl(CATCGMStream* ipItf);

  virtual CATCGMStreamImpl* _CreateCATCGMStreamImpl(void*         iBuffer,
    size_t        iSizeBuffer,
    CATCGMStream* ipItf);

  virtual CATCGMStreamImpl* _CreateCATCGMStreamImpl(ostream&         ioFile,
    size_t           iInitialNumberOfBytes,
    const CATBoolean iEnableByAddress,
    CATCGMStream*    ipItf);

  virtual CATCGMStreamImpl* _CreateCATCGMStreamImpl(istream&      ioFile,
    CATCGMStream* ipItf);

  virtual CATCGMStreamImpl* _CreateCATCGMStreamImpl(const char*            iFilename,
    const CATCGMStreamType iAcces,
    const CATBoolean       iEnableByAddress,
    CATCGMStream*          ipItf);

  virtual CATCGMStreamImpl* _CreateCATCGMStreamImpl(size_t                 iInitialNumberOfBytes,
    const CATCGMStreamType iAcces,
    const CATBoolean       iEnableByAddress,
    CATCGMStream*          ipItf);

  virtual CATCGMStreamImpl* _CreateCATCGMStreamImpl(CATStream&             iDirectStreaming,
    const CATCGMStreamType iAcces,
    const CATBoolean       iEnableByAddress,
    CATCGMStream*          ipItf);

  virtual CATCGMStreamImpl* _CreateCATCGMStreamImpl(CATStream&    iDirectStreaming,
    size_t        iSizeStream,
    CATCGMStream* ipItf);

  virtual void _TransferSharpness(CATListPtrCATEdgeCurve & iSources, CATEdgeCurve & iTarget);

  virtual CATCompareGeometry * _CreateCompareGeometry(CATCompareContext * ioContext);

#ifdef CATIACGMR419CAA
  virtual CATBoolean _IsGMPolyObject(CATICGMObject *piICGMObject);

  virtual CATBoolean _Is_MixedPolyExactInputs_Allowed(CATCGMOperator *piCGMOperator);

  virtual CATBoolean _IsGMImplicitSurfaceObject(CATICGMObject *piICGMObject);
#endif

private :

#ifdef CATIACGMR419CAA
  CATBoolean _IsGMPolyObject_SpecialRescue(CATICGMObject *piICGMObject);
  CATBoolean _IsGMImplicitSurfaceObject_SpecialRescue(CATICGMObject *piICGMObject);
#endif

   static CATTrace   *_CATCGMCheckCurve;     // for deeper CheckUp analysis of Curve
   static CATTrace   *_CATCGMCheckEdgeCurve; // for Check on fly of CATEdgeCurve 
   static CATTrace   *_CATCGMCheckPOEC;      // for Check on fly of POEC

   static CATTrace   *_CATCGMCheckUpwardLinks;      // for Check UpwardLinks on fly 
   static int _UpwardLinksTemporaryChange;
	 static int _IncrementalStreamActivated; // 1 : active : 0: inactive
};

//=============================================================================
// INLINE IMPLEMENTATION
//=============================================================================
INLINE CATCGMObject * CATCGMDebugImpl::GetCATCGMObject( const CATICGMObject *itf )
{
  return itf ? (CATCGMObject* )itf->IsCGMV5() : NULL;
}


#endif
