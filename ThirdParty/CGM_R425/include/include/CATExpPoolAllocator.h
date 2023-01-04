//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2013
//==============================================================================================================
// Usage notes:
//    RAII
//==============================================================================================================
// 2015-10-XX - RNO/TYF : PLEASE USE NOW THE THREADSAFEVERSION (TS)
// 2013-05-03 - T6L : Creation
//==============================================================================================================



#ifndef CATExpPoolAllocator_H
#define CATExpPoolAllocator_H


#include <algorithm>
#include <deque>
#include <vector>

//#if defined (_WINDOWS_SOURCE)
//#define thread_local __declspec(thread)  
//#else
//#define thread_local __thread
//#endif

//#define DEBUG
#ifdef DEBUG
#include <typeinfo>
#endif


/**
* Class managing memory for cheap dynamic allocation.
* First, the user supplies a statically allocated array.
* If this array happens to be not sufficient, then other arrays of memory are allocated as things go along.
*/
template <typename T>
class CATExpPoolAllocator
{
public:
  /**
  * @param memory_area is a pointer to an array allocated by the user.
  * @param capacity is the number of objects of the provided array
      (which is used also as the capacity to dynamically allocate if necessary). 
  */
  CATExpPoolAllocator(T *memory_area = nullptr, std::size_t capacity = 0)
  : default_capacity_(capacity ? capacity : 1000000), max_capacity_(capacity), 
    used_capacity_(0),
    memory_area_(memory_area), next_free_chunk_(memory_area),
    previous_pool_allocator_(active_pool_allocator_)
  { active_pool_allocator_ = this; }

  ~CATExpPoolAllocator()
  {
#ifdef DEBUG
      size_t nb_arrays = spare_memory_.size();
      size_t total_used_capacity = nb_arrays ? default_capacity_ : used_capacity_;
      for (std::deque<std::vector<T> >::const_iterator i = spare_memory_.begin(); i < spare_memory_.end(); ++i)
        total_used_capacity += i->size();
      printf("Number of %s provided by pool: %u\n", typeid(T).name(), total_used_capacity);
      //printf("Number of extra dynamically allocated arrays: %u\n", nb_arrays);
#endif
      active_pool_allocator_ = previous_pool_allocator_;
  }

  static const CATExpPoolAllocator<T> *CurrentAllocator() { return active_pool_allocator_; } 

  T* allocate(std::size_t nb_objects) const
  {
    if (nb_objects == 0) return nullptr;
    used_capacity_ += nb_objects;
    if (used_capacity_ > max_capacity_)
    {
      max_capacity_ = std::max<size_t>(default_capacity_, nb_objects);
      spare_memory_.push_back(std::vector<T>(max_capacity_));
      used_capacity_ = nb_objects;
      T *next = &spare_memory_.back()[0];
      next_free_chunk_ = next + nb_objects;
      return next;
    }
    else
    {
      T *next = next_free_chunk_;
      next_free_chunk_ += nb_objects;
      return next;
    }
  }

private:
  const size_t default_capacity_;
  mutable size_t max_capacity_, used_capacity_;
  T *const memory_area_;
  mutable T *next_free_chunk_;
  mutable std::deque<std::vector<T> > spare_memory_;
  //thread_local
  static const CATExpPoolAllocator *active_pool_allocator_;
  const CATExpPoolAllocator *const previous_pool_allocator_; 
};


template <typename T> class CATExpScopedAllocator;
//template <typename T> CATExpScopedAllocator<T> MakeCATExpFastAllocator();

template <typename T>
class CATExpScopedAllocator
{
  template <class A, class B>
  friend inline bool operator==(const CATExpScopedAllocator<A> &a, const CATExpScopedAllocator<B> &b)
  { return false; }

  template <class A, class B>
  friend inline bool operator!=(const CATExpScopedAllocator<A> &a, const CATExpScopedAllocator<B> &b)
  { return true; }

public:
  typedef T value_type;

  CATExpScopedAllocator()
  : pool_allocator_(CATExpPoolAllocator<T>::CurrentAllocator()) {} 

  CATExpScopedAllocator(const CATExpScopedAllocator<T> &other)
  : pool_allocator_(CATExpPoolAllocator<T>::CurrentAllocator()) {}

  CATExpScopedAllocator(CATExpScopedAllocator<T> &&other)
  : pool_allocator_(CATExpPoolAllocator<T>::CurrentAllocator()) {}

  //CATExpFastAllocator<T> select_on_container_copy_construction () { return CATExpFastAllocator(); }
  //typedef std::true_type propagate_on_container_copy_assignment;
  //typedef std::true_type propagate_on_container_move_assignment;
  //typedef std::true_type propagate_on_container_swap;

  T* allocate(std::size_t nb_objects) const
  { return pool_allocator_->allocate(nb_objects); }

  void deallocate(T* p, std::size_t nb_objects) const {}

  template <typename U>
  struct rebind { typedef CATExpScopedAllocator<U> other; };

private:
  const CATExpPoolAllocator<T> *pool_allocator_;
};


//template <typename T>
//inline T *CATExpNewArray(size_t nb_objects)
//{ return CATExpAllocatorsTable<T>::NewArray(nb_objects); }
//
//template <typename T>
//inline T *CATExpNewCopy(T value)
//{ 
//  T *res = CATExpAllocatorsTable<T>::NewArray(1);
//  *res = value;
//  return res;
//}
//
//template <typename T>
//static T *CATExpCopyArray (T *source, size_t nb_objects)
//{
//  T *res = CATExpAllocatorsTable<T>::NewArray(nb_objects);
//  std::copy_n(source, nb_objects, res);
//  //T *r = res;
//  //for (size_t i = 0; i < nb_objects; i++) *r++ = *source++;
//  return res;
//}
//
//




#endif

