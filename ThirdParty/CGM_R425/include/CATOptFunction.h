//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2011/06/03
//===================================================================
// CATOptFunction.cpp
// Header definition of class CATOptFunction
//===================================================================
//
// Usage notes:
//
//===================================================================
// 03/06/11 TE9 Creation                        2011-06-03 : T. Rose
// 06/04/12 ??? (N.LOSSING)
// 13/05/15 NLD Securisation de l'usage des macros par parenthesage des expressions
// 08/02/16 NLD Suppression des macros CATMATHCOORD2D() et CATMATHCOORD3D()
//              Renommage de CATOptNorme en CATOptNorm
//                        de SetNorme()  en SetNorm()
//              et        de GetNorme()  en GetNorm()
//                        de _norme      en _NormOpt
// 08/02/17 KJD - Addition of EvalJacobian which computes the jacobian matrix and 
//                the gradient of every function (vector size NbFunction) (with a norm)
//                WARNING : contrary to EvalGradient which computes the gradient according to the variables
//               (vector size NbVar) (with a norm)
//              - Management of gradient sparse jacobian 
//                 --EvalSparseJacobian + ComputeJacobianSparseSkeleton
//                 --_SparseData,_aVariableIndex, _aGradientIndex,_SparseGradMatrixSize;
//                   _SparseGradMatrixSize = nb of the nonzero coefficients of the jacobian matrix
//                   _aVariableIndex = new order of the variables such as the jacobian is the sparsest as possible
//                   _aGradientIndex = array storing the list of the new variable index of the nonzero coefficients
//                                     of the gradient for all the line of the matrix
//                                     Between each line is inserted the space size
// 10/10/18 KJD - Class not used anymore => under define
//                 (can't be deleted or migrated in private 
//                  because called in an off define in the protected class CATMathOptimizer)
//===================================================================

#ifndef CATOptFunction_H
#define CATOptFunction_H

#include "YN000OPT.h"
#include "CATDataType.h"
#include "CATOptTypes.h"
#include "CATMathOptimizer.h"
#include "CATIAV5Level.h"


// Les macros publiques devraient obeir a une nomenclature
// par exemple ici etre prefixees par CATOptFunction_
//   NLD130515
// NLD080216 #define CATMATHCOORD2D(i, j, jmax)          (i*jmax + j)
// NLD080216 #define CATMATHCOORD3D(i, j, k, jmax, kmax) (i*jmax*kmax + j*kmax + k)
//

//#ifdef CATMathOpt_OldArchi
//#define CATMATHNormalization(iresult, ivalueAddNorme)   \
//                                                        \
//switch (_NormOpt)                                       \
//{                                                       \
//case nAbsolute:                                         \
//  iresult += CATFabs(ivalueAddNorme);                   \
//  break;                                                \
//case nEuclidian:                                        \
//  iresult += ivalueAddNorme*ivalueAddNorme;             \
//  break;                                                \
//case nInfinite:                                         \
//  iresult = CATMax(iresult, CATFabs(ivalueAddNorme));   \
//  break;                                                \
//}                                                       \
//#endif
//-----------------------------------------------------------------------

class ExportedByYN000OPT CATOptFunction
{
public:
  CATOptFunction ();
  virtual ~CATOptFunction ();
#ifdef CATMathOpt_OldArchi
  /**
//   * @Deprecated 
   * Evals a function of the systeme
   * @param iIdx            The index of the function
   * @param iaX             The point function is evaluated
   * @return                The evaluation of the function
   */
  virtual CATOptReal EvalF           (CATULONG32 iIdx, CATOptReal const * iaX) = 0;
  /**
   * Evals systeme of function
   * @param iaX             The point where each function is evaluated
   * @return                The evaluation of the system (with a norm)
   */
  virtual CATOptReal Eval            (CATOptReal const * iaX);
  /**
   * Evals systeme of function
   * @param iaX             The point where each function is evaluated
   * @param oaEval          The evaluation of each function (size NbFunction)
   */
  virtual void       Eval            (CATOptReal const * iaX, CATOptReal * oaEval);
  /**
   * Evals systeme of function
   * @param iaX             The point where each function is evaluated
   * @param oaEval          The evaluation of each function (size NbFunction)
   * @return                The evaluation of the system (with a norm)
   */
  virtual CATOptReal Evals           (CATOptReal const * iaX, CATOptReal * oaEval = 0) = 0;


  /**
   * Evals a function differentiate of the systeme
   * @param iIdx            The index of the function
   * @param iVar            The variable from which each function is derived
   * @param iaX             The point differentiate is evaluated
   * @return                The evaluation of the differentiate
   */
  virtual CATOptReal EvalFirstDerivF (CATULONG32 iIdx, CATULONG32 iVar, CATOptReal const * iaX) = 0;
  /**
   * Evals systeme of function differentiate
   * @param iVar            The variable from which each function is derived
   * @param iaX             The point where each differentiate is evaluated
   * @return                The evaluation of the system of differentiate (with a norm)
   */
  virtual CATOptReal EvalFirstDeriv  (CATULONG32 iVar, CATOptReal const * iaX);
  /**
   * Evals systeme of function differentiate
   * @param iVar            The variable from which each function is derived
   * @param iaX             The point where each differentiate is evaluated
   * @param oaDerivs        The evaluation of each differentiate (size NbFunction)
   */
  virtual void       EvalFirstDeriv  (CATULONG32 iVar, CATOptReal const * iaX, CATOptReal * oaDerivs);
  /**
   * Evals systeme of function differentiate
   * @param iVar            The variable from which each function is derived
   * @param iaX             The point where each differentiate is evaluated
   * @param oaDerivs        The evaluation of each differentiate (size NbFunction)
   * @return                The evaluation of the system of differentiate (with a norm)
   */
  virtual CATOptReal EvalFirstDerivs (CATULONG32 iVar, CATOptReal const * iaX, CATOptReal * oaDerivs = 0) = 0;

  /**
  * Evaluates the jacobian matrix of the system
  * @param iaX            The point where gradient is evaluated
  * @param oaFuncGradient     The gradient of every function (vector size NbFunction) (with a norm)
  * @param oa2Gradient    The jacobian matrix (size NbFunction*NbVariable)
  * @return               The evaluation of the system of jacobian (with a norm)
  */
  CATOptReal EvalJacobian(const CATOptReal * iaX, const CATULONG32 & iaXSize, CATOptReal * oaFuncGradient, CATOptReal * oa2Gradient);
  CATOptReal EvalSparseJacobian(const CATOptReal * iaX, const CATULONG32 & iaXSize, CATOptReal * oaGradient, CATOptReal * oa2Gradient);

  /**
   * Evals a function 2nd differentiate of the systeme
   * @param iIdx            The index of the function
   * @param iVar1           The first variable
   * @param iVar2           The second variable
   * @param iaX             The point 2nd differentiate is evaluated
   * @return                The evaluation of the 2nd differentiate
   */
  virtual CATOptReal EvalSecondDerivF(CATULONG32 iIdx, CATULONG32 iVar1, CATULONG32 iVar2, CATOptReal const * iaX) = 0;
  /**
   * Evals systeme of function 2nd differentiate
   * @param iVar1           The first variable
   * @param iVar2           The second variable
   * @param iaX             The point where each 2nd differentiate is evaluated
   * @return                The evaluation of the system of 2nd differentiate (with a norm)
   */
  virtual CATOptReal EvalSecondDeriv (CATULONG32 iVar1, CATULONG32 iVar2, CATOptReal const * iaX);
  /**
   * Evals systeme of function 2nd differentiate
   * @param iVar1           The first variable
   * @param iVar2           The second variable
   * @param iaX             The point where each 2nd differentiate is evaluated
   * @param oaDerivs        The evaluation of each 2nd differentiate (size NbFunction)
   */
  virtual void       EvalSecondDeriv (CATULONG32 iVar1, CATULONG32 iVar2, CATOptReal const * iaX, CATOptReal * oaDerivs);
  /**
   * Evals systeme of function 2nd differentiate
   * @param iVar1           The first variable
   * @param iVar2           The second variable
   * @param iaX             The point where each 2nd differentiate is evaluated
   * @param oaDerivs        The evaluation of each 2nd differentiate (size NbFunction)
   * @return                The evaluation of the system of 2nd differentiate (with a norm)
   */
  virtual CATOptReal EvalSecondDerivs(CATULONG32 iVar1, CATULONG32 iVar2, CATOptReal const * iaX, CATOptReal * oaDerivs = 0) = 0;


  /**
   * Evals gradient of the systeme
   * @param iaX            The point where gradient is evaluated
   * @param oaGradient     The gradient of the system (vector size NbVariable) (with a norm)
   * @param oa2Gradient    The gradient of each function (size NbFunction*NbVariable)
   */
  virtual void       EvalGradient    (CATOptReal const * iaX, CATOptReal * oaGradient, CATOptReal * oa2Gradient = 0) = 0;


  /**
   * Evals hessian of the systeme
   * @param iaX            The point where hessian is evaluated
   * @param oa2Hessian     The hessian of the system (matrix size NbVariable*NbVariable) (with a norm)
   * @param oa3Hessian     The hessian of each function (size NbFunction*NbVariable*NbVariable)
   */
  virtual void       EvalHessian     (CATOptReal const * iaX, CATOptReal * oa2Hessian, CATOptReal * oa3Hessian = 0) = 0;


  /**
   * Determines which variables really are use in each function
   * @param oa2PresentVariable      Array (matrix size NbFunction*NbVariable) with the presence or not of each variable for each function
   * @return                        The number of non-zero coefficients in all the system
   */
  virtual int        FillPresentVariables(unsigned char *oa2PresentVariable) = 0;

  /**
   * Determines which variables really are use in each function
   * @param oa2PresentVariables     Array of the indexes of the variable with non-zero coefficients (for each function, begin at i*NbVariable, 0<=i<NbFunction)
   * @param oaNbVarPerFunction      Array of number of non-zero coefficients per function
   * @return                        The number of non-zero coefficients in all the system
   */
  virtual int        GetPresentVariables(int * oa2PresentVariables, int * oaNbVarPerFunction = 0) = 0;

  /**
   * Determines which variables really are use in a function
   * @param iIdxFunction            index of the function that we want to know the number of non-zero coefficients
   * @param oaPresentVariables      Array of the indexes of the variable with non-zero coefficients
   * @return                        The number of non-zero coefficients for the function
   */
  virtual int        GetPresentVariables(int iIdxFunction, int * oaPresentVariables) = 0;

  /**
   * Reset cache and all pre-calculated objects
   */
  virtual void       Reset              ();

  /**
   * Get the norme use
   * @return               The norme use
   */
  virtual CATOptNorm GetNorm            () const;

  /**
   * Set the norme use
   * @param inorme         The new norme to use
   */
  virtual void       SetNorm            (CATOptNorm inorme);

  /**
   * Get the number of functions
   * @return               The number of functions
   */
  virtual int        GetNbFunction      () const = 0;

  /**
   * Get the number of variables
   * @return               The number of variables
   */
  virtual int        GetNbVariable      () const = 0;

  /*
  * Compute the data to describe the profile of the sparse jacobian matrix 
  * @param  iVarNb the nb of variables of the system
  * @param  oSparseGradSize the nb of non nul coefficients of the jacobian matrix
  * @param  oaVariableIndex the variable order such as the matrix is the sparsest as possible
  * @param  oaGradientIndex 
  * @WARNING the arrays oaVariableIndex and oaGradientIndex have to deleted by the caller.
  */
  void ComputeJacobianSparseData(const CATULONG32 & iVarNb, CATULONG32 *&  oaGradientIndex, CATULONG32 *&  oaVariableIndex,
                                 CATULONG32 & oSparseGradSize);

  private:
  /**
  * Manage the sparse gradient matrix 
  */
   void ComputeJacobianSparseSkeleton(const CATULONG32 & iaXSize);
 


protected:
  // Norme absolue par default
  CATOptNorm _NormOpt;

private:
  CATOptFunction (CATOptFunction &);
  CATOptFunction& operator=(CATOptFunction&);
  //Data for Sparse Matrix
  CATBoolean   _SparseData; // status of the sparse jacobian skeleton (up to date(TRUE) or not(FALSE))
  CATULONG32 * _aVariableIndex; //new order of the variables such as the jacobian is the sparsest as possible
  CATULONG32 * _aGradientIndex; //array of the new var index of the nonzero coef for every line. Between lines, space size
  CATULONG32   _SparseGradMatrixSize;//nb of the nonzero coefficients of the jacobian matrix
#endif
};

//-----------------------------------------------------------------------

#endif
