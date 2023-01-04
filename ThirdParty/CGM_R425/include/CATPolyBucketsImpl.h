// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBucketsImpl.h
//
//=============================================================================
//
// Generic (macro-based) buckets-based vector.
//
// Remark that the implementation uses direct OS memory allocation, and does
// not rely on another, conflicting layer of software memory handling (e.g. a
// memory pool). The malloc/free pair is prefered to new/delete because its
// behavior is more stable across environment (most notably when memory gets
// exhausted).
//
//=============================================================================
// May 2015 Creation: NDO Template version of CATPolyBuckets_T.h
//=============================================================================
#ifndef CATPolyBucketsImpl_H
#define CATPolyBucketsImpl_H

#include "CATPolyBuckets.h"
#include <utility>


// template<unsigned int n>
// struct Log2
// {
//   enum { res = Log2< (n >> 1) >::res + 1 };
// };
//
// template<>
// struct Log2<1>
// {
//   enum { res = 0 };
// };
//
// template<>
// struct Log2<0>
// {
// };


template<class T>
unsigned int CATPolyBuckets<T>::Log2 (unsigned int i)                             
{                                                                       
  unsigned int r = 0;                                                   
  while (i >>= 1)                                                       
    ++r;                                                                
  return r;                                                             
}                                                                       
                                                                        
/* Compile-time constants */                                            
                                                                        
template<class T>
const unsigned int CATPolyBuckets<T>::_Shift = /* Log2(RegionSize) */            
  Log2 (1024 < sizeof (T) ? sizeof (T) : 1024 / sizeof (T));                            

template<class T>
const unsigned int CATPolyBuckets<T>::_Mask = /* (1 << _Shift) - 1 */            
  (1 << Log2 (1024 < sizeof (T) ? sizeof (T) : 1024 / sizeof (T))) - 1;                 

template<class T>
const unsigned int CATPolyBuckets<T>::_NbItemsByRegion = /* 1 << _Shift */       
  1 << Log2 (1024 < sizeof (T) ? sizeof (T) : 1024 / sizeof (T));                       
                                                                        
/* */                                                                   


template<class T>
unsigned int CATPolyBuckets<T>::PushBack (const T &v)                                  
{                                                                       
  const unsigned int i = _NbItems + 1;                                  
                                                                        
  const unsigned int r = RegionNum(i);                                  
  const unsigned int c = CellNum(i);                                    
                                                                        
  if (_NbRegions <= r)                                                  
    /* Grow root array */                                               
    if (FAILED(Grow()) || _NbRegions <= r) return 0;                    
                                                                        
  if (!_Regions[r])                                                     
  {                                                                     
    /* Grow sub-array */                                                
    _Regions[r] = new T [_NbItemsByRegion];                      
    if (!_Regions[r]) return 0;                                         
  }                                                                     
                                                                        
  _Regions[r][c] = v;                                                   
  return ++_NbItems;                                                    
}                                                                       

#ifndef _AIX
template<class T>
unsigned int CATPolyBuckets<T>::PushBack (T &&v)                                  
{                                                                       
  const unsigned int i = _NbItems + 1;                                  
                                                                        
  const unsigned int r = RegionNum(i);                                  
  const unsigned int c = CellNum(i);                                    
                                                                        
  if (_NbRegions <= r)                                                  
    /* Grow root array */                                               
    if (FAILED(Grow()) || _NbRegions <= r) return 0;                    
                                                                        
  if (!_Regions[r])                                                     
  {                                                                     
    /* Grow sub-array */                                                
    _Regions[r] = new T [_NbItemsByRegion];                      
    if (!_Regions[r]) return 0;                                         
  }                                                                     
                                                                        
  _Regions[r][c] = std::forward<T>(v);                                                   
  return ++_NbItems;                                                    
}                                                                       
#endif

template<class T>
HRESULT CATPolyBuckets<T>::Grow ()                                                        
{                                                                       
  if (_Regions)                                                         
    /* Grow existing */                                                 
  {                                                                     
    const unsigned int NewNbRegions = _NbRegions * 2;                   
                                                                        
    T **NewRegions = new T *[NewNbRegions];             
    if (!NewRegions) return E_OUTOFMEMORY;                              
                                                                        
    memcpy(NewRegions, _Regions, _NbRegions * sizeof (T *));    
    /* Tricky: NewNbRegions - _NbRegions == _NbRegions */               
    memset(NewRegions + _NbRegions, 0, _NbRegions * sizeof (T *)); 
    delete [] _Regions;                                                 
    _Regions = NewRegions;                                              
    _NbRegions = NewNbRegions;                                          
  }                                                                     
  else                                                                  
    /* First allocation */                                              
  {                                                                     
    _NbRegions = 2;                                                     
    _Regions = new T *[_NbRegions];                             
    if (!_Regions) return E_OUTOFMEMORY;                                
                                                                        
    memset(_Regions, 0, _NbRegions * sizeof (T *));             
  }                                                                     
                                                                        
  return S_OK;                                                          
}                                                                       


template<class T>
HRESULT CATPolyBuckets<T>::Resize (unsigned int n)
{                                                                       
  if (n < _NbItems)                                                     
  {                                                                     
    const unsigned int NewNbRegions = (0 < n) ? (RegionNum(n) + 1) : 0; 
    if (NewNbRegions < _NbRegions)                                      
      /* Root array must be resized */                                  
    {                                                                   
      /* Kill regions that are beyond future limit */                   
      while (NewNbRegions < _NbRegions)                                 
      {                                                                 
        --_NbRegions;                                                   
        if (_Regions[_NbRegions])                                       
        {                                                               
          delete [] _Regions[_NbRegions];                               
          _Regions[_NbRegions] = 0;                                     
        }                                                               
      }                                                                 
      /* At this point, NewNbRegions == _NbRegions */                   
                                                                        
      /* Resize region pointer array: */                                
      T **NewRegions = 0;                                       
      if (0 < NewNbRegions)                                             
      {                                                                 
        /* - build new one, copy, */                                    
        NewRegions = new T *[NewNbRegions];                     
        memcpy(NewRegions, _Regions, _NbRegions * sizeof (T *)); 
      }                                                                 
                                                                        
      /* - kill old one and reassign. */                                
      delete [] _Regions;                                               
      _Regions = NewRegions;                                            
    }                                                                   
                                                                        
    /* FIXME: Reset data beyond specified limit in the last sub-array? */ 
                                                                        
    _NbItems = n;                                                       
  }                                                                     
  /* FIXME: else Reserve() */                                           
  return S_OK;                                                          
}                                                                       


template<class T>
HRESULT CATPolyBuckets<T>::Clear (CATBoolean iKeepAllocatedMemory)
{                                                                       
  return Resize (0);                                       
}

#endif // !CATPolyBucketsImpl_H
