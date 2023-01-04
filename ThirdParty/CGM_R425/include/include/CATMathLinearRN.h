// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathLinearRN :
// Class of linear functions of N variables
//
//===================================================================
// Usage notes:
//
//===================================================================
// XX/XX/XX XXX Creation
// 07/03/13 NLD XScale:
//              - les deux constructeurs avec arguments recoivent iConfig et iTolObject
//===================================================================


#ifndef CATMathLinearRN_h
#define CATMathLinearRN_h

#include "YN000FUN.h"

#include "CATMathFunctionRN.h"
#include "CATCGMNewArray.h"
class CATSoftwareConfiguration;
class CATTolerance;
//-------------------------------------------------------------------
class ExportedByYN000FUN CATMathLinearRN : public CATMathFunctionRN
{
 public:
  //-----------------------------------------------------------------
  //- Object Management
  //-----------------------------------------------------------------
  CATMathLinearRN(const CATMathLinearRN & iF);
  CATMathLinearRN(const CATLONG32               & iN         = 0,
                        CATSoftwareConfiguration* iConfig    = 0,
                  const CATTolerance            * iTolObject = 0
                 );
  CATMathLinearRN(const CATLONG32               & iN,
                  const double                  * iCoef,
                  const double                  & iConstant,
                        CATSoftwareConfiguration* iConfig    = 0,
                  const CATTolerance            * iTolObject = 0
                 );
  ~CATMathLinearRN();
  CATMathFunctionRN * Duplicate() const;
  CATCGMNewClassArrayDeclare;
  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------
  CATMathClassId IsA                () const;
  int            GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
  CATBoolean     IsAKindOf          (const CATMathClassId iClassId) const;
  CATBoolean     IsOption           (const CATMathOption iOption) const;

  //-----------------------------------------------------------------
  // Edition methods
  //-----------------------------------------------------------------
  void Set(const CATLONG32 & iN, const double * iCoef,
           const double & iConstant);

  //-----------------------------------------------------------------
  // Evaluators on doubles
  //-----------------------------------------------------------------   

  double Eval           (const double * iX) const;

  // In the following, iVar0, iVar1 and iVar2 represent the index of the variable
  // between 0 and _N-1
  double          EvalFirstDeriv (const CATLONG32 & iVar0,
                                  const double * iX) const;

  double          EvalSecondDeriv(const CATLONG32 & iVar0,
                                  const CATLONG32 & iVar1,
                                  const double * iX) const;

  double          EvalThirdDeriv (const CATLONG32 & iVar0,
                                  const CATLONG32 & iVar1,
                                  const CATLONG32 & iVar2,
                                  const double * iX) const;

  //
  // Evaluator of function and derivatives at the same time :
  //
  void            Eval           (const double        * iX,
                                  const CATMathOption   iOption,
                                        double        * f      ,
                                        double        * df     = 0,
                                        double        * d2f    = 0) const;
   
  //-----------------------------------------------------------------
  // Evaluators on intervals
  //-----------------------------------------------------------------
  CATMathInterval Eval           (const CATMathIntervalND & iD) const;
  CATMathInterval EvalFirstDeriv (const CATLONG32 & iVar0,
                                  const CATMathIntervalND & iD) const;
  CATMathInterval EvalSecondDeriv(const CATLONG32 & iVar0, const CATLONG32 & iVar1,
                                  const CATMathIntervalND & iD) const;
  CATMathInterval EvalThirdDeriv (const CATLONG32 & iVar0, const CATLONG32 & iVar1, const CATLONG32 & iVar2,
                                  const CATMathIntervalND & iD) const;
  //-----------------------------------------------------------------
  // Composition creation
  //-----------------------------------------------------------------

  CATMathFunctionX  * CreateCompositionX (const CATMathFunctionX  ** iTabFunctionX)  const;
  CATMathFunctionXY * CreateCompositionXY(const CATMathFunctionXY ** iTabFunctionXY) const;

  //-----------------------------------------------------------------
  //- Overloaded Operators
  //-----------------------------------------------------------------
  CATMathLinearRN & operator = (const CATMathLinearRN & iF);

 private:
  double * _coef;
  double _constant;
  double _Buffer[3];
};

#endif
