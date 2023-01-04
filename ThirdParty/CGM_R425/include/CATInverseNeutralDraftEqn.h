//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2005
//=============================================================================
//
// CATInverseNeutralDraftEqn :
// Class used to find a parameter on the neutral curve using a point on the cone 
// and draft pulling direction ( i.e cone axis) 
// 
//=============================================================================
// Usage notes:
//
//=============================================================================
// Dec. 2005  Creation                                        SOU
//=============================================================================

#ifndef CATInverseNeutralDraftEqn_H
#define CATInverseNeutralDraftEqn_H

#include "Connect.h"
#include "CATMathFunctionX.h"
#include "CATMathBasisFunctionX.h"
#include "CATTolerance.h"



class CATMathPoint;
class CATMathDirection;
class CATSoftwareConfiguration;

class ExportedByConnect CATInverseNeutralDraftEqn: public CATMathBasisFunctionX
{
public:
	//-----------------------------------------------------------------
	// Object management
	//-----------------------------------------------------------------
  CATInverseNeutralDraftEqn(CATSoftwareConfiguration* iConfig
                            ,const CATMathFunctionX* iC[3]
                            ,const CATMathPoint& iPoint
                            ,const CATMathDirection& iDraftDir,
                            const CATTolerance & iTolObject = CATGetDefaultTolerance()
                            );

	CATInverseNeutralDraftEqn(const CATInverseNeutralDraftEqn& iF);

	~CATInverseNeutralDraftEqn();
	CATMathFunctionX* Duplicate() const;
	
	//-----------------------------------------------------------------
	// Information methods
	//-----------------------------------------------------------------
	
	CATMathClassId IsA() const;
	CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
	CATBoolean IsOption(const CATMathOption iOption) const;
	//-----------------------------------------------------------------
	// Evaluators on doubles
	//-----------------------------------------------------------------   
	double Eval(const double& t) const;
	//double EvalFirstDeriv(const double& t) const;
	//double EvalSecondDeriv(const double& t) const;
	//double EvalThirdDeriv(const double& t) const;
	
	//void Eval(const double t, const CATMathOption iOption,
	//	double * f, double * df = 0, double * d2f = 0) const;

	//-----------------------------------------------------------------
	// Set methods
	//-----------------------------------------------------------------   
  void SetPoint(const CATMathPoint& iPoint);

  //-----------------------------------------------------------------------------
  // Private data
  //-----------------------------------------------------------------------------
private:
  void InitDataMembers();

  const CATMathFunctionX * _C[3]; 
  double _DraftPoint[3];
  double* _pDraftDir;
  CATSoftwareConfiguration* _Config;
  
};

#endif
