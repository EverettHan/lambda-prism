#ifndef CATMATHATTRSTRING_H
#define CATMATHATTRSTRING_H

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  1999
//=============================================================================
//
// Advanced mathematics operators attributes for specific parameterizations: string type
//
//=============================================================================
// 31/07/08 NLD Utilisation d'un tableau statique (ajouts _staticid, CATMathAttrString_StaticSize)
// 28/07/09 NLD Gestion du stream.
//              Ajout IsStreamable(), StreamRun(), UnStream(), GetStreamType()
//              et constructeur avec stream
//              (voir aussi gestion dans CATMathAttribute::UnStream())
//              Ajout SetId()
//              Ajout Dump()
//=============================================================================
#include "YN000FUN.h"

#include "CATMathAttribute.h"

// taille du tableau statique pour l'identificateur (au dela: allocation)
#define CATMathAttrString_StaticSize 34

class ExportedByYN000FUN CATMathAttrString : public CATMathAttribute
{
 private:
  char * _id;
  CATBoolean _excl;

 #ifdef CATMathAttrString_StaticSize
 char _staticid[CATMathAttrString_StaticSize] ;
 #endif

 void SetId(CATMathAttrId id);

 public:
  CATMathAttrString();
  CATMathAttrString(CATMathAttrId id,
  const CATLONG32 exclusive = 1);
  ~CATMathAttrString();

  CATMathAttrId GetType() const;

  CATBoolean IsExclusive() const;

  virtual void Dump(CATCGMOutput &os) const;

  // Stream management
  virtual CATBoolean IsStreamable(const CATCGMStreamVersion iTargetVersion)const;
  virtual void StreamRun( CATMathStream& Str, const char iLabelReserved[] = "") const;
  virtual short GetStreamType() const;
  CATMathAttrString(CATMathAttrId Id, CATLONG32 Exclusive, CATMathStream& Str, const char iLabelReserved[] = "");
};
#endif
