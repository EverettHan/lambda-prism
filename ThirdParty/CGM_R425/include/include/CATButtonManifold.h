#ifndef CATButtonManifold_h
#define CATButtonManifold_h

// COPYRIGHT DASSAULT SYSTEMES  2017
// VB7 February 2017

#include "CATContextualManifold.h"
#include "YI00IMPL.h"
#include "CATGMLiveShapeGlobalButtonNavigatorEnumInterface.h"
#include "ListPOfCATCellManifold.h"

class CATMathPoint;
class CATMathPlane;
class CATDeclarativeManifoldCarrierBase;

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByYI00IMPL IID IID_CATButtonManifold ;
#else
extern "C" const IID IID_CATButtonManifold ;
#endif

//TODO VB7 - Define
//Button Type
//Button Side

class ExportedByYI00IMPL CATButtonManifold : public CATContextualManifold
{
  CATDeclareInterface;

public:

  //Get methods
  virtual void                     GetSphereCenter(CATMathPoint & oSphereCenter) const = 0;
  virtual double                   GetSphereRadius()                             const = 0;
  virtual CATGMLiveShapeButtonType GetButtonType()                               const = 0;
  virtual CATGMLiveShapeButtonSide GetButtonSide()                               const = 0;
  virtual void                     GetEdgeCenter(CATMathPoint & oEdgeCenter)     const = 0;
  virtual double                   GetEdgeRadius()                               const = 0;
  virtual void                     GetEdgePlane(CATMathPlane & oEdgePlane)       const = 0;

  //Set method
  virtual void Set(const ListPOfCATCellManifold &iRepList,
                   const ListPOfCATCellManifold &iSupportList,
                   const CATMathPoint           &iSphereCenter,
                   double                        iSphereRadius,
                   CATGMLiveShapeButtonType      iButtonType,
                   CATGMLiveShapeButtonSide      iButtonSide,
                   const CATMathPoint           &iEdgeCenter,
                   double                        iEdgeRadius,
                   const CATMathPlane           &iEdgePlane) = 0 ;

  virtual HRESULT CheckValidity(CATLiveBody &iLiveBody, CATDeclarativeManifoldCarrierBase &iDMCarrier) const = 0;
};
  
CATDeclareHandler(CATButtonManifold,CATContextualManifold);

#endif
