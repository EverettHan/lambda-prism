#ifndef CATMATHATTRDOUBLEVALUE_H
#define CATMATHATTRDOUBLEVALUE_H

// COPYRIGHT DASSAULT SYSTEMES  1999
//=============================================================================
//
// Advanced mathematics operators attributes for specific parameterizations: real type
//
//=============================================================================
// 16/01/08 NLD Ajout _OKReviewed, SetOKReviewed(), GetOKReviewed()
// 28/07/09 NLD Gestion du stream.
//              Ajout IsStreamable(), StreamRun(), UnStream(), GetStreamType()
//              et constructeur avec stream
//              (voir aussi gestion dans CATMathAttribute::UnStream())
//              Ajout SetId()
//              Ajout Dump()
// 05/08/09 NLD Ajout Init()
//=============================================================================

#include "YN000FUN.h"

#include "CATMathAttribute.h"


class ExportedByYN000FUN CATMathAttrDoubleValue : public CATMathAttribute
{
 private:
  char * _id;
  double _value;
  CATBoolean _excl;
  int _OKReviewed ;
  void Init();

 public:
  CATMathAttrDoubleValue();
  CATMathAttrDoubleValue(CATMathAttrId id,
       const double value,
       const CATLONG32 exclusive = 1);
  ~CATMathAttrDoubleValue();

  CATMathAttrId GetType() const;
  void SetId(CATMathAttrId id);

  virtual void Dump(CATCGMOutput &os) const;

  CATBoolean IsExclusive() const;
  double GetValue() const;
  void SetValue(const double & valeur);
  // Pour exclusion du systeme de controle/traces des attributs duement certifies. NLD070108
  void SetOKReviewed() ;
  CATLONG32 GetOKReviewed() ;

  // Stream management
  virtual CATBoolean IsStreamable(const CATCGMStreamVersion iTargetVersion)const;
  virtual void StreamRun( CATMathStream& Str, const char iLabelReserved[] = "") const;
  virtual short GetStreamType() const;
  CATMathAttrDoubleValue(CATMathAttrId id, CATLONG32 Exclusive, CATMathStream& Str, const char iLabelReserved[] = "");

};
#endif
