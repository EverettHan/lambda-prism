#ifndef CATPGMHatchFaceResultIter_H
#define CATPGMHatchFaceResultIter_H
#include "CATIAV5Level.h"
#if defined (CATIAV5R23) || defined (CATIAR213)

//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 2012
//
// CATPGMHatchFaceResultIter
//
// DESCRIPTION :
//
//               Hatching iterator to get all the dots and dashes
//
//=============================================================================
// Abstract Class     : YES
//
// History
//
// February. 2012   Dominique PREVOST (DPS)    Creation    
//
//=============================================================================

#include "CATGMOperatorsInterfaces.h"  // ExportedBy
 
#include "CATBoolean.h"                // define

class CATMathPoint2D;
class CATPGMHatchFaceResult;


/**
* Class defining the iterator that returns all the hatching dots and dashes
*<ul>
* <li>CATPGMHatchFaceResultIter is created with the <tt>CATPGMHatchFaceResult::CreateHatchFaceResultIter</tt> method.
* It can be reused several times thanks to the <tt>Begin</tt> method
* It must be directly removed with the <tt>delete</tt> method after use.
* It is not streamable.
* @see CATPGMHatchFaceResult
*/

class ExportedByCATGMOperatorsInterfaces CATPGMHatchFaceResultIter
{

public:

 /**
  * Life Cycle Management
  * No constructor, PLEASE USE THE CATPGMHatchFaceResult::CreateHatchFaceResultIter METHOD TO INSTANCIATE THE OPERATOR
  * PLEASE USE delete function TO REMOVE THE OPERATOR INSTANCE
  */
  virtual ~CATPGMHatchFaceResultIter() {};


public:

 /** @name Iterator Interface
  @{ */

 /**
  * Resets the iterator for a new iteration through the dots and dashes.
  * This method may be called several times.
  */
  virtual void Begin () = 0;

  virtual CATBoolean End () = 0;

  virtual void operator++ () = 0;

 /** @} */


public:

 /** @name Accessors to the elements composing the result.
  @{ */

 /**
  * Returns the dimension of the element:
  * <ul>
  *   0 Dot
  *   1 Dash
  * </ul>
  */
  virtual int GetDimension() = 0;

 /**
  * Returns a dot element.
  */
  virtual void GetDot (CATMathPoint2D& oDot) = 0;

 /**
  * Returns a dash element defined by its two extremities
  */
  virtual void GetDash (CATMathPoint2D& oDashStart, CATMathPoint2D& oDashEnd) = 0;

 /** @} */

};

#endif
#endif
