#ifndef CATIPGMVirtual_h
#define CATIPGMVirtual_h

#include "CATMathematics.h"
#include "CATCGMVirtualItf.h"

extern ExportedByCATMathematics IID IID_CATIPGMVirtual;

/**
 * Protected CGM interface root class.
 */
class ExportedByCATMathematics CATIPGMVirtual: public CATCGMVirtualItf
{
public:
  /**
   * Constructor
   */
  CATIPGMVirtual();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMVirtual();

private:
  CATIPGMVirtual(const CATIPGMVirtual &iObject); // Prohibited
  CATIPGMVirtual &operator=(const CATIPGMVirtual &iObject); // Prohibited
};

#endif
