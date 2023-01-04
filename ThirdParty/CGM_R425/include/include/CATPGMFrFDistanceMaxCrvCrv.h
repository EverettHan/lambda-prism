#ifndef CATPGMFrFDistanceMaxCrvCrv_h_
#define CATPGMFrFDistanceMaxCrvCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATCGMVirtual.h"
#include "CATSkillValue.h"

class CATCrvLimits;
class CATCurve;
class CATFrFCheckGeometricContinuity;
class CATGeoFactory;
class CATSoftwareConfiguration;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATPGMFrFDistanceMaxCrvCrv: public CATCGMVirtual
{
public:
  /**
   * Constructor
   */
  CATPGMFrFDistanceMaxCrvCrv();

  /**
   * Destructor
   */
  virtual ~CATPGMFrFDistanceMaxCrvCrv();

  //------------------- Data Access Methods -------------------  
  // Recuperation de la distance max ; la methode Run doit avoir ete appelee
  // auparavent ou le createur doit avoir ete appele avec iMode = BASIC.
  virtual double GetMaxDistance() const = 0;

  // impose les courbes et leur crvlimits
  virtual void SetCurveRef(const CATCurve *CRef, const CATCrvLimits &CLRef) = 0;

  virtual void SetCurveTwo(const CATCurve *C2, const CATCrvLimits &CL2) = 0;

  // Impose le nombre de points discretises ou se feront les tests 
  // de continuite (10 par defaut).
  virtual void SetNbOfDiscretizedPoints(int NbOfDiscretizedPoints) = 0;

  //------------------- Compute Methods -------------------  
  virtual int  Run() = 0; // NLD170622  virtual void Run() = 0;
};

//  constructors
ExportedByCATGMOperatorsInterfaces CATPGMFrFDistanceMaxCrvCrv *CATPGMCreateFrFDistanceMaxCrvCrv(
  CATGeoFactory *iFactory,
  const CATCurve *CRef,
  const CATCurve *C2,
  const CATCrvLimits &CLRef,
  const CATCrvLimits &CL2,
  const CATSkillValue &iMode = BASIC,
  CATSoftwareConfiguration *iSoftwareConfiguration = NULL);

#endif /* CATPGMFrFDistanceMaxCrvCrv_h_ */
