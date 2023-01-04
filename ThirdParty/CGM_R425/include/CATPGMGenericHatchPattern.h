#ifndef CATPGMGenericHatchPattern_H
#define CATPGMGenericHatchPattern_H

//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 2011
//
// CATPGMGenericHatchPattern
//
// DESCRIPTION :
//
//    Description of a Generic Hatch Pattern,
//    composed by a set of Hatch SubPatterns (full lines or dashed lines patterns)
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


//============================================================
// Includes
//------------------------------------------------------------ 

#include "CATPGMHatchPattern.h"        // derivation
#include "CATGMOperatorsInterfaces.h"  // ExportedBy


/**
* Class defining a generic Hatch Pattern, as a set of SubPatterns.
* Each SubPattern is itself a layer of dashed line pattern to apply on a set of lines
* <li>CATPGMGenericHatchPattern is created with the <tt>CATPGMCreateGenericHatchPattern</tt> global function.
* It can be reused for different Hatching computations.
* @see CATPGMCreateGenericHatchPattern at the end of this header
*/

class ExportedByCATGMOperatorsInterfaces CATPGMGenericHatchPattern : public CATPGMHatchPattern
{

public:

 /**
  * Life Cycle Management
  * PLEASE USE THE CATPGMCreateGenericHatchPattern() GLOBAL FUNCTION TO INSTANCIATE THE OPERATOR
  * PLEASE USE delete function TO REMOVE THE OPERATOR INSTANCE
  */
  virtual ~CATPGMGenericHatchPattern() {};


public:

 /** @name Accessors to define the current sub-element of the pattern.
  * This current element is a SubPattern defined as a set of full lines or dashed lines patterns
  @{ */

 /**
  * Adds and defines a new SubPattern of a Hatch Pattern
  * This SubPattern is a pattern of full lines or dashed lines patterns
  * @param iAngle
  *   angle (degrees) defining the rotation to apply on the planar reference axes
  * @param iOrigin
  *   planar coordinates X, Y (before rotation) to define the line support reference
  * @param iOffset
  *   Offset values X & Y to apply (after rotation) to compute the next instance of line support
  *   Offset value X is the offset along the line reference and doesn't matter in case of full lines
  *   Offset value Y is the distance between 2 successive line support instances
  * @param iDashedLinePattern
  *   successive values of Lengths and EmptySpaces to define the dashed lines pattern
  *   no value means full lines !
  *   a positive value defines the length of a segment to draw (dash)
  *   a null value means a dot to draw on the line support
  *   a negative value defines the length of the empty space between 2 successive elements (dot or dash)
  *   sample : { 3., -2., 0., -2. } means ___  .  ___  .  ___  .  ___  .  ___  .
  */
  virtual void AddGenericHatchSubPattern(double iAngle, CATMathPoint2D &iOrigin, double iOffset[2], CATListOfDouble &iDashedLinePattern) = 0;

 /** @} */

};

// =======================================================================================================================================================

/**
 * Creates a generic hatch pattern to be applied on a given CATFace
 * <br>The constructor generates a CATPGMGenericHatchPattern instance
 *   To be removed with the <tt>delete</tt> method.
 * @see CATPGMGenericHatchPattern
 */

ExportedByCATGMOperatorsInterfaces
CATPGMGenericHatchPattern * CATPGMCreateGenericHatchPattern();


#endif
