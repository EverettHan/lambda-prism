#ifndef CATGMLiveShapeButtonNavigatorInterface_H
#define CATGMLiveShapeButtonNavigatorInterface_H

#include "CATGMModelInterfaces.h"
#include "CATManifoldNavigator.h"
#include "ListPOfCATCellManifold.h"
#include "CATGMLiveShapeGlobalButtonNavigatorInterface.h"

class CATLiveBody;
class CATMathPlane;
class CATMathPoint;
class CATManifoldAttribute;


class ExportedByCATGMModelInterfaces CATGMLiveShapeButtonNavigatorInterface : public CATManifoldNavigator
{
public:

  // Constructor
  CATGMLiveShapeButtonNavigatorInterface(); 

  // Destructor
  virtual ~CATGMLiveShapeButtonNavigatorInterface();

  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATGMLiveShapeButtonNavigatorInterface * GetAsButtonNavigatorInterface();

  
  //Get methods
  virtual CATLiveBody * GetInputLiveBody()=0;

  virtual void GetAllCellManifolds(ListPOfCATCellManifold & oCellManifoldList)=0;
  virtual void GetSupportCellManifoldList(ListPOfCATCellManifold & oSupportCellManifoldList)=0;
  virtual void GetTopCellManifoldList(ListPOfCATCellManifold & oTopCellManifoldList)=0;

  virtual CATBoolean IsEquivalentTo(const CATGMLiveShapeButtonNavigatorInterface &iOtherManifoldButtonNavigatorInterface, CATGeoFactory * iFactory) const = 0;

  virtual CATGMLiveShapeButtonType GetButtonType()=0;

  virtual void   GetSphereCenter(CATMathPoint & oSphereCenter)=0;
  virtual double GetSphereRadius()=0;
  virtual double GetButtonHeight()=0;
  virtual CATGMLiveShapeButtonSide GetButtonSide()=0;
  virtual void   GetCircularEdgePlane(CATMathPlane & oEdgePlane)=0;
  virtual void   GetCircularEdgeCenter(CATMathPoint & oCenterPoint)=0;
  virtual double GetCircularEdgeRadius()=0;

private:


};


#endif
