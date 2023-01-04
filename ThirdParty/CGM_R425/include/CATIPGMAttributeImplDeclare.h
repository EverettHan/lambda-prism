#include "CATIPGMVirtualImplDeclare.h"

  // ---------- CATCGMAttribute

  virtual int IsPersistent();

  virtual const CATCGMAttrId *GetCGMAttrId() const;

  virtual int IsATypeOf(const CATCGMAttrId *iId);

  virtual CATULONG32 AddAttrRef();

  virtual CATULONG32 ReleaseAttrRef();

  virtual CATULONG32 GetNbAttrRef() const;

  virtual void Dump(CATCGMOutput &os);

  virtual short IsDirty();

  virtual const CATCGMAttributeDef *GetAttributeDef() const;

  virtual void PutObject(CATICGMObject *iToPoint);

