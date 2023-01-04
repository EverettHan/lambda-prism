//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2017, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBucketsCache
//
// Use of CATPolyBuckets for memory allocation and a chained list for
// memory reuse
// New  : O(1)
// Free : O(1)
//
//===================================================================
// 16/11/17 F1Z : Creation
// DD/MM/YY
//===================================================================
#ifndef CATPolyBucketsCache_H
#define CATPolyBucketsCache_H

// Special API
#include "CATSysErrorDef.h"

// Polyhedral Mathematics
#include "CATPolyBuckets.h"
#include "CATPolyBucketsImpl.h"

/**
 * Cache of data T. T should have a default constructor.
 * This container creates and handles memory of T objects.
 */
template<typename T>
class CATPolyBucketsCache
{
public:
   // -----------------------------------------------------------------
   // Object management
   // -----------------------------------------------------------------
   CATPolyBucketsCache()
                      : _Free(0)
   {
   };

   ~CATPolyBucketsCache()
   {
   }

   // -----------------------------------------------------------------
   // New
   // -----------------------------------------------------------------
   T * New()
   {
      T * ptrNewElement = PopFree();

      if(!ptrNewElement)
      {
         int id = _Cache.PushBack(LocalData());
         ptrNewElement = &(_Cache[id]);
      }

      return ptrNewElement;
   }

   // -----------------------------------------------------------------
   // Free
   // -----------------------------------------------------------------
   HRESULT Free(const T * iToFree)
   {
      HRESULT status = S_OK;

      if(iToFree)
         PushFree((LocalData*)iToFree);

      return status;
   }

   // -----------------------------------------------------------------
   // Clear
   // -----------------------------------------------------------------
   void Clear(CATBoolean iKeepAllocatedMemory=FALSE)
   {
      _Cache.Clear(iKeepAllocatedMemory);
      _Free = 0;
   }

private:
   // -----------------------------------------------------------------
   // Local Data
   // -----------------------------------------------------------------
   struct LocalData : public T
   {
      LocalData * _NextFreeElement;
   };

   // -----------------------------------------------------------------
   // Methods (private)
   // -----------------------------------------------------------------
   void PushFree(LocalData * iToPushFree)
   {
      if(iToPushFree!=0)
      {
         iToPushFree->_NextFreeElement = _Free;
         _Free                         = iToPushFree;
      }
   }

   T * PopFree()
   {
      LocalData * freeElement = _Free;

      if(_Free)
      {
         _Free                         = _Free->_NextFreeElement;
         freeElement->_NextFreeElement = 0;
      }

      return freeElement;
   }

   // -----------------------------------------------------------------
   // Attributs (private)
   // -----------------------------------------------------------------
   CATPolyBuckets<LocalData>   _Cache;
   LocalData                 * _Free ;
};

#endif

