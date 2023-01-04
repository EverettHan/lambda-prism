// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBoxSupport.h
//
//===================================================================
// 2010-09-21  XXC: Creation
// 2011-05-17  NDO: Revisited
//===================================================================
#ifndef CATPolyBoxSupport_H
#define CATPolyBoxSupport_H

#include "PolySupports.h"
#include "CATIPolyPrimitiveSupport.h"
#include "CATPolyMathCylinderSurface.h"
#include "CATMathOBB.h"

class CATMathBox;


/**
 * Class implementing a support as a box primitive.
 */
class ExportedByPolySupports CATPolyBoxSupport : public CATIPolyPrimitiveSupport
{

public:

  /**
   * Constructs of a CATPolyBoxSupport from a CATMathBox.
   */
  CATPolyBoxSupport (const CATMathBox& iBox);

  /**
   * Constructs a CATPolyBoxSupport from a CATMathOBB.
   */
  CATPolyBoxSupport (const CATMathOBB& iBox);

  virtual ~CATPolyBoxSupport () {}

public:

  static const CATPolyBoxSupport* Cast (const CATIPolyLayer*);
  static CATPolyBoxSupport* Cast (CATIPolyLayer*);

  static const CLSID& ClassID ();
  const CLSID& GetClassID () const;

public:

  inline const CATMathOBB& GetOBB () const;

public:

  Type GetType () const;
  const CATPolyBoxSupport* CastAsBoxSupport () const;

protected:

  CATMathOBB _OBB;

};

const CATMathOBB& CATPolyBoxSupport::GetOBB () const
{
  return _OBB;
}

#endif // !CATPolyBoxSupport_H
