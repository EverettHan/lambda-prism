// COPYRIGHT DASSAULT SYSTEMES 1997 
/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#ifndef CATSweepSurface_h
#define CATSweepSurface_h

#include "CATBaseUnknown.h"
#include "CATSurface.h"
#include "CATMathDef.h"

#include "ExportedByCATGMGeometricInterfaces.h"

class CATNurbsSurface;
class CATMathSetOfPoints;

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATSweepSurface ;
#else
extern "C" const IID IID_CATSweepSurface ;
#endif

/**
 * Interface to retrieve the Nurbs surface from a sweep.
 */

class ExportedByCATGMGeometricInterfaces CATSweepSurface : public CATSurface
{
  CATDeclareInterface;

 public:
/**
 * Returns a pointer to the Nurbs surface.
 * @return
 * The pointer to the CATNurbsSurface.
 */
    virtual CATNurbsSurface* GetSweepSurface() const= 0;

};
  CATDeclareHandler(CATSweepSurface,CATSurface);
#endif
