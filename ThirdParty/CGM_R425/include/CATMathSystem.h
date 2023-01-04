// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATMathSystem:
//  Abstract class used to Solve a system F of N functions of N variables
//  with F differentiable (C1).
//
// XScaleRules:
//  - Strongly recommended: use variables and functions behaving like power 1 of factory scale
//  - Otherwise use SetScaleOption()
//  - iUserDomain is a user domain corresponding to user problem/system/functions
//  - iDomain     is a rescaled domain to XScale hypotheses, ussing the scale option specified
//                and ComputeScaledDomain()
//
//=============================================================================
// 21/02/08 NLD SetRelativeEpsSol() remplace SetEpsSol() for XScale purpose
// 25/02/08 NLD _UnScaleX_Spy, _ScaleFX_Spy for XScale debug purpose
// 23/09/11 R1Y Added the function GetToleranceObject() (for comparing geometries).
// 23/05/16 NLD Smart indent
//              "EasySolver" attribute mention
//              Ajout AttrSystemEasySolver (en remplacement de valeur en dur)
// 01/06/16 NLD Mise en coherence des signatures
//              TryChangeSignInHyperCube() rend un entier et non plus un CATBoolean
//              Ajout _FSolveAlloc pour clarifier/securiser les usages d'allocations groupees
// 03/06/16 NLD Preparation versionning
//              - ajout _SystemConfig
//              - ajout Init()
//              - ajout constructeur avec configuration
// 14/06/16 NLD Deplacement des declarations de donnees a la fin
//              Ajout XScaleRules
// 01/07/16 NLD Changement de notations:
//              - iEquationIndex  remplace iEquationNumber
//              - iVariableIndex  remplace iVariableNumber
//              - iVariableIndex1 remplace iVariableNumber1
//              - iVariableIndex2 remplace iVariableNumber2
//=============================================================================

#ifndef CATMathSystem_H
#define CATMathSystem_H

#include "YN000FUN.h"

#include "CATMathDef.h"
#include "CATMathConstant.h"
#include "CATMathDiagnostic.h"
#include "CATCGMVirtual.h"
#include "CATTolerance.h"
#include "CATMathInline.h"
#include "CATMathAttrList.h"
#include "CATMathAttrScaleOption.h"

class CATMathIntervalND;
class CATMathSetOfPointsND;
class CATMathAttrList;
class CATMathNxNFullMatrix;
class CATMathInterval;
class CATSoftwareConfiguration;

// Attributes strings used as options for the Solve method
extern ExportedByYN000FUN const CATMathAttrId AttrSystemSamplingPoints;
extern ExportedByYN000FUN const CATMathAttrId AttrSystemNoSingularityTreatment;
extern ExportedByYN000FUN const CATMathAttrId AttrSystemLightSingularityTreatment;
extern ExportedByYN000FUN const CATMathAttrId AttrSystemEasySolver;

//-----------------------------------------------------------------------------
class ExportedByYN000FUN CATMathSystem : public CATCGMVirtual
{ 
public:  

  //--------------------------------------------------------------------------
  //  Constructor (iNumberOfVariables is the number of unknowns of the system)
  //--------------------------------------------------------------------------

                                        CATMathSystem               (      CATSoftwareConfiguration *  iConfig           ,
                                                                     const CATTolerance              & iTolObject        ,
                                                                     const CATLONG32                   iNumberOfVariables,
                                                                     const CATMathAttrList          *  attributes        = NULL);

   #define CATMathSystem_KeepOldConstructor "necessaire pour applications"
   #ifdef  CATMathSystem_KeepOldConstructor
  //--------------------------------------------------------------------------
  //  Constructor (iNumberOfVariables is the number of unknowns of the system)
  //--------------------------------------------------------------------------
  // DEPRECATED


                                        CATMathSystem               (const CATLONG32                   iNumberOfVariables,
                                                                     const CATTolerance              & iTolObject        = CATGetDefaultTolerance(),
                                                                     const CATMathAttrList          *  attributes        = NULL);
  #endif

  virtual                              ~CATMathSystem               ();

  //--------------------------------------------------------------------------
  // Information methods
  //--------------------------------------------------------------------------
         
  virtual CATMathClassId                IsA                         ()                                                     const;
  virtual CATBoolean                    IsAKindOf                   (const CATMathClassId              iClassId          ) const;

   //  Get the number of unknowns of the system (N) 
  INLINE  CATLONG32                     GetNumberOfVariables        ();

  // Get the tolerance object.
  const   CATTolerance                & GetToleranceObject          () const;
   
  //--------------------------------------------------------------------------
  // Solver
  //--------------------------------------------------------------------------  
  //
  // Solver interface :
  // iAttributes is a pointer to a list of attributes to pass options to the solver
  // (default is 0, i.e. no option).
  //
  // The available attributes, defined from the CATMathAttrId
  // listed in the beginning of the file, are the following :
  // 
  // * CATMathAttrPointerValue((CATMathAttrId) AttrSystemSamplingPoints, (CATLONG32 *) NbPoints)
  //     with this attribute, the sampling grid used by Solve 
  //     has NbPoints[i] number of points along variable number i.
  //
  // * CATMathAttrString      ((CATMathAttrId) AttrSystemNoSingularityTreatment)
  //     this attribute tells the solver not to use singularity treatment to find double
  //     solutions or close solutions. In this case :
  //     - The output is less reliable;
  //     - the performance is increased.
  //
  // other attributes to document
  // AttrSystemLightSingularityTreatment
  // * CATMathAttrString      ((CATMathAttrId) AttrSystemEasySolver)
  //   ("EasySolver")
  virtual CATMathDiagnostic             Solve                       (const CATMathIntervalND         & iUserDomain       , 
                                                                           CATMathSetOfPointsND      & oSolutions        ,
                                                                     const CATMathAttrList          *  iAttributes       = 0);

  //
  // Safe Newton process in iDomain : 1 is returned if success, else 0 is returned
  // ioSolution is the init and the returned solution
  // if pointers FX and/or Jacobian are not null, then use them as temporary variables
  // in the Newton process
  // If oSingular is not null, *oSingular is filled with 0 or 1 depending if the last
  // Newton iteration was singular (Jacobian singular) or not.
  virtual CATBoolean                    SolveSafeNewton             (const CATMathIntervalND         & iDomain           ,
                                                                           double                   *  ioSolution        ,
                                                                           double                   *  FX                = 0,
                                                                           double                   *  NewSol            = 0,
                                                                           CATMathNxNFullMatrix     *  Jacobian          = 0,
                                                                           CATBoolean               *  oSingular         = 0);


  //--------------------------------------------------------------------------
  // Evaluators on points in RN
  //--------------------------------------------------------------------------

   //
   // Evaluators: iX is a point in RN.
   //  . oFX = F(iX) is the image of iX by F. oFX is in RN and is already allocated. 
   //  . oJacobianFX is the jacobian of F at iX and is a NxN Matrix alread allocated
   //
  virtual void                          Eval                        (const double                   *  iX                ,
                                                                           double                   *  oFX               ) = 0;

  virtual void                          EvalJacobian                (const double                   *  iX                ,
                                                                           CATMathNxNFullMatrix     *  oJacobianFX       ); 

  virtual void                          Eval                        (const double                   *  iX                ,
                                                                           double                   *  oFX               ,
                                                                           CATMathNxNFullMatrix     *  oJacobianFX       );

  //
  //  IsRoot is a method to determine if iFX = F(iX) can be considered as a root 
  //  at iX and oNormFX is any norm of F(X) computed by IsNull.
  //  iJacobianFX is an optional parameter which contains the jacobian at iX.
  virtual CATBoolean                    IsRoot                      (const double                   *  iX                ,
                                                                     const double                   *  iFX               ,
                                                                           double                    & oNormFX           ,
                                                                     const CATMathNxNFullMatrix     *  iJacobianFX       = 0);
   
  //
  //  IsNull is a method to determine if iFX = F(iX) can be considered as null 
  //  at iX and oNormFX is any norm of F(X) computed by IsNull.
  //  iJacobianFX is an optional parameter which contains the jacobian at iX.
  // If the system satisfy IsNull along a curve, it is considered as ill conditionned
  virtual CATBoolean                    IsNull                      (const double                   *  iX                ,
                                                                     const double                   *  iFX               ,
                                                                           double                    & oNormFX           ,
                                                                     const CATMathNxNFullMatrix     *  iJacobianFX       = 0);

  // Homotopy specific method to keep the latest non inside point when the return code
  // of Newton is 0
  // Now used by some other operators.                             (comment NLD140616)
  virtual void                          SetInterSol                 ();

  // XScaleRules: returned value is scale independant              (comment NLD140616)
  virtual double                        InterSol_GetFlatness        ();

  // Method to be used to know if the solver switched to easy solver mode or not
  // (this is the case in some difficult situations).
  virtual CATBoolean                    IsEasySolverOn              ();

  // used with the easy solver: this is a dimension by dimension estimate of
  // (the sag of the curve) / (the parametre width)^2
          void                          SetVerySuspectCoeffs        (const double                   *  VerySuspectCoeff  );

  // To take into account big numerical error internal to the evaluation of the system
  // from 2008/02/21st : relative value (not depending on scale)
  virtual void                          SetRelativeEpsSol           (      double                      iRelativeEpsSol   );

          void                          SetScaleOption              (      CATMathAttrScaleOption   *  iScaleOption      ) ;


protected:

   //-----------------------------------------------------------------------
   // Specialized evaluators on points in RN for Parmeval Solver
   // on one equation of the system : 0 <= iEquationIndex  <= N-1
   //-----------------------------------------------------------------------
  virtual double                        EvalEquation                (const CATLONG32                   iEquationIndex    ,
                                                                     const double                   *  iX                );

  virtual double                        EvalFirstDerivEquation      (const CATLONG32                   iEquationIndex    ,
                                                                     const CATLONG32                   iVariableIndex    ,
                                                                     const double                   *  iX                );

  virtual double                        EvalSecondDerivEquation     (const CATLONG32                   iEquationIndex    , 
                                                                     const CATLONG32                   iVariableIndex1   ,
                                                                     const CATLONG32                   iVariableIndex2   ,
                                                                     const double                   *  iX                );
   
  virtual void                          EvalFirstDerivEquation      (const CATLONG32                   iEquationIndex    ,
                                                                     const double                   *  iX                ,
                                                                           double                   *  oDFX              );

  virtual void                          EvalEquation                (const CATLONG32                   iEquationIndex    ,
                                                                     const double                   *  iX                ,
                                                                           double                    & oFX               ,
                                                                           double                   *  oDFX              );   

  // Multi-evaluation of iEquationIndex -th equation and derivatives on a regular 
  // N Dimensional grid delimited by  iDomain, the number of points on the grid along
  // the i-th variable being iSampling[i].
  // Explanation of the Output :
  //  For each N-Dimensional integer I = (i[0], i[1], ..., i[N-1]), we define
  //  its INTEGER REPRESENTATION as :
  //  IR(I) =  (.. ( i[0]*iSampling[1] ) + .. + i[N-2] ) * iSampling[N-1] + i[N-1]
  //    * the double  oFX[  IR(I) ] 
  //      contains the value of the iEquationIndex -th equation at the point
  //      X = ( DMin[k] + i[k]/iSample[k] * (DMax[k]-DMin[k]) )_{ 0 <= k <= N-1}
  //    * the double oDFX[ IR(I) * N + k ]  contains the value of the k-th derivative
  //      of the iEquationIndex -th  equation at the point X (0 <= k <= N-1)
  virtual void                          EvalEquation                (const CATLONG32                   iEquationIndex    ,
                                                                     const CATMathIntervalND         & iDomain           ,
                                                                     const CATLONG32                *  iSampling         ,
                                                                           double                   *  oFX               ,
                                                                           double                   *  oDFX              );

  virtual void                          EvalEquation                (const CATLONG32                   iEquationIndex    ,
                                                                     const CATMathIntervalND         & iDomain           ,
                                                                     const CATLONG32                *  iSampling         ,
                                                                           double                   *  oFX               );
   
  //-----------------------------------------------------------------------
  //- Parmeval Solver
  //-----------------------------------------------------------------------

  virtual CATLONG32                     FSolve                      (const CATMathIntervalND         & iDomain           ,
                                                                     const CATLONG32                *  Sampling          );

  // Classic Discretization solver
  virtual CATLONG32                     DSolve                      (const CATMathIntervalND         & iDomain           ,
                                                                     const CATLONG32                *  Sampling          ,
                                                                     const char                     *  TestSubGrid       = 0);

  // Classic Discretization solver with a simple discretization
          CATLONG32                     SimpleDSolve                (const CATMathIntervalND         & iDomain           );
               
  // Local Classic Discretization solver
          CATLONG32                     DSolveLocal                 (const CATMathIntervalND         & iDomain           );

  virtual void                          FillLocalHyperCube          (const CATLONG32                *  Sampling          ,
                                                                     const double                   *  GridX             ,
                                                                     const double                   *  GridDX            ,
                                                                           double                   *  LocalGridX        ,
                                                                           double                   *  LocalGridDX       );
   
  virtual CATBoolean                    IsChangingSignOnHyperCube   (const double                   *  LocalGridX        ); 

  virtual short                         EasyChangingSignOnHyperCube (      double                      VerySuspectThreshold);

          CATLONG32                     TreatSuspectHyperCube       (const CATLONG32                   iEquationIndex    ,
                                                                     const CATMathIntervalND         & iDomain           ,
                                                                     const double                   *  LocalGridX        ,
                                                                     const double                   *  LocalGridDX       );

          CATLONG32                     TryChangeSignOnEdge         (const CATLONG32                   iEquationIndex    ,
                                                                     const CATMathIntervalND         & iDomain           ,
                                                                     const CATLONG32                   Code0             ,
                                                                     const CATLONG32                   VariableIndex     ,
                                                                     const CATLONG32                   sign              ,
                                                                     const double                      Point0            ,
                                                                           double                      Derivative0       ,
                                                                     const double                      Point1            ,
                                                                           double                      Derivative1       );
   
          CATLONG32                     TryChangeSignInHyperCube    (const CATLONG32                   iEquationIndex    ,
                                                                     const CATMathIntervalND         & iDomain           ,
                                                                     const CATLONG32                   PositionCode      ,
                                                                     const CATLONG32                   DirectionCode     ,
                                                                     const CATLONG32                   sign              );
  
          CATLONG32                     TreatSingularJacobian       (const CATMathIntervalND         & iDomain           );   

  // Safe Newton process with FX and Jacobian already allocated
  // oSingular = 1 if at the last step, the jacobian was found singular
          CATBoolean                    SolveSafeNewtonWithAlloc    (const CATMathIntervalND         & iDomain           ,
                                                                           double                   *  ioSolution        ,
                                                                           double                   *  FX                ,
                                                                           double                   *  NewSol            ,
                                                                           CATMathNxNFullMatrix     *  Jacobian          ,
                                                                     const CATLONG32                   iSystemType       ,
                                                                           CATBoolean                & oSingular         );

  // test if two potential solutions are separate or not.
          CATBoolean                    AreSeparateSolutions        (const double                   *  Solution1         ,
                                                                     const double                   *  Solution2         );   

          CATBoolean                    AddSolution                 (const double                   *  iSolution         );

  // methods which unscale the parameter (homogenous to the scale )to the natural param
          void                          UnScaleX                    (const double                   *  iX                ,
                                                                           double                   *  oX                );
  // methods which scale F so this this vector become homogenous to the scale .
          void                          ScaleFx                     (      double                   *  iFx               ,
                                                                           double                   *  oFx               );
  // methods which scale jacobian  similarly to the above methods.
          void                          ScaleJacobianFX             (      CATMathNxNFullMatrix     *  iJacobianFX       ,
                                                                           CATMathNxNFullMatrix     *  oJacobianFX       );

          void                          ComputeScaledDomain         (      CATMathIntervalND         & ioDomain          );

          void                          ComputeUnScaledRoots        (      CATMathSetOfPointsND      & ioRoots           );

          void                          ComputeUnScaledRoots        (      double                   *  ioRoots           );

   //
   //- Methods concerned with the singularities
   //
          void                          FillIntervalJacobian        (const double                   *  LocalGridDX       ,
                                                                           double                   *  CoeffJacMin       ,
                                                                           double                   *  CoeffJacMax       );

  virtual CATBoolean                    IsSingularIntervalJacobian  (const double                   *  CoeffJacMin       , 
                                                                     const double                   *  CoeffJacMax       );

  // CAUTION: default implementation is empty et returns FALSE.     NLD140616
  virtual CATBoolean                    TryMarching                 (      double                   *  iInit             );

  // Should ne redefined if the type of system enable to have good techniques
  // to handle double roots or bad conditionned contexts
  // CAUTION: default implementation is empty et returns FALSE.     NLD140616
  virtual CATBoolean                    FindRootNearSingularity     (const CATMathIntervalND         & iDomain           );

  virtual void                          EvalForDoubleRoot           (const double                   *  iX                ,
                                                                           double                   *  oFX               ,
                                                                           CATMathNxNFullMatrix     *  oJacobianFX       );

  protected:
  virtual void                          SetEasySolver               ();

  private:
          void                          Init                        (      CATSoftwareConfiguration *  iConfig           ,
                                                                     const CATLONG32                   iNumberOfVariables,
                                                                     const CATMathAttrList          *  attributes        = NULL);

  //===========================================================================
  // DATA
  //===========================================================================

protected:

  //****************************************************************
  // CAUTION NLD060616
  // -------
  // - used in CATMathConicDeformationFolded/CATMathConicDeformation/CATMathNonLinearTransformation
  //   and some other equations
  // - every modification in data definition must be accompanied by
  //   - replay of GeometricObjectsCGM.tst CompareGeometrySizeof_IfKOContactGeometryTeam
  //   - update of GeometricObjectsCGM\CATGeometricObjectsCGM.m\src\CATCompareGeometryImp.cpp
  //****************************************************************
  CATSoftwareConfiguration * _SystemConfig;

  CATLONG32                  _N;
  CATLONG32                  _2PowerN;   

  const CATMathIntervalND  * _Def;
  CATMathSetOfPointsND     * _Solutions;
   
  CATMathNxNFullMatrix     * _Jacobian;
  CATLONG32                * _SimpleSampling;   

  double                   * _FSolveAlloc; // regroupement des allocations _LocalGridX, _LocalGridDX, _CoeffJacMin, _CoeffJacMax
  double                   * _CoeffJacMin, // desormais sous-allocation de _FSolveAlloc
                           * _CoeffJacMax; // desormais sous-allocation de _FSolveAlloc
  double                   * _LocalGridX,  // desormais sous-allocation de _FSolveAlloc
                           * _LocalGridDX; // desormais sous-allocation de _FSolveAlloc

  double                     _GiveUpWidth;
  CATLONG32                  _SingularityMaxDepth,

                             _DSolveDepth;
  CATLONG32                  _DSolveCounter;

  CATBoolean                 _EasySolverOn;

  double                   * _VerySuspectCoeffs;

  //                                       // XScale data
  //                                       // -----------
  double                   * _mu ,
                           * _lambda; 
  CATBoolean                 _ToBeScaled;
  double                     _EpsSolRelative;
  double                     _EpsSol;
  CATMathAttrScaleOption     _ScaleOption ;
  int                        _UseScaleOption ;
  int                        _UnScaleX_Spy,      //NLD250208 for debug purpose
                             _ScaleFX_Spy ;      //NLD250208 for debug purpose
  const CATTolerance       & _TolObject;

  // if _InterSol!=0, _InterSol is an array of _N double used by
  // Newton to keep the latest non inside point 
  // if it does no succeed.
  // Useful for the homotopy operators. Also used by other operators.
  double                   * _InterSol; 

};

//===========================================================================
//                                 INLINE Methods
//===========================================================================

//--------------------------------------------------------------------------
 CATLONG32                     CATMathSystem::GetNumberOfVariables ()
{
  return _N;
}




#endif  

