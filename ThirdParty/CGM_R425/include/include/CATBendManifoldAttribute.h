#ifndef CATBendManifoldAttribute_h
#define CATBendManifoldAttribute_h

#include "CATCGMNewArray.h"
#include "CATManifoldAttribute.h"
#include "CATPersistentCell.h"
#include "CATSoftwareConfiguration.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "CATListOfShort.h"

class CATCloneManager;
class CATTransfoManager;

class ExportedByPersistentCell CATBendManifoldAttribute : public CATManifoldAttribute
{
public:
  CATCGMDeclareAttribute(CATBendManifoldAttribute, CATManifoldAttribute);

  CATBendManifoldAttribute();
  ~CATBendManifoldAttribute();
  CATCGMNewClassArrayDeclare; // Pool allocation

  CATCellManifoldGroupNavigator* CreateGroupNavigator(CATLiveBody *iLiveBody, const CATTopData &iTopData, CATCellManifoldGroup *iGroup) const;
  CATManifoldAttribute* CreateImageManifoldAttribute(CATLiveBody &iLiveBody, CATLISTP(CATManifoldAttribute) &iParentManifoldAttributes) const;
  CATManifoldAttribute* Clone(CATCloneManager& iCloneManager) const;
  void Move3D(CATTransfoManager& iTransfoManager);
  void GetColor(int &oR, int &oG, int &oB) const;

  CATBendManifoldAttribute *GetAsBendManifoldAttribute();
  virtual CATBoolean HaveSameType(CATManifoldAttribute &iOtherManifoldAttribute)const;
  virtual CATBoolean IsEquivalentTo(const CATManifoldAttribute &iOtherManifoldAttribute, CATGeoFactory *iFactory) const;

  virtual void Dump(CATCGMOutput& iWhereToWrite) const;
  void Stream(CATCGMStream & ioStream) const;
  void UnStream(CATCGMStream& ioStream);

  //------------------------------------------------------------
  // Bend specific methods (utils)
  //------------------------------------------------------------
  static HRESULT GetCylinderData(CATCellManifoldGroup &iBendGroup, CATSoftwareConfiguration *iConfig, CATMathLine oAxis[2], double oRadius[2]);
  static HRESULT GetRepByWallSide(CATCellManifoldGroup &iBendGroup, CATSoftwareConfiguration *iConfig, ListPOfCATCellManifold oRep[2]);
  static HRESULT GetBendData(CATCellManifoldGroup &iBendGroup, CATSoftwareConfiguration *iConfig, CATLiveBody &iLiveBody, double &oThickness, double &oMinRadius, double &oMaxRadius, double &oAngle);
  static HRESULT GetConnectedWallsByBendSide(CATCellManifoldGroup &iBendGroup, CATSoftwareConfiguration *iConfig, CATLiveBody &iLiveBody, ListPOfCATCellManifoldGroup oConnectedWalls[2], CATListOfShort oRelativeWallSideOrientationForEachConnectedWall[2] = NULL);
  static HRESULT GetGroupOfWallAndBend(CATCellManifoldGroup &iWallGroup, CATSoftwareConfiguration *iConfig, CATLiveBody &iLiveBody, ListPOfCATCellManifoldGroup &oGroupOfWallAndBend, CATListOfShort *oRelativeWallSideOrientation = NULL);
  //------------------------------------------------------------

protected:
  virtual CATManifoldAttribute * CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) &iParentGroups,
    const CATCellManifoldGroup &iImageCellManifoldGroup,
    CATCellManifoldsManager &iCellManifoldsManager) const;

private:
  CATSoftwareConfiguration* GetConfig() const;
  CATSoftwareConfiguration* _Config;
};

#endif

