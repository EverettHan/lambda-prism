#ifndef CATMathConstraintOption_H
#define CATMathConstraintOption_H

// COPYRIGHT DASSAULT SYSTEMES  1999


#include "YN000FUN.h"

#include "CATMathAttribute.h"
#include "CATMathDef.h"

class ExportedByYN000FUN CATMathConstraintOption : public CATMathAttribute
{
 public:
  virtual ~CATMathConstraintOption();
  CATMathAttrId GetType() const { return "CATMathConstraintOption"; }
  CATBoolean IsExclusive() const { return 1; }
};

#endif
