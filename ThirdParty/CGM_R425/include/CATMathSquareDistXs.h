#ifndef CATMathSquareDistXs_H
#define CATMathSquareDistXs_H
//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
//===================================================================
//
// CATMathSquareDistXs:
//  class of function for the distance min between one N (<=3) dimensional
//   curve and one N (<=3) dimensional point :
//  (F[0](t) - P[0])^2 + ... + (F[N-1](t) - P[N-1])^2 - SqShift
//
//===================================================================
//
// Usage notes:
//
//
//===================================================================
// 13/02/08 NLD XScale. ajout argument iScaleOption a ComputeOptimalImage() en R19
// 27/01/09 NLD Interface R20 (SoftwareConfiguration) et deflaggage R19 pour ComputeOptimalImage
// 13/04/11 NLD Deflaggage R20 pour ComputeOptimalImage()
//===================================================================
#include "CATIACGMLevel.h"

#include "CATMathFoundationX.h"
#include "CATBoolean.h"
#include "YN000FUN.h"

//-------------------------------------------------------------------

class ExportedByYN000FUN CATMathSquareDistXs : public CATMathFoundationX
{
private:
	CATLONG32 _N; // Dimension, <= 3
	const CATMathFunctionX * _F[3];
	double _Point[3];
	double _SqShift;

public:
	
	CATMathSquareDistXs(const CATLONG32 iN, const CATMathFunctionX ** iF,
	                     const double *iPoint, double iSqShift = 0.0);
	
	virtual ~CATMathSquareDistXs();
	CATCGMNewClassArrayDeclare;
	
	//-----------------------------------------------------------------
	// Information methods
	//-----------------------------------------------------------------
	
	virtual CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
	virtual CATBoolean IsOption(const CATMathOption iOption) const;
	virtual CATMathClassId IsA() const;
	/** @nodoc */
  int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
	/** @nodoc  Not Published  */
  CATMathFunctionX * Duplicate() const;
	/** @nodoc  Not Published  */
  CATMathFunctionX * DeepDuplicate() const ;
#if defined ( CATIACGMR216CAA )
	/** @nodoc  Not Published  */
  CATMathFunctionX * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
#endif

	//-----------------------------------------------------------------
	// Evaluators on doubles
	//-----------------------------------------------------------------
	
	virtual double Eval(const double & iT) const;
	
	/** 
	* Evaluates the first derivative of <tt>this</tt> CATMathFunctionX.
	* @param iT
	* The variable value where <tt>this</tt> CATMathFunctionX is evaluated.
	* @return
	* The result of the evaluation.
	*/
	virtual double EvalFirstDeriv(const double & iT) const;
	
	/** 
	* Evaluates the second derivative of <tt>this</tt> CATMathFunctionX.
	* @param iT
	* The variable value where <tt>this</tt> CATMathFunctionX is evaluated.
	* @return
	* The result of the evaluation.
	*/
	virtual double EvalSecondDeriv(const double & iT) const;
	
	/** 
	* Evaluates the third derivative of <tt>this</tt> CATMathFunctionX.
	* @param iT
	* The variable value where <tt>this</tt> CATMathFunctionX is evaluated.
	* @return
	* The result of the evaluation.
	*/
	virtual double EvalThirdDeriv (const double & iT) const;
	
	
	/** 
	* Simultaneously evaluates <tt>this</tt> CATMathFunctionX and its derivatives.
	* <br><b>Precondition</b>: The pointers
	* must have been previously allocated if you asked for the corresponding evaluation. 
	* @param iT
	* The variable value where <tt>this</tt> CATMathFunctionX is evaluated.
	* @param iOption
	* The type of evalution.
	* <br><b>Legal values</b>:
	* <dl> <dt>OptionEval   </dt>  <dd>  evaluation of the function
	* <dt>OptionEvalFirstDeriv   </dt>  <dd>  evaluation of the first derivatives of the function
	* <dt>OptionEvalSecondDeriv</dt>  <dd>  evaluation of the second derivatives of the function
	* <dt>sum of preceeding values</dt><dd> multiple evaluation.
	* </dl>
	* @param ioF
	* A pointer to the value of <tt>this</tt> CATMathFunctionX.
	* @param ioDf
	* A pointer to the first derivative of <tt>this</tt> CATMathFunctionX.
	* @param ioD2f
	* A pointer to the second derivative of <tt>this</tt> CATMathFunctionX.
	*/
	virtual void Eval(const double iT, const CATMathOption iOption,
	                  double * ioF, double * iodF = 0, double * iod2F = 0) const;
	
		/** 
		* Simultaneously evaluates <tt>this</tt> CATMathFunctionX and its derivatives at regularly spaced values.
		* <br><b>Precondition</b>: The output arrays
		* must have been previously allocated if you asked for the corresponding evaluation.
		* @param iI
		* The interval containing the regularly spaced values.
		* @param iNbPoints
		* The number of values of <tt>iI</tt> where <tt>this</tt> CATMathFunctionX must be evaluated. 
		* If <tt>NbPoints = 1</tt>, the evaluations are made on the first value of <tt>iI</tt>.
		* @param iOption
		* The type of evalution.
		* <br><b>Legal values</b>:
		* <dl> <dt>OptionEval   </dt>  <dd>  evaluation of the function
		* <dt>OptionEvalFirstDeriv   </dt>  <dd>  evaluation of the first derivatives of the function
		* <dt>OptionEvalSecondDeriv</dt>  <dd>  evaluation of the second derivatives of the function
		* <dt>sum of preceeding values</dt><dd> multiple evaluation.
		* </dl>
		* @param ioF
		* The array of evaluations of <tt>this</tt> CATMathFunctionX at the regurlarly spaced values.
		* @param ioDf
		* The array of the first derivatives of <tt>this</tt> CATMathFunctionX at the regurlarly spaced values.
		* @param ioD2f
		* The array of the second derivatives of <tt>this</tt> CATMathFunctionX at the regurlarly spaced values.
	*/
	virtual void Eval(const CATMathInterval & iI, const CATLONG32 iNbPoints,
	                  const CATMathOption iOption,
	                  double * ioF, double * iodF = 0, double * iod2F = 0) const;
	
	
	/** @nodoc */
	virtual CATMathInterval Eval(const CATMathInterval & iI) const;
	/** @nodoc */
	virtual CATMathInterval EvalFirstDeriv(const CATMathInterval & iI) const;
	/** @nodoc */
	virtual CATMathInterval EvalSecondDeriv(const CATMathInterval & iI) const;
	/** @nodoc */
	virtual CATMathInterval EvalThirdDeriv (const CATMathInterval & iI) const;
	/** 
	* @nodoc 
	* Interval evaluator of function and derivatives at the same time :
	* (performance are increased if redefined in derived classes)
	* iOptions is a command which contains which derivatives are requested
	* (usually, iOptions = OptionEvalInterval + OptionEvalFirstDerivInterval)
	*/
	virtual void Eval(const CATMathInterval & iI, const CATMathOption iOption,
	                  CATMathInterval * ioF, CATMathInterval * iodF = 0, 
	                  CATMathInterval * iod2F = 0) const;
	
	/**
		* @nodoc
		* Computes a quite good interval containing the image of (I), thanks to a recursive process.
    */
  virtual CATMathInterval ComputeOptimalImage(const CATMathInterval & I,
                                              const CATTolerance & iTolObject=CATGetDefaultTolerance(),
                                              CATMathAttrScaleOption* iScaleOption=NULL,
                                              CATSoftwareConfiguration* iConfig=NULL
                                             ) const;

};

#endif
