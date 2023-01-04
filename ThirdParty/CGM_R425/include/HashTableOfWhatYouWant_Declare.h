/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2011
// 
//==========================================================================
// Jul. 11  Creation                                                     WQO
// April 2014 Modification                                               U29
//==========================================================================
#include "CATCollec.h"
#include "CATCGMHashTableBase.h"
#include "CATAdaptiveHashTable.h"

//==========================================================================
// Partie invariante:

unsigned int WHAT_I_WANT_AS_HASH_FUNCTION_NAME(void * ipElem);
int WHAT_I_WANT_AS_COMPARE_FUNCTION_NAME(void* ipElem1, void* ipElem2);

class WHAT_I_WANT_AS_HASH_TABLE_NAME
{
private:
  CATAdaptiveHashTable _RealHT;

public:
  WHAT_I_WANT_AS_HASH_TABLE_NAME(int iEstimatedSize = 0)
    : _RealHT(iEstimatedSize, 
              WHAT_I_WANT_AS_HASH_FUNCTION_NAME, 
              WHAT_I_WANT_AS_COMPARE_FUNCTION_NAME) {};

  ~WHAT_I_WANT_AS_HASH_TABLE_NAME();

  INLINE int Size() const { return _RealHT.Size(); };

  WHAT_I_WANT_AS_STRUCT_NAME * Insert(WHAT_I_WANT_TO_LOCATE);

  INLINE WHAT_I_WANT_AS_STRUCT_NAME * Locate(WHAT_I_WANT_TO_LOCATE) const
  { 
    WHAT_I_WANT_AS_STRUCT_NAME Elem(WHAT_I_WANT_TO_LOCATE_SHORT);
    WHAT_I_WANT_AS_STRUCT_NAME ** Existing = (WHAT_I_WANT_AS_STRUCT_NAME **)_RealHT.Locate(&Elem);
    if (Existing)
      return *Existing;
    else
      return NULL; 
  };

  WHAT_I_WANT_AS_STRUCT_NAME * LocateOrInsert(WHAT_I_WANT_TO_LOCATE);

  int Remove(WHAT_I_WANT_TO_LOCATE);

  WHAT_I_WANT_AS_STRUCT_NAME * Get(int iPos) const;

 //April 2014 - Added by U29----------------------------------------
  #ifdef ADD_ASSOC_METHODS
    INLINE WHAT_I_WANT_AS_ASSOC_TYPE LocateAssoc(WHAT_I_WANT_TO_LOCATE) const
    {
      WHAT_I_WANT_AS_STRUCT_NAME* pElem = Locate(WHAT_I_WANT_TO_LOCATE_SHORT);

      if(pElem)
        return pElem->GetAssoc();
      else 
        return NULL;
    }
    INLINE void  LocateOrInsertAssoc(WHAT_I_WANT_TO_LOCATE,WHAT_I_WANT_AS_ASSOC_NAME)
    {
      WHAT_I_WANT_AS_STRUCT_NAME * pItem = LocateOrInsert(WHAT_I_WANT_TO_LOCATE_SHORT);

      if(pItem)
        pItem->SetAssoc(WHAT_I_WANT_AS_ASSOC_NAME_SHORT);
    }
  #endif
  //----------------------------------------------------------------
  void RemoveAll();
};

