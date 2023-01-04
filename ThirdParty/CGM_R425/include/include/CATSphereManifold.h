#ifndef CATSphereManifold_h
#define CATSphereManifold_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATEvaluableManifold.h"

#include "ListPOfCATCellManifold.h"


class CATMathPoint;

#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATSphereManifold ;
#else
extern "C" const IID IID_CATSphereManifold ;
#endif
class ExportedByCATGMModelInterfaces CATSphereManifold : public CATEvaluableManifold
{
  CATDeclareInterface;

public:

  virtual void Set(const ListPOfCATCellManifold &iRepresentation, const CATMathPoint& iCenter, const CATPositiveLength iRadius) = 0;

  virtual void GetPosition(CATMathPoint &oCenter) const = 0; 
  virtual CATPositiveLength GetRadius() const = 0;
};
  
CATDeclareHandler(CATSphereManifold,CATEvaluableManifold);

#endif
