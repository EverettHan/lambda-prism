#ifndef CATIPGMIdenticalSurSur_h_
#define CATIPGMIdenticalSurSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"

class CATGeoFactory;
class CATMathTransformation2D;
class CATSurLimits;
class CATSurface;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMIdenticalSurSur;

//-----------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATIPGMIdenticalSurSur: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMIdenticalSurSur();

  /**
 * Set the surfaces 
 * Note : 
 * - This service is to be used to reuse the same operator with different surfaces.
 * - If called , it has to be called before any other service ( before "HoldDomain" for exemple ).
 */
  virtual void SetSurfaces(CATSurface *iSurface1, CATSurface *iSurface2) = 0;

  /**
 * Set the domains on each surface in <tt>ADVANCED</tt> mode.
 */
  virtual void HoldDomain(const CATSurLimits *iLimit1, const CATSurLimits *iLimit2) = 0;

  /**
 * Returns 1 if the two surfaces are identical and 0 otherwise.
 */
  virtual CATBoolean GetIdentity() const = 0;

  /**
 * Returns 1 if the two surfaces are identical with same normals and -1
 * if the normals are opposite.
 */
  virtual CATLONG32 GetNormalOrientation() const = 0;

  /**
 * Returns the change of mapping between the surface 1 and 2.
 */
  virtual void GetMapping12(CATMathTransformation2D *&oTransfo2D) = 0;

  /**
 * Returns the change of mapping between the surface 2 and 1.
 */
  virtual void GetMapping21(CATMathTransformation2D *&oTransfo2D) = 0;

  /**
 * Filter the surfaces to be tested based on a logical criterion
 * This service is done for performance purpose to avoid unecessary operator creation
 * Return TRUE if the 2 surfaces can not be identical ( in this case the operator has not to be created )
 * Return FALSE if the 2 surfaces may be identical ( in this case the operator has to be created )
 */
  static CATBoolean FilterSurfacesToTestTested(
    CATSurface *iSurface1,
    CATSurface *iSurface2);

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMIdenticalSurSur(); // -> delete can't be called
};

#endif /* CATIPGMIdenticalSurSur_h_ */
