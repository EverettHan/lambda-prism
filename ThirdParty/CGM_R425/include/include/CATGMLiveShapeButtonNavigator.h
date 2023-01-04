#ifndef CATGMLiveShapeButtonNavigator_H
#define CATGMLiveShapeButtonNavigator_H

#include "CATPersistentCell.h"
#include "ListPOfCATCellManifold.h"
#include "CATGMLiveShapeButtonNavigatorInterface.h"
#include "CATMathPlane.h"
#include "CATMathPoint.h"

class CATCGMStream;
class CATICGMContainer;
class CATLiveBody;
class CATCellManifold;
class CATFace;
class CATGeoFactory;
class CATManifoldAttribute;
class CATButtonManifold;

class ExportedByPersistentCell CATGMLiveShapeButtonNavigator : public CATGMLiveShapeButtonNavigatorInterface
{
public:
  // Attribute Declaration
  CATCGMDeclareManifoldNavigator(CATGMLiveShapeButtonNavigator, CATGMLiveShapeButtonNavigatorInterface);

  // Constructor
  CATGMLiveShapeButtonNavigator(CATLiveBody* iLiveBody, CATButtonManifold * iButtonManifold);

  CATGMLiveShapeButtonNavigator(CATGMLiveShapeButtonNavigator * iButtonNavigator);

  // DO NOT USE : For Unstream Only
  CATGMLiveShapeButtonNavigator();

  // Destructor
  virtual ~CATGMLiveShapeButtonNavigator();

  // @nocgmitf
  CATGMLiveShapeButtonNavigator * GetAsButtonNavigator() const;
  
  //Get methods
  //@nocgmitf
  CATLiveBody * GetInputLiveBody();
  //@nocgmitf
  CATGeoFactory * GetFactory();

  virtual void GetAllCellManifolds(ListPOfCATCellManifold & oCellManifoldList);
  virtual void GetSupportCellManifoldList(ListPOfCATCellManifold & oSupportCellManifoldList);
  virtual void GetTopCellManifoldList(ListPOfCATCellManifold & oTopCellManifoldList);

  virtual CATBoolean IsEquivalentTo(const CATGMLiveShapeButtonNavigatorInterface &iOtherManifoldButtonNavigatorInterface, CATGeoFactory * iFactory) const;

  //@nocgmitf
  CATBoolean Contains(CATCellManifold * iCM);
  //@nocgmitf
  CATBoolean Contains(CATFace * iFace);

  virtual HRESULT GetCells(ListPOfCATCell& oCells) const;

  virtual CATGMLiveShapeButtonType GetButtonType();
  virtual void GetSphereCenter(CATMathPoint & oSphereCenter);
  virtual double GetSphereRadius(); //>=0
  virtual double GetButtonHeight(); //>=0
  virtual CATGMLiveShapeButtonSide GetButtonSide(); //Inner or outer
  virtual void   GetCircularEdgePlane(CATMathPlane & oEdgePlane);
  virtual void   GetCircularEdgeCenter(CATMathPoint & oCenterPoint);
  virtual double GetCircularEdgeRadius();


  CATButtonManifold * GetButtonManifold();

  // @nocgmitf
  //-------------------------------------------------------------------------------------------------
   virtual void Stream(CATCGMStream & ioStream) const;
   virtual void UnStream( CATCGMStream& ioStr, CATGeoFactory * iFactory);

   virtual void Dump(CATCGMOutput& Output);

private :

  CATLiveBody * _InputLiveBody;

  CATButtonManifold * _ButtonManifold;

};

// --------------------------------------
// CATCreateGMLiveShapeButtonNavigator
// --------------------------------------
// @nocgmitf
ExportedByPersistentCell CATGMLiveShapeButtonNavigator * CATCreateGMLiveShapeButtonNavigator(CATLiveBody & iLiveBody, CATButtonManifold & iButtonManifold);

#endif
