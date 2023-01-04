#ifndef CATCellManifoldPatternLayer_h
#define CATCellManifoldPatternLayer_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATIACGMLevel.h"
#include "CATCGMNewArray.h"
#include "CATCellManifoldGroupLayer.h"
#include "CATMathPoint.h"

class CATGeometry;
class CATCloneManager;
class CATTransfoManager;

#include "CATGMModelInterfaces.h"
class ExportedByCATGMModelInterfaces CATCellManifoldPatternLayer : public CATCellManifoldGroupLayer
{
public:
  CATCGMDeclareAttribute (CATCellManifoldPatternLayer,CATCellManifoldGroupLayer);

  CATCellManifoldPatternLayer(); // Default constructr is mandatory
  virtual ~CATCellManifoldPatternLayer();

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

