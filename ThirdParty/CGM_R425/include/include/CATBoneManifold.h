#ifndef CATBoneManifold_h
#define CATBoneManifold_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATContextualManifold.h"
#include "ListPOfCATCellManifold.h"
#include "YI00IMPL.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByYI00IMPL IID IID_CATBoneManifold ;
#else
extern "C" const IID IID_CATBoneManifold ;
#endif

class ExportedByYI00IMPL CATBoneManifold : public CATContextualManifold
{
  CATDeclareInterface;

public:

  virtual void GetSupport(ListPOfCATCellManifold oLeftAndRightSupport[2]) const = 0;

};
  
CATDeclareHandler(CATBoneManifold,CATContextualManifold);

#endif
