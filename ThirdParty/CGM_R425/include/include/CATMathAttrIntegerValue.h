#ifndef CATMATHATTRINTEGERVALUE_H
#define CATMATHATTRINTEGERVALUE_H

// COPYRIGHT DASSAULT SYSTEMES  1999
//=============================================================================
//
// Advanced mathematics operators attributes for specific parameterizations: integer type
//
//=============================================================================
// 28/07/09 NLD Gestion du stream.
//              Ajout IsStreamable(), StreamRun(), UnStream(), GetStreamType()
//              et constructeur avec stream
//              (voir aussi gestion dans CATMathAttribute::UnStream())
//              Ajout SetId()
//              Ajout Dump()

#include "YN000FUN.h"

#include "CATMathAttribute.h"

class ExportedByYN000FUN CATMathAttrIntegerValue : public CATMathAttribute
{
 private:
  char * _id;
  CATLONG32 _value;
  CATBoolean _excl;

 public:
  CATMathAttrIntegerValue();
  CATMathAttrIntegerValue(CATMathAttrId id,
           const CATLONG32 value,
           const CATLONG32 exclusive = 1);
  ~CATMathAttrIntegerValue();

  CATMathAttrId GetType() const;

  CATBoolean IsExclusive() const;
  CATLONG32 GetValue() const;

  virtual void Dump(CATCGMOutput &os) const;

  void SetId(CATMathAttrId id);

  // Stream management
  virtual CATBoolean IsStreamable(const CATCGMStreamVersion iTargetVersion)const;
  virtual void StreamRun( CATMathStream& Str, const char iLabelReserved[] = "") const;
  virtual short GetStreamType() const;
  CATMathAttrIntegerValue(CATMathAttrId id, CATLONG32 Exclusive, CATMathStream& Str, const char iLabelReserved[] = "");

};
#endif
