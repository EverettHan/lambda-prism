#ifndef CATPCurveEquation_h
#define CATPCurveEquation_h

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CATPCurve.h"
#include "CATMathDef.h"

class CATSurface;
class CATMathFunctionX;
class CATCrvLimits;


#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATPCurveEquation ;
#else
extern "C" const IID IID_CATPCurveEquation ;
#endif

class ExportedByCATGMGeometricInterfaces CATPCurveEquation : public CATPCurve
{
  CATDeclareInterface;

public :

    virtual  void Set (const CATMathFunctionX* iFx      ,
		       const CATMathFunctionX* iFy      ,
		       const double            iStart   ,
		       const double            iEnd     ,
		       const double            iMaxStart,
		       const double            iMaxEnd  ,
		             CATSurface*       iSupport ) =0;

 virtual  void SetEquationU(const CATMathFunctionX* iFx) =0;

 virtual  void SetEquationV(const CATMathFunctionX* iFy) =0;  

};
  CATDeclareHandler(CATPCurveEquation,CATPCurve);

#endif
