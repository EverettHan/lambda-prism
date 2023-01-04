//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2011
//=============================================================================
//
// CATCompareGeometryOpe:
//    Header file for the operator associated with comparing geometries.
//
//=============================================================================
// Usage notes:
//=============================================================================
//   /04/11 XMH/R1Y Creation
//   /02/12 Q48 Added GetConfig function
//   /10/14 R1Y Added an option to check current-limits data
//   /11/16 R1Y Added an option to check the maximum limits for a circle
//   /12/16 R1Y Added an option for extrapolated surfaces
//   /01/17 R1Y Added an option to check maximum limits
//   /11/17 PKC ExportedByA3HGG not C3XGG
// 20/11/19 Q48 Small migration to use const
// 30/01/20 R1Y Added GetCheckCircleMaxLimits().
// 10/02/20 R1Y Renamed the option for extrapolated surfaces (to geometry).
// 14/02/20 R1Y Added GetSoftwareConfiguration() for CATMathDirtyCGMLevel().
//=============================================================================
#ifndef CATCompareGeometryOpe_H
#define CATCompareGeometryOpe_H

//#include "Y30C3XGG.h"
#include "Y30A3HGG.h"
#include "CATGeoOperator.h"
#include "CATCompareResult.h"

class CATCompareContext;

/**
 * Class defining the operator for comparing geometries.
 * <br> The operator returns 1 for success and 0 for failure.
 *<ul>
 *<li>The CATCompareGeometry operator is created with the <tt>CreateGeoOpTemplate</tt> method and 
 * directly <tt>delete</tt>d with the usual C++ delete operator.
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>Set</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method.
 *<li>In both cases, the result is accessed using <tt>GetResult()</tt>.
 *</ul>
 */
//class ExportedByY30C3XGG CATCompareGeometryOpe : public CATGeoOperator
class ExportedByY30A3HGG CATCompareGeometryOpe : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATCompareGeometryOpe);
 public:

 /** 
  * @nodoc
  * Do not use this constructor. Use the creation method
  * <tt>CreateCompareGeometry</tt>.
  */
   CATCompareGeometryOpe(CATGeoFactory * iFactory);

  virtual ~CATCompareGeometryOpe();

  //-----------------------------------------------------------------------
  //- Get methods
  //-----------------------------------------------------------------------
  
  // Get the software configuration
  virtual CATSoftwareConfiguration * GetConfig() const = 0;

  // Get the software configuration (an over-ride of the CATCGMOperator version for CATMathDirtyCGMLevel()) 
  CATSoftwareConfiguration * GetSoftwareConfiguration() const;

  // Get the first geoemetric entity that is to be compared
  virtual const CATGeometry * GetFirstGeometry() const = 0;

  // Get the second geometric entity that is to be compared
  virtual const CATGeometry * GetSecondGeometry() const = 0;

  // Get the flag that indicates whether current-limits data is to be checked
  virtual CATBoolean GetCheckCurrentLimits() const = 0;

  // Get the flag that indicates whether the maximum limits for a circle are to be checked
  virtual CATBoolean GetCheckCircleMaxLimits() const = 0;

  // Get the flag that indicates whether extrapolated geometry is to be taken into account
  virtual CATBoolean GetCheckExtrapolatedGeometry() const = 0;

  // Get the flag that indicates whether maximum limits are to be checked
  virtual CATBoolean GetCheckMaximumLimits() const = 0;

  // Get the context
  virtual const CATCompareContext * GetContext() const = 0;

  // Get the result
  virtual const CATCompareResult * GetResult() const = 0;

  // Get the outcome
  virtual CATCompareGeometryOutcome GetOutcome() const = 0;

  // Determine whether same geometries are being stored
  virtual CATBoolean GetStoreSameComparedGeometries() const = 0;

  // Get the number of entries in the repository of compared geometries that are the same
  virtual int GetNumSameComparedGeometries() const = 0;

  // Get the entry at a specified location (>= 0) in the repository of compared geometries that are the same
  virtual void GetSameComparedGeometries(const int             iLocation,
                                         const CATGeometry *& oGeometry1,
                                         const CATGeometry *& oGeometry2) const = 0;

 //-----------------------------------------------------------------------
  //- Set methods
  //-----------------------------------------------------------------------
  // Set the first geometric entity that is to be compared
  virtual void SetFirstGeometry(const CATGeometry * iGeometry1) = 0;

  // Set the second geometric entity that is to be compared
  virtual void SetSecondGeometry(const CATGeometry * iGeometry2) = 0;

  // Set the two geometric entities that are to be compared
  virtual void SetGeometries(const CATGeometry * iGeometry1, const CATGeometry * iGeometry2) = 0;

  // Set the flag that indicates whether current-limits data is to be checked
  virtual void SetCheckCurrentLimits(const CATBoolean iCheckCurrentLimits) = 0;

  // Set the flag that indicates whether the maximum limits for a circle are to be checked
  virtual void SetCheckCircleMaxLimits(const CATBoolean iCheckCircleMaxLimits) = 0;

  // Set the flag that indicates whether extrapolated geometry is to be taken into account
  virtual void SetCheckExtrapolatedGeometry(const CATBoolean iCheckExtrapolatedGeometry) = 0;

  // Set the flag that indicates whether maximum limits are to be checked
  virtual void SetCheckMaximumLimits(const CATBoolean iCheckMaximumLimits) = 0;

  // Indicate whether to store compared geometries that are the same
  virtual void SetStoreSameComparedGeometries(CATBoolean iStoreSameComparedGeometries) = 0;

  //-----------------------------------------------------------------------
  //- Other methods
  //-----------------------------------------------------------------------
  // Clear the repository of compared geometries that are the same
  virtual void ClearSameComparedGeometries() = 0;
};

ExportedByY30A3HGG CATCompareGeometryOpe * CreateCATCompareGeometry(CATGeoFactory * iFactory, CATCompareContext * ioContext);
#endif
