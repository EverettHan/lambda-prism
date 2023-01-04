#ifndef CATIPGMWirePolyline_h_
#define CATIPGMWirePolyline_h_

// COPYRIGHT DASSAULT SYSTEMES 2008

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMSolidPrimitive.h"

class CATMathPoint;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMWirePolyline;

class ExportedByCATGMOperatorsInterfaces CATIPGMWirePolyline: public CATIPGMSolidPrimitive
{
public:
  /**
   * Constructor
   */
  CATIPGMWirePolyline();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMWirePolyline(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMWirePolyline *CATPGMCreateWirePolyline(
  CATGeoFactory *iFactory,
  const int numberOfPoints,
  CATMathPoint **points,
  CATCGMJournalList *iReport = NULL);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMWirePolyline *CATPGMCreateWirePolyline(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  const int numberOfPoints,
  CATMathPoint **points);

#endif /* CATIPGMWirePolyline_h_ */
