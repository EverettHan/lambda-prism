#ifndef CATClay_h
#define CATClay_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * CATGeoFactory interface to create a CATClay.
 */
#include "CATGeometry.h"
#include "CATMathBox.h"
#include "CATMathDef.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATClay ;
#else
extern "C" const IID IID_CATClay ;
#endif


class ExportedByCATGMGeometricInterfaces CATClay : public CATGeometry
{
  CATDeclareInterface;

public:

// Returns the total number of points in the entire CATClay.
  virtual CATLONG32 GetNumberOfPoints () const = 0 ;
  
// Returns the array of points in the CATClay.
  virtual const float * GetPoints () const = 0 ;

// Set the entire array of points in the CATClay. This method force
// the recomputation of all data in the CATClay.
  virtual void SetPoints (CATLONG32 size,const float *iPoints) = 0 ;

// Returns the point corresponding to the index.
  virtual const float * GetPoint (CATLONG32 index) const = 0 ;

// Returns the index of the point corresponding to the input coordinates.
  virtual CATLONG32 GetPointIndex (const float * iPoint) const = 0 ;

// Set some points. Could force the recomputation of all data in the CATClay
// i.e. the index of the points could change.
// This method don't recompute all the data, i.e., BoundingBoxs can only widen, and
// characteristic distance is not recomputed at all.
  virtual void SetPoints (CATLONG32 size,const CATLONG32 * indexes,const float * iPoint) = 0 ;

// Returns the array of normals in the CATClay (as many as points).
  virtual const float * GetNormals () const = 0 ;

// Set the entire array of normals in the CATClay, keeping its size.
  virtual void SetNormals (const float * iNormal) = 0 ;

// Returns a normal.
  virtual const float * GetNormal (CATLONG32 index) const = 0 ;

// Set a normal.
  virtual void SetNormal (CATLONG32 index,const float * iNormal) = 0 ;


/* The CharacteristicDistance is an estimation of the max of the min distance 
 * between points.
 */
  virtual CATPositiveLength GetCharacteristicDistance () const = 0 ;

  virtual void SetCharacteristicDistance (CATPositiveLength dist) = 0 ;

// Remove a point.
// This method don't recompute all the data, i.e., BoundingBoxs are only widen, and
// characteristic distance is not recomputed at all.
  virtual void RemoveAPoint (CATLONG32 index) = 0;

// Insert a point - If the clay has Normals, you should enter a normal for the point to be inserted.
// Else, the 3 coordinates will be equal 0.
// In the case of a cloud, if the index does not correspond to the coordinates of NewPoint, the true index
// of NewPoint may be different from index. If you are not sure of the index of the point you want to
// insert, you can choose for index, GetNumberOfPoints().
// This method don't recompute all the data, characteristic distance is not recomputed at all.
  virtual void InsertAPointAtPosition (CATLONG32 index,const float * NewPoint,const float * NewNormal=0) = 0;


/* Activity is a bit for each points. It is used by some operators, allowing
 * them to work only on a sub-cloud.
 */
// Set/Unset the activity for a point.
  virtual void SetActivityForAPoint (CATLONG32 index) = 0;

  virtual void UnsetActivityForAPoint (CATLONG32 index) = 0;

// Get the number of active points.
  virtual CATLONG32 GetNumberOfActivePoints() const = 0;

// Get the index array of the active points.
  virtual CATLONG32 * GetActivePoints (CATLONG32 &oNbActivePoints) const = 0;

// Invert the activity for all points.
  virtual void InvertActivity () = 0;

// Get activity.
  virtual CATLONG32 IsPointActive (CATLONG32 index) const = 0;

};
CATDeclareHandler(CATClay,CATGeometry);

#endif

