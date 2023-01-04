//=========================================================================
// COPYRIGHT DASSAULT SYSTEMES 1999
//=========================================================================
//
// CATGeodesicParallelComputer:
//   Implementation of Geodesic Parallel Operator.
//
//=========================================================================
// Usage notes:
//=========================================================================
// 11/04/17 NLD Detabulation. Mise au propre. Regroupement des donnees
//              XScaleRules for SetTolerance() and _TOL_PTDIR
//=========================================================================
#ifndef CATGeodesicParallelComputer_h
#define CATGeodesicParallelComputer_h

#include "Connect.h"
#include "CATParallelComputer.h"
#include "CATBoolean.h"
#include "CATListOfDouble.h"

class CATMathVectorialFunctionX;
class CATMathQuickDiscretizeFunctionX;
class CATMathPoint;
class CATMathVector;
class CATSoftwareConfiguration;

//-------------------------------------------------------------------------
class ExportedByConnect CATGeodesicParallelComputer : public CATParallelComputer
{
public:
   //-----------------------------------------------------------------------
   // Object Management.
   //-----------------------------------------------------------------------
   CATGeodesicParallelComputer(CATSoftwareConfiguration        * iConfig,
                               CATGeoFactory                   * iFactory,
                               CATCurve                        * iCurve,
                               CATCrvLimits                    & iCurveLimit,
                               CATLONG32                         iOrientationEdge,
                               CATBoolean                        iExtrapolEdge,
                               CATSurface                      * iSupport,
                               CATSurLimits                    & iLimit,
                               CATLONG32                         iOrientationSur,
                               CATBoolean                        iExtrapolSur,
                               CATParallelConnectTool          * iTool,
                               CATMathSetOfPointsND            * iInitPoints,
                               CATMathQuickDiscretizeFunctionX * iFunction,
                               CATBoolean                        iLoopSearch=0);
   
   ~CATGeodesicParallelComputer();
   
   //-----------------------------------------------------------------------
   // Public methods.
   //-----------------------------------------------------------------------
   
  virtual CATMathQuickDiscretizeFunctionX * GetExplicitSystem();

   // Set or override default tolerances (see below)
   //   Compute local tolerances form one unique geodesic tolerance
   // la tolerance recue doit prendre la puissance 1 de l'echelle. NLD110417
   void SetTolerance (double ParallelTolerance = -1);
   
   int Run();

   CATBoolean ReportInit(const CATGeometry                     * iReportGeometry,
                         const CATLONG32                         iReportID      ,
                         double                                * ioInitPoint    ,
                         double                                & ioInitParam    ,
                               CATBoolean                      & oSmallDeformation,
                         const CATCrvLimits                    * iReportGeometryLimits);
   
   void       Interpol  (const CATMathFunctionX                * iF[3]          ,
                         const CATMathFunctionXY               * iG[3]          ,
                         const CATLONG32                         iOrientationF  ,
                         const CATLONG32                         iOrientationG  ,
                               CATMathSetOfPointsNDWithVectors * iSet           ,
                               CATMathSetOfPointsND            & oParameters    ,
                               CATMathSetOfPointsND            & oPoints        ,
                               CATMathSetOfPointsND            & oTangents      ,
                               CATMathSetOfPointsND            & oSecondDerivatives);
   
  // ST5 begin modifs

  // Fill in a list of double with Knots presence proportions on each interval of the
  // wire divided in 10 uniform intervals; then compute a List of parameters where a
  // refinement is done in the wire portion containing more than 89% of Knots.
  // For QuickSampling purpose (IR on discretization..)

  void RetrieveKnotsRepartition(CATListOfDouble& ioListOfKnotsProportion);
  void ComputeListOfDiscrParam(CATListOfDouble & iListOfKnotsProportion, 
                               CATListOfDouble & oListOfDiscrParam);

  // ST5 end modifs

protected:
// computation of twist extremities : caution this method can modify the number of results
// return CATLONG32 = 0 : couldn't converge -> throw error.
//             = 1 : OK, keep working on the current result that contains no more twist and,
//                    after replacing first point of twist using interpolation on current,
//                    store the twist following.
//             = 2 : OK, keep working on the current result that contains no more twist and,
//                    after replacing last point of twist using interpolation on current,
//                    store the twist before.
//             = 3 : OK, no need to work on the current result : it is completely twisted and
//                    store the twist.
// iResultIndex is the current result we're working on
// Sets of Points are the data to build the piece of the twist part.
   CATLONG32 TwistExtremities(CATLONG32              iResultIndex,
                              CATMathSetOfPointsND & oParameters ,
                              CATMathSetOfPointsND & oPoints     ,
                              CATMathSetOfPointsND & oTangents   ,
                              CATMathSetOfPointsND & oSecondDerivatives);


private:
   CATMathSetOfPointsND *ComputeInit( CATMathInterval &CurveDomain );
   //int ReconvergedInit(double *ioParam, CATPCurve *pcurve );
   
   CATBoolean Extrapol     (double               * iParameters  ,
                            CATMathPoint         * iPoints      ,
                            CATMathVector        * iTangents    ,
                            CATMathVector        * iSecondDerivatives,
                            double               & oParameter   ,
                            CATMathPoint         & oPoint       ,
                            CATMathVector        & oTangent     ,
                            CATMathVector        & oSecondDerivative,
                            CATLONG32              iDirection   );
   
  void        TwistInterpol(double                 PtBeforeTwist,
                            double                 PtAfterTwist ,
                            CATMathSetOfPointsND & ioParameters ,
                            CATMathSetOfPointsND & ioPoints     ,
                            CATMathSetOfPointsND & ioTangents   ,
                            CATMathSetOfPointsND & ioSecondDerivatives,
                            double               * oAddedPt1    ,
                            double               * oAddedTan1   ,
                            double               * oAddedPt2    ,
                            double               * oAddedTan2   );

   // return CATLONG32 = 0 : couldn't converge -> throw error
   //             = 1 : not twisted
   //             = 2 : twisted
   CATLONG32 IsTwistPoint(double iPoint, double iStep = 0.1);

   // void Smooth(CATGeoFactory        * iFactory   ,
   //             CATMathSetOfPointsND & iParameters,
   //             CATMathSetOfPointsND & ioPoints   ,
   //             CATMathSetOfPointsND & ioTangents ,
   //             CATMathSetOfPointsND & ioSecondDerivatives);
   //    same for euclidean and geodesic : now in mother class (klx)

  void ComputeOptimumDomain();

//======================================================================
// DATA
//======================================================================
protected:
   // Parametres, tolerance locale
   //
   CATLONG32                         _GEODPAR_NBINIT;         // Nombre minimal de point-dir a lancer pour une parallele
   double                            _TOL_PTDIR;              // Tolerance pour le calcul d'un point dir. Suit la puissance 0 de l'echelle. NLD110417



private:
   CATBoolean                        _DestroyInit;

   CATMathQuickDiscretizeFunctionX * _ExplicitFunction;



};

#endif

