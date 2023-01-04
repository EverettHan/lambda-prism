//=============================================================================
// COPYRIGHT Dassault Systemes 2009
//=============================================================================
//
// CATTessParamToken
//
//=============================================================================
// 2009-07-29 MPX: New
//=============================================================================
#ifndef CATTessParamToken_H
#define CATTessParamToken_H

#include "TessCacheObjects.h"
#include "CATMathInline.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATGeometry.h"
#include <limits.h>


class CATCGMStream;
class CATGeometry;
class CATGeoFactory;

typedef unsigned char AttribLocalIdType;

#define MaxValueOfAttribLocalId UCHAR_MAX
#define MinValueOfAttribLocalId 0

class ExportedByTessCacheObjects CATTessParamToken
{
public:
  INLINE CATTessParamToken();
  INLINE CATTessParamToken(CATGeometry& iParamOwner, AttribLocalIdType iAttribLocalId);
  INLINE CATTessParamToken(const CATTessParamToken& iOther);
  INLINE ~CATTessParamToken();

  INLINE const CATTessParamToken& operator = (const CATTessParamToken& iOther);

  INLINE CATBoolean operator == (const CATTessParamToken& iOther) const;
  INLINE CATBoolean operator != (const CATTessParamToken& iOther) const;

  INLINE CATGeometry* GetParamOwner() const;
  INLINE CATULONG32 GetParamOwnerTag() const;


public:
  void Stream(CATCGMStream& iStream) const;
  void UnStream(CATCGMStream& iStream);

public:
  INLINE AttribLocalIdType GetLocalId () const;

protected:
  INLINE void CopyFrom(const CATTessParamToken& iOther);

protected:
  CATGeometry* _ParamOwner;  // to do: AddRef()/Release() on this CATGeometry.
  AttribLocalIdType _AttribLocalId; // Attribute Local Id, this is locally unique (i.e. unique amongst the attributes of a particular CGM Object)

  friend class CATTessParamAttribute;
};

INLINE 
CATTessParamToken::CATTessParamToken(CATGeometry& iParamOwner, AttribLocalIdType iAttribLocalId)
:
_AttribLocalId(iAttribLocalId)
{
  _ParamOwner = &iParamOwner;
}

INLINE 
CATTessParamToken::CATTessParamToken()
:
_ParamOwner(0),
_AttribLocalId(0)
{
}

INLINE 
CATTessParamToken::CATTessParamToken(const CATTessParamToken& iOther)
{
  CopyFrom(iOther);
}

INLINE const CATTessParamToken& 
CATTessParamToken::operator = (const CATTessParamToken& iOther)
{
  CopyFrom(iOther);
  return *this;
}

INLINE void
CATTessParamToken::CopyFrom(const CATTessParamToken& iOther)
{
  _ParamOwner = iOther._ParamOwner;
  _AttribLocalId = iOther._AttribLocalId;
}

INLINE 
CATTessParamToken::~CATTessParamToken()
{
  _ParamOwner = 0;
  _AttribLocalId = 0;
}

INLINE CATBoolean 
CATTessParamToken::operator == (const CATTessParamToken& iOther) const
{
  return 
    (  (_ParamOwner == iOther._ParamOwner)
    && (_AttribLocalId == iOther._AttribLocalId) );
}

INLINE CATBoolean 
CATTessParamToken::operator != (const CATTessParamToken& iOther) const
{
  return ! ((*this) == iOther);
}

INLINE CATGeometry* 
CATTessParamToken::GetParamOwner() const
{
  return _ParamOwner;
}

INLINE CATULONG32 
CATTessParamToken::GetParamOwnerTag() const
{
  return _ParamOwner ? _ParamOwner->GetPersistentTag() : 0;
}

INLINE AttribLocalIdType 
CATTessParamToken::GetLocalId () const
{
  return _AttribLocalId;
}

#endif // !CATTessParamToken_H

