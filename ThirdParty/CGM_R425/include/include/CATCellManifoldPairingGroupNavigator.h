// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : ZUT
//
// DESCRIPTION  : CATCellManifoldPairingGroupNavigator
//
//=============================================================================
// Creation ZUT February 2021
//=============================================================================

#ifndef CATCellManifoldPairingGroupNavigator_H
#define CATCellManifoldPairingGroupNavigator_H

#include "CATPersistentCell.h"
#include "CATCellManifoldPairingGroupNavigatorInterface.h"
#include "CATMathInline.h"

class CATPairingManifoldAttribute;

class ExportedByPersistentCell CATCellManifoldPairingGroupNavigator : public CATCellManifoldPairingGroupNavigatorInterface
{
public:

  CATCGMDeclareManifoldNavigator(CATCellManifoldPairingGroupNavigator, CATCellManifoldPairingGroupNavigatorInterface);

  // Constructor
  CATCellManifoldPairingGroupNavigator(CATLiveBody * iLiveBody, CATCellManifoldGroup * iNetworkGroup);
  CATCellManifoldPairingGroupNavigator(CATDRepNavigator * iDrepNavigator, CATCellManifoldGroup * iNetworkGroup);
  CATCellManifoldPairingGroupNavigator(CATCellManifoldPairingGroupNavigator * iPairingGroupNavigator);

  // Destructor
  virtual ~CATCellManifoldPairingGroupNavigator();

  // Cast
  virtual CATCellManifoldPairingGroupNavigator * GetAsPairingGroupNavigator();

  virtual HRESULT GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const;

  virtual HRESULT GetDeclarativeType(CATDeclarativeType & oType) const;

  virtual HRESULT GetAllCellManifolds(CATLISTP(CATCellManifold) & oListOfCMs) const;

  virtual CATBoolean BelongsToPairingGroup(CATCellManifold * iCM) const;

  virtual CATLiveBody * GetLiveBody() const;

  // @nocgmitf
  void Stream(CATCGMStream& ioStr, CATGeoFactory * iFactory) const;
  // @nocgmitf
  void UnStream(CATCGMStream& ioStr, CATGeoFactory * iFactory);

protected:

  CATCellManifoldPairingGroupNavigator();

  void Init(CATLiveBody * iLiveBody, CATCellManifoldGroup * iNetworkGroup);
  void GetPairingManifoldAttribute(CATPairingManifoldAttribute *& oPairingAttr);

  CATLiveBody                  * _LiveBody;
  CATCellManifoldGroup         * _NetworkGroup;
  CATPairingManifoldAttribute  * _PairingAttr;
};

// ---------------------------------------
// CATCreateCellManifoldPairingGroupNavigator
// ---------------------------------------
ExportedByPersistentCell CATCellManifoldPairingGroupNavigator * CATCreateCellManifoldPairingGroupNavigator(CATLiveBody          * iLiveBody,
                                                                                                           CATCellManifoldGroup * iNetworkGroup);

#endif /* CATCellManifoldPairingGroupNavigator_H */
