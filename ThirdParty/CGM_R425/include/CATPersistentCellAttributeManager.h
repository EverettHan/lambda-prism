#ifndef CATPersistentCellAttributeManager_H
#define CATPersistentCellAttributeManager_H
//===================================================================
// COPYRIGHT Dassault Systemes 2004
//===================================================================
//
// CATPersistentCellAttributeManager.h
// 		
//===================================================================
//  Jab 2008  Creation: PFV
//===================================================================

#include "CATAutoBaseAttributeManager.h"
#include "CATCell.h"
#include "ListPOfCATPersistentCells.h"
#include "CATCGMNewArray.h"
#include "CATMathInline.h"

class CATCGMAttrId;
class CATPersistentCellFactory;
class CATPersistentCellAttr;
class CATPersistentCell;
class CATCell;

class ExportedByPersistentCell CATPersistentCellAttributeManager : public CATAutoBaseAttributeManager
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
  DEFINE_ADVOP_CLASS(CATPersistentCellAttributeManager)

  CATPersistentCellAttributeManager();
  virtual ~CATPersistentCellAttributeManager();

  void SetPersistentCellFactory(CATPersistentCellFactory* iFactory);
  void AttachPersistentCellToCATCell(CATPersistentCell &iPersistentCell, CATCell &iCell);
  void GetPersistentCells(CATCell* iCell, ListPOfCATPersistentCells& oPCells);
  void RemoveRepInCellAttribute(CATCell *iCell, CATPersistentCell* iPCell);

protected:
  virtual void ReleaseOneAttribute(CATGeometry *iGeometry, CATCGMAttribute * iAttribute);

private:
  CATPersistentCellFactory * _Factory;
};

#endif
