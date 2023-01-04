#ifndef CATMathMetric_H
#define CATMathMetric_H

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "YN000FUN.h"

#include "CATMathAttribute.h"
#include "CATMathInterval.h"
#include "CATMathDef.h"

class ExportedByYN000FUN CATMathMetric : public CATMathAttribute
{
 public:
  virtual ~CATMathMetric();
  CATMathAttrId GetType() const { return "CATMathMetric"; }
  CATBoolean IsExclusive() const { return 1; }
};

#endif
