#ifndef CATBRepCopyManifoldAttribute_h
#define CATBRepCopyManifoldAttribute_h

// COPYRIGHT DASSAULT SYSTEMES  2013

#include "CATCGMNewArray.h"
#include "CATManifoldAttribute.h"
#include "CATPersistentCell.h"
class CATCloneManager;
class CATTransfoManager;

class ExportedByPersistentCell CATBRepCopyManifoldAttribute : public CATManifoldAttribute
{
public:
  CATCGMDeclareAttribute (CATBRepCopyManifoldAttribute,CATManifoldAttribute);

  CATBRepCopyManifoldAttribute();
  virtual ~CATBRepCopyManifoldAttribute();
  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual CATManifoldAttribute* CreateImageManifoldAttribute(CATLiveBody &iLiveBody, CATLISTP(CATManifoldAttribute) &iParentManifoldAttributes) const;
  virtual CATManifoldAttribute* Clone(CATCloneManager& iCloneManager) const;
  virtual void Move3D(CATTransfoManager& iTransfoManager);
  virtual void GetColor(int &oR, int &oG, int &oB) const;

  virtual CATBRepCopyManifoldAttribute* GetAsBRepCopyManifoldAttribute();
  virtual CATBoolean HaveSameType(CATManifoldAttribute &iOtherManifoldAttribute)const;

  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream);
};

#endif

