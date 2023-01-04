#ifndef CATMathFoundationX_H
#define CATMathFoundationX_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "YN000FUN.h"
#include "CATMathFunctionX.h"


/**
 * Class representing a predefined scalar function of one variable.
 *  <pre> F: R   -> R
 * x   -> F(x)
 * </pre>
 */ 
class ExportedByYN000FUN CATMathFoundationX : public CATMathFunctionX 
{

 public:

 /** 
 * Evaluates <tt>this</tt> CATMathFoundationX.
 * @param iT
 * The variable value where <tt>this</tt> CATMathFoundationX is evaluated.
 * @return
 * The result of the evaluation.
 */
 virtual double Eval(const double & iT) const = 0;

 /** 
 * Evaluates the first derivative of <tt>this</tt> CATMathFoundationX.
 * @param iT
 * The variable value where <tt>this</tt> CATMathFoundationX is evaluated.
 * @return
 * The result of the evaluation.
 */
 virtual double EvalFirstDeriv(const double & iT) const = 0;

 /** 
 * Evaluates the second derivative of <tt>this</tt> CATMathFoundationX.
 * @param iT
 * The variable value where <tt>this</tt> CATMathFoundationX is evaluated.
 * @return
 * The result of the evaluation.
 */
 virtual double EvalSecondDeriv(const double & iT) const = 0;

 /** @nodoc  Not Published  */
	virtual CATMathFunctionX * Duplicate() const = 0;

 /** @nodoc  Not Published  */
 virtual CATMathFunctionX * DeepDuplicate() const  = 0;

  /** @nodoc Not Published  */
  virtual int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const= 0;
};

#endif

