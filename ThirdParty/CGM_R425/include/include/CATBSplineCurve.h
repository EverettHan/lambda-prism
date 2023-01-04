
#ifndef CATBSplineCurve_h
#define CATBSplineCurve_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * Use now the CATNurbsCurve class.
 */

#include "CATBaseUnknown.h"

#include "CATBoundedCurve.h"

class CATMathPoint ;
#include "CATMathSetOfPoints.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATBSplineCurve ;
#else
extern "C" const IID IID_CATBSplineCurve ;
#endif

class ExportedByCATGMGeometricInterfaces CATBSplineCurve : public CATBoundedCurve
{
  CATDeclareInterface;

public:

  virtual CATLONG32 GetNumberOfControlPoints()const =0;

  virtual CATMathPoint GetOneControlPoint(CATLONG32 number)const =0;

  virtual CATMathSetOfPoints *GetControlPoints()const =0;

  virtual CATLONG32 GetDegree()const =0;
  
  virtual void SetOneControlPoint(CATLONG32 number,
				  const CATMathPoint & controlpointm)=0;

};

  CATDeclareHandler(CATBSplineCurve,CATBoundedCurve);

#endif
