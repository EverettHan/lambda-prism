#ifndef CATIPGMTriTangentPCrv_h_
#define CATIPGMTriTangentPCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"

class CATCircle;
class CATCrvLimits;
class CATCrvParam;
class CATGeoFactory;
class CATPCircle;
class CATPCurve;
class CATPointOnCurve;
class CATPointOnSurface;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTriTangentPCrv;

class ExportedByCATGMModelInterfaces CATIPGMTriTangentPCrv: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTriTangentPCrv();

  //-----------------------------------------------------------------------
  //- Public Interface Methods
  //-----------------------------------------------------------------------
  // Setting Limits
  virtual void SetLimits(
    const CATPCurve *PCurve,
    const CATCrvLimits &CurveLimits) = 0;

  // Setting RadiusDomain
  virtual void SetRadiusDomain(double iMinRadius, double iMaxRadius) = 0;

  // Running the operator
  virtual int Run() = 0;

  // Number of solutions
  virtual CATLONG32 GetNumberOfPCircles() const = 0;

  // Iterators
  virtual void BeginningPCircle() = 0;

  virtual CATBoolean NextPCircle() = 0;

  // Methods which can be used after each NextPCircle () call
  virtual CATPointOnCurve *GetPointOnPCurve(const CATPCurve *PCurve) const = 0;

  virtual void GetCrvParam(const CATPCurve *iPCurve, CATCrvParam &oParam) const = 0;

  virtual CATPCircle *GetPCircle() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTriTangentPCrv(); // -> delete can't be called
};

#endif /* CATIPGMTriTangentPCrv_h_ */
