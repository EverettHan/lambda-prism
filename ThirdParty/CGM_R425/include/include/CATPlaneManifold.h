#ifndef CATPlaneManifold_h
#define CATPlaneManifold_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATEvaluableManifold.h"

#include "ListPOfCATCellManifold.h"
#include "CATIACGMLevel.h"

class CATMathPoint;
class CATMathDirection;

#ifdef CATIACGMV5R20
  #include "CATGMModelInterfaces.h"
  #ifndef LOCAL_DEFINITION_FOR_IID
  extern ExportedByCATGMModelInterfaces IID IID_CATPlaneManifold ;
  #else
  extern "C" const IID IID_CATPlaneManifold ;
  #endif
  class ExportedByCATGMModelInterfaces CATPlaneManifold : public CATEvaluableManifold
#else
  #ifndef LOCAL_DEFINITION_FOR_IID
  #include "YI00IMPL.h"
  extern ExportedByYI00IMPL IID IID_CATPlaneManifold ;
  #else
  extern "C" const IID IID_CATPlaneManifold ;
  #endif
  class ExportedByYI00IMPL CATPlaneManifold : public CATEvaluableManifold
#endif

{
  CATDeclareInterface;

public:

  virtual void Set(const ListPOfCATCellManifold &iRepresentation, const CATMathPoint &iPointOnPlane, const CATMathDirection& iNormal) = 0;

  virtual void GetPosition(CATMathPoint &oPointOnPlane, CATMathDirection& oNormal) const = 0; // oPointOnPlane may differ from iPointOnPlane

  virtual void GetPlane(CATMathPlane &ioMathPlane) const = 0;

};
  
CATDeclareHandler(CATPlaneManifold,CATEvaluableManifold);

#endif
