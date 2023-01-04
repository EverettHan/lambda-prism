#ifndef CATIPGMSurTo2DGlobalCompositionMapping_h_
#define CATIPGMSurTo2DGlobalCompositionMapping_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMSurTo2DGlobalMapping.h"

class CATMathFunctionXY;
class CATSurLimits;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMSurTo2DGlobalCompositionMapping;

//----------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATIPGMSurTo2DGlobalCompositionMapping: public CATIPGMSurTo2DGlobalMapping
{
public:
  /**
   * Constructor
   */
  CATIPGMSurTo2DGlobalCompositionMapping();

  //-------------
  //-------------
  // Methods
  //-------------
  //  Create LocalMapping 
  /**
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
  virtual ~CATIPGMSurTo2DGlobalCompositionMapping(); // -> delete can't be called
};

#endif /* CATIPGMSurTo2DGlobalCompositionMapping_h_ */
