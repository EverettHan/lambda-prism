#ifndef CATAutoBaseAttributeManager_H
#define CATAutoBaseAttributeManager_H
//===================================================================
// COPYRIGHT Dassault Systemes 2004
//===================================================================
//
// CATAutoFilletCATAutoFilletBuildStatus.h
// 		
//===================================================================
//  Feb 2004  Creation: JHG
//===================================================================

#include "PersistentCell.h"
#include "CATTopRibTraceObject.h"
#include "CATBoolean.h"
#include "CATCGMNewArray.h"

#include "CATListOfCATGeometries.h"
#include "CATMathInline.h"

class CATGeoFactory;
class CATSoftwareConfiguration;

class CATCGMAttribute;
class CATCGMAttrId;
class CATCell;

class ExportedByPersistentCell CATAutoBaseAttributeManager : public CATTopRibTraceObject
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
  DEFINE_ADVOP_CLASS(CATAutoBaseAttributeManager)

  CATAutoBaseAttributeManager(CATCGMAttrId* iAttrId);
  virtual ~CATAutoBaseAttributeManager();

  CATLONG32 PutAttributeOnCell(CATGeometry* iGeometry, CATCGMAttribute* iAttribute);

  void ReleaseAttributes();

protected:
  void AddCATCell(CATGeometry *iGeometry);
  virtual void ReleaseOneAttribute(CATGeometry *iGeometry, CATCGMAttribute * iAttribute);
  INLINE CATCGMAttrId* GetAttrId() const;

private:
  CATCGMAttrId*         _AttrId;
  CATLISTP(CATGeometry) _Geometries;
};

INLINE CATCGMAttrId* CATAutoBaseAttributeManager::GetAttrId() const
{
  return _AttrId;
}

#endif
