//
//===========================================================================
// Class CATCellManifoldGroupAttr
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
// Apr. 2012  Creation.                                                JJ3
//
//===========================================================================
#ifndef CATCellManifoldGroupAttr_H
#define CATCellManifoldGroupAttr_H

#include "CATCGMAttribute.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "ListVOfCATCellManifoldGroupInLiveBodies.h"

#include "CATCellManifoldGroup.h"
#include "CATWeekVersioning.h"

class CATLiveBody;
class CATCellManifoldGroupLayer;


class CATCellManifoldGroupAttr : public CATCGMAttribute
{

  friend class CATCellManifoldGroupAttributeManager;
  CATCGMDeclareAttribute(CATCellManifoldGroupAttr,CATCGMAttribute);

protected:
  CATCellManifoldGroupAttr();
  ~CATCellManifoldGroupAttr();

  CATBoolean AddCellManifoldGroup(CATCellManifoldGroup &iCellManifoldGroup, CATLiveBody *iLiveBody);
  void RemoveCellManifoldGroup(CATCellManifoldGroup &iCellManifoldGroup, CATLiveBody *iLiveBody);

  CATBoolean HasCellManifoldGroups();
  void RemoveCellManifoldGroupsInLiveBody(CATLiveBody *iLiveBody, CATCellManifoldGroupLayer* iCMGroupLayer = NULL);
  

public:
  void GetCellManifoldGroups(const CATLiveBody *iLiveBody, ListPOfCATCellManifoldGroup &oCellManifoldGroups);
  INLINE CATCellManifoldGroup* GetCellManifoldGroup(const CATLiveBody *iLiveBody, CATCellManifoldGroupLayer* iCMGroupLayer);

  // New - SheetMetal request
  void GetCellManifoldGroups(const CATLiveBody *iLiveBody, const CATCellManifoldGroupLayer* iCMGroupLayer, ListPOfCATCellManifoldGroup &oCellManifoldGroups);

private: 
  ListVOfCATCellManifoldGroupInLiveBodies _CellManifoldGroupsInLiveBodies;
};

INLINE CATCellManifoldGroup* CATCellManifoldGroupAttr::GetCellManifoldGroup(const CATLiveBody *iLiveBody, CATCellManifoldGroupLayer* iCMGroupLayer)
{
  int i = 1, n = _CellManifoldGroupsInLiveBodies.Size();
  CATCellManifoldGroup * resultCMGroup = NULL;
  for (i = n; i >= 1; i--)
  {
    CATCellManifoldGroupInLiveBody & CellManifoldGroupInLiveBody = _CellManifoldGroupsInLiveBodies[i];
    if (CellManifoldGroupInLiveBody.GetLiveBody() == iLiveBody)
    {
      CATCellManifoldGroup * curGroup = CellManifoldGroupInLiveBody.GetCellManifoldGroup();
      if ( curGroup && curGroup->HasSameLayer(iCMGroupLayer) )
      {
        if (!resultCMGroup || curGroup==resultCMGroup)
          resultCMGroup = curGroup;
        else
          return NULL; // si plusieur resultat, on retourne NULL. (nouvelle spec LAP)
      }
    }
  }

  return resultCMGroup;
};
#endif
