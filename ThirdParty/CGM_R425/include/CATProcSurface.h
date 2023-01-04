#ifndef CATProcSurface_h
#define CATProcSurface_h

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CATSurface.h"

class CATProcSurface ;
class CATProcSurfaceDef;
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATProcSurface ;
#else
extern "C" const IID IID_CATProcSurface ;
#endif

/**
 * Interface representing  any procedural surface defined by CATProcSurfaceDef
 *<br> The CATProcSurface is created by the <tt>CreateProcSurface</tt>
 * method of the <tt>CATGeoFactory</tt> interface.
 */

class ExportedByCATGMGeometricInterfaces CATProcSurface : public CATSurface
{
  CATDeclareInterface;
  
public:
  
/**
* Returns a pointer to the CATProcSurfaceDef of a CATProcSurface. 
* Warning : the returned pointer does not belong to the caller
*/
  virtual const CATProcSurfaceDef * GetProcSurfaceDef() const = 0;
/**  
* Returns a pointer to the reference surface of a CATProcSurface.
*/
  virtual CATSurface * GetReference() const = 0;
  
/**
* Update after extrapol.
*/
  virtual void Extrapol (CATLONG32 OldNbPatchU,CATLONG32 OldNbPatchV,CATLONG32 OldOffsetU,CATLONG32 OldOffsetV) = 0 ;
};

CATDeclareHandler(CATProcSurface,CATSurface);

#endif
