#ifndef CATMathCurveFunction_H
#define CATMathCurveFunction_H

// COPYRIGHT DASSAULT SYSTEMES  2000
// 10/12/07 NLD XScale: ajout SetScale() et _Scale, _OKScale, _H1, _H2

#include "MathGeo.h"

#include "CATMathDef.h"

class CATMathPoint;
class CATMathVector;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

#include "CATIAV5Level.h"
#include "CATCGMVirtual.h"

/**
 * Base class representing a mathematical parametric curve
 * <tt> t -> M(t) </tt> from <tt>R</tt>  to <tt>R3</tt>.<br>
 */
class ExportedByMathGeo CATMathCurveFunction : public CATCGMVirtual
{
  public:

/**
 * Returns the class name of <tt>this</tt>  CATMathCurveFunction.
 * @return
 * A pointer to the class name.
 */
   virtual CATMathClassId IsA() const = 0;

/** 
 * Evaluates <tt>this</tt> CATMathCurveFunction.
 * @param iParam
 * The variable value where <tt>this</tt> CATMathCurveFunction is evaluated.
 * @param oResult
 * The result of the evaluation.
 */
   virtual void EvalPoint (double iParam, CATMathPoint & oResult) const = 0;

/** 
 * Evaluates the first derivative of <tt>this</tt> CATMathCurveFunction.
 * @param iParam
 * The variable value where <tt>this</tt> CATMathCurveFunction is evaluated.
 * @param oResult
 * The result of the evaluation.
 */
   virtual void EvalFirstDeriv(double iParam, CATMathVector & oResult) const;

/** 
 * Evaluates the second derivative of <tt>this</tt> CATMathCurveFunction.
 * @param iParam
 * The variable value where <tt>this</tt> CATMathCurveFunction is evaluated.
 * @param oResult
 * The result of the evaluation.
 */
   virtual void EvalSecondDeriv(double iParam, CATMathVector & oResult) const;

/**
 * Tests if an evaluator is available for <tt>this</tt> CATMathCurveFunction.
 * @param iOption
 * The type of evalution.
 * <br><b>Legal values</b>:
 * <dl> <dt>OptionEval   </dt>  <dd>  evaluation of the function
 * <dt>OptionEvalFirstDeriv   </dt>  <dd>  evaluation of the first derivative of the function
 * <dt>OptionEvalSecondDeriv</dt>  <dd>  evaluation of the second derivative of the function
 * <dt>OptionEvalThirdDeriv</dt>  <dd>  evaluation of the third derivative of the function
 * </dl>
 * @return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if the evaluation is available for <tt>this</tt> CATMathCurveFunction,
 * <tt>FALSE</tt> otherwise.
 */
   virtual CATBoolean IsOption (const CATMathOption iOption) const;
   
/** 
 * Set the limits of definition of <tt>this</tt> CATMathCurveFunction.
 * @param iStart
 * The low limitation of the interval of definition.
 * @param iEnd
 * The high limitation of the interval of definition.
 */
   virtual void SetLimits(double iStart, double iEnd);



   void SetScale(double iScale) ;

   virtual ~CATMathCurveFunction();
   CATMathCurveFunction();
 
  private:
      double * _Limits;
      double _Scale ;
      double _H1 ;
      double _H2 ;
      int _OKScale ;

 };
#endif





