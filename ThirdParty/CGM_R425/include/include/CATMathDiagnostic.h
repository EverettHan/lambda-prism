#ifndef CATMathDiagnostic_H 
#define CATMathDiagnostic_H 

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
/**
 * Mathematical error diagnosis.
 * @param CATMathOK
 * No problem.
 * @param CATMathNullFunction
 * A null function cannot be taken into account.
 * @param CATMathConstantFunction
 * A constant function cannot be taken into account.
 * @param CATMathNullVector
 * A null vector cannot be taken into account.
 * @param CATMathInvalidDomain
 * The defined domain is not valid.
 * @param CATMathSingularSystem
 * A singular system cannot be solved.
 * @param CATMathSingularJacobian
 * A singular jacobian is encoutered.
 * @param CATMathMaxIteration
 * The convergence is not reached.
 * @param CATMathOutOfDomain
 * No solution inside the domain.
 * @param CATMathNoConvergence
 * The convergence cannot be reached.
 * @param CATMathIllConditionnedSystem
 * The system is bad conditionned.
 * @param CATMathOneVariableFunction
 * Problem by using a function of one variable.
 */
typedef enum
{
CATMathOK = 0,
CATMathNullFunction,
CATMathConstantFunction,
CATMathNullVector,
CATMathInvalidDomain,
CATMathSingularSystem,
CATMathSingularJacobian,
CATMathMaxIteration,
CATMathOutOfDomain,
CATMathNoConvergence,
CATMathIllConditionnedSystem,
CATMathOneVariableFunction
}
CATMathDiagnostic;


#endif
