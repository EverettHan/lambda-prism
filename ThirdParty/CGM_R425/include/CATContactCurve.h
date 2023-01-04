#ifndef CATContactCurve_h
#define CATContactCurve_h

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CATEdgeCurve.h"

class CATSurface;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATContactCurve ;
#else
extern "C" const IID IID_CATContactCurve ;
#endif

class ExportedByCATGMGeometricInterfaces CATContactCurve : public CATEdgeCurve
{
  CATDeclareInterface;

public:
/**
 * Replaces the CATEdgeCurve and the Surface of a CATContactCurve.
 */
// virtual void Set(CATEdgeCurve* iEdgeCurve, CATSurface* iSurface) = 0;

/**
 * Replaces the Surface of a CATContactCurve.
 */
 virtual void SetSurface(CATSurface* iSurface) = 0;


/**
 * Returns the CATSurface of a CATContactCurve.
 */ 
 virtual CATSurface* GetSurface() = 0;
};

CATDeclareHandler(CATContactCurve,CATEdgeCurve);

#endif
