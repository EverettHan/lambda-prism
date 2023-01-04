#ifndef CATCGMHashTableSmart_h
#define CATCGMHashTableSmart_h

//*************************************************************************************************
// Macros to navigate hash tables.
//-----------------------------------------------------------------------------------------------
// 2010 05 Creation                                                                LD2
//*************************************************************************************************

#include "BOOPER.h"
#include "CATCGMHashTable.h"
#include "CATAdaptiveHashTable.h"
#include "GMScanMacros.h"

#define CATCGMHashTableWithAssocBegin(TABLE, ITEM, ITEMTYPE, ASSOC, ASSOCTYPE)                    \
{                                                                                                 \
  int _##ITEM##Index;                                                                             \
  int _##ITEM##Size = (TABLE).Size();                                                             \
  for (_##ITEM##Index = 0; _##ITEM##Index < _##ITEM##Size; _##ITEM##Index++)                      \
  {                                                                                               \
    void *ASSOCVOID = NULL;                                                                       \
    void *ITEMVOID = (TABLE).GetItemAndAssoc(_##ITEM##Index,& ASSOCVOID);                         \
    if (ITEMVOID && ASSOCVOID) {                                                                  \
      ITEMTYPE ITEM = (ITEMTYPE) ITEMVOID;                                                        \
      ASSOCTYPE ASSOC = (ASSOCTYPE) ASSOCVOID;                                                    \
      {                                                                                           

#define CATCGMHashTableWithAssocEnd                                                               \
      }                                                                                           \
    }                                                                                             \
  }                                                                                               \
}

#define HashTableAssocData_Begin(TABLE, CURRENT, TYPE) CATCGMHashTableBegin(TABLE, CURRENT, TYPE)

#define HashTableAssocData_End                         CATCGMHashTableEnd


#endif
