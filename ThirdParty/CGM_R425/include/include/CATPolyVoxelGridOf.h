//===================================================================
// COPYRIGHT Dassault Systemes 2019
//===================================================================
// CATPolyVoxelGridOf.cpp
// Header definition of class CATPolyVoxelGridOf
//===================================================================
//
// Usage notes:
// Voxel grid of elements
//
//===================================================================
// 07/19 - F1Z - Creation
// MM/YY
//===================================================================
#ifndef CATPolyVoxelGridOf_H
#define CATPolyVoxelGridOf_H

// Polyhedral Interfaces
#include "CATPolyRefCounted.h"

// Polyhedral Objects
#include "CATPolyVoxelPartition.h"

/**
 * Simple voxel grid structure to encapsulate a voxel grid container of type T and a voxel partition
 * The cost of the structure depend of the container choice
 */
template<typename T, typename Container>
class CATPolyVoxelGridOf : public CATPolyRefCounted
{
public:
  CATPolyVoxelGridOf(CATPolyVoxelPartition * iPartition) : _partition(iPartition)
  {
    if(_partition)
    {
      _partition->AddRef();
      _voxelGrid.Initialize(_partition->GetNbVoxels(0)*_partition->GetNbVoxels(1)*_partition->GetNbVoxels(2));
    }
  }

  virtual ~CATPolyVoxelGridOf()
  {
    if(_partition)
      _partition->Release();
  }

public:
  class Iterator
  {
  public:
    Iterator(const CATPolyVoxelGridOf & iVoxelGrid, const int iIdVoxel) : _ite(iVoxelGrid._voxelGrid, iIdVoxel) {};
    ~Iterator(){};
    Iterator & Begin() { _ite.Begin(); return *this; };
    Iterator & operator++() { ++_ite; return *this; };
    bool End() { return _ite.End(); };
    const T & operator*() { return (const T &) *_ite; };
  private:
    typename Container::Iterator _ite;
  };

public:
  inline const CATPolyVoxelPartition * GetPartition() const { return _partition; };
  inline const int                     GetSize     () const { return _voxelGrid.GetSize(); };

public:
  inline HRESULT Add   (const T & iToAdd   , const int iIdVoxel) { return _voxelGrid.Add   (iToAdd   , iIdVoxel); };
  inline HRESULT Remove(const T & iToRemove, const int iIdVoxel) { return _voxelGrid.Remove(iToRemove, iIdVoxel); };

public:
  using ContainerType = Container;

private:
  CATPolyVoxelPartition * _partition;
  Container               _voxelGrid;
};

/**
 * Dedicated interface for pointer type
 */
template<typename T, typename Container>
class CATPolyVoxelGridOf<T*, Container>
{
public:
  CATPolyVoxelGridOf(CATPolyVoxelPartition * iPartition) : _partition(iPartition)
  {
    if(_partition)
    {
      _partition->AddRef();
      _voxelGrid.Initialize(_partition->GetNbVoxels(0)*_partition->GetNbVoxels(1)*_partition->GetNbVoxels(2));
    }
  }

  virtual ~CATPolyVoxelGridOf()
  {
    if(_partition)
      _partition->Release();
  }

public:
  class Iterator
  {
  public:
    Iterator(const CATPolyVoxelGridOf & iVoxelGrid, const int iIdVoxel) : _ite(iVoxelGrid._voxelGrid, iIdVoxel) {};
    ~Iterator(){};
    Iterator & Begin() { _ite.Begin(); return *this; };
    Iterator & operator++() { ++_ite; return *this; };
    bool End() { return _ite.End(); };
    T * operator*() { return *_ite; };
  private:
    typename Container::Iterator _ite;
  };

public:
  inline const CATPolyVoxelPartition * GetPartition() const { return _partition; };
  inline const int                     GetSize     () const { return _voxelGrid.GetSize(); };

public:
  inline HRESULT Add   (T * iToAdd   , const int iIdVoxel) { return _voxelGrid.Add   (iToAdd   , iIdVoxel); };
  inline HRESULT Remove(T * iToRemove, const int iIdVoxel) { return _voxelGrid.Remove(iToRemove, iIdVoxel); };

private:
  CATPolyVoxelPartition * _partition;
  Container               _voxelGrid;
};


#endif
