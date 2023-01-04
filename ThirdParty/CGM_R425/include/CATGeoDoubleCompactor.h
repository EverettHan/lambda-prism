/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2009
//=============================================================================
// Jul 09   Creation                                    AAD  
//=============================================================================
#ifndef CATGeoDoubleCompactor_H
#define CATGeoDoubleCompactor_H

#include "CATDataType.h"
#include "YN000FUN.h"

class CATMathStreamImpl;
#include "CATDoubleCompactor.h" //For FlowType

class ExportedByYN000FUN CATGeoDoubleCompactor
{
public: 
	CATGeoDoubleCompactor(CATULONG32 iTag, CATMathStreamImpl * ioStream, CATMathStreamBits::FlowType iFlowType);
	~CATGeoDoubleCompactor();

protected:
	CATBoolean _Stat;
	CATULONG32 _Tag;
	CATMathStreamBits::FlowType _FlowType;
	CATMathStreamImpl * _Stream;
	CATDoubleCompactor * _DoubleCompactor;

	void ReframePoint(double * ioPoint, int iN, double * oOffset);
	void ReframeParam(double * ioParam, int iN, CATBoolean iIncludeLast);

private:
  CATGeoDoubleCompactor(const CATGeoDoubleCompactor &);
	void operator = (const CATGeoDoubleCompactor &);
};

#endif
