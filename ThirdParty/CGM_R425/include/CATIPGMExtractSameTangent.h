#ifndef CATIPGMExtractSameTangent_h_
#define CATIPGMExtractSameTangent_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"

class CATCartesianPoint;
class CATCrvLimits;
class CATCrvParam;
class CATPointOnCurve;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMExtractSameTangent;

class ExportedByCATGMModelInterfaces CATIPGMExtractSameTangent: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMExtractSameTangent();

  //-----------------------------------------------------------------------
  //- Public Interface Methods
  //-----------------------------------------------------------------------
  virtual CATLONG32 GetNumberOfPoints() const = 0;

  virtual void BeginningPoint() = 0;

  virtual CATBoolean NextPoint() = 0;

  virtual CATCrvParam GetCrvParam() const = 0;

  virtual CATPointOnCurve *GetPointOnCurve() const = 0;

  virtual CATCartesianPoint *GetCartesianPoint() const = 0;

  virtual void SetLimits(const CATCrvLimits& iLimits) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMExtractSameTangent(); // -> delete can't be called
};

#endif /* CATIPGMExtractSameTangent_h_ */
