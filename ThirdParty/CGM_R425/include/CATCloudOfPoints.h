#ifndef CATCloudOfPoints_h
#define CATCloudOfPoints_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * Interface representing a permanent set of 3D mathematical points.
 * 
 * Use the CreateCloudOfPoints method of the 
 * CATGeoFactory interface to create a CATCloudOfPoints.
 */
#include "CATGeometry.h"
#include "CATMathDef.h"

class CATMathPoint;
class CATMathDirection;
class CATMathSetOfPointsND;
#include "CATListOfCATMathSetOfPointsND.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCloudOfPoints ;
#else
extern "C" const IID IID_CATCloudOfPoints ;
#endif


class ExportedByCATGMGeometricInterfaces CATCloudOfPoints : public CATGeometry
{
  CATDeclareInterface;

public:

// Returns the total number of points in the entire CATCloudOfPoints.
    virtual CATLONG32 GetNumberOfPoints () const = 0 ;
	
// Returns the number of scans in the CATCloudOfPoints.
    virtual CATLONG32 GetNumberOfScans () const = 0 ;

// Returns the number of points on a given scan.
    virtual CATLONG32 GetNumberOfPointsOnScan (const CATLONG32 iScan) const = 0 ;

/* Returns the topological points confusion distance of a CATCloudOfPoints.
 * The distance defines how close two points need to be in order to be
 * topologically related.
 */
    virtual CATPositiveLength GetOperatingDistance () const = 0 ;


  //-------------------------------------------------------------------------
  // Points read.
  // 	iGlobIndex goes from 0 to (global point count - 1),
  // 	iLocIndex goes from 0 to (point count on scan - 1),
  // 	iScan goes from 0 to (scan count - 1).
  //-------------------------------------------------------------------------

// Returns the point corresponding the index (global or local).
  virtual CATMathPoint GetPoint (const CATLONG32 iGlobIndex) const = 0 ;
  virtual CATMathPoint GetPoint (const CATLONG32 iScan, const CATLONG32 iLocIndex) const = 0 ;

/* Returns the pointer to the corresponding mathematical set of points
 * of a given scan
 * This method should be used for quick navigation through the cloud.
 * The output object cannot be changed and must not be deleted.*/
  virtual const CATMathSetOfPointsND * GetScan (const CATLONG32 iScan) const = 0;		    


  //-------------------------------------------------------------------------
  // Normals read.
  // 	iGlobIndex goes from 0 to (global point count - 1),
  // 	iLocIndex goes from 0 to (point count on scan - 1),
  // 	iScan goes from 0 to (scan count - 1).
  //-------------------------------------------------------------------------

// Returns 0 if the CATCloudOfPoints has no associated normals.
  virtual CATBoolean HasNormalsDefined() const =0 ;

// Returns the Normal associated to a given Point (global or local index).
// (!!! if vectors not defined returns default CATMathVector.)
  virtual CATMathDirection GetNormal (const CATLONG32 iIndex) const = 0 ;
  virtual CATMathDirection GetNormal (const CATLONG32 iScan, const CATLONG32 iLocIndex) const = 0 ;

  //-------------------------------------------------------------------------
  // Activation bits read.
  // 	iGlobIndex goes from 0 to (global point count - 1),
  // 	iLocIndex goes from 0 to (point count on scan - 1),
  // 	iScan goes from 0 to (scan count - 1).
  //-------------------------------------------------------------------------
// Returns 1 if the point is active, 0 otherwise
  virtual CATLONG32 IsPointActive (const CATLONG32 iGlobIndex) const = 0 ;
  virtual CATLONG32 IsPointActive (const CATLONG32 iScan, const CATLONG32 iLocIndex) const = 0 ;
  
// Returns the number of active points
  virtual CATLONG32 GetNumberOfActivePoints() const = 0 ;
  
// Fills an array of CATLONG32 of size (number of active points)
// with the global indices of the active points
  virtual void GetActivePointsGlobIndices (CATLONG32 * oPointsGlobIndices) const =0 ;

// Fills an array of CATLONG32 of size 2*(number of active points)
// with the scan indices and the local indices of the active points
  virtual void GetActivePointsLocIndices (CATLONG32 * oPointsScanAndLocIndices) const =0 ;

/* Fills the ioSetOfPoints with the only the active points of the cloud*/
  virtual void GetActivePoints (CATMathSetOfPointsND & oSetOfPoints) const = 0;		    

  //-------------------------------------------------------------------------
  //- Operating Distance modification.
  //-------------------------------------------------------------------------

/* Modifies the topological points confusion distance of a CATCloudOfPoints.
 * The distance defines how close two points need to be in order to be
 * topologically related.
 */
  virtual void SetOperatingDistance (const CATPositiveLength iNewOperatingDistance) = 0 ;


  //-------------------------------------------------------------------------
  //- Points modification.
  // 	iGlobIndex goes from 0 to (global point count - 1),
  // 	iLocIndex goes from 0 to (point count on scan - 1),
  // 	iScan goes from 0 to (scan count - 1).
  //-------------------------------------------------------------------------

// Modifies the coordinates of a given Point (global or local index).
  virtual void SetPoint (const CATLONG32 iGlobIndex, const CATMathPoint & iNewCoord) = 0 ;
  virtual void SetPoint ( const CATLONG32 iScan, const CATLONG32 iLocIndex,
			  const CATMathPoint & iNewCoord) = 0 ;


  //-------------------------------------------------------------------------
  //- Normals Modification.
  // 	iGlobIndex goes from 0 to (global point count - 1),
  // 	iLocIndex goes from 0 to (point count on scan - 1),
  // 	iScan goes from 0 to (scan count - 1).
  //-------------------------------------------------------------------------
// Modifies the normal associated to a given point (global or local index).
  virtual void SetNormal (const CATLONG32 iGlobIndex, const CATMathDirection & iNewVector) = 0 ;
  virtual void SetNormal (const CATLONG32 iScan, const CATLONG32 iLocIndex,
			  const CATMathDirection & iNewVector) = 0 ;

  //-------------------------------------------------------------------------
  // Activation bits modification.
  // 	iGlobIndex goes from 0 to (global point count - 1),
  // 	iLocIndex goes from 0 to (point count on scan - 1),
  // 	iScan goes from 0 to (scan count - 1).
  //-------------------------------------------------------------------------
// Modifies the activation bit of a given point (global or local index)  
  virtual void SetPointActivity ( const CATLONG32 iGlobIndex, const int iActivity) = 0 ;
  virtual void SetPointActivity ( const CATLONG32 iScan, const CATLONG32 iLocIndex,
				  const int iActivity) = 0 ;
// Modifies the activation bit of the iCount points of global indices iGlobIndices[i]
  virtual void SetPointActivity ( const CATLONG32 * iGlobIndices, const CATLONG32 iCount,
				  const int iActivity) = 0; 
// Resets all the points to active
  virtual void SetAllPointsToActive () = 0 ;

  //-------------------------------------------------------------------------
  //- Inserting and Removing Points (and Normals if defined)
  // 	iGlobIndex goes from 0 to (global point count - 1),
  // 	iLocIndex goes from 0 to (point count on scan - 1),
  // 	iScan goes from 0 to (scan count - 1).
  //-------------------------------------------------------------------------
// Inserts a Point and its Normal at a given index (global or local).
  virtual void InsertAt (const CATLONG32 iGlobIndex, 
			 const CATMathPoint & iNewPoint, 
			 const CATMathDirection & iNewVector )  = 0 ;
  virtual void InsertAt (const CATLONG32 iScan,
			 const CATLONG32 iLocIndex, 
			 const CATMathPoint & iNewPoint, 
			 const CATMathDirection & iNewVector )  = 0 ;

// Removes a given Point (global or local index)
// (and its associated Normal if defined).
  virtual void RemovePosition ( const CATLONG32 iGlobIndex ) = 0 ;
  virtual void RemovePosition ( const CATLONG32 iScan, const CATLONG32 iLocIndex ) = 0 ;

// Inserts a scan at a given position
  virtual void InsertScanAt ( const CATLONG32 iScan, 
			      CATMathSetOfPointsND * iSetOfPoints ) = 0 ;

// Removes a given scan
  virtual void RemoveScan ( const CATLONG32 iScan ) = 0 ;


  //-------------------------------------------------------------------------
  // Search for the closest point of the cloud to a given point
  //-------------------------------------------------------------------------
/* Searches for the index of the closest point to a given point
 * The search is done inside a sphere of radius iMaxDistance and of 
 * center iRefPoint. */
  virtual void Locate (CATMathPoint & iRefPoint,
		       const CATPositiveLength iMaxDistance,
		       CATLONG32 & oGlobIndex) const = 0 ;
  virtual void Locate (CATMathPoint & iRefPoint,
		       const CATPositiveLength iMaxDistance,
		       CATLONG32 & oScan, CATLONG32 & oLocIndex) const = 0 ;
		        

  //-------------------------------------------------------------------------
  //- Method called for the creation of the cloud of points
  //-------------------------------------------------------------------------
/* Replaces the referred CATLISTP(CATMathSetOfPointsND) by another one.
 * The previous referred CATLISTP(CATMathSetOfPointsND) is deleted.
 * @param iOperatingDistance:
 * The distance defines how close two points need to be in order to be
 * topologically related.*/
  virtual void Set (CATLISTP(CATMathSetOfPointsND) & iSetOfPoints,
		    const CATPositiveLength iOperatingDistance) = 0 ;

};
CATDeclareHandler(CATCloudOfPoints,CATGeometry);

#endif

