/**
 * @COPYRIGHT DASSAULT SYSTEMES 2009
 */
/* -*-c++-*- */
//===========================================================================
//
// Hash table qui associe un int a une clef.
//
// Nov. 2009   Creation                                                  JJ3
// May  2010   Macros for iteration                                      WQO
// Jan. 2016   Template method for creation from lists                   LD2
// Feb. 2018   Migrate to KeyBucketMap                                   LD2
// Mar. 2018   Insert returns the position of insertion
//             Insert has additional output parameter "oInserionNeeded"
//             INLINE A GOGO                                             LD2
//
//===========================================================================

#ifndef  CATCGMHashTableWithIntAssoc_h
#define  CATCGMHashTableWithIntAssoc_h

#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMHashTable.h"
#include "CATCGMHashTableWithAssoc.h"
#include "CATMathematics.h"
#include "CATCGMVirtual.h"
#include "CATMathInline.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "KeyBucketMap.h"
#include "CATThrowForNullPointer.h"
#include "CATAdaptiveHashTable.h"

#define CHTWIA_MigrateToAHT

#ifdef CHTWIA_MigrateToAHT
class ExportedByCATTopologicalObjects CATHashTableWithIntAssoc : public CATAdaptiveHashTable
#else
class ExportedByCATTopologicalObjects CATHashTableWithIntAssoc : public KeyBucketMap
#endif
{
public:

  CATHashTableWithIntAssoc(int iEstimatedSize = 0);

  virtual ~CATHashTableWithIntAssoc();

  //Warning: The associated value is not modified if the element already exists in the table
  int                 Insert(void* ipElem, int iAssoc, CATBoolean * oInserionNeeded = NULL);
  int                 LocateItem(void* ipElem, int* ipAssoc) const;
#ifndef CHTWIA_MigrateToAHT
  INLINE void *       GetItem(int iPos) const;
#endif
  INLINE void         SetAssoc(int iPos, int iNewAssoc);
  INLINE int          GetAssoc(int iPos) const;
  INLINE int          GetAssoc(void* ipElem);
#ifndef CHTWIA_MigrateToAHT
  INLINE CATBoolean   Contain(void* ipElem);
#endif

protected:

  virtual void Reallocate();
  virtual void CreateEmptyTables();
  virtual void ResetTables();
#ifdef CHTWIA_MigrateToAHT
  virtual void ReplaceByLastElement(int iPos);

private:
  int * _AssocElements;
#else
  void ** _Elements;
  int   * _AssocElements;
  PFHASHKEYFUNCTION	_pHashKeyFunction;
#endif
};

/**
* INLINE implementations
*/

#ifndef CHTWIA_MigrateToAHT
INLINE void* CATHashTableWithIntAssoc::GetItem(int iPos) const
{
  if(0 <= iPos && iPos < this->Size())
    return _Elements[iPos];
  else
    return NULL;
}
#endif

INLINE void CATHashTableWithIntAssoc::SetAssoc(int iPos, int iNewAssoc)
{
  if(0 <= iPos && iPos < this->Size())
    _AssocElements[iPos] = iNewAssoc;
  else
    CATThrowForNullPointer();
}

INLINE int CATHashTableWithIntAssoc::GetAssoc(int iPos) const
{
  if(0 <= iPos && iPos < this->Size())
    return _AssocElements[iPos];
  else
    CATThrowForNullPointerReturnValue(0);
}

INLINE int CATHashTableWithIntAssoc::GetAssoc(void* ipElem)
{
  int result = 0;
  if(this->LocateItem(ipElem, &result) >= 0)
  {
    return result;
  }
  return 0;
}

#ifndef CHTWIA_MigrateToAHT
INLINE CATBoolean CATHashTableWithIntAssoc::Contain(void* ipElem)
{
  int iForCall = 0;
  return (this->LocateItem(ipElem, &iForCall) >= 0);
}
#endif

/**
* Macros for iteration:
*
* CATHashTableWithIntAssocBegin(TABLE, ITEM, ITEMTYPE, ASSOC)
* {
*   ...
* } CATHashTableWithIntAssocEnd;
*/

#define CATHashTableWithIntAssocBegin(TABLE, ITEM, ITEMTYPE, ASSOC)                    \
{                                                                                      \
  int __##ITEM##Index;                                                                 \
  int __##ITEM##Size = (TABLE).Size();                                                 \
  for (__##ITEM##Index = 0; __##ITEM##Index < __##ITEM##Size; __##ITEM##Index++)       \
  {                                                                                    \
    ITEMTYPE ITEM = (ITEMTYPE)(TABLE).GetItem(__##ITEM##Index);                        \
    if (ITEM)                                                                          \
    {                                                                                  \
      int ASSOC = (TABLE).GetAssoc(__##ITEM##Index);


#define CATHashTableWithIntAssocEnd                                                    \
    }                                                                                  \
  }                                                                                    \
}

/**
* Method to create a CATHashTableWithIntAssoc from a list of type LISTTYPE.
* LISTTYPE must respect the following rules:
*  - have a method Size returning the number of elements
*  - have an operator[int I] accessing elements with I=1...Size
*/
template <class LISTTYPE>
CATHashTableWithIntAssoc * CreateAssociationToIndexInList(const LISTTYPE & iList)
{
  int Idx, Nb(iList.Size());
  CATHashTableWithIntAssoc * PositionHashTable = new CATHashTableWithIntAssoc(2 * Nb);
  for (Idx = 1; Idx <= Nb; Idx++)
  {
    PositionHashTable->Insert((void *)iList[Idx], Idx);
  }
  return PositionHashTable;
}

#endif
