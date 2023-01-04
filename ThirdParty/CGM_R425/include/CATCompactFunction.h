#ifdef _Coverage_GOO
#ifndef CATCompactFunction_H
#define CATCompactFunction_H
//
// COPYRIGHT DASSAULT SYSTEMES 2003
//
//===================================================================
// August 2003 - ALA - Creation
//===================================================================
//
#include "CompactFunction.h"
#include "CATMathDef.h" 
#include "CATMathInterval.h" 
#include "CATMathFunctionXY.h" 
//
class CATCompactFunctionImp;
//
class ExportedByCompactFunction CATCompactFunction  : public CATMathFunctionXY 
{
  public:



	//
	CATCompactFunction (CATCompactFunctionImp *iF);
	~CATCompactFunction ();
	//
	double Eval(const double & iX, const double & iY) const;
	double EvalFirstDerivX(const double & iX, const double & iY) const;
	double EvalFirstDerivY(const double & iX, const double & iY) const;
	double EvalSecondDerivX2(const double & iX, const double & iY) const;
	double EvalSecondDerivXY(const double & iX, const double & iY) const;
	double EvalSecondDerivY2(const double & iX, const double & iY) const;
	double EvalThirdDerivX3(const double & iX, const double & iY) const;
	double EvalThirdDerivX2Y(const double & iX, const double & iY) const;
	double EvalThirdDerivXY2(const double & iX, const double & iY) const;
	double EvalThirdDerivY3(const double & iX, const double & iY) const;

   	//
	void Eval(const double u, const double v, 
		    const CATMathOption iOptions,
		    double * ioF,
		    double * ioFx =0, double * ioFy=0,
		    double * ioFx2=0, double * ioFxy=0, double *ioFy2=0) const;
//
  virtual CATMathInterval Eval(const CATMathInterval & Du,
    const CATMathInterval & Dv, const CATTolerance & iTolObject=CATGetDefaultTolerance()) const;
	virtual CATMathInterval EvalFirstDerivX(const CATMathInterval & Du,
					  const CATMathInterval & Dv) const;
	virtual CATMathInterval EvalFirstDerivY(const CATMathInterval & Du,
					  const CATMathInterval & Dv) const;
	/*
	virtual CATMathInterval EvalSecondDerivX2(const CATMathInterval & Du,
						const CATMathInterval & Dv) const;
	virtual CATMathInterval EvalSecondDerivXY(const CATMathInterval & Du,
						const CATMathInterval & Dv) const;
	virtual CATMathInterval EvalSecondDerivY2(const CATMathInterval & Du,
						const CATMathInterval & Dv) const;
	*/

 /** 
  * @nodoc 
  * Interval evaluator of function and derivatives at the same time .
  * (performance are increased if redefined in derived classes)
  * iOptions is a command which contains which derivatives are requested
  * (usually, iOptions = OptionEvalInterval + OptionEvalFirstDerivInterval)
  */
  virtual void Eval(const CATMathInterval & Du, const CATMathInterval & Dv,
				const CATMathOption iOptions,
				CATMathInterval * f,
				CATMathInterval * fx =0, CATMathInterval * fy=0,
				CATMathInterval * fx2=0, CATMathInterval *fxy=0, 
				CATMathInterval *fy2=0, const CATTolerance & iTolObject=CATGetDefaultTolerance()) const;
	// return 0 if OK
	//


 //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------
   
  virtual CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
  virtual CATBoolean IsOption(const CATMathOption iOption) const;
  virtual CATMathClassId IsA() const;

	//
private:
	//

	CATCompactFunctionImp *_FunctionImp;
};


#endif
#endif
