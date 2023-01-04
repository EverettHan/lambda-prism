#ifndef CATIPGMSurTo2DGlobalPlanarMapping_h_
#define CATIPGMSurTo2DGlobalPlanarMapping_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMSurTo2DGlobalMapping.h"

class CATSurLimits;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMSurTo2DGlobalPlanarMapping;

/**
 * Class defining the mapping between one set of surfaces and a
 * virtual  2 dimension space defined by an axis.
 * CATIPGMSurTo2DGlobalPlanarMapping is created with the @href CATPGMCreatePlanarMapping
 * global function and released with the <tt>Release</tt> method.
 */
class ExportedByCATGMModelInterfaces CATIPGMSurTo2DGlobalPlanarMapping: public CATIPGMSurTo2DGlobalMapping
{
public:
  /**
   * Constructor
   */
  CATIPGMSurTo2DGlobalPlanarMapping();

  /**
      * @nodoc
      * @return [out, IUnknown#Release]
      */
  virtual CATIPGMSurTo2DMapping *CreateLocalMapping(
    CATSurface *iLocalReference,
    const double &iRefOrientation,
    const CATSurLimits &iRefLimits) const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSurTo2DGlobalPlanarMapping(); // -> delete can't be called
};

#endif /* CATIPGMSurTo2DGlobalPlanarMapping_h_ */
