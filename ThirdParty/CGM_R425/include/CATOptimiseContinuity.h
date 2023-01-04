/* -*-c++-*- */
#ifndef CATOptimiseContinuity_H
#define CATOptimiseContinuity_H
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATOptimiseContinuity
//
//=============================================================================
//       97 DHN Design
//              method of the CATFrFNurbsBipar
//   /12/00 PRG Creation of a class to make it
//              Rearchitecture, modification of the weight computation
//              objective : a few iterations
//   /07/01 PRG Creation of an interface CATOptimiseContinuity to export this class
//              the previous one is moved to the class CATOptimiseContinuity
//              as an implementation. New method to impose boundary conditions.
//   /08/01 PRG Creation of a new option. The operator can be created with a
//              deformationTolerance, that equals -1, the default value. It means
//              that we will apply a deformation to reach the objective continuity
//              at each knot that can be optimised. The deformation will be then 
//              provided to the user.
//   /01/03 PRG Creation of a new implementation that makes a global optimisation
//              that achieve an advanced mode of the optimisation
//              It includes an eventual degree increase.
// 19/05/14 NLD Clean up
//              - untabify
//              - smart indent
// 08/07/15 NLD ActivateG1BoundaryCheck() replaces ActivateG1BoundayCheck() (faute de frappe ancestrale)
// 27/07/15 NLD Ajout SetSupportDebug() (VERSION NON LIVREE. NE SERA PAS CONSERVEE)
// 29/07/15 NLD Reordonnancement logique des methodes 1) Settings 2) Run() 3) Results
//              Ajout SetCGMReplayPrefixName()
// 28/07/16 JSX Add SetEmulateMultiFormFunction
//              CreateMultiFormOptimiseContinuity_EmulateMultiFormFunction
//=============================================================================
class CATFrFNurbsBipar;
class CATFrFNurbsMultiForm;
class CATMathSetOfPointsND;
class CATMathPoint;
class CATMathVector;
class CATMathFunctionXY;

#include "YP00IMPL.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"
#include "CATBoolean.h"


class ExportedByYP00IMPL CATOptimiseContinuity : public CATCGMVirtual
{
  // public methods
public :
  virtual                      ~CATOptimiseContinuity     () {};

  // 1) Settings
  //    --------
  // This activation enables us to prevent from G1 deviation.
  // G1BoundaryTolerance : maximum authorized G1 Deviation, in radian.
  // if G1BoundaryTolerance is a negative value, then a default tolerance
  // will be taken so that the deviation is equal or less than the equivalent of 0.25 degree.
  virtual void                  ActivateG1BoundaryCheck   (      double                 iG1BoundaryTolerance          = -1.) = 0;

  // to set the segmentation mode 
  //    keepSegmentation = 0 : we do not keep the segmentation, we may surpress many knots
  //    keepSegmentation = 1 : we keep the initial segmentation, no knot removal
  // if we want to keep the segmentation, we can not require inifinite continuity as 
  // ObjectiveContinuity.
  // defaultMode is KeepSegmentation == 0
  virtual void                  SetKeepSegmentationMode   (      CATLONG32              iKeepSegmentation             )    = 0;

  // default value equals 2
  // -1 for C-infinite, ie up to knot suppression  
  virtual void                  SetObjectiveContinuity    (      CATLONG32              iObjectiveContinuity          )    = 0;

  //Allows people to give an other factor of discretisation that the one used by the Optimise (i.e. 2)
  //iLocalDiscretization attempts to only discretize where necessary. Ideally, allows for higher iDiscretizationFactor without the 
  //full performance hit.
  virtual void                  SetDiscretizationFactor   (      CATLONG32              iDiscretizationFactor         ,
                                                                 CATBoolean             iLocalDiscretization = FALSE  )    = 0;

  // direction 0 pour u pour pour les multiformes, 1 en v pour les bipares
  virtual void                  SetKnotsNotToOptimise     (      CATLONG32              iNbOfKnotsNotToOptimise  ,
                                                                 CATLONG32           *  iKnotIndicesNotToOptimise,
                                                                 CATLONG32              iDir                     = 0) = 0;

  // We enable to respect continuity with the initial geometry
  // iLeftContinuity  = 0, 1 or 2 (0 is the default value)
  // iRightContinuity = 0, 1 or 2 (0 is the default value)
  // iDir : 0 for multiforms or u for bipares, 1 for v in the case of bipare
  // Here we talk about C continuity, not G. The C continuity introduces more constraints
  // that G continuity.
  // C continuity can be preserved for mulitformes without any problem.
  // However, for Bipare, it is not the case : since the algorithm is based
  // on a one-direction optimization (u and v alternatively),
  // constraints are not kept during the whole process in both direction. Hence,
  // this option should enable us to minimize the C1/C2 deviation on the boundaries but not
  // prevent it completely. In the same way, the more constraints we add, the less we optimise
  // the geometry.
  virtual void                  SetBoundaryConditions     (      CATLONG32              iLeftContinuity          ,
                                                                 CATLONG32              iRightContinuity         ,
                                                                 CATLONG32              iDir                     = 0) = 0;

  // to autorize parameter-sliding (available only for MultiForms)
  virtual void                  SetSlidingMode            (      CATLONG32              iSlidingMode             = 1) = 0;

  // see the new constructor CreateSlidingBiparOptimiseContinuity below
  virtual CATLONG32             GetSlidingModeHasBeenUsed ()                                                          = 0;

  // set support (in the case of 2d - multiforms)
  // to compute 3d-deviation
  virtual void                  SetSupport                (      CATFrFNurbsBipar    *  iSupportingBipare        )    = 0;

  // set support (in the case of 2d - multiforms)
  // (only for debug / visualization: no impact on computation
  // (VERSION NON LIVREE. NE SERA PAS CONSERVEE)
  virtual void                  SetSupportDebug           (      CATFrFNurbsBipar    *  iSupportingBipare        )    = 0;

  // set support (in the case of 2d - multiforms)
  // to compute 3d-deviation even for other support than NURBS
  virtual int                   SetSupportEquations       (      CATMathFunctionXY   *  iSupportX                ,
                                                                 CATMathFunctionXY   *  iSupportY                ,
                                                                 CATMathFunctionXY   *  iSupportZ                )    = 0;

  // set specific checks to be performed. Warning: Pointers should be valid until Run method is performed (no duplication for CPU reasons)
  // if iTargetPoints[i] or iTargetNormal[i] == NULL then corresponding check will not be performed
  // iTolPoint and iTolAngle allow you to specify specifics tolerances. By default (i.e. if NULL), tolerance used for point is equal to the
  // input deformationTolerance and 0.5 degree for normal.
  // This mode is not compatible with SetSlidingMode(1), nor with CreateGlobalMultiFormOptimiseContinuity/CreateGlobalBiparOptimiseContinuity creators
  // return 1 if input points already do not fit criterions
  virtual int                   AddMeasurePoints          (const CATMathSetOfPointsND*  iUVPoints                ,
                                                           const CATMathPoint        ** iTargetPoints            ,
                                                           const CATMathVector       ** iTargetNormal            ,
                                                           const double              *  iTolPoint                ,
                                                           const double              *  iTolAngle                )    = 0;

  // switch on limit surface evaluation for measurements (default is done thru control points distance)
  virtual void                  SetDiscreetMeasureMode    (      int                    iActivate                = 1) = 0;

  // set Reference to compute 3d-deviation
  virtual void                  SetReference              (      CATFrFNurbsMultiForm*  iRefMultiForm            )    = 0;

  // set Mode, force the use of the run that simulates the CATMultiForm::OptimiseContinuity behavior
  virtual void                  SetEmulateMultiFormFunction(CATLONG32 iNewOldMode )                                   = 0;

  // set prefix name for CGMReplay files
  virtual void                  SetCGMReplayPrefixName    (const char                *  iPrefix                  )    = 0;

  // 2) Run
  //    ---
  // Run method
  // return an non 0 value if run fails
  virtual CATLONG32             Run                       ()                                                          = 0;

  // 3) Results
  //    -------
  virtual CATFrFNurbsBipar    * GetResultingBipar         ()                                                          = 0;

  virtual CATFrFNurbsMultiForm* GetResultingMultiForm     ()                                                          = 0;

  // if there is no deformationTolerance,
  // GetDeformationRatio() will return -1.
  virtual double                GetDeformationRatio       ()                                                          = 0;

  virtual double                GetDeformation            ()                                                          = 0;
 
};


//=================================================================================
//  both following functions enable us to instanciate a standard implementation
//  of the continuity optimisation
//=================================================================================

// if (deformationTolerance==-1.), which is the default value,
// there won't be any deformation tolerance. We will apply the deformation to reach the objective
// continuity at the knots that we are allowed to deform.
ExportedByYP00IMPL
CATOptimiseContinuity* CreateMultiFormOptimiseContinuity  (      CATFrFNurbsMultiForm*  initialMultiForm         ,
                                                                 double                 deformationTolerance     = -1.);

// if (deformationTolerance==-1.), which is the default value,
// there won't be any deformation tolerance. We will apply the deformation to reach the objective
// continuity at the knots that we are allowed to deform.
ExportedByYP00IMPL
CATOptimiseContinuity* CreateBiparOptimiseContinuity      (      CATFrFNurbsBipar    * initialBipar              ,
                                                                 double                deformationTolerance      = -1.);

ExportedByYP00IMPL
CATOptimiseContinuity* CreateMultiFormOptimiseContinuity_EmulateMultiFormFunction
                                                          (      CATFrFNurbsMultiForm*  iInitialMultiForm        ,
                                                                 double                 iDeformationTolerance    = -1);

//=================================================================================
//  both following functions enable us to instanciate a global implementation
//  of the continuity optimisation based on the above implementation.
//  Using it, the processing time may be increased,
//  but it enables us to make the optimisation in a very controlled mode
//  and limit the number of discontinuities by taking the data size into account
//  A way to make geometry more continuous is to increase degrees, but
//  this is only done if it leads to a more continuous result.
//  Indeed it is done in such a way that
//      - the degree will be increased up to the authorized value if 
//      this enables us to smooth more discontinuities.
//      - the extra optimisation that make the decrease the data size thanks to
//      the NoKeepSegmentation mode is finally processed.
//=================================================================================
ExportedByYP00IMPL
CATOptimiseContinuity* CreateGlobalMultiFormOptimiseContinuity  (CATFrFNurbsMultiForm* iInitialMultiForm         ,
                                                                 double                iDeformationTolerance     ,
                                                                 CATLONG32             iAuthorizedElevationDegree= 1);
ExportedByYP00IMPL
CATOptimiseContinuity* CreateGlobalBiparOptimiseContinuity      (CATFrFNurbsBipar    * iInitialBipar             ,
                                                                 double                iDeformationTolerance     ,
                                                                 CATLONG32             iAuthorizedElevationDegree= 1);

//=================================================================================
//  this function enable us to make the optimisation with a sliding mode
//  for some specific bipars (ruled surfaces for the moment).
//  If BiparSlidingMode==0, the behaviour is the same as the previous constructor
//  If BiparSlidingMode==1, ruled surfaces will be treated as MultiForm 
//  and the sliding mode for multiforms will be activated
//  If it is done in this way, the user can know it by using the method GetSlidingModeHasBeenUsed()
//  Note that in this case, the parametrisation of PCurves lying on this surface must be updated.
//=================================================================================
ExportedByYP00IMPL
CATOptimiseContinuity* CreateSlidingBiparOptimiseContinuity     (CATFrFNurbsBipar    * iInitialBipar             ,
                                                                 CATLONG32             iBiparSlidingMode         ,
                                                                 double                iDeformationTolerance     ,
                                                                 CATLONG32             iAuthorizedElevationDegree= 1);

#endif
