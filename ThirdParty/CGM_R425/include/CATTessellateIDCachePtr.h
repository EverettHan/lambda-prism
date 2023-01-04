// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATTessellateIDCachePtr
//
//===================================================================
//
// June 2013  Creation: TPG
//===================================================================
#ifndef CATTessellateIDCachePtr_H
#define CATTessellateIDCachePtr_H

#include "CATCGMTessellateID.h"
#include "CATListOfCATCells.h"
#include "CATBoolean.h"

class ExportedByCATGMModelInterfaces CATTessellateIDCachePtr: public CATCGMTessellateID
{
public:
  CATTessellateIDCachePtr(const void* iCachePtr, int iOrientation, CATListPtrCATCell * iListOfDeltaCells);
  CATTessellateIDCachePtr(const CATTessellateIDCachePtr& iRHS);

  ~CATTessellateIDCachePtr();

public:
  CATCGMTessellateID& operator = (const CATCGMTessellateID& iRHS);
  CATTessellateIDCachePtr& operator = (const CATTessellateIDCachePtr& iRHS);
  int operator == (const CATCGMTessellateID& iRHS) const;
  int operator != (const CATCGMTessellateID& iRHS) const;
  int operator < (const CATCGMTessellateID& iRHS) const;

  inline CATBoolean HasDelta() const;
  inline int GetOrientation() const;
  inline const void* GetCachePtr() const;

protected:
  const void* _CachePtr;
  int _Orientation; // only for contextual comparison, 0 by default
  CATListPtrCATCell * _ListOfDeltaCells;
};

inline CATBoolean CATTessellateIDCachePtr::HasDelta() const
{
  if (_ListOfDeltaCells && _ListOfDeltaCells->Size()>0)
	return TRUE;
  return FALSE;
}

inline int CATTessellateIDCachePtr::GetOrientation() const
{
  return _Orientation;
}

inline const void* CATTessellateIDCachePtr::GetCachePtr() const
{
  return _CachePtr;
}

#endif // CATTessellateIDCachePtr_H

