
#ifndef CATBezierCurve_h
#define CATBezierCurve_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * Use now the CATNurbsCurve class.
 */
#include "CATBaseUnknown.h"

#include "CATBSplineCurve.h"

class CATMathSetOfPoints;
#include "CATMathSetOfLongs.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATBezierCurve ;
#else
extern "C" const IID IID_CATBezierCurve ;
#endif

class ExportedByCATGMGeometricInterfaces CATBezierCurve : public CATBSplineCurve
{
  CATDeclareInterface;

public:

  virtual CATLONG32 GetDegreeOfOneArc(CATLONG32 ArcIndex)const =0;

  virtual void ModifyControlPoints(CATLONG32 iNbrOfArcs,
				   CATMathSetOfLongs *iArcsDegree,
				   CATMathSetOfPoints *iCtrlPts)const =0;

};

  CATDeclareHandler(CATBezierCurve,CATBSplineCurve);

#endif
