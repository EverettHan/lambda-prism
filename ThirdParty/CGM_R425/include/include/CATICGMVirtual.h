#ifndef CATICGMVirtual_h
#define CATICGMVirtual_h

#include "CATMathematics.h"
#include "CATCGMVirtualItf.h"

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

extern ExportedByCATMathematics IID IID_CATICGMVirtual;

/**
 * Public CGM interface root class.
 */
class ExportedByCATMathematics CATICGMVirtual: public CATCGMVirtualItf
{
public:
  /**
   * Constructor
   */
  CATICGMVirtual();

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMVirtual();

private:
  CATICGMVirtual(const CATICGMVirtual &iObject); // Prohibited
  CATICGMVirtual &operator=(const CATICGMVirtual &iObject); // Prohibited
};

#endif
