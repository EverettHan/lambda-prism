//===================================================================
// COPYRIGHT Dassault Systemes 2019
//===================================================================
// ArrayOfSet.h
// Header definition of class ArrayOfSet
//===================================================================
//
// Usage notes:
// Array of poly set.
// Example of use: content for a voxel grid.
//
//===================================================================
// 07/19 - F1Z - Creation
// MM/YY
//===================================================================
#ifndef ArrayOfSet_H
#define ArrayOfSet_H

#include "Poly/Set.h"

#include <stdlib.h> 
#include <string.h>

namespace Poly
{
  /**
   * Container for cell element
   * Each grid case has an associated set to store the element T (unique element per set)
   * Cost: in average O(1) to insert, O(1) to remove.
   *       worse case O(N) to insert, O(N) to remove.
   */
   template<typename T>
   class ArrayOfSet
   {
   public:
     ArrayOfSet() : _sets(0), _nbSets(0) {};
     virtual ~ArrayOfSet();

     /**
      * Initialisation of the array of set
      * This should be call once
      */
      void Initialize(const int iNbSets);

      inline int Size() const { return _nbSets; };
      inline int GetSize(int iIdSet) const { return _sets[iIdSet]? _sets[iIdSet]->Size() : 0; };

      HRESULT Add   (const T & iToAdd   , const int iIdSet);
      HRESULT Remove(const T & iToRemove, const int iIdSet);

      class Iterator
      {
      public:
        Iterator(const ArrayOfSet & iContainer, int iIdSet) : _ite(iContainer._sets[iIdSet]==0? iContainer._emptySet : *iContainer._sets[iIdSet]) {};
        virtual ~Iterator(){};

        Iterator & Begin() { _ite.Begin(); return *this; };
        Iterator & operator++() { ++_ite; return *this; };
        bool End() { return _ite.End(); };
        const T & operator*() { return *_ite; };

      private:
        typename Poly::Set<T>::Iterator _ite;
      };
      friend Iterator;

   private:
     Poly::Set<T>    ** _sets;
     int                _nbSets;

     const Poly::Set<T> _emptySet;
   };

   template<typename T>
   ArrayOfSet<T>::~ArrayOfSet()
   {
     if (_sets)
     {
       int k = 0;
       for (; k < _nbSets; ++k)
       {
         if (_sets[k] != 0)
           delete _sets[k];
       }
       delete[] _sets;
       _sets = 0;
     }
   }
   template<typename T>
   void ArrayOfSet<T>::Initialize(const int iNbSets)
   {  
     _nbSets = iNbSets;
     // JXO on 2020/05/18 to prevent NSA
     int preventnsa = CATMax(1, _nbSets);
     _sets = new Poly::Set<T>*[preventnsa];
     memset(_sets,0, preventnsa *sizeof(Poly::Set<T>*));
   }

   template<typename T>
   HRESULT ArrayOfSet<T>::Add(const T & iToAdd, const int iIdSet)
   {
     HRESULT hr = S_OK;

     if (_sets[iIdSet] == 0)
       _sets[iIdSet] = new Poly::Set<T>(1);

     if (_sets[iIdSet])
       hr = _sets[iIdSet]->Insert(iToAdd);
     else
       hr = E_FAIL; // shouldn't get here

     return hr;
   }

   template<typename T>
   HRESULT ArrayOfSet<T>::Remove(const T & iToRemove, const int iIdSet)
   {
     HRESULT hr = S_FALSE;

     if (_sets[iIdSet])
       hr = _sets[iIdSet]->Remove(iToRemove);

     return hr;
   }

   // ----------------------------------------------------------------------- //
 
   template<typename T>
   class ArrayOfSet<T*>
   {
   public:
     ArrayOfSet() : _sets(0), _nbSets(0) {};
     ~ArrayOfSet();

     /**
      * Initialisation of the array of set
      * This should be call once
      */
      void Initialize(const int iNbSets);

      inline int Size() const { return _nbSets; };
      inline int GetSize(int iIdSet) const { return _sets[iIdSet]? _sets[iIdSet]->Size() : 0; };

      HRESULT Add   (T * iToAdd   , const int iIdSet);
      HRESULT Remove(T * iToRemove, const int iIdSet);

      class Iterator
      {
      public:
        Iterator(const ArrayOfSet<T*> & iContainer, int iIdSet) : _ite(iContainer._sets[iIdSet]==0? iContainer._emptySet : *iContainer._sets[iIdSet]) {};
        ~Iterator(){};

        Iterator & Begin() { _ite.Begin(); return *this; };
        Iterator & operator++() { ++_ite; return *this; };
        bool End() { return _ite.End(); };
        T * operator*() { return *_ite; };

      private:
        typename Poly::Set<T*>::Iterator _ite;
      };
      friend Iterator;

   private:
     Poly::Set<T*>    ** _sets;
     int                 _nbSets;

     const Poly::Set<T*> _emptySet;
   };

   template<typename T>
   ArrayOfSet<T*>::~ArrayOfSet()
   {
     if (_sets)
     {
       int k = 0;
       for (; k < _nbSets; ++k)
       {
         if (_sets[k] != 0)
           delete _sets[k];
       }
       delete[] _sets;
       _sets = 0;
     }
   }

   template<typename T>
   void ArrayOfSet<T*>::Initialize(const int iNbSets)
   {  
     _nbSets = iNbSets;
     // JXO on 2020/05/18 to prevent NSA
     int preventnsa = CATMax(1, _nbSets);
     _sets = new Poly::Set<T*>*[preventnsa];
     memset(_sets,0, preventnsa *sizeof(Poly::Set<T*>*));
   }

   template<typename T>
   HRESULT ArrayOfSet<T*>::Add(T * iToAdd, const int iIdSet)
   {
     HRESULT hr = S_OK;

     if (_sets[iIdSet] == 0)
       _sets[iIdSet] = new Poly::Set<T*>();

     if (_sets[iIdSet])
       hr = _sets[iIdSet]->Insert(iToAdd);
     else
       hr = E_FAIL; // shouldn't get here

     return hr;
   }

   template<typename T>
   HRESULT ArrayOfSet<T*>::Remove(T * iToRemove, const int iIdSet)
   {
     HRESULT hr = S_FALSE;

     if (_sets[iIdSet])
       hr = _sets[iIdSet]->Remove(iToRemove);

     return hr;
   }
};



#endif
