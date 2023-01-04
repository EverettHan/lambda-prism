#ifndef CATIPGMWireIntersectionChecker_h_
#define CATIPGMWireIntersectionChecker_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMIntersectionChecker.h"

class CATCXWireIntersectionChecker;
class CATSurface;
class CATWire;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMWireIntersectionChecker;

class ExportedByCATGMModelInterfaces CATIPGMWireIntersectionChecker: public CATIPGMIntersectionChecker
{
public:
  /**
   * Constructor
   */
  CATIPGMWireIntersectionChecker();

  //======================================
  // Methodes specifiques a CATIPGMTopOperator
  //======================================
  //====================================
  // Parametrisation de l'operateur
  //====================================
  virtual void SetWiresToCheck(CATWire *iWire1, CATWire *iWire2 = (CATWire*)0) = 0;

  virtual void SetSurface(CATSurface *iSurface) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMWireIntersectionChecker(); // -> delete can't be called
};

#endif /* CATIPGMWireIntersectionChecker_h_ */
