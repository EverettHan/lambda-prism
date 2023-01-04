#ifndef CATGMLiveShapeButtonData_H
#define CATGMLiveShapeButtonData_H

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

class ExportedByPersistentCell CATGMLiveShapeButtonData : public CATGMLiveShapeButtonNavigatorInterface
{
public:
  // Attribute Declaration
  CATCGMDeclareManifoldNavigator(CATGMLiveShapeButtonData, CATGMLiveShapeButtonNavigatorInterface);

  // Constructor
  CATGMLiveShapeButtonData(
    CATLiveBody            * iLiveBody,
    ListPOfCATCellManifold & iCellManifoldList, 
    CATListOfInt           & iCellManifoldTypeList,
    CATGMLiveShapeButtonType iButtonType,
    CATGMLiveShapeButtonSide iButtonSide,
    CATMathPoint           & iSphereCenter,
    double                   iSphereRadius,
    CATMathPoint           & iEdgeCenter,
    double                   iEdgeRadius, 
    CATMathPlane           & iEdgePlane);

  CATGMLiveShapeButtonData(CATGMLiveShapeButtonData * iButtonData);

  // DO NOT USE : For Unstream Only
  CATGMLiveShapeButtonData();

  // Destructor
  virtual ~CATGMLiveShapeButtonData();

  // @nocgmitf
  CATGMLiveShapeButtonData * GetAsButtonData() const;

  //@nocgmitf
  CATLiveBody * GetInputLiveBody();

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
  virtual double GetButtonHeight(); 
  virtual CATGMLiveShapeButtonSide GetButtonSide(); //Inner or outer
  virtual void   GetCircularEdgePlane(CATMathPlane & oEdgePlane);
  virtual void   GetCircularEdgeCenter(CATMathPoint & oCenterPoint);
  virtual double GetCircularEdgeRadius();
  

  // @nocgmitf
  void GetAllCellManifoldTypes(CATListOfInt & oCellManifoldTypeList);

  // @nocgmitf
  CATButtonManifold * CreateButtonManifoldFromData(CATLiveBody & iLiveBody);

  // @nocgmitf
  //-------------------------------------------------------------------------------------------------
   virtual void Stream(CATCGMStream & ioStream) const;
   virtual void UnStream( CATCGMStream& ioStr, CATGeoFactory * iFactory);

   virtual void Dump(CATCGMOutput& Output);

private :

  void GetTopCellManifoldListByType(int iType, ListPOfCATCellManifold & oCellManifoldList); //iType == 1:top; iType == 2:support
  void ResetData();

private :

  CATLiveBody            * _InputLiveBody;

  ListPOfCATCellManifold   _InputCellManifoldList;
  CATListOfInt             _InputCellManifoldTypeList;//parallel to _InputCellManifoldList initialized to -1; 1=>Top; 2=>Support
  
  CATGMLiveShapeButtonType _ButtonType;
  CATGMLiveShapeButtonSide _ButtonSide;
  CATMathPoint             _SphereCenter;
  double                   _SphereRadius;
  CATMathPoint             _EdgeMathPoint;
  double                   _EdgeRadius;
  CATMathPlane             _EdgeMathPlane;
};

// --------------------------------------
// CATCreateGMLiveShapeButtonData
// --------------------------------------
// @nocgmitf
ExportedByPersistentCell CATGMLiveShapeButtonData * CATCreateGMLiveShapeButtonData(
  CATLiveBody            * iLiveBody,
  ListPOfCATCellManifold & iCellManifoldList, 
  CATListOfInt           & iCellManifoldTypeList,
  CATGMLiveShapeButtonType iButtonType,
  CATGMLiveShapeButtonSide iButtonSide,
  CATMathPoint           & iSphereCenter,
  double                   iSphereRadius,
  CATMathPoint           & iEdgeCenter,
  double                   iEdgeRadius,
  CATMathPlane           & iEdgePlane);

#endif
