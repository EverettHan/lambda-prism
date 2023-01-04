#include "CATIPGMAttributeImplDeclare.h"

  // ---------- CATCGMStreamAttribute

  virtual void Stream(CATCGMStream &ioStream) const;

  virtual void UnStream(CATCGMStream &ioStr);

  virtual void AddLink(CATICGMObject *iObject);

  virtual void RemoveLink(CATICGMObject *iObject);

  virtual void SetLinks(const CATLISTP(CATICGMObject) &iObjects);

  virtual void GetLinks(CATLISTP(CATICGMObject) &ioLinkedObjects);

  virtual CATBoolean IsStreamable(
    const CATCGMStreamVersion iTargetVersion,
    CATBoolean &ioReversible) const;

  virtual void SetMustStreamForStreamCompact(int iMustStreamForStreamCompact);

  virtual int MustStreamForStreamCompact() const;

