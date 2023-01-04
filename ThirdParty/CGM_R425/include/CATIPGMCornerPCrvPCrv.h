#ifndef CATIPGMCornerPCrvPCrv_h_
#define CATIPGMCornerPCrvPCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"

class CATCircle;
class CATCrvLimits;
class CATGeoFactory;
class CATPCircle;
class CATPCurve;
class CATPointOnCurve;
class CATPointOnSurface;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMCornerPCrvPCrv;

class ExportedByCATGMModelInterfaces CATIPGMCornerPCrvPCrv: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMCornerPCrvPCrv();

  //-----------------------------------------------------------------------
  //- Public Interface Methods
  //-----------------------------------------------------------------------
  // Running the operator
  virtual int Run() = 0;

  // Number of solutions
  virtual CATLONG32 GetNumberOfCorners() const = 0;

  // Iterators
  virtual void BeginningCorner() = 0;

  virtual CATBoolean NextCorner() = 0;

  // Methods which can be used after each NextCorner () call
  virtual CATPointOnCurve *GetPointOnPCurve(const CATPCurve *PCurve) const = 0;

  virtual CATPCircle *GetCircle() const = 0;

  virtual CATCircle *Get3DCircle() const = 0;

  // Methods to set limits on the PCurve(s)
  virtual void SetLimits(
    const CATPCurve *PCurve,
    const CATCrvLimits &CurveLimits) = 0;

  virtual void SetLimits2(
    const CATCrvLimits &CurveLimits1,
    const CATCrvLimits &CurveLimits2) = 0;

  // Confusion for intersection between the parallels.
  virtual CATBoolean GetConfusion() = 0;

  // Method to disable curve length check when creating the PCircle (corner in complete mode ONLY)   
  virtual void SetNoCurveLengthCheckForCompleteMode() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMCornerPCrvPCrv(); // -> delete can't be called
};

#endif /* CATIPGMCornerPCrvPCrv_h_ */
