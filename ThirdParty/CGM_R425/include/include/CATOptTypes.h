// Usage notes:
//=============================================================================
// 15/01/2020 : SMT1 : Added CATOptRealND and CATSetOfOptRealND
//=============================================================================


#ifndef CATOptTypes_h
#define CATOptTypes_h

// System/PublicInterfaces
#include "CATString.h"
#include "CATListOfDouble.h"
#include "CATMathLimits.h"


//-----------------------------------------------------------------------
typedef double CATOptReal;
typedef CATListOfDouble CATLISTV_CATOptReal; 
#define CATOptRealMax  CATdoubleMax; //1.797693134862348623157E+308

class CATOptRealND
{
public:
    CATOptRealND(const CATLONG32 iSpaceSize);
    CATOptRealND(const CATLONG32 iSpaceSize, CATOptReal* iCoords);
    ~CATOptRealND();

    inline CATLONG32 GetDim() {return _SpaceSize;}
    CATLONG32 Compare(CATOptRealND &iCompareTo, CATLONG32 iDim);
    inline const CATOptReal * GetCoords(){return _Coords;}

    CATOptReal& operator[] (int index);
    void operator=(const CATOptRealND &iAssign );
    
private:
    CATLONG32 _SpaceSize;
    CATOptReal * _Coords;
};

#include "CATLISTPP_Clean.h"
#define CATLISTPP_Append
#define CATLISTPP_RemoveAll
#include "CATLISTPP_Declare.h"
CATLISTPP_DECLARE( CATOptRealND)
typedef CATLISTP(CATOptRealND) CATSetOfOptRealND;

enum CATOptMethodId  //mo =optim method 
{
  omUndefined,
  omDefault,
  omLevenbergMarquardt,
  omNelderMead,
  omParticuleAndLocal,
  omParticuleSwarm,
  omBFGS,
  omSQP, 
  omGA
};

enum CATClusteringMethodId  //mc =clustering method
{
  cmUndefined,
  cmDensity,
  cmKMeans,
  cmFuzzy,
  cmMinimum,
  cmMinimumSpanningTree
};

enum CATOptNorm
{
  nNone        ,
  nAbsolute    , // anciennement "nAbsolue"
  nEuclidian   , // anciennement "nEuclidienne"
  nInfinite      // anciennement "nInifini" (BRAVO)
};

enum CATOptSparseMode
{
  No,
  Auto,
  Sparse
};

enum CATOptAcceleratorMode
{
  NoAcceleratorMode,
  RadialInterpolation,
  BarycenterApproximation,
};

enum CATOptParamType
{
  optNone,
  optBoolean,
  optLong,
  optULong,
  optReal,
  optRealArray,
  optOptMethodId,
  optClustMethodId,
  optSparseMode,
  optAcceleratorMode
};

enum CATOptExprType
{
  sObjective,
  sEqualityConstraint,
  sInequalityConstraint,
  sBoundConstraint
};


enum CATOptInternalMethod
{
  imDefault_SelectedMethod,
  imHybrid_GlobalMethod, 
  imHybrid_LocalMethod,
  imGlobal_FinalClusteringMethod,
  imGlobal_ClusteringMethodForRun
};


typedef CATULONG32 CATOptDescription; 
#define CATOptDescription_Default             (CATOpt_HYBRID | CATOpt_MULTIPLE_SOLUTIONS | CATOpt_EQUATION_WHITEBOX | CATOpt_GRADIENT | CATOpt_HESSIAN)
#define CATOptDescription_LevenbergMarquardt  (CATOpt_LOCAL                              | CATOpt_EQUATION_WHITEBOX | CATOpt_GRADIENT                 )
#define CATOptDescription_NelderMead          (CATOpt_LOCAL                                                                                           )
#define CATOptDescription_ParticuleAndLocal   (CATOpt_HYBRID | CATOpt_MULTIPLE_SOLUTIONS                                                              )
#define CATOptDescription_ParticuleSwarm      (CATOpt_GLOBAL | CATOpt_MULTIPLE_SOLUTIONS                                                             )


#define CATOpt_Undefined 0
#define CATOpt_LOCAL 1
#define CATOpt_GLOBAL 2
#define CATOpt_HYBRID 3            //local and global
#define CATOpt_MULTIPLE_SOLUTIONS 4
#define CATOpt_EQUATION_WHITEBOX 8
#define CATOpt_GRADIENT 16
#define CATOpt_HESSIAN 32


#define CATOpt_UsedFunctionValues 1
#define CATOpt_ComputeClusterNb 2
#define CATOpt_UsedSpecifiedClusterNb 3  

enum CATOptParamLabel
{
  plUndefined,
  cplDensity_MinimumPointNumber,
  cplDensity_SphereRadius,
  cplKMeans_MaxIteration,
  cplKMeans_Epsilon,
  cplKMeans_Fuzzyness,
  oplGlobal_StartPoints,                      // (CATULONG32, CATOptReal *) sets initial particles positions given by the user.
  oplGlobal_ClusterNumber,
  oplGlobal_RealClusterNumber,
  oplGlobal_PopulationSize,                   // (Get/Set ->CATULONG32)
  oplGlobal_RandomSeed,                       // (Get/Set -> int)
  oplGlobal_SynchronousMode,                  // (Get/Set -> CATBoolean)
  oplGlobal_AcceleratorMode,                  // (Get/Set -> CATOptAcceleratorMode)
  oplGlobal_NeighbourhoodSize,                // (Get/Set -> CATULONG32)
  oplGlobal_IsNeighbourhoodFixed,             // (Get/Set -> CATBoolean)
  oplGlobal_ClusteringPeriod,                 // (Get/Set -> CATULONG32)
  oplGlobal_ReplayNumber,                     // (Get/Set -> CATULONG32)
  oplGlobal_IsReallocated,                    // (Get/Set -> CATBoolean)
  oplGlobal_FinalClusteringMethodName,        // (Get/Set -> CATString)
  oplGlobal_ClusteringMethodNameForRun,       // (Get/Set -> CATString)
  oplLocal_WithPerturbation,
  oplHybrid_GlobalMethodName,
  oplHybrid_LocalMethodName,
  oplPSO_IntrinsicParameters,
  oplNM_IntrinsicParameters,
  oplNM_InitialSimplexSize,
  oplNM_SmallestSimplexSize,
  oplLM_InitialLambda,
  oplLM_NbIterationMax,
  oplLM_SparseMode,
  oplLM_Discrepancy,
  oplGA_CrossParam,
  oplGA_MutatParam,
  oplGA_FitnessReference,
  oplGA_Process,
  oplGA_IdemFitnessCount
};


//-----DEPRECATED
static CATString const CATMathOpti_Method_Default           = "CATOptDefaultOptimizer";
static CATString const CATMathOpti_Method_LevenbergMarquardt= "CATOptLevenbergMarquardt";
static CATString const CATMathOpti_Method_NelderMead        = "CATOptNelderMeadMethod";
static CATString const CATMathOpti_Method_ParticulemLocal   = "CATOptParticuleOptimizationLocalMethod";
static CATString const CATMathOpti_Method_ParticuleSwarm    = "CATOptParticuleSwarmOptimization";

typedef CATOptReal (* CATOptFunctional)(CATOptReal const *, void const *);
typedef void (* CATOptGradient)(CATOptReal const *, CATOptReal *, void const *);
typedef void (* CATOptHessian) (CATOptReal const *, CATOptReal *, void const *);


typedef CATOptReal (* CATOptNormRes)(CATOptReal &   );
typedef void (*CATOptNormAcc)      (CATOptReal &, CATOptReal const &);


//-----------------------------------------------------------------------
#endif
