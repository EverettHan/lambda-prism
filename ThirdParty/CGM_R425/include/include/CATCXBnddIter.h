/* -*-c++-*- */
#ifndef CATCXCellBnddIter_H
#define CATCXCellBnddIter_H
// COPYRIGHT DASSAULT SYSTEMES 2005
//=============================================================================
//
// CATCXBnddIter:
// 
// Base class for iterator implementations.
//=============================================================================
// Aug. 05 Creation                                                       HCN
//=============================================================================
#include "CATBoundedCellsIterator.h"
#include "CATCGMNewArray.h"
#include "CATGeometryType.h"
#include "CATMathInline.h"

struct CATCGMBnddCellIterUDStats;

class  CATCXBnddIter : public CATBoundedCellsIterator
{
public :

  CATCGMNewClassArrayDeclare;
  
  CATCXBnddIter();

  virtual ~CATCXBnddIter();

  virtual const char* IsA() = 0;

  INLINE CATULONG32 GetSessionIdentifier() const;

  virtual CATGeometricType GetCellType() const = 0;
  virtual int GetTypeIndex() const = 0;
  const char* GetCellTypeName() const;
  static const char* GetCellTypeName(int iTypeIndex);

  // Statistiques parcours UpDown
  // En public pour acces depuis CATCXTopology::DumpUpDownMethod(...)
  CATCGMBnddCellIterUDStats* _pUpDownStatEntry;
  
protected :

  static CATULONG32 _SessionNbBorn;
  CATULONG32 _SessionId;
};

//-----------------------------------------------------------------------------
// GetSessionIdentifier
//-----------------------------------------------------------------------------
INLINE CATULONG32 CATCXBnddIter::GetSessionIdentifier() const
{
  return _SessionId;
}

#endif
