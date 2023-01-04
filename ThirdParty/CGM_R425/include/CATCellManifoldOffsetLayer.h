#ifndef CATCellManifoldOffsetLayer_h
#define CATCellManifoldOffsetLayer_h

// COPYRIGHT DASSAULT SYSTEMES  2010

#include "CATIACGMLevel.h"
#include "CATCGMNewArray.h"
#include "CATCellManifoldGroupLayer.h"
#include "CATMathPoint.h"

class CATGeometry;
class CATCloneManager;
class CATTransfoManager;

#include "CATGMModelInterfaces.h"
class ExportedByCATGMModelInterfaces CATCellManifoldOffsetLayer : public CATCellManifoldGroupLayer
{
public:
  CATCGMDeclareAttribute (CATCellManifoldOffsetLayer,CATCellManifoldGroupLayer);

  CATCellManifoldOffsetLayer(); // Default constructr is mandatory
  virtual ~CATCellManifoldOffsetLayer();

  virtual CATBoolean IsHierarchichal();
  virtual CATBoolean IsContextual();
  virtual HRESULT IsCellManifoldGroupMergeAllowed(CATBoolean iWithCellManifoldBelongingToAnOtherGroup);

  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream);
  
  virtual void Dump(CATCGMOutput& iWhereToWrite) const; 

  virtual HRESULT CreateGroupNavigators(CATLiveBody * iLiveBody, CATTopData & iTopData, ListPOfCATCellManifoldGroupNavigator &oNavigatorList);

private:
};
#endif

