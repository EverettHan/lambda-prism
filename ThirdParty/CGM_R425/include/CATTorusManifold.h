#ifndef CATTorusManifold_h
#define CATTorusManifold_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATEvaluableManifold.h"
#include "ListPOfCATCellManifold.h"
#include "CATIACGMLevel.h"

class CATMathPoint;
class CATMathAxis;

#ifdef CATIACGMR421Code
  #include "CATGMModelInterfaces.h"
  #ifndef LOCAL_DEFINITION_FOR_IID
  extern ExportedByCATGMModelInterfaces IID IID_CATTorusManifold ;
  #else
  extern "C" const IID IID_CATTorusManifold ;
  #endif
  class ExportedByCATGMModelInterfaces CATTorusManifold : public CATEvaluableManifold
#else
  #ifndef LOCAL_DEFINITION_FOR_IID
  #include "YI00IMPL.h"
  extern ExportedByYI00IMPL IID IID_CATTorusManifold ;
  #else
  extern "C" const IID IID_CATTorusManifold ;
  #endif
  class ExportedByYI00IMPL CATTorusManifold : public CATEvaluableManifold
#endif
{
  CATDeclareInterface;

public:

  //iRepresentation : the CATCellManifolds representing the CATTorusManifold
  //iAxis : Axis which center is the center of the torus and third direction the axe of revolution
  //iMajorRadius & iMinorRadius : major and minus radius of the torus
  virtual void Set(const ListPOfCATCellManifold &iRepresentation,const CATMathAxis &iAxis,
    const CATPositiveLength iMajorRadius,const CATPositiveLength iMinorRadius) = 0;

  //Get Methods  
  virtual void GetPosition(CATMathPoint &oCenter) const = 0;
  virtual void GetAxisDirection(CATMathDirection& oAxisDirection) const = 0;
  virtual CATPositiveLength GetMajorRadius() const = 0;
  virtual CATPositiveLength GetMinorRadius() const = 0;

};
  
CATDeclareHandler(CATTorusManifold,CATEvaluableManifold);

#endif
