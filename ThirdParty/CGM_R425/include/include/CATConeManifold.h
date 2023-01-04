#ifndef CATConeManifold_h
#define CATConeManifold_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATEvaluableManifold.h"
#include "ListPOfCATCellManifold.h"
#include "CATIACGMLevel.h"

class CATMathAxis;

#ifdef CATIACGMR421Code
  #include "CATGMModelInterfaces.h"
  #ifndef LOCAL_DEFINITION_FOR_IID
  extern ExportedByCATGMModelInterfaces IID IID_CATConeManifold ;
  #else
  extern "C" const IID IID_CATConeManifold ;
  #endif
  class ExportedByCATGMModelInterfaces CATConeManifold : public CATEvaluableManifold
#else
  #ifndef LOCAL_DEFINITION_FOR_IID
  #include "YI00IMPL.h"
  extern ExportedByYI00IMPL IID IID_CATConeManifold ;
  #else
  extern "C" const IID IID_CATConeManifold ;
  #endif
  class ExportedByYI00IMPL CATConeManifold : public CATEvaluableManifold
#endif
{
  CATDeclareInterface;

public:
  //iRepresentation : the CATCellManifolds representing the CATConeManifold
  //iAxis : Axis which center is the summit of the cone and third direction the axe of the half-cone oriented toward the inside
  //WARNING : iAngle is PI/2 minus the angle of the cone in radian
  virtual void Set(const ListPOfCATCellManifold &iRepresentation, const CATMathAxis &iAxis,CATAngle iAngle) = 0;

  //Get Methods  
  virtual void GetSummit(CATMathPoint &oSummit) const = 0;
  virtual void GetAxisDirection(CATMathDirection& oAxisDirection) const = 0;
  virtual CATAngle GetAngle() const = 0;




};
  
CATDeclareHandler(CATConeManifold,CATEvaluableManifold);

#endif
