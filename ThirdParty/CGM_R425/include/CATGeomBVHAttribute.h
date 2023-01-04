// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATGeomBVHAttribute
//
//===================================================================
// 2011-03-06   JXO
//      * New
// August 2009 - Revisit Architecture -NDO
//===================================================================
#ifndef CATGeomBVHAttribute_H
#define CATGeomBVHAttribute_H
#include "BVHObjects.h"

// Poly
#include "CATBVHAttribute.h"

// System
#include "CATBoolean.h"

class CATCellId;

/**
 * Base class from which BVH attributes with geometric data derive.
 */
class ExportedByBVHObjects CATGeomBVHAttribute : public CATBVHAttribute
{
public:
  /**
   * Basic constructor.
   */
  CATGeomBVHAttribute () {}
  /**
   * Destructor.
   */
  virtual ~CATGeomBVHAttribute () {}

public:
  /**
   * Casting method.
   */
  virtual CATGeomBVHAttribute* CastAsGeomAttribute ();
  /**
   * Casting method.
   */
  virtual const CATGeomBVHAttribute* CastAsGeomAttribute () const;

  /**
   * Return wether this node contains a body (could be an exact or tesselated body, or whatever looks like a solid.)
   * Note: this is not necessarily of dimension 3. This could be a body containing only wires for example.
   */
  virtual CATBoolean HasBody()const {return FALSE;}
  /**
   * Return wether this node contains a cell of dimension 2.
   */
  virtual CATBoolean HasFace()const {return FALSE;}
  /**
   * Return wether this node contains a cell of dimension 1.
   */
  virtual CATBoolean HasEdge()const {return FALSE;}
  /**
   * Return wether this node contains a cell of dimension 0.
   */
  virtual CATBoolean HasPoints()const {return FALSE;}
  /**
   * If the attribute is relative to a body, return its dimension.
   * The dimension can be 0 for points, 1 for lines, 2 for surfaces or 3 for volumes.
   * If something went wrong, return a negative value.
   */
  virtual int GetBodyDimension() const {return -1;}

  /**
   * Returns the id associated to this geometry.
   * Call release on it after use.
   */
  virtual CATCellId * GetId()const {return 0;}

};

#endif
