/* -*-c++-*- */
#ifndef CATCGMStreamAttrData_H
#define CATCGMStreamAttrData_H
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATCGMStreamAttrData
//   internal data for class CATCGMStreamAttribute
//=============================================================================
// Jun. 99                                       RAD
//=============================================================================

#include "YP0LOGRP.h"
#include "CATListOfCATICGMObjects.h"
#include "CATCGMVirtual.h"
#include "CATMathInline.h"

class CATICGMObject;

typedef int (*CATCGMAddReferenceFunc)(CATICGMObject*);
typedef int (*CATCGMReleaseReferenceFunc)(CATICGMObject*);


class ExportedByYP0LOGRP CATCGMStreamAttrData : public CATCGMVirtual
{
public :
  CATCGMStreamAttrData(int nballoc = 1) : _List(nballoc) {};
  ~CATCGMStreamAttrData();

  void Add(CATICGMObject*);
  void Remove(CATICGMObject*);
  void Set(const CATLISTP(CATICGMObject)&);

  INLINE const CATLISTP(CATICGMObject)& GetList() const;

  static int SetAddReference(CATCGMAddReferenceFunc);
  static int SetReleaseReference(CATCGMReleaseReferenceFunc);

  void AddReference(CATICGMObject*);
  void ReleaseReference(CATICGMObject*);

private:
  CATLISTP(CATICGMObject) _List;

  static CATCGMAddReferenceFunc     _FctAddReference;
  static CATCGMReleaseReferenceFunc _FctReleaseReference;
};


ExportedByYP0LOGRP const CATLISTP(CATICGMObject)& CATCGMStreamAttrData::GetList() const
{
  return _List;
}

#endif








