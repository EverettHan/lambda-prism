// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATCGMTessID
//
//===================================================================
//
// August 2010  Creation: NDO
//===================================================================
#ifndef CATCGMTessID_H
#define CATCGMTessID_H

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATMathInline.h"

class CATCGMTessBody; 


/**
* Class defining a tessellation ID. 
*
* A CATCGMTessID is a small object that can be used efficiently to say if the tessellation of a CATCell has changed or not after some operation 
* on a CATBody.  To obtain the CATCGMTessID associated to a CATCell, see the method GetTessID () from CATCGMTessBody.
*
* A CATCGMTessID identifies the tessellation of a CATCell within its CATBody context.  It is unique to a specific tessellation
* of a CATCell.  A cell having two distinct CATCGMTessID (for example a shared cell between two distinct bodies) means 
* that it is tessellated differently. If the CATCGMTessID-s are identical, then the tessellation of the CATCell is the same 
* in the two contexts.
*
* Instances of CATCGMTessID can be copied.  Default, copy constructor and assignment operator are provided.  No other constructor are supported.
* 
* This class supports the <tt> operator == </tt> and <tt> operator != </tt>.  It also supports <tt> operator </tt> for storage of CATCGMTessID 
* in associative arrays and trees requiring a comparison operator.
*
* A CATCGMTessID cannot be streamed.
*/
class ExportedByCATGMModelInterfaces CATCGMTessID
{

public:

  /**
   * Default constructor.
   */
  CATCGMTessID ();

  /**
   * Copy constructor.
   */
  CATCGMTessID (const CATCGMTessID& iRHS);

  ~CATCGMTessID ();

  /**
   * Assignment operator.
   */
  CATCGMTessID& operator = (const CATCGMTessID& iRHS);

public:

  /**
   * Compares two CATCGMTessID-s.
   *
   * Two CATCGMTessID-s are equal when the tessellations of the CATCell refer to the same data.
   * The CATCGMTessID obtained for two distinct CATCell-s (regardless of their body and factory context) cannot be equal 
   * (even though the tessellated data may be equivalent.)
   */
  int operator == (const CATCGMTessID& iRHS) const;

  /**
   * Compares two CATCGMTessID-s.
   */
  int operator != (const CATCGMTessID& iRHS) const;

  /**
   * Compares two CATCGMTessID-s.
   * 
   * This operator may be used to store CATCGMTessID in associative arrays and sets such as a binary tree.
   * It's only specifications are: antisymmetry and transitivity.
   */
  int operator < (const CATCGMTessID& iRHS) const;

  /**
   * Returns a 32-bit hash key of the CATCGMTessID.
   * The hash key of two distinct CATCGMTessID may be equal.
   */
  int GetHashCode () const;

protected:

  CATCGMTessBody* _TessBody;

  const void* _DataHandle;
  int _Orientation;

};

#endif // !CATCGMTessID_H
