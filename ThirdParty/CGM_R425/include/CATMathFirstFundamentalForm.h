#ifndef CATMathFirstFundamentalForm_H
#define CATMathFirstFundamentalForm_H

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "YN000ANL.h"
#include "CATMathVector.h"

ExportedByYN000ANL void FirstFundamentalForm(const CATMathVector & FirstDeriv, 
                                             const CATMathVector & SecondDeriv,
                                             double & E, double & F, double & G);

#endif
