#ifndef CATCellManifoldCRTCurvedBendNavigator_H
#define CATCellManifoldCRTCurvedBendNavigator_H

#include "CATGMModelInterfaces.h"
#include "CATCellManifoldCRTNavigator.h"

#include "CATErrorDef.h"

class CATCellManifoldGroup;


class ExportedByCATGMModelInterfaces CATCellManifoldCRTCurvedBendNavigator : public CATCellManifoldCRTNavigator
{
public:

  // Constructor
  CATCellManifoldCRTCurvedBendNavigator(); 

  // Destructor
  virtual ~CATCellManifoldCRTCurvedBendNavigator();

  virtual CATCellManifoldCRTCurvedBendNavigator* GetAsCRTCurvedBendNavigator();

  virtual HRESULT GetNetworkGroup(CATCellManifoldGroup*& oNetworkGroup);

  virtual HRESULT GetBendGroup(CATCellManifoldGroup*& oBendGroup);

  virtual HRESULT GetFirstWallGroup(CATCellManifoldGroup*& oFirstWallGroup);

  virtual HRESULT GetSecondWallGroup(CATCellManifoldGroup*& oSecondWallGroup);

protected:
  void Dump(CATCGMOutput& Output);

};


#endif
