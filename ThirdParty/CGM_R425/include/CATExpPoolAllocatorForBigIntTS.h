//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2015-2016
//==============================================================================================================
// Usage notes: One Pool of 1024*1024 single_utin is created per thread
// Allways call CATExpSThreadAllocatorLifeCycle_Reset() at the beginning of each sequence of usage of FloatRing, FloatField or BigInt 
//==============================================================================================================
// 2019-06-14 : RNO : Compil Linux (classe vide sur Linux)
// 14-11-2015 : RNO/MMO : Correction probleme VS2015 sur les operateurs == et != il faut inverser true et false
// 17-06-2015 : RNO : Enhanced version that can be shared between several thread
//==============================================================================================================




#ifndef CATEXPPOOLALLOCATORFORBIGINTTS_H
#define CATEXPPOOLALLOCATORFORBIGINTTS_H
#if defined(_WINDOWS_SOURCE)


#include "CATExpExactArithmetic.h"
#include "CATExpNumericDeclarations.h"
/*         THIS ALLOCATOR FOLLOW THE MALLOCATOR
Visual C++ Team Blog : Mallocator
http://blogs.msdn.com/b/vcblog/archive/2008/08/28/the-mallocator.aspx
*/

template <typename T> class CATExpPoolAllocatorForBigIntTS;
// The following headers are required for all allocators.
#include <stddef.h>  // Required for size_t and ptrdiff_t and NULL
#include <new>       // Required for placement new and std::bad_allo
#include <stdexcept> // Required for std::length_error
// The following headers contain stuff that Mallocator uses.
#include <stdlib.h>  // For malloc() and free()
#include <iostream>  // For std::cout
#include <ostream>   // For std::endl
// The following headers contain stuff that main() uses.
#include <list>      // For std::list
#include "CATIAV5Level.h" //versionning

#ifndef __EXPNOEXCEPT__
#if defined(CATIAR421) ||  defined(CATIAV5R30)
#define __EXPNOEXCEPT__ noexcept
#else
#define __EXPNOEXCEPT__
#endif
#endif

#ifndef INLINE
#if defined(_WINDOWS_SOURCE) && defined(_MSC_VER) && _MSC_VER>1300
#define  INLINE     __forceinline
#else
#define  INLINE     inline
#endif
#endif

static const int MAX_SIZE_ALLOC=2048*2048;
static const int INIT_SIZE_TAB_ALLOC=1024;

template <typename T> class CATExpPoolAllocatorForBigIntTS 
{

public:
  // The following will be the same for virtually all allocators.
  typedef T * pointer;
  typedef const T * const_pointer;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T value_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  T * address(T& r) const {return &r;}



  const T * address(const T& s) const { return &s;}



  size_t max_size() const {

    // The following has been carefully written to be independent of

    // the definition of size_t and to avoid signed/unsigned warnings.

    return (static_cast<size_t>(0) - static_cast<size_t>(1)) / sizeof(T);

  }
  // The following must be the same for all allocators.

  template <typename U> struct rebind {
    typedef CATExpPoolAllocatorForBigIntTS<U> other;

  };



  bool operator!=(const CATExpPoolAllocatorForBigIntTS& other) const {
    // return true; VS2015 : il n'y a qu'un allocateur, ils ne peuvent donc pas etre différents
    return false;
  }

  INLINE void construct(T * const p, const T& t) const {
    void * const pv = static_cast<void *>(p);
    new (pv) T(t);

  }

  void destroy(T * const p) const; // Defined below.

  // Returns true if and only if storage allocated from *this

  // can be deallocated from other, and vice versa.

  // Always returns true for stateless allocators.

  bool operator==(const CATExpPoolAllocatorForBigIntTS& other) const {  
    // return false; VS2015 : il n'y a qu'un allocateur, ils sont donc forcement identiques
    return true;
  }



  // Default constructor, copy constructor, rebinding constructor, and destructor.

  // Empty for stateless allocators.
#if defined(CATIAR420) ||  defined(CATIAV5R29) 
  //on laisse les implementations par defaut ... ce qui nous permet d'avoir un move operator
  CATExpPoolAllocatorForBigIntTS() { }

  CATExpPoolAllocatorForBigIntTS(const CATExpPoolAllocatorForBigIntTS&) { }

  template <typename U> CATExpPoolAllocatorForBigIntTS(const CATExpPoolAllocatorForBigIntTS<U>&) { }

  ~CATExpPoolAllocatorForBigIntTS() { }
#endif
  // The following will be different for each allocator.

  T * allocate(const size_t n) const {
    // Mallocator prints a diagnostic message to demonstrate
    // what it's doing. Real allocators won't do this.
    
   /* if(n!=8)
    {
      int abrk=1;
    }*/
//    std::cout << "Allocating " << n << (n == 1 ? " object" : "objects")  << " of size " << sizeof(T) << "." << std::endl;
    // The return value of allocate(0) is unspecified.
    // Mallocator returns NULL in order to avoid depending
    // on malloc(0)'s implementation-defined behavior
    // (the implementation can define malloc(0) to return NULL,
    // in which case the bad_alloc check below would fire).
    // All allocators can return NULL in this case.
    if (n == 0) 
    {
      return NULL;
    }



    // All allocators should contain an integer overflow check.
    // The Standardization Committee recommends that std::length_error
    // be thrown in the case of integer overflow.
    if (n > max_size()) 
    {
      throw std::length_error("Mallocator<T>::allocate() - Integer overflow.");
    }
    // Mallocator wraps malloc().
    void * const pv = malloc(n * sizeof(T));
    // Allocators should throw std::bad_alloc in the case of memory allocation failure.

    if (pv == NULL) {
      throw std::bad_alloc();
    }
    return static_cast<T *>(pv);
  }



  void deallocate(T * const p, const size_t n) const {
    // Mallocator prints a diagnostic message to demonstrate
    // what it's doing. Real allocators won't do this.
//    std::cout << "Deallocating " << n << (n == 1 ? " object" : "objects") << " of size " << sizeof(T) << "." << std::endl;
    // Mallocator wraps free().
    free(p);

  }





  // The following will be the same for all allocators that ignore hints.

  template <typename U> T * allocate(const size_t n, const U * /* const hint */) const { return ::allocate(n);}


  // Allocators are not required to be assignable, so
  // all allocators should have a private unimplemented
  // assignment operator. Note that this will trigger the
  // off-by-default (enabled under /Wall) warning C4626
  // "assignment operator could not be generated because a
  // base class assignment operator is inaccessible" within
  // the STL headers, but that warning is useless.

private:
#if defined(CATIAR420) || defined(CATIAV5R29) 
  CATExpPoolAllocatorForBigIntTS& operator=(const CATExpPoolAllocatorForBigIntTS&) =default;
#else
  CATExpPoolAllocatorForBigIntTS& operator=(const CATExpPoolAllocatorForBigIntTS&) {};
#endif
};

// A compiler bug causes it to believe that p->~T() doesn't reference p.


#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100) // unreferenced formal parameter
#endif
// The definition of destroy() must be the same for all allocators.
template <typename T> void CATExpPoolAllocatorForBigIntTS<T>::destroy(T * const p) const { p->~T();}




ExportedByCATExpExactArithmetic void CATExpSThreadAllocatorLifeCycle_Reset();
ExportedByCATExpExactArithmetic void CATExpSThreadAllocatorLifeCycle_AddRef();
ExportedByCATExpExactArithmetic void CATExpSThreadAllocatorLifeCycle_Release();

class CATExpScopedAllocatorTS
{
public :

  //  [5/24/2018 RNO] CATIAR420 : Plus besoin de ca car il n'y a plus d'allocateur !!!
  //l'optimiseur doit supprimer ces objets qui ne servent a rien
  CATExpScopedAllocatorTS() __EXPNOEXCEPT__
  {
#if !defined(CATIAR420) && !defined(CATIAV5R29) 
    CATExpSThreadAllocatorLifeCycle_AddRef();
#endif
  }
  ~CATExpScopedAllocatorTS()
  {
#if !defined(CATIAR420) && !defined(CATIAV5R29) 
    CATExpSThreadAllocatorLifeCycle_Release();
#endif
  } 

};

template <> class CATExpPoolAllocatorForBigIntTS<single_uint_t>
{

public:
  // The following will be the same for virtually all allocators.
  typedef single_uint_t * pointer;
  typedef const single_uint_t * const_pointer;
  typedef single_uint_t& reference;
  typedef const single_uint_t& const_reference;
  typedef single_uint_t value_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  INLINE single_uint_t * address(single_uint_t& r) const __EXPNOEXCEPT__  {return &r;}



  INLINE const single_uint_t * address(const single_uint_t& s) const __EXPNOEXCEPT__  { return &s;}



  size_t max_size() const __EXPNOEXCEPT__  {

    // The following has been carefully written to be independent of

    // the definition of size_t and to avoid signed/unsigned warnings.

    return (static_cast<size_t>(0) - static_cast<size_t>(1)) / sizeof(single_uint_t);

  }
  // The following must be the same for all allocators.

  template <typename U> struct rebind {
    typedef CATExpPoolAllocatorForBigIntTS<U> other;

  };


  INLINE bool operator!=(const CATExpPoolAllocatorForBigIntTS& other) const __EXPNOEXCEPT__ 
  {
    // return true; VS2015 : il n'y a qu'un allocateur, ils ne peuvent donc pas etre différents
    return false;
  }

  INLINE void construct(single_uint_t * const p, const single_uint_t& t) const __EXPNOEXCEPT__ {
    void * const pv = static_cast<void *>(p);
    new (pv) single_uint_t(t);

  }

  INLINE void destroy(single_uint_t * const p) const __EXPNOEXCEPT__  {}; // Defined below.

  // Returns true if and only if storage allocated from *this

  // can be deallocated from other, and vice versa.

  // Always returns true for stateless allocators.

  INLINE bool operator==(const CATExpPoolAllocatorForBigIntTS& other) const __EXPNOEXCEPT__ {
    // return false; VS2015 : il n'y a qu'un allocateur, ils sont donc forcement identiques
    return true;
  }



  // Default constructor, copy constructor, rebinding constructor, and destructor.

  // Empty for stateless allocators.
#if !defined(CATIAR420) && !defined(CATIAV5R29) 
  // ON ne defnit pas ces constructeur pour avoir un move operator [5/22/2018 RNO]
  CATExpPoolAllocatorForBigIntTS() { }

  CATExpPoolAllocatorForBigIntTS(const CATExpPoolAllocatorForBigIntTS&) { }

  template <typename U> CATExpPoolAllocatorForBigIntTS(const CATExpPoolAllocatorForBigIntTS<U>&) { }

  ~CATExpPoolAllocatorForBigIntTS() { }
#endif
  // The following will be different for each allocator.

  

   single_uint_t * allocate(const size_t n) const;

  INLINE  void deallocate(single_uint_t * const p, const size_t n) const __EXPNOEXCEPT__ {
    // Mallocator prints a diagnostic message to demonstrate
    // what it's doing. Real allocators won't do this.
//    std::cout << "Deallocating " << n << (n == 1 ? " object" : "objects") << " of size " << sizeof(T) << "." << std::endl;
    // Mallocator wraps free().
    // _aligned_free(p);
  }

  // The following will be the same for all allocators that ignore hints.

  template <typename U> single_uint_t * allocate(const size_t n, const U * /* const hint */) const { return allocate(n);}


  // Allocators are not required to be assignable, so
  // all allocators should have a private unimplemented
  // assignment operator. Note that this will trigger the
  // off-by-default (enabled under /Wall) warning C4626
  // "assignment operator could not be generated because a
  // base class assignment operator is inaccessible" within
  // the STL headers, but that warning is useless.

private:
#if defined(CATIAR420) || defined(CATIAV5R29)
  CATExpPoolAllocatorForBigIntTS& operator=(const CATExpPoolAllocatorForBigIntTS&)=default;
#else
	CATExpPoolAllocatorForBigIntTS& operator=(const CATExpPoolAllocatorForBigIntTS&){};
#endif
};

#else
	class CATExpScopedAllocatorTS{};
//template <> void CATExpPoolAllocatorForBigIntTS<single_uint_t>::destroy(single_uint_t * const p) const { p->~single_uint_t();}
#endif



#endif
