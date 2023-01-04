#ifndef CATIPGMTopThickWire_h_
#define CATIPGMTopThickWire_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopThickWire;

// COPYRIGHT DASSAULT SYSTEMES  1999
//
class ExportedByCATGMOperatorsInterfaces CATIPGMTopThickWire: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopThickWire();

  /*
* BASICS METHODS
*/
  virtual int Run() = 0;

  virtual CATBody *GetResult(CATCGMJournalList *) = 0;

  virtual void SetStraightRelimitation() = 0;

  virtual void SetOffsetValue(double iSecondOffset) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopThickWire(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopThickWire *CATPGMCreateTopThickWire(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATLISTP(CATBody) *iWires,
  CATBody *iSupport,
  double iOffset);

#endif /* CATIPGMTopThickWire_h_ */
