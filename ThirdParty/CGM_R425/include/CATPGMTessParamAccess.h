/* -*-C++-*- */

#ifndef CATPGMTessParamAccess_H
#define CATPGMTessParamAccess_H

// COPYRIGHT DASSAULT SYSTEMES 2018

//=============================================================================
//
// CATPGMTessParamAccess : 
// Class to access to default values of SAG as tessellation parameter
// The returned values depend on the scale and can be selected through an accuracy discrete level (enum)
// Those values may change in the future, depending on versionning mechanism 
//
//=============================================================================

#include "CATGMModelInterfaces.h" // ExportedBy

#include "CATCGMScaleCategoryDef.h"
#include "CATBoolean.h"
#include "CATSysBoolean.h"
#include "CATSysErrorDef.h"

#ifndef NULL
#define NULL 0
#endif

class CATSoftwareConfiguration;
class CATGeoFactory;
class CATTolerance;

/**
 * Tessellation Accuracy as a discrete value instead of a double.
 * The associated double values will depend on the current scale and may change over time
 * Those potential changes will be managed by a versionning mechanism
 * 
 * @param FineTessAccuracy
 *   small deviation between exact and tessellated data :
 * This mode is not recommended for good performances, 
 * and may fail if the precision of the original model is not good enough
 * (in case of gaps, overlaps greater than the demanded accuracy, etc...)
 *
 * @param OptimizedTessAccuracy
 *   recommended, best compromise between performances and precision
 *   this medium value guarantees that the maximum deviation between the exact and tessellated data 
 *   will be consistent with the tolerant resolution of the CGM modeler :
 *   see CATTolerance::LargeResolutionForLengthTest(), 0.1mm for NormalScale
 *
 * @param CoarseTessAccuracy  
 *   high deviation between exact and tessellated data : 
 *   -> speeds up the computation and reduces the number of generated triangles
 * This mode is not recommended for a nice visualisation
*/
enum CATGMTessAccuracyLevel
{
  FineTessAccuracy = 0,
  OptimizedTessAccuracy, 
  CoarseTessAccuracy,
};


/**
* Class to access to default values of tessellation parameters
*/
class ExportedByCATGMModelInterfaces CATPGMTessParamAccess
{

public :
  
  /**
  * Destructor, to call directly to remove an instance of this class
  */
  virtual ~CATPGMTessParamAccess();

  /**
  * Set the Software Configuration
  * @param iConfig
  *   Optional software configuration to manage the potential changes of values over time
  *   a Null pointer is equivalent to an open configuration with the last level of implementation (best so far)
  */
  virtual void SetSoftwareConfiguration(CATSoftwareConfiguration * iConfig) = 0;

  /**
  * Get the absolute SAG values, depending on the contextual range / scale
  * returns E_FAIL if the range / scale is undefined
  */
  virtual HRESULT GetAccuracySagValue(CATGMTessAccuracyLevel iAccuracyLevel, double & oSAGValue) = 0;

  virtual HRESULT GetOptimizedSagValue(double & oSAGValue) = 0;

  virtual HRESULT GetMinMaxSagValues(double & oMinSAGValue, double & oMaxSAGValue) = 0;

  virtual CATBoolean IsUpToDate() = 0;


  /**
  * Retrieve inputs
  */

  virtual CATSoftwareConfiguration * GetSoftwareConfiguration() = 0;

  virtual CATCGMScaleCategory GetScaleCategory() = 0;

  virtual const CATTolerance & GetCGMTolerance() = 0;


protected :
  
  CATPGMTessParamAccess();
};

/**
* Constructs an instance of CATPGMTessParamAccess.
* @param iGeoFactory
*   The mandatory pointer to the CATGeoFactory instance building the bodies to tessellate.
*   a Null pointer is forbidden and leads to not create any CATPGMTessParamAccess instance !
* @param iConfig
*   Optional software configuration to manage the potential changes of values over time
*   a Null pointer is equivalent to an open configuration with the last level of implementation (best so far)
* Please delete this instance after use
*/
ExportedByCATGMModelInterfaces CATPGMTessParamAccess * CATPGMCreateTessParamAccess(CATGeoFactory * iGeoFactory, CATSoftwareConfiguration * iConfig=NULL);

/**
* Constructs an instance of CATPGMTessParamAccess.
* @param iScaleCategory
*   The Category of scale of bodies to tessellate.
*   ScaleNotSet value is forbidden and leads to not create any CATPGMTessParamAccess instance !
* Please delete this instance after use
*/
ExportedByCATGMModelInterfaces CATPGMTessParamAccess * CATPGMCreateTessParamAccess(CATCGMScaleCategory iScaleCategory);

#endif

//===========================================================================================================
