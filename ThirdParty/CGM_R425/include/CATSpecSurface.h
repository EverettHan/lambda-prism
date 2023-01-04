#ifndef CATSpecSurface_h
#define CATSpecSurface_h

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CATSurface.h"

class CATSpecSurface ;
class CATSpecSurfaceDef;
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATSpecSurface ;
#else
extern "C" const IID IID_CATSpecSurface ;
#endif

/**
 * Interface representing  any Surface defined by CATSpecSurfaceDef
 * Ex : bissector surface.
 *<br> The CATSpecSurface is created by the <tt>CreateSpecSurface</tt>
 * method of the <tt>CATGeoFactory</tt> interface.
 */


class ExportedByCATGMGeometricInterfaces CATSpecSurface : public CATSurface
{
  CATDeclareInterface;

public:

/**
 * Returns a pointer to the CATSpecSurfaceDef of a CATSpecSurface. 
 * Warning : the returned pointer does not belong to the caller
 */
  virtual const CATSpecSurfaceDef * GetSpecSurfaceDef() const = 0;

};

CATDeclareHandler(CATSpecSurface,CATSurface);

#endif
