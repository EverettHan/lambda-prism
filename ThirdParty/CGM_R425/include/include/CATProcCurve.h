#ifndef CATProcCurve_h
#define CATProcCurve_h

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CATCurve.h"

class CATProcCurve ;
class CATProcCurveDef;
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATProcCurve ;
#else
extern "C" const IID IID_CATProcCurve ;
#endif

/**
 * Interface representing  any procedural curve defined by CATProcCurveDef
 * Ex :Offset of the Profile of the Tabulated Cylinder.
 *<br> The CATProcCurve is created by the <tt>CreateProcCurve</tt>
 * method of the <tt>CATGeoFactory</tt> interface.
 */

class ExportedByCATGMGeometricInterfaces CATProcCurve : public CATCurve
{
  CATDeclareInterface;

public:

/**
 * Returns a pointer to the CATProcCurveDef of a CATProcCurve. 
 * Warning : the returned pointer does not belong to the caller
 */
  virtual const CATProcCurveDef * GetProcCurveDef() const = 0;
/**  
 * Returns a pointer to the reference curve of a CATProcCurve.
 */
  virtual CATCurve * GetReference() const = 0;

/**
 * Update after extrapol.
 */
  virtual void Extrapol (CATLONG32 OldNbPatch,CATLONG32 OldOffset) = 0 ;
};

CATDeclareHandler(CATProcCurve,CATCurve);

#endif
