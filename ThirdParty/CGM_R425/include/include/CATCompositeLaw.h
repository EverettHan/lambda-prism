#ifndef CATCompositeLaw_h
#define CATCompositeLaw_h

// COPYRIGHT DASSAULT SYSTEMES 2000

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATLaw.h"
#include "CATMathSideEval.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCompositeLaw ;
#else
extern "C" const IID IID_CATCompositeLaw ;
#endif


/**
 * Interface for the piecewise laws.
 * <br>Each piece of the law is C2 continuous, but the junction between the laws
 * are not constraint: they can even be not continuous.
 */
class ExportedByCATGMGeometricInterfaces CATCompositeLaw : public CATLaw
{
  CATDeclareInterface;

public:
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  /** 
   * Evaluates <tt>this</tt> CATCompositeLaw.
   * @param iT
   * The global parameter on the law.
   * @param iSide
   * The side on which the evaluation is done. At the law extremities or on an area with sufficient continuity,
   * the result is the same whether evaluating at the left or at the right.
   * @return
   * The evaluated value.
   */
  virtual double            EvalWithSide                    (      double                iT                   ,
                                                                   CATMathSideEval       iSide                )    const = 0 ;

  /** 
   * Evaluates the first derivative of <tt>this</tt> CATCompositeLaw.
   * @param iT
   * The global parameter on the law.
   * @param iSide
   * The side on which the evaluation is done. At the law extremities or on an area with sufficient continuity,
   * the result is the same whether evaluating at the left or at the right.
   * @return
   * The value of the first derivative.
   */
  virtual double            EvalFirstDerivWithSide          (      double                iT                   ,
                                                                   CATMathSideEval       iSide                )    const = 0 ;

  /** 
   * Evaluates the second derivative of <tt>this</tt> CATCompositeLaw.
   * @param iT
   * The global parameter on the law.
   * @param iSide
   * The side on which the evaluation is done. At the law extremities or on an area with sufficient continuity,
   * the result is the same whether evaluating at the left or at the right.
   * @return
   * The value of the second derivative.
   */
  virtual double            EvalSecondDerivWithSide         (      double                iT                   ,
                                                                   CATMathSideEval       iSide                )    const = 0 ;

  /** 
   * Evaluates the third derivative of <tt>this</tt> CATCompositeLaw.
   * @param iT
   * The global parameter on the law.
   * @param iSide
   * The side on which the evaluation is done. At the law extremities or on an area with sufficient continuity,
   * the result is the same whether evaluating at the left or at the right.
   * @return
   * The value of the third derivative.
   */
  virtual double            EvalThirdDerivWithSide          (      double                iT                   ,
                                                                   CATMathSideEval       iSide                )    const = 0 ;


  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  /** 
   * @nodoc
   */
  virtual void              InsertFunction                  (const CATLONG32             iNbrOfFunction       ,
                                                             const double             *  borders              ,
                                                             const CATMathFunctionX  **  functions            ) = 0;

};

CATDeclareHandler(CATCompositeLaw,CATLaw);

#endif

