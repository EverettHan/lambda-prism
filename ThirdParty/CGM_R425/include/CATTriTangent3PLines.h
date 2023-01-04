//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
//
// CATTriTangent3PLines :
// Interface class for operator of TriTangent between 3 PLines
// These PLines must have the same support
//
//=============================================================================
//
// Usage Notes:
//
//=============================================================================
// Aug 2001    Creation                      F. Caillaud
//=============================================================================

#ifndef CATTriTangent3PLines_h
#define CATTriTangent3PLines_h

#include "Y30C1XMM.h"
#include "CATMathDiagnostic.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"

//BQJ : BigScale Modification
#include "CATTolerance.h"


class CATMathFunctionX;
class CATMathIntervalND;
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;

class ExportedByY30C1XMM CATTriTangent3PLines  : public CATCGMVirtual
{
public:
	CATTriTangent3PLines(	const CATMathFunctionX * ipcrv1eqU,
							const CATMathFunctionX * ipcrv1eqV,
							const CATMathFunctionX * ipcrv2eqU,
							const CATMathFunctionX * ipcrv2eqV,
							const CATMathFunctionX * ipcrv3eqU,
							const CATMathFunctionX * ipcrv3eqV,
							CATLONG32 iSide1,
							CATLONG32 iSide2,
							CATLONG32 iSide3);

  void SetSoftwareConfiguration (CATSoftwareConfiguration * iConfig);
  
	virtual ~CATTriTangent3PLines();

	CATMathDiagnostic Solve (	const CATMathIntervalND & iDomain,
								CATMathSetOfPointsND & oSolutions, const CATTolerance & iTol);

private:
	double _a[16],_b[4];
  CATSoftwareConfiguration * _SoftwareConfiguration;
};

#endif
