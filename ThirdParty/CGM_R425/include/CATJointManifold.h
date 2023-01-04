#ifndef CATJointManifold_h
#define CATJointManifold_h

// COPYRIGHT DASSAULT SYSTEMES  2019

#include "CATContextualManifold.h"
#include "ListPOfCATCellManifold.h"
#include "YI00IMPL.h"


#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByYI00IMPL IID IID_CATJointManifold ;
#else
extern "C" const IID IID_CATJointManifold ;
#endif

class ExportedByYI00IMPL CATJointManifold : public CATContextualManifold
{
  CATDeclareInterface;

public:
  
  virtual void Set(const ListPOfCATCellManifold &iRepresentation,
                   const ListPOfCATCellManifold &iConnectedCellManifold,
                   const CATListOfInt           &iType) = 0;



};
  
CATDeclareHandler(CATJointManifold, CATContextualManifold);

#endif
