// COPYRIGHT DASSAULT SYSTEMES 2020, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : ZUT
//
// DESCRIPTION  : CATCellManifoldThinWallDraftGroupNavigator
//
//=============================================================================
// Creation ZUT March 2020
//=============================================================================

#ifndef CATCellManifoldThinWallDraftGroupNavigator_H
#define CATCellManifoldThinWallDraftGroupNavigator_H

#include "CATPersistentCell.h"
#include "CATCellManifoldVolatileDraftGroupNavigator.h"
#include "CATMathInline.h"

class CATThinWallDraftGroupManifoldAttribute;

class ExportedByPersistentCell CATCellManifoldThinWallDraftGroupNavigator : public CATCellManifoldVolatileDraftGroupNavigator
{
public:

  CATCGMDeclareManifoldNavigator(CATCellManifoldThinWallDraftGroupNavigator, CATCellManifoldVolatileDraftGroupNavigator);

  // Constructor
  CATCellManifoldThinWallDraftGroupNavigator(CATLiveBody * iLiveBody, CATCellManifoldGroup * iNetworkGroup);
  CATCellManifoldThinWallDraftGroupNavigator(CATDRepNavigator * iDrepNavigator, CATCellManifoldGroup * iNetworkGroup);
  CATCellManifoldThinWallDraftGroupNavigator(CATCellManifoldThinWallDraftGroupNavigator * iThinWallDraftGroupNavigator);

  // Destructor
  virtual ~CATCellManifoldThinWallDraftGroupNavigator();

  // Cast
  virtual CATCellManifoldThinWallDraftGroupNavigator * GetAsThinWallDraftGroupNavigator();

  virtual CATBoolean BelongsToThinWallDraftGroup(CATCellManifold * iCM) const;

  void Dump(CATCGMOutput & oStr);

  // @nocgmitf
  void Stream(CATCGMStream& ioStr, CATGeoFactory * iFactory) const;
  // @nocgmitf
  void UnStream(CATCGMStream& ioStr, CATGeoFactory * iFactory);

protected:

  CATCellManifoldThinWallDraftGroupNavigator();

  void GetThinWallDraftGroupManifoldAttribute(CATThinWallDraftGroupManifoldAttribute *& oThinWallDraftGroupAttr);

  CATThinWallDraftGroupManifoldAttribute  * _ThinWallDraftGroupAttr;
};

// ---------------------------------------
// CATCreateCellManifoldThinWallDraftGroupNavigator
// ---------------------------------------
ExportedByPersistentCell CATCellManifoldThinWallDraftGroupNavigator * CATCreateCellManifoldThinWallDraftGroupNavigator(CATLiveBody          * iLiveBody,
                                                                                                                       CATCellManifoldGroup * iNetworkGroup);

#endif /* CATCellManifoldThinWallDraftGroupNavigator_H */
