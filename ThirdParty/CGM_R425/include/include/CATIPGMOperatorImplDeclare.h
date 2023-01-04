#include "CATIPGMVirtualImplDeclare.h"

  // ---------- CATCGMOperator

  virtual int Run();

  virtual CATGeoFactory *GetFactory() const;

  virtual const CATString *GetOperatorId();

  virtual void SetOperatorId(const CATString iOperatorName);

  virtual void EnableInterrupt(CATCGMInterruptFunction ipInterruptFunction);

  virtual CATSoftwareConfiguration *GetSoftwareConfiguration() const;

  virtual CATIPGMTopOperator *IsTopological();

  virtual void DefineFactory(CATGeoFactory *Factory);

  virtual CATULONG32 GetSessionIdentifier();

  virtual void SetWarningMode(CATCGMWarning iMode);

  virtual CATCGMWarning GetWarningMode() const;

  virtual void GetResultStatus(short &ioValidation, short &ioModifiable) const;

  virtual void SetResultStatus(const short iValidation, const short iModifiable);

  virtual short GetNumberOfReplay();

  virtual CATExtGeoOperator *GetExtensible(CATBoolean iRequired) const;

  virtual HRESULT DumpObjects(
    const unsigned int iOptions,
    CATechAttribute *iOutput,
    CATechSet *iJournaling);

