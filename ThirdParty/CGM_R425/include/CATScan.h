#ifndef CATScan_h
#define CATScan_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * CATGeoFactory interface to create a CATScan.
 */
#include "CATClay.h"
#include "CATMathBox.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATScan ;
#else
extern "C" const IID IID_CATScan ;
#endif


class ExportedByCATGMGeometricInterfaces CATScan : public CATClay
{
  CATDeclareInterface;

public:

// Get the index of the first point of a scan.
  virtual CATLONG32 GetIndexOfFirstPointForAScan (CATLONG32 IndexOfScan) const = 0;

// Get number of scans.
  virtual CATLONG32 GetNumberOfScans () const = 0;

// Get the number of points for a scan.
  virtual CATLONG32 GetNumberOfPointsForOneScan (CATLONG32 IndexOfScan) const = 0;
  
// Get the points for a scan.
  virtual const float * GetPointsForOneScan (CATLONG32 IndexOfScan) const = 0;

// Get the bounding box for one scan.
  virtual void GetBoundingBoxForOneScan (CATLONG32 IndexOfScan,CATMathBox &oBox) const = 0;

// Get the index of the scan owning the point.
  virtual CATLONG32 GetScanIndexFromPointIndex (CATLONG32 IndexOfPoint) const = 0;
  
};
CATDeclareHandler(CATScan,CATClay);

#endif
