// COPYRIGHT DASSAULT SYSTEMES 2020, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : ZUT
//
// DESCRIPTION  : CATCellManifoldVolatileDraftGroupNavigator
//
//=============================================================================
// Creation ZUT March 2020
//=============================================================================

#ifndef CATCellManifoldVolatileDraftGroupNavigator_H
#define CATCellManifoldVolatileDraftGroupNavigator_H

#include "CATPersistentCell.h"
#include "CATCellManifoldVolatileDraftGroupNavigatorInterface.h"
#include "CATMathInline.h"

class CATVolatileDraftGroupManifoldAttribute;

class ExportedByPersistentCell CATCellManifoldVolatileDraftGroupNavigator : public CATCellManifoldVolatileDraftGroupNavigatorInterface
{
public:

  CATCGMDeclareManifoldNavigator(CATCellManifoldVolatileDraftGroupNavigator, CATCellManifoldVolatileDraftGroupNavigatorInterface);

  // Constructor
  CATCellManifoldVolatileDraftGroupNavigator(CATLiveBody * iLiveBody, CATCellManifoldGroup * iNetworkGroup);
  CATCellManifoldVolatileDraftGroupNavigator(CATDRepNavigator * iDrepNavigator, CATCellManifoldGroup * iNetworkGroup);
  CATCellManifoldVolatileDraftGroupNavigator(CATCellManifoldVolatileDraftGroupNavigator * iVolatileDraftGroupNavigator);

  // Destructor
  virtual ~CATCellManifoldVolatileDraftGroupNavigator();

  // Cast
  virtual CATCellManifoldVolatileDraftGroupNavigator * GetAsVolatileDraftGroupNavigator();

  virtual HRESULT GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const;

  virtual HRESULT GetDeclarativeType(CATDeclarativeType & oType) const;

  virtual HRESULT GetAllCellManifolds(CATLISTP(CATCellManifold) & oListOfCMs) const;

  virtual CATBoolean BelongsToVolatileDraftGroup(CATCellManifold * iCM) const;

  virtual CATLiveBody * GetLiveBody() const;

  // @nocgmitf
  void Stream(CATCGMStream& ioStr, CATGeoFactory * iFactory) const;
  // @nocgmitf
  void UnStream(CATCGMStream& ioStr, CATGeoFactory * iFactory);

protected:

  CATCellManifoldVolatileDraftGroupNavigator();

  void Init(CATLiveBody * iLiveBody, CATCellManifoldGroup * iNetworkGroup);
  void GetVolatileDraftGroupManifoldAttribute(CATVolatileDraftGroupManifoldAttribute *& oVolatileDraftGroupAttr);

  CATLiveBody                             * _LiveBody;
  CATCellManifoldGroup                    * _NetworkGroup;
  CATVolatileDraftGroupManifoldAttribute  * _VolatileDraftGroupAttr;
};

// ---------------------------------------
// CATCreateCellManifoldVolatileDraftGroupNavigator
// ---------------------------------------
ExportedByPersistentCell CATCellManifoldVolatileDraftGroupNavigator * CATCreateCellManifoldVolatileDraftGroupNavigator(CATLiveBody          * iLiveBody,
                                                                                                                       CATCellManifoldGroup * iNetworkGroup);

#endif /* CATCellManifoldVolatileDraftGroupNavigator_H */
