#ifndef CATCellManifoldGroupInLiveBody_H
#define CATCellManifoldGroupInLiveBody_H

#include "CATBoolean.h"
#include "CATMathInline.h"

class CATCellManifoldGroup;
class CATLiveBody;

class CATCellManifoldGroupInLiveBody 
{
  friend class CATCellManifoldGroupAttr;

protected:
  // Constructor
  CATCellManifoldGroupInLiveBody(CATCellManifoldGroup * iCellManifoldGroup, CATLiveBody * iLiveBody);

public:
  // Destructor
  ~CATCellManifoldGroupInLiveBody();

  INLINE CATCellManifoldGroup * GetCellManifoldGroup();
  INLINE CATLiveBody * GetLiveBody();
  static CATBoolean AreEqual(const CATCellManifoldGroupInLiveBody &iCMILB1, const CATCellManifoldGroupInLiveBody &iCMILB2);
  

private:
  CATCellManifoldGroup* _CellManifoldGroup;
  CATLiveBody* _LiveBody;
};


int operator != (const CATCellManifoldGroupInLiveBody &iCMILB1, const CATCellManifoldGroupInLiveBody &iCMILB2);
int operator == (const CATCellManifoldGroupInLiveBody &iCMILB1, const CATCellManifoldGroupInLiveBody &iCMILB2);

INLINE CATCellManifoldGroup * CATCellManifoldGroupInLiveBody::GetCellManifoldGroup()
{
  return _CellManifoldGroup;
}

INLINE CATLiveBody * CATCellManifoldGroupInLiveBody::GetLiveBody()
{
  return _LiveBody;
}
  
#endif

