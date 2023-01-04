// COPYRIGHT DASSAULT SYSTEMES 2020, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : ZUT
//
// DESCRIPTION  : CATCellManifoldVolatileDraftGroupLayer
//
//=============================================================================
// Creation ZUT March 2020
//=============================================================================

#ifndef CATCellManifoldVolatileDraftGroupLayer_H
#define CATCellManifoldVolatileDraftGroupLayer_H

#include "CATCGMNewArray.h"
#include "CATCellManifoldGroupLayer.h"
#include "CATGMModelInterfaces.h"

class ExportedByCATGMModelInterfaces CATCellManifoldVolatileDraftGroupLayer : public CATCellManifoldGroupLayer
{
public:
  CATCGMDeclareAttribute (CATCellManifoldVolatileDraftGroupLayer, CATCellManifoldGroupLayer);

  CATCellManifoldVolatileDraftGroupLayer(); 
  virtual ~CATCellManifoldVolatileDraftGroupLayer();

  virtual CATBoolean IsHierarchichal();
  virtual CATBoolean IsContextual();
  virtual HRESULT IsCellManifoldGroupMergeAllowed(CATBoolean iWithCellManifoldBelongingToAnOtherGroup);

  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream);
  
  virtual void Dump(CATCGMOutput & oStr) const; 

  HRESULT CreateGroupNavigators(CATLiveBody * iLiveBody, CATTopData & iTopData, CATLISTP(CATCellManifoldGroupNavigator) & oListOfNavigator);

private:
};

#endif /* CATCellManifoldVolatileDraftGroupLayer_H */
