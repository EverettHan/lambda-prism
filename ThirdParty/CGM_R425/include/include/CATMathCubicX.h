// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATMathCubicX :
// Derived class of polynoms of 3 degrees
//
//=============================================================================
// Usage notes:
// Base class : CATMathPolynomX
//
//=============================================================================

#ifndef CATMathCubicX_H
#define CATMathCubicX_H

#include "YN000FUN.h"

#include "CATMathDef.h"
#include "CATMathPolynomX.h"

class ExportedByYN000FUN CATMathCubicX : public CATMathPolynomX
{
  public :
  //---------------------------------------------------------------
  // Constructors
  //---------------------------------------------------------------
  CATMathCubicX (const double *Array=0);
  CATMathCubicX (const CATMathCubicX &p);
  
  //---------------------------------------------------------------
  // Destructor
  //---------------------------------------------------------------
  ~CATMathCubicX();
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
	/** @nodoc */
  virtual CATBoolean _IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;
 
  //---------------------------------------------------------------
  // Methods
  //---------------------------------------------------------------
  void SetCoefficients (const double *Array);
  void GetCoefficients(double * c) const;
  CATMathClassId IsA () const;
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
  double _poly[4];
  

};

#endif

 
