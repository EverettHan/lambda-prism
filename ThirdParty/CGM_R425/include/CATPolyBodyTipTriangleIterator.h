// COPYRIGHT DASSAULT SYSTEMES 2014, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyTipTriangleIterator.h
//
//===================================================================
// May 2014  Creation NDO
//===================================================================
#pragma once

#include "PolyMODEL.h"
#include "CATErrorDef.h"
#include "CATListOfInt.h"
#include "CATPoly.h"

class CATPolyBody;
class CATPolyCell;
class CATPolyFace;
class CATPolyEdgeFaceIterator;
class CATPolyVertexFaceIterator;


/**
 * Iterator through all the triangles adjacent to a tip from a CATPolyBody.
 */
class ExportedByPolyMODEL CATPolyBodyTipTriangleIterator
{

public :

  inline CATPolyBodyTipTriangleIterator (CATPolyBody& iPolyBody);

  //inline CATPolyBodyTipTriangleIterator (CATPolyBody& iPolyBody, Poly::Tip& iTip);

  inline CATPolyBodyTipTriangleIterator (CATPolyBody& iPolyBody, CATPolyCell* C, int cv);

  CATPolyBodyTipTriangleIterator (const CATPolyBodyTipTriangleIterator& iRHS);

  ~CATPolyBodyTipTriangleIterator ();

public:

  CATPolyBodyTipTriangleIterator& Begin ();
  //inline CATPolyBodyTipTriangleIterator& Begin (Poly::Tip& iTip);
  inline CATPolyBodyTipTriangleIterator& Begin (CATPolyCell* C, int cv);

  inline bool End () const;

  CATPolyBodyTipTriangleIterator& operator++ ();

public:

  inline CATPolyFace* GetFace () const;
  inline int GetTriangle () const;

  /**
   * Returns the surface vertex from the current triangle matching the tip.
   */
  inline int GetSurfaceVertex () const;

  //inline Poly::Triangle operator* () const;

private:

  CATPolyBody& _PolyBody;
  CATPolyCell* _Cell;  // Minimum cell.
  CATPolyEdgeFaceIterator* _EdgeFaceIt;
  CATPolyVertexFaceIterator* _VertexFaceIt;

  CATPolyFace* _Face;
  int _CellVertex;
  int _MeshVertex;
  unsigned int _Index;

  CATListOfInt _Triangles;

private:

  static CATPolyCell* GetMinimumCell (CATPolyCell* C, int cv, int& ci);

};


inline CATPolyBodyTipTriangleIterator::CATPolyBodyTipTriangleIterator (CATPolyBody& iPolyBody) :
  _PolyBody (iPolyBody),
  _Cell (0),
  _EdgeFaceIt (0),
  _VertexFaceIt (0),
  _Face (0),
  _CellVertex (0),
  _MeshVertex (0),
  _Index (1)
{
}

#if 0
inline CATPolyBodyTipTriangleIterator::CATPolyBodyTipTriangleIterator (CATPolyBody& iPolyBody, Poly::Tip& iTip) :
  _PolyBody (iPolyBody),
  _Cell (0),
  _EdgeFaceIt (0),
  _VertexFaceIt (0),
  _Face (0),
  _CellVertex (0),
  _MeshVertex (0),
  _Index (1)
{
  Begin ();
}
#endif

inline CATPolyBodyTipTriangleIterator::CATPolyBodyTipTriangleIterator (CATPolyBody& iPolyBody, CATPolyCell* C, int cv) :
  _PolyBody (iPolyBody),
  _Cell (0),
  _EdgeFaceIt (0),
  _VertexFaceIt (0),
  _Face (0),
  _CellVertex (0),
  _MeshVertex (0),
  _Index (1)
{
  _Cell = GetMinimumCell (C, cv, _CellVertex);
  Begin ();
}

#if 0
inline CATPolyBodyTipTriangleIterator& CATPolyBodyTipTriangleIterator::Begin (Poly::Tip& iTip)
{
  _Cell = 0;
  _CellVertex = 0;
  return Begin ();
}
#endif

inline CATPolyBodyTipTriangleIterator& CATPolyBodyTipTriangleIterator::Begin (CATPolyCell* C, int cv)
{
  _Cell = GetMinimumCell (C, cv, _CellVertex);
  return Begin ();
}

inline bool CATPolyBodyTipTriangleIterator::End () const
{
  return _Index > (unsigned int) _Triangles.Size ();
}

inline CATPolyFace* CATPolyBodyTipTriangleIterator::GetFace () const
{
  return _Face;
}

inline int CATPolyBodyTipTriangleIterator::GetTriangle () const
{
  return _Triangles[_Index];
}

inline int CATPolyBodyTipTriangleIterator::GetSurfaceVertex () const
{
  return _MeshVertex;
}

#if 0
inline Poly::Triangle CATPolyBodyTipTriangleIterator::operator* () const
{
  //return Poly::Triangle (GetFace (), GetTriangle ());
  return Poly::Triangle ();
}
#endif
