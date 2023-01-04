#ifndef CATCellManifoldGroupAttributeManager_H
#define CATCellManifoldGroupAttributeManager_H
//===================================================================
// COPYRIGHT Dassault Systemes 2012
//===================================================================
//
// CATCellManifoldGroupAttributeManager.h
// 		
//===================================================================
//  Apr 2012  Creation: JJ3
//===================================================================


#include "CATAutoBaseAttributeManager.h"
#include "CATCGMNewArray.h"
#include "CATMathInline.h"
#include "ListPOfCATCellManifoldGroup.h"

class CATCGMAttrId;
class CATLiveBody;
class CATCellManifoldGroup;
class CATCell;
class CATCellManifoldGroupLayer;

class CATCellManifoldGroupAttributeManager : public CATAutoBaseAttributeManager
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
  DEFINE_ADVOP_CLASS(CATCellManifoldGroupAttributeManager)

  CATCellManifoldGroupAttributeManager();
  virtual ~CATCellManifoldGroupAttributeManager();

  void SetLiveBody(CATLiveBody* iLiveBody);

  CATCellManifoldGroup* GetCellManifoldGroup(CATGeometry& iObject, CATCellManifoldGroupLayer* iGroupLayer) const ;
  
  // Sheet Metal
  void GetCellManifoldGroups(CATGeometry& iObject, const CATCellManifoldGroupLayer* iGroupLayer, ListPOfCATCellManifoldGroup &oCellManifoldGroups) const ;

  void AttachCellManifoldGroupToObject(CATCellManifoldGroup &iCellManifoldGroup, CATGeometry &iObject);
  void DetachCellManifoldGroupFromObject(CATCellManifoldGroup &iCellManifoldGroup, CATGeometry &iObject);

protected:
  virtual void ReleaseOneAttribute(CATGeometry *iGeometry, CATCGMAttribute * iAttribute);

private:
  CATLiveBody* _LiveBody;
};

#endif
