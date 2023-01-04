#ifndef CATMathAttrPointerValue_h
#define CATMathAttrPointerValue_h

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "YN000FUN.h"

#include "CATMathAttribute.h"

class ExportedByYN000FUN CATMathAttrPointerValue : public CATMathAttribute
{
 private:
  char * _id;
  const void * _value;
  CATBoolean _excl;

 public:
  CATMathAttrPointerValue();
  CATMathAttrPointerValue(CATMathAttrId id,
			  const void * value,
			  const CATLONG32 exclusive = 1);
  ~CATMathAttrPointerValue();

  CATMathAttrId GetType() const;

  CATBoolean IsExclusive() const;
  const void * GetValue() const;
};

#endif
