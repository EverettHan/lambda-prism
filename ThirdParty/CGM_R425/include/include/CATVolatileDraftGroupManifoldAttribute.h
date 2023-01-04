// COPYRIGHT DASSAULT SYSTEMES 2020, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : ZUT
//
// DESCRIPTION  : CATVolatileDraftGroupManifoldAttribute
//
//=============================================================================
// Creation ZUT March 2020
//=============================================================================

#ifndef CATVolatileDraftGroupManifoldAttribute_H
#define CATVolatileDraftGroupManifoldAttribute_H

#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATManifoldAttribute.h"
#include "CATManifoldGroupAttribute.h"
#include "CATDataType.h"
#include "ListPOfCATFace.h" 
#include "CATMathInline.h"

class CATCell;

class ExportedByPersistentCell CATVolatileDraftGroupManifoldAttribute : public CATManifoldGroupAttribute
{
public:
  CATCGMDeclareAttribute (CATVolatileDraftGroupManifoldAttribute, CATManifoldAttribute);

  CATCGMNewClassArrayDeclare; // Pool allocation

  CATVolatileDraftGroupManifoldAttribute(); 
  virtual ~CATVolatileDraftGroupManifoldAttribute();

  // Cast
  virtual CATVolatileDraftGroupManifoldAttribute * GetAsVolatileDraftGroupManifoldAttribute();
  
  virtual CATManifoldAttribute * CreateImageManifoldAttribute(CATLiveBody & iLiveBody, CATLISTP(CATManifoldAttribute) & iParentManifoldAttributes) const;

  virtual CATCellManifoldGroupNavigator * CreateGroupNavigator(CATLiveBody * iLiveBody, const CATTopData & iTopData, CATCellManifoldGroup * iGroup) const;

  virtual CATBoolean AreSpecificDatasImagesEqualToParents(CATCellManifoldGroupCarrier * iCellManifoldGroupCarrier)const;
  virtual CATBoolean HaveSameType(CATManifoldAttribute & iOtherManifoldAttribute)const;

  virtual CATManifoldAttribute * Clone(CATCloneManager & iCloneManager) const;
  virtual void Move3D(CATTransfoManager & iTransfoManager);

  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream & ioStream);

  virtual void Dump(CATCGMOutput & oStr) const;
  virtual void GetColor(int & oRed, int & oGreen, int & oBlue) const;

protected:

  virtual void Write(CATCGMStream & ioStream) const;
  virtual void Read(CATCGMStream & ioStream);

  virtual CATManifoldAttribute * CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) & iListOfParentGroups, 
                                                      const CATCellManifoldGroup           & iImageCellManifoldGroup, 
                                                            CATCellManifoldsManager        & iCellManifoldsManager) const;

  short _VDGStreamVersion; // Version du stream
};

#endif /* CATVolatileDraftGroupManifoldAttribute_H */
