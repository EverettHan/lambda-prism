//=========================================================================
// COPYRIGHT DASSAULT SYSTEMES 1999
//=========================================================================
//
// CATParallelComputer:
//   Implementation of Parallel Operator.
//   derivated with EuclidianParallel and GeodesicParallel
//
//=========================================================================
// Usage notes:
//=========================================================================
// 12/04/17 NLD Mise au propre
//              - smart indent 
//              Documenation du fonctionnement et des precautions d'usage des tolerances
//              XScaleRules for SetTolerance()
// 23/03/22 S9L Overlap of twisted piece with adjacent non-twisted pieces
// 06/04/22 S9L Cleaning of twists overlapping within 1 micron with adjacent pieces 
//=========================================================================
#ifndef CATParallelComputer_h
#define CATParallelComputer_h

#include "Connect.h"
#include "CATConnectComputer.h"

#include "CATSurLimits.h"
#include "CATCrvLimits.h"

#include "CATMathDef.h"
#include "CATMathIntervalND.h"

class CATConnectPiece;
class CATParallelConnectTool;
class CATGeoFactory;
class CATSurface;
class CATCurve;
class CATPurve;
class CATCrvParam;
class CATMathFunctionX;
class CATMathFunctionXY;
class CATMathSetOfLongs;
class CATMathSetOfPointsND;
class CATMathSetOfPointsNDWithVectors;
class CATMathQuickDiscretizeFunctionX;
class CATMathVectorialFunctionX;
class CATSoftwareConfiguration;

//-------------------------------------------------------------------------
class ExportedByConnect CATParallelComputer : public CATConnectComputer 
   {
   public:
      //-----------------------------------------------------------------------
      // Object Management.
      //-----------------------------------------------------------------------
      CATParallelComputer(CATSoftwareConfiguration * iConfig,
                          CATGeoFactory            * iFactory,
                          CATCurve                 * iCurve,
                          CATCrvLimits             & iCurveLimit,
                          CATLONG32                  iOrientationEdge,
                          CATBoolean                 iExtrapolEdge,
                          CATSurface               * iSupport,
                          CATSurLimits             & iLimit,
                          CATLONG32                  iOrientationSur,
                          CATBoolean                 iExtrapolSur,
                          CATParallelConnectTool   * iTool,
                          CATMathSetOfPointsND     * iInitPoints,
                          CATBoolean                 iLoopSearch=0);

      ~CATParallelComputer();

      //-----------------------------------------------------------------------
      // Public methods.
      //-----------------------------------------------------------------------

              void                              SetOriginCurveSupport(      CATSurface * iSurface,
                                                                      const CATLONG32    iOrient );

      // Fixe la tolerance globale (-1 pour les valeurs par defaut).
      // la tolerance recue doit prendre la puissance 1 de l'echelle. NLD110417
      virtual void                              SetTolerance       (double      tol            = -1.);

      // Renvoie les tolerances locales (valeurs de _TOL_INTERPOL et _TOL_SMOOTH)
      // ATTENTION: la tolerance d'interpolation rendue reste en puissance 1 de l'echelle
      //            et ne doit pas etre utilisee directement dans les classes d'interpolation (famille de CATMathInterpol)
      //            NLD110417
              void                              GetTolerances      (double     & oInterpolTol  ,
                                                                    double     & oSmoothTol    ,
                                                                    CATBoolean & oSmoothEnabled);

      // Active (defaut) ou desactive le smooth en sortie.
              void                              ToggleSmooth         (CATBoolean   enabled);

      // Accepte les points uniques comme solutions.
      // Si desactive (defaut), ne renvoie rien plutot qu'un point unique, a moins
      // que l'on ait affaire a un cercle reconverge en son centre.
              void                              ToggleAcceptPointSol (CATBoolean accept);

      // Renvoie l'etat
              CATBoolean                        AcceptPointSol ();

      // Indique que l'on n'a qu'un point solution
              void                              IsPointSol (CATBoolean iInfo);

              CATMathSetOfPointsNDWithVectors * GetResult() const;
              CATBoolean                        IsTwisted() const;
              CATLONG32                         IsOverlapped() const;

      // For Connect Use Only
              CATBoolean                        HasBeenRunInReportInit() const;

      virtual CATLONG32                         GetConfiguration() const;

      // Renvoie le systeme explicite eventuel
      virtual CATMathQuickDiscretizeFunctionX * GetExplicitSystem();

              CATLONG32                         GetInitIndex() const;
      virtual void                              Interpol (const CATMathFunctionX                * iF[3],
                                                          const CATMathFunctionXY               * iG[3],
                                                          const CATLONG32                         iOrientationF,
                                                          const CATLONG32                         iOrientationG,
                                                                CATMathSetOfPointsNDWithVectors * iSet,
                                                                CATMathSetOfPointsND            & oParameters,
                                                                CATMathSetOfPointsND            & oPoints,
                                                                CATMathSetOfPointsND            & oTangents,
                                                                CATMathSetOfPointsND            & oSecondDerivatives ) = 0;

              void                      ComputeAutoIntersection(CATConnectSupport               & iSupport1  ,
                                                                CATConnectSupport               & iSupport2  ,
                                                                CATConnectPiece               **& oPieces    ,
                                                                CATLONG32                       & oNbOfPieces,
                                                                CATMathSetOfLongs               & ioIsTwisted);

              HRESULT                   RemoveOverlappedTwists(CATMathSetOfPointsND & ioParameters,
                                                               CATMathSetOfPointsND & ioPoints,
                                                               CATMathSetOfPointsND & ioTangents,
                                                               CATMathSetOfPointsND & ioSecondDerivatives,
                                                               CATMathSetOfLongs    & iC1Discontinuities);

      // Ask computer to try an explicit solving method. Usefull for EuclidianParallel cases on plane.
      // (euclidian only - no effect for geodesic cases)
      void TryExplicitSolve(CATBoolean iEnable = TRUE);

      // If TryExplicitSolve has been set, and an explicit solution has been computed, this method allows
      // to get the result as a quintic vectorial function. A null pointer is returned otherwise.
      // (euclidian only - no effect for geodesic cases)
      virtual CATMathVectorialFunctionX * GetEuclidianQuinticX();

   protected:
      void      DestroyResults();
      CATLONG32 CheckSignature(       CATMathSetOfPointsNDWithVectors * set);
      CATLONG32 CheckInit     (       double                          * initPt,
                                      double                          * initTg);
      CATLONG32 CheckTwist    ( const CATMathSetOfPointsNDWithVectors * iResultSet) const;

      // Do Not Use
      CATBoolean IsSeveralPointsOld (CATConnectSupport & iSupport1,
                                     CATConnectSupport & iSupport2,
                                     CATConnectPiece **& oPieces,
                                     CATLONG32         & oNbOfPieces,
                                     CATMathSetOfLongs & ioIsTwisted,
                                     CATLONG32           iResultIndex);

      CATLONG32 IsSeveralPoints     (CATMathSetOfPointsND & iSetOfPoints);

      void      CheckSeveralPoints  ();

      // computation of twist extremities : caution this method can modify the number of results
      // return CATLONG32 = 0 : couldn't converge -> throw error.
      //             = 1 : OK, keep working on the current result that contains no more twist and,
      //                    after replacing first point of twist using interpolation on current,
      //                    store the twist following.
      //             = 2 : OK, store the twist before working on the current result that may contain
      //                    some more twist.
      //             = 3 : OK, no need to work on the current result : it is completely twisted and
      //                    store the twist.
      // iResultIndex is the current result we're working on
      // Sets of Points are the data to build the piece of the twist part.
      virtual CATLONG32 TwistExtremities(CATLONG32              iResultIndex,
                                         CATMathSetOfPointsND & oParameters,
                                         CATMathSetOfPointsND & oPoints,
                                         CATMathSetOfPointsND & oTangents,
                                         CATMathSetOfPointsND & oSecondDerivatives);

      // Optional smooth (enabled by default - see ToggleSmoothing())
              void      Smooth          (CATGeoFactory        * iFactory   ,
                                         double                 iSmoothTol ,
                                         CATMathSetOfPointsND & iParameters,
                                         CATMathSetOfPointsND & ioPoints   ,
                                         CATMathSetOfPointsND & ioTangents ,
                                         CATMathSetOfPointsND & ioSecondDerivatives);


      //-----------------------------------------------------------------------
      // Data.
      //-----------------------------------------------------------------------
      // Input data.
      CATCurve          *const _Curve;
      CATCrvLimits             _CurveLimit;
      CATSurface             * _OriginCrvSupport;
      CATLONG32                _OriginSupportOrient;
      CATSurface             * _Support;
      CATSurLimits             _SupportLimit;
      CATLONG32                _side;
      CATLONG32                _orient1,
                               _orient2;

      CATParallelConnectTool * _tool;
      CATBoolean               _loop;

      CATBoolean               _HasBeenRunInReportInit;
      CATCrvLimits             _DomainForExtrapol;

      // TWIST
      CATMathSetOfLongs      * _IsTwisted; 
      CATBoolean               _TwistFound;
      CATLONG32                _TwistIndex;
      double                   _TwistParam;
      CATMathSetOfLongs      * _IsOverlapped;

      double                   _GlobalTolerance;
      CATBoolean               _SmoothEnabled;
      CATBoolean               _PointSolEnabled;
      CATBoolean               _IsEuclidean;

      //                                      Tolerances (_TOL_INTERPOL, _TOL_SMOOTH). Documentation NLD120417
      //                                      ----------
      //                                      - initialisees par les classes filles au 110417. NLD
      //                                      - apparition le 14/11/02 par KLX (a qui j'ai envie de mettre des claques chaque fois que je vois son code)
      //                                        avec une gestion initiale deleguee aux classes filles aussi pourrie qu'elle est a ce jour
      //                                      - ces tolerances sont homogenes et prennent toutes deux la puissance 1 de l'echelle
      //                                      - DO NOT USE _TOL_INTERPOL directly as a tolerance for CATMathInterpol family in AdvancedMathematics
      //                                        (the real interpolation toleance must be deduced with a square value,
      //                                         which may be done by a dedicated and specific GeometricOperators software
      //                                         as CATGeodesicParallelCheapInterpol)
      double                   _TOL_INTERPOL;
      double                   _TOL_SMOOTH;

      CATLONG32                _Config;
      CATLONG32              * _Configs;

      // Explicit solve data (euclidian only - no effect for geodesic cases)
      CATBoolean               _TryExplicitSolve;
   };

#endif

