#ifndef CATIPGMTopIntersectByMultiBodies_h_
#define CATIPGMTopIntersectByMultiBodies_h_

// COPYRIGHT DASSAULT SYSTEMES 2022

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopMultiResult.h"
#include "ListPOfCATBody.h"

class CATBody;
class CATExtTopIntersectByMultiBodies;
class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopIntersectByMultiBodies;

class ExportedByCATGMOperatorsInterfaces CATIPGMTopIntersectByMultiBodies: public CATIPGMTopMultiResult
{
public:
  /**
   * Constructor
   */
  CATIPGMTopIntersectByMultiBodies();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopIntersectByMultiBodies(); // -> delete can't be called
};

/**
* External method that creates an instance of CATIPGMTopIntersectByMultiBodies.
*   @param ipFactory
*     the pointer to the factory of the geometry.
*   @param ipTopdata
*     the pointer to the data defining the software configuration and the journal.
*     If the journal inside the configuration is <tt>NULL</tt>, it is not filled.
*   @param iBodyToIntersect
*     1D (curve), 2D (surface)
*   @param iListOfIntersectingBodies
*     2D (surfaces) bodies to intersect with iBodyToIntersect
* The dimension of each result body will depend on the dimension of its 2 operands
* curve       by     surface       ->     point
* surf        by     surface       ->     curve
* =>   result dimension     =      iBodyToIntersect dimension – 1  
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopIntersectByMultiBodies *CATPGMCreateTopIntersectByMultiBodies(
  CATGeoFactory *ipFactory,
  CATTopData *ipTopdata,
  CATBody *iBodyToIntersect,
  const CATLISTP(CATBody) &iListOfIntersectingBodies);

#endif /* CATIPGMTopIntersectByMultiBodies_h_ */
