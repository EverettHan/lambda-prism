#ifndef CATCellManifoldWallNavigatorInterface_H
#define CATCellManifoldWallNavigatorInterface_H

#include "CATCellManifoldGroupNavigator.h"
#include "CATGMModelInterfaces.h"
#include "CATListOfShort.h"
#include "ListPOfCATCellManifoldGroup.h"

class CATLiveBody;
class CATCellManifoldGroup;

class ExportedByCATGMModelInterfaces CATCellManifoldWallNavigatorInterface : public CATCellManifoldGroupNavigator
{
public:

  // Constructor
  CATCellManifoldWallNavigatorInterface();

  // Destructor
  virtual ~CATCellManifoldWallNavigatorInterface();

  CATCGMNewClassArrayDeclare; // Pool allocation

  CATCellManifoldWallNavigatorInterface * GetAsWallNavigatorInterface();

  virtual HRESULT GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const = 0;
  virtual HRESULT GetAllCellManifolds(ListPOfCATCellManifold & oCellManifolds) const = 0;

  virtual CATLiveBody& GetLiveBody() const = 0;

  //------------------------------------------------------------
  // Wall specific methods
  //------------------------------------------------------------
  virtual HRESULT GetRepByWallSide(ListPOfCATCellManifold oRep[2]) = 0;
  virtual HRESULT GetWallData(double &oThickness) = 0;

  // oRelativeWallSideOrientationForEachConnectedBend is index synchronized with oConnectedWalls and can take the following value :
  //  - 0 : if Rep[0] of the bend corresponds (is connected) to Rep[0] of the wall
  //  - 1 : if Rep[0] of the bend corresponds (is connected) to Rep[1] of the wall
  virtual HRESULT GetConnectedBends(ListPOfCATCellManifoldGroup &oConnectedBends, CATListOfShort *oRelativeWallSideOrientationForEachConnectedBend = NULL) = 0;

  // oRelativeWallSideOrientation is index synchronized with oGroupOfWallAndBend and can be either 0 or 1
  // if two elements of oGroupOfWallAndBend have the same orientation value, then Rep1[0] corresponds to Rep2[0], else, Rep1[0] corresponds to Rep2[1]
  virtual HRESULT GetGroupOfWallAndBend(ListPOfCATCellManifoldGroup &oGroupOfWallAndBend, CATListOfShort *oRelativeWallSideOrientation = NULL) = 0;
  //------------------------------------------------------------

protected:
  void Dump(CATCGMOutput& Output);
};

#endif
