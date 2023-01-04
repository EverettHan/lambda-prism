#ifndef CATPGMHatchPattern_H
#define CATPGMHatchPattern_H

//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 2011
//
// CATPGMGenericHatchPattern
//
// DESCRIPTION :
//
//    Interface defining an agnostic Hatch Pattern,
//    A hatch pattern is defined as an iterator through a list of lines (or dashed lines) elements.
//    This interface iterates throught all the elements of the pattern.
//
//=============================================================================
// Abstract Class     : YES
//=============================================================================
//
// History
//
// December. 2011   Dominique PREVOST (DPS) / Nicolas DUSAUSSOY (NDO)  Creation    
//
//=============================================================================

//============================================================
// Includes
//------------------------------------------------------------ 

#include "CATGMOperatorsInterfaces.h"  // ExportedBy
#include "CATBoolean.h"
#include "CATListOfDouble.h"

class CATMathPoint2D;


/**
* Class defining an agnostic Hatch Pattern
* This interface iterates throught all the sub-elements of the pattern.
* Each SubPattern is itself a layer of dashed line pattern to apply on a set of lines
* This class has to be derivated to be instanciated
* @see CATPGMGenericHatchPattern (default derivation for all generic Hatch Patterns)
*/

class ExportedByCATGMOperatorsInterfaces CATPGMHatchPattern 
{

public:

 /**
  * Life Cycle Management
  * PLEASE USE derivated class (default class is CATPGMGenericHatchPattern) to instanciate the Pattern
  * PLEASE USE delete function TO REMOVE THE OPERATOR INSTANCE
  */
  virtual ~CATPGMHatchPattern() {};


public:

/** @name Iterator Interface
  @{ */

 /**
  * Sets the iterator to the beginning.
  * Resets the iterator for a new iteration.
  * This method may be called several times.
  */
  virtual void Begin () = 0;

 /**
  * Checks if the iterator reached the end.
  */
  virtual CATBoolean End () = 0;

 /**
  * Increments the iterator.
  */
  virtual void operator++ () = 0;

 /** @} */


public:

 /** @name Accessors to the current sub-element of the pattern.
  * This current element is a SubPattern defined as a set of full lines or dashed lines patterns
  @{ */

 /**
  * returns the angle (degrees) defining the rotation to apply on the planar reference axes
  */
  virtual double GetAngle () = 0;

 /**
  * returns the planar coordinates X,Y (before rotation) to define the line support reference
  */
  virtual void GetOrigin (CATMathPoint2D& oOrigin) = 0;

 /**
  * returns the Offset values X & Y to apply (after rotation) to compute the next instance of line support
  *   Offset value X is the offset along the line reference and doesn't matter in case of full lines
  *   Offset value Y is the distance between 2 successive line support instances
  */
  virtual void GetOffset (double oOffset[2]) = 0;

 /**
  * returns the successive values of Lengths and EmptySpaces defining the dashed lines pattern
  * no value means full lines !
  * a positive value defines the length of a segment to draw (dash)
  * a null value means a dot to draw on the line support
  * a negative value defines the length of the empty space between 2 successive elements (dot or dash)
  * sample : { 3., -2., 0., -2. } means ___  .  ___  .  ___  .  ___  .  ___  .
  */
  virtual CATBoolean GetDashedLinePattern (CATListOfDouble& oDashedLinePattern) = 0;

/** @} */

};

#endif
