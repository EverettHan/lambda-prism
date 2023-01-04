#ifndef CATCylinderManifold_h
#define CATCylinderManifold_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATEvaluableManifold.h"

#include "ListPOfCATCellManifold.h"

class CATMathLine;

#include "CATGMModelInterfaces.h" 
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATCylinderManifold ;
#else
extern "C" const IID IID_CATCylinderManifold ;
#endif
class ExportedByCATGMModelInterfaces CATCylinderManifold : public CATEvaluableManifold
{
  CATDeclareInterface;

public:

  virtual void Set(const ListPOfCATCellManifold &iRepresentation, const CATMathLine& iAxis, const CATPositiveLength iRadius) = 0;

  virtual CATPositiveLength GetRadius() const = 0;
  virtual void GetPosition(CATMathLine& oAxis) const = 0; // NB: Origin of Axis may have been shifted

};
  
CATDeclareHandler(CATCylinderManifold,CATEvaluableManifold);

#endif
