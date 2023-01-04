//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// Filter that sets and gets gridded vertex positions.
//
//=============================================================================
// 2008-07-21   NDO: New
//=============================================================================
#ifndef CATPolyGriddedPositionsConst_H
#define CATPolyGriddedPositionsConst_H

#include "PolyMathArithmetic.h"
#include "CATErrorDef.h" // HRESULT

class CATPolyExactArithmetic;


class ExportedByPolyMathArithmetic CATPolyGriddedPositionsConst
{

public:

  CATPolyGriddedPositionsConst (const CATPolyExactArithmetic& iExactArithmetic);

  virtual ~CATPolyGriddedPositionsConst ();

public:

  // Return the instance of exact arithmetic used for the gridding.
  inline const CATPolyExactArithmetic& GetExactArithmetic () const;

public:

  // Return a gridded vertex position.
  virtual HRESULT Get (int v, double &x, double &y, double &z) const = 0;

protected:

  const CATPolyExactArithmetic& _ExactArithmetic;

};


inline const CATPolyExactArithmetic& CATPolyGriddedPositionsConst::GetExactArithmetic () const
{
  return _ExactArithmetic;
}

#endif // !CATPolyGriddedPositionsConst_H
