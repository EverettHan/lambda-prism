//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// Filter that sets and gets gridded vertex positions.
//
//=============================================================================
// 2008-07-21   NDO: New
//=============================================================================
#ifndef CATPolyGriddedPositions_H
#define CATPolyGriddedPositions_H

#include "PolyMathArithmetic.h"
#include "CATPolyGriddedPositionsConst.h"
#include "CATErrorDef.h"

class CATPolyExactArithmetic;


class ExportedByPolyMathArithmetic CATPolyGriddedPositions : public CATPolyGriddedPositionsConst
{

public:

  CATPolyGriddedPositions (const CATPolyExactArithmetic& iExactArithmetic);

  virtual ~CATPolyGriddedPositions ();

public:

  // Set a gridded vertex position.
  virtual HRESULT Set (int v, double x, double y, double z) = 0;

};

#endif // !CATPolyGriddedPositions_H
