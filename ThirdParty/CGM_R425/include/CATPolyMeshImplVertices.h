// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMeshImplVertices.cpp
//
//===================================================================
// May 2015 Creation: NDO Migration from CATPolyMeshImpl
//===================================================================
#ifndef CATPolyMeshImplVertices_H
#define CATPolyMeshImplVertices_H

#include "CATPolyBuckets.h"


/**
 * Vertex data structure.
 */
class CATPolyMeshImplVertex
{

public:

  inline CATPolyMeshImplVertex ();
  inline CATPolyMeshImplVertex (bool);
  inline ~CATPolyMeshImplVertex ();

  inline CATBoolean IsDefined () const;
  inline void Undefine ();

public:

  inline void Recycle ();
  void Clear ();  // Clears the list of triangles.
  void Absorb (CATPolyMeshImplVertex& iRHS);

public:

  HRESULT Insert (unsigned int t);
  CATBoolean Remove (unsigned int t);

  inline unsigned int GetNbTriangles () const;
  inline unsigned int GetTriangle (unsigned int t) const;

//private:
public:

  unsigned int _Defined  :  1;
  unsigned int _ABit     :  1;
  unsigned int _NbTriangles: 15;
  unsigned int _TriangleListSize: 15;

  union
  {
    unsigned int  _T;
    unsigned int* _List;
  } _Triangle;

//private: 
  //CATPolyMeshImplVertex& operator= (const CATPolyMeshImplVertex& iRHS);
};

inline CATPolyMeshImplVertex::CATPolyMeshImplVertex () :
  _Defined (0),
  _ABit (0),
  _NbTriangles (0),
  _TriangleListSize (0)
{
  _Triangle._List = 0;
}

inline CATPolyMeshImplVertex::CATPolyMeshImplVertex (bool) :
  _Defined (1),
  _ABit (0),
  _NbTriangles (0),
  _TriangleListSize (0)
{
  _Triangle._List = 0;
}

inline CATPolyMeshImplVertex::~CATPolyMeshImplVertex ()
{
  Clear ();
}

inline CATBoolean CATPolyMeshImplVertex::IsDefined () const
{
  return _Defined;
}

inline void CATPolyMeshImplVertex::Undefine ()
{
  _Defined = 0;
}

inline void CATPolyMeshImplVertex::Recycle ()
{
  _Defined = 1;
  _NbTriangles = 0; // Keep allocated list of triangles.
}

inline unsigned int CATPolyMeshImplVertex::GetNbTriangles () const
{
  return _NbTriangles;
}

inline unsigned int CATPolyMeshImplVertex::GetTriangle (unsigned int e) const // WARNING: Valid if 0 < e and e <= _NbTriangles.
{
  if (_TriangleListSize)
    return _Triangle._List[e - 1];
  return _Triangle._T;
}


/**
 * Buckets of vertices for implementation of CATPolyMeshImpl.
 */
class CATPolyMeshImplVertices : public CATPolyBuckets<CATPolyMeshImplVertex>
{

public:

  CATPolyMeshImplVertices () {}
  ~CATPolyMeshImplVertices () {}

};

#endif // !CATPolyMeshImplVertices_H
