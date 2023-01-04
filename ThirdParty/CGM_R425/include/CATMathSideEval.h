#ifndef CATMathSideEval_H
#define CATMathSideEval_H

// COPYRIGHT DASSAULT SYSTEMES  2000

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/**
 * Defines the side of the law at the parameter where to evaluate.
 * <br>Useful in case of non continuous junctions.
 * @param CATMathEvalLeft
 * The evaluation is made at the left side (in the parameterization sense) of the parameter.
 * @param CATMathEvalRigth
 * The evaluation is made at the right side (in the parameterization sense) of the parameter.
 */
enum CATMathSideEval
{
  CATMathSideEvalLeft=0,
  CATMathSideEvalRight=1
};

#endif
