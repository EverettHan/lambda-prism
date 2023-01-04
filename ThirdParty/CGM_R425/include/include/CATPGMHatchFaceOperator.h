/* -*-C++-*-*/
#ifndef CATPGMHatchFaceOperator_H
#define CATPGMHatchFaceOperator_H

//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES 2011
//
// CATPGMHatchFaceOperator
//
// DESCRIPTION :
//
//               Apply the Hatching on a CATFace with a set of dashed line patterns
//               to compute a result as a set of parametric dots and dashes
//
//=============================================================================
// Abstract Class     : YES
//=============================================================================
//
// History
//
// December. 2011   Dominique PREVOST (DPS)    Creation    
//
//=============================================================================


#include "CATGMOperatorsInterfaces.h"  // ExportedBy

#include "CATErrorDef.h"               // HRESULT define
#include "CATBoolean.h"
#include "CATSysBoolean.h"

class CATPGMHatchFaceResult;
class CATPGMHatchPattern;

class CATFace;
class CATSoftwareConfiguration;

/**
* Class defining the operator that applies the Hatching on a CATFace from a set of dashed line patterns
* The returned result is a set of parametric (2D) dots and dashes.
* The input face is never modified by the operator. 
*<ul>
* <li>CATPGMHatchFaceOperator is created with the <tt>CATPGMCreateHatchFaceOperator</tt> global function.
* It can be reused for different Hatching parameters.
* It must be directly removed with the <tt>delete</tt> method after use.
* It is not streamable. 
* <li>The Hatching can be limited or not to a given area from the face boundaries with the methods
* <tt>DefineALimitingBorderStrip</tt> and <tt>UnsetLimitingBorderStrip</tt>
*<li>The CATPGMHatchFaceResult data instance is accessed through the <tt>Run</tt> method. 
* It can be kept by the user even if the operator is removed, but it must be directly removed with the <tt>delete</tt> method after use.
*</ul>
* @see CATPGMCreateHatchFaceOperator at the end of this header
*/

class ExportedByCATGMOperatorsInterfaces CATPGMHatchFaceOperator
{

public:

 /**
  * Life Cycle Management
  * PLEASE USE THE CATPGMCreateHatchFaceOperator() GLOBAL FUNCTION TO INSTANCIATE THE OPERATOR
  * PLEASE USE delete function TO REMOVE THE OPERATOR INSTANCE
  */
  virtual ~CATPGMHatchFaceOperator() {};


 /** @name Main Method
  @{ */

 /**
  * Runs the operator for a given hatch pattern.
  * @param iPattern
  *   The hatch pattern to apply to the face.
  * @param oResult
  *   An output argument with the result of the operation.
  *   The returned object must be deleted by the caller.
  * @param iAngle
  *   The angle of the pattern with the first axis in degrees.
  * @param iScale
  *   The scaling of the pattern. A larger scale means a bigger pattern is applied.
  * @return
  * <ul>
  *   <li> <tt>S_OK</tt> if the operator runs successfully.
  *   <li> <tt>E_FAIL</tt> if an error occurs.
  * </ul>
  */
  virtual HRESULT Run (CATPGMHatchPattern& iPattern, CATPGMHatchFaceResult*& oResult,
                       double iAngle=0., double iScale=1.) = 0;

 /** @} */

public: 


 /** @name Settings
  @{ */

 /**
  * Defines a strip to limit the hatching area from the boundary
  * @param iStripWidth
  *   A positive value defining the hatching area inside the face.
  *   A negative value defining the hatching area outside the face.
  * @param iRoundedOffsetMode
  *   Drives the offset behavior on concave (resp. convexe) sharp border vertices in case of positive (resp. negative) width value
  *   TRUE leads to create a circular arc (according to the Minkowsky offset specification),
  *   FALSE leads to create a sharp vertex computed by extrapolation (in this case, the width value is not respected).
  */
  virtual void DefineALimitingBorderStrip (double iStripWidth, CATBoolean iRoundedOffsetMode=TRUE) = 0;

 /**
  * Unsets the Strip.  Hatching will occur on the full face.
  * This is the default setting.
  */
  virtual void UnsetLimitingBorderStrip () = 0;

 
 /**
  * Enable/Disable the option to set the precision
  * @param iEnabledApproximation
  *   The result will be conformed in respect with (cf CATTolerance.h) :
  *     -> the strict tolerance resolution if the option is disabled (default behavior)
  *     -> the large tolerance resolution if the option is enabled 
  * The performances depend on this option : to speed up the hatching, activate the ApproximationMode
  */
  virtual void SetApproximationMode(CATBoolean iEnabledApproximation=TRUE) = 0;

 /** @} */

};

// =======================================================================================================================================================

/**
 * Creates an operator to apply the hatching on a given CATFace
 * <br>The constructor generates a CATHatchFaceOperator instance
 * @param iFace
 *   The pointer to the topological face defining the area to hatch.
 *   Its geometrical support (parametric CATSurface) imposes its own reference system 2D
 *   for both the Haching Pattern definition and the Hatching Result.
 * @param iConfig
 *   Versioning management (BestSoFar if not)
 * @return
 *   The pointer to the created operator ( NULL if iFace is NULL). 
 *   To be removed with the <tt>delete</tt> method.
 * The result will be conformed to the tolerance resolution (large resolution in case of approximate mode) included in the face container
 * @see CATPGMHatchFaceOperator
 */

ExportedByCATGMOperatorsInterfaces CATPGMHatchFaceOperator * CATPGMCreateHatchFaceOperator(CATFace                  * iFace, 
                                                                                           CATSoftwareConfiguration * iConfig);

#endif
