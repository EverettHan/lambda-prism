#ifndef CATPGMTopologicalDeviation_h_
#define CATPGMTopologicalDeviation_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "CATGMOperatorsInterfaces.h"

class CATMathPoint;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATPGMTopologicalDeviation
{
public:
  /**
   * Constructor
   */
  CATPGMTopologicalDeviation();

  /**
   * Destructor
   */
  virtual ~CATPGMTopologicalDeviation();

  //
  //  Run : Compute Results
  //
  virtual void Run() = 0;

  //
  //  GetDistance
  //
  virtual double GetDeviation() = 0;

  //
  //  SetThreshold
  //
  virtual void SetThreshold(double &iThreshold) = 0;

  //
  //  GetPointLocation
  //
  virtual void GetPointLocation(CATMathPoint &oPtB1, CATMathPoint &oPtB2) = 0;

};

#endif /* CATPGMTopologicalDeviation_h_ */
