#ifndef CATIPGMSurfaceClosure_h_
#define CATIPGMSurfaceClosure_h_

// COPYRIGHT DASSAULT SYSTEMES 2013

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"
#include "CATIsoParameter.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATSurParamReport;
class CATSurface;
class CATSurLimits;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMSurfaceClosure;

class ExportedByCATGMModelInterfaces CATIPGMSurfaceClosure: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMSurfaceClosure();

  //-----------------------------------------------------------------------
  //- Settings methods
  //-----------------------------------------------------------------------
  // Default is current limits
  virtual void SetLimits(const CATSurLimits &iLimits) = 0;

  // No default
  virtual void SetIsoparType(const CATIsoParameter iIsoType) = 0;

  //-----------------------------------------------------------------------
  //- Get methods
  //-----------------------------------------------------------------------
  virtual CATBoolean IsClosedG0() = 0;

  virtual CATBoolean IsClosedG1() = 0;

  //  CATBoolean IsClosedG2(); Not yet implemented
  // Return an object which permits to report surface parameter between one isopar of
  // the close and the other.
  // WARNING : the returned pointer is owned by the caller and must be deleted by the caller.
  // Note (Implicit specification) :
  // the returned CATSurParamReport has direct report from isopar min to isopar max.
  virtual CATSurParamReport *GetParamReport() = 0;

  //-----------------------------------------------------------------------
  //- Running the operator
  //-----------------------------------------------------------------------
  virtual int Run() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSurfaceClosure(); // -> delete can't be called
};

/**
 * return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMSurfaceClosure *CATPGMCreateSurfaceClosure(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurface);

#endif /* CATIPGMSurfaceClosure_h_ */
