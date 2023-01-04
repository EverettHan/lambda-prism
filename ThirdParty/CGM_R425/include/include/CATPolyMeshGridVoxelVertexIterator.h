// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMeshGridVoxelVertexIterator.h
// Header definition of CATPolyMeshGridVoxelVertexIterator
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// November 2007 Creation: ndo
//===================================================================
#ifndef CATPolyMeshGridVoxelVertexIterator_H
#define CATPolyMeshGridVoxelVertexIterator_H

#include "PolyPartitions.h"
#include "CATBoolean.h"

class CATPolyMeshGridVoxel;


class ExportedByPolyPartitions CATPolyMeshGridVoxelVertexIterator
{

public:

  CATPolyMeshGridVoxelVertexIterator (const CATPolyMeshGridVoxel& iVoxel);
  inline ~CATPolyMeshGridVoxelVertexIterator ();

public:

  CATPolyMeshGridVoxelVertexIterator& Begin (const CATPolyMeshGridVoxel& iVoxel);
  inline CATBoolean End() const;

public:

  inline int Get ();
  inline int operator* ();
  inline int operator-> ();

public:

  inline CATPolyMeshGridVoxelVertexIterator& operator++ ();

private :

  // No implementation of copy constructor and operator =.
  CATPolyMeshGridVoxelVertexIterator (const CATPolyMeshGridVoxelVertexIterator& iOther) ;
  CATPolyMeshGridVoxelVertexIterator& operator = (const CATPolyMeshGridVoxelVertexIterator& iOther) ;  

private:

  int* _IndexPointer;
  int _IndexCount;

};


inline CATPolyMeshGridVoxelVertexIterator::~CATPolyMeshGridVoxelVertexIterator ()
{
  _IndexPointer = 0;
}

inline CATBoolean CATPolyMeshGridVoxelVertexIterator::End () const
{
  return _IndexPointer ? FALSE : TRUE;
}

inline int CATPolyMeshGridVoxelVertexIterator::Get ()
{
  return _IndexPointer ? *_IndexPointer : 0;
}

inline int CATPolyMeshGridVoxelVertexIterator::operator* ()
{
  return _IndexPointer ? *_IndexPointer : 0;
}

inline int CATPolyMeshGridVoxelVertexIterator::operator-> ()
{
  return _IndexPointer ? *_IndexPointer : 0;
}

inline CATPolyMeshGridVoxelVertexIterator& CATPolyMeshGridVoxelVertexIterator::operator++ ()
{
  --_IndexCount;
  _IndexPointer = (_IndexCount > 0) ? ++_IndexPointer : 0;
  return *this;
}

#endif
