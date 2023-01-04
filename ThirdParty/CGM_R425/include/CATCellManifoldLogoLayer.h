// --------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2015
// ................................
//
// JNF: Feature recognition -- Logo Layer -- | Generic group model creation |
// --------------------------------------------------------------------------------------//

#ifndef CATCellManifoldLogoLayer_H
#define CATCellManifoldLogoLayer_H

#include "CATCGMNewArray.h"
#include "CATCellManifoldGroupLayer.h"
#include "CATGMModelInterfaces.h"

class ExportedByCATGMModelInterfaces CATCellManifoldLogoLayer : public CATCellManifoldGroupLayer
{
public:
  CATCGMDeclareAttribute (CATCellManifoldLogoLayer,CATCellManifoldGroupLayer);

  CATCellManifoldLogoLayer(); 
  virtual ~CATCellManifoldLogoLayer();

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

