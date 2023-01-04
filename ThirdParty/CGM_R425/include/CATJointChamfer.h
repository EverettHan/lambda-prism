#ifndef CATJointChamfer_h
#define CATJointChamfer_h

// COPYRIGHT DASSAULT SYSTEMES  2019

#include "CATContextualManifold.h"
#include "CATJointManifold.h"
#include "ListPOfListPOfCATCellManifolds.h"


#include "YI00IMPL.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByYI00IMPL IID IID_CATJointChamfer ;
#else
extern "C" const IID IID_CATJointChamfer ;
#endif

//class ExportedByYI00IMPL CATJointChamfer : public CATContextualManifold
class ExportedByYI00IMPL CATJointChamfer : public CATJointManifold
{
  CATDeclareInterface;

public:
  

};
  
//CATDeclareHandler(CATJointChamfer, CATContextualManifold);
CATDeclareHandler(CATJointChamfer, CATJointManifold);

#endif
