// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyCoodinatesSystemUtil.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// Sep 2009 Creation: zfi
//===================================================================

#ifndef CATPolyCoodinatesSystemUtil_H
#define CATPolyCoodinatesSystemUtil_H

#include "PolyMathContainers.h"

#include "CATErrorDef.h"
#include "CATMathVector.h"


class ExportedByPolyMathContainers CATPolyCoodinatesSystemUtil
{
public:
  CATPolyCoodinatesSystemUtil();
  virtual ~CATPolyCoodinatesSystemUtil();


public :
  static HRESULT CompleteBasis(const CATMathVector& iW,
                               CATMathVector& oU,
                               CATMathVector& oV);

  static double GetOrientedAngle(const CATMathVector& iX,
                                 const CATMathVector& iY,
                                 const CATMathVector& iVec);

  static double GetAngle(const CATMathVector& iX,
                         const CATMathVector& iY,
                         const CATMathVector& iVec);                                        
  
};

#endif
