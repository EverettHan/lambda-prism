//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2011
//=============================================================================
//
// CATCompareContext:
//    Definition of the context for comparing geometric entities.
//
//=============================================================================
// Usage notes:
//=============================================================================
// June 2011 Creation                                                       R1Y
// Oct. 2014 Added an option to check current-limits data.                  R1Y
// Feb. 2015 Stored the current CGM level as member data.                   R1Y
// Nov. 2016 Added an option to check the maximum limits for a circle.      R1Y
// Dec. 2016 Added an option for extrapolated surfaces.                     R1Y
// Jan. 2017 Added an option to check maximum limits.                       R1Y
// Sep. 2017 Added SetConfig().                                             R1Y
// Feb. 2020 Renamed the option for extrapolated surfaces (to geometry).    R1Y
// May  2020 Stored tags in the cache, and streamed the cache.              R1Y
//=============================================================================
#ifndef CATCompareContext_H
#define CATCompareContext_H

#include "ExportedByGeometricObjects.h"
#include "CATCGMVirtual.h"
#include "CATBoolean.h"
#include "CATMathLimits.h"  // For CAT_ABSOLUTE_EPSILON
#include "CATListOfInt.h"
#include "CATCompareResult.h"

class CATGeometry;
class CATCompareCache;
class CATNewHashTable2Entries;
class CATCGMStream;
class CATSoftwareConfiguration;

class ExportedByGeometricObjects CATCompareContext : public CATCGMVirtual
{
public:
  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------
  // Constructor
  // Note that if the input tolerance is negative then the default tolerance value is used.
  CATCompareContext(CATSoftwareConfiguration * iConfig,
                    double                     iTolerance = CAT_ABSOLUTE_EPSILON);

  // Destructor
  ~CATCompareContext();

  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------
  // Set the tolerance
  // Note that if the input tolerance is negative then the default tolerance value is used.
  void SetTolerance(double iTolerance);

  // Set the flag that indicates whether current-limits data is to be checked
  void SetCheckCurrentLimits(const CATBoolean iCheckCurrentLimits);

  // Set the flag that indicates whether the maximum limits for a circle are to be checked
  void SetCheckCircleMaxLimits(const CATBoolean iCheckCircleMaxLimits);

  // Set the flag that indicates whether extrapolated geometry is to be taken into account
  void SetCheckExtrapolatedGeometry(const CATBoolean iCheckExtrapolatedGeometry);

  // Set the flag that indicates whether maximum limits are to be checked
  void SetCheckMaximumLimits(const CATBoolean iCheckMaximumLimits);

  // Get the software configuration
  INLINE CATSoftwareConfiguration * GetConfig() const;

  // Get the CGM level
  INLINE short GetCurrentLevel() const;

  // Get the tolerance
  INLINE double GetTolerance() const;

  // Get the flag that indicates whether current-limits data is to be checked
  INLINE CATBoolean GetCheckCurrentLimits() const;

  // Get the flag that indicates whether the maximum limits for a circle are to be checked
  INLINE CATBoolean GetCheckCircleMaxLimits() const;

  // Get the flag that indicates whether extrapolated geometry is to be taken into account
  INLINE CATBoolean GetCheckExtrapolatedGeometry() const;

  // Get the flag that indicates whether maximum limits are to be checked
  INLINE CATBoolean GetCheckMaximumLimits() const;

  // Store the result of the comparison in the cache (if there is one)
  void StoreComparison(const CATGeometry      * const & iGeometry1,
                       const CATGeometry      * const & iGeometry2,
                             CATCompareResult         & ioResult);

  // Get the result from the cache (if there is one)
  CATBoolean GetComparison(const CATGeometry      * const & iGeometry1,
                           const CATGeometry      * const & iGeometry2,
                                 CATCompareResult         & oResult);

  // Indicate whether to store compared geometries that are the same
  void SetStoreSameComparedGeometries(CATBoolean iStoreSameComparedGeometries);

  // Determine whether same geometries are being stored
  CATBoolean GetStoreSameComparedGeometries() const;

  // Get the number of entries in the repository of compared geometries that are the same
  int GetNumSameComparedGeometries() const;

  // Get the entry at a specified location (>= 0) in the repository of compared geometries that are the same
  void GetSameComparedGeometries(const int            iLocation,
                                 const CATGeometry *& oGeometry1,
                                 const CATGeometry *& oGeometry2) const;

  // Clear the repository of compared geometries that are the same
  void ClearSameComparedGeometries();

  // Get the number of elements in the cache
  int GetNumCacheElements() const;

  // Stream the class data
  void Stream(CATCGMStream & oStream) const;

  // Un-stream the class data
  void UnStream(CATGeoFactory * const   iFactory,
                CATCGMStream          & iStream);

  // Get the element in a specified location (>= 0) in the cache
  CATBoolean GetCacheElement(const int                         iLocation,
                                   CATLONG32                 & oTag1,
                                   CATLONG32                 & oTag2,
                                   CATCompareGeometryOutcome & oOutcome) const;

  // Get the number of values in the check sum for the cache
  int GetNumCheckSumValues() const;

  // Compute the check-sum values for the cache
  CATBoolean ComputeCheckSumValues(CATGeoFactory * const   iFactory,
                                   CATListOfInt          & oCheckSumValues) const;

private:
  //-----------------------------------------------------------------------
  //- Private Methods
  //-----------------------------------------------------------------------

  // Function to set the software configuration.
  void SetConfig(CATSoftwareConfiguration * const iConfig);

  // Store the result of the comparison in the cache (if there is one)
  void StoreComparison(      CATGeoFactory             * const   iFactory,
                       const CATLONG32                           iTag1,
                       const CATLONG32                           iTag2,
                       const CATCompareGeometryOutcome         & iOutcome);

  // Get the outcome from the cache (if there is one)
  CATBoolean GetComparison(      CATGeoFactory             * const   iFactory,
                           const CATLONG32                           iTag1,
                           const CATLONG32                           iTag2,
                                 CATCompareGeometryOutcome         & oOutcome);

  // Add two geometries to the repository of compared geometries that are the same
  void AddSameComparedGeometries(const CATGeometry * const & iGeometry1,
                                 const CATGeometry * const & iGeometry2);

  // Add two geometries to the repository of compared geometries that are the same
  void AddSameComparedGeometries(      CATGeoFactory * const iFactory,
                                 const CATLONG32             iTag1,
                                 const CATLONG32             iTag2);

  // Empty the cache and the repository of compared geometries that are the same
  void ResetCacheAndRepository();

  // Function to stream the cache.
  void StreamCache(CATCGMStream & oStream) const;

  // Function to un-stream the cache.
  void UnStreamCache(CATGeoFactory * const   iFactory,
                     CATCGMStream          & iStream);

  // Set the numbers of cache elements involving points, curves, and surfaces
  void SetNumCacheGeometryElements(const int iNumPoints,
                                   const int iNumCurves,
                                   const int iNumSurfaces);

  // Function to get the numbers of cache elements involving points, curves, and surfaces
  void GetNumCacheGeometryElements(int & oNumPoints,
                                   int & oNumCurves,
                                   int & oNumSurfaces) const;

  // Function to stream the data of the cache elements from the tag and outcome arrays.
  // Helper function for StreamCache().
  CATBoolean StreamCacheElements(      CATCGMStream         & oStream,
                                 const CATLONG32              ioNumGeometryElements,
                                 const CATLONG32    * const   iGeometryTags,
                                 const short        * const   iGeometryOutcomes) const;

  // Function to un-stream the data of cache elements into the tag and outcome arrays.
  // Helper function for UnStreamCache().
  void UnStreamGeometry(CATCGMStream  & iStream,
                        CATLONG32     & oNumPointElements,
                        CATLONG32     & oNumCurveElements,
                        CATLONG32     & oNumSurfaceElements,
                        CATLONG32     & ioNumGeometryElements,
                        CATLONG32    *& oGeometryTags,
                        short        *& oGeometryOutcomes) const;

  // Function to add un-streamed data from the tag and outcome arrays to the cache.
  // Helper function for UnStreamCache().
  void AddUnStreamedElementsToCache(      CATGeoFactory * const  iFactory,
                                    const CATLONG32              iNumPointElements,
                                    const CATLONG32              iNumCurveElements,
                                    const CATLONG32              iNumSurfaceElements,
                                    const CATLONG32              iNumGeometryElements,
                                    const CATLONG32      * const iGeometryTags,
                                    const short          * const iGeometryOutcomes);

//-----------------------------------------------------------------------
  //- Private data
  //-----------------------------------------------------------------------  
  double _Tolerance;
  CATSoftwareConfiguration * _Config;
  short _CGMLevel;
  CATBoolean _CheckCurrentLimits;
  CATBoolean _CheckCircleMaxLimits;
  CATBoolean _CheckExtrapolatedGeometry;
  CATBoolean _CheckMaximumLimits;
  CATCompareCache * _Cache;
  CATBoolean _UseCache;  // for debug purposes only
  CATBoolean _StoreSameComparedGeometries;
  CATNewHashTable2Entries * _SameComparedGeometriesTable;
};

//-----------------------------------------------------------------------
// Inline functions.
//-----------------------------------------------------------------------

//- Function to get the software configuration
INLINE CATSoftwareConfiguration * CATCompareContext::GetConfig() const
{
   return _Config;
}

//- Function to get the CGM level
INLINE short CATCompareContext::GetCurrentLevel() const
{
  return _CGMLevel;
}

//- Function to get the tolerance
INLINE double CATCompareContext::GetTolerance() const
{
  return _Tolerance;
}

//- Function to get the flag that indicates whether current-limits data is to be checked
INLINE CATBoolean CATCompareContext::GetCheckCurrentLimits() const
{
  return _CheckCurrentLimits;
}

//- Function to get the flag that indicates whether the maximum limits for a circle are to be checked
INLINE CATBoolean CATCompareContext::GetCheckCircleMaxLimits() const
{
  return _CheckCircleMaxLimits;
}

//- Function to get the flag that indicates whether extrapolated geometry is to be taken into account
INLINE CATBoolean CATCompareContext::GetCheckExtrapolatedGeometry() const
{
  return _CheckExtrapolatedGeometry;
}

//- Function to get the flag that indicates whether maximum limits are to be checked
INLINE CATBoolean CATCompareContext::GetCheckMaximumLimits() const
{
  return _CheckMaximumLimits;
}

//- Function to determine whether same geometries are being stored
INLINE CATBoolean CATCompareContext::GetStoreSameComparedGeometries() const
{
  return _StoreSameComparedGeometries;
}
#endif
