#ifndef CATMathArctanCosX_h
#define CATMathArctanCosX_h

// COPYRIGHT DASSAULT SYSTEMES  1999

//=============================================================================
// 29/09/11 R1Y Added access functions (for comparing geometries).
//=============================================================================

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
#include "CATIACGMLevel.h"
#include "YN000FUN.h"

#include "CATMathFoundationX.h"

class ExportedByYN000FUN CATMathArctanCosX : public CATMathFoundationX
{
 public:
  CATMathArctanCosX(const double a=1.0,
			              const double b=1.0,
			              const double c=1.0,
			              const double d=1.0,
			              const double e=1.0);

  CATMathArctanCosX(const double* ArrayOfData);
  CATCGMNewClassArrayDeclare;

  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------

  CATMathClassId IsA() const;
  int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
  CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
  CATBoolean IsATypeOf(const CATMathFunctionXTypeId iType) const;  
  CATBoolean IsOption(const CATMathOption iOption) const;

  double GetCoeffA() const;
  double GetCoeffB() const;
  double GetCoeffC() const;
  double GetCoeffD() const;
  double GetCoeffE() const;

  CATMathFunctionX * Duplicate() const;
  CATMathFunctionX * DeepDuplicate() const;
#if defined ( CATIACGMR216CAA )
  CATMathFunctionX * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
#endif
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
   
  //- operator <<
  friend ExportedByYN000FUN ostream & operator <<
    (ostream& os, CATMathArctanCosX & f);

 private:
  double _a, _b, _c, _d, _e;
};
#endif
