#ifndef CATCellManifoldWallNavigator_H
#define CATCellManifoldWallNavigator_H

#include "CATPersistentCell.h"

#include "CATCellManifoldWallNavigatorInterface.h"
#include "CATCellManifoldGroupNavigator.h"
#include "CATDRepNavigator.h"
#include "CATWallManifoldAttribute.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATCellManifoldGroup.h"

class CATLiveBody;
class CATCellManifold;
class CATCellManifoldGroup;

class ExportedByPersistentCell CATCellManifoldWallNavigator : public CATCellManifoldWallNavigatorInterface
{
public:

  // Constructor
  CATCellManifoldWallNavigator();
  CATCellManifoldWallNavigator(CATLiveBody * iLiveBody, CATCellManifoldGroup * iNetworkGroup);
  CATCellManifoldWallNavigator(CATDRepNavigator * iDrepNavigator, CATCellManifoldGroup * iNetworkGroup);
  CATCellManifoldWallNavigator(CATCellManifoldWallNavigator *iWallNavigator);

  CATCGMDeclareManifoldNavigator(CATCellManifoldWallNavigator, CATCellManifoldWallNavigatorInterface);

  // Destructor
  virtual ~CATCellManifoldWallNavigator();

  CATCellManifoldWallNavigator * GetAsWallNavigator();

  virtual HRESULT GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const;
  virtual HRESULT GetAllCellManifolds(ListPOfCATCellManifold & oCellManifolds) const;
  INLINE virtual CATLiveBody& GetLiveBody() const { return *_LiveBody; };

  //------------------------------------------------------------
  // Wall specific methods
  //------------------------------------------------------------
  HRESULT GetRepByWallSide(ListPOfCATCellManifold oRep[2]);
  HRESULT GetWallData(double &oThickness);

  // oRelativeWallSideOrientationForEachConnectedBend is index synchronized with oConnectedWalls and can take the following value :
  //  - 0 : if Rep[0] of the bend corresponds (is connected) to Rep[0] of the wall
  //  - 1 : if Rep[0] of the bend corresponds (is connected) to Rep[1] of the wall
  HRESULT GetConnectedBends(ListPOfCATCellManifoldGroup &oConnectedBends, CATListOfShort *oRelativeWallSideOrientationForEachConnectedBend = NULL);

  // oRelativeWallSideOrientation is index synchronized with oGroupOfWallAndBend and can be either 0 or 1
  // if two elements of oGroupOfWallAndBend have the same orientation value, then Rep1[0] corresponds to Rep2[0], else, Rep1[0] corresponds to Rep2[1]
  HRESULT GetGroupOfWallAndBend(ListPOfCATCellManifoldGroup &oGroupOfWallAndBend, CATListOfShort *oRelativeWallSideOrientation = NULL);
  //------------------------------------------------------------

  //------------------------------------------------------------
  // Stream / Unstream 
  //------------------------------------------------------------
  void Stream(CATCGMStream& ioStr, CATGeoFactory * iFactory) const;
  void UnStream(CATCGMStream& ioStr, CATGeoFactory * iFactory);

protected:
  void Init(CATLiveBody * iLiveBody, CATCellManifoldGroup * iNetworkGroup);
  void GetWallManifoldAttribute(CATWallManifoldAttribute *& oWallAttr);
  INLINE CATSoftwareConfiguration* GetConfig() { return (_TopData && _TopData->GetSoftwareConfiguration()) ? _TopData->GetSoftwareConfiguration() : _BSFConfig; };

private:
  CATLiveBody * _LiveBody;
  CATCellManifoldGroup * _NetworkGroup;
  CATWallManifoldAttribute * _WallAttr;
  CATSoftwareConfiguration *_BSFConfig;
};

// ---------------------------------------
// CATCreateCellManifoldWallNavigator
// ---------------------------------------
ExportedByPersistentCell CATCellManifoldWallNavigator * CATCreateCellManifoldWallNavigator(CATLiveBody * iLiveBody, CATCellManifoldGroup * iNetworkGroup);

#endif
