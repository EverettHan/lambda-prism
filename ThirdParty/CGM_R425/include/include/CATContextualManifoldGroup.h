#ifndef CATContextualManifoldGroup_h
#define CATContextualManifoldGroup_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATManifoldGroup.h"

#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATContextualManifoldGroup ;
#else
extern "C" const IID IID_CATContextualManifoldGroup ;
#endif

#include "ListPOfCATDeclarativeManifold.h"

class ExportedByCATGMModelInterfaces CATContextualManifoldGroup : public CATManifoldGroup
{
  CATDeclareInterface;

public:
  virtual void GetContext(ListPOfCATDeclarativeManifold &oContext) const=0;
  virtual void GetContext(ListPOfCATDeclarativeManifold &oContext, CATListOfShort &oType) const=0;
  virtual void GetContext(const int iType, ListPOfCATDeclarativeManifold &oContext) const=0;

};
  
CATDeclareHandler(CATContextualManifoldGroup,CATManifoldGroup);

#endif
