//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
//
// CATMathInterpol:
//
//   Base abstract class for quintic polynomial C2 interpolation of an object
//   after a marching algorithm, with reconvergence on the parameters to 
//   have the best possible interpolation.
//
//=============================================================================
// Usage notes:
//
//  This base class combines generic methods for an implicit or an explicit
//  interpolation. You must choose the appropriate available subclass
//  according to your needs :
//       - CATMathCleverInterpol   after an implicit marching 
//    or - CATMathExplicitInterpol after an explicit discretization.
//
//  The number of subelements generated tries to be as small as possible, with 
//  the constraint on the tolerance for the Quality evaluator.
//
// XScaleRules:                                                                                 (NLD021213)
//  - there is no ScaleOption (of typeCATMathAttrScaleOption) describing the vectorial function :
//    scale behaviour is imposed
//  - domains          must behave  like power 1 of factory scale
//  - parameters       must behave  like power 1 of factory scale
//  - points computed  must behave  like power 1 of factory scale
//  - steps  computed  must behave  like power 1 of factory scale
//  - quality computed      behaves like power 2 of factory scale
//  - error   computed      behaves like power 2 of factory scale
//=============================================================================
// 22/05/08 NLD Suppression des arguments par defaut, commentaires
//              sur l'usage des tolerances
// 09/07/12 NLD GetDistanceAtRatio() renommée GetSquareDistanceAtRatio()
//              FindC1Discontinuity() devient privée et son code de retour de type CATMathC1Disc_Diag
// 13/07/12 NLD Ajout RunParallelDebug(), _OKScaleReviewed, SetOKScaleReviewed()
// 16/07/12 NLD Ajout InitTolerances()
// 17/07/12 NLD Smart Indent (1)
// 02/12/13 NLD Ajout XScaleRules
//              Smart Indent (2)
// 19/05/15 jsx Remontee des methodes privees avant les donnees
//              RemovePointsPrivate() remplace RemovePoints()
// 25/01/16 KJD Addition of the define CATMathInterpol_AdvQualityComparison (off by default)
// 14/04/17 NLD Ajout CATMathInterpolDebug
//              Documentation des valeurs pirates de CheckComponent()
// 08/06/18 NLD Ajout ComputeQualityOpt()
//              Ajout StorePointData()
// 08/08/18 F4E Ajout IsTooBigSecondDeriv()
// 13/09/18 F4E CATMathInterpolDebug class moved to \YN000FUN.m\LocalInterfaces\CATMathInterpolDebug.h
//=============================================================================


#ifndef CATMathInterpol_h
#define CATMathInterpol_h

#include "YN000FUN.h"

#include "CATMathDiagnostic.h"
// #include "CATMathDef.h"
#include "CATListOfInt.h"
#include "CATCGMVirtual.h"
// #include "CATTolerance.h"
#include "CATMathImplicitSystem.h"

class CATMathSetOfPointsNDWithVectors;
class CATMathSetOfPointsND;
class CATMathPoint;
class CATMathIntervalND;
class CATMathQuinticX;
class CATMathFunctionXY;
class CATMathSetOfLongs;
class CATSoftwareConfiguration;
class CATMathInterpolDebug;
// #define CATMathInterpol_AdvQualityComparison
class CATMathDef;
class CATTolerance;



class ExportedByYN000FUN CATMathInterpol : public CATCGMVirtual
{
  CATCGMVirtualDeclareClass(CATMathInterpol);

  friend class CATMathInterpolDebug;
public:

// -----------------------------------------------------------------------
//  Object Management
// -----------------------------------------------------------------------
/**
 * Constructor
 *  iTolerance = the maximum gap between the piecewise quintic result,
 *               and the theoretical exact solution.
 * (XScaleRules) Must behave like squared value of factory scale
 *               Non null negative value: the standard 1E-10 value will be used
 *               taking factory scale into account
 *               (or 1E-4*SquareFactoryResolution)
 *  iAcceptableTolerance = the acceptable gap in singular contexts.
 /               if null, value will be equal to the tolerance deduced from iTolerance
 */
                     CATMathInterpol           (      CATSoftwareConfiguration *  iConfig              ,
                                                const CATLONG32                   iN                   ,
                                                      CATMathImplicitSystem    *  iSystem              ,
                                                const CATMathIntervalND        *  iDomain              ,
                                                const double                      iTolerance           ,
                                                const double                      iAcceptableTolerance ,
                                                const CATTolerance              & iTolObject           );

/**
 * Destructor
 */
  virtual            ~CATMathInterpol          ();

/**
 * Tolerances initialization with input values or default values if input values inconsistency
 */
  static  void       InitTolerances            (const double                     iTolerance           ,
                                                const double                     iAcceptableTolerance ,
                                                const CATTolerance             & iTolObject           ,
                                                      double                   & oTolerance           ,
                                                      double                   & oAcceptableTolerance
                                               );

// -----------------------------------------------------------------------
//  Settings
// -----------------------------------------------------------------------

/**
 * Avoid the calculation of additional points when the tolerance
 * is not reached.
 */
          void       DisableInsertion          ();


/**
 * Enable or disable the reconvergence on DeltaParam to optimize
 * the quality. This feature is on by default.
 */
          void       SetBestParametrization    (      CATBoolean                 iEnable              );

/**
 * Reconvergence-skipping factor.
 * Consider that no reconvergence is needed when the quality at the middle
 * of the arc is < Tolerance * Factor.
 */
          void       SetTolQualityFactor       (      double                     Factor               = 0.1);

/**
 * Force the given points to be used as interpolation points. 
 * It is the responsaiblity of the caller to delete iTabIndex.
 */
          void       SetExactPoints            (const CATLONG32               *  iTabIndex            ,
                                                const CATLONG32                  iNbIndex             ,
                                                      CATLONG32               *  oTabOfIndexExit      = 0);

/**
 * Set up the maximum square norm for a second derivative
 * (whenever a too big norm is computed, the second derivative will
 * be set to 0.)
 */
          void       SetMaxSquareSecondDeriv   (      double                     iMaxSquareSecondDeriv);

/**
 * Avoid the creation of arcs whose norm is too small,
 * and set up the minimal acceptable distance.
 */
          void       SetInternalMinLength      (      double                     iInternalMinLength   );

/**
 * Enable the possibility of skipping more than 9 points during
 * the interpolation.
 */
          void       SetSkipAll                (      CATBoolean                 iSkipAll             = 1);

/**
 * Activate the cleaning of data a the end of the interpolation.
 * Only the start and end points will be affected.
 */
  virtual void       SetCleanOutput            (      CATBoolean                 iCleanOutput         = 1);

/**
 * Activate PointRemovalAfterInterpol mode.
 * Sometimes unnecessary points are added during interpolation, so
 * the caller must activate this option to get cleaner results.
 * Please use it whenever possible (a versionning may be required)
 */
          void       SetPointsRemoval          (      CATBoolean                 iPointsRemoval       = 1);
  
/**
 * Maximum depth for point insertion (default value is 3).
 * If PointRemoval mode is ON (previous method), you can also specify
 * an additional depth (default is 0), that will allow the algorithm to
 * insert more points if the extra depth tolerance is not reached.
 * If Strategy == 0, this extra depth will be used only for a ponctual
 * difficulty. If 1, everytime (recommended).
 * If iExtraTolerance = 0., the default value is the Acceptable Tolerance.
 */
          void       SetMaxDepth               (      CATLONG32                  iMaxDepth             = 3,
                                                      CATLONG32                  iExtraAcceptableDepth = 0,
                                                      double                     iExtraTolerance       = 0.,
                                                      CATLONG32                  iStrategy             = 0,
                                                      double                     iMinLength            = -1.);

/**
 * Activate the detection of C1 discontinuities.
 * This is a DEPRECATED method. Please use SetCutOnC1Discontinuities() instead (see below).
 * If this method is called:
 *   1) Unnecessary points are removed after the interpolation (which can occur even if the solution is C1).
 *   2) Discontinuity detection is launched where the tolerance could not be reached. If a discontinuity is
 *   found, the solution is cut. The different pieces can then be retrieved in two ways:
 *              -- The CATMathSetOfPointsNDs given as arguments to Run() contain all the pieces: each
 *                 discontinuity correspond to two almost confused points (one on each adjacent piece) 
 *                 with different tangents and second derivatives. The indices of these points can be retrieved
 *                 with GetC1Discontinuities().
 *              -- Each piece can be retrieved separately with GetPiece().
 */
  virtual void       SetC1DiscontinuitiesDetection();

/**
 * Set the tolerance for C1 discontinuity.
 * If the angle between the tangent at the left and the tangent at the right of a discontinuity
 * is greater than this tolerance, the solution will be cut at this point.
 * For example, take iSinAngleTol = 8.7265e-3 for 0.5 degrees.
 * Do not use simultaneously with SetC1DiscontinuitiesDetection()
 * This is the ADVISED method. You must overload ComputeAngleAtDiscontinuity, see below.
 */
          void       SetCutOnC1Discontinuities (      double                     iSinAngleTol          );

/**
 * Set Energy controls on/off.
 * If on, the energy of a given arc will never be > 1 whenever possible.
 * This has an influence on the final parametrization.
 * Default is 1 for clever, 0 for explicit.
 */
          void       SetCheckEnergy            (      CATBoolean                 iBool                 );

/**
 * Activate the detection of arcs going outside of the input domain.
 * The indexes of invalid arcs will be provided by GetInvalidArcs (see below).
 * Do not overload BestInterpol for this to work.
 */
          void       SetDetectInvalidArcs      (      CATLONG32                  iEnable               =  1 ,
                                                      double                     iTolerance            = -1.);


/**
 * At each step, try to compute a better parametrization in order to avoid
 * the creation of arcs going outside of the domain -- if possible. 
 * This is experimental for the moment. Do not overload BestInterpol for this to work.
 * Do not use SetDetectInvalidArcs at the same time.
 * You can be informed of the failure of this treatment by using GetInvalidArcs
 * (see below).
 * NOT RECOMMANDED : this will lead to bad parameterizations and has a limited gain.
 */
          void       SetTightenArcIntoDomain   (      CATLONG32                  iEnable               =  1   ,
                                                      double                     iTolerance            = -1.  );



// -----------------------------------------------------------------------
//  Get Information After Run
// -----------------------------------------------------------------------


/**
 *                                                           (homogeneous to power 2 of factory scale)
 * Retrieve the max error noticed during the interpolation process.
 * If this returns a highest error than the tolerance (or the acceptable tolerance),
 * it means that the maximum insertion level has been reached, or the computation
 * of additionnal points has failed. You should consider to refine your initial
 * discretization.
 * Please notice that the error calculation is based on a discretization process
 * and not on an maximization algorithm.
 */
          double     GetMaxError               ();

/**
 * Discretizes the input result piece then compute its maximum error.
 * Although this method gives a more reliable result than the previous one,
 * it is not based on an maximization algorithm. So not very stable, but still
 * informative.
 * The deviation is another indicator. On each arc, the square distance between the middle
 * point and this point after reconvergence is comuted thanks to GetSquare3DDistance
 * and the maximal value found is returned to the caller.
 */
          void       ComputeMaxError           (      CATMathSetOfPointsND     & iParameters           ,
                                                      CATMathSetOfPointsND     & iPoints               ,
                                                      CATMathSetOfPointsND     & iTangents             ,
                                                      CATMathSetOfPointsND     & iSecondDerivatives    ,
                                                      CATMathSetOfPointsND     *  iCorrespondingParams  ,
                                                      double                   & oMaxErr               ,
                                                      double                   & oMaxSquareDev         ) ;

/**
 * Retrieve the number of discontinuities that have been detected.
 * Useful only if SetC1DiscontinuitiesDetection() has been called.
 * The number of pieces is equal to this number plus 1.
 */
  virtual int        GetNbOfC1Discontinuities  ();

/**
 * Retrieve the indices of discontinuities in the CATMathSetOfPointsNDs given as arguments to Run().
 * Useful only if SetC1DiscontinuitiesDetection() has been called.
 * The table ioC1Discontinuities must be allocated (size: Nb of discontinuities).
 * Piece number i starts at point ioC1Discontinuities[i - 1] and ends at point ioC1Discontinuities[i] - 1
 */
  virtual void       GetC1Discontinuities      (      int                     *  ioC1Discontinuities   );


/**
 * Retrieve the indexes of arcs going outside of the domain.
 * The first arc has index 1.
 * This only works with SetTightenArcIntoDomain or SetDetectInvalidArcs modes.
 */
          void       GetInvalidArcs            (      CATMathSetOfLongs        & oIndexes              );


// -----------------------------------------------------------------------
//  Get Piece By Piece Result
// -----------------------------------------------------------------------

/**
 * Retrieve a given piece.
 * Useful only if SetC1DiscontinuitiesDetection() has been called.
 * We must have:
 *  0 <= iIndex <= NbOfC1Discontinuities
 *  iParameters, iPoints, iTangents, iSecondDerivatives must be the arguments passed to (and filled by) Run()
 *  oParametersPiece, oPointsPiece, oTangentsPiece, oSecondDerivativesPiece must be of correct dimensions
 *  and are filled with data corresponding to the given piece (parameters start at 0 for each piece).
 */
  virtual void       GetPiece                  (      int                        iIndex                ,
                                                      CATMathSetOfPointsND     & iParameters           ,
                                                      CATMathSetOfPointsND     & iPoints               ,
                                                      CATMathSetOfPointsND     & iTangents             ,
                                                      CATMathSetOfPointsND     & iSecondDerivatives    ,
                                                      CATMathSetOfPointsND     & oParametersPiece      ,
                                                      CATMathSetOfPointsND     & oPointsPiece          ,
                                                      CATMathSetOfPointsND     & oTangentsPiece        ,
                                                      CATMathSetOfPointsND     & oSecondDerivativesPiece);


  virtual CATLONG32  GetDiagnostic();


protected:

// -----------------------------------------------------------------------
//  Functionnal Evaluators
// -----------------------------------------------------------------------

/**
 * Retrieve data from the initial set.
 */
  virtual void       GetDataFromISet           (      CATMathSetOfPointsND     & iSet                  ,
                                                      CATLONG32                  iPos                  ,
                                                      double                  *  oParam                = 0,
                                                      double                  *  oP                    = 0,
                                                      double                  *  oT                    = 0) = 0;

/**
 * Retrieve or compute point from the initial set.
 */
  virtual void       GetPointFromISet          (      CATMathSetOfPointsND     & iSet                  ,
                                                      CATLONG32                  iPos                  ,
                                                      double                  *  oParam                = 0,
                                                      double                  *  oP                    = 0) = 0;

/**
 * Compute and store data for the specified quintic.
 */
  virtual void       ComputeQuintic            (const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                const double                  *  iC1                   ,
                                                const double                     iDeltaParam           );

/**
 * Eval current quintic.
 */
  virtual void       EvalQuintic               (const double                     iParam                ,
                                                      double                  *  oFX                   );


public:
/** 
 * Compute point, tangent and second derivative in the dimension of
 * interpolation. Point and tangent computed in the dimesion of marching
 * may have to be given as inputs.
 * iOrientation = -1 for a derivative on the left, 1 on the right and 0 
 *   for both sides.
 */
  virtual void       ComputeData               (      double                     iParam                ,
                                                      double                  *  ioP                   ,
                                                      double                  *  ioT                   ,
                                                      double                  *  ioC                   ,
                                                      int                        iOrientation          ) = 0;


// -----------------------------------------------------------------------
//  Quality Evaluators
// -----------------------------------------------------------------------

protected:
/** 
 * Compute the quality of the current arc at specified ratio. (homogeneous to power 2 of factory scale)
 */
  virtual double     Quality                   (const double                     iRatio                ,
                                                const double                     iParam0               ,
                                                const double                     iParam1               ,
                                                const double                     iDeltaParam           ,
                                                      CATBoolean               & ioCheckDomain         ) = 0;

/** 
 * Compute the quality of the specified arc at middle point. (homogeneous to power 2 of factory scale)
 */
  virtual double     QualityOpt                (const double                     iParam0,
                                                const double                     iParam1               ,
                                                const double                     iDeltaParam           ,
                                                      CATBoolean               & ioCheckDomain         ) = 0;

/** 
 * Compute and store internal data before one or more calls to QualityOpt.
 * This method is systematically called before QualityOpt.
 * iOnlyDelta = 1 if and only if only the delta parameter has changed since
 * last call.
 */
  virtual void       PrepareQualityOpt         (const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                const double                  *  iC1                   ,
                                                const double                     iDeltaParam           ,
                                                      CATBoolean                 iOnlyDelta            ) = 0;

/** 
 * Compute quality, with intermediate storage.               (homogeneous to power 2 of factory scale)
 * through PrepareQualityOpt() and QualityOpt() methods
 * not a virtual method; not to be derived.
 */
          double     ComputeQualityOpt         (const double                     iParam0               ,
                                                const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                const double                     iParam1               ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                const double                  *  iC1                   ,
                                                const double                     iDeltaParam           ,
                                                      CATBoolean                 iOnlyDelta            ,
                                                      CATBoolean               & ioCheckDomain         );

 
 /**
 *  kjd 21AUG2007 : RI593816
 * Method which  intervenes in the check process of the quality of the current arc.
 * This method can be overriden to implement a sampling capturing more efficiently a possible local treatment
 * (for instance in the case of a CATVariableFillet).
 *  (void default implementation)
 */
  virtual void UpdateSamplingForQualityCheck(CATLONG32 iNbSample, 
                                                const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                const double                  *  iC1                   ,
                                                const double                     iDeltaParam           ,
                                                      CATMathSetOfPointsND     & oSetOfRatio           );


/** 
 * Point checker (called on the first point only).
 */
  virtual void       CheckValidityOfPoint      (      CATMathSetOfPointsND     & iSet                  ,
                                                const double                  *  iP                    ,
                                                      double                  *  ioT                   ,
                                                      double                  *  ioC                   ,
                                                      double                     iCosMin               ,
                                                      CATBoolean               & oIsSingularLeft       ) = 0;

/** 
 * Point checker (called on the end point and on each required point).
 */
  virtual void       CheckValidityOfLastPoint  (const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iP1                   ,
                                                      double                  *  ioT1                  ,
                                                      double                  *  ioC1                  ,
                                                      double                     iCosMin               ,
                                                      CATBoolean               & oIsSingularRight      ) = 0;

/**
 * Compute the cosinus of the angle between the two vectors.
 * The vectors must be normalized, and are given in the dimension of the functionnal
 * evaluator (implicit system). You must overload this method if you plan to use
 * SetCutOnC1Discontinuities.
 */
  virtual double     Compute3DCosAngle         (const double                  *  iP0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iT1                   );

// -----------------------------------------------------------------------
//  Quality Control And Parametrization Management
// -----------------------------------------------------------------------

/**
 * Increase the quality control (must be called once before RunMain).
 * If the quality of the current arc is between CarefulRatio * Tolerance and Tolerance, the discretization
 * will be increased to ensure that the tolerance is really not reached.
 * This method also specifies that the whole quintic is required to estimate the quality at a given point
 * (i.e. PrepareQualityOpt will calculates it and be called inside the Interpol method).
 * (XScaleRules) iNewTolerance must behave like squared value of factory scale
 *               Non null negative value: the standard 1E-4 value will be used
 *               taking factory scale into account

 */
          void       SetIncreaseQualityControl (      double                     iNewTolerance         ,
                                                      double                     iNewAcceptableTolerance,
                                                      double                     iCarefulRatio         ,
                                                      CATLONG32                  iMaxDepth             );

/** 
 *                                                           (homogeneous to power 2 of factory scale)
 * Sample the interpolated arc and compute its maximum deviation.
 * The sampling will stop if the deviation at some point is greater than the acceptable tolerance,
 * except if you provide a non-null pointer for oDomainSqDist. In this case, you will get the maximum
 * square distance between the domain and the points sampled (0 if always inside domain).
 */
  virtual double     Interpol                  (const double                     iParam0               ,
                                                const double                     iParam1               ,
                                                const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                const double                  *  iC1                   ,
                                                const double                     iDeltaParam           ,
                                                const CATLONG32                  NbSample              ,
                                                const CATBoolean                 iEasyInterpol         ,
                                                      double                  *  oDomainSqDist         = NULL);

/** 
 *                                                           (homogeneous to power 2 of factory scale)
 * In "Increase Quality Control" mode, sample the interpolated arc between the specified ratios
 * and compute its maximum deviation. (This method is called by the method Interpol.)
 */
  virtual double     InterpolAtStep            (const CATLONG32                  NbSample              ,
                                                const CATBoolean                 iEasyInterpol         ,
                                                const double                     alpha                 ,
                                                const double                     iRatioStart           ,
                                                const double                     iRatioEnd             ,
                                                const CATLONG32                  iDepth                );

/**
 * Compute the default value for the delta parameter (before reconvergence).
 */
  virtual double     InitializeDeltaParam      (const double                     iParam0               ,
                                                const double                     iParam1               ,
                                                const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                const double                  *  iC1                   ) = 0;


/** 
 * Minimize the function :
 *   DeltaParam |-> Quality_of_the_arc
 */
  virtual double     BestInterpol              (const double                     iParam0               ,
                                                const double                     iParam1               ,
                                                const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                const double                  *  iC1                   ,
                                                      double                   & oDeltaParam           ,
                                                const CATLONG32                  iNbSample             ,
                                                const CATBoolean                 iEasyInterpol         ,
                                                      CATLONG32                & oArcInfo              );

/**
 * Return the finite difference step to use during the minimization of the function
 *   DeltaParam |-> Quality_of_the_arc
 */
  virtual double     GetFiniteDifferenceStep   (      double                     iDeltaParam           ,
                                                      double                     iParam0               ,
                                                      double                     iParam1               ) = 0;


// -----------------------------------------------------------------------
//  Insertion Management
// -----------------------------------------------------------------------
  // Convergence info : pour un arc donne
  //         ATTENTION: la programmation a le mauvais gout de faire des tests d'inegalité
  //                    sur la valeur prise par l'information de convergence, et donc
  //                    de supposer cette liste ordonnée; en particulier, la valeur WatchArc
  //                    sépare le bon du moins bon.                                NLD100712
  // If changed please update CATMathInterpolDebug::TraceConvergenceInfo() in CATMathInterpolDebug.cpp    F4E091118
  enum ConvergenceInfo
  {
    NoPointAdded =  1,  // Les deux points extemites proviennent du set original
    GoodQuality  =  2,  // Au moins une des extremites a ete rajoutee et la qualite de l'arc est bonne
    WatchArc     =  0,  // Faire attention a cet arc (mauvaise qualite par rapport aux arcs voisins)
    MaxDepth     = -1,  // Pas de point ajoute parce qu'on en a deja ajoute beaucoup
    AddSolveKO   = -2,  // Pas de point ajoute en raison d'un solve KO
    AddSmallArc  = -3,  // Pas de point ajoute en raison d'un arc trop court
    AddCheckKO   = -4,  // Pas de point ajoute pour une autre raison
    AddSmallTL   = -5,  // Pas de point ajoute en raison d'une trop courte distance transverse
    TwistError   = -6,  // Fin du processus d'interpolation en raison d'un twist.
    WatchExtraD  = -7,  // Idem a WatchArc mais l'une des extremites a ete creee par ExtraDepth.
    ConvergenceInfoError = -99,
  };

/**
 * Compute a new point inside the arc, and do some various controls.
 * The point is chosen at the middle (by default or at _Lambda if set via SetMiddleValue()) in case of an implicit interpol,
 * or at parameter oParam in case of an explicit interpol.
 * The return value is 0 in case of success, -2 or another value < -2
 * corresponding to a failure diagnostic otherwise.
 */
  virtual enum ConvergenceInfo ComputeDataAtMiddle (  double                   & oParam                ,
                                                const double                     iParam0               ,
                                                const double                     iParam1               ,
                                                const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                const double                  *  iC1                   ,
                                                      double                     iMinLength            ,
                                                      double                  *  ioPHalf               ,
                                                      double                  *  ioTHalf               ,
                                                      double                  *  ioCHalf               ) = 0;

  /*
  * To set the _Lambda internal parameter.
  * It used in ComputeDataAtMiddle() in CleverInterpol case to change where the middle point is computed
  * At class construction _Lambda=0.5 thus middle point is compute at middle.
  * /!\\ If SetMiddleValue() method used _Lambda=iLambda: don't forget to use ResetMiddleValue() to go back to 0.5 /!\\
  * F4E260918
  */
  void SetMiddleValue(double iLambda);
  /*
  * To reset _Lambda internal parameter to 0.5 (see SetMiddleValue() documentation) F4E260918
  */
  void ResetMiddleValue();

  
/**
 * Return the discretization number to use to compute the deviation of the arcs
 * when splitting an arc. Default is 5.
 */
  virtual CATLONG32  GetNbSampleInAddPoint     ();

/**
 * Insert a middle point inside the arc and compute the interpolation on both parts.
 * The insertion process will be repeated with respect to the tolerance and a maximum depth.
 *  iInformation = (when iDepth > 1) 1 if the difficulty seems not to be pontual.
 *  iSqNorm      = quality of the input arc.
 *  return       = max quality between the two arcs.
 */
  virtual double AddPointAndInterpol(           const double                     iParam0               ,
                                                const double                     iParam1               ,
                                                const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                const double                  *  iC1                   ,
                                                const double                     iDeltaParam           ,
                                                      CATBoolean                 iIsSingularLeft       ,
                                                      CATBoolean                 iIsSingularRight      ,
                                                      CATMathSetOfPointsND     & oParameters           ,
                                                      CATMathSetOfPointsND     & oPoints               ,
                                                      CATMathSetOfPointsND     & oTangents             ,
                                                      CATMathSetOfPointsND     & oSecondDerivatives    ,
                                                      CATMathSetOfPointsND    *  oCorrespondingInitialParams,
                                                const CATLONG32                  iDepth                ,
                                                      CATLONG32                  iInformation          ,
                                                const double                     iSqNorm               ,
                                                      CATListOfInt            *  ioConvergenceInfo     );

// -----------------------------------------------------------------------
//  Small Arcs Management (Length Controls)
// -----------------------------------------------------------------------

/**
 * This method must be overrided in derived classes.
 * It returns the 3D square distance between two points of the implicit system.
 *
 * It is used to avoid creating small arcs or small patches, and the definition of the 3D distance
 * is linked to the definition of a small arc or patch:
 *      1)If one point of the implicit system correspond to one 3D point (intersection sur/sur for example), 
 *        the distance is simply the distance between the 3D points;
 *      2)If one point of the implicit system correspond to two 3D point (fillet for example), 
 *        let M and M' be the points corresponding to point P; then distance = max(dist(M0, M1), dist(M0', M1')) 
 *      3)In other cases the distance depends on the definition of the geometric element(s) to be created;
 *        For example for draft both sides, two surfaces are created. Taking same notations than above,
 *        if M is the common point to both surfaces,
 *        distance = min(max(dist(M0, M1), dist(M0', M1')) , max(dist(M0, M1), dist(M0'', M1'')))
 *
 * iP is the point of the implicit system (dimension _M).
 * ioPosition is used to store and retrieve intermediary data (often the 3D coordinates of the point(s))
 * iRequestData: 1 if it is useful to store the intermediary data in ioPosition
 *
 * Mechanism (example of intersection sur/sur): --if ioPosition == 0 and iRequestData == 1, compute the
 * 3D coordinates of the point from its uv coordinates (contained in iP), allocate ioPosition, fill it
 * with the 3D coordinates, and then return the square 3D distance;
 *                                             --if ioPosition != 0, retrieve the 3D coordinates from
 * ioPosition, and return the square 3D distance;
 * Memory deletion is managed by the caller.
 *
 * In cases 1 and 2 above, which are by far the most frequent, a simplified mechanism can be used:
 * 1) Call the method GetSquare3DDistance1 with same arguments and override the method
 *  virtual void Get3DPosition(const double * iP, CATMathPoint & oPosition);
 * 2) Call the method GetSquare3DDistance2 with same arguments and override the method
 *  virtual void Get3DPosition(const double * iP, CATMathPoint & oPosition0, CATMathPoint & oPosition1);
 *
 * See AAD for further explanations.
 */
  virtual double     GetSquare3DDistance       (const double                  *  iP0                   ,
                                                const double                  *  iP1                   ,
                                                      double                  *& ioPosition0           ,
                                                      double                  *& ioPosition1           ,
                                                      CATBoolean                 iRequestData0         ,
                                                      CATBoolean                 iRequestData1         ) = 0;

/**
 * iP is a point of the implicit system;
 * oPosition is its 3D position.
 * To be overriden only if you use method GetSquare3DDistance1 in the implementation of
 * the overriding of GetSquare3DDistance
 */
  virtual void       Get3DPosition             (const double                  *  iP                    ,
                                                      CATMathPoint             & oPosition             );

/**
 * iP is a point of the implicit system;
 * oPosition0 is the 3D position of the first corresponding 3D point.
 * oPosition1 is the 3D position of the second corresponding 3D point.
 * To be overriden only if you use method GetSquare3DDistance2 in the implementation of
 * the overriding of GetSquare3DDistance
 */
  virtual void       Get3DPosition             (const double                  *  iP                    ,
                                                      CATMathPoint             & oPosition0            ,
                                                      CATMathPoint             & oPosition1            );

/**
 * Possible implementation for GetSquare3DDistance.
 * NOT VIRTUAL ON PURPOSE
 */
          double     GetSquare3DDistance1      (const double                  *  iP0                   ,
                                                const double                  *  iP1                   ,
                                                double                        *& ioPosition0           ,
                                                double                        *& ioPosition1           ,
                                                CATBoolean                       iRequestData0         ,
                                                CATBoolean                       iRequestData1         );
/**
 * Possible implementation for GetSquare3DDistance.
 * NOT VIRTUAL ON PURPOSE
 */
          double     GetSquare3DDistance2      (const double                  *  iP0                   ,
                                                const double                  *  iP1                   ,
                                                double                        *& ioPosition0           ,
                                                double                        *& ioPosition1           ,
                                                CATBoolean                       iRequestData0         ,
                                                CATBoolean                       iRequestData1         );


// -----------------------------------------------------------------------
//  Acceptance Management (Transverse Length Controls)
// -----------------------------------------------------------------------

/**
 * Compute the Transverse Length of the specified arc.
 * Default is 2 * InternalMinLength * InternalMinLength
 * The algorithm will avoid creating any arc with a too
 * small transverse length.
 * iPoint is a buffer of dimension 6 * _N (pt, tan, snd der).
 */
  virtual double     GetSquareTransverseLength (const double                  *  iPoint                );

/** 
 * Acceptance of a point in a transverse length check context.
 * The default behaviour is : Quality < AcceptableTolerance.
 * See the second form below for more details.
 */
  virtual CATBoolean IsAcceptable              (const double                  *  iX                    );

/** 
 * Acceptance of an arc in a transverse length check context.
 * The default behaviour is : IsAcceptable for iNbSample equidistributed
 * points. If an arc does not pass this test, its will be divided into
 * arcs that may not satisfy the transverse length criterion, but will
 * ensure an acceptable quality for the result.
 */
  virtual CATBoolean IsAcceptable(              const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                const double                  *  iC1                   ,
                                                      double                     ialpha                ,
                                                      CATLONG32                  iNbSample             );


// -----------------------------------------------------------------------
//  Post Treatments Submethods
// -----------------------------------------------------------------------

/** 
 * In CleanOutput mode : checkup of a quintic component.
 * Return 0 if the component is ok,
 *        1 if the data should be recomputed,
 *        2 if one point should be removed
 *       10, 11 CAUTION: Bootleg values from specific derivation. NLD140417 comment, klx code (CATSurSurInterpol, CATMathInterpol::CleanOutputData)
 */
 
  virtual CATLONG32 CheckComponent(                   double                  *  iP0                   ,
                                                      double                  *  iT0                   ,
                                                      double                  *  iC0                   ,
                                                      double                  *  iP1                   ,
                                                      double                  *  iT1                   ,
                                                      double                  *  iC1                   ,
                                                      double                     iDeltaParam           );


// -----------------------------------------------------------------------
//  Main Steps Of The Algorithm
// -----------------------------------------------------------------------


/** 
 * Provide a guess of the index point to use to make the next arc.
 * Also provide min and max indexes with respect to the small arc
 * and required points management.
 */
  virtual CATLONG32 GetNextPoint               (      CATMathSetOfPointsND     & iSet                  ,
                                                      CATLONG32                  iCurrentPoint         ,
                                                      double                     iCosMin               ,
                                                      double                  *  iOldT                 ,
                                                      CATLONG32                & oMinPoint             ,
                                                      CATLONG32                & ioMaxPoint             ,
                                                      CATLONG32                & oMinPointTransverse   ,
                                                      CATBoolean               & oRequiredPoint        ,
                                                      CATLONG32                & oIndexExit            ,
                                                      double                   & oParam                ,
                                                      double                  *  ioP                   ,
                                                      double                  *  ioT                   ,
                                                      double                  *  ioC                   );

/** 
 * Compute and store the interpolation at position iCurrentPoint.
 * An initial guess for the next (maximal) index point is given by
 * ioTargetNewPoint.
 * The next point will be chosen as far as possible with respect to the 
 * tolerance and to the constraints iMinPoint, iMinPointTransverse.
 * Some additional points may be computed and added if necessary.
 */
          double     InterpolateWithinTol      (      CATMathSetOfPointsND     & iSet                  ,
                                                      CATMathSetOfPointsND     & oParameters           ,
                                                      CATMathSetOfPointsND     & oPoints               ,
                                                      CATMathSetOfPointsND     & oTangents             ,
                                                      CATMathSetOfPointsND     & oSecondDerivatives    ,
                                                      CATMathSetOfPointsND    *  oCorrespondingParams  ,
                                                      CATListOfInt            *  ioConvergenceInfo     ,
                                                      CATLONG32                  iCurrentPoint         ,
                                                      CATLONG32                  iMinPoint             ,
                                                      CATLONG32                & ioTargetNewPoint      ,
                                                      CATLONG32                  iMinPointTransverse   ,
                                                      double                     iParam0               ,
                                                      double                   & ioParam1              ,
                                                const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                      double                  *  iP1                   ,
                                                      double                  *  iT1                   ,
                                                      double                  *  iC1                   ,
                                                      CATBoolean                 iIsSingularLeft       ,
                                                      CATBoolean                 iIsSingularRight      );

/*
 * Store all point data.
*/
          void       StorePointData            (
                                                      // 1) sets in which storage must be done
                                                      CATMathSetOfPointsND     & oParameters           ,
                                                      CATMathSetOfPointsND     & oPoints               ,
                                                      CATMathSetOfPointsND     & oTangents             ,
                                                      CATMathSetOfPointsND     & oSecondDerivatives    ,
                                                      CATMathSetOfPointsND    *  oCorrespondingParams  ,
                                                      CATListOfInt            *  ioConvergenceInfo     ,
                                                      // 2) data to store
                                                      CATLONG32                  iArcInfo              ,
                                                      double                     iParam                ,
                                                const double                  *  iP                    ,
                                                const double                  *  iT                    ,
                                                const double                  *  iC                    ,
                                                const double                  *  CorrespondingParam    ,
                                                      int                        iConvergenceInfo      );
 

/**
 * Handle PointsRemovalAfterInterpol mode.
 * Remove unnecessary points added during the main algorithm (if this option has been set up).
 */
          void       RemovePoints              (      CATMathSetOfPointsND     & oParameters           ,
                                                      CATMathSetOfPointsND     & oPoints               ,
                                                      CATMathSetOfPointsND     & oTangents             ,
                                                      CATMathSetOfPointsND     & oSecondDerivatives    ,
                                                      CATMathSetOfPointsND    *  oCorrespondingInitialParams,
                                                      CATListOfInt             & ioConvergenceInfo     );

  
/**
 * Find C1 Discontinuities.
 * Works only for a Clever Interpol.
 */
          void       FindDiscontinuities       (      CATMathSetOfPointsND     & oParameters           ,
                                                      CATMathSetOfPointsND     & oPoints               ,
                                                      CATMathSetOfPointsND     & oTangents             ,
                                                      CATMathSetOfPointsND     & oSecondDerivatives    ,
                                                      CATListOfInt             & ioConvergenceInfo     );

  
/**
 * Check the first and last arcs if required.
 */

  virtual void       CleanOutputData           (      CATMathSetOfPointsND     & oParameters           ,
                                                      CATMathSetOfPointsND     & oPoints               ,
                                                      CATMathSetOfPointsND     & oTangents             ,
                                                      CATMathSetOfPointsND     & oSecondDerivatives    ,
                                                      CATMathSetOfPointsND    *  oCorrespondingInitialParams = 0,
                                                      CATListOfInt            *  ioConvergenceInfo     = 0);

// -----------------------------------------------------------------------
//  Run Of The Algorithm
// -----------------------------------------------------------------------

/** 
 * Provide an interpolation of a trajectory.
 * The initial set is either a set of points with vectors (implicit case) or a set of
 * parameters (explicit case).
 * Return Values : 0 - Invalid Entries
 */
  virtual CATLONG32  RunMain                   (      CATMathSetOfPointsND     & iSet                  ,
                                                const double                     iCosMin               ,
                                                      CATMathSetOfPointsND     & oParameters           ,
                                                      CATMathSetOfPointsND     & oPoints               ,
                                                      CATMathSetOfPointsND     & oTangents             ,
                                                      CATMathSetOfPointsND     & oSecondDerivatives    ,
                                                      CATMathSetOfPointsND    *  oCorrespondingInitialParams = 0,
                                                      CATListOfInt            *  ioConvergenceInfo     = 0);



// -----------------------------------------------------------------------
//  Internal Auxiliary Services
// -----------------------------------------------------------------------


/*
 * Reconverge ioParam, parametre sur la quintique courante d'indices iFirstRank (X), iFirstRank+1 (X) et
 * iFirstRank+2 (Z) pour trouver le point le plus proche en 3D de iPt3D.
 */
          CATBoolean ClosestPointOnQuintic     (const CATLONG32                  iFirstRank            ,
                                                const double                     iDeltaParam           ,
                                                const double                  *  iPt3D                 ,
                                                      double                   & ioParam               ,
                                                      double                   & oDist                 );

/*
 * Reconverge ioParam, parametre sur la quintique courante d'indices iFirstRank (U) et iFirstRank+1 (V),
 * pour trouver le point le plus proche en 3D de iPt3D, sur une surface dont les equations 3D sont specifiees.
 */
          CATBoolean ClosestPointOnQuintic     (const CATLONG32                  iFirstRank            ,
                                                const CATMathFunctionXY      **  Eq                    ,
                                                const double                     iDeltaParam           ,
                                                const double                  *  iPt3D                 ,
                                                      double                   & ioParam               ,
                                                      double                   & oDist                 );

// -----------------------------------------------------------------------
//  Miscellaneous Services
// -----------------------------------------------------------------------

  virtual double     GetSquare3DDistance       (      CATMathSetOfPointsND     & iSet                  ,
                                                      CATLONG32                  iPoint0               ,
                                                      CATLONG32                  iPoint1               ,
                                                      double                  *& ioPosition0           ,
                                                      double                  *& ioPosition1           ,
                                                      CATBoolean                 iRequestData0         ,
                                                      CATBoolean                 iRequestData1         ,
                                                      CATBoolean                 iThroughMiddle        );

  virtual void       GetMinMaxPointTransverse  (      CATMathSetOfPointsND     & iSet                  ,
                                                      CATLONG32                  iCurrentPoint         ,
                                                      CATLONG32                & ioMinPointTransverse  ,
                                                      CATLONG32                & ioMaxPointTransverse  ,
                                                      CATLONG32                  iMaxPoint             );

  virtual void       SetSecondDerivToNullIfTooBig(    double                  *  ioC                   );
  CATBoolean         IsTooBigSecondDeriv (            double                  *  ioC                   ) const;

  //                                  kjd 02Jul2007
  // Define specific scales for all the  coordinates   (to avoid to dimension angle (etc ) by a distance)
  // called in virtual void SetSecondDerivToNullIfTooBig(double * ioC)
  // ************************************************
  // * DO NOT USE; NOT FULLY SUPPORTED, BY FAR      *
  // * INTERPOLATE HOMOGENEOUS DATA   NLD 17/07/12  *
  // ************************************************
  virtual void       SetSpecificScale          (      double                  *  iScale                );

  // Reserve one (or three) vector(s) of dimension _N into an internal buffer.
          void       BufferAlloc               (      double                  *& oBuff                 );

          void       BufferAlloc               (      double                  *& oBuff1                ,
                                                      double                  *& oBuff2                ,
                                                      double                  *& oBuff3                );

  // Make the corresponding buffer(s) space available again.
          void       BufferRelease             (      double                  *& oBuff                 );

          void       BufferRelease             (      double                  *& oBuff1                ,
                                                      double                  *& oBuff2                ,
                                                      double                  *& oBuff3                );

  // Explicit = Cumulates on-the-fly.
  // Implicit = Does not cumulate till the end.
  virtual void       StoreParameter            (      CATMathSetOfPointsND     & ioParams              ,
                                                      double                     iParam                ,
                                                      CATLONG32                  iArcInfo              ) = 0;

  virtual void       StoreFirstParameter       (      CATMathSetOfPointsND     & ioParams              ,
                                                      double                     iParam                ) = 0;

  virtual void       CompleteParameters        (      CATMathSetOfPointsND     & ioParameters          ) = 0;


  virtual double     GetCosAngleBetweenTangents(      CATMathSetOfPointsND     & iSet                  ,
                                                const double                  *  iT0                   ,
                                                      CATLONG32                  iPoint1               ) = 0;

  virtual double     GetCosAngleBetweenTangents(      CATMathSetOfPointsND     & iSet                  ,
                                                      CATLONG32                  iPoint0               ,
                                                      CATLONG32                  iPoint1               ) = 0;

          double     GetSquareDistance         (const double                  *  iP0                   ,
                                                const double                  *  iP1                   ,
                                                      CATLONG32                  iN                    ) const; //const method F4E070818

          double     GetDotProd                (const double                  *  iT0                   ,
                                                const double                  *  iT1                   ,
                                                      CATLONG32                  iN                    ) const; //const method F4E070818;

  // Distance between approximated and reconverged point on current quintic
          double     GetSquareDistanceAtRatio  (      double                     iLambda               ); // NLD090712 anciennement GetDistanceAtRatio()

  // The method to call first in the Run method.
  // Force some settings according to environnement variables (debug)
          void       ForceConfig               ();

  // Second method to call in the Run method.
  // Evaluates the default value (if unspecified by SetInternalMinLength) for min length.
  virtual void       HandleMinLength           ();

          CATLONG32  GetNextRequiredPoint      (      CATLONG32                  iCurrentPoint         ,
                                                      CATLONG32                & oIndexOfNextRequiredPoint);

  virtual CATBoolean Verif                     (      CATMathSetOfPointsND     & iSet                  ,
                                                      CATMathSetOfPointsND     & oParameters           ,
                                                      CATMathSetOfPointsND     & oPoints               ,
                                                      CATMathSetOfPointsND     & oTangents             ,
                                                      CATMathSetOfPointsND     & oSecondDerivatives    ,
                                                      CATMathSetOfPointsND    *  oCorrespondingInitialParams);

  // Valid only after a call to ::CompleteParameters()
          void       UpdateParameters          (      CATMathSetOfPointsND     & ioParameters          ,
                                                      CATLONG32                  iPosition             ,
                                                      double                     iNewDelta             );

  // Valid only after a call to ::CompleteParameters()
          void       InsertParameter           (      CATMathSetOfPointsND     & ioParameters          ,
                                                      CATLONG32                  iPosition             ,
                                                      double                     iNewDelta             );
#ifdef CATMathInterpol_AdvQualityComparison
          void       RestoreInvalidArcs         (     int                        iInvalidArcNbRef      );

  virtual void       StoreInvalidArcs           (     CATMathSetOfPointsND     & ioParams              ,
                                                      CATLONG32                  iArcInfo              )
          {};
#endif

  // For a Quintic Q defined by P0,T0,C0,P1,T1,C1 on [0,DeltaParam], compute
  // the energy value defined by :
  //   E = 1/DeltaParam * int_0^DeltaParam Q"(t)^2 dt
          double     ComputeEnergy             (const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                const double                  *  iC1                   ,
                                                      CATLONG32                  iDim                  ,
                                                      double                     iDeltaParam           );

  // For debug
  // Only for clever interpol for the moment
          int        CheckOutput               (      CATMathSetOfPointsNDWithVectors & iSet           ,
                                                      CATMathSetOfPointsND     & iParameters           ,
                                                      CATMathSetOfPointsND     & iPoints               ,
                                                      CATMathSetOfPointsND     & iTangents             ,
                                                      CATMathSetOfPointsND     & iSecondDerivatives    ,
                                                      CATBoolean                 iPiece);

public:
  // XScale certification for this object: all variables and tolerances certified (with CATMathInterpolParallelDebug())
          void       SetOKScaleReviewed        () ;


// -----------------------------------------------------------------------
//  Private  Methods
// -----------------------------------------------------------------------
//
          private:
          //  PointRemoval Submethods
          //
          CATBoolean GetPointsToRemove         (      CATListOfInt             & iConvergenceInfo      ,
                                                      int                      & oStartPoint           ,
                                                      int                      & oEndPoint             ,
                                                      int                      & oSkipEnd              );

          void       RemovePointsPrivate       (      CATMathSetOfPointsND     & oParameters           ,
                                                      CATMathSetOfPointsND     & oPoints               ,
                                                      CATMathSetOfPointsND     & oTangents             ,
                                                      CATMathSetOfPointsND     & oSecondDerivatives    ,
                                                      CATMathSetOfPointsND    *  oCorrespondingInitialParams,
                                                      int                        iStartPoint           ,
                                                      int                        iEndPoint             ,
                                                      CATListOfInt             & ioConvergenceInfo     ,
                                                      int                        iSkipEnd              );

#ifdef CATMathInterpol_AdvQualityComparison
          void       RemovePoints               (     int                        iIndex                 ,
                                                      CATMathSetOfPointsND     & ioParameters           ,
                                                      CATMathSetOfPointsND     & ioPoints               ,
                                                      CATMathSetOfPointsND     & ioTangents             ,
                                                      CATMathSetOfPointsND     & ioSecondDerivatives    ,
                                                      CATMathSetOfPointsND    *  ioCorrespondingInitialParams);

#endif

          void       PrepareConvergenceInfo    (      CATListOfInt             & ioConvergenceInfo     );

          CATBoolean IsPointRemovable          (      CATLONG32                  iIndexToRemove        );

          void       UpdateAdditionalArrays    (      CATLONG32                  iRemovedMaxIndex      ,
                                                      CATLONG32                  iNbOfRemovedIndex     ,
                                                      CATLONG32                  iNewArcInfo           );

          void       UpdateListOfC1Discontinuities();


// Energy Computation Submethod
//
          double     LocalEnergy               (      double                     p0                    ,
                                                      double                     t0                    ,
                                                      double                     c0                    ,
                                                      double                     p1                    ,
                                                      double                     t1                    ,
                                                      double                     c1                    ,
                                                      double                     alpha                 );

  CATMathC1Disc_Diag FindC1Discontinuity       (const CATMathIntervalND        & iDomain               ,
                                                const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                      double                  *  oPL                   ,
                                                      double                  *  oPR                   ,
                                                      double                  *  oTL                   ,
                                                      double                  *  oTR                   );


          void       RunParallelDebug          (      CATMathSetOfPointsND     & iSet                  ,
                                                      CATMathSetOfPointsND     & oPoints               );

// -----------------------------------------------------------------------
//  Non-documented fields and methods
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
//   DATA
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
protected:
   // Input
  const CATTolerance                     & _TolObject;
        CATSoftwareConfiguration        *  _Config;


        CATLONG32                          _N;             // Dimension of the SetOfPoints to be filled
        CATMathImplicitSystem           *  _MathSystem;
        CATLONG32                          _M;             // Number of variables in _MathSystem
  const CATMathIntervalND               *  _Domain;
  const CATMathIntervalND               *  _ValidityDomain;

        CATLONG32                       *  _TabIndex,
                                        *  _TabIndexExit; // Contains an array of indexes for which the interpolation should pass
        CATLONG32                          _NbIndex;      // contains the number of indexes

  const CATMathSetOfPointsNDWithVectors *  _StartingSet;

        //                                 Tolerances
        //                                 ----------
        //                                                          // (XScaleRules) Must behave like squared value of factory scale. NLD110417
        double                             _Tolerance;
        double                             _AcceptableTolerance;

        double                             _InternalMinLength;
        double                             _MaxSquareSecondDeriv;
        double                             _MaxSquareSecondDeriv2;
        double                             _BalancingFactor;
        double                             _TolQualityFactor;       // factor to adjust tolerance on quality

        double                          *  _Coef;

        // _X, _FX, _TX dans la dimension de l'evaluateur de qualite (_N par defaut)
        //                               // - allocation groupee;
        //                               // - Attention reallocation par la classe fille CATMathCleverInterpol
        //                               // (commentaires NLD200417)
        double                          *  _X;
        double                          *  _FX;
        double                          *  _TX;

        double                             _CurrentDelta;
        double                             _CurrentW;
        CATBoolean                         _AddPointEnabled;

        // C1
        CATListOfInt                       _C1Discontinuities;
        CATBoolean                         _CleanOutput;
        CATBoolean                         _C1DiscontinuitiesDetection;
        CATBoolean                         _C1DiscontinuitiesCut;
        double                             _C1SinAngleTol;
        int                                _VectorFieldOrientation; // a redescendre (mais utilise ici dans soft C1)


        CATBoolean                         _PointsRemovalAfterInterpol;
        double                             _MaxError;

        CATLONG32                          _InterpolationPointKO;
        CATLONG32                          _Diagnostic; 
        double                         **  _BufferTab;
        CATLONG32                       *  _BufferUse;
        CATLONG32                          _BufferSize;

        CATBoolean                         _SkipAll;
        CATBoolean                         _CheckEnergy;
        CATBoolean                         _NoReconvergence;  // Best Quality with reconvergence

        // Depth
        CATLONG32                          _InsertionMaxDepth;
        CATLONG32                          _InsertionExtraDepth;
        CATLONG32                          _ExtraDepthStrategy;
        double                             _ExtraDepthTolerance;
        double                             _ExtraDepthMinLength;

       


        // _Increased Control parameter 
        CATBoolean                         _IncreaseControl;
        CATLONG32                          _ICMaxDepth;
        double                             _ICRatio;

        CATLONG32                          _QualityDerFst;
        CATLONG32                          _QualityDerLst;
        
        // Manage arc in Domain 
        CATLONG32                          _DomainManagement;
        double                             _TolDomain;

        CATMathSetOfLongs               *  _InvalidArcs;

        CATBoolean                         _OKScaleReviewed ; // NLD130712 for XScale certification

        CATBoolean                         _DeleteTabIndexExit;

        double                             _Lambda;          // F4E260918 For changing where the middle point is computed (default is at middle _Lambda=0.5)
        
        CATBoolean                         _2ndDerTmp;       // F4E270618 For testing issues with bad second derivatives 

        CATMathInterpolDebug            *   _Debug;          // F4E050918

private:

        double                          *  _SpecificScale ; // kjd 02Jul2007 : Correction of scaling for quantities which are not distances


};

//=============================================================================
// Code de debug de CATMathInterpol
// (isolation du code dans classe dediee NLD140417)
//=============================================================================

// moved to YN000FUN.m/LocalInterfaces/CATMathInterpolDebug.h   F4E130918

//=============================================================================
// END OF Code de debug de CATMathInterpol
//=============================================================================



#endif

