#ifndef CATCompareGeometry_H
#define CATCompareGeometry_H
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2011
//=============================================================================
//
// CATCompareGeometry: service to compare two geometries
//
//=============================================================================
// Usage notes:    Here is an example code snippet 
//    CATCompareGeometryOutcome result = CATCompare_NotImplemented;
//    CATSoftwareConfiguration * config = ...  // get a software configuration
//    CATCompareContext ioContext( config, 0.0000001 );  // set the software configuration and numerical comparision tolerance (the default tolerance value is CAT_ABSOLUTE_EPSILON, which is 1.0e-38)
//    CATCompareGeometry* compare = CATCompareGeometry::CreateCompareGeometry( &ioContext );
//
//    if ( compare )
//    {
//      // Set the geometries to be compared
//    	compare->SetFirstGeometry(  _Curve1 );
//    	compare->SetSecondGeometry( _Curve2 );
//    	compare->Run();
//    	result = compare->GetOutcome();
//
//      delete compare;
//      compare = NULL;
//    }
//
//    if ( result == CATCompare_Same )
//    { ... }
//=============================================================================
// June 2011 Creation                                                     XMH
// Oct. 2011 Added a "sizeof" test for geometry classes.                  R1Y
// Jan. 2012 Added functionality for outputing geometry to NCGM files.    R1Y
// Oct. 2012 Modifications for CATTolerance under CATIACGMR215CAA.        R1Y
// Oct. 2014 Added an option to check current-limits data.                R1Y
// Nov. 2016 Added an option to check the maximum limits for a circle.    R1Y
// Dec. 2016 Added an option for extrapolated surfaces.                   R1Y
// Jan. 2017 Added an option to check maximum limits.                     R1Y
// Feb. 2020 Renamed the option for extrapolated surfaces (to geometry).  R1Y
// Apr. 2020 Stored tags (instead of geometry pointers) in the cache.     R1Y
//=============================================================================
#include "CATIACGMLevel.h" // automatic treatment EB_2014_04_16

#include "ExportedByGeometricObjects.h"
#include "CATCompareResult.h"
#include "CATGeometryType.h"
#include "CATBoolean.h"
#include "CATListOfInt.h"
#include "CATString.h"

class CATCompareContext;
class CATGeometry;
class CATGeoFactory;

#ifdef DEBUG_COMPAREGEOMETRY
class CATCGMObject;
#endif

class ExportedByGeometricObjects CATCompareGeometry
{
public:

  virtual ~CATCompareGeometry() {};

  static CATCompareGeometry* CreateCompareGeometry(const CATCompareContext * ioContext);

  //-----------------------------------------------------------------------
  //- Get methods
  //-----------------------------------------------------------------------
  // Get the first geometry that is to be compared
  virtual const CATGeometry * GetFirstGeometry() const = 0;
  // Get the second geometry that is to be compared
  virtual const CATGeometry * GetSecondGeometry() const = 0;
  // Get the flag that indicates whether current-limits data is to be checked
  virtual CATBoolean GetCheckCurrentLimits() const = 0;
  // Get the flag that indicates whether the maximum limits for a circle are to be checked
  virtual CATBoolean GetCheckCircleMaxLimits() const = 0;
  // Get the flag that indicates whether extrapolated geometry is to be taken into account
  virtual CATBoolean GetCheckExtrapolatedGeometry() const = 0;
  // Get the flag that indicates whether maximum limits are to be checked
  virtual CATBoolean GetCheckMaximumLimits() const = 0;
  // Get the result
  virtual const CATCompareResult * GetResult() const = 0;
  // Get the outcome
  virtual CATCompareGeometryOutcome GetOutcome() const = 0;
  // Get the context
  virtual const CATCompareContext * GetContext() const = 0;
  // Get the number of elements in the cache
  virtual int GetNumCacheElements() const = 0;
  // Get the element in a specified location (>= 0) in the cache
  virtual CATBoolean GetCacheElement(const int                          iLocation,
                                            CATLONG32                 & iTag1,
                                            CATLONG32                 & iTag2,
                                            CATCompareGeometryOutcome & oOutcome) const = 0;
  // Get the number of values in the check sum for the cache
  virtual int GetNumCheckSumValues() const = 0;
  // Compute the check-sum values for the cache
  virtual CATBoolean ComputeCheckSumValues(CATGeoFactory * const   iFactory,
                                           CATListOfInt          & oCheckSumValues) const = 0;
  // Indicate whether to store compared geometries that are the same
  virtual void SetStoreSameComparedGeometries(CATBoolean iStoreSameComparedGeometries) = 0;
  // Determine whether same geometries are being stored
  virtual CATBoolean GetStoreSameComparedGeometries() const = 0;
  // Get the number of entries in the repository of compared geometries that are the same
  virtual int GetNumSameComparedGeometries() const = 0;
  // Get the entry at a specified location (>= 0) in the repository of compared geometries that are the same
  virtual void GetSameComparedGeometries(const int             iLocation,
                                         const CATGeometry *& oGeometry1,
                                         const CATGeometry *& oGeometry2) const = 0;
  // Clear the repository of compared geometries that are the same
  virtual void ClearSameComparedGeometries() = 0;

  //-----------------------------------------------------------------------
  //- Set methods
  //-----------------------------------------------------------------------
  // Set the context
  virtual void SetContext(CATCompareContext * iContext) = 0;
  // Set the first geometry that is to be compared
  virtual void SetFirstGeometry(const CATGeometry * iGeometry) = 0;
  // Set the second geometry that is to be compared
  virtual void SetSecondGeometry(const CATGeometry * iGeometry) = 0;
  // Set the two geometries that are to be compared
  virtual void SetGeometries(const CATGeometry * iGeometry1, const CATGeometry * iGeometry2) = 0;
  // Set the flag that indicates whether current-limits data is to be checked
  virtual void SetCheckCurrentLimits(const CATBoolean iCheckCurrentLimits) = 0;
  // Set the flag that indicates whether the maximum limits for a circle are to be checked
  virtual void SetCheckCircleMaxLimits(const CATBoolean iCheckCircleMaxLimits) = 0;
  // Set the flag that indicates whether extrapolated geometry is to be taken into account
  virtual void SetCheckExtrapolatedGeometry(const CATBoolean iCheckExtrapolatedGeometry) = 0;
  // Set the flag that indicates whether maximum limits are to be checked
  virtual void SetCheckMaximumLimits(const CATBoolean iCheckMaximumLimits) = 0;

  //-----------------------------------------------------------------------
  //- Other methods
  //-----------------------------------------------------------------------
  // Run the operator.
  virtual void Run() = 0;

  //-----------------------------------------------------------------------
  //- Public test methods
  //-----------------------------------------------------------------------
  // Test to determine whether there are any changes in the sizes of
  // geometry classes for which the CompareGeometry() function is
  // implemented
  virtual CATBoolean TestGeometryClassSizes(CATBoolean & oIsGeometryClass,
                                            CATString  & oClassName,
                                            size_t     & oOriginalClassSize,
                                            size_t     & oCurrentClassSize) const = 0;

#ifdef DEBUG_COMPAREGEOMETRY
  // Output geometric entities to an NCGM file
  virtual void DebugOutputGeometryToNCGM(const CATCGMObject * const & iObject) const = 0;
#endif

protected:
  // Do not use the constructor directly. Instead use CreateCompareGeometry.
  CATCompareGeometry() {}

private:
  //------------------------------------------------------------------------
  // Forbidden (Declared, Not Defined) : Constructor by copy  et   operator =
  //------------------------------------------------------------------------
  CATCompareGeometry(const CATCompareGeometry &iCopy);
  CATCompareGeometry& operator=(const CATCompareGeometry &iCopy);
};

extern "C" { typedef CATCompareGeometry* CATCompareGeometry_Creator(const CATCompareContext * ioContext); }
#endif
