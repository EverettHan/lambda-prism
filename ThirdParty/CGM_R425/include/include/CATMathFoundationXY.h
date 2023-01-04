#ifndef CATMathFoundationXY_H
#define CATMathFoundationXY_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "YN000FUN.h"
#include "CATMathFunctionXY.h"


/**
 * Class representing a pre-defined scalar function of two variables.
 *  <pre> F: RxR   -> R
 *          (x,y)  -> F(x,y)
 * </pre>
 */ 
class ExportedByYN000FUN CATMathFoundationXY : public CATMathFunctionXY 
{

 public:
  
 /** 
 * Evaluates <tt>this</tt> CATMathFoundationXY.
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFoundationXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFoundationXY is evaluated.
 * @return
 * The result of the evaluation.
 */
  virtual double Eval(const double & iX, const double & iY) const=0;

 /** 
 * Evaluates the first partial derivative with respect to the first variable of <tt>this</tt> CATMathFoundationXY.
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFoundationXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFoundationXY is evaluated.
 * @return
 * The value of the first partial derivative with respect to the first variable.
 */
  virtual double EvalFirstDerivX(const double & iX, const double & iY) const=0;

 /** 
 * Evaluates the first partial derivative with respect to the second variable of <tt>this</tt> CATMathFoundationXY.
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFoundationXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFoundationXY is evaluated.
 * @return
 * The value of the first partial derivative with respect to the second variable.
 */
  virtual double EvalFirstDerivY(const double & iX, const double & iY) const=0;
 
 /** 
 * Evaluates the second partial derivative of <tt>this</tt> CATMathFoundationXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFoundationXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFoundationXY is evaluated.
 * @return
 * The value of the second partial derivative.
 */
  virtual double EvalSecondDerivX2(const double & iX, const double & iY) const=0;

 /** 
 * Evaluates the second partial derivative of <tt>this</tt> CATMathFoundationXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFoundationXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFoundationXY is evaluated.
 * @return
 * The value of the second partial derivative.
 */
  virtual double EvalSecondDerivXY(const double & iX, const double & iY) const=0;

 /** 
 * Evaluates the second partial derivative of <tt>this</tt> CATMathFunctionXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @return
 * The value of the second partial derivative.
 */
  virtual double EvalSecondDerivY2(const double & iX, const double & iY) const=0;
   
  
 /** @nodoc  Not Published  */
  virtual CATMathFunctionXY* Duplicate() const = 0;

 /** @nodoc  Not Published  */
  virtual CATMathFunctionXY* DeepDuplicate() const = 0;

  /** @nodoc Not Published  */
  virtual int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const= 0;
};

#endif
