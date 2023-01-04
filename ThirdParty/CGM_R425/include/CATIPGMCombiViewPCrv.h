#ifndef CATIPGMCombiViewPCrv_h_
#define CATIPGMCombiViewPCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"
#include "CATSkillValue.h"

class CATCurve;
class CATGeoFactory;
class CATGeometry;
class CATPCurve;
class CATPlane;
class CATPoint;
class CATPointOnSurface;
class CATSoftwareConfiguration;
class CATSurface;
class CATCrvLimits;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMCombiViewPCrv;

class ExportedByCATGMModelInterfaces CATIPGMCombiViewPCrv: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMCombiViewPCrv();

  //-----------------------------------------------------------------------
  //- Set methods
  //-----------------------------------------------------------------------
  // When an input geometry is a pcurve, SetLimits permits to associate a given
  // limits on this PCurve (default is the currentlimits on the pcurve)
  virtual void SetLimits(CATPCurve *iPCrv, const CATCrvLimits &iLimits) = 0;

  //-----------------------------------------------------------------------
  //- Get methods
  //-----------------------------------------------------------------------
  virtual CATLONG32 GetNumberOfCurves() = 0;

  virtual void BeginningCurve() = 0;

  virtual CATBoolean NextCurve() = 0;

  // The result PCurve lies on iResultSupport and is as canonic as possible
  virtual CATPCurve *GetPCurve(CATCrvLimits &oLimits) = 0;

  //CATPCurve * GetPCurve();
  virtual CATLONG32 GetNumberOfPoints() = 0;

  virtual void BeginningPoint() = 0;

  virtual CATBoolean NextPoint() = 0;

  virtual CATPointOnSurface *GetPoint() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMCombiViewPCrv(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMCombiViewPCrv *CATPGMCreateCombiViewPCrv(
  CATGeoFactory *iFactory,
  CATGeometry *iGeometry1,
  CATGeometry *iGeometry2,
  CATPlane *iSupport1,
  CATPlane *iSupport2,
  CATPlane *iResultSupport,
  CATSkillValue iMode = BASIC);

#endif /* CATIPGMCombiViewPCrv_h_ */
