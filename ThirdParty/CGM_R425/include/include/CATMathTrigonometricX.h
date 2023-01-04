#ifndef CATMathTrigonometricX_H
#define CATMathTrigonometricX_H

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1999
//
//=============================================================================
// 05/10/07 NLD XScale _TolObject devient public
// 13/02/08 NLD XScale. ajout argument iScaleOption a ComputeOptimalImage() en R19
// 27/01/09 NLD Interface R20 (SoftwareConfiguration) et deflaggage R19 pour ComputeOptimalImage
// 27/01/09 NLD Interface R20 (CATSoftwareConfiguration) pour Solve()
// 13/04/11 NLD Deflaggage R20 pour ComputeOptimalImage() et Solve()
// 29/09/11 R1Y Added access functions (for comparing geometries).
// 14/12/12 NLD _TolObject devient un pointeur
//=============================================================================
#include "CATIACGMLevel.h"

#include "YN000FUN.h"

#include "CATMathFoundationX.h"
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

class ExportedByYN000FUN CATMathTrigonometricX : public CATMathFoundationX
{
public:
  CATMathTrigonometricX(const double a=1.0,
    const double b=0.0,
    const double c=0.0,
    const double w=1.0,
    const CATTolerance & iTolObject = CATGetDefaultTolerance());
  
  CATMathTrigonometricX(const double* ArrayOfData, const CATTolerance & iTolObject = CATGetDefaultTolerance());
  CATCGMNewClassArrayDeclare;

  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------
  
  CATMathClassId IsA() const;
  /** @nodoc */
  int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
  CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
  CATBoolean IsATypeOf(const CATMathFunctionXTypeId iType) const;  
  CATBoolean IsOption(const CATMathOption iOption) const;
  
  CATMathFunctionX * Duplicate() const;
  CATMathFunctionX * DeepDuplicate() const;
#if defined ( CATIACGMR216CAA )
  CATMathFunctionX * DeepDuplicateWithTol(const CATTolerance * ipTolObject) const;
#endif
  
  double GetAmplitude() const;
  double GetPhase() const;
  double GetFrequency() const;
  double GetDCOffset() const;

  //-----------------------------------------------------------------
  // Stream 
  //-----------------------------------------------------------------
#if defined ( CATIACGMV5R21 )
   virtual short GetStreamDomainType(char ioDomain[3]) const;
#else
   virtual short GetStreamType() const;
#endif
  void Stream( CATMathStream& Str, const char iLabelReserved[] = "" ) const;
  virtual size_t  GetStaticMemoryBytes() const;   
  /** @nodoc */
  virtual CATBoolean _IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;
  
  //-----------------------------------------------------------------
  // Evaluators on doubles
  //-----------------------------------------------------------------   
  double Eval(const double & t) const;
  double EvalFirstDeriv(const double & t) const;
  double EvalSecondDeriv(const double & t) const;
  double EvalThirdDeriv(const double & t) const;
  
  //
  // Evaluator of function and derivatives at the same time :
  //
  void Eval(const double t, const CATMathOption iOption,
    double * f, double * df = 0, double * d2f = 0) const;
  
  //
  // MultiEvaluator on a regular one dimensional grid on I.
  //
  void Eval(const CATMathInterval & I, const CATLONG32 NbPoints,
    const CATMathOption iOption,
    double * f, double * df = 0, double * d2f = 0) const;
  
  //-----------------------------------------------------------------
  // Evaluators on intervals
  //-----------------------------------------------------------------
  CATMathInterval Eval(const CATMathInterval & Dx) const;
  CATMathInterval EvalFirstDeriv(const CATMathInterval & Dx) const;
  CATMathInterval EvalSecondDeriv(const CATMathInterval & Dx) const;
  CATMathInterval EvalThirdDeriv(const CATMathInterval & Dx) const;
  //
  // Interval evaluator of function and derivatives at the same time :
  //
  void Eval(const CATMathInterval & I, const CATMathOption iOptions,
    CATMathInterval * f, CATMathInterval * df = 0, 
    CATMathInterval * d2f = 0) const;
  CATMathInterval ComputeOptimalImage(const CATMathInterval & I, 
                                      const CATTolerance & iTolObject=CATGetDefaultTolerance(),
                                      CATMathAttrScaleOption* iScaleOption=NULL,
                                      CATSoftwareConfiguration* iConfig=NULL
                                     ) const;
 
  //- Derivative
  CATMathFunctionX * CreateDeriv () const;
  
  //-----------------------------------------------------------------
  //- Solve
  //-----------------------------------------------------------------
  CATMathDiagnostic Solve(const CATMathInterval & D,
                              CATMathSetOfPointsND & roots,
                        const CATMathAttrList * attributes=NULL,
                                CATSoftwareConfiguration* iConfig=NULL
                         ) const;
  
  //- operator <<
  friend ExportedByYN000FUN ostream & operator <<
    (ostream& os, CATMathTrigonometricX & f);
  
  // protected methods
protected:
  virtual CATMathFunctionX * FormalCombination(const CATLONG32 iN, 
    const CATMathFunctionX ** iFunc,
    const double * iCoef, 
    const double iConstant) const;
  
private:
  double _Amplitude, _Phase, _Freq, _DCOffset;
public:
  const CATTolerance * _TolObject; // const CATTolerance & _TolObject;
};
#endif
