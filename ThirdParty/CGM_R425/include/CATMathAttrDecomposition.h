// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATMathAttrDecomposition
// Class used to define the mode of decomposition of the dimension for
// a sampled curve.
//
//=============================================================================
//
// Usage notes:
// The curve may be parametric (t->M(t)) or implicit (F(X)=0).
// The decomposition of the dimension allow, for example,to have a best
// angular control during the sampling of the curve.
//=============================================================================


#ifndef CATMathAttrDecomposition_H
#define CATMathAttrDecomposition_H

#include "YN000FUN.h"
#include "CATMathAttribute.h"

//-----------------------------------------------------------------------------
class ExportedByYN000FUN CATMathAttrDecomposition : public CATMathAttribute
{
  public:
//--------------
//  Constructors
//---------------
  // iNumber = The number of subsets that you want
  // Tab = array of the repartition giving the count of coordinates
  // in each subset. Ex: for two subsets of 2 coordinates in dimension 4,
  //  Tab[0] = 2; Tab[1] = 2.
CATMathAttrDecomposition (const CATLONG32 iNumber, CATLONG32 *Tab);
//--------------
//  Destructors
//---------------
~CATMathAttrDecomposition ();
//---------------
//  Other Methods
//---------------
CATMathAttrId GetType() const;
CATBoolean IsExclusive() const;

CATLONG32  GetDecompositionNumber () const;
const CATLONG32 *GetDecompositionTab () const;

private:
  CATLONG32 _NumberOfDecomposition;
  CATLONG32 *_TabOfDecomposition;
};

#endif
