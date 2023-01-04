#ifndef CATIPGMSurTo2DGlobalMapping_h_
#define CATIPGMSurTo2DGlobalMapping_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"

class CATMathAxis;
class CATSoftwareConfiguration;
class CATSurLimits;
class CATSurface;
class CATCGMStream;
class CATGeoFactory;
class CATIPGMSurTo2DMapping;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMSurTo2DGlobalMapping;

/**
 * Class defining a consistant global mapping between a set of CATSurface and a
 * virtual  2 dimension space.
 * <br>This class is the base class for some supplied operators 
 * such as @href CATIPGMSurTo2DGlobalPlanarMapping,
 * but you must not derive it yourself.
 * <br>All global computations are done once when constructing the CATIPGMSurTo2DGlobalMapping.
 */
class ExportedByCATGMModelInterfaces CATIPGMSurTo2DGlobalMapping: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMSurTo2DGlobalMapping();

  /**
   * @nodoc
   * @return [out, IUnknown#Release]
      */
  virtual CATSoftwareConfiguration *GetSoftwareConfiguration() const = 0;

  /**
      * @nodoc
   * @return [out, IUnknown#Release]
   */
  virtual CATIPGMSurTo2DMapping *CreateLocalMapping(
    CATSurface *iLocalReference,
    const double &iRefOrientation,
    const CATSurLimits &iRefLimits) const = 0;

  /**
      * @nodoc
      */
  virtual void RemoveLocalMapping(CATIPGMSurTo2DMapping *iLocalMapping) = 0;

  /**
    * @nodoc
    */
  virtual void Stream(CATCGMStream &Str, const char *iLabelReserved = "") const = 0;

  /**
    * @nodoc
    * @param Str
    * @param iFactory
    * @param oMapping [out, IUnknown#Release]
    * @param iLabelReserved
    */
  static void UnStream(
    CATCGMStream &Str,
    CATGeoFactory *iFactory,
    CATIPGMSurTo2DGlobalMapping *&oMapping,
    const char *iLabelReserved = "");

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSurTo2DGlobalMapping(); // -> delete can't be called
};

#endif /* CATIPGMSurTo2DGlobalMapping_h_ */
