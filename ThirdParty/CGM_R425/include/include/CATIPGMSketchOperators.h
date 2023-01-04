#ifndef CATIPGMSketchOperators_h_
#define CATIPGMSketchOperators_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATCGMJournalList;
class CATWire;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMSketchOperators;

/**
  * Parent class of CATIPGMSketchGeodesic.
  * @see CATIPGMSketchGeodesic.
  */
class ExportedByCATGMOperatorsInterfaces CATIPGMSketchOperators: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMSketchOperators();

  /**
  * Retrieve the geodesic curve.
  * @param oBody
  * The geodesic curve.
  */
  virtual void GetResult(CATBody *&oBody) = 0;

  /**
  * @nodoc
  */
  virtual CATLONG32 GetNumberOfResults() const = 0;

  /**
  * @nodoc
  */
  virtual void BeginningResult() = 0;

  /**
  * @nodoc
  */
  virtual CATBoolean NextResult() = 0;

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
  virtual ~CATIPGMSketchOperators(); // -> delete can't be called
};

#endif /* CATIPGMSketchOperators_h_ */
