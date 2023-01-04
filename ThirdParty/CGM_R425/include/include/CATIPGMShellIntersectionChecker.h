#ifndef CATIPGMShellIntersectionChecker_h_
#define CATIPGMShellIntersectionChecker_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMIntersectionChecker.h"

class CATCXShellIntersectionChecker;
class CATGeoFactory;
class CATLISTP_CATFace_;
class CATShell;
class CATTopData;
class CATVolume;
class CATLISTP(CATFace);

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMShellIntersectionChecker;

class ExportedByCATGMModelInterfaces CATIPGMShellIntersectionChecker: public CATIPGMIntersectionChecker
{
public:
  /**
   * Constructor
   */
  CATIPGMShellIntersectionChecker();

  //======================================
  // Methodes specifiques a CATIPGMTopOperator
  //======================================
  //====================================
  // Parametrisation de l'operateur
  //====================================
  virtual void SetShellsToCheck(CATShell *iShell1, CATShell *iShell2 = (CATShell*)0) = 0;

  virtual void SetVolumeToCheck(CATVolume *iVolumeToCheck) = 0;

  virtual void SetListOfRestrictedFaces(CATLISTP(CATFace) &iSetOfRestrictedFaces) = 0;

  virtual void SetOnlyDisjoinFaces(CATBoolean iOnlyDisjoinFaces) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMShellIntersectionChecker(); // -> delete can't be called
};

#endif /* CATIPGMShellIntersectionChecker_h_ */
