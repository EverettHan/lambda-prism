#ifndef CATIPGMFrFObject_h_
#define CATIPGMFrFObject_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMFrFObjectVirtual.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATTolerance;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMFrFObject;

class ExportedByCATGMOperatorsInterfaces CATIPGMFrFObject: public CATIPGMFrFObjectVirtual
{
public:
  /**
   * Constructor
   */
  CATIPGMFrFObject();

  virtual CATSoftwareConfiguration *GetSoftwareConfiguration() const = 0;

  virtual void SetSoftwareConfiguration(CATSoftwareConfiguration *iConfig) = 0;

  // Ici la configuration ne doit etre appliquee que si elle contient un niveau CGM superieur ou egal a FirstLevelToSet
  virtual void SetSoftwareConfiguration(
    CATSoftwareConfiguration *iConfig,
    int FirstLevelToSet) = 0;

  virtual void SetFactory(CATGeoFactory *iFactory) = 0;

  virtual CATLONG32 GetCGMLevel() const = 0;

  virtual CATGeoFactory *GetFactory(int iNoErrorIfNullFactory = 0) const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMFrFObject(); // -> delete can't be called
};

#endif /* CATIPGMFrFObject_h_ */
