#ifndef CATHierarchicalManifoldGroup_h
#define CATHierarchicalManifoldGroup_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATManifoldGroup.h"

#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATHierarchicalManifoldGroup ;
#else
extern "C" const IID IID_CATHierarchicalManifoldGroup ;
#endif

#include "ListPOfCATDeclarativeManifold.h"

class ExportedByCATGMModelInterfaces CATHierarchicalManifoldGroup : public CATManifoldGroup
{
  CATDeclareInterface;

public:
  virtual HRESULT SetRep(ListPOfCATDeclarativeManifold &iRep, CATListOfShort* iType = NULL)=0;

};
  
CATDeclareHandler(CATHierarchicalManifoldGroup,CATManifoldGroup);

#endif
