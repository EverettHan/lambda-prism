/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATCGMAttributeOld
//   this class describes the behavior af on attribute class which is 
//   recognized by a CATCGMAttrId
//   this attribute class describes the behaviour of old attributes.
//=============================================================================
// Nov. 98   Creation                                     JHN
//=============================================================================
#ifndef CATCGMAttributeOld_H
#define CATCGMAttributeOld_H


class CATCGMAttributeDef;
class CATCGMStream;
class CATICGMObject;

#include "CGMObject.h"
#include "CATCGMAttribute.h"
#include "CATCGMNewArray.h"


//-----------------------------------------------------------------------------
class  CATCGMAttributeOld : public CATCGMAttribute 
{
CATCGMDeclareAttribute (CATCGMAttributeOld, CATCGMAttribute);
public :
  CATCGMNewClassArrayDeclare;

  CATCGMAttributeOld();
  ~CATCGMAttributeOld();
  void SetBuffer(const void * , CATLONG32 memlength);
  const void * GetBuffer(CATLONG32 &memlength);
  void SetKey(int key);
  int GetKey();

  virtual void Dump( CATCGMOutput & os ); // For Debug Purpose

protected :
  virtual CATLONG32 Compare(const CATCGMAttribute & newattr);
private :
  void * buf;
  CATLONG32 lgbuf;
  int _Key;
  double _StaticBuffer;

  friend class CATCGMObject;
};

void CastTo(CATCGMAttribute *, CATCGMAttributeOld * &);

#endif








