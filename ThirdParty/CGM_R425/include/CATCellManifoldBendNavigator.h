#ifndef CATCellManifoldBendNavigator_H
#define CATCellManifoldBendNavigator_H

#include "CATPersistentCell.h"

#include "CATCellManifoldBendNavigatorInterface.h"
#include "CATCellManifoldGroupNavigator.h"
#include "CATDRepNavigator.h"
#include "CATBendManifoldAttribute.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATCellManifoldGroup.h"

class CATLiveBody;
class CATCellManifold;
class CATCellManifoldGroup;

class ExportedByPersistentCell CATCellManifoldBendNavigator : public CATCellManifoldBendNavigatorInterface
{
public:

  // Constructor
  CATCellManifoldBendNavigator();
  CATCellManifoldBendNavigator(CATLiveBody * iLiveBody, CATCellManifoldGroup * iNetworkGroup);
  CATCellManifoldBendNavigator(CATDRepNavigator * iDrepNavigator, CATCellManifoldGroup * iNetworkGroup);
  CATCellManifoldBendNavigator(CATCellManifoldBendNavigator *iBendNavigator);

  CATCGMDeclareManifoldNavigator(CATCellManifoldBendNavigator, CATCellManifoldBendNavigatorInterface);

  // Destructor
  virtual ~CATCellManifoldBendNavigator();

  CATCellManifoldBendNavigator * GetAsBendNavigator();

  virtual HRESULT GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const;
  virtual HRESULT GetAllCellManifolds(ListPOfCATCellManifold & oCellManifolds) const;
  INLINE virtual CATLiveBody& GetLiveBody() const { return *_LiveBody; };

  //------------------------------------------------------------
  // Bend specific methods
  //------------------------------------------------------------
  HRESULT GetRepByWallSide(ListPOfCATCellManifold oRep[2]);
  HRESULT GetBendData(double &oThickness, double &oMinRadius, double &oMaxRadius, double &oAngle);

  // oRelativeWallSideOrientationForEachConnectedWall is index synchronized with oConnectedWalls and can take the following value :
  //  - 0 : if Rep[0] of the bend corresponds (is connected) to Rep[0] of the wall
  //  - 1 : if Rep[0] of the bend corresponds (is connected) to Rep[1] of the wall
  HRESULT GetConnectedWallsByBendSide(ListPOfCATCellManifoldGroup oConnectedWalls[2], CATListOfShort oRelativeWallSideOrientationForEachConnectedWall[2] = NULL);

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
  void GetBendManifoldAttribute(CATBendManifoldAttribute *& oBendAttr);
  INLINE CATSoftwareConfiguration* GetConfig() { return (_TopData && _TopData->GetSoftwareConfiguration()) ? _TopData->GetSoftwareConfiguration() : _BSFConfig; };

private:
  CATLiveBody * _LiveBody;
  CATCellManifoldGroup * _NetworkGroup;
  CATBendManifoldAttribute * _BendAttr;
  CATSoftwareConfiguration *_BSFConfig;
};

// ---------------------------------------
// CATCreateCellManifoldBendNavigator
// ---------------------------------------
ExportedByPersistentCell CATCellManifoldBendNavigator * CATCreateCellManifoldBendNavigator(CATLiveBody * iLiveBody, CATCellManifoldGroup * iNetworkGroup);

#endif
