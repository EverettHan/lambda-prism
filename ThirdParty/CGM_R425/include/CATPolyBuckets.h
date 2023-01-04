// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBuckets.h
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
#ifndef CATPolyBuckets_H
#define CATPolyBuckets_H

#include <stdlib.h>
#include <string.h>

#include "CATBoolean.h"
#include "CATErrorDef.h"


template <class T>  
class CATPolyBuckets
{

public:

  inline CATPolyBuckets ();
  inline ~CATPolyBuckets ();

  /* CATPolyBuckets<T> (const CATPolyBuckets<T>& iRHS); */
  /* CATPolyBuckets<T>& operator= (const CATPolyBuckets<T>& iRHS); */

public:

  /** (Explicit) */
  inline unsigned int Size () const;

  /** (Explicit) */
  inline CATBoolean Empty () const;

public:

  /** Accesses element i (read-only). */
  /** WARNING: Assume that `i' is a valid index */
  inline const T& operator[] (unsigned int i) const;

  /** Accesses element i (read-only). */
  /** `i' is checked for correctness */
  inline HRESULT Get (unsigned int i, T& v) const;
                                                                        
  /** Accesses element i (read-write). */                                 
  /** WARNING: Assume that `i' is a valid index */                      
  inline T& operator[] (unsigned int i);                      
                                                                        
  /** Accesses element i (read-write). */                                 
  /** `i' is checked for correctness */                                 
  inline HRESULT Set (unsigned int i, const T& v) const;
                                                                        
public:                                                                 

  /** Inserts a new element at the end. Returns the index of the new */ 
  /** element, or 0 if a problem is encountered (e.g. exhausted memory) */ 
  unsigned int PushBack (const T & v);                            

#ifndef _AIX
  unsigned int PushBack (T && v);
#endif
public:

  inline unsigned int Capacity () const                                  
  {                                                                     
    return _Regions ? _NbRegions : 0;                                   
  }                                                                     
                                                                        
  HRESULT Resize (unsigned int n);                                       
                                                                        
  HRESULT Clear (CATBoolean iKeepAllocatedMemory = FALSE);               
                                                                        
private: 

  HRESULT Grow ();                                                       
                                                                        
private:

  inline unsigned int RegionNum (unsigned int i) const                   
  {                                                                     
    return (i - 1) >> _Shift;                                           
  }                                                                     
                                                                        
  inline unsigned int CellNum (unsigned int i) const                     
  {                                                                     
    return (i - 1) & _Mask;                                             
  }
                                                                        
private:

  static unsigned int Log2 (unsigned int i);

private:                                                                

  /* Compile-time constants (only dependant upon size of value type) */ 
  static const unsigned int _NbItemsByRegion;                           
  static const unsigned int _Shift;                                     
  static const unsigned int _Mask;                                      
                                                                        
private:                                                                

  /* Actual buckets */                                                  
  unsigned int _NbRegions;
  T** _Regions;
                                                                        
private:                                                                

  /* Tail */                                                            
  unsigned int _NbItems;

};


template<class T>
inline CATPolyBuckets<T>::CATPolyBuckets () :
  _NbRegions (0),
  _Regions (0),
  _NbItems (0)
{
}

template<class T>
inline CATPolyBuckets<T>::~CATPolyBuckets ()
{
  Clear (FALSE);
}

template<class T>
inline unsigned int CATPolyBuckets<T>::Size () const
{
  return _NbItems;
}

template<class T>
inline CATBoolean CATPolyBuckets<T>::Empty () const
{
  return _NbItems == 0;
}

template<class T>
inline const T& CATPolyBuckets<T>::operator[] (unsigned int i) const
{
  const unsigned int r = RegionNum (i);
  const unsigned int c = CellNum (i);
  return _Regions[r][c];
}

template<class T>
inline HRESULT CATPolyBuckets<T>::Get (unsigned int i, T &v) const
{                                                                     
  if (i < 1 || _NbItems < i) 
    return E_FAIL;                           
  const unsigned int r = RegionNum(i);                                
  const unsigned int c = CellNum(i);                                  
  if (!_Regions[r]) 
    return E_FAIL;                                    
  v = _Regions[r][c];                                                 
  return S_OK;                                                        
}                                                                     

template<class T>
inline T& CATPolyBuckets<T>::operator[] (unsigned int i)                         
{                                                                     
  const unsigned int r = RegionNum (i);                                
  const unsigned int c = CellNum (i);                                  
  return _Regions[r][c];                                              
}                                                                     
                                                                        
template<class T>
inline HRESULT CATPolyBuckets<T>::Set (unsigned int i, const T &v) const          
{                                                                     
  if (i < 1 || _NbItems < i) 
    return E_FAIL;                           
  const unsigned int r = RegionNum (i);                                
  const unsigned int c = CellNum (i);                                  
  if (!_Regions[r]) 
    return E_FAIL;                                    
  _Regions[r][c] = v;                                                 
  return S_OK;                                                        
}

#endif // !CATPolyBuckets_H
