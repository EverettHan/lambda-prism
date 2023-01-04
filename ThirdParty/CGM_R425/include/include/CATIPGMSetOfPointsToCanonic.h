#ifndef CATIPGMSetOfPointsToCanonic_h_
#define CATIPGMSetOfPointsToCanonic_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"
#include "CATGeometryType.h"
#include "CATSkillValue.h"

class CATCGMStream;
class CATGeoFactory;
class CATMathSetOfPoints;
class CATSoftwareConfiguration;
class CATSurLimits;
class CATSurface;
class CATMathPoint;
class CATMathVector;
class CATGeoOpTimer;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMSetOfPointsToCanonic;

class ExportedByCATGMModelInterfaces CATIPGMSetOfPointsToCanonic: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMSetOfPointsToCanonic();

  //
  // Returns canonical equivalent surface (or return 0 if no canonical equivalent
  // surface has been found), together with the surface limits.
  //
  virtual CATSurface *GetSurface(CATSurLimits &oLimits) = 0;

  virtual CATGeometricType IsCanonic() = 0;

  virtual void SetFormToRecognize(CATGeometricType iFormToRecognize) = 0;

  // 
  // Dans le cas ou on cherche un cylindre, cette methode permet de 
  // donner une init 
  // iCenter = point sur l'axe du cylindre
  // iDir = direction normalisee de l'axe du cylindre
  // Radius = rayon du cylindre
  //	
  virtual void SetInitialCylinder(
    CATMathPoint &iCenter,
    CATMathVector &iDir,
    double iRadius) = 0;

  // 
  // Dans le cas ou on cherche un cone, cette methode permet de 
  // donner une init 
  // iApex = sommet du cone (apex)
  // iDir = direction normalisee de l'axe du cone
  // iAngle = demi angle au sommet (radian)
  //
  virtual void SetInitialCone(CATMathPoint &iApex, CATMathVector &iDir, double iAngle) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSetOfPointsToCanonic(); // -> delete can't be called
};

//
// Create and remove 
//
// Deprecated create methods ...Use the one with SoftwareConfiguration 
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMSetOfPointsToCanonic *CATPGMCreateSetOfPointsToCanonic(
  CATGeoFactory *iFactory,
  CATMathSetOfPoints *iSetOfPoints,
  double iTolApprox,
  CATGeometricType iFormToRecognize = CATGeometryType,
  CATSkillValue iMode = BASIC);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMSetOfPointsToCanonic *CATPGMCreateSetOfPointsToCanonic(
  CATGeoFactory *iFactory,
  CATMathPoint *iSetOfPoints,
  CATLONG32 NbPoints,
  double iTolApprox,
  CATGeometricType iFormToRecognize = CATGeometryType,
  CATSkillValue iMode = BASIC);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMSetOfPointsToCanonic *CATPGMCreateSetOfPointsToCanonic(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATMathSetOfPoints *iSetOfPoints,
  double iTolApprox,
  CATGeometricType iFormToRecognize = CATGeometryType,
  CATSkillValue iMode = BASIC);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMSetOfPointsToCanonic *CATPGMCreateSetOfPointsToCanonic(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATMathPoint *iSetOfPoints,
  CATLONG32 NbPoints,
  double iTolApprox,
  CATGeometricType iFormToRecognize = CATGeometryType,
  CATSkillValue iMode = BASIC);

#endif /* CATIPGMSetOfPointsToCanonic_h_ */
