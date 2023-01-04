//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2017, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBucketQueueCache
//
// Use of CATPolyBuckets for memory allocation and CATEventQueue to reduce the complexity
// to ensure there is no data duplication.
// Useful if a hash table can't be used but a CATEventQueue can.
// New : O(1)
// Add : O(Log(N)) + Observer cost
// Remove: O(Log(N)) + Observer cost
//
//===================================================================
// 13/11/17 F1Z : Creation
// DD/MM/YY
//===================================================================
#ifndef CATPolyBucketsQueueCache_H
#define CATPolyBucketsQueueCache_H

// Special API
#include "CATSysErrorDef.h"

// Polyhedral Mathematics
#include "CATPolyBucketsCache.h"
#include "CATEventQueue.h"
#include "CATCompareElements.h"
#include "CATPolyActiveCacheObserver.h"

/**
 * Cache of data T. T should have a default constructor.
 * This container creates and handles memory of T objects.
 * The cache is O(log(N)) for Add/Remove methods, O(1) for new
 */
template<typename T>
class CATPolyBucketsQueueCache
{
public:
   // -----------------------------------------------------------------
   // Define
   // -----------------------------------------------------------------
   typedef CATPolyActiveCacheObserver<T> CacheObserver;

public:
   // -----------------------------------------------------------------
   // Object management
   // -----------------------------------------------------------------
   CATPolyBucketsQueueCache()
                           : _Observers   (0),
                             _ActiveData  (0),
                             _HandleMemory(false)
   {
   };

   CATPolyBucketsQueueCache(const CATCompareElements & iCompareData)
                           : _Observers   (0),
                             _HandleMemory(true)
   {
      _ActiveData = new CATEventQueue(iCompareData);
   };

   ~CATPolyBucketsQueueCache()
   {
      // Clear active data
      // ----------------------------------
      if(_ActiveData)
      {
         _ActiveData->Clear();

         if(_HandleMemory)
            delete _ActiveData;
      }
      _ActiveData = 0;

      // Clear observers
      // ----------------------------------
	  if(_Observers)
         _Observers->Release();
   }

   // -----------------------------------------------------------------
   // SetQueue
   // Perform a clear before switching to the new queue
   // -----------------------------------------------------------------
   void SetQueue(CATEventQueue * ioQueue           ,
                 bool            iHandleMemory=true)
   {
      Clear();

      if(_ActiveData && _HandleMemory)
      {
         delete _ActiveData;
      }

      _ActiveData   = ioQueue;
      _HandleMemory = iHandleMemory;
   }

   // -----------------------------------------------------------------
   // New
   // -----------------------------------------------------------------
   T * New()
   {
      T * newData = _Cache.New();
      return newData;
   }

   // -----------------------------------------------------------------
   // Free
   // No check is performed
   // -----------------------------------------------------------------
   void Free(const T * iToFree)
   {
      if(!iToFree) return;

      for(CacheObserver * iteObserver = _Observers; iteObserver && iToFree; iteObserver = iteObserver->Next())
         iteObserver->DataFree(*iToFree);

      _Cache.Free(iToFree);
   }

   // -----------------------------------------------------------------
   // Add
   // -----------------------------------------------------------------
   T * Add(T    * iToAdd               ,
           bool   iFreeIfAlreadyIn=true)
   {
      if(!_ActiveData || !iToAdd) return 0;

      T                       * addedElement = 0;
      CATEventQueue::Iterator   positionIte;
      HRESULT                   status       = S_OK;
      bool                      isOkToAdd    = true;

      // We check if all the observer are ok to add this new data
      // ------------------------------------------------------------------
      for(CacheObserver * iteObserver = _Observers; iteObserver && iToAdd && isOkToAdd; iteObserver = iteObserver->Next())
            isOkToAdd = iteObserver->IsOkToAdd(*iToAdd);

      if(isOkToAdd)
      {
         // We add the new data
         status = _ActiveData->Insert (iToAdd, &positionIte); // S_OK if not found
      }
      else
      {
         // We check if the data is already added
         positionIte = _ActiveData->Find(iToAdd);
         status = S_FALSE;
      }

      // We spread the information
      // ------------------------------------------------------------------
      if (status == S_OK)
      {
         for(CacheObserver * iteObserver = _Observers; iteObserver && iToAdd; iteObserver = iteObserver->Next())
            iteObserver->DataAdded(*iToAdd);
         addedElement = iToAdd;
      }
      else
      {
         // The bar is already in the active bar
         T * foundElement = (positionIte.End())? 0 : (T*) positionIte.GetElement();
         if(foundElement!=iToAdd && iFreeIfAlreadyIn)
         {
            Free(iToAdd);
         }
         addedElement = foundElement;
      }

      return addedElement;
   }

   // -----------------------------------------------------------------
   // Find
   // -----------------------------------------------------------------
   T * Find(const T * iToFind) const
   {
      if(!_ActiveData || !iToFind) return 0;

      CATEventQueue::Iterator positionIte = _ActiveData->Find(iToFind);

      T * toReturn = (positionIte.End())? 0 : (T*) positionIte.GetElement();

      // Observer spreading
      for(CacheObserver * iteObserver = _Observers; iteObserver && toReturn!=0; iteObserver = iteObserver->Next())
         iteObserver->DataFound(*toReturn);

      return toReturn;
   }

   // -----------------------------------------------------------------
   // Remove
   // -----------------------------------------------------------------
   HRESULT Remove(const T          * iToRemove         ,
                        bool         iFreeData    =true,
                        bool         iCheckSamePtr=true)
   {
      if(!_ActiveData || !iToRemove) return S_FALSE;

      HRESULT status = S_OK;

      CATEventQueue::Iterator positionToRemove = _ActiveData->Find(iToRemove);

      const T * data = (const T *) _ActiveData->Get(positionToRemove);

      if(data && (!iCheckSamePtr || data==iToRemove))
      {
         status = _ActiveData->Remove(positionToRemove);

         for(CacheObserver * iteObserver = _Observers; iteObserver && data; iteObserver = iteObserver->Next())
            iteObserver->DataRemoved(*data);

         if(iFreeData)
            Free(data);
      }
      else
      {
         // The input is not an active data
         // Either it is already free or is not linked to this cache
         status = S_FALSE;
      }

      return status;
   }

   // -----------------------------------------------------------------
   // FirstActif
   // -----------------------------------------------------------------
   CATEventQueue::Iterator FirstActif()
   {
     if(_ActiveData)
       return _ActiveData->First();
     else
       return CATEventQueue::Iterator();
   }

   // -----------------------------------------------------------------
   // LastActif
   // -----------------------------------------------------------------
   CATEventQueue::Iterator LastActif()
   {
     if(_ActiveData)
       return _ActiveData->Last();
     else
       return CATEventQueue::Iterator();
   }

   // -----------------------------------------------------------------
   // Size
   // -----------------------------------------------------------------
   int Size() const
   {
      return (_ActiveData)? _ActiveData->Size() : 0;
   }

   // -----------------------------------------------------------------
   // Clear
   // -----------------------------------------------------------------
   void Clear()
   {
      if(!_ActiveData) return;

      CATEventQueue::Iterator iteQueue = _ActiveData->First();

      for(; !iteQueue.End(); ++iteQueue)
      {
         T * data = (T*) iteQueue.GetElement();
         Free(data);

         for(CacheObserver * iteObserver = _Observers; iteObserver && data; iteObserver = iteObserver->Next())
            iteObserver->DataRemoved(*data);
      }

      _ActiveData->Clear();
   }

   // -----------------------------------------------------------------
   // RegisterObserver
   // -----------------------------------------------------------------
   HRESULT RegisterObserver(CacheObserver * iObserver)
   {
      HRESULT status = S_OK;

      status = CacheObserver::Register(_Observers, iObserver);

      return status;
   }

   // -----------------------------------------------------------------
   // UnregisterObserver
   // -----------------------------------------------------------------
   HRESULT UnregisterObserver(CacheObserver * iObserver)
   {
      HRESULT status = S_OK;

      CacheObserver::Unregister(_Observers, iObserver);

      return status;
   }

private:

   // -----------------------------------------------------------------
   // Attributs (private)
   // -----------------------------------------------------------------
   CacheObserver          * _Observers   ;
   CATPolyBucketsCache<T>   _Cache       ;
   CATEventQueue          * _ActiveData  ;
   bool                     _HandleMemory;
};

#endif

