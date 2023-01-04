#ifndef CATCellManifoldOffsetNavigator_H
#define CATCellManifoldOffsetNavigator_H

#include "CATPersistentCell.h"
#include "CATCellManifoldGroupNavigator.h"
#include "CATTopData.h"
#include "CATLiveBody.h"
#include "CATCellManifoldGroup.h"
#include "CATOffsetManifoldSpecificationAttribute.h"
#include "CATOffsetLateralFacesManifoldAttribute.h"
#include "CATCellManifoldOffsetNavigatorInterface.h"

class CATDRepNavigator;
class CATCGMOutput;
class CATInstancesNavigator;

class ExportedByPersistentCell CATCellManifoldOffsetNavigator : public CATCellManifoldOffsetNavigatorInterface
{
public:
  CATCellManifoldOffsetNavigator(const CATTopData &iData, CATLiveBody* iLiveBody, CATCellManifoldGroup* iNetworkGroup); 
  CATCellManifoldOffsetNavigator(CATDRepNavigator * iDrepNavigator, CATCellManifoldGroup* iNetworkGroup);
  CATCellManifoldOffsetNavigator(CATCellManifoldOffsetNavigator * iOffsetNavigator);
  CATCGMNewClassArrayDeclare;      // Pool allocation

  // Destructor
  virtual ~CATCellManifoldOffsetNavigator();
  // @nocgmitf
  HRESULT    GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const;
  // @nocgmitf
  CATBoolean BelongsToOffsetGroup(CATCellManifold * iCM, short &oSkinNumber);
  // @nocgmitf
  CATBoolean BelongsToOffsetGroup(CATCell * iCell, short &oSkinNumber);
  // @nocgmitf
  double     GetOffsetValue(short iSkinNumber); // we presume that each son of a skin has the same offsetValue - To Delete VB7
  // @nocgmitf
  CATBoolean IsNullOffset(short iSkinNumber); // we presume that each son of a skin has the same offsetValue - To Delete VB7
  // @nocgmitf
  int        GetOverloadOffsetValues(short iSkinNumber, CATLISTP(CATCellManifoldGroup) &oOverloadCMGroupRef);
  // @nocgmitf
  CATBoolean HasUpdateGlobalThicknessInputs(short iSkinNumber, CATLISTP(CATFace) &oThickInputFaces, double &oThicknessValue); // global value only - do not use when local value are overloaded
  // @nocgmitf
  double     GetOffsetValue(short iSkinNumber, CATCellManifold * iCM);
  // @nocgmitf
  CATBoolean IsNullOffset(short iSkinNumber, CATCellManifold * iCM);
  // @nocgmitf
  double     GetThicknessValue(short iFirstSkinNumber, short iSecondSkinNumber);
  // @nocgmitf
  // For NaturalShape - assume that there is only two skins
  double     GetThicknessValue(CATCellManifold * iCM);
  //For OffsetReplicator - uses in hyperNavigator
  // @nocgmitf
  void       GetThicknessValueImage(CATFace * iFace, double iThicknessValue, short iSkinNumber, double & oThicknessValue);
  // input : fillet DeclarativeManifold and its radius, target Skin
  // output : radius of image of input DeclarativeManifold on target Skin
  // @nocgmitf
  double     GetFilletParameterImage(double iFilletRadius, CATDeclarativeManifold * iDM, short iTargetSkin);
  // input : edge where Fillet will be created and its radius, target Skin
  // output : radius after an offset on target Skin
  // @nocgmitf
  double     GetFilletParameterImage(double iFilletRadius, CATEdge * iEdge, short iTargetSkin);

  // @nocgmitf
  void GetAllSkins(ListPOfCATCellManifoldGroup& oInstanceGroups, CATListOfShort & oSkinNumbers);
  // @nocgmitf
  int  GetSkinNumber(CATCellManifoldGroup * iGroup) const;

  // @nocgmitf
  void GetSkinGroup(int iSkin, CATCellManifoldGroup *& oOffsetGroup);

  // @nocgmitf
  void GetAllCellManifolds( CATLISTP(CATCellManifold) &oCellManifolds);
  // @nocgmitf
  void GetSkinCellManifolds(int iSkinNumber, CATLISTP(CATCellManifold) &oSkinCellManifolds);
  // @nocgmitf
  void GetSkinCells(int iSkinNumber, CATLISTP(CATCell) &oSkinCells);

  // @nocgmitf
  void GetLateralFacesCellManifolds(CATLISTP(CATCellManifold) &oLateralCellManifolds);
  // @nocgmitf
  CATOffsetLateralFacesManifoldAttribute::LateralFacesType GetLateralFacesType();

  // @nocgmitf <-------------- USED BY KUB/PKC
  void GetReferenceCellManifolds(CATLISTP(CATCellManifold) & oReferenceCellManifolds);
  // @nocgmitf
  void GetReferenceCellManifold(CATCellManifold* &iSkinCellManifold, ListPOfCATCellManifold &oRefCellManifold);
  // @nocgmitf 
  void GetReferenceCellManifoldImages(CATCellManifold *        iReferenceCellManifold, 
                                      short                    iSkinNumber, 
                                      ListPOfCATCellManifold & oReferenceCellManifoldImages);
  // @nocgmitf <-------------- USED BY KUB/PKC
  void GetReferenceCellManifoldImages(CATCellManifold *        iReferenceCellManifold, 
                                      short                    iSkinNumber, 
                                      ListPOfCATCellManifold & oReferenceCellManifoldImages,
                                      double                 & oOffsetValue);
  // @nocgmitf
  void GetSkinCellManifoldImages(CATCellManifold *        iCellManifold,
                                 short                    iSkinNumber, 
                                 ListPOfCATCellManifold & oCellManifoldImages);

  // @nocgmitf
  void GetSkinCellManifoldImages(CATCellManifold *        iCellManifold,
                                 short                    iSkinNumber, 
                                 ListPOfCATCellManifold & oCellManifoldImages,
                                 double                 & oThicknessValue);

  
  //return TRUE if this group is modifiable with CATManifoldEditor
  // @nocgmitf
  virtual CATBoolean IsEditable() const;

  // @nocgmitf
  CATLiveBody * CreateReferenceLiveBody() const;

  // @nocgmitf <-------------- USED BY KUB/PKC
  int GetNumberOfSkins() const;
  // @nocgmitf
  CATLiveBody * GetLiveBody();
  // @nocgmitf
  void DiGraphDump(CATCGMOutput& Output);
  // Check si le model est coherent
  // @nocgmitf
  //-------------------------------------------------------------------------------------
  HRESULT CheckModel(int & oError);

  CATCellManifoldOffsetNavigator * GetAsOffsetNavigator();

private:
  void Dump(CATCGMOutput& Output);
  void Init(const CATTopData *iData, CATLiveBody* iLiveBody, CATCellManifoldGroup* iNetworkGroup);

  CATCellManifoldGroup * GetLateralFacesGroup();

  //VB7 TopData_Nav
  //CATTopData _TopData;
  CATLiveBody* _LiveBody;
  CATCellManifoldGroup* _NetworkGroup;
  CATOffsetManifoldSpecificationAttribute* _OffsetSpec;

  CATInstancesNavigator * _InstancesNavigator;
};

#endif
