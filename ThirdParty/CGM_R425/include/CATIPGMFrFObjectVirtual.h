#ifndef CATIPGMFrFObjectVirtual_h_
#define CATIPGMFrFObjectVirtual_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMVirtual.h"
#include "CATDataType.h"

class CATSoftwareConfiguration;
class CATGeoFactory;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMFrFObjectVirtual;

class ExportedByCATGMOperatorsInterfaces CATIPGMFrFObjectVirtual: public CATIPGMVirtual
{
public:
  /**
   * Constructor
   */
  CATIPGMFrFObjectVirtual();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMFrFObjectVirtual(); // -> delete can't be called
};

#endif /* CATIPGMFrFObjectVirtual_h_ */
