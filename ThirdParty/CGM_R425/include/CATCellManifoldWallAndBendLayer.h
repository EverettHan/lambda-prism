#ifndef CATCellManifoldWallAndBendLayer_H
#define CATCellManifoldWallAndBendLayer_H

#include "CATCGMNewArray.h"
#include "CATCellManifoldGroupLayer.h"
#include "CATGMModelInterfaces.h"

class ExportedByCATGMModelInterfaces CATCellManifoldWallAndBendLayer : public CATCellManifoldGroupLayer
{
public:
  CATCGMDeclareAttribute (CATCellManifoldWallAndBendLayer,CATCellManifoldGroupLayer);

  CATCellManifoldWallAndBendLayer();
  virtual ~CATCellManifoldWallAndBendLayer();

  virtual CATBoolean IsHierarchichal();
  virtual CATBoolean IsContextual();
  virtual HRESULT IsCellManifoldGroupMergeAllowed(CATBoolean iWithCellManifoldBelongingToAnOtherGroup);

  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream);
  
  virtual void Dump(CATCGMOutput& iWhereToWrite) const; 

  HRESULT CreateGroupNavigators(CATLiveBody * iLiveBody, CATTopData & iTopData, ListPOfCATCellManifoldGroupNavigator &oNavigatorList);

private:
};

#endif

