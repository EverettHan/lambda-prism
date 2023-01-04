#ifndef CATIPGMSurfaceToCanonic_h_
#define CATIPGMSurfaceToCanonic_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include "CATCollec.h"
#include "CATIsoParameter.h"
#include "CATSkillValue.h"

class CATCrvParam;
class CATCurve;
class CATGeoFactory;
class CATMathDirection;
class CATMathPlane;
class CATMathPoint;
class CATMathTransformation2D;
class CATMathVector;
class CATPoint;
class CATSoftwareConfiguration;
class CATSurface;
class CATSurLimits;
class CATLISTP(CATSurLimits);

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMSurfaceToCanonic;

class ExportedByCATGMModelInterfaces CATIPGMSurfaceToCanonic: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMSurfaceToCanonic();

  //-----------------------------------------------------------------------
  //- Settings
  //-----------------------------------------------------------------------
  // Take into account the given limits on the surface.
  // The default value is the max limits of the surface.
  virtual void SetLimits(CATSurLimits &iLimits) = 0;

  virtual void SetListOfLimits(CATLISTP(CATSurLimits) &iLimits) = 0;

  //-----------------------------------------------------------------------
  //- Options for the classical way of detection
  //-----------------------------------------------------------------------
  // Find the canonic surface only if a bilinear mapping is defined between the
  // original surface and the canonical surface (default value : no bilinear 
  // mapping is required).
  virtual void SetBilinearMapping() = 0;

  // Find the canonic surface (cylinder) when the original surface is a 
  // revolution surface(nurbs).
  virtual void SetCylinderRecognition() = 0;

  //-----------------------------------------------------------------------
  //- Options for the most up to date way of detection
  //-----------------------------------------------------------------------
  // These methods activate GeometricDetection mode, which is the most up to date.
  // They are NOT supposed to be used with SetBilinearMapping and SetCylinderRecognition.
  // You can combine them to activate several detection algorithms.
  // They will search, taking the input tolerance into account, if the input surface is ... :
  // ...a cylinder modulo a bilinear mapping on the parametrization :
  virtual void SearchIsoCylinder() = 0;

  // ...a cone modulo a bilinear mapping on the parametrization :
  virtual void SearchIsoCone() = 0;

  // ...a plane modulo a bilinear mapping on the parametrization :
  virtual void SearchIsoPlane() = 0;

  // ...a sphere modulo a bilinear mapping on the parametrization :
  // (only on RevolutionSurface for the moment)
  virtual void SearchIsoSphere() = 0;

  // ...a plane even if there is no mapping between the parametrizations :
  virtual void SearchPlane() = 0;

  // ...a cylinder with no mapping between the parametrizations :
  // (only on GenericFillet for the moment)
  virtual void SearchNoIsoCylinder() = 0;

  // ...a tore with no mapping between the parametrizations :
  // (only on GenericFillet for the moment)
  virtual void SearchNoIsoTore() = 0;

  // ...a cylinder even if there is no mapping between the parametrizations :
  virtual void SearchCylinder() = 0;

  // ...a Torus even if there is no mapping between the parametrizations :
  virtual void SearchTorus() = 0;

  //-----------------------------------------------------------------------
  //- Get result
  //-----------------------------------------------------------------------
  // Returns canonical equivalent surface (or return 0 if no canonical equivalent
  // surface has been found), together with the surface limits.
  virtual CATSurface *GetSurface(CATSurLimits &oLimits) = 0;

  // Retrieve the bilinear mapping between the original surface and the canonical
  // surface. (Ucan, Vcan) = oMappingUV * (uSurf, vSurf). The return value is true
  // if a mapping is found.
  virtual CATBoolean GetBilinearMappingToCanonic(CATMathTransformation2D &oMappingUV) = 0;

  //-----------------------------------------------------------------------
  //- Miscellanous Services
  //-----------------------------------------------------------------------
  // Do not use. Use GetRuleDirection service
  // Static method designed to check if the input surface is a ruled surface,
  // modulo a tolerance and a bilinear mapping on the parametrization.
  //Inputs:
  //iSurface : the input surface
  //iSurLimits: Surface portion which needs to be checked
  //iTolerance: tolerance for geometric check
  //Output = CATIsoParNoDir if the surface portion is not ruled
  //       = CATIsoParamU if the surface portion is ruled in V (iso-U) direction
  //       = CATIsoParamV if the surface portion is ruled in U (iso-V) direction
  //       = CATIsoParBothDir if the surface portion is ruled in both U & V directions
  static CATIsoParameter IsRuledSurface(
    const CATSurface *iSurface,
    const CATSurLimits &iSurLimits,
    double iTolerance);

  // Start : SUH : 2004:2:9
  // Returns whether the input surface to the operator is a ruled surface.
  // Expect useful return value ONLY if SearchRuleDirection(int) is called with a non-zero argument.
  // One can specify the tolerance for geometric check at operator creation and limits of surface to examine via SetLimits.
  // To be used after operator Run
  // Output = CATIsoParNoDir if the surface portion is not ruled
  //        = CATIsoParamU if the surface portion is ruled in V (iso-U) direction
  //        = CATIsoParamV if the surface portion is ruled in U (iso-V) direction
  //        = CATIsoParBothDir if the surface portion is ruled in both U & V directions
  virtual CATIsoParameter GetRuleDirection() = 0;

  // To set if information about Rule Direction of input surface is required
  // Input:
  // iRuleDirOption = 0  => No search for Rule Direction of input surface is made.
  // iRuleDirOption = 1  => Search for Rule Direction. To get it, use GetRuleDirection().
  // iRuleDirOption = 2  => NO CANONIC RESULT is computed, only search for Rule Direction is made. To get it, use GetRuleDirection().
  // Output = 1 if successful
  //        = 0 otherwise
  // 
  virtual int SearchRuleDirection(int iRuleDirOption = 1) = 0;

  // End : SUH : 2004:2:9
  // For debug only : Checks the result.
  // Return values are 1 in case of success, 0 otherwise.
  // Also returns the maximum computed gap.
  virtual CATLONG32 CheckResult(double &maxgap) = 0;

  // For debug only : Checks the result.
  // Return values are 1 in case of success, 0 otherwise.
  // Print traces to cgmout.
  virtual CATLONG32 CheckResult() = 0;

  virtual CATSoftwareConfiguration *GetSoftwareConfiguration() const = 0;

  //-----------------------------------------------------------------------
  //- Gestion timer 
  //-----------------------------------------------------------------------  
  virtual CATGeoOpTimer *GetTimer() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSurfaceToCanonic(); // -> delete can't be called
};

//
// Create and remove 
//
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMSurfaceToCanonic *CATPGMCreateSurfaceToCanonic(
  CATGeoFactory *iFactory,
  CATSurface *iSurface,
  double iTolApprox,
  CATSkillValue iMode = BASIC);

#endif /* CATIPGMSurfaceToCanonic_h_ */
