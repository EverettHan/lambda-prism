/* -*-c++-*- */
//====================================================================
// Copyright Dassault Systemes Provence 2008, All Rights Reserved 
//====================================================================
//
/**
* @nodoc
*/

#ifndef CATSobCellHashTable_H
#define CATSobCellHashTable_H

#include "CATCGMHashTable.h"
//#include "CATCGMNewArray.h"

class CATSobCell;

// exporting module
#include "CATSmoOperators.h"


typedef		int	         (*PFCompareFunction) ( CATSobCell *, CATSobCell * );	
typedef		unsigned int (*PFHashKeyFunction) ( CATSobCell * ) ;



class   ExportedByCATSmoOperators  CATSobCellHashTable : public CATCGMHashTable
{
public:
  CATSobCellHashTable (PFHashKeyFunction ipHashKeyFunction, PFCompareFunction ipCompareFunction, int iEstimatedSize = 0);
  ~CATSobCellHashTable();
  //CATCGMNewClassArrayDeclare;
  
  inline int      Insert(CATSobCell* ipCell);
  inline CATSobCell* Get(int iPos) const;
  inline void*    Locate(CATSobCell* ipCell) const;
  inline CATSobCell* KeyLocate(unsigned int iKey) const; 
  inline int      Remove(CATSobCell* ipCell);

  CATSobCell*        Next(CATSobCell* ipCell) const;
  int             Size() const;
};

//-----------------------------------------------------------------------------
// Insert
//-----------------------------------------------------------------------------
inline int CATSobCellHashTable::Insert(CATSobCell* ipCell)
{
  return (this->CATCGMHashTable::Insert((void*)ipCell));
}

//-----------------------------------------------------------------------------
// Get
//-----------------------------------------------------------------------------
inline CATSobCell* CATSobCellHashTable::Get(int iPos) const
{
  return ((CATSobCell*)this->CATCGMHashTable::Get(iPos));
}

//-----------------------------------------------------------------------------
// Locate
//-----------------------------------------------------------------------------
inline void* CATSobCellHashTable::Locate(CATSobCell* ipCell) const
{
  return (this->CATCGMHashTable::Locate((void*)ipCell));
}

//-----------------------------------------------------------------------------
// KeyLocate
//-----------------------------------------------------------------------------
inline CATSobCell* CATSobCellHashTable::KeyLocate(unsigned int iKey) const
{
  return ((CATSobCell*)this->CATCGMHashTable::KeyLocate(iKey));
}

//-----------------------------------------------------------------------------
// Remove
//-----------------------------------------------------------------------------
inline int CATSobCellHashTable::Remove(CATSobCell* ipCell)
{
  return (this->CATCGMHashTable::Remove((void*)ipCell));
}


#define CATHashTabCATSobCell CATSobCellHashTable

ExportedByCATSmoOperators unsigned int HashKeyFunction( CATSobCell * iCell );

ExportedByCATSmoOperators int CompareFunction( CATSobCell * iCell1, CATSobCell *iCell2 );

#endif 
