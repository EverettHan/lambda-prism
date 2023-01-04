#ifndef CATInstancesManifoldAttribute_h
#define CATInstancesManifoldAttribute_h

// COPYRIGHT DASSAULT SYSTEMES  2013
// VB7

#include "CATCGMNewArray.h"
#include "CATMathInline.h"
#include "CATManifoldGroupAttribute.h"
#include "CATPersistentCell.h"

class CATManifoldAttribute;

class ExportedByPersistentCell CATInstancesManifoldAttribute : public CATManifoldGroupAttribute
{
public:
  CATCGMDeclareAttribute (CATInstancesManifoldAttribute,CATManifoldAttribute);

  CATInstancesManifoldAttribute(); // Default constructor is mandatory
  CATInstancesManifoldAttribute(short iInstanceNumber);
  virtual ~CATInstancesManifoldAttribute();
  CATCGMNewClassArrayDeclare;      // Pool allocation

  INLINE CATInstancesManifoldAttribute *GetAsInstancesManifoldAttribute();

  INLINE short GetInstanceNumber();

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
  short _InstanceNumber;

};

INLINE short CATInstancesManifoldAttribute::GetInstanceNumber()
{
  return _InstanceNumber;
}

INLINE CATInstancesManifoldAttribute *CATInstancesManifoldAttribute::GetAsInstancesManifoldAttribute() {
  return this; }
#endif

