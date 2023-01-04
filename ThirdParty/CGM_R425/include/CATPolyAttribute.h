// COPYRIGHT DASSAULT SYSTEMES 2005, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyAttribute.h
//
//===================================================================
// April 2005 Creation: ndo
//===================================================================
#ifndef CATPolyAttribute_H
#define CATPolyAttribute_H

#include "PolyhedralAttributes.h"
#include "CATIPolyLayer.h"
#include "CATErrorDef.h"     // HRESULT definition
#include "CATIPolyMesh.h"    // Obsolete CATPolyAttributeID


// DEPRECATED.  DO NOT USE.
class ExportedByPolyhedralAttributes CATPolyAttribute : public CATIPolyLayer
{

public :

  inline CATPolyAttribute () {}

  virtual ~CATPolyAttribute () {}

  inline CATPolyAttributeID GetID () const;

};


inline CATPolyAttributeID CATPolyAttribute::GetID () const
{
  return ePolyVertexNormal;
}


#endif
