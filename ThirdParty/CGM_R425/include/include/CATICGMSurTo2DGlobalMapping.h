#ifndef CATICGMSurTo2DGlobalMapping_h_
#define CATICGMSurTo2DGlobalMapping_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMOperator.h"

class CATMathAxis;
class CATSoftwareConfiguration;
class CATSurLimits;
class CATSurface;

extern ExportedByCATGMModelInterfaces IID IID_CATICGMSurTo2DGlobalMapping;

/**
 * Class defining a consistant global mapping between a set of CATSurface and a
 * virtual  2 dimension space.
 * <br>This class is the base class for some supplied operators 
 * such as @href CATICGMSurTo2DGlobalPlanarMapping,
 * but you must not derive it yourself.
 * <br>All global computations are done once when constructing the CATICGMSurTo2DGlobalMapping.
 */
class ExportedByCATGMModelInterfaces CATICGMSurTo2DGlobalMapping: public CATICGMOperator
{
public:
  /**
   * Constructor
   */
  CATICGMSurTo2DGlobalMapping();

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMSurTo2DGlobalMapping(); // -> delete can't be called
};

#endif /* CATICGMSurTo2DGlobalMapping_h_ */
