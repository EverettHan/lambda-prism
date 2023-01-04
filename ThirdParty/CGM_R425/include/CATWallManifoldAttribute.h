#ifndef CATWallManifoldAttribute_h
#define CATWallManifoldAttribute_h

#include "CATCGMNewArray.h"
#include "CATManifoldAttribute.h"
#include "CATPersistentCell.h"
#include "CATSoftwareConfiguration.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "CATListOfShort.h"

class CATCloneManager;
class CATTransfoManager;

class ExportedByPersistentCell CATWallManifoldAttribute : public CATManifoldAttribute
{
public:
  CATCGMDeclareAttribute (CATWallManifoldAttribute,CATManifoldAttribute);

  CATWallManifoldAttribute();
  ~CATWallManifoldAttribute();
  CATCGMNewClassArrayDeclare; // Pool allocation

  CATCellManifoldGroupNavigator* CreateGroupNavigator(CATLiveBody *iLiveBody, const CATTopData &iTopData, CATCellManifoldGroup *iGroup) const;
  CATManifoldAttribute* CreateImageManifoldAttribute(CATLiveBody &iLiveBody, CATLISTP(CATManifoldAttribute) &iParentManifoldAttributes) const;
  CATManifoldAttribute* Clone(CATCloneManager& iCloneManager) const;
  void Move3D(CATTransfoManager& iTransfoManager);
  void GetColor(int &oR, int &oG, int &oB) const;

  CATWallManifoldAttribute *GetAsWallManifoldAttribute();
  virtual CATBoolean HaveSameType(CATManifoldAttribute &iOtherManifoldAttribute)const;
  virtual CATBoolean IsEquivalentTo(const CATManifoldAttribute &iOtherManifoldAttribute, CATGeoFactory *iFactory) const;

  virtual void Dump(CATCGMOutput& iWhereToWrite) const;
  void Stream(CATCGMStream & ioStream) const;
  void UnStream(CATCGMStream& ioStream);

  //------------------------------------------------------------
  // Wall specific methods (utils)
  //------------------------------------------------------------
  static HRESULT GetPlaneData(CATCellManifoldGroup &iWallGroup, CATSoftwareConfiguration *iConfig, CATMathPlane oPlane[2]);
  static HRESULT GetRepByWallSide(CATCellManifoldGroup &iWallGroup, CATSoftwareConfiguration *iConfig, ListPOfCATCellManifold oRep[2]);
  static HRESULT GetWallData(CATCellManifoldGroup &iWallGroup, CATSoftwareConfiguration *iConfig, double &oThickness);
  static HRESULT GetConnectedBends(CATCellManifoldGroup &iWallGroup, CATSoftwareConfiguration *iConfig, CATLiveBody &iLiveBody, ListPOfCATCellManifoldGroup &oConnectedBends, CATListOfShort *oRelativeWallSideOrientationForEachConnectedBend = NULL);
  static HRESULT GetGroupOfWallAndBend(CATCellManifoldGroup &iWallGroup, CATSoftwareConfiguration *iConfig, CATLiveBody &iLiveBody, ListPOfCATCellManifoldGroup &oGroupOfWallAndBend, CATListOfShort *oRelativeWallSideOrientation = NULL);
  //------------------------------------------------------------

protected:
  virtual CATManifoldAttribute * CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) &iParentGroups, const CATCellManifoldGroup &iImageCellManifoldGroup, CATCellManifoldsManager &iCellManifoldsManager) const;

private:
  CATSoftwareConfiguration* GetConfig() const;
  CATSoftwareConfiguration* _Config;
};

#endif

