// COPYRIGHT DASSAULT SYSTEMES 2005, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceVertexNNormalsLayer.h
// Header definition of CATPolySurfaceVertexNNormalsLayer
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// September 2005 Creation: ndo
//===================================================================
#ifndef CATPolySurfaceVertexNNormalsLayer_H
#define CATPolySurfaceVertexNNormalsLayer_H

#include "PolyMeshImpl.h"
#include "CATPolyRefCounted.h"
#include "CATPolyBuckets_T.h"
#include "CATErrorDef.h"     // HRESULT definition
#include "CATListPV.h"
#include "CATListOfInt.h"

class CATIPolySurface;
class CATMathVector;


/*
Implementation class for vertex normal attributes. 
This class defines a layer of normals that can be associated to each vertex of a surface.
There can be as many normals at a vertex as the number of surface supports the vertex belongs to.
Each normal at a vertex is associated to the key of a surface support.
*/
class ExportedByPolyMeshImpl CATPolySurfaceVertexNNormalsLayer : public CATPolyRefCounted
{

public:

  CATPolySurfaceVertexNNormalsLayer (const CATIPolySurface& iSurface);

  virtual ~CATPolySurfaceVertexNNormalsLayer ();

  /**
   * Set a normal at a vertex for a given key of the surface support.
   */
  HRESULT Set (const int iIdxVertex, const CATMathVector& iNormal, const int iKeySupport = 0);

  /**
   * Get the normal at a vertex for a given key of the surface support.
   */
  HRESULT Get (const int iIdxVertex, CATMathVector& oNormal, const int iKeySupport = 0) const;

  /**
   * Unset the normal at a vertex for a given key of the surface support.
   */
  HRESULT Unset (const int iIdxVertex, const int iKeySupport);

  /**
   * Get the number of normals at a vertex (equivalently, the number of support the vertex belongs to).
   */
  int GetNbNormals (const int iKeySupport) const;

  /*
   * Return the keys of the normals at a vertex.
   */
  HRESULT GetIndices (const int iIdxVertex, CATListOfInt& oKeySupportList) const;

private:

  inline int PushBack ();           // Add a slot for a vertex.
  inline void Reset (const int v);  // Reset a slot for a vertex (undefined vertex).

private:

  struct Normal 
  {
    float _X;
    float _Y;
    float _Z;
    int _KeySupport;
    int _KeyInNormalList;

    Normal () : 
      _X (0),
      _Y (0),
      _Z (0),
      _KeySupport (0),
      _KeyInNormalList (0)
      {} ;

    void Reset ();
  };

  // Buckets of normals.
  class Specialize_CATPolyBuckets_T (NormalBuckets, Normal);

private:

  const CATIPolySurface& _Surface;

  NormalBuckets _Normals;
  CATListPV _ListOfNormals;

};


inline int CATPolySurfaceVertexNNormalsLayer::PushBack ()
{
  return _Normals.PushBack (Normal ());
}

void CATPolySurfaceVertexNNormalsLayer::Reset (const int v)
{
  if (0 < v && v <= (int) _Normals.Size ())
  {
    _Normals[v].Reset ();
  }
}

#endif
