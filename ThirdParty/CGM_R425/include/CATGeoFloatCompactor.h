
#ifndef CATGeoFloatCompactor_H
#define CATGeoFloatCompactor_H

#include "CATDataType.h"
#include "YN000FUN.h"

class CATMathStreamImpl;
#include "CATFloatCompactor.h" //For CATFloatCompactor::FlowType

class ExportedByYN000FUN CATGeoFloatCompactor
{
public: 
	CATGeoFloatCompactor(CATULONG32 iTag, CATMathStreamImpl * ioStream, CATMathStreamBits::FlowType iFlowType);
	~CATGeoFloatCompactor();

protected:
	CATBoolean _Stat;
	CATULONG32 _Tag;
	CATMathStreamBits::FlowType _FlowType;
	CATMathStreamImpl * _Stream;
	CATFloatCompactor * _FloatCompactor;

	void ReframePoint(double * ioPoint, int iN, float * oOffset);
	void ReframeParam(float * ioParam, int iN, CATBoolean iIncludeLast);

private:
  CATGeoFloatCompactor(const CATGeoFloatCompactor &);
	void operator = (const CATGeoFloatCompactor &);
};

#endif
