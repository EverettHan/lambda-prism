/* -*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATConnectCheckerInterfaceOfSurfaces
//  Base class for checking geometric continuity between two surfaces
//
//=============================================================================
// Usage Notes:
//=============================================================================
// Oct.  03 RHA Creation                                              R. Hamza
// March 05 CQI Modifications + new specs R16
// 02/08/17 NLD Ajout Init()
// 19/09/18 MWE SetCurvatureTolerances
// 15/03/21 Q48 Migration to derive from CATGeoOperator (and store config)
// 27/05/22 NLD Smart indent
//              G2 more precise documentation
//=============================================================================

#ifndef CATConnectCheckerInterfaceOfSurfaces_H
#define CATConnectCheckerInterfaceOfSurfaces_H

// Class header
#include "CATGeoOperator.h" // Q48__ConnectCheckerMigration
//#include "CATCGMOperator.h"

// ExportedBy
#include "Y30A3HGG.h"

// Utility
#include "CATCGMVirtual.h"

// Mathematics
#include "CATMathPoint.h"
#include "CATMathInline.h"
#include "CATCrvParam.h"
#include "CATSurParam.h"

// GeometricObjects
#include "CATSurLimits.h"

// GeometricOperators
#include "CATCreateConnectChecker.h"

class CATGeoFactory;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATCurve;
class CATMathVector;
class CATMathInterval;
class CATSurLimits;
class CATDistanceMinPtCrv;
class CATCrvParam;

/** 
 * Type to define the command of Connect Checker.
 * @param OptionGaps
 * Evaluation of Gap.
 * @param OptionAngles
 * Evaluation of Angles between normals.
 * @param OptionCurvatures
 * Evaluation of Curvatures.
 * @param OptionOverlaps
 * Search of Overlaps.
 */

#include "CATConnectCheckerDef.h"
#include "CATMathSurfaceGData.h"
#include "CATMathLocalConnectChecker.h"

// Debug
#include "CATGeoOpTimer.h"

class ExportedByY30A3HGG CATConnectCheckerInterfaceOfSurfaces : public CATGeoOperator // Q48__ConnectCheckerMigration
//class ExportedByY30A3HGG CATConnectCheckerInterfaceOfSurfaces : public CATCGMOperator
{
   CATCGMVirtualDeclareClass(CATConnectCheckerInterfaceOfSurfaces);
public:
   //-----------------------------------------------------------------------
   //- Object management
   //-----------------------------------------------------------------------
   //
   // Connect Checker of Surfaces
   //
   
   /////////////////////////////////////////////////////////////
   // Constructor information :
   //
   // PCurve vs Surface orientation = Product of the 4 following
   //                                 orientations :
   // O1- Orientation Edge / Face 
   //     ex.:_Edge->GetMatterSide(_Face1): +1 = left;-1 = Right
   //
   // O2- Orientation Edge / EdgeCurve
   //
   // O3- Orientation Curve / EdgeCurve
   //
   // O4- Orientation Face / Surface
   /////////////////////////////////////////////////////////////
   
   /////////////////////////////////////////////////////////////
   // Generic constructor
   /////////////////////////////////////////////////////////////
   CATConnectCheckerInterfaceOfSurfaces (     CATGeoFactory            * iFactory,
                                              CATSoftwareConfiguration * iConfig,
                                              CATEdgeCurve             * iEdgeCurve,
                                              CATSurface               * iSurface1,
                                              CATSurface               * iSurface2,
                                         const CATSurLimits            & iLimitSurf1,
                                         const CATSurLimits            & iLimitSurf2,
                                         const CATMathBox              * iBoxFace1,
                                         const CATMathBox              * iBoxFace2,
                                         const CATPointOnEdgeCurve     * iPOECStart,
                                         const CATPointOnEdgeCurve     * iPOECEnd,
                                         const CATPCurve               * iPCrv1,
                                         const CATPCurve               * iPCrv2,
                                               int                       iOriPCrv1VsSurf1,
                                               int                       iOriPCrv2VsSurf2,
                                               int                       iOriSurf1Face1,
                                               int                       iOriSurf2Face2);
   
   /////////////////////////////////////////////////////////////
   // Healing constructor (call with Normal and Tangential gap)
   // iOriPCrv1Mat and iOriPCrv2Mat = matter orientations
   // iIsSmooth = 1 if edge is smooth, 0 otherwise
   /////////////////////////////////////////////////////////////
   CATConnectCheckerInterfaceOfSurfaces(      CATGeoFactory            * iFactory,
                                              CATSoftwareConfiguration * iConfig,
                                              CATEdgeCurve             * iEdgeCurve,
                                              CATSurface               * iSurface1,
                                              CATSurface               * iSurface2,
                                        const CATSurLimits             & iLimitSurf1,
                                        const CATSurLimits             & iLimitSurf2,
                                        const CATPointOnEdgeCurve      * iPOECStart,
                                        const CATPointOnEdgeCurve      * iPOECEnd,
                                        const CATPCurve                * iPCrv1,
                                        const CATPCurve                * iPCrv2,
                                              int                        iOriPCrv1VsSurf1,
                                              int                        iOriPCrv2VsSurf2,
                                              CATBoolean                 iIsSmooth);
   
   /////////////////////////////////////////////////////////////
   // Light constructor
   /////////////////////////////////////////////////////////////
   CATConnectCheckerInterfaceOfSurfaces(      CATGeoFactory            * iFactory,
                                              CATSoftwareConfiguration * iConfig,
                                              CATEdgeCurve             * iEdgeCurve,
                                              CATSurface               * iSurface1,
                                              CATSurface               * iSurface2,
                                        const CATPointOnEdgeCurve      * iPOECStart,
                                        const CATPointOnEdgeCurve      * iPOECEnd,
                                        const CATPCurve                * iPCrv1,
                                        const CATPCurve                * iPCrv2,
                                              int                        iOriPCrv1VsSurf1,
                                              int                        iOriPCrv2VsSurf2);
   
   ~CATConnectCheckerInterfaceOfSurfaces();
   
   //-----------------------------------------------------------------------
   //- Public methods
   //-----------------------------------------------------------------------
   
   // @nocgmitf
   int        RunOperator();
   
   // Post-Run diagnostic on whole computations (TRUE if OK, FALSE otherwise).
   // If FALSE, Get methods could return a throw if they are called 
   CATBoolean IsRunOK();
   
   // *** Only to take account of V5R16 new specifications. ***
   //
   // USE EXPLICITLY THIS METHOD BEFORE RUN OPERATOR 
   // TO SWITCH TO V5R16 SPECIFICATIONS.
   //
   void       SetNewSpecs(short iSetNewSpecs = 1);
   
   /////////////////////////////////////////////////////////////
   // MANDATORY SET METHODS
   /////////////////////////////////////////////////////////////
   
   // Choose the computation type
   // ex.: Gaps + Curvatures : SetTypeOfEvalutation(CATGap | CATCurvature)
   //
   // CATConnectCheckerGap              1
   // CATConnectCheckerAngle            2
   // CATConnectCheckerCurvature        4
   // CATConnectCheckerOverLaps         8
   // CATConnectCheckerTgtAndNormGap    16
   // CATConnectCheckerCurvatureComb    32
   void       SetTypeOfEvaluation (CATCommandOption iCommand);
   
   //
   // STANDARD DISCRETIZATION MODE
   //
   // Choose the type of discretization (pre-defined values)
   //
   // iType = 0 : Standard = Nb of Points =  5
   // iType = 1 : Coarse   = Nb of Points = 15
   // iType = 2 : Medium   = Nb of Points = 30
   // iType = 3 : Fine     = Nb of Points = 45
   void       SetTypeOfDiscretization (int iType);
   
   //
   // THESE MODES ARE ALTERNATIVES TO STANDARD DISCRETIZATION
   //
   // *** Available with V5R16 new specifications. ***
   //
   // Exact G1 reconvergence of Min/Max gap G1 in [0,PI]
   // (call with iEnable = TRUE to activate this mode)
   //
   // iSideOnFace is optionnal (it allows internally to compute G1 values
   // with true sign, in [-PI,PI])
   // 
   // Output results are obtained by calling GetMinMaxAngle method.
   //
   void       SetExactG1MinMaxMode(CATBoolean iEnable     ,
                                   int        iSideOnFace = 1);
   //
   //
   //
   // OptimalSampling Mode : an optimal discretization is performed
   //                        according to the complexity of input
   //                        geometries
   //
   void       SetOptimalSamplingMode();
   //
   // OpenSampling Mode : the caller is free to choose the discretization
   //                     sampling value.
   //
   // NB. : iSamplingValue must be higher than 3
   void       SetOpenSamplingMode(const CATLONG32 iSamplingValue = 5);
   
   /////////////////////////////////////////////////////////////
   // SET METHODS IN ACCORDANCE WITH LIGHT CONSTRUCTOR
   /////////////////////////////////////////////////////////////
   
   // void SetBoxFace             (const CATMathBox * iBoxFace1, const CATMathBox * iBoxFace2,);
   // void SetSurfaceLimits       (const CATSurLimits & iLimitSurf1, const CATSurLimits & iLimitSurf2);
   // void SetOrientationSurfFace (const int iOriPCrv1VsSurf1, const int iOriPCrv2VsSurf2);
   
   //Modif du type de l'edge
   // 1 = mort, 0 = vive sinon CATThrow
   void            SetEdgeType(int iIsSmooth);
   
   
   // To stop the angle evaluations as soon as an angle higher, in absolute value, than the given tolerance
   void            SetStopOnAngleTolerance(double iAngleMax);
   
   // Only for New Specs : define the interval of valid curvatures for your scope
   // By default : iMinCurvature corresponds to the inverse of the largest radius that can be created in CATIA.
   // At scale 1 the maximum radius for a circle is 1E+7, so iMinCurvature is 1E-7.
   // CAUTION: these are values varying like power -1 of factory scale
   void            SetCurvatureTolerances(double iMinCurvature,
                                          double iMaxCurvature);
   
   /////////////////////////////////////////////////////////////
   // GET METHODS
   /////////////////////////////////////////////////////////////
   
   // Returns the number of points used for discreete computations.
   INLINE int      GetNumberOfPoints()
   {return _NbPoints;};
   
   // NB: for all methods flaged by * MD * THE CALLER MUST MANAGE DEALLOCATION ONLY
   
   ////////////////////
   // G0 get methods //
   ////////////////////
   //
   // Returns [ _MinGap , _MaxGap ] (with respect to the input poecs) and associated points if needed
   CATMathInterval GetMinMaxGap      (CATMathPoint      oPointMin     [2] = NULL,
                                      CATMathPoint      oPointMax     [2] = NULL);
   
   // Returns all discretized couple of points (P1,P2) (with respect to the input poecs)
   // and respected gaps ||P1-P2|| (the method allocates memory)
   //
   // * MD *
   void            GetAllPoints      (double         *& oGaps             ,
                                      CATMathPoint   *& oPoint1           ,
                                      CATMathPoint   *& oPoint2           );
   
   ////////////////////
   // G1 get methods //
   ////////////////////
   //
   // Returns [ min(_Angles) , max(_Angles) ] (in radians) and associated points if needed
   //
   // NB1 : the operator should be initialized with the constructor and
   //       the two Curves (iPCrv1 and iPCrv2) must be some PCurves.
   // NB2 : the angles returned are between 0 and PI radians
   CATMathInterval GetMinMaxAngle    (CATMathPoint     oPoint1MinMax  [2] = NULL,
                                      CATMathVector    oNormal1MinMax [2] = NULL);
   
   // Returns all G1 angles defaults (with respect to the input poecs) and discretized points and normals
   // on first curve (the method allocates memory)
   //
   // * MD *
   void            GetAllTangency    (double        *& oAngles            ,
                                      CATMathPoint  *& oPoint1            ,
                                      CATMathVector *& oNormal1           );
   
   // to get the sharpness if the "StopOnTolerance" mode has been activated
   CATBoolean      GetStopOnAngleTolerance();
   
   
   ////////////////////
   // G2 get methods //
   ////////////////////
   //
   // CAUTION: in the following G2 get methods, "Curvature" is always, in fact, a percentage of curvature deviation
   //          NLD270522

   // Returns [ min(_Curvatures) , max(_Curvatures) ] in percent and associated points if needed
   CATMathInterval GetMinMaxCurvature(CATMathPoint     oPoint1MinMax  [2] = NULL,
                                      CATMathVector    oNormal1MinMax [2] = NULL);
   
   // Returns all G2 curvatures defaults in percent
   // (with respect to the input poecs) and discretized points and normals
   // on first curve (the method allocates memory)
   //
   // * MD *
   void            GetAllCurvature   (double        *& oCurvature        ,
                                      CATMathPoint  *& oPoint1           ,
                                      CATMathVector *& oNormal1          );
   
   // *** Available with V5R16 new specifications. ***
   //
   // * MD *
   //
   // Returns all G2 curvatures defaults in percent
   // (with respect to the input poecs), same convexity booleans, and
   // discretized points and normals on first curve (the method allocates memory)
   void       GetAllCurvatureAndConvexities
                                     (double        *& oCurvature        ,
                                      CATBoolean    *& oSameConvexities  ,
                                      CATMathPoint  *& oPoint1           ,
                                      CATMathVector *& oNormal1          );
   
   ////////////////////
   // G3 get methods //
   ////////////////////
   //
   // *** Available with V5R16 new specifications. ***
   //
   // * MD *
   //
   // Returns all G3 angle defaults in radians (with respect to the input poecs) of normal section
   // curvature comb between the two surfaces, and discretized points and normals on first curve
   // (the method allocates memory)
   void            GetAllCurvatureCombAngles
                                     (double        *& oCurvatureCombAngles,
                                      CATMathPoint  *& oPoint1             ,
                                      CATMathVector *& oNormal1            );
   
   // Returns [ min(CurvCombAngle) , max(CurvCombAngle) ] in radians and associated points and normals if needed
   CATMathInterval GetMinMaxCurvatureCombAngles
                                     (CATMathPoint     oPoint1MinMax [2] = NULL,
                                      CATMathVector    oNormal1MinMax[2] = NULL);
   
   
   // Overlap and healing get methods
   //
   // Returns all overlaps boolean diagnostics for each couple of points (P1,P2) discretized
   // (the method allocates memory)
   //
   // * MD *
   CATBoolean    * GetOverlap();
   
   // Get dans le cas mort, on retourne les gaps calculés p/r
   // la moyenne des deux normales.
   // TgGap < 0 => overlaps, TgGap > 0 => pas d'overlaps
   double          GetMaxTgtGap();
   double          GetMinTgtGap();
   double          GetMaxNoGap();
   
   // Get dans le cas vif, on retourne les gaps calcules p/r
   // a une des normales.
   // TgGap < 0 => overlaps, TgGap > 0 => pas d'overlaps
   double          GetMaxTgtGap(CATPCurve * iPCrvRef);
   double          GetMinTgtGap(CATPCurve * iPCrvRef);
   double          GetMaxNoGap (CATPCurve * iPCrvRef);
   
   // DANGER = si le mauvais get est appelé (mode vif ou mort) on sort en Throw!!!
   
   //Retourne les valeurs des snapping au debut et a la fin de l'edge
   void            GetSnapping(double & oSnapStart,double & oSnapEnd);
   
private :
   
   //-----------------------------------------------------------------------
   //- Private methods
   //-----------------------------------------------------------------------
   // Object initialization. same arguments as generic constructor. NLD020817
   void       Init                      (     CATGeoFactory            * iFactory,
                                              CATSoftwareConfiguration * iConfig,
                                              CATEdgeCurve             * iEdgeCurve,
                                              CATSurface               * iSurface1,
                                              CATSurface               * iSurface2,
                                         const CATSurLimits            & iLimitSurf1,
                                         const CATSurLimits            & iLimitSurf2,
                                         const CATMathBox              * iBoxFace1,
                                         const CATMathBox              * iBoxFace2,
                                         const CATPointOnEdgeCurve     * iPOECStart,
                                         const CATPointOnEdgeCurve     * iPOECEnd,
                                         const CATPCurve               * iPCrv1,
                                         const CATPCurve               * iPCrv2,
                                               int                       iOriPCrv1VsSurf1,
                                               int                       iOriPCrv2VsSurf2,
                                               int                       iOriSurf1Face1,
                                               int                       iOriSurf2Face2
                                        );

   CATBoolean      Initialize();

   CATBoolean      PreProcess();

   void            ComputeDiscretization();
   void            ComputeNormals();
   void            ComputeDerivatives(CATBoolean iComputeThirdDeriv = FALSE);
   
   // iGType = 1: G2 only
   // iGType = 2: G3 only
   // iGType = 4: G2 and G3
   CATBoolean      ComputeG0();
   CATBoolean      ComputeG1();
   CATBoolean      ComputeG2();
   CATBoolean      ComputeG3();
   CATBoolean      ComputeG2andG3(CATLONG32 iGType);
   CATBoolean      ComputeOverlap();
   
   int             RunNew();
   int             RunOld();

   
   // Context = overlap computation :
   // Analyse the orientation of a given point on surface in respect to the PCurve
   int        MatterOrientationAnalysis(CATPCurve   * PCrv               ,
                                        CATSurParam & PointParam         ,
                                        CATCrvParam & ResultOfDistanceMin,
                                        CATCrvParam & Start              ,
                                        CATCrvParam & End                );
   
   // Snapping management to guarantee symetric behavior
   // + computation of snapping distances for CATConnectCheckerTgtAndNormGap mode
   void       ManageSnapping           (CATCrvParam & oStart             ,
                                        CATCrvParam & oStart1            ,
                                        CATCrvParam & oStart2            ,
                                        CATCrvParam & oEnd               ,
                                        CATCrvParam & oEnd1              ,
                                        CATCrvParam & oEnd2              ,
                                        int           RefCurve           );
   
   // CATConnectCheckerTgtAndNormGap mode : evaluations of normal and tangential
   // components of all gaps ||P1-P2||
   void       EvalNormalAndTangentGap();
   
   // Max and min gap reconvergences : Newton step from best discreet init.
   void       ReconvergeMaxGap         (int           max                ,
                                  const CATCrvParam & CrvP1              ,
                                  const CATCrvParam & CrvP2              ,
                                  const CATCrvParam & End1               ,
                                  const CATCrvParam & End2               );
   void       ReconvergeMinGap   (      int           min                ,
                                  const CATCrvParam & CrvP1              ,
                                  const CATCrvParam & CrvP2              ,
                                  const CATCrvParam & End1               ,
                                  const CATCrvParam & End2               );
   
   CATBoolean CheckMaxGapSymmetry(const double      iMaxGap,
                                  const CATCrvParam iMaxGapPar[]) const;

   /////////////////////////////////////////////////////////////
   // MEMORY MANAGEMENT
   /////////////////////////////////////////////////////////////
   // Users data management
   void       AllocateMem();
   void       DeleteOutput();
   void       ResetOutput();
   
   // Contextual data management
   void       AllocateTmpMem();
   void       DeallocateTmpMem();
   
protected:
   CATGeoFactory              * _Factory;
   CATSoftwareConfiguration   * _SoftwareConfiguration;
   CATEdgeCurve               * _ECrv;
   CATBoolean                   _SmoothECrv;
   const CATPointOnEdgeCurve  * _POECStart,
                              * _POECEnd;
   CATSurface                 * _Support[2];
   const CATMathBox           * _BoxFace[2];
   const CATPCurve            * _PCurve[2];
   int                          _OriPCrv1VsSurf1,
                                _OriPCrv2VsSurf2;
   int                          _OriSurf1Face1,
                                _OriSurf2Face2;
   CATSurLimits                 _SurLimits1;
   CATSurLimits                 _SurLimits2;
   
   int                          _NbPoints;
   CATBoolean                   _OpenSamplingMode;
   CATBoolean                   _OptimalSamplingMode;
   CATCommandOption             _Command;
   
   ////////////////////////////////////////////////////////////
   // Connect checker analysis data
   ////////////////////////////////////////////////////////////
   // G0
   double                     * _Gaps;
   double                     * _GapsTg1;
   double                     * _GapsTg2;
   double                     * _GapsNo1;
   double                     * _GapsNo2;
   double                       _MaxGapsTg1,_MaxGapsTg2,_MinGapsTg1,_MinGapsTg2;
   double                       _MaxGapsNo1,_MaxGapsNo2;
   double                       _SnapingEnd, _SnapingStart;
   // G1
   double                     * _Angles;
   CATBoolean                   _SetStopOnAngle;
   CATBoolean                   _SharpnessFound;
   double                       _AngleMaxTol;
   // G2
   double                     * _Curvatures;
   CATBoolean                 * _SameConvexities; // TRUE if same convexity has been found, FALSE otherwise
   // G3
   double                     * _Phi;
   // Overlaps
   CATBoolean                 * _OverLaps;
   
   // Reconvergences data
   
   // G0-reconvergence
   double                       _MaxGap;
   CATLONG32                    _imax; // index of discreet max
   CATMathPoint                 _Point1MaxGap;
   CATMathPoint                 _Point2MaxGap;
   double                       _MinGap;
   CATLONG32                    _imin; // index of discreet min
   CATMathPoint                 _Point1MinGap;
   CATMathPoint                 _Point2MinGap;
   
   // G1-reconvergence
   CATBoolean                   _G1ExactMode;
   int                          _SideOnFace;
   double                       _MaxGapG1;
   double                       _MinGapG1;
   CATMathPoint                 _Pt1MinGapG1;
   CATMathPoint                 _Pt1MaxGapG1;
   CATMathVector                _Normal1AtG1Max;
   CATMathVector                _Normal1AtG1Min;
   
   ////////////////////////////////////////////////////////////
   // Geometric data linked to surfaces
   ////////////////////////////////////////////////////////////
   CATMathSurfaceGData        * _SurData; // 2 * _NbPoints containers
   
   // Local operator used for G-computations
   CATMathLocalConnectChecker * _LocalConnectChecker;
   
   // Limit parameters
   CATCrvParam                  _Start, _End, _Start1, _End1, _Start2, _End2;
   // Discretized parameters
   CATCrvParam                * _cp1, * _cp2;
   CATSurParam                * _sp1, * _sp2;
   // G0
   CATMathPoint               * _Point1;
   CATMathPoint               * _Point2;
   // G1
   CATMathVector              * _Normal1;
   CATMathVector              * _Normal2;
   short                        _Orientation;
   
   ////////////////////////////////////////////////////////////
   // ConnectChecker tolerances
   ////////////////////////////////////////////////////////////
   double                       _CRBmin;
   double                       _CRBmax;
   
   // _RefCurveID
   // 0 : none PCurve is the RefCurve
   // 1 : _PCurve[0] is the RefCurve
   // 2 : _PCurve[1] is the RefCurve
   CATLONG32                    _RefCurveID;
   CATBoolean                   _RunOK;

private:
   short                        _NewSpecs;
   
   //========================================================================
   // CGMReplay management
   //========================================================================
protected:
   friend class CATGeoStreamFactory;
   
   // private static data
   static CATString             _OperatorId;
   static CATGeoOpTimer         _Timer;
public:
   /** @nodoc @nocgmitf */
   const   CATString        * GetOperatorId();
   
   /** @nodoc @nocgmitf */
   virtual CATGeoOpTimer    * GetTimer();

   /** @nodoc @nocgmitf */
           CATExtCGMReplay  * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
   /** @nodoc @nocgmitf */
   virtual void               WriteInput(CATCGMStream  & os);
   /** @nodoc @nocgmitf */
   virtual void               WriteOutput(CATCGMStream & os);
   /** @nodoc @nocgmitf */
   virtual CATBoolean         ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
   /** @nodoc @nocgmitf */
   virtual void               Dump( CATCGMOutput& os ) ;
   /** @nodoc @nocgmitf */
   virtual void               DumpOutput(CATCGMOutput & os);
   /** @nodoc @nocgmitf */
   virtual void               DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
   /** @nodoc @nocgmitf */
   virtual CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
};

#endif




