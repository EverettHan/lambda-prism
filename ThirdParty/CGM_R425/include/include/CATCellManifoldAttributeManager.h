#ifndef CATCellManifoldAttributeManager_H
#define CATCellManifoldAttributeManager_H
//===================================================================
// COPYRIGHT Dassault Systemes 2004
//===================================================================
//
// CATCellManifoldAttributeManager.h
// 		
//===================================================================
//  Apr 2008  Creation: PFV
//===================================================================


#include "CATAutoBaseAttributeManager.h"
#include "CATCGMNewArray.h"
#include "CATMathInline.h"

class CATCGMAttrId;
class CATLiveBody;
class CATCellManifold;
class CATCell;

class ExportedByPersistentCell CATCellManifoldAttributeManager : public CATAutoBaseAttributeManager
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
  DEFINE_ADVOP_CLASS(CATCellManifoldAttributeManager)

  CATCellManifoldAttributeManager();
  virtual ~CATCellManifoldAttributeManager();

  CATCellManifold* GetCellManifold(CATCell& iCell) const ;

  void SetLiveBody(CATLiveBody* iLiveBody);

  void AttachCellManifoldToCATCell(CATCellManifold &iCellManifold, CATCell &iCell, const CATBoolean iCheck = FALSE);

protected:
  virtual void ReleaseOneAttribute(CATGeometry *iGeometry, CATCGMAttribute * iAttribute);

private:
  CATLiveBody* _LiveBody;
};

#endif
