#ifndef HashTableAssocTable_h
#define HashTableAssocTable_h

/**
*---------------------------------------------------------------------------------------------------------------------
* class HashTableAssocTable
*---------------------------------------------------------------------------------------------------------------------
* Class implementing an hash table associating each element to an hash table.
*---------------------------------------------------------------------------------------------------------------------
* 2018 WEEK 15      Creation                                                                                      LD2
*---------------------------------------------------------------------------------------------------------------------
*/

#include "CATAdaptiveHashTable.h"
#include "CATBoolean.h"
#include "ExportedByCATTopologicalObjects.h"

class HTAT_InternalTable;

class ExportedByCATTopologicalObjects HashTableAssocTable : public CATAdaptiveHashTable
{
public:
  /**
  * Constructor
  *
  * @param iAllocatedSize
  * The estimated number of elements in the table.
  */
  HashTableAssocTable(int iAllocatedSize);

  /**
  * Destructor
  */
  virtual ~HashTableAssocTable();

  /**
  * Adds element iFrom to the table (if it is not yet inside).
  * Adds element iTo to the table associated to iFrom (if it is not yet inside).
  * Cost: 1
  */
  void AddLink(void * iFrom, void * iTo, int iEstimatedNumberOfAssoc = 0);

  /**
  * Creates a HashTableAssocTable having, for each link A->B, the complementary B->A.
  * Cost: N+M, where N is the number of elements in this, and M is the average number of elements in an internal table.
  */
  HashTableAssocTable * CreateComplementary();

  /**
  * Returns the number of elements contained in the table associated to iItem.
  * Cost: 1
  */
  int GetNbAssoc(void * iItem);

  /**
  * Returns the table associated to iItem.
  * Cost: 1
  */
  CATAdaptiveHashTable * GetTable(void * iItem);

  /**
  * Returns the internal table at a given position.
  * Cost: 1
  */
  CATAdaptiveHashTable * GetTable(int iPos);

protected:
  virtual void Reallocate();
  virtual void CreateEmptyTables();
  virtual void ResetTables();
  virtual void ReplaceByLastElement(int iPos);

private:
  HTAT_InternalTable ** _HashTables;
};

/**
* Scan all elements associated to an element A:
*    HashTableAssocTable_ItemBegin(*Table, A, CurrentAssoc, CastedAssocType)
*    {
*       CurrentAssoc->CastedAssocType::...
*    } HashTableAssocTable_ItemEnd;
*/

#define HashTableAssocTable_ItemBegin(TABLE, ITEM, ASSOC, ASSOCTYPE)                            \
CATAdaptiveHashTable * __##ASSOC##Iterator = (TABLE).GetTable(ITEM);                            \
if (__##ASSOC##Iterator)                                                                     \
{                                                                                            \
  int __##ASSOC##i, __##ASSOC##n(__##ASSOC##Iterator->Size());                               \
  for (__##ASSOC##i = 0; __##ASSOC##i < __##ASSOC##n; __##ASSOC##i++)                        \
  {                                                                                          \
    ASSOCTYPE ASSOC = (ASSOCTYPE)__##ASSOC##Iterator->Get(__##ASSOC##i);                     \
    if (ASSOC)                                                                               \
    {

#define HashTableAssocTable_ItemEnd                  \
    }                                             \
  }                                               \
}

/**
* Scan all links inside the table:
*    HashTableAssocTable_Begin(*Table, CurrentItem, CastedItemType, CurrentAssoc, CastedAssocType)
*    {
*       CurrentItem->CastedItemType::...
*       CurrentAssoc->CastedAssocType::...
*    } HashTableAssocTable_End;
*/

#define HashTableAssocTable_Begin(TABLE, ITEM, ITEMTYPE, ASSOC, ASSOCTYPE)             \
int __##ITEM##i, __##ITEM##n((TABLE).Size());                                       \
for (__##ITEM##i = 0; __##ITEM##i < __##ITEM##n; __##ITEM##i++)                     \
{                                                                                   \
  ITEMTYPE ITEM = (ITEMTYPE)(TABLE).GetItem(__##ITEM##i);                           \
  HashTableAssocTable_ItemBegin(TABLE, ITEM, ASSOC, ASSOCTYPE)                         \
  {

#define HashTableAssocTable_End        \
  } HashTableAssocTable_ItemEnd;       \
}

#endif
