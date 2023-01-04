//=========================================================================
// COPYRIGHT DASSAULT SYSTEMES 1999
//=========================================================================
//
// CATEuclidianParallelComputer:
//   Implementation of Euclidian Parallel Operator.
//
//=========================================================================
// Usage notes:
//=========================================================================
// 11/04/17 NLD Mise au propre. smart indent
//              XScaleRules for SetTolerance()
// 22/06/20 S9L Hard coded value of dimension replaced by variable for 
//                possible extension over higher dimension
//=========================================================================

#ifndef CATEuclidianParallelComputer_h
#define CATEuclidianParallelComputer_h

#include "Connect.h"
#include "CATParallelComputer.h"

#include "CATSurLimits.h"
#include "CATCrvLimits.h"

#include "CATMathDef.h"
#include "CATMathIntervalND.h"

#include "CATMathDirection.h"

#include "CATBoolean.h"

class CATEuclidianParallelEquation;
class CATGeoFactory;
class CATSurface;
class CATCurve;
class CATPurve;
class CATCrvParam;
class CATMathSetOfPointsND;
class CATMathSetOfPointsNDWithVectors;
class CATSoftwareConfiguration;
class CATMathAttrList;
class CATMathAttrRepartition;
class CATMathAttribute;
class CATMathIntervalND;
class CATMathVectorialFunctionX;


//-------------------------------------------------------------------------
class ExportedByConnect CATEuclidianParallelComputer : public CATParallelComputer
{
public:
   //-----------------------------------------------------------------------
   // Object Management.
   //-----------------------------------------------------------------------
   CATEuclidianParallelComputer(CATSoftwareConfiguration        * iConfig         ,
                                CATGeoFactory                   * iFactory        ,
                                CATCurve                        * iCurve          ,
                                CATCrvLimits                    & iCurveLimit     ,
                                CATLONG32                         iOrientationEdge,
                                CATBoolean                        iExtrapolEdge   ,
                                CATSurface                      * iSupport        ,
                                CATSurLimits                    & iLimit          ,
                                CATLONG32                         iOrientationSur ,
                                CATBoolean                        iExtrapolSur    ,
                                CATParallelConnectTool          * iTool           ,
                                CATMathSetOfPointsND            * iInitPoints     ,
                                CATBoolean                        iLoopSearch     = 0);
   
   ~CATEuclidianParallelComputer();
   
   //-----------------------------------------------------------------------
   // Public methods.
   //-----------------------------------------------------------------------
   // Donner la tolerance globale
   // la tolerance recue doit prendre la puissance 1 de l'echelle. NLD110417
   virtual void SetTolerance (double tol = -1.);
   
   int        Run();
   CATBoolean ReportInit (const CATGeometry                     * iReportGeometry       ,
                          const CATLONG32                         iReportID             ,
                                double                          * ioInitPoint           ,
                                double                          & ioInitParam           ,
                                CATBoolean                      & oSmallDeformation     ,
                          const CATCrvLimits                    * iReportGeometryLimits);

   void       Interpol   (const CATMathFunctionX                * iF[3]                  ,
                          const CATMathFunctionXY               * iG[3]                  ,
                          const CATLONG32                         iOrientationF          ,
                          const CATLONG32                         iOrientationG          ,
                                CATMathSetOfPointsNDWithVectors * iSet                   ,
                                CATMathSetOfPointsND            & oParameters            ,
                                CATMathSetOfPointsND            & oPoints                ,
                                CATMathSetOfPointsND            & oTangents              ,
                                CATMathSetOfPointsND            & oSecondDerivatives     );

  // If TryExplicitSolve has been set (see CATParallelComputer), and an explicit solution has been computed,
  // this method allows to get the result as a quintic vectorial function. A null pointer is returned otherwise.
  CATMathVectorialFunctionX * GetEuclidianQuinticX();
   
private:
   //-----------------------------------------------------------------------
   // Private methods.
   //-----------------------------------------------------------------------
   CATMathSetOfPointsNDWithVectors * ComputeInit();
   // if the results are almost confused in one point search if it is
   // the result of the parallele of a circle on a plane to its center.
   CATBoolean AnalyseAndSimplifyResults();

   // Check the inversion of sgnature to split the results if necessary
   void ComputeSignatureAndUpdateResults();

   // Compute Init points for the homogeneous equation system
  CATMathSetOfPointsNDWithVectors * ComputeHomogeneousInit();

  // Main steps of the run
  void       RunMarching               (CATMathSetOfPointsND   *  init         ,
                                        CATMathAttrList         & iMarchOptions,
                                        CATMathAttrRepartition *  iRepartition);
  void       RunPostMarchingTreatments ();
  void       BuildOptimalDomain        ();
  void       BuildImplicitSystem       (CATLONG32              *  iDimArray ,
                                        CATLONG32               & oNbOptions,
                                        CATMathAttribute      **& oMarchAttr,
                                        CATMathIntervalND       & oMaxDomain,
                                        CATMathAttrRepartition *& RepartitionPtr);


  int        SolveByProjection(CATMathSetOfPointsNDWithVectors *& iopInitPoints);

  // Internal method used to manage difficult cases where the radius law has zeroes.
  // This method is only usefull for PLine input curve lying on plane support.
  void       ApplyOffset(CATMathSetOfPointsND * init);

  //
  // Explicit solving dedicated methods (see CATParallelComputer TryExplicitSolve method)
  //

  // Global run method. Returns 1 if succeeded, 0 otherwise (irrelevant configuration, deep failure, etc.).
  int        RunExplicit();

  // Initialization method: returns 0 if explcit solving is not possible, 1 otherwise.
  // In this case, calling ComputeExplicitSolution() is relevant.
  int        InitializeExplicitData();

  // Explicit solve computations. Returns 1 if succeeded, 0 otherwise
  int        ComputeExplicitSolution();

  // Storage of explicit result. Returns 1 if succeeded, 0 otherwise.
  int        StoreExplicitSolution(CATMathSetOfPointsND * iCurveParams,
                                   CATMathSetOfPointsND * iPoints2D,
                                   CATMathSetOfPointsND * iTangents2D,
                                   CATMathSetOfPointsND * iSecondDeriv2D,
                                   CATMathSetOfPointsND * iQuinticParams);
  
  // Quality checks on current explicit solution at _DistanceTol tolerance.
  // Returns TRUE if the quintic interpolation of input data lead to a resulting
  // curve that does not deviate more than iDistanceTol from theoritical solution.
  // Returns FALSE if quality is not good enough.
  //
  // oEvalOK is an output diagnostic: 1 means everything is OK, 0 means
  // that a deep error occured.
  //
  // NB.: _Nsub controls the number of sub-evaluations to evaluate quality; _NewtonStep the number of
  //      steps of quality loop.
  CATBoolean CheckQuality(CATMathSetOfPointsND *& ioCurveParams,
                          CATMathSetOfPointsND *& ioPoints2D,
                          CATMathSetOfPointsND *  iTangents2D,
                          CATMathSetOfPointsND *  iSecondDeriv2D,
                          CATMathSetOfPointsND *  iQuinticParams,
                          CATLONG32 & oEvalOK);

  CATBoolean CheckInjectivity(CATMathSetOfPointsND * iCurveParams);

//======================================================================
// DATA
//======================================================================
  CATPCurve *                   _OriginPCurve;
  CATLONG32                     _Dimension;
  double                        _DistanceTol;
  CATLONG32                     _Nsub       ,
                                _NewtonStep ,
                                _MaxSize    ;
  CATMathVectorialFunctionX *   _EuclidianQuinticX;
  CATMathDirection              _PlaneNormal; // For planar supports
	CATSurLimits								  _OriginalSurLimits; // Save original limits for the planar supports
  CATBoolean                    _IsAllZeroLaw;
};

#endif

