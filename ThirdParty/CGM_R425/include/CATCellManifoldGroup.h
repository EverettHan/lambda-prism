#ifndef CATCellManifoldGroup_h
#define CATCellManifoldGroup_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATManifold.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "CATIACGMLevel.h"
#include "CATListOfShort.h"

class CATManifoldAttribute;
class CATCellManifoldGroupLayer;

#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATCellManifoldGroup ;
#else
extern "C" const IID IID_CATCellManifoldGroup ;
#endif
class ExportedByCATGMModelInterfaces CATCellManifoldGroup : public CATManifold
{
  CATDeclareInterface;

public:
  // 
  virtual void GetLeaves(ListPOfCATCellManifold &oLeaves) const=0;
  virtual const ListPOfCATCellManifold & GetLeaves() const=0;
  virtual void GetSons(ListPOfCATCellManifoldGroup &oSons) const=0;
  virtual const ListPOfCATCellManifoldGroup * GetSons() const=0;
  virtual void GetAllLeaves(ListPOfCATCellManifold &oLeaves) const=0;

  // Layer
  virtual CATBoolean HasSameLayer(const CATCellManifoldGroupLayer* iCMGroupLayer) const=0;
  virtual CATBoolean HasSameLayer(const CATCellManifoldGroup* iOtherMGroup) const=0;
  
  // Representation
  virtual void GetRep(ListPOfCATCellManifold &oRep, CATListOfShort &oType) const=0;
  virtual void GetRep(const int iType, ListPOfCATCellManifold &oRep) const=0;

  // Context, available for contextual layer only
  virtual void GetContext(ListPOfCATCellManifold &oContext) const=0;
  virtual void GetContext(ListPOfCATCellManifold &oContext, CATListOfShort &oType) const=0;
  virtual void GetContext(const int iType, ListPOfCATCellManifold &oContext) const=0;

  // Manifold Attribute
  virtual void SetManifoldAttribute(CATManifoldAttribute *iAttribute)=0;
  virtual CATManifoldAttribute* GetManifoldAttribute() const=0;

  // Deprecated - Use GetCellManifoldRep()
  virtual void GetRep(ListPOfCATCellManifold &oRep) const=0;

};
  
CATDeclareHandler(CATCellManifoldGroup, CATManifold);

#endif
