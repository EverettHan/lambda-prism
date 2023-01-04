// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATMathExplicitInterpol:
//   Base class for quintic polynomial C2 interpolation of an object
//   after an explicit marching algorithm, with reconvergence on the parameters to 
//   have the best possible interpolation.
//
//=============================================================================
// Usage notes:
//
//  This base class works for interpolation of a curve defined by an explicit
//  equation but can be derived for other problems
//
//  The number of subelements generated tries to be as small as possible, with 
//  the constraint on the tolerance for the Quality evaluator.
//
//
//=============================================================================
// 11/04/08 PKC Versionning
// 24/07/12 NLD XScale. passage par CATHardTol() pour detection dynamique
//              Et finalement suppression de la valeur par defaut de la tolerance
//              et de tous les arguments par defaut
// 28/04/16 NLD XScale:
//              - suppression de la valeur par defaut de l'argument de SetHFactor()
//              Reordonnancement des methodes en conformite avec la classe mere
//              Smart indent
//=============================================================================


#ifndef CATMathExplicitInterpol_h
#define CATMathExplicitInterpol_h

#include "YN000FUN.h"

// #include "CATMathCleverInterpol.h"

#include "CATMathInterpol.h"
#include "CATMathDef.h"
#include "CATMathInterval.h"

class CATMathSetOfPointsNDWithVectors;
class CATMathSetOfPointsND;
class CATMathVectorialFunctionX;
class CATSoftwareConfiguration;

class ExportedByYN000FUN CATMathExplicitInterpol : public CATMathInterpol
{
public:

                     CATMathExplicitInterpol   (      CATSoftwareConfiguration *  iConfig              ,
                                                const CATLONG32                   iN                   ,
                                                      CATMathVectorialFunctionX*  iSampler             ,
         //                                     Must behave like squared value of factory scale
                                                const double                      iTolerance           , // = CATHardTol(1.e-10),
                                                const CATTolerance              & iTolObject           ); //= CATGetDefaultTolerance());
  
  virtual           ~CATMathExplicitInterpol();
  virtual void       Run                       (      CATMathSetOfPointsND     & iInitialParams        ,
                                                      CATMathSetOfPointsND     & oParameters           ,
                                                      CATMathSetOfPointsND     & oPoints               ,
                                                      CATMathSetOfPointsND     & oTangents             ,
                                                      CATMathSetOfPointsND     & oSecondDerivatives    ,
                                                      CATMathSetOfPointsND     * oCorrespondingInitialParams = 0);


          // To avoid reconvergence (Default is FALSE)
          void       SetParametrizedByDistance (      CATBoolean                 value                 );

          // To adjust the finite difference parameter
          void       SetHFactor                (      double                     h                     );// NLD280416 = 2.e-5);

          // To stay with old Newton Mode (regression testOffskin_052, cf DPS)
          void       SetOldNewtonMode          ();

protected:

// -----------------------------------------------------------------------
//  Mandatory Services Required By Mother Class
// -----------------------------------------------------------------------

  // See mother class for details.

/**
 * Retrieve data from the initial set.
 */
          void       GetDataFromISet           (      CATMathSetOfPointsND     & iSet                  ,
                                                      CATLONG32                  iPos                  ,
                                                      double                  *  oParam                = 0,
                                                      double                  *  oP                    = 0,
                                                      double                  *  oT                    = 0);

/**
 * Retrieve or compute point from the initial set.
 */
          void       GetPointFromISet          (      CATMathSetOfPointsND     & iSet                  ,
                                                      CATLONG32                  iPos                  ,
                                                      double                  *  oParam                = 0,
                                                      double                  *  oP                    = 0);


/** 
 * Compute point, tangent and second derivative in the dimension of
 * interpolation. Point and tangent computed in the dimesion of marching
 * may have to be given as inputs.
 * iOrientation = -1 for a derivative on the left, 1 on the right and 0 
 *   for both sides.
 */
          void       ComputeData               (      double                     iParam                ,
                                                      double                  *  ioP                   ,
                                                      double                  *  ioT                   ,
                                                      double                  *  ioC                   ,
                                                      int                        iOrientation          );

// -----------------------------------------------------------------------
//  Quality Evaluators
// -----------------------------------------------------------------------
/** 
 * Compute the quality of the current arc at specified ratio. (homogeneous to power 2 of factory scale)
 */
          double     Quality                   (const double                     iRatio                ,
                                                const double                     iParam0               ,
                                                const double                     iParam1               ,
                                                const double                     iDeltaParam           ,
                                                      CATBoolean               & ioCheckDomain         );

/** 
 * Compute the quality of the specified arc at middle point. (homogeneous to power 2 of factory scale)
 */
  // Warning : here, this method requires the current quintic  coefficients
  // to be computed, which is not the case for CATMathCleverInterpol.
  // PrepareQualityOpt does this precomputation.
          double     QualityOpt                (const double                     iParam0,
                                                const double                     iParam1               ,
                                                const double                     iDeltaParam           ,
                                                      CATBoolean               & ioCheckDomain         );


          void       PrepareQualityOpt         (const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                const double                  *  iC1                   ,
                                                const double                     iDeltaParam           ,
                                                      CATBoolean                 iOnlyDelta            );

// -----------------------------------------------------------------------
//  Quality Control And Parametrization Management
// -----------------------------------------------------------------------
/** 
 * Point checker (called on the first point only).
 */
  // Implementation is void for the explicit interpol
  virtual void       CheckValidityOfPoint      (      CATMathSetOfPointsND     & iSet                  ,
                                                const double                  *  iP                    ,
                                                      double                  *  ioT                   ,
                                                      double                  *  ioC                   ,
                                                      double                     iCosMin               ,
                                                      CATBoolean               & oIsSingularLeft       );

/** 
 * Point checker (called on the end point and on each required point).
 */
  // Implementation is void for the explicit interpol
  virtual void       CheckValidityOfLastPoint  (const double                  *  iP0                    ,
                                                const double                  *  iT0                    ,
                                                const double                  *  iP1                    ,
                                                      double                  *  ioT1                   ,
                                                      double                  *  ioC1                   ,
                                                      double                     iCosMin                ,
                                                      CATBoolean               & oIsSingularRight       );


          void       StoreParameter            (      CATMathSetOfPointsND     & ioParams              ,
                                                      double                     iParam                ,
                                                      CATLONG32                  iArcInfo              );

          void       StoreFirstParameter       (      CATMathSetOfPointsND     & ioParams              ,
                                                      double                     iParam                );

          void       CompleteParameters        (      CATMathSetOfPointsND     & ioParameters          );

  virtual double     GetCosAngleBetweenTangents(      CATMathSetOfPointsND     & iSet                  ,
                                                const double                  *  iT0                   ,
                                                      CATLONG32                  iPoint1               );

  virtual double     GetCosAngleBetweenTangents(      CATMathSetOfPointsND     & iSet                  ,
                                                      CATLONG32                  iPoint0               ,
                                                      CATLONG32                  iPoint1               );

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
                                                const double                  *  iC1                   );

/**
 * Return the finite difference step to use during the minimization of the function
 *   DeltaParam |-> Quality_of_the_arc
 */
  virtual double     GetFiniteDifferenceStep   (      double                     iDeltaParam           ,
                                                      double                     iParam0               ,
                                                      double                     iParam1               );

// -----------------------------------------------------------------------
//  Insertion Management
// -----------------------------------------------------------------------
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
                                                      double                  *  ioCHalf               );


// StoreParameter               moved above
// StoreFirstParameter          moved above
// CompleteParameters           moved above
// GetCosAngleBetweenTangents   moved above
// CheckValidityOfPoint         moved above
// CheckValidityOfLastPoint     moved above

// -----------------------------------------------------------------------
// Specific methods
// -----------------------------------------------------------------------

  virtual void       ComputeDataAtParam        (const double                     iParam                ,
                                                      double                  *  ioP                   ,
                                                      double                  *  ioT                   ,
                                                      double                  *  ioC                   );

// InitializeDeltaParam     moved above

  virtual CATBoolean NewtonOnQuintic           (const double                  *  iPt                   ,
                                                      double                   & ioParam               );

  virtual double     QualityExplicit           (const double                     iLambda               ,
                                                const double                     iParam0               ,
                                                const double                     iParam1               ,
                                                const double                     iDeltaParam           );

  // FX is a point on the sampled curve, iLambda the init parameter ratio : return the Quality of the
  // approached curve from FX.
  virtual double     QualityExplicitAtPoint    (const double                  *  FX                    ,
                                                      double                     iLambda               ,
                                                      double                     iDeltaParam           );

/**
 * Return the discretization number to use to compute the deviation of the arcs
 * when splitting an arc. Default is 5.
 */
  virtual CATLONG32  GetNbSampleInAddPoint     ();

  virtual CATBoolean Verif                     (      CATMathSetOfPointsND     & iSet                  ,
                                                      CATMathSetOfPointsND     & oParameters           ,
                                                      CATMathSetOfPointsND     & oPoints               ,
                                                      CATMathSetOfPointsND     & oTangents             ,
                                                      CATMathSetOfPointsND     & oSecondDerivatives    ,
                                                      CATMathSetOfPointsND    *  oCorrespondingInitialParams);

/*
  virtual CATLONG32  GetNextPoint              (      CATMathSetOfPointsND     & iSet                  ,
                                                      CATLONG32                  iCurrentPoint         ,
                                                      double                     iCosMin               ,
                                                      double                  *  iOldT                 ,
                                                      CATLONG32                & oMinPoint             ,
                                                      CATLONG32                & oMaxPoint             ,
                                                      CATLONG32                & oMinPointTransverse   ,
                                                      CATBoolean               & oRequiredPoint        ,
                                                      CATLONG32                & oIndexExit            ,
                                                      double                   & oParam                ,
                                                      double                  *  ioP                   ,
                                                      double                  *  ioT                   ,
                                                      double                  *  ioC                   );

          CATLONG32  GetNextPoint              (      CATMathSetOfPointsND     & iInitialParams        ,
                                                      CATLONG32                  iCurrentPoint         ,
                                                      double                     iCosMin               ,
                                                      double                  *  iOldT                 ,
                                                      CATLONG32                & oMinPoint             ,
                                                      CATBoolean               & oRequiredPoint        ,
                                                      double                   & oParam                ,
                                                      double                  *  ioP                   ,
                                                      double                  *  ioT                   ,
                                                      double                  *  ioC                   );

          CATLONG32  GetNextPointOld           (      CATMathSetOfPointsND     & iInitialParams        ,
                                                      CATLONG32                  iCurrentPoint         ,
                                                      double                     iCosMin               ,
                                                      double                  *  iOldT                 ,
                                                      CATBoolean               & oRequiredPoint        ,
                                                      double                   & oParam                ,
                                                      double                  *  ioP                   ,
                                                      double                  *  ioT                   ,
                                                      double                  *  ioC                   );
*/

          void       Eval                      (      CATMathSetOfPointsND     & iInitialParams        ,
                                                      CATLONG32                  iPoint                ,
                                                      double                  *  ioResult              );

//
// Protected data
//
protected:
  CATMathSetOfPointsND      * _InitialParams;
  CATLONG32                   _NbInitialPoints;
  CATMathVectorialFunctionX * _Sampler;
  CATBoolean                  _OldNewtonMode;

  // finite difference factor
  double                      _hFactor;



private :
  // boolean for non reconvergence (within the run method)
  CATBoolean                  _ParametrizedByDistance;
  // for local nonreconvergence use the last parameter of BestExplicitInterpol

};


#endif

