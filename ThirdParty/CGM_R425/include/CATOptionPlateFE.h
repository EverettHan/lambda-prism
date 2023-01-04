/// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
// CATOptionPlateFE :
//  This  class store the option for a Finite Element
//        Method algorithm able  to  define a BSpline   two variable
//        function satisfying   some constraints and  minimizing  an
//        energy like criterion.

//     see also CATMathPlateFE.

//=============================================================================
// Feb . 2000    Creation             P.Mangin
//=============================================================================
// File : CATOptionPlateFE.h

#ifndef CATOptionPlateFE_H
#define CATOptionPlateFE_H

#include "CATGMOperatorsInterfaces.h"
#include "CATMathDef.h"

class ExportedByCATGMOperatorsInterfaces CATOptionPlateFE 
{
public:

  CATOptionPlateFE();
	~CATOptionPlateFE();

	// Read the CodeLevel
	int CodeLevel() const;

	// Write the CodeLevel
	void SetCodeLevel(const int iCodeLevel);

	// Write normalization coefficient 
	void SetNormalizationCoefficient(const double Coeff);
	// Read normalization coefficient 
	double NormalizationCoefficient() const;

	// Write a weight to an order of Energy
	// Order have to be  0 <= order <= 9;
	// to suppress an order you have to write coef  0.	
	void SetEnergyCoefficient(const int IndexOfOrder, const double iEnergyCoefficient);
	// Read a weight to an order of Energy
	// Order have to be  0 <= order <= 9;
	// to suppress an order you have to write coef  0.	
	double EnergyCoefficient(const int IndexOfOrder)const;
	
	// Set if the approximation precessus begin with one Bezier 
	// or with the initial surface.
  void SetDefineInit(const	CATBoolean  iDefInit);
  // Read Define if the approximation precessus begin with one Bezier 
	// or with the initial surface.
	CATBoolean DefineInit() const;

	// Set if the Target must be reached in Phase 1 
	// Very usful when the number of phase 2 is 0.
	// The default is FALSE.
	void SetQTargetMode(const CATBoolean isQTargetMode);

	// Get if the Target must be reached in Phase 1 
	CATBoolean IsQTargetMode() const;

	// Write the maximum number of iteration of each Phasis
	// Step1 : Number of iteration to Find Equilibrum beetween Constraint and Energy
	// Step2 : Number of iteration to Find the best number of vertexes on 
	//             the Delta Surface:  Each iteration can multiply the vertexes number by 2
	// Step3 : Number of iteration to reach the wanted accuracy.
	// Warning : Each NumberOfIteration can be Zero but one of them have to be positive
	void SetIterationsOfStep1(const int iNumber);
	void SetIterationsOfStep2(const int iNumber);
	void SetIterationsOfStep3(const int iNumber);
	void SetIterationsOfStep4(const int iNumber);

	// Read the maximum number of iteration of each Phasis
	// Step1 : Number of iteration to Find Equilibrum beetween Constraint and Energy
	// Step2 : Number of iteration to Find the best number of vertexes on 
	//             the Delta Surface:  Each iteration can multiply the vertexes number by 2
	// Step3 : Number of iteration to reach the wanted accuracy.
	// Warning : Each NumberOfIteration can be Zero but one of them have to be positive
	int IterationsOfStep1() const;
	int IterationsOfStep2() const;
	int IterationsOfStep3() const;
	int IterationsOfStep4() const;

	// Impose cutting values
	void SetImposedCutting(const CATBoolean iNeed);
	CATBoolean GetImposedCutting()const;

	// Minimal Continuity
	void SetMinimalContinuities(const int iUMinCont, const int iVMinCont);
	void GetMinimalContinuities(int& oUMinCont, int& oVMinCont)const;

   /**
    * ktu 17/03/03
    * SetFilterOfCuttingByRatio:
    * Permet d'activer le filtre local des decoupes
    * par les ratio des spans
    */
   void SetFilterOfCuttingByRatio( CATBoolean iFilterOn);
   CATBoolean GetFilterOfCuttingByRatio();

   void ActivedCldMode( CATBoolean iActive ) { _CloudMode = iActive;  }
   CATBoolean  IsActivedCldMode(  ) const { return _CloudMode; }

   void SetMaxContinuity(const int iCont);

   int  GetMaxContinuity() const;

   //@nodoc
   void BegingWith1( CATBoolean iWith1);
   CATBoolean BegingWith1( )const;


private :	
	double _TabE[10];
	double _Coeff;
	CATLONG32 _CodeLevel;

	int _Step1;
	int _Step2;
	int _Step3;
	int _Step4;
	int _UMinCont, _VMinCont;
  int _MaxContinuity;

	CATBoolean _DefInit;
	CATBoolean _ImposedCuting;
  CATBoolean _IsFilterOfCuttingByRatio;
  CATBoolean _CloudMode;
	CATBoolean _IsQTargetMode;
	CATBoolean _Phase1With1;
};

inline void CATOptionPlateFE::SetImposedCutting(const CATBoolean iNeed)
{
	_ImposedCuting = iNeed;
}

inline CATBoolean CATOptionPlateFE::GetImposedCutting() const
{
	return _ImposedCuting;
}
#endif
