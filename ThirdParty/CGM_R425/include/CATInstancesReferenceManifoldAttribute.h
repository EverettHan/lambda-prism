#ifndef CATInstancesReferenceManifoldAttribute_h
#define CATInstancesReferenceManifoldAttribute_h

// COPYRIGHT DASSAULT SYSTEMES  2013
// VB7

#include "CATCGMNewArray.h"
#include "CATPersistentCell.h"
#include "CATManifoldGroupAttribute.h"

class CATCellManifold;

class ExportedByPersistentCell CATInstancesReferenceManifoldAttribute : public CATManifoldGroupAttribute
{
public:
  CATCGMDeclareAttribute (CATInstancesReferenceManifoldAttribute,CATManifoldAttribute);

  CATInstancesReferenceManifoldAttribute(); // Default constructor is mandatory
  CATInstancesReferenceManifoldAttribute(CATCellManifold * iReferenceCellManifold);
  virtual ~CATInstancesReferenceManifoldAttribute();
  CATCGMNewClassArrayDeclare;      // Pool allocation
  
  INLINE CATInstancesReferenceManifoldAttribute *GetAsInstancesReferenceManifoldAttribute();

  virtual CATManifoldAttribute* CreateImageManifoldAttribute(CATLiveBody &iLiveBody, CATLISTP(CATManifoldAttribute) &iParentManifoldAttributes ) const;
  virtual CATManifoldAttribute* Clone(CATCloneManager& iCloneManager) const;
  virtual void Move3D(CATTransfoManager& iTransfoManager);
  virtual void GetColor(int &oR, int &oG, int &oB) const;
  virtual HRESULT GenerateParameters (CATTopData * iTopData, CATCellManifoldGroupCGM * iGroup, ListPOfCATManifoldParameter &oManifoldParameters) const;
  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream);
  virtual void Dump(CATCGMOutput& iWhereToWrite) const; 

protected:

private:
};

INLINE CATInstancesReferenceManifoldAttribute *CATInstancesReferenceManifoldAttribute::GetAsInstancesReferenceManifoldAttribute() {
  return this; }

#endif

