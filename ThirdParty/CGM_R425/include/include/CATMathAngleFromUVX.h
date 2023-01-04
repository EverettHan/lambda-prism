//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
// CATMathAngleFromUVX :
// Arctan(FV(w)/FU(w))-AngleShift, result in [-PI,PI]
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// 30/09/11 R1Y Added access functions (for comparing geometries).
//=============================================================================


#ifndef CATMathAngleFromUVX_H
#define CATMathAngleFromUVX_H

#include "YN000FUN.h"

#include "CATMathFunctionX.h"
#include "CATMathPoint2D.h"
#include "CATTolerance.h"

class ExportedByYN000FUN CATMathAngleFromUVX : public CATMathFunctionX
{
public:
	//-----------------------------------------------------------------
	//- Object Management
	//-----------------------------------------------------------------
	CATMathAngleFromUVX(const CATMathFunctionX * iFU, const CATMathFunctionX * iFV,
	                    const CATMathPoint2D &iOrigin, const double AngleShift = 0.0,
                      const CATTolerance & iTolObject=CATGetDefaultTolerance());
	~CATMathAngleFromUVX();
	CATMathFunctionX * Duplicate() const;
	
	//-----------------------------------------------------------------
	//- Information methods
	//-----------------------------------------------------------------
	CATMathClassId IsA() const;
  int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
	CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
	CATBoolean IsATypeOf(const CATMathFunctionXTypeId iType) const;
	CATBoolean IsOption (const CATMathOption iOption) const;

  void SetSideOfDomain(CATLONG32 iDomainSide)
  {_domainSide = iDomainSide;};

  CATLONG32 GetDomainSide() const;
  double GetCosTheta() const;
  double GetSinTheta() const;
  void GetOrigin(CATMathPoint2D & oOrigin) const;
  const CATTolerance & GetToleranceObject() const;

	//-----------------------------------------------------------------
	// Evaluators on doubles
	//----------------------------------------------------------------- 
	double Eval(const double & iT) const;
  double EvalFirstDeriv(const double & iT) const;
  double EvalSecondDeriv(const double & iT) const;
private:
	const CATMathFunctionX *_FU;
	const CATMathFunctionX *_FV;
	double _CosTheta, _SinTheta;
	CATMathPoint2D _Origin;

  CATLONG32 _domainSide;

  const CATTolerance & _TolObject;
};

#endif

