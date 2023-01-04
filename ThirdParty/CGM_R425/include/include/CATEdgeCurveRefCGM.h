/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATEdgeCurveRefCGM
// CGM common implementation for types of CATEdgeCurve able to redirect
// methods on one of their curves.
//=============================================================================
// Usage notes:
//
// CXR2
// If you inherit from this class, you have to ;
// - maintain _RefCurve pointer to a reference curve which will be used for eval, ...
// - provide the object base methods ( constructor, set, ...),
//   and the ApplyTransformation and Next methods.
//=============================================================================
// Jul. 97   Creation                                     R. Rorato
// Apr. 98   Add IsInvariant method                       I. Levy
// Apr. 98   Modify GetParam method                       I. Levy
// May  98   New GetEquivalentPoint                       P. Tonnerre
// July 98   Inheritance from CATCurveBase                R. Rorato
// July 98   Move IsInvariant into CATCurveBase           I. Levy
// May  99   New EdgeCurves, using CATMapX                E. Guerin
// Nov. 03 Parametre iopNbDatas pour GetSharpnessCGMData(...)             HCN
// Jan. 04 GetLockCount() passe de protected a public                     HCN
// Mar. 04 Stream/UnStreamMapXAndSharpnessCpt(...),
//         Stream/UnStreamMapXAndSharpnessCptLoss(...)                    HCN
// May. 04 GetStreamSortingKey(...),
//         GetMaxSimilarityLevel()                                        HCN
// Mar. 05 RI0486478 : GetStreamPreferedRank(),
//                     AllLinkedObjectsAlreadyStreamed()
//                     HasOrderedLinkedObjectStream()                     HCN
// Jul. 09 Suppression du StreamCompact                                   VUC
// Aug. 11 Added access functions for data in the Math Bloc data (for
//         comparing geometries).                                         R1Y
// Jan. 14 Moved GetTabMapX() from protected to public.                   R1Y
//=============================================================================
#ifndef CATEdgeCurveRefCGM_H
#define CATEdgeCurveRefCGM_H

#include "ExportedToCGMV5Interoperability.h"                  

#include "CATMathDef.h"
#include "CATCurveBaseCGM.h"                
#include "CATEdgeCurve.h"
#include "CATParamData.h"
#include "CATMathInline.h"

class CATSurface ;
class CATGeometry ;
class CATKnotVector;
class CATMathBox ;
class CATMathCurve ;
class CATCrvParam ;
class CATCrvLimits ;
class CATMathFunctionX ;
class CATMapX;
class CATSharpnessCGMData;

#define StaticTabMapXSIZE 1
#define MaxTabMapXCount  ((unsigned short) 0xFFFF)


struct CATMergedCurveCGMDataForUnstream
{
  CATParamData start;
  CATParamData end;
};


//--------------------------------------------------------------------
class ExportedToCGMV5Interoperability CATEdgeCurveRefCGM: public CATCurveBaseCGM
{
  public :

  CATCGMDeclareVirtualClass;

  //-------------------------------------------------------------------------
  // Methods of the CATEdgeCurve Interface
  //-------------------------------------------------------------------------
  virtual const CATCurve*  Next          ( const CATCurve *CurrentSubElement ) const;
  virtual const CATPCurve* NextOnSupport ( const CATCurve   *iCurrentSubElement, 
                                           const CATSurface *iSupport            ) const ;
  virtual const CATCurve*  NextThru      ( const CATCurve *CurrentSubElement ) const ;
  virtual void  GetEquivalentParam       ( const CATLONG32          iSpecsCount, 
                                           const CATCurve*     iSpecCurves[],
                                           const CATCrvParam   iSpecParams[],
                                           CATCrvParam&        oBestParam) const;
  virtual CATEdgeCurve::CATCompareDiagnostic Compare( const CATLONG32          iCurvesCount, 
                                                      const CATCurve*     iCurves[],
                                                      const CATCrvParam   iParams[],
                                                      CATCrvParam & oSuggestedParam,
                                                      CATPositiveLength* oGap = NULL ) const ; 
  virtual CATCrvParam GetEquivalentPoint (const CATCrvParam &iLocationOnCurrentCurve,
                                          const CATCurve    *iCurrentCurveOrEdgeCurve,
                                          const CATCurve    *iEquivalentCurve,
                                          const short        iReconverge=1) const ;
  virtual void  GetEquivalentPoint    ( const CATCrvParam &iParamOnCurrentCurve,
                                        const CATCurve    *iCurrentCurveOrEdgeCurve,
                                        const CATCurve    *iEquivalentCurve, 
                                        CATCrvParam       &oParamOnEquivalentCurve,
                                        const short        iReConverge=1) const ;

 

  virtual CATMathFunctionX* GetParamMap ( const CATCurve *iCurvew,
                                          const CATCurve *iCurvefw, CATBoolean iAdjustedC2=0, const double * iDomain=0 ) const ;
  virtual CATMapX* GetMapX ( const CATCurve *iCurvew,
                             const CATCurve *iCurvefw ) const ;
  virtual short GetRelativeOrientation( const CATCurve    *iCurrentCurve ) const;
  virtual CATPositiveLength GetMaxGap () const;
  virtual CATPositiveLength ComputeMaxGap();
  virtual CATCurve* GetRefCurve() const;
  virtual CATCurve* GetCurveRep() const;
  virtual CATMapX* GetMapX ( const CATCurve* iCurve)const;
  virtual void     SetMapX ( const CATMapX*  iMapX, const double iMaxGap=0,
                             const short iEvent=0);
  virtual void     UpdateMapX();

  virtual short GetSharpness ( 
              const CATPCurve   *iC1,
              const CATPCurve   *iC2,
              CATGeoContinuity *oContinuity,
              CATGeoConvexity  *oConvexity = 0) const;

  virtual void SetSharpness (
              const CATPCurve*                  iC1,
              const CATPCurve*                  iC2,
              const CATGeoContinuity           iSharpness,
              const CATGeoConvexity            iConcavity = CATUnknownConvexity);

  virtual void ClearSharpness();

  //------------------------------------------------------------------
  // Methods of the CATCurve Interface (see CATCurve.h for comments)
  //------------------------------------------------------------------
  virtual CATCrvLimits  GetInternalLimits   ( const CATLONG32 Internal ) const ;
  virtual CATCrvLimits  GetInternalMaxLimits( const CATLONG32 Internal ) const ;
  virtual CATLONG32          GetNumberOfComponent() const ;
  virtual CATCrvLimits  GetLimits() const ;
  virtual const CATKnotVector * GetKnotVector() const;
  virtual CATCrvParam   CreateParam         ( const double & param) const;
  virtual CATCrvParam   CreateParam         ( const double & w, const CATLONG32 & iarc) const;
  virtual const CATCrvParamReference * GetParamReference() const;  

  void Lock(const void *iDebugUsage=NULL) ;
  void Unlock(const void *iDebugUsage=NULL) ;
  virtual void OpenEquation(const void *iDebugUsage=NULL);
  virtual void CloseEquation(const void *iDebugUsage=NULL);

  virtual void GetEquation ( const CATLONG32 iArcIndex,
                             const CATMathFunctionX * & oFx,
                             const CATMathFunctionX * & oFy,
                             const CATMathFunctionX * & oFz) const;
  virtual void GetGlobalEquation ( const CATMathFunctionX * & oFx,
                                   const CATMathFunctionX * & oFy,
                                   const CATMathFunctionX * & oFz) const;
  virtual CATBoolean IsClosed() const ;
  virtual void GetInternalMaxBoundingBox ( const CATLONG32 iArc, CATMathBox & oBox) const ;
  virtual void GetInternalBoundingBox    ( const CATLONG32 iArc, CATMathBox & oBox) const ;
  virtual CATMathBox GetInternalBoundingBox(const CATLONG32 iInternal) const ;
  virtual CATMathBox GetInternalMaxBoundingBox(const CATLONG32 iInternal) const ;
  virtual void GetBox( const CATCrvLimits & iLimits, CATMathBox & oBox ) const ;
  //-------------------------------------------------------------------------------------------
  // IR 174792 (Specific Corrupted Hidden Data,  mkodtimpact CATEdgeCurveRefCGM::ZornGetBox
  //     Drop 0/ T Limited correction here By Soft For coverage by dedicated error management (Time-Driven) 
  //     After Review 
  //       ?  ToStudy  Drop 1/ RCA (operator chain and LifeCycle)
  //       ?  ToStudy  Drop 2/ Datumiser-Simplification with reparametrisation Impact 
  //-------------------------------------------------------------------------------------------
  virtual CATBoolean  ZornGetBox( const CATCrvLimits & iLimits, CATMathBox & oBox ) const ;
  virtual int GetAdvancedBox(const CATCrvLimits &iLimits, CATMathAdvancedBox &oBox) const;
  virtual CATBoolean IsAdvancedBoundingBoxTypeAvailable(CATMathAdvancedBoxType iType) const;
  virtual CATCurve::CATSolutionDiagnostic GetParam(const CATMathPoint & iLocation,
                                                   CATCrvParam  & oIndex ) const ;
  virtual CATCurve::CATSolutionDiagnostic GetParam(const CATMathPoint & iLocation,
                                                   CATCrvParam  & oIndex   ,
                                                   const CATCrvLimits & iInside  ) const ;
  virtual CATMathCurve* GetMathCurve() const ;
  virtual CATBoolean HasMathCurve() const ;
  virtual const CATCurve * GetGeometricRep(CATCrvLimits & oRepLimits,
                                           short & oOrientation) const ;
  virtual CATGeometry * GetOwner() const ;
  virtual  CATCurve::CATProjectionDiagnostic CreateProjection(CATPlane* iOn, 
							      CATPCurve* & oProjection, 
							      CATSetOfCrvParams* iIndexOnCurve,
							      CATSetOfCrvParams* ioIndexOnPCurve) const ;

  virtual void Eval( const CATCrvParam       & iPoint,
                     const CATCrvEvalCommand & iCommand,
                     CATCrvEvalLocal         & oResult) const ;
  virtual void Eval( const CATCrvLimits      & iDomainToEvaluate,
                     const CATLONG32                iNbOfPoints,
                     const CATCrvEvalCommand & iCommand,
                     CATCrvEvalResult        & oResult) const  ;
  virtual void Eval(const CATCrvParam & iParam,
                    const CATCrvEvalCommand & iCommand,
                    CATMathPoint* oPoint,
                    CATMathVector* oFirstDeriv = NULL,
                    CATMathVector* oSecondDeriv = NULL,
                    CATMathVector* oThirdDeriv = NULL ) const ;
  virtual void Eval (const CATCrvLimits & box,
                     CATEvalCommand command,
                     CATMathSetOfPoints *& point,
                     CATMathSetOfVectors *& dw,
                     CATMathSetOfVectors *& dw2) const;
  virtual void GetLimits(CATCrvLimits & oCurrentLimits) const ;
  virtual void GetInternalLimits(const CATLONG32 iArc, CATCrvLimits & oInternalMaxLimits) const ;
  virtual void GetInternalMaxLimits(const CATLONG32 iArc, CATCrvLimits & oInternalMaxLimits) const ;
  virtual void CreateParam(const double iGlobalParam, CATCrvParam & oParam) const ;
  virtual void CreateParam(const double iLocal, const CATLONG32 iArc, CATCrvParam & oParam) const ;

  virtual void GetStartLimit(CATCrvParam & oStartParam) const;
  virtual void GetEndLimit(CATCrvParam & oEndParam) const;
  virtual void GetMaxLimits(CATCrvLimits & oMaxLimits) const;
  virtual CATCrvParam GetStartLimit() const;
  virtual CATCrvParam GetEndLimit() const;
  virtual CATCrvLimits GetMaxLimits() const;
  virtual void SetLimits(const CATCrvLimits & iLimits);

  virtual CATBoolean IsInvariant(const CATMathTransformation & iTransfo,
                                 CATMathTransformation1D* oTransfo1D = NULL) const ;
  virtual CATBoolean IsConfused(const CATMathTransformation   & iTransfo,
                                const CATCurve                * iTCurve,
			                          CATMathTransformation1D * iTransfo1D = NULL) const ;
  virtual CATBoolean IsContaining ( const CATCurve* iContained ) const ;
  virtual CATBoolean IsContainingWithLimits ( const CATCurve* iContained, CATPointOnEdgeCurve *StartPOECOnEdgeCurve,
                                                                          CATPointOnEdgeCurve *EndPOECOnEdgeCurve,
                                                                          CATPointOnEdgeCurve *StartPOECOnCurve,
                                                                          CATPointOnEdgeCurve *EndPOECOnCurve) const;

  virtual CATCurve * Simplify(CATSurface * iSurface1,
                              CATSurface * iSurface2,
                              CATMathFunctionX * &oMapping) const;

	virtual double GetNaturalParamFromParam(const CATCrvParam &iParam) const;
	virtual void GetParamFromNaturalParam(double iNatural, CATCrvParam &oParam) const;

  //------------------------------------------------------------------
  // Methods of the CATGeometry Interface
  //------------------------------------------------------------------
  virtual CATMathBox GetBoundingBox() const ;// a supprimer
  void GetBoundingBox(CATMathBox & oBox) const;

  //------------------------------------------------------------------
  // Methods of the CATCurveBase Implementation
  //------------------------------------------------------------------
  virtual CATLONG32 GetIndexOffset() const;
  
  //------------------------------------------------------------------
  // Object Management
  //------------------------------------------------------------------
  CATEdgeCurveRefCGM(CATCGMContainer * iContainer) ;
  virtual ~CATEdgeCurveRefCGM();

  //----------------------------------------------------------------------
  // Stream/UnStream
  //----------------------------------------------------------------------
  virtual CATBoolean _IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;

  // Optimisation de la structure du container sur disque
  virtual CATULONG32 GetStreamPreferedRank();
  virtual CATBoolean AllLinkedObjectsAlreadyStreamed();

  void StreamMapXAndSharpness( CATCGMStream& Str ) ;
  void UnStreamMapXAndSharpness( CATCGMStream& Str, CATLISTP(CATICGMObject)& ListDependencies ) ;

  void StreamMapXAndSharpness_MonoCurve( CATCGMStream& Str, CATMapX** TabMapX, CATLONG32 nbSharp, unsigned char MonoCurve);
  void UnStreamMapXAndSharpness_MonoCurve( CATCGMStream& Str, CATLISTP(CATICGMObject)& ListDependencies, unsigned char MonoCurve) ;

  virtual int    GetMaxSimilarityLevel();
 
  // stream compact 2011Spring
  void GetGlobalParamOfRefCurve(double& oLowLimit, double& oHighLimit,  CATCGMStreamImpl* pStrImpl);
  void GetStartLocalParam(double & oStartParam, CATLONG32& oPartNumber) const;
  void GetEndLocalParam(double & oEndParam, CATLONG32& oPartNumber) const;
  // for LoopCompact
  CATBoolean FindPCOnSupportForLoopCompact(CATSurface* iSupport, CATPCurve* & oPC);
	// stream incremental
	void SpecificUnstreamLimitsForIncrementalStream(CATCGMStreamImpl * pStrImpl, CATLISTP(CATICGMObject)& ListDependencies, LimitCompactInfo & oLimits );

  //------------------------------------------------------------------------------
  // CATCGMQueryManager (donnees extrapolees + ..)
  //------------------------------------------------------------------------------
  virtual CATCGMLimitsManagement QueryLimitsManagement(CATCrvLimits *ioMinimaLimits = NULL);
  void DoLimitsRequest(const CATCGMLimitsRequest iRequest, CATCGMQueryManager &iQuery);

  void PropagateQuery(CATICGMUnknown *iFrom, const CATCrvLimits & iLimits, CATCGMQueryManager &iQuery );


  //------------------------------------------------------------------
  // Cycle de Vie
  //------------------------------------------------------------------

  virtual void Clear();

  virtual void Set(const CATCurve* iC1, const CATCurve* iC2, const short iEvent=1);
  virtual void Set(const CATCurve* iC1, const CATCrvLimits & iLim1,
                   const CATCurve* iC2, const CATCrvLimits & iLim2,const short iEvent=1);
  virtual void SetMapX(CATLONG32 iNbMapX,CATMapX* iMapX[], const double iMaxGap=0, 
                       const short iDuplic=1, const short iEvent=1);
  CATCurve* GetICurve(const CATLONG32 iIndex,CATMapX** oMapX=NULL)const;
  CATLONG32      GetNbCurves()const;

  virtual void ClearMapX(CATCurve* iNewRefCurve = NULL);

  //------------------------------------------------------------------
  // Macro for using ObjectModeler
  //------------------------------------------------------------------
//  CATCGMDeclareClass;
  //---------------------------------------------------------------------------
  // Clone 
  //---------------------------------------------------------------------------
  CATICGMObject* Clone(CATCloneManager& iCloneManager) const;

  //---------------------------------------------------------------------------
  // Methods of the CATTransfoManager 
  //---------------------------------------------------------------------------
  void Move3D(CATTransfoManager& iTransfo);
  CATGeometry* CloneAndMove3D(CATTransfoManager& iTransfo);
  void GetLinksCGM(CATLISTP(CATICGMObject) &oLinks,
		CATCGMLinkType         iLinkType = CatCGMDependancies,
		CATRCOLL(int)*         oSharedStatus = NULL,
		CATLISTV(CATString)*   oLinksString = NULL);
  CATBoolean IsDeepConfused(CATTransfoManager & iTransfo, const CATGeometry * iTGeometry) const;

  //----------------------------------------------------------------
  // Analyse content of Object for checkup report
  //----------------------------------------------------------------
  void PerformEdgeCurveCheck() const;
  void PerformEdgeCurveCheck2() const;
  void PerformEdgeCurveCheck_EIP() const;
  virtual void CheckUp(CATCX_CHECKUP* report);
  virtual void Dump(CATCGMOutput& os);
  virtual void DeepDump(CATCGMOutput& os, short iColumn);

  void GetParamInside(CATCrvParam & ioParam,const CATCurve* iCurve) const;


	// RHA le 25/10/99
  CATBoolean CheckGeometry(CATPointOnEdgeCurve *StartPOEC=0, CATPointOnEdgeCurve *EndPOEC=0, 
    double iTol=0. , CATCX_CHECKUP* report=0, CATCGMObject *cxedge = 0) const;

  //------------------------------------------------------------------------
  // Gestion des informations dynamiques rarement utilises
  // pour gain de consommation memoire ..
  //------------------------------------------------------------------------
  virtual CATCGMDynObject *CreateDynObject();  
  virtual short            DynObjectIsUseless(); 

  //------------------------------------------------------
  //  Pour IntCurve et SimCurve
  //------------------------------------------------------
  CATParamData* GetV2R0Data() const;
  void SetV2R0Data(CATParamData* iData);

  //------------------------------------------------------
  //  Pour MergeCurve
  //------------------------------------------------------
  CATMergedCurveCGMDataForUnstream* GetV2R0DataMergeCurve() const;
  void SetV2R0DataMergeCurve(CATMergedCurveCGMDataForUnstream* iData);

  //------------------------------------------------------
  //  Pour Gestion Sharpness 
  //------------------------------------------------------
  CATSharpnessCGMData* GetSharpnessCGMData(int* iopNbDatas = NULL) const;
  void SetSharpnessCGMData(CATSharpnessCGMData* iData);

  //-------------------------------------------------------------------------
  // Pour Analyse Topologie
  //-------------------------------------------------------------------------
  virtual void GetAllGeometricRep( CATLISTP(CATCurve) &ioReps, CATHashTabCATICGMUnknown *iPerfoLocate = NULL);

  int GetLockCount() const;

 //-------------------------------------------------------------------------
  // GetApproximateXXX  for tessellation purpose 
  //    with SAG value rather than Resolution criteria
  //-------------------------------------------------------------------------

  virtual HRESULT GetApproximateEquivalentPoint( const CATCrvParam       &  iParamOnCurrentCurve,
				         const CATCurve          *  iCurrentCurveOrEdgeCurve,
	 			         const CATCurve          *  iEquivalentCurve,
                                                 const CATPositiveLength &  iApproximateResolution ,
                                	         CATCrvParam             &  ioParamOnEquivalentCurve ) const;

  
  virtual void GetApproximateEquivalentPointSingle (const CATCurve          * iCurrentCurveOrEdgeCurve,
                                        	     const CATCrvParam       & iLocationOnCurrentCurve,
                                        	     const CATCurve          * iEquivalentCurve,
                                                       const CATPositiveLength & iApproximateResolution,
                                      	               CATCrvParam             & oLocationOnEquivalentCurve ) const;



    
  //-------------------------------------------------------------------------
  // Integration native CATCGMPeriodicityInfo
  //-------------------------------------------------------------------------
  virtual CATBoolean CATCGMPeriodicityManager_GetInfo(CATCGMPeriodicityInfo & oInfo) const ;

  void DetectNullRefCurve();

  //-------------------------------------------------------------------------
  // Methods for accessing data in the Math Bloc
  //-------------------------------------------------------------------------
  unsigned short GetNbMapX() const;
  unsigned short GetNbMaxMapX() const;
  static CATLONG32 GetStaticTableSize();
  const CATMapX * const * const GetStaticTable() const;
  CATMapX** GetTabMapX(CATLONG32 *MaxMapX = NULL) const;

  // RHA le 25/10/99
protected :

  void SetRefCurve(CATCurve* iCurve, CATBoolean iForClearing = FALSE);

  void FreeTabMapX();

  virtual size_t GetDynamicMemoryBytes( ) const ;

private :
  CATCGMAttrReframeDesignLimits * ReframeDesignLimits( const double & iOldInfinite , const CATCloneManager *  iCloneManager=NULL);
  //-----------------------------------------------------------------------------
  // Internal utility.
  //-----------------------------------------------------------------------------
  const CATCurve* SearchFor( const CATSurface * iSupport, 
                             int              & ioFirstFoundIsOK, 
                             const CATCurve   * iCurrentSubElement ) const ;

  virtual CATCurve * Simplify(CATSurface * iSurface1,
                              CATSurface * iSurface2,
                              CATMapX * &oMapping) const;
  CATEdgeCurveRefCGM* GetEdgeCurveForSharpness(const CATCurve* iC1,const CATCurve* iC2)const;

  //-----------------------------------------------------------------------------
  // Mandatory methods for Child classes
  //-----------------------------------------------------------------------------
  virtual void GetEquivalentPointSingle (const CATCurve    *iCurrentCurveOrEdgeCurve,
                                         const CATCrvParam &iLocationOnCurrentCurve,
                                         const CATCurve    *iEquivalentCurve,
                                         CATCrvParam &oLocationOnEquivalentCurve,
                                         const short        iReconverge) const;
  

  virtual CATMapX* GetMapXSingle ( const CATCurve *iCurvew,	const CATCurve *iCurvefw ) const;

  void ComputeGapPointOnEdgeCurve(const CATPointOnEdgeCurve *  iPointOnEdgeCurve, double &oGap) const ; 


  static void MayChangeToEdgeCurveTol(double &ioToler);

  short IsUnextrapolIrrelevant();

  double ComputeSafeGap2();


protected :
  //-------------------------------------------------------------------------
  // Buffer refering to the curve where the methods need to be redirected.
  // This data must be maintained by child classes.
  //-------------------------------------------------------------------------
  CATCurve* const _RefCurve ;
  
  double       _DataMaxGap;
  double       _LowLimit;
  double       _HighLimit;

  //-------------------------------------------------------------------------
  // Math Bloc
  //-------------------------------------------------------------------------
  CATMapX** AllocateTabMapX( CATLONG32 NbMapX );

  unsigned short _NbMapX;
  unsigned short _nbMAXMapX;
  
  CATMapX*  _StaticArray[ StaticTabMapXSIZE ];

  CATLONG32         _BufferIndex;
  CATCurve*    _BufferCurve;

  //-----------------------------------------------------------------------
  // Detection d'equation ouvertes empechant la redefinition d'un objet
  //-----------------------------------------------------------------------
  virtual CATBoolean IsLocked(int * oLockCount = 0) ;

private :
  int         _LockCount ;
  
} ;

#endif
