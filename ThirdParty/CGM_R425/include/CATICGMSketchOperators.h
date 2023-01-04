#ifndef CATICGMSketchOperators_h_
#define CATICGMSketchOperators_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"

class CATBody;
class CATCGMJournalList;
class CATWire;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMSketchOperators;

/**
  * Parent class of CATICGMSketchGeodesic.
  * @see CATICGMSketchGeodesic.
  */
class ExportedByCATGMOperatorsInterfaces CATICGMSketchOperators: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMSketchOperators();

  /**
  * Retrieve the geodesic curve.
  * @param oBody
  * The geodesic curve.
  */
  virtual void GetResult(CATBody *&oBody) = 0;

  /**
  * Retrieves the created wire.
  * @param iWire
  * The geodesic wire.
  */
  virtual void GetWire(CATWire *&iWire) const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMSketchOperators(); // -> delete can't be called
};

#endif /* CATICGMSketchOperators_h_ */
