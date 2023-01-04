#ifndef CATMATHATTREXCLUSION2D_H
#define CATMATHATTREXCLUSION2D_H

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "YN000FUN.h"

#include "CATMathAttribute.h"
#include "CATMathInterval2D.h"

class ExportedByYN000FUN CATMathAttrExclusion2D : public CATMathAttribute
{
 private:
  CATMathInterval2D * _exclusion;
  CATLONG32 _nbConf;

 public:
  CATMathAttrExclusion2D();
  CATMathAttrExclusion2D(const CATMathInterval2D & I);
  ~CATMathAttrExclusion2D();

  void AddInterval(const CATMathInterval2D & I);

  CATMathAttrId GetType() const;
  CATBoolean IsExclusive() const;
  CATBoolean Includes(CATMathInterval2D & I) const;
};

#endif
