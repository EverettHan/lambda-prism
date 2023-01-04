#ifndef CATIPGMExtractTangentAlongDir_h_
#define CATIPGMExtractTangentAlongDir_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"

class CATCrvLimits;
class CATCurve;
class CATGeoFactory;
class CATMathDirection;
class CATPointOnCurve;
class CATPointOnSurface;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMExtractTangentAlongDir;

class ExportedByCATGMModelInterfaces CATIPGMExtractTangentAlongDir: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMExtractTangentAlongDir();

  //-----------------------------------------------------------------------
  //- Public Interface Methods
  //-----------------------------------------------------------------------
  // Setting methods
  virtual void SetCurve(const CATCurve *iCurve) = 0;

  virtual void SetLimits(
    const CATPointOnCurve *iStartPoc,
    const CATPointOnCurve *iEndPoc) = 0;

  virtual void SetDirection(const CATMathDirection &iDirection) = 0;

  virtual void SetAngularTol(const double iAngleInRadians) = 0;

  // Running the operator
  virtual int Run() = 0;

  // Number of solutions
  virtual CATLONG32 GetNumberOfPoints() const = 0;

  virtual CATLONG32 GetNumberOfCurves() const = 0;

  // Read the Point solutions
  virtual void BeginningPoint() = 0;

  virtual CATBoolean NextPoint() = 0;

  virtual CATPointOnCurve *GetPointOnCurve() const = 0;

  // Read the Part of the Curve solutions
  virtual void BeginningCurve() = 0;

  virtual CATBoolean NextCurve() = 0;

  virtual void GetPartOfCurves(CATCrvLimits &oLimits) const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMExtractTangentAlongDir(); // -> delete can't be called
};

#endif /* CATIPGMExtractTangentAlongDir_h_ */
