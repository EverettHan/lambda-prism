// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATMathQuinticX :
// Derived class of polynoms of five degrees
//
//=============================================================================
// Usage notes:
// Base class : CATMathPolynomX
//
//=============================================================================

#ifndef CATMathQuinticX_H
#define CATMathQuinticX_H

#include "YN000FUN.h"

#include "CATMathDef.h"
#include "CATMathPolynomX.h"

class CATMathStream;


class ExportedByYN000FUN CATMathQuinticX : public CATMathPolynomX
{
  public :
  //---------------------------------------------------------------
  // Constructors
  //---------------------------------------------------------------
  CATMathQuinticX (const double *Array=0, const double iShift=0.);
  CATMathQuinticX (const double x0, const double dx0, const double d2x0,
			       const double x1, const double dx1, const double d2x1,
			       const double DeltaParam);
  CATMathQuinticX (const CATMathQuinticX &p);
  
  //---------------------------------------------------------------
  // Destructor
  //---------------------------------------------------------------
  ~CATMathQuinticX();
  CATCGMNewClassArrayDeclare;

  //---------------------------------------------------------------
  // Stream
  //---------------------------------------------------------------
#if defined ( CATIACGMV5R21 )
   virtual short GetStreamDomainType(char ioDomain[3]) const;
#else
   virtual short GetStreamType() const;
#endif
  void Stream( CATMathStream &Str, const char iLabelReserved[] = "") const;
  virtual size_t  GetStaticMemoryBytes() const;   
   /**
   * @nodoc
   */   
   virtual CATBoolean _IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;
  
  //---------------------------------------------------------------
  // Methods
  //---------------------------------------------------------------
  void SetCoefficients (const double *Array);
  void GetCoefficients(double * c) const;
  CATMathClassId IsA () const;
	/** @nodoc */
  int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
  CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
  CATBoolean IsATypeOf(const CATMathFunctionXTypeId iClassId) const;
  
  //---------------------------------------------------------------
  // Evaluators
  //---------------------------------------------------------------
  double Eval(const double & t) const;
  double EvalFirstDeriv (const double & t) const;
  double EvalSecondDeriv(const double & t) const;
  double EvalThirdDeriv (const double & t) const;
  void Eval(const double t, const CATMathOption iOption,
	    double * f, double * df=0, double * d2f=0) const;
  
  CATMathInterval Eval(const CATMathInterval & x) const;
  CATMathInterval EvalFirstDeriv(const CATMathInterval & x) const;
  CATMathInterval EvalSecondDeriv(const CATMathInterval & x) const;
  CATMathInterval EvalThirdDeriv(const CATMathInterval & x) const;
  
  
     
private:
  double _poly[6];
  

};

#endif

 
