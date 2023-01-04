/* -*-c++-*- */
#ifndef CATGeoFactoryCGM_H
#define CATGeoFactoryCGM_H
// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
// CATGeoFactoryCGM:
// Base class for implementations of the CATGeoFactory for creating CGM Objects
//
//=============================================================================
// Usage notes:
//
// this is an implementation of the CATGeoFactory which uses
// internal container facilities for performances reasons.
//
// Every Object able to create CXR2 geometric objects should inherit from me.
//=============================================================================
// Avril. 2000   Creation                                  T.Chailloux
// Jul. 05 Renommage de CATGeoFactoryImpl en CATGeoFactoryProtected
//       
// Oct. 09 Suppression du #ifdef CATIACGMV5R17, pour CATCldVectors, aujourd'hui 
//         cette variable vaut toujours TRUE.                                    DNR
// Nov. 14 Add the polyhedral factory in order to instanciate polyhedral bodies 
//         in the CGM Container                                                  DPS
// Dec 19  Added Deformation flags for Create(Generic)Fillet                     SMT1
//=============================================================================
#include "CATGeoFactoryProtected.h"    // For all create definition (inheritance)

#include "CATIACGMLevel.h"
#include "ExportedByCATGeometricObjectsCGM.h"
#include "CATMathDef.h"                // CATLength, CATPositiveLength
#include "CATGeoFactory.h"             // For GetDatum signature
#include "CATCGMContainer.h"           // Necessary for macros  CATMacCreate...
#include "CATListOfCATMathSetOfPointsND.h"
#include "CATListOfCATCrvParams.h"
#include "CATListOfInt.h"
#include "CATCGMDebug.h"
#include "CATParameterizationOption.h"

#include "CATCGMBOAObject.h"
#include "CATRootContainerCGM.h"
#include "CATICGMObject.h"
#include "CATIAV5Level.h"
#include "CATCGMScaleCategoryDef.h"
#include "CATTolerance.h"
#include "CATMathInline.h"
#include "CATTolerance.h"

class CATBaseUnknown;
//-----------------------------------------------------------------------------
//class CATGeometryCGM ; // a supprimer en meme temps que AddToMe
//-----------------------------------------------------------------------------
class CATGeometry ;
class CATICGMObject;
class CATCartesianPoint ;
class CATPointOnCurve ;
class CATPointOnEdgeCurve ;
class CATPointOnSurface ;
class CATMacroPoint;
class CATCloudOfPoints ;
class CATLine ;
class CATCircle ;
class CATEllipse ;
class CATBezierCurve ;
class CATParabola ;
class CATHyperbola ;
class CATNurbsCurve ;
class CATSplineCurve ;
class CATHelix ;
class CATPCurve ;
class CATEdgeCurve ;
class CATPLine ;
class CATPCircle ;
class CATPEllipse ;
class CATPParabola ;
class CATPHyperbola ;
class CATPCurveEquation ;
class CATPNurbs ;
class CATPSpline ;
class CATIntCurve;
class CATMergedCurve;
class CATSimCurve;
class CATContactCurve;
class CATProcCurve;
class CATProcCurveDef;
class CATPlane ;
class CATNurbsSurface ;
class CATRuledSurface ;
class CATGenericRuledSurface ;
class CATDirectionalSurface ;
class CATTabulatedCylinder ;
class CATRevolutionSurface ;
class CATProcOffsetSurface;
class CATOffsetSurface ;
class CATCircularSweep ;
class CATSweepSurface;
class CATFilletSurface ;
class CATDraftSurface ;
class CATDraftSurfaceCreationData;
class CATChamferSurface;
class CATSpecSurface;
class CATSpecSurfaceDef;
class CATProcSurface;
class CATProcSurfaceDef;
class CATSphere ;
class CATCylinder ;
class CATCone ;
class CATTorus ;
class CATNonLinearTransfoSurface;
class CATLinearTransfoSurface;
class CATOrientable ;
class CATConstantLaw ;
class CATLinearLaw ;
class CATSTypeLaw ;
class CATSplineLaw ;
class CATCompositeLaw;
class CATIForeignSurface;
class CATForeignSurfaceData;
class CATIForeignCurve;
class CATForeignCurveData;
class CATIForeignPCurve;
class CATForeignPCurveData;
class CATSweepSegmentSurface;
class CATSweepSegmentSurfaceCreationData;
class CATUserGeometry;
class CATBody ;

class CATCldGenEntity;
class CATCldBody;
class CATCldCloud;
class CATCldScan;
class CATCldGrid;
class CATCldPolygon;
class CATCldVectors;
class CATCldSetOfScans;
class CATCldSetOfGrids;
class CATCldScanOnPolygon;
class CATCldSetOfPointsF;
class CATCldSetOfPointsD;

class CATClay;
class CATTessClay;
class CATCloud;
class CATTessCloud;
class CATScan;
class CATTessScan;

#ifdef CATIACGMV5R15
class CATSubdivMesh;
class CATSobMesh;
#endif

#if defined CATIAV5R19 || defined CATIAR206
class CATSubdivCellSurface;
class CATSobFace;
class CATSubdivMeshGeo;
#endif

class CATMathLine ;
class CATMathPoint ;
class CATMathPlane ;
class CATMathDirection ;
class CATMathFunctionX ;
class CATMathSetOfPoints ;
class CATMathSetOfPointsND;
class CATMathSetOfPointsNDWithVectors;
class CATSurParam ;
class CATKnotVector ;
class CATCurve ;
class CATSurface ;
class CATCrvParam ;
class CATCrvLimits ;
class CATString ;
class CATGeoFactory ;

class CATCGMJournalList;
class CATGeoMeshFactory;
class CATGeoMeshFactoryCGM;
class CATGeoPolyFactory;

class CATGeoImplicitFactory;

class CATTopData;
class CATSoftwareConfiguration;
class CATCXBody;

#include "CATRootContainerCGM.h"
#include "CATMathInline.h"

#ifndef CATLocation
#define CATLocation      short
#endif

class CATCell;
class CATDomain;
class CATVolume;
class CATFace;
class CATEdge;
class CATVertex;
class CATLump;
class CATShell;
class CATWire;
class CATVertexInVolume;
class CATLoop;
class CATVertexInFace;

#include "CATCGMNewArray.h"
#include "CATCGMBOAObject.h"

class ExportedByCATGeometricObjectsCGM CATGeoFactoryCGM : public CATGeoFactoryProtected
{



public:

  

  //---------------------------------------------------------------------------
  // Object Management
  //---------------------------------------------------------------------------


  virtual ~CATGeoFactoryCGM() ;

#if defined ( CATCGMBOAObject )
#include "CATGeoFactoryCGM_CATCGMBOAObject.h"

  void InitRootContainer();
#else
  //---------------------------------------------------------------------------
  // Object Management
  //---------------------------------------------------------------------------
  CATGeoFactoryCGM( const CATCGMMode iMode = CatCGMImplicit) ;

  //---------------------------------------------------------------------------
  // Object Modeler declaration
  //---------------------------------------------------------------------------
  CATDeclareClass;

  //---------------------------------------------------------------------------
  // Surcharge new/delete ...
  //---------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;

#endif


  void Remove( CATICGMObject* iObjectToRemove, 
                       const CATICGMContainer::CATRemovingDependancies iHow= CATICGMContainer::KeepDependancies)  ;

  void Remove( CATICGMObject* iObjectToRemove, CATCGMJournalList* iInReport);

  void Remove( CATBody* iBody,   CATTopData &iTopData);

  void PropagateQuery(CATICGMUnknown *iFrom, CATCGMQueryManager &iQuery ) ;

  HRESULT ChangeComponentState(ComponentState iFromState,  ComponentState iToState,
                                                 const CATSysChangeComponentStateContext * iContext);

  //-----------------------------------------------------------------------------
  // Body creation implementation
  //-----------------------------------------------------------------------------
  CATBody * CreateBody(CATBodyMode  iMode        = CatBodyMode_Working ,
                                const char  iRole[]      = "Unknown",
                                const char *iTracability = __FILE__ ,
                                const int   iLine        = __LINE__ )  ; 

  //---------------------------------------------------------------------------
  // Pour differenciation rapide Factory V5-CGM et autre
  //---------------------------------------------------------------------------
  INLINE void *GetImplementCGM() const;
  INLINE void *IsCGMV5() const;
  INLINE int   IsSameTypeAs(CATICGMUnknown * iOtherObject)  const;
  INLINE int   IsImplementCGMRemoved(const CATGeometricType iTypeReference=CATGeometryType) const;


  //---------------------------------------------------------------------------
  //- Standard iterator
  //---------------------------------------------------------------------------
  CATGeometry* Next ( CATGeometry* iCurrent ,CATGeometricType iInType = CATGeometryType) ; 

  //---------------------------------------------------------------------------
  //- Standard Find From Tag
  //---------------------------------------------------------------------------
  CATICGMObject* FindObjectFromTag(CATULONG32  tag, CATGeometricType iType = CATGeometryType);

  //-------------------------------------------------------------------------
  // Multiple Retrieves an object from its tag 
  //-------------------------------------------------------------------------
  void FindObjectsFromTag(const CATLONG32 iNbObject, const CATULONG32  iTags[],  CATLISTP(CATICGMObject) &ioObjects );
 

  //---------------------------------------------------------------------------
  //- Tass
  //---------------------------------------------------------------------------
  void Tass();

  //---------------------------------------------------------------------------
  //- Implicit objects management
  //---------------------------------------------------------------------------
  CATGeoFactory* GetImplicitGeoFactory() const ;

  //---------------------------------------------------------------------------
  //- Explicit objects management
  //---------------------------------------------------------------------------
  CATGeoFactory* GetExplicitGeoFactory() const ;
  
  //---------------------------------------------------------------------------
  //- Implicit or Explicit objects management
  //---------------------------------------------------------------------------
  CATGeoFactory* GetGeoFactory() const ;

  //---------------------------------------------------------------------------
  // GetGeoMeshFactory
  //---------------------------------------------------------------------------
  CATGeoMeshFactory* GetGeoMeshFactory();

  //---------------------------------------------------------------------------
  // GetGeoPolyFactory
  //---------------------------------------------------------------------------
  CATGeoPolyFactory* GetGeoPolyFactory(CATBoolean iCreationMode=FALSE);

  //---------------------------------------------------------------------------
  // GetGeoImplicitFactory
  //---------------------------------------------------------------------------
  CATGeoImplicitFactory* GetGeoImplicitFactory(CATBoolean iCreationMode=FALSE);

  //-------------------------------------------------------------------------
  //- Default tolerances management
  //-------------------------------------------------------------------------
  double GetResolution(const CATResolutionType iResolutionType) const ;

  CATPositiveLength GetModelSize() const ;

  CATPositiveLength GetUnit() const ;

  CATPositiveLength GetInfinite() const ;

  void SetModelSize(const CATPositiveLength &iTolerance) ;
  void SetModelSizeAndResolution(double iModelSizeInUnit,
                            CATBoolean iKeepPreviousResolution,
                            double iResolutionC0FromModelSize);

  CATCGMTolerancesCompatibility CompareTolerances(CATGeoFactory *iOtherFactory, CATBoolean  iThrowIfComparableButNotIdentical);

  void SetUnit(const CATPositiveLength iUnitInMeter) ;

  //---------------------------------------------------------------------------
  // ScaleCategory Management
  //---------------------------------------------------------------------------
  const  CATTolerance & GetToleranceObject() const;

  CATCGMScaleCategory GetScaleCategory() const; 
  
  void SetScaleCategory(CATCGMScaleCategory iScaleCategory); 
  //-----------------------------------------------------------------------------
  // Compare objects ages
  //-----------------------------------------------------------------------------
  int GetOldestElemBasic(CATGeometry * iGeo1, CATGeometry * iGeo2);

  //-----------------------------------------------------------------------
  // List of attribute keys that are necessary within topological operators
  //-----------------------------------------------------------------------
  void AddKernelAttributeKey( int iAttributeKey, int iAttributeType );
  void RemoveKernelAttributeKey( int iAttributeKey );
  CATLONG32 GetNbKernelAttributeKeys();
  int  GetKernelAttributeKey( CATLONG32 iIndex, int & oAttributeType );

  //-------------------------------------------------------------------------
  //- Geometric Datum access
  //-------------------------------------------------------------------------
  const CATGeometry* GetDatum ( const CATGeoFactory::CATDatumId Id ) const ;

  //---------------------------------------------------------------------------
  // Interface access
  //---------------------------------------------------------------------------
  CATICGMUnknown* GetInterface() const ;

  //---------------------------------------------------------------------------
  //- Cartesian point basic creation
  //---------------------------------------------------------------------------
  CATCartesianPoint * CreateCartesianPointBasic ( const CATLength x, 
						  const CATLength y,
						  const CATLength z) ;
  
  //---------------------------------------------------------------------------
  //- Point on curve basic creation
  //---------------------------------------------------------------------------
  CATPointOnCurve* CreatePointOnCurveBasic ( const CATCrvParam &, CATCurve * );

  //---------------------------------------------------------------------------
  //- Point on EdgeCurve basic creation
  //---------------------------------------------------------------------------
  CATPointOnEdgeCurve* CreatePointOnEdgeCurveBasic( const CATLONG32 iSpecCount, 
						    const CATCurve* iSpecCurves[],
						    const CATCrvParam iSpecParams[],
						    const CATEdgeCurve* iSupport   ) ;

  //---------------------------------------------------------------------------
  //- Point on surface basic creation
  //---------------------------------------------------------------------------
  CATPointOnSurface* CreatePointOnSurfaceBasic (const CATSurParam &, CATSurface *);

  //-------------------------------------------------------------------------
  //- MacroPoint basic creation
  //-------------------------------------------------------------------------
  CATMacroPoint * CreateMacroPointBasic () ;

  //---------------------------------------------------------------------------
  //- Line basic creation
  //---------------------------------------------------------------------------
  CATLine* CreateLineBasic (const CATMathPoint &iP, const CATMathDirection &iD);
  
  //-----------------------------------------------------------------------------
  //- Trimmed Line basic creation implementation
  //-----------------------------------------------------------------------------
  CATLine* CreateLineBasic (const CATMathPoint &iP1, const CATMathPoint &iP2 );

  //---------------------------------------------------------------------------
  //- Circle basic creation
  //---------------------------------------------------------------------------
  CATCircle* CreateCircleBasic (const CATPositiveLength  iRadius, 
				const CATMathPlane      &iSupport,
				const CATAngle           iFrom,
				const CATAngle           iTo           );

  //---------------------------------------------------------------------------
  //- Ellipse basic creation
  //---------------------------------------------------------------------------
  CATEllipse* CreateEllipseBasic (const CATPositiveLength  iMajorAxis,
				  const CATPositiveLength  iMinorAxis,
				  const CATMathPlane      &iBackgroundPlane, 
				  const CATAngle           iFrom,
				  const CATAngle           iTo        );
  
  //-------------------------------------------------------------------------
  //- Parabola creation
  //-------------------------------------------------------------------------
  CATParabola * CreateParabolaBasic (const CATLength &iFocalDistance,
				     const CATMathPlane &iBackgroundPlane);

  //-------------------------------------------------------------------------
  //- Hyperbola creation
  //-------------------------------------------------------------------------
  CATHyperbola * CreateHyperbolaBasic (const CATPositiveLength &majaxis,
				       const CATPositiveLength &minaxis,
				       const CATMathPlane &axis2m) ;

  //---------------------------------------------------------------------------
  //- Bezier curve basic creation
  //---------------------------------------------------------------------------
  CATBezierCurve *CreateBezierCurveBasic(const int &iNbrCtrlPts, 
					 const int &iNbrOfArc,
					 const int *iDegrees,
					 const CATMathPoint *MathCtrlPts);
  
  
  //---------------------------------------------------------------------------
  //- Basic NURBS curve creation
  //---------------------------------------------------------------------------
  CATNurbsCurve* CreateNurbsCurveBasic(const CATKnotVector &iKnotVector, 
				       const CATLONG32 &iIsRational, 
				       const CATMathSetOfPoints &iVertices,
				       const double * iWeight,
                                       const CATParameterizationOption iParameterizationOption=CatAutomaticParameterization  ,
                                       int iCheckLevel=0);


  //-----------------------------------------------------------------------------
  //- Basic Spline curve creation
  //-----------------------------------------------------------------------------
  CATSplineCurve * CreateSplineCurveBasic(const CATMathSetOfPointsNDWithVectors * iPoints,
					  const double * iParameters);

  CATSplineCurve * CreateSplineCurveBasic(const CATMathSetOfPointsND * iParams,
					  const CATMathSetOfPointsND * iPoints,
					  const CATMathSetOfPointsND * iTangents,
					  const CATMathSetOfPointsND * iSecondDerivatives,
					  const CATLONG32 iFirstCoordIndex,
					  const CATLONG32 iSecondCoordIndex,
					  const CATLONG32 iThirdCoordIndex);

  //---------------------------------------------------------------------------
  //- Helix creation
  //---------------------------------------------------------------------------
  CATHelix * CreateHelixBasic( const CATMathLine      &iAxis,
                               const CATMathPoint     &iStartingPoint,
  	                           const CATAngle          iStart,
	                           const CATAngle          iEnd,
                               const double            iPitch,
                               const CATLONG32              iTrigonometricOrientation,
                               double                  iRadiusEvolution = 0.);

  //-------------------------------------------------------------------------
  // ForeignCurve creation 
  //-------------------------------------------------------------------------
  CATIForeignCurve * CreateForeignCurveBasic(CATForeignCurveData* iForeignCurveData) ;

  CATTrimmedPCurve* CreateTrimmedPCurveBasic(CATSurface * iSupport, CATPCurve * iReference, const CATCrvLimits & iLimits);

  //--------------------------------------------------------------------------
  //- PLine basic creation implementation
  //--------------------------------------------------------------------------
  CATPLine* CreatePLineBasic(CATSurface  *iSupport, 
			     const CATSurParam &iStart, 
			     const CATSurParam &iEnd ) ;

  //-----------------------------------------------------------------------------
  //- PCircle basic creation implementation
  //-----------------------------------------------------------------------------
  CATPCircle* CreatePCircleBasic( const double       iRadius,
				  const CATSurParam &iCenter,
				  const CATAngle     iStart,
				  const CATAngle     iEnd,
				        CATSurface  *iSupport ) ;

  //-----------------------------------------------------------------------------
  //- PEllipse basic creation implementation
  //-----------------------------------------------------------------------------
  CATPEllipse* CreatePEllipseBasic( const double      &iMajorAxis,
				    const double      &iMinorAxis,
				    const double      &iOffsetAngle,
				    const CATSurParam &iCenter,
				    const CATAngle     iStart,
				    const CATAngle     iEnd,
				          CATSurface  *iSupport ) ;

  //-----------------------------------------------------------------------------
  //- PParabola basic creation implementation
  //-----------------------------------------------------------------------------
  CATPParabola * CreatePParabolaBasic(const CATMathAxis2D & iAxis,
                                      const double ip,
                                      const double * Limits,
                                      CATSurface        *iSupport );

  
  //-----------------------------------------------------------------------------
  //- PHyperbola basic creation implementation
  //-----------------------------------------------------------------------------

  CATPHyperbola * CreatePHyperbolaBasic(const CATMathAxis2D & iAxis,
                                        const double iA,
                                        const double iB,
                                        const double * Limits,
                                        CATSurface        *iSupport );



  //-----------------------------------------------------------------------------
  //- PCurveEquation basic creation implementation
  //-----------------------------------------------------------------------------
  CATPCurveEquation* CreatePCurveEquationBasic(const CATMathFunctionX* iFx      ,
					       const CATMathFunctionX* iFy      ,
					       const double            iStart   ,
					       const double            iEnd     ,
					       const double            iMaxStart,
					       const double            iMaxEnd  ,
					             CATSurface*       iSupport );

  //-----------------------------------------------------------------------------
  //- PNurbs basic creation implementation
  //-----------------------------------------------------------------------------
  CATPNurbs* CreatePNurbsBasic(CATKnotVector &iKnotVector,
			       const CATLONG32 &iIsRational,
			       const double * iVertices,
			       const double * iWeights,
			       CATSurface        *iSupport,
			       const CATParameterizationOption iParameterizationOption=CatAutomaticParameterization,
                               int iCheckLevel=0 ) ;

  //-----------------------------------------------------------------------------
  //- PSpline basic creation implementation
  //-----------------------------------------------------------------------------
  CATPSpline * CreatePSplineBasic(const CATMathSetOfPointsNDWithVectors * iPoints,
				  const double * iParameters,
				  CATSurface * iSupport);

  CATPSpline * CreatePSplineBasic(const CATMathSetOfPointsND * iParams,
				  const CATMathSetOfPointsND * iPoints,
				  const CATMathSetOfPointsND * iTangents,
				  const CATMathSetOfPointsND * iSecondDerivatives,
				  const CATLONG32 iFirstCoordIndex,
				  const CATLONG32 iSecondCoordIndex,
				  CATSurface * iSupport );

  //-------------------------------------------------------------------------
  // ForeignPCurve creation 
  //-------------------------------------------------------------------------
  CATIForeignPCurve * CreateForeignPCurveBasic(CATForeignPCurveData* iForeignPCurveData, 
                                               CATSurface* iSurface) ;

  //-------------------------------------------------------------------------
  //- IntCurve creation
  //-------------------------------------------------------------------------
  CATIntCurve * CreateIntCurveBasic (CATPCurve* iC1, CATPCurve* iC2) ;
  CATIntCurve * CreateIntCurveBasic (const CATLONG32              iNbMapX,
                                     const CATMapX**         iMapX,
                                     const CATPositiveLength iGap);

  //-------------------------------------------------------------------------
  //- SimCurve creation
  //-------------------------------------------------------------------------
  CATSimCurve * CreateSimCurveBasic ( CATLISTP(CATCurve) & iNewCurves,
                                      CATLISTP(CATCrvLimits) & iLimits,
                                      CATListOfInt           & iOrns,
				                      const CATPositiveLength    iGap       ) ;
  CATSimCurve * CreateSimCurveBasic (const CATLONG32              iNbMapX,
                                     const CATMapX**         iMapX,
                                     const CATPositiveLength iGap);


  //-------------------------------------------------------------------------
  //- MergedCurve creation
  //-------------------------------------------------------------------------
  CATMergedCurve * CreateMergedCurveBasic ( const CATCurve* iC1,
					    const CATCrvLimits & iLim1, 
					    const CATCurve* iC2,
					    const CATCrvLimits & iLim2 ) ; 

  CATMergedCurve * CreateMergedCurveBasic ( const CATCurve* iC1,
					    const CATCrvLimits & iLim1,
					    const CATCurve* iC2,
					    const CATCrvLimits & iLim2,
					    const CATMathSetOfPointsND & iParamMapping,
                                            const CATPositiveLength      iMaxGap       ) ; 
  CATMergedCurve * CreateMergedCurveBasic (const CATLONG32              iNbMapX,
                                           const CATMapX**         iMapX,
                                           const CATPositiveLength iGap);

  //-------------------------------------------------------------------------
  //- ContactCurve creation
  //-------------------------------------------------------------------------
  CATContactCurve * CreateContactCurveBasic (CATEdgeCurve* iEdgeCurve,
					     CATSurface*   iSurface  );
    
   //-------------------------------------------------------------------------
  //- ProcCurve creation
  //-------------------------------------------------------------------------
  CATProcCurve * CreateProcCurveBasic (CATProcCurveDef* iProcCurveDef );
					     
  //---------------------------------------------------------------------------
  //- Plane basic creation
  //---------------------------------------------------------------------------
  CATPlane* CreatePlaneBasic (const CATMathPlane &);

  //---------------------------------------------------------------------------
  // Sphere Creation
  //---------------------------------------------------------------------------
  CATSphere * CreateSphereBasic(const CATMathAxis       &iAxis, 
				const CATPositiveLength  iRadius,
				const CATAngle           iMeridianStart,
				const CATAngle           iMeridianEnd,
				const CATAngle           iParallelStart,
				const CATAngle           iParallelEnd    ) ;
  
  //---------------------------------------------------------------------------
  // Cylinder Creation
  //---------------------------------------------------------------------------
  CATCylinder * CreateCylinderBasic(const CATMathAxis &iAxis,
				    const CATLength   &iRadius,
				    const CATLength   &iAxisStart,
				    const CATLength   &iAxisEnd,
				    const CATAngle    &iAngleStart,
				    const CATAngle    &iAngleEnd) ;
  //---------------------------------------------------------------------------
  // Cone Creation
  //---------------------------------------------------------------------------
  CATCone * CreateConeBasic(const CATMathAxis &iConeAxis,
                     const CATLength   iStartRadius,
                     const CATAngle    iConeAngle,
                     const CATAngle    iStartAngle,
                     const CATAngle    iEndAngle,
                     const CATLength   iStartRuleLength,
		     const CATLength   iEndRuleLength);

//  CATCone * CreateCone(const CATMathAxis &iAxis,
//		       const CATLength   iRadius1,
//		       const CATLength   iRadius2,
//		       const CATLength   iHeight) ;

  //---------------------------------------------------------------------------
  // Torus Creation
  //---------------------------------------------------------------------------
  CATTorus * CreateTorusBasic(const CATMathAxis &iTorusAxis,
			      const CATLength   iMajorRadius,
			      const CATAngle    iMajorStartAngle,
			      const CATAngle    iMajorEndAngle,
			      const CATLength   iMinorRadius,
			      const CATAngle    iMinorStartAngle,
			      const CATAngle    iMinorEndAngle);

  //-----------------------------------------------------------------------------
  // TabulatedCylinder creation 
  //-----------------------------------------------------------------------------
  CATTabulatedCylinder * CreateTabulatedCylinderBasic(CATCurve* Profile,
                                                      const CATCrvLimits & iProfileLimits,
						                              const CATMathDirection &iDirection,
						                              const CATLength &iStart,
						                              const CATLength &iEnd          ) ;
  
  //-------------------------------------------------------------------------
  // RevolutionSurface creation
  //-------------------------------------------------------------------------
  CATRevolutionSurface * CreateRevolutionSurfaceBasic(CATCurve* iProfile,
                                                      const CATCrvLimits & iProfileLimits,
						                              const CATMathAxis &iRefAxis,
						                              const CATAngle &iStart,
						                              const CATAngle &iEnd            )  ;

	//-----------------------------------------------------------------------------
  //- ProcOffsetSurface basic creation implementation
  //-----------------------------------------------------------------------------
  CATProcOffsetSurface * CreateProcOffsetSurfaceBasic(const CATLength   iOffset,
					            CATSurface *iReference,
											const CATSurLimits &iLimits) ;

  //-----------------------------------------------------------------------------
  //- OffsetSurface basic creation implementation
  //-----------------------------------------------------------------------------
  CATOffsetSurface * CreateOffsetSurfaceBasic(const CATLength   iOffset,
					            CATSurface *iReference,
											const CATSurLimits &iLimits) ;


  CATOffsetSurface * CreateOffsetSurfaceBasic(const CATLength   iOffset,
														                  CATSurface *iReference,
														                  CATSurface *iGeometricRep  );
  //-----------------------------------------------------------------------------
  //  CircularSweep basic creation 
  //-----------------------------------------------------------------------------
  CATCircularSweep * CreateCircularSweepBasic(
		            const CATMathSetOfPointsNDWithVectors *iPoints,
					      const double *iParameters);

  //-----------------------------------------------------------------------------
  //  GenericFillet basic creation 
  //-----------------------------------------------------------------------------
  CATGenericFillet * CreateGenericFilletBasic(const CATMathSetOfPointsND * iParams,
					      const CATMathSetOfPointsND * iPoints,
					      const CATMathSetOfPointsND * iTangents,
					      const CATMathSetOfPointsND * iSecondDerivatives,
					      const CATLONG32 iFirstTraceIndex,
					      const CATLONG32 iSecondTraceIndex,
					      const CATLONG32 iCenterCurveIndex,
					      const CATLONG32 iAngleIndex,
                          const CATMathBox2D * iBox = NULL,
                          CATBoolean      iDeformedStart  = FALSE,
                          CATBoolean      iDeformedEnd    = FALSE);

  //-----------------------------------------------------------------------------
  //- SweepSurface basic creation 
  //-----------------------------------------------------------------------------
  CATSweepSurface* CreateSweepSurfaceBasic( CATNurbsSurface* iNurbsSurface );

  //-----------------------------------------------------------------------------
  //- SweepSegmentSurface basic creation 
  //-----------------------------------------------------------------------------
  CATSweepSegmentSurface * CreateSweepSegmentSurfaceBasic
     ( const CATSweepSegmentSurfaceCreationData* iSweepSegmentSurfaceCreationData );  

  //-----------------------------------------------------------------------------
  //- NurbsSurface basic creation implementation
  //-----------------------------------------------------------------------------
  CATNurbsSurface* CreateNurbsSurfaceBasic( const CATKnotVector &iKnotVectorU, 
					   const CATKnotVector &iKnotVectorV,
					   const CATLONG32 &iIsRational, 
					   const CATMathGridOfPoints &iVertices,
					   const double * iWeights,
					   const CATParameterizationOption iParameterizationOption=CatAutomaticParameterization,
                                           int iCheckLevel=0) ;

  //-----------------------------------------------------------------------------
  //- RuledSurface basic creation implementation
  //-----------------------------------------------------------------------------
  CATRuledSurface* CreateRuledSurfaceBasic(
				const CATCurve * profile,
				const CATMathDirection & direction,
				const CATAngle & angle,
				const double & length1,
				const double & length2,
				const CATCrvLimits * limits=0,
				const CATLISTP(CATCrvParam) * params=0);

  CATRuledSurface* CreateRuledSurfaceBasic(const CATCurve * profile1,
					   const double & length1,
					   const double & limit1,
					   const CATCurve * profile2,
					   const double & length2,
					   const double & limit2);

  //-----------------------------------------------------------------------------
  //- GenericRuledSurface basic creation implementation
  //-----------------------------------------------------------------------------
  CATGenericRuledSurface* CreateGenericRuledSurfaceBasic(const CATMathSetOfPointsND * iParams,
						 const CATMathSetOfPointsND * iPoints,
						 const CATMathSetOfPointsND * iTangents,
						 const CATMathSetOfPointsND * iSecondDerivatives,
						 const CATLONG32 iFirstTraceIndex,
						 const CATLONG32 iSecondTraceIndex);

  //-----------------------------------------------------------------------------
  // FilletSurface basic creation
  //-----------------------------------------------------------------------------

  CATFilletSurface * CreateFilletSurfaceBasic(const CATMathSetOfPointsND * iParams,
    const CATMathSetOfPointsND * iPoints,
    const CATMathSetOfPointsND * iTangents,
    const CATMathSetOfPointsND * iSecondDerivatives,
    const CATLONG32                   iFirstTraceIndex,
    const CATLONG32                   iSecondTraceIndex,
    const CATLONG32                   iCenterCurveIndex,
    const CATLONG32                   iAngleIndex,
    const short                  iConfiguration,
    double                       iRadius,
    CATGeometry*                 iSupport1,
    CATGeometry*                 iSupport2,
    int                          iOrientation1,
    int                          iOrientation2,
    CATGeometry*                 iContact1,
    CATGeometry*                 iContact2,
    CATLONG32 &                       CentripetalOrientation,
    CATBoolean                  iDeformedStart  = FALSE,
    CATBoolean                  iDeformedEnd    = FALSE);
  
  CATFilletSurface * CreateFilletSurfaceBasic(const CATMathSetOfPointsND * iParams,
    const CATMathSetOfPointsND * iPoints,
    const CATMathSetOfPointsND * iTangents,
    const CATMathSetOfPointsND * iSecondDerivatives,
    const CATLONG32                   iFirstTraceIndex,
    const CATLONG32                   iSecondTraceIndex,
    const CATLONG32                   iCenterCurveIndex,
    const CATLONG32                   iAngleIndex,
    const short                  iConfiguration,
    CATCurve *                   iSpine,
    CATLaw   *                   iRadiusLaw,
    CATLaw   *                   iMappingLaw,
    CATGeometry*                 iSupport1,
    CATGeometry*                 iSupport2,
    int                          iOrientation1,
    int                          iOrientation2,
    CATGeometry*                 iContact1,
    CATGeometry*                 iContact2,
    CATLONG32 &                       CentripetalOrientation,
    const CATLONG32              iContinuityMode = 0);
  
  CATFilletSurface * CreateTriTangentFilletSurfaceBasic(const CATMathSetOfPointsND * iParams,
    const CATMathSetOfPointsND * iPoints,
    const CATMathSetOfPointsND * iTangents,
    const CATMathSetOfPointsND * iSecondDerivatives,
    const CATLONG32                   iFirstTraceIndex,
    const CATLONG32                   iSecondTraceIndex,
    const CATLONG32                   iCenterCurveIndex,
    const CATLONG32                   iAngleIndex,
    const short                  iConfiguration,
    CATGeometry*                 iSupport1,
    CATGeometry*                 iSupport2,
    CATGeometry*                 iSupport3,
    int                          iOrientation1,
    int                          iOrientation2,
    int                          iOrientation3,
    CATGeometry*                 iContact1,
    CATGeometry*                 iContact2,
    CATGeometry*                 iContact3,
    CATLONG32 &                       CentripetalOrientation);
 
  CATFilletSurface * CreateBiTangentCircleFilletSurfaceBasic(
    const CATMathSetOfPointsND * iParams,
    const CATMathSetOfPointsND * iPoints,
    const CATMathSetOfPointsND * iTangents,
    const CATMathSetOfPointsND * iSecondDerivatives,
    const CATLONG32                   iFirstTraceIndex,
    const CATLONG32                   iSecondTraceIndex,
    const CATLONG32                   iCenterCurveIndex,
    const CATLONG32                   iAngleIndex,
    const short                  iConfiguration,
    CATCurve *                   iCircleSpine,
    CATCurve *                   iRadiusSpine,
    CATLaw   *                   iRadiusLaw,
    CATLaw   *                   iMappingLaw,
    CATGeometry*                 iSupport1,
    CATGeometry*                 iSupport2,
    int                          iOrientation1,
    int                          iOrientation2,
    CATGeometry*                 iContact1,
    CATGeometry*                 iContact2,
    CATLONG32 &                       oCentripetalOrientation);

  #ifdef CATIACGMV5R18 
  CATFilletSurface* CreateChordalFilletSurfaceBasic( const CATMathSetOfPointsND* iParams,
                                                     const CATMathSetOfPointsND* iPoints,
                                                     const CATMathSetOfPointsND* iTangents,
                                                     const CATMathSetOfPointsND* iSecondDerivatives,
                                                     const CATLONG32             iFirstTraceIndex,
                                                     const CATLONG32             iSecondTraceIndex,
                                                     const CATLONG32             iCenterCurveIndex,
                                                     const CATLONG32             iAngleIndex,
                                                     const short                 iConfiguration,	    
                                                     double                      iChord,
                                                     CATGeometry*                iSupport1,
                                                     CATGeometry*                iSupport2,
                                                     int                         iOrientation1,
                                                     int                         iOrientation2,
                                                     CATGeometry*                iContact1,
                                                     CATGeometry*                iContact2,
                                                     CATLONG32&                  oCentripetalOrientation);
  
  CATFilletSurface* CreateChordalFilletSurfaceBasic( const CATMathSetOfPointsND* iParams,
                                                     const CATMathSetOfPointsND* iPoints,
                                                     const CATMathSetOfPointsND* iTangents,
                                                     const CATMathSetOfPointsND* iSecondDerivatives,
                                                     const CATLONG32             iFirstTraceIndex,
                                                     const CATLONG32             iSecondTraceIndex,
                                                     const CATLONG32             iCenterCurveIndex,
                                                     const CATLONG32             iAngleIndex,
                                                     const short                 iConfiguration,
                                                     CATCurve*                   iSpine,
                                                     CATLaw*                     iChordLaw,
                                                     CATLaw*                     iMappingLaw,
                                                     CATGeometry*                iSupport1,
                                                     CATGeometry*                iSupport2,
                                                     int                         iOrientation1,
                                                     int                         iOrientation2,
                                                     CATGeometry*                iContact1,
                                                     CATGeometry*                iContact2,
                                                     CATLONG32&                  oCentripetalOrientation,
                                                     const CATLONG32             iContinuityMode = 0);

#endif

  CATFilletSurface * CreateSweepCircleSurfaceBasic(const CATMathSetOfPointsND * iParams,
    const CATMathSetOfPointsND * iPoints,
    const CATMathSetOfPointsND * iTangents,
    const CATMathSetOfPointsND * iSecondDerivatives,
    const CATLONG32                   iFirstTraceIndex,
    const CATLONG32                   iSecondTraceIndex,
    const CATLONG32                   iCenterCurveIndex,
    const CATLONG32                   iAngleIndex,
    const short                  iConfiguration,
    double                       iRadius,
    CATCurve *                   iCircleSpine,
    CATGeometry*                 iSupport1,
    CATGeometry*                 iSupport2,
    int                          iOrientation1,
    int                          iOrientation2,
    CATGeometry*                 iContact1,
    CATGeometry*                 iContact2,
    CATLONG32 &                       oCentripetalOrientation);


  //-----------------------------------------------------------------------------
  // DraftSurface basic creation
  //-----------------------------------------------------------------------------
  CATDraftSurface * CreateDraftSurfaceBasic(
			const CATCurve * profile,
			const CATMathDirection & direction,
			const CATAngle & angle,
			const double & length1,
			const double & length2,
      CATMathSetOfPointsND & ioMapping,
			const CATCrvLimits * limits=0,
			const CATLISTP(CATCrvParam) * params=0);

/**
 * DraftSurface creation.
 */
  CATDraftSurface * CreateDraftSurfaceBasic(CATDraftSurfaceCreationData * ioData);

  CATDraftSurface * CreateDraftSurfaceBasic(const CATSurface * ToCopy);
  //-----------------------------------------------------------------------------
  //  DirectionalSurface basic creation
  //-----------------------------------------------------------------------------
  CATDirectionalSurface* CreateDirectionalSurfaceBasic(
								   CATPCurve * iGuideCurve,
								   CATCrvLimits * iLimits,
								   CATAngle iAngleWithNormal,
								   CATLength iLengthRuled,
								   CATMathSetOfPointsND &ioMapping);

  //-----------------------------------------------------------------------------
  // ChamferSurface basic creation
  //-----------------------------------------------------------------------------
  CATChamferSurface * CreateChamferSurfaceBasic(const CATMathSetOfPointsND * iParams,
					      const CATMathSetOfPointsND * iPoints,
					      const CATMathSetOfPointsND * iTangents,
					      const CATMathSetOfPointsND * iSecondDerivatives,
					      const CATLONG32 iFirstTraceIndex,
					      const CATLONG32 iSecondTraceIndex,
                const short iConfiguration,
// Modif alm 02/10 : suppression de la spine, le chamfer type est defini dans
// GeometricObjects/PublicInterfaces/CATConnectDefines.h
//		  CATCurve * iSpine,
	        const CATLONG32 iChamferType,
	        const double iFirstValue,
	        const double iSecondValue,
                CATSurface* iSurface1,
                CATSurface* iSurface2,
                int iOrientation1,
                int iOrientation2,
                CATGeometry* iContact1,
                CATGeometry* iContact2);

  //-----------------------------------------------------------------------------
  // LinearSurface basic creation
  //-----------------------------------------------------------------------------
  CATLinearTransfoSurface * CreateLinearTransfoSurfaceBasic(CATMathTransformation & iTransformation,
                                                            CATSurface            * iReference );

  //-----------------------------------------------------------------------------
  // NonLinearSurface basic creation
  //-----------------------------------------------------------------------------
  CATNonLinearTransfoSurface * CreateNonLinearTransfoSurfaceBasic
                               (CATMathNonLinearTransformation & iTransformation,
                                CATSurface                     * iReference );
  //-----------------------------------------------------------------------------
  // NonLinearSurface basic creation
  //-----------------------------------------------------------------------------
  CATNonLinearTransfoSurface * CreateNonLinearTransfoSurfaceBasic
                               (CATMathNonLinearTransformation & iTransformation,
                                CATSurface    * iReference ,
                                CATSurLimits  & iSurMaxLimits);
  //-------------------------------------------------------------------------
  //- Non Linear Transformed PCurves
  //-------------------------------------------------------------------------
  CATNonLinearTransfoPCurve * CreateNonLinearTransfoPCurveBasic
  (CATPCurve * iFromPCrv,
   const double iuShift, const double ivShift,
   CATMathNonLinearTransformation2D * ioTransfo,
   CATSurface * iSupport);

  //-------------------------------------------------------------------------
  // ForeignSurface creation
  //-------------------------------------------------------------------------
  CATIForeignSurface * CreateForeignSurfaceBasic(CATForeignSurfaceData* iForeignSurfaceData) ;
  

    //-------------------------------------------------------------------------
  //- SpecSurface creation
  //-------------------------------------------------------------------------
  CATSpecSurface * CreateSpecSurfaceBasic (CATSpecSurfaceDef* iSpecSurfaceDef );

  
  //-------------------------------------------------------------------------
  //- ProcSurface creation
  //-------------------------------------------------------------------------
  CATProcSurface * CreateProcSurfaceBasic (CATProcSurfaceDef* iProcSurfaceDef );

  //---------------------------------------------------------------------------
  // Orientable creation
  //---------------------------------------------------------------------------
  CATOrientable* CreateOrientableBasic(CATGeometry *iGeometry,
						const CATLONG32 iOrientable);

  //---------------------------------------------------------------------------
  //- Constant Law basic creation implementation
  //---------------------------------------------------------------------------
  CATConstantLaw* CreateConstantLawBasic (const double iTMin,
					  const double iTMax,
					  const double iValue);

  //---------------------------------------------------------------------------
  //- Linear Law basic creation implementation
  //---------------------------------------------------------------------------
  CATLinearLaw* CreateLinearLawBasic(const double iTMin,
				     const double iValueAtTMin,
				     const double iTMax,
				     const double iValueAtTMax);

  //---------------------------------------------------------------------------
  //- SType Law basic creation implementation
  //---------------------------------------------------------------------------
  CATSTypeLaw* CreateSTypeLawBasic(const double iTMin,
				   const double iValueAtTMin,
				   const CATLONG32   iOrderAtTMin,
				   const double iTMax,
				   const double iValueAtTMax,
				   const CATLONG32   iOrderAtTMax);

  //---------------------------------------------------------------------------
  //- Spline Law basic creation implementation
  //---------------------------------------------------------------------------
  CATSplineLaw* CreateSplineLawBasic(const CATLONG32 iNbrOfConstraint,
				     const double *iT,
				     const double *iValue);

  //---------------------------------------------------------------------------
  //- Composite Law basic creation implementation
  //---------------------------------------------------------------------------
  CATCompositeLaw* CreateCompositeLawBasic(const CATLONG32 iNbrOfFunctions,
					   const double * iBorders,
					   const CATMathFunctionX ** iFunctions) ;

  CATCompositeLaw* CreateC2ExtrapolationCompositeLawBasic
    (const CATLaw *iToExtrapolate, const double iMinLimiteValue, const double iMaxLimiteValue,const CATLONG32 iSide=0);

  //---------------------------------------------------------------------------
  //  Scale option management for laws
  //---------------------------------------------------------------------------
  void       SetScaleOptionBasic (CATLaw* iLaw, CATLONG32 iPowerScaleF, CATLONG32 iPowerScaleX, CATLONG32 iReviewed=0);
  // returns 0 if not previously set
  CATLONG32  GetScaleOptionBasic (CATLaw* iLaw,
                                  CATLONG32& oPowerScaleF, CATLONG32& oPowerScaleX, CATLONG32& oReviewed);

  //---------------------------------------------------------------------------
  //  Surcharge de methode  de CATBaseUnknown pour PERFOS (FW System)
  //---------------------------------------------------------------------------
  virtual CATBaseUnknown * __stdcall GetImpl(int iFlag = 0) const;
  virtual ULONG            __stdcall AddRef();
  virtual ULONG            __stdcall Release();  
  virtual HRESULT          __stdcall QueryInterface(const IID &iid,void **ppv);
  virtual CATBaseUnknown *           QueryInterface(CATClassId iInterface) const;
 

  //---------------------------------------------------------------------------
  //- Standard Remove
  //---------------------------------------------------------------------------
protected :
  void CommonRemove ( CATICGMObject *iObject, 
                      const CATICGMContainer::CATRemovingDependancies how,
                      CATCGMJournalList* iInReport,  
                      CATSoftwareConfiguration* iConfig=NULL) ; 


  //---------------------------------------------------------------------------
  // Pour le Model Topologique dynamique
  // Pont GeometricObjectsCGM-NewTopologicalObjects
  //---------------------------------------------------------------------------
  friend class CATCGMTopoCXMODEL;
  friend class CATCXBody;
  friend class CATDeclarativeManifoldCGM;
  friend class CATGeoMeshFactoryCGM;

  //---------------------------------------------------------------------------
  // Data
  //---------------------------------------------------------------------------

protected:
  CATGeoMeshFactory * _GeoMeshFactory;
  CATGeoPolyFactory * _GeoPolyFactory;
  CATGeoImplicitFactory * _GeoImplicitFactory; 
};


//_________________________________________________
#if defined ( CATCGMBOAObject ) 

#ifndef _TIECGMCATGeoFactory_H
#define _TIECGMCATGeoFactory_H

#include "CATMacBuildCGM.h"
#include "TIE_CATGeoFactory.h"
TIE_CGM_DECLARE(CATGeoFactory,CATGeoFactoryCGM);

#endif

#endif

//_________________________________________________
INLINE  void *CATGeoFactoryCGM::GetImplementCGM() const
{
#if defined ( CATCGMBOAObject )
  return  (void *) & _MyRoot;
#else
  if ( _Root == NULL )
  {
    ((CATGeoFactoryCGM*)this)->InitRootContainer();
    if ( _Root == NULL )
      return NULL;
  }
  return ( _CreateExplicit ? (void *) _Root->GetExplicitContainer() : (void *) _Root->GetImplicitContainer() );
#endif
}
//_________________________________________________
INLINE  void *CATGeoFactoryCGM::IsCGMV5() const
{
#if defined ( CATCGMBOAObject )
  return  (void *) & _MyRoot;
#else
  if ( NULL == _Root )
  {
    ((CATGeoFactoryCGM*)this)->InitRootContainer();
    if ( NULL == _Root )
      return NULL;
  }
  return ( _CreateExplicit ? (void *) _Root->GetExplicitContainer() : (void *) _Root->GetImplicitContainer() );
#endif
}
//_________________________________________________
INLINE int CATGeoFactoryCGM::IsSameTypeAs(CATICGMUnknown * iOtherObject)  const 
{
#if defined ( CATCGMBOAObject )
  return _MyRoot.IsSameTypeAs(iOtherObject);
#else
  if ( NULL == _Root )
  {
    ((CATGeoFactoryCGM*)this)->InitRootContainer();
    if ( NULL == _Root )
      return 0;
  }
  return _Root->IsSameTypeAs(iOtherObject);
#endif
}
//_________________________________________________
INLINE  int CATGeoFactoryCGM::IsImplementCGMRemoved(const CATGeometricType iTypeReference) const
{
#if defined ( CATCGMBOAObject )
  return _MyRoot.IsImplementCGMRemoved(iTypeReference);
#else
  if ( NULL == _Root )
    return 1;

  return _Root->IsImplementCGMRemoved(iTypeReference);
#endif
}
//_________________________________________________

INLINE  CATGeoFactory* CATGeoFactoryCGM::GetGeoFactory() const 
{ 
  return ( _CreateExplicit ? GetExplicitGeoFactory() : GetImplicitGeoFactory() );
}

//_________________________________________________


#endif
