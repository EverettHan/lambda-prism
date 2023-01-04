#ifndef CATMathLinearX_H
#define CATMathLinearX_H// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATMathLinearX :
// class of linear functions of one variable
//
//=============================================================================
// Usage notes:
// Base class : CATMathPolynomX
//
//=============================================================================
// 13/02/08 NLD XScale. ajout argument iScaleOption a ComputeOptimalImage() en R19
// 27/01/09 NLD Interface R20 (SoftwareConfiguration) et deflaggage R19 pour ComputeOptimalImage
// 13/04/11 NLD Deflaggage R20 pour ComputeOptimalImage()
//=============================================================================
#include "CATIACGMLevel.h"
#include "YN000FUN.h"

#include "CATMathDef.h"
#include "CATMathPolynomX.h"


class ExportedByYN000FUN CATMathLinearX : public CATMathPolynomX
{
public :
  //---------------------------------------------------------------
  // Constructors
  //---------------------------------------------------------------
  
  // F(t) = iScale * t + iShift
  CATMathLinearX (const double iScale, const double iShift);
  // F(t) = iArray[1] * t + iArray[0]
  CATMathLinearX (const double *iArray);
  // Copy
  CATMathLinearX (const CATMathLinearX &iL);
  // Construction method
  void SetCoefficients (const double *iArray);
  
  //---------------------------------------------------------------
  // Destructor
  //---------------------------------------------------------------
  ~CATMathLinearX();
  CATCGMNewClassArrayDeclare;
  //---------------------------------------------------------------
  // Stream
  //---------------------------------------------------------------
#if defined ( CATIACGMV5R21 )
   virtual short GetStreamDomainType(char ioDomain[3]) const;
#else
   virtual short GetStreamType() const;
#endif
  void Stream( CATMathStream &oStr, const char iLabelReserved[] = "") const;
  virtual size_t  GetStaticMemoryBytes() const;   
  /** @nodoc */
  virtual CATBoolean _IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;

  
  //---------------------------------------------------------------
  // Information Methods
  //---------------------------------------------------------------

  void GetCoefficients(double *oCoeff) const;
  double GetScale() const;
  double GetShift() const;
  CATBoolean IsMonotone(const CATMathInterval & iD,CATLONG32 & oMonotonicity) const;

  CATMathClassId IsA () const;
  int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
  CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
  CATBoolean IsATypeOf(const CATMathFunctionXTypeId iClassId) const;
  
  //---------------------------------------------------------------
  // Evaluators
  //---------------------------------------------------------------
  double Eval(const double & iT) const;
  double EvalFirstDeriv (const double & iT) const;
  double EvalSecondDeriv(const double & iT) const;
  double EvalThirdDeriv (const double & iT) const;
  void Eval(const double iT, const CATMathOption iOption,
  double * oF, double * oDF=0, double * oD2F=0) const;
  void Eval(const CATMathInterval & iD, const CATLONG32 iNbPoints,
  const CATMathOption iOption,
  double * oF, double * oDF=0, double * oD2F=0) const; 
  
  CATMathInterval Eval(const CATMathInterval & iD) const;
  virtual CATMathInterval ComputeOptimalImage(const CATMathInterval & I,
                                              const CATTolerance & iTolObject=CATGetDefaultTolerance(),
                                              CATMathAttrScaleOption* iScaleOption=NULL,
                                              CATSoftwareConfiguration* iConfig=NULL
                                             ) const;
  CATMathInterval EvalFirstDeriv(const CATMathInterval & iD) const;
  CATMathInterval EvalSecondDeriv(const CATMathInterval & iD) const;
  CATMathInterval EvalThirdDeriv(const CATMathInterval & iD) const;

  //-----------------------------------------------------------------
  // - Integrate
  //-----------------------------------------------------------------
  virtual double Integrate(const CATMathInterval & iD, const double iTol) const;

  //-----------------------------------------------------------------
  //- Derivative
  //-----------------------------------------------------------------
  CATMathFunctionX * CreateDeriv () const;
  
  //-----------------------------------------------------------------
  // Duplicator
  //-----------------------------------------------------------------
  virtual CATMathFunctionX * Duplicate() const;
  virtual CATMathFunctionX * DeepDuplicate() const;
#if defined ( CATIACGMR216CAA )
  CATMathFunctionX * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
#endif

     
protected:
  double _poly[2];
  
  // protected methods
  virtual CATMathFunctionX * FormalCompositionX(const CATMathFunctionX * iF) const;
  
  
  virtual CATMathFunctionX * FormalCombination(const CATLONG32 iN, 
    const CATMathFunctionX ** iFunc,
    const double * iCoeff, 
    const double iConstant) const;


};
#endif
