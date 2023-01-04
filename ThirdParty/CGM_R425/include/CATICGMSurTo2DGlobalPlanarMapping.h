#ifndef CATICGMSurTo2DGlobalPlanarMapping_h_
#define CATICGMSurTo2DGlobalPlanarMapping_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMSurTo2DGlobalMapping.h"

class CATSurLimits;

extern ExportedByCATGMModelInterfaces IID IID_CATICGMSurTo2DGlobalPlanarMapping;

/**
 * Class defining the mapping between one set of surfaces and a
 * virtual  2 dimension space defined by an axis.
 * CATICGMSurTo2DGlobalPlanarMapping is created with the @href CATCGMCreatePlanarMapping
 * global function and released with the <tt>Release</tt> method.
 */
class ExportedByCATGMModelInterfaces CATICGMSurTo2DGlobalPlanarMapping: public CATICGMSurTo2DGlobalMapping
{
public:
  /**
   * Constructor
   */
  CATICGMSurTo2DGlobalPlanarMapping();

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMSurTo2DGlobalPlanarMapping(); // -> delete can't be called
};

#endif /* CATICGMSurTo2DGlobalPlanarMapping_h_ */
