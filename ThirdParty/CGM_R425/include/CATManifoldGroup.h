#ifndef CATManifoldGroup_h
#define CATManifoldGroup_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATGeometry.h"

#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATManifoldGroup ;
#else
extern "C" const IID IID_CATManifoldGroup ;
#endif

#include "ListPOfCATDeclarativeManifold.h"
#include "CATListOfShort.h"

class CATManifoldAttribute;
class CATContextualManifoldGroup;

class ExportedByCATGMModelInterfaces CATManifoldGroup : public CATGeometry
{
  CATDeclareInterface;

public:

  // Representation
  virtual void GetRep(ListPOfCATDeclarativeManifold &oRep) const=0;
  virtual void GetRep(ListPOfCATDeclarativeManifold &oRep, CATListOfShort &oType) const=0;
  virtual void GetRep(const int iType, ListPOfCATDeclarativeManifold &oRep) const=0;

  // Manifold Attribute
  virtual void SetManifoldAttribute(CATManifoldAttribute *iAttribute)=0;
  virtual CATManifoldAttribute* GetManifoldAttribute() const=0;

  virtual CATContextualManifoldGroup* GetAsContextualManifoldGroup()=0;
};
  
CATDeclareHandler(CATManifoldGroup,CATGeometry);

#endif
