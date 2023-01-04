#ifndef CATMathSingularity_H
#define CATMathSingularity_H

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "YN000FUN.h"

#include "CATMathAttribute.h"
#include "CATMathInterval.h"
#include "CATMathDef.h"

class ExportedByYN000FUN CATMathSingularity : public CATMathAttribute
{
 public:
  virtual ~CATMathSingularity();
  CATMathAttrId GetType() const { return "CATMathSingularity"; }
  CATBoolean IsExclusive() const { return 1; }
};

#endif
