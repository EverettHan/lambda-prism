// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyPointSupport.h
//
//===================================================================
// March 2009  Creation: NDO
//===================================================================
#ifndef CATIPolyPointSupport_H
#define CATIPolyPointSupport_H

#include "PolyhedralAttributes.h"
#include "CATIPolySupport.h"

class CATPolyCGMVertexSupport;


/**
 * A CATIPolyPointSupport is an attribute to a CATIPolyPoint.
 */
class ExportedByPolyhedralAttributes CATIPolyPointSupport : public CATIPolySupport
{

public:

  virtual ~CATIPolyPointSupport () {}

public:

  /**
   * Returns the type of the support.
   */
  Type GetType () const;

  /**
   * Casts the support as a CGM vertex.
   */
  virtual const CATPolyCGMVertexSupport* CastAsCGMVertex () const;

public:

  const CATIPolyPointSupport* CastAsPoint () const;
  CATIPolyPointSupport* CastAsPoint ();

protected:

  CATIPolyPointSupport () {}

};


#endif // !CATIPolyPointSupport_H
