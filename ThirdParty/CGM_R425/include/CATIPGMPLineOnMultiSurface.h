#ifndef CATIPGMPLineOnMultiSurface_h_
#define CATIPGMPLineOnMultiSurface_h_

// COPYRIGHT DASSAULT SYSTEMES 2013

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include "CATBoolean.h"
#include "CATMathPoint.h"
#include "CATCollec.h"

class CATMultiSurface;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATMathPoint2D;
class CATLISTP(CATPCurve);

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMPLineOnMultiSurface;

class ExportedByCATGMModelInterfaces CATIPGMPLineOnMultiSurface: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMPLineOnMultiSurface();

  /**
  * @nodoc
  * Creates the  solution curve of <tt>this</tt> CATIPGMPLineOnMultiSurface operator.
  */
  virtual void GetResults(CATLISTP(CATPCurve) *ioListOfPlines) = 0;

  /**
  * @nodoc
  * Force Border Options
  * By default it is not set 
  */
  virtual void SetForceBorderOption(CATBoolean iOption) = 0;

  /**
  * @nodoc
  * 3D Boudaries Options
  */
  virtual void Set3DBoundaries(CATMathPoint & iStart3D, CATMathPoint & iEnd3D) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMPLineOnMultiSurface(); // -> delete can't be called
};

/**
 * @nodoc
 * Create CATIPGMPLineOnMultiSurface Operator
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMPLineOnMultiSurface *CATPGMCreatePLineOnMultiSurface(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  CATMultiSurface *iSurface,
  CATMathPoint2D &iStart,
  CATMathPoint2D &iEnd);

#endif /* CATIPGMPLineOnMultiSurface_h_ */
