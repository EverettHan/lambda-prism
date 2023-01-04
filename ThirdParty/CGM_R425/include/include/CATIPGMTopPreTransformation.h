#ifndef CATIPGMTopPreTransformation_h_
#define CATIPGMTopPreTransformation_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopPreTransformation;

/**
* Class representing the topological operator that creates a CATBody suitable for being transformed.
* <br>
* It follows the use frame of all operator and satisfies to the smart mechanism: the
* input body is not modified. A new resulting body is created, 
* possibly sharing data with the input one.
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMTopPreTransformation: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopPreTransformation();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopPreTransformation(); // -> delete can't be called
};

#endif /* CATIPGMTopPreTransformation_h_ */
