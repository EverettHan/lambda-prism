// --------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2012
// ................................
//
// ST5: Feature recognition -- Extrusion Layer -- | Generic group model creation |
// --------------------------------------------------------------------------------------//

#ifndef CATCellManifoldExtrusionLayer_H
#define CATCellManifoldExtrusionLayer_H

#include "CATCGMNewArray.h"
#include "CATCellManifoldGroupLayer.h"
#include "CATGMModelInterfaces.h"

class ExportedByCATGMModelInterfaces CATCellManifoldExtrusionLayer : public CATCellManifoldGroupLayer
{
public:
  CATCGMDeclareAttribute (CATCellManifoldExtrusionLayer,CATCellManifoldGroupLayer);

  CATCellManifoldExtrusionLayer(); 
  virtual ~CATCellManifoldExtrusionLayer();

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

