//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATParallelConnectTool:
//
//=============================================================================
// Usage notes:
//   /11/2004  EAB  Versionning interne
// 23/10/2014  Q48  Implement X-scale in CGM-replay
//  Mars 2016 JSX : Tool with CATsoftwareconfiguration
// 16/07/20 S9l Streaming origin support information in Parallel Connect Tool
// 22/04/2021 SME31 Implement GetCutterDimension()
//=============================================================================
#ifndef CATParallelConnectTool_h
#define CATParallelConnectTool_h

#include "Connect.h"
#include "CATConnectTool.h"
#include "CATListOfCATGeometries.h"
#include "CATApproxDiagnosticType.h"

#include "CATBoolean.h"

#include "CATCGMStream.h"
#include "CATString.h"
#include "CATIACGMLevel.h"

class CATMathSetOfPointsND;
class CATMathFunctionX;
class CATMathPiecewiseX;
class CATMathInterval;
class CATGeoFactory;
class CATGeometry;
class CATCurve;
class CATSurface;
class CATCrvLimits;
class CATSurLimits;
class CATLaw;
class CATTolerance;

class CATDistanceTool;
class CATICGMDistanceTool;
class CATParallelComputer;
class CATSoftwareConfiguration;

class ExportedByConnect CATParallelConnectTool : public CATConnectTool
   {
   CATCGMVirtualDeclareClass(CATParallelConnectTool);

   public:

      //=====================
      // Object Management
      //=====================
      CATParallelConnectTool(CATSoftwareConfiguration * iConfig,     CATDistanceTool *iDistanceTool,
                             CATLaw *iMappingLaw, CATBoolean iIsPlanarBody = FALSE); // iMappingLaw = 0 possible si loi constante

      CATParallelConnectTool(CATSoftwareConfiguration * iConfig, CATICGMDistanceTool *iDistanceTool,
                             CATLaw *iMappingLaw, CATBoolean iIsPlanarBody = FALSE); // iMappingLaw = 0 possible si loi constante

      // **** for intern use only ****
      CATParallelConnectTool(CATSoftwareConfiguration * iConfig, CATLONG32 iSide, CATLaw *iRadiusLaw,
                            CATLaw *iMappingLaw, CATBoolean iIsEuclidian = TRUE, CATBoolean iIsPlanarBody = FALSE);
      CATParallelConnectTool(CATLONG32 iSide, CATLaw *iRadiusLaw,
                            CATLaw *iMappingLaw, CATBoolean iIsEuclidian = TRUE, CATBoolean iIsPlanarBody = FALSE);

      ~CATParallelConnectTool();


      //=====================
      // Get/Set Methods
      //=====================
      CATLONG32 GetType() const;
      CATLONG32 GetCutterDimension(CATConnectTool::CutterType iCutterType) const;

      CATLONG32 GetSide() const;
      void SetSide(CATLONG32 iSide);

      // Check Twist
      // iCheck = 0 : OFF
      // iCheck = 1 : ON
      // iCheck = 2 : new management of twist in euclidian and geodesic
      void SetCheckTwist(CATLONG32 iCheck);
      CATLONG32 GetCheckTwist() const;

      // Methods used to obtain input laws (radius and mapping)
      const CATLaw * GetRadius() const;
      const CATLaw * GetMapping() const;

      // *** INTERNAL USE ONLY ***
      // Methods dedicated to the storage of non-approximate radius law.
      // Could be usefull to have more precise law evaluations when radius
      // law shape is critical (for instance vertical tangency)
      void SetNonApproxLaw(CATLaw * iNonApproxLaw);
      const CATLaw * GetNonApproxLaw() const;

      // *** INTERNAL USE ONLY ***
      // Methods dedicated to the storage of specific diagnosis from the
      // approx law evaluation. The existence of vertical tangents is specified
      // in this attribute.
      // @nocgmitf
      void SetApproxDiagnostic(CATApproxDiagnostic iApproxDiagnostic);
      // @nocgmitf
      const CATApproxDiagnostic GetApproxDiagnostic() const;

      // *** INTERNAL USE ONLY ***
      // Methods dedicated to the storage of specific diagnosis from the
      // approx law evaluation. The existence of vertical tangents is specified
      // in this attribute.
      void SetApproxDeviation(double iApproxDeviation) ;
      const double GetApproxDeviation() const;


      // Method used to obtain the mathematical composition function Rfunc between radius and mapping:
      //
      //
      //        CurveDomain ---> RadiusDomain
      // Rfunc: w           ---> Rfunc(w) = RadiusLaw( Mapping ( w ) ) , where CurveDomain is mapping domain
      //                                                                 ie. physical limits of the mapping law
      //
      // *** INTERNAL USE ONLY ***
      // If iApproximateLaw = FALSE and SetNonApproxLaw has been previously called, the method
      // takes the non-approximate law as reference (ie. Rfunc(w) = NonApproxRadiusLaw( Mapping ( w ) ) )
      // Be careful, if non-approximate law has not been set, this throws
      //
      const CATMathFunctionX * GetRadiusFunction(CATBoolean iApproximateLaw=TRUE);

      // CheckSmallArcs
      //
      // This method tries to retrieve the component functions of the global radius law that match with current mapping limits.
      // If this searching phase succeeded, a check on small arcs is then performed on each sub-component if they are of PolynomX type:
      //
      // |ti+1 - ti| <= iRelativTol * DomainWidth ===> small arc (iRelativTol is optionnal).
      //
      // The method returns:
      //    -1: deep error (null pointer, non polynomial function, etc.): check is irrelevant.
      //     0: check is OK (no small arcs).
      //     1: check is KO (radius law contains small arcs).
      //
      // *** INTERNAL USE ONLY ***
      //
      int CheckSmallArcs(double iRelativTol=1.e-6); //@NumValidated ( relative value )

      // S9L : Start
      CATBoolean  IsPlanarBodyInput() const;
      // S9L : End

      // @nocgmitf
      CATDistanceTool * GetDistanceTool();


      void SetEndSurface( CATSurface *iEndSurface );
      void GetEndSurface( CATSurface ** ioEndSurface);

#ifdef CATIACGMV5R20
      /**
      * Returns the distance tool.
      * @return  [out, IUnknown#Release]
      *   The tool.
      */
      CATICGMDistanceTool * GetIDistanceTool();
#endif

      CATParallelComputer * GetComputer( CATCurve   * iCurve , CATCrvLimits & iCurveLimit , CATLONG32 iOrientationEdge  , CATBoolean iExtrapolEdge   ,
                                         CATSurface * iSupport,CATSurLimits & iSupportLimit,CATLONG32 iOrientationSupport,CATBoolean iExtrapolSupport,
                                         CATMathSetOfPointsND * iInitPoints,
                                         CATBoolean iLoopSearch );

      CATLONG32 ValidateInitSide(CATCurve * iCurve, CATCrvParam & iCrvParam,
                                 CATSurface * iSurface, CATSurParam & iSurParam,
                                 double iRadiusValue, double * iTangent3D,
                                 double * oProduct = NULL);

      CATLONG32 ProjectOnOriginalSurface(CATCurve        *  iCurve,
                                         CATCrvParam     &  iParam,
                                         CATSurface     *&  oOriginalSurface,
                                         CATPCurve      *&  oOriginalPCurve,
                                         CATCrvParam     &  oCrvParam,
                                         CATSurParam     &  oSurParam);

      /***********************************************************/
      /* Methods to save information for geodesic function which */
      /* needs topological informations                          */
      /***********************************************************/
      void SetAttributes( CATLISTP(CATGeometry) &iAttributes );
      void GetAttributes( CATLISTP(CATGeometry) &oAttributes );
      void SetVariableAttribute( CATGeometry *iAttribute );
      void GetVariableAttribute( CATGeometry *& oAttribute );
      void SetOriginCurveSupport( CATSurface * iSupp, CATLONG32 iOrient );
      void GetOriginCurveSupport( CATSurface *& oSupp, CATLONG32 & oOrient );
      void SetCurve3DOrientation(CATLONG32 & iOriginCrvOrient);
      void SetOriginSurface(CATSurface * iSurface, const CATLONG32 iOrient,
                            CATEdgeCurve * iOriginECrv, CATPCurve * iOriginPCrv,
                            CATLONG32 iSide);
      void GetOriginSurface(CATSurface *& oSurface, CATLONG32 & oSurOrient,
                            CATEdgeCurve *& oOriginECrv, CATPCurve *& oOriginPCrv);

      /***********************************************************/
      /* AHG :Methods to stream and unstream the tool for the    */
      /* CGMReplay                                               */
      /***********************************************************/
      static CATString _OperatorId;
      /** @nodoc @nocgmitf */
      const CATString * GetOperatorId();
      /** @nodoc @nocgmitf */
      CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
      /** @nodoc @nocgmitf */
      void WriteInput(CATCGMStream  & ioStream);


   private:
      void Init();

      void Init(CATLONG32 iSide, CATLaw *iRadius                                  ,CATLaw *iMapping, CATBoolean iIsEuclidian);

      void Init(CATDistanceTool *iDistanceTool,CATICGMDistanceTool *iIDistanceTool,CATLaw *iMapping );

      // CheckSmallArcsOnComponent
      //
      // To be called internally by CheckSmallArcs on each sub-component function.
      //
      // The method returns:
      //    -1: deep error, check is irrelevant.
      //     0: check is OK (no small arcs).
      //     1: check is KO (radius law contains small arcs).
      //
      int CheckSmallArcsOnComponent(const CATMathFunctionX * iComponent,
                                    CATMathInterval        & iComponentDomain,
                                    CATMathInterval        & iGlobalDomain,
                                    double                   iRelativTol,
                                    const CATTolerance     & iTol,
                                    CATLONG32                iDepth=0);

      //=====================
      // Data
      //=====================
   private:
      CATLONG32 _Side;
      CATLONG32 _OrientCrvSupp;
      double _ApproxDeviation;
      CATBoolean _IsEuclidian;
      CATBoolean _IsPlanarBody;
      CATApproxDiagnostic _ApproxDiagnostic;
      CATLONG32 _CheckTwist;

      CATGeometry * _Face;
      CATSurface  * _CurveSupport;
      CATSurface  * _EndSurface;

      CATLaw *_Radius;
      CATLaw *_Mapping;
      CATLaw *_NonApproxLaw;
      CATMathFunctionX  * _Composition;
      CATMathFunctionX  * _CompositionNonApprox;
      CATMathFunctionX  * _Translation;
      CATMathFunctionX  * _LocalRadius;
      CATMathPiecewiseX * _LocalPiecewise;

      CATDistanceTool     *_DistanceTool;
      CATICGMDistanceTool *_IDistanceTool;
      CATLISTP(CATGeometry) _BodyShellWireEdge;

      CATLONG32 _RefSide;
      CATLONG32 _OriginCrvOrient;
      CATPCurve * _pOriginPCurve;
      CATEdgeCurve * _pOriginEdgeCurve;
   };

/**
* @return [out, delete]
*/
ExportedByConnect CATParallelConnectTool *CATCreateParallelConnectTool(CATSoftwareConfiguration * iConfig,CATDistanceTool *iDistanceTool,
                                                                       CATLaw *iMappingLaw, CATBoolean iIsPlanarBody = FALSE); // iMappingLaw = 0 possible si loi constante

#endif
