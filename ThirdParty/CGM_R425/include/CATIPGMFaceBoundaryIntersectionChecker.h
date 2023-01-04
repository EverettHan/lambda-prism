#ifndef CATIPGMFaceBoundaryIntersectionChecker_h_
#define CATIPGMFaceBoundaryIntersectionChecker_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMIntersectionChecker.h"

class CATCXFaceBoundaryIntersectionChecker;
class CATFace;
class CATGeoFactory;
class CATShell;
class CATTopData;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMFaceBoundaryIntersectionChecker;

class ExportedByCATGMModelInterfaces CATIPGMFaceBoundaryIntersectionChecker: public CATIPGMIntersectionChecker
{
public:
  /**
   * Constructor
   */
  CATIPGMFaceBoundaryIntersectionChecker();

  //======================================
  // Methodes specifiques a CATIPGMTopOperator
  //======================================
  //====================================
  // Parametrisation de l'operateur
  //====================================
  virtual void SetFaceToCheck(CATFace *iFaceToCheck) = 0;

  virtual void SetShellToCheck(CATShell *iShellToCheck) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMFaceBoundaryIntersectionChecker(); // -> delete can't be called
};

#endif /* CATIPGMFaceBoundaryIntersectionChecker_h_ */
