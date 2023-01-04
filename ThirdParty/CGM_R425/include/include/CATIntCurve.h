#ifndef CATIntCurve_h
#define CATIntCurve_h

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CATEdgeCurve.h"

class CATPCurve ;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATIntCurve ;
#else
extern "C" const IID IID_CATIntCurve ;
#endif

/**
 * Interface representing the aggregating curve resulting of the intersection
 * of two surfaces.
 *<br> The CATIntCurve is created by the <tt>CreateIntCurve</tt>
 * method of the <tt>CATGeoFactory</tt> interface.
 *<br>The two CATPCurves of a CATIntCurve must not belong to another
 * CATEdgeCurve. They can be only modified through their CATEdgeCurve.
 */
 
class ExportedByCATGMGeometricInterfaces CATIntCurve : public CATEdgeCurve
{
  CATDeclareInterface;

public:
/**
 * Replaces the two CATPCurves of a CATIntCurve.
 */
 virtual void Set(CATPCurve* iC1, CATPCurve* iC2) = 0;

/**
 * Returns a pointer to the other CATPCurve of a CATIntCurve. 
 */
  virtual const CATPCurve * GetCoPCurve(const CATPCurve * iC) = 0;
};

CATDeclareHandler(CATIntCurve,CATEdgeCurve);

#endif
