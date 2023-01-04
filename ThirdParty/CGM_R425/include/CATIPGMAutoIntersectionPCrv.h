#ifndef CATIPGMAutoIntersectionPCrv_h_
#define CATIPGMAutoIntersectionPCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"

class CATMathSetOfPointsND;
class CATPCurve;
class CATCrvLimits;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMAutoIntersectionPCrv;

class ExportedByCATGMModelInterfaces CATIPGMAutoIntersectionPCrv: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMAutoIntersectionPCrv();

  // Set a maximum number of solutions to be found
  // We stop looking for solutions as soon as we have obtained iMaximumNumSolutions solutions.
  // We might obtain more solutions because the solver can return multiple solutions.
  virtual void SetMaximumNumSolutions(CATLONG32 iMaximumNumSolutions) = 0;

  //========================================================================
  // Management of Solutions
  //========================================================================
  virtual CATLONG32 GetNumberOfCuttingLimits() = 0;

  virtual void BeginningCutout() = 0;

  virtual CATBoolean NextCuttingLimits() = 0;

  virtual void GetCuttingLimits(CATCrvLimits &ioCrvLimits) = 0;

  virtual CATLONG32 GetNumberOfSelfIntersection() = 0;

  virtual void BeginningSelfIntersection() = 0;

  virtual CATLONG32 NextSelfIntersection() = 0;

  virtual void GetSelfIntersection(double *ioSelfIntersectionParam) = 0;

  //-----------------------------------------------------------------------
  //- Gestion timer 
  //-----------------------------------------------------------------------  
  virtual CATGeoOpTimer *GetTimer() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMAutoIntersectionPCrv(); // -> delete can't be called
};

//Do not use
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMAutoIntersectionPCrv *CATPGMCreateAutoIntersectionPCrv(
  CATGeoFactory *iFactory,
  CATPCurve *iPCrv,
  CATCrvLimits &iCrvLimits);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMAutoIntersectionPCrv *CATPGMCreateAutoIntersectionPCrv(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATPCurve *iPCrv,
  CATCrvLimits &iCrvLimits);

#endif /* CATIPGMAutoIntersectionPCrv_h_ */
