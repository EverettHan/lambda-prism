#ifndef CATPGMHatchFaceResult_H
#define CATPGMHatchFaceResult_H
#include "CATIAV5Level.h"
#if defined (CATIAV5R23) || defined (CATIAR213)

//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 2012
//
// CATPGMHatchFaceResult
//
// DESCRIPTION :
//
//               Hatching result which contains all the segments and dots
//               computed from a HatchPattern inside a face
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
class CATPGMHatchFaceResultIter;


/**
* Class defining the Hatching result containing all the segments and dots
*<ul>
* <li>CATPGMHatchFaceResult is instanciated through the <tt>CATPGMHatchFaceOperator::Run</tt> method.
* It can be kept by the user even if the operator is removed, but it must be directly removed with the <tt>delete</tt> method after use.
* It is not streamable. 
* @see CATPGMHatchFaceResultIter
*/

class ExportedByCATGMOperatorsInterfaces CATPGMHatchFaceResult
{

public:

 /**
  * Life Cycle Management
  * No constructor, this class is instanciated by the CATPGMHatchFaceOperator during the Run() computation.
  * PLEASE USE delete function TO REMOVE THE OPERATOR INSTANCE
  */
  virtual ~CATPGMHatchFaceResult() {};


 /**
  * Creates a CATPGMHatchFaceResultIter instance 
  * <br>The constructor generates a CATPGMHatchFaceResultIter instance
  * -> allows to use several iterators at the same time (one for dots and another one for dashes for example)
  * -> to be removed by the caller before the CATPGMHatchFaceResult instance deletion
  * @param iSkipDots
  *              -> to skip all the dots and get only the dashes
  *              -> GetDimension() calling is not required if iSkipDots is TRUE
  * @param iSkipDashes
  *              -> to skip all the dashes and get only the dots
  *              -> GetDimension() calling is not required if iSkipDashes is TRUE
  * Returns NULL if both iSkipDots & iSkipDashes are TRUE
  * To be removed with the <tt>delete</tt> method.
  * @see CATPGMHatchFaceResultIter
  */
  virtual CATPGMHatchFaceResultIter * CreateHatchFaceResultIter(CATBoolean iSkipDots=FALSE, CATBoolean iSkipDashes=FALSE)=0;

};

#endif
#endif
