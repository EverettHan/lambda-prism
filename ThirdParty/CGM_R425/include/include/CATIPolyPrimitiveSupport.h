// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyPrimitiveSupport.h
//
//===================================================================
// May 2011  Creation: NDO
//===================================================================
#ifndef CATIPolyPrimitiveSupport_H
#define CATIPolyPrimitiveSupport_H

#include "PolyhedralAttributes.h"
#include "CATIPolySupport.h"

class CATPolyBoxSupport;
class CATPolySphereSupport;
class CATPolyCylinderSupport;
class CATPolyConicCapsuleSupport;


/**
 * A CATIPolyPrimitiveSupport is an attribute to a CATPolyBody.
 * It defines the support as primitive (box, sphere, cylinder or capsule.)
 */
class ExportedByPolyhedralAttributes CATIPolyPrimitiveSupport : public CATIPolySupport
{

public:

  virtual ~CATIPolyPrimitiveSupport () {}

public:

  /**
   * Returns the type of the support.
   */
  Type GetType () const;

public:

  /**
   * Casts the support as a box support.
   */
  virtual const CATPolyBoxSupport* CastAsBoxSupport () const;

  /**
   * Casts the support as a sphere support.
   */
  virtual const CATPolySphereSupport* CastAsSphereSupport () const;

  /**
   * Casts the support as a cylinder support.
   */
  virtual const CATPolyCylinderSupport* CastAsCylinderSupport () const;

  /**
   * Casts the support as a conic-capsule support.
   */
  virtual const CATPolyConicCapsuleSupport* CastAsConicCapsuleSupport () const;

public:

  const CATIPolyPrimitiveSupport* CastAsPrimitive () const;
  CATIPolyPrimitiveSupport* CastAsPrimitive ();

protected:

  CATIPolyPrimitiveSupport () {}

};

#endif // !CATIPolyPrimitiveSupport_H
