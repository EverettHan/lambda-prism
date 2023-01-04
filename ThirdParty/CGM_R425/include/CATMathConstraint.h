#ifndef CATMATHCONSTRAINT_H
#define CATMATHCONSTRAINT_H

// COPYRIGHT DASSAULT SYSTEMES  1999


#include "YN000FUN.h"

#include "CATMathAttribute.h"
#include "CATMathInterval.h"
#include "CATMathDef.h"

class ExportedByYN000FUN CATMathConstraint : public CATMathAttribute
{
 public:
  virtual CATBoolean Eval(const CATMathInterval & D) const=0;
  virtual double  EvalConstraint(const double iX)    const=0;
  virtual double  EvalDerivConstraint(const double iX) const;
  virtual ~CATMathConstraint();
  CATMathAttrId GetType() const { return "CATMathConstraint"; }
  CATBoolean IsExclusive() const { return 1; }
};

#endif
