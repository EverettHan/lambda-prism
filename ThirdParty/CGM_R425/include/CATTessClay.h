#ifndef CATTessClay_h
#define CATTessClay_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * CATGeoFactory interface to create a CATTessClay.
 */
class CATClay;
#include "CATGeometry.h"
#include "CATMathBox.h"
#include "CATMathDef.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATTessClay ;
#else
extern "C" const IID IID_CATTessClay ;
#endif


class ExportedByCATGMGeometricInterfaces CATTessClay : public CATGeometry
{
  CATDeclareInterface;

public:

// Returns the total number of points in the entire CATTessClay.
  virtual const CATClay * GetReference () const = 0 ;
  
/* Primitive is the kind of object linking the points of a CATTessClay.
 * The primitive of a CATTessScan or CATTessCloud, is a triangle. 
 */
// Returns the total number of primitives in the entire CATTessClay.
  virtual CATLONG32 GetNumberOfPrimitives () const = 0 ;
  
// Get number of active primitives.
  virtual CATLONG32 GetNumberOfActivePrimitives () const = 0;
  
// Get the index array of the active primitives.
  virtual CATLONG32 * GetActivePrimitives (CATLONG32 &oNbActivePrimitives) const = 0;
  
// Get all primitives.
  virtual const CATLONG32 * GetPrimitives () const = 0;

// Get all primitives in a given box.
  virtual CATLONG32 * GetPrimitivesInABox (CATLONG32 IndexOfBox) const = 0;

// Get all neighbours.
  virtual const CATLONG32 * GetNeighbours () const = 0;

// Remove a primitive
  virtual void RemoveAPrimitive (CATLONG32 index) = 0;

/* Activity is a bit for each primitives. It is used by some operators, allowing
 * them to work only on a sub-cloud.
 */
// Set/Unset the activity for a primitive.
  virtual void SetActivityForAPrimitive (CATLONG32 index) = 0;

  virtual void UnsetActivityForAPrimitive (CATLONG32 index) = 0;

// Invert the activity for all primitives.
  virtual void InvertActivity () = 0;

// Get activity.
  virtual CATBoolean IsPrimitiveActive (CATLONG32 index) const = 0;

};
CATDeclareHandler(CATTessClay,CATGeometry);

#endif

