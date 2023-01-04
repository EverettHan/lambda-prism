// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATCGMTessellateID
//
//===================================================================
//
// October 2013  Creation: TPG
//===================================================================
#ifndef CATCGMTessellateID_H
#define CATCGMTessellateID_H

/**
 * @C_A_A_2_Level L1
 * @C_A_A_2_Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATCGMRefCounted.h"
#include "CATBoolean.h"

/**
* Class defining a tessellation ID. 
*
* A CATCGMTessellateID identifies the tessellation of a CATCell within its CATBody context.  It is unique to a specific tessellation
* of a CATCell.  A cell having two distinct CATCGMTessellateID (for example a shared cell between two distinct bodies) means 
* that it is tessellated differently. If the CATCGMTessellateID-s are identical, then the tessellation of the CATCell is the same 
* in the two contexts.
*
* The object is ref-counted.
*/
class ExportedByCATGMModelInterfaces CATCGMTessellateID : public CATCGMRefCounted
{

public:

  /**
   * Default constructor.
   */
  CATCGMTessellateID ();
  
	/**
   * Copy constructor.
   */
  CATCGMTessellateID (const CATCGMTessellateID& iRHS);

  /**
   * Destructor
   */
  virtual ~CATCGMTessellateID ();

  /**
   * Assignment operator.
   */
  virtual CATCGMTessellateID& operator = (const CATCGMTessellateID& iRHS) = 0;

public:

  /**
   * Compares two CATCGMTessellateID-s.
   *
   * Two CATCGMTessellateID-s are equal when the tessellations of the CATCell refer to the same data.
   * The CATCGMTessellateID obtained for two distinct CATCell-s (regardless of their body and factory context) cannot be equal 
   * (even though the tessellated data may be equivalent.)
   */
  virtual int operator == (const CATCGMTessellateID& iRHS) const = 0;

  /**
   * Compares two CATCGMTessellateID-s.
   */
  virtual int operator != (const CATCGMTessellateID& iRHS) const = 0;

  /**
   * Compares two CATCGMTessellateID-s.
   * 
   * This operator may be used to store CATCGMTessellateID in associative arrays and sets such as a binary tree.
   * It's only specifications are: antisymmetry and transitivity.
   */
  virtual int operator < (const CATCGMTessellateID& iRHS) const = 0;

  /**
   * Compares the settings of two CATCGMTessellateID-s.
   */
  virtual CATBoolean AreSettingsEqual(const CATCGMTessellateID& iRHS) const;

};

#endif // !CATCGMTessellateID_H
