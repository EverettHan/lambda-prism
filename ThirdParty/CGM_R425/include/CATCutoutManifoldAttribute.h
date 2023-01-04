#ifndef CATCutoutManifoldAttribute_h
#define CATCutoutManifoldAttribute_h

// COPYRIGHT DASSAULT SYSTEMES  2013

#include "CATCGMNewArray.h"
#include "CATManifoldAttribute.h"
#include "CATPersistentCell.h"
#include "CATSoftwareConfiguration.h"
#include "ListPOfCATCellManifold.h"
#include "CATCell.h"
#include "ListPOfCATFace.h"

class CATCloneManager;
class CATTransfoManager;

class ExportedByPersistentCell CATCutoutManifoldAttribute : public CATManifoldAttribute
{
public:
  CATCGMDeclareAttribute (CATCutoutManifoldAttribute,CATManifoldAttribute);

  CATCutoutManifoldAttribute();
  CATCutoutManifoldAttribute(ListPOfCATCellManifold iCutoutSupports[2]);
  ~CATCutoutManifoldAttribute();
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATCellManifoldGroupNavigator* CreateGroupNavigator(CATLiveBody * iLiveBody, const CATTopData & iTopData, CATCellManifoldGroup * iGroup) const;
  CATManifoldAttribute* CreateImageManifoldAttribute(CATLiveBody &iLiveBody, CATLISTP(CATManifoldAttribute) &iParentManifoldAttributes) const;
  CATManifoldAttribute* Clone(CATCloneManager& iCloneManager) const;
  void Move3D(CATTransfoManager& iTransfoManager);
  void GetColor(int &oR, int &oG, int &oB) const;

  CATCutoutManifoldAttribute* GetAsCutoutManifoldAttribute();
  virtual CATBoolean HaveSameType(CATManifoldAttribute &iOtherManifoldAttribute)const;
  virtual CATBoolean IsEquivalentTo(const CATManifoldAttribute &iOtherManifoldAttribute, CATGeoFactory * iFactory) const;

  virtual void Dump(CATCGMOutput& iWhereToWrite) const;
  void Stream(CATCGMStream & ioStream) const;
  void UnStream(CATCGMStream& ioStream);

  //------------------------------------------------------------
  // Cutout specific methods
  //------------------------------------------------------------
  void GetCutoutSupports(ListPOfCATCellManifold oCutoutSupports[2]) const;
  //------------------------------------------------------------

protected:
  virtual CATManifoldAttribute * CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) &iParentGroups, 
                                                      const CATCellManifoldGroup           &iImageCellManifoldGroup, 
                                                      CATCellManifoldsManager &iCellManifoldsManager) const;

  short CompareCells(const CATCell *iRefCell, const CATCell *iResultCell) const;
  CATBoolean CompareFaceLists(const ListPOfCATFace &iThisFaceList, const ListPOfCATFace &iOtherFaceList, CATBoolean iPrintDebugInfo = TRUE) const;
  CATBoolean CompareCMList(const ListPOfCATCellManifold &iThisList, const ListPOfCATCellManifold &iOtherList) const;

private:
  CATSoftwareConfiguration* GetConfig() const;
  CATSoftwareConfiguration* _Config;

  //------------------------------------------------------------
  // Cutout specific data
  //------------------------------------------------------------
  ListPOfCATCellManifold _CutoutSupports[2];
  //------------------------------------------------------------
};

#endif

