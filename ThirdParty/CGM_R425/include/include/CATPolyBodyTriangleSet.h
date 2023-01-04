// COPYRIGHT DASSAULT SYSTEMES 2018, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyTriangleSet.h
//
//===================================================================
// July 2018  Creation: NDO
//===================================================================
#ifndef CATPolyBodyTriangleSet_H
#define CATPolyBodyTriangleSet_H

#include "PolyMeshImpl.h"
#include "CATMapOfPtrToPtr.h"
#include "CATSetOfInt.h"

class CATPolyFace;


/**
 * A set of triangles from a CATPolyBody.
 */
class ExportedByPolyMeshImpl CATPolyBodyTriangleSet
{

public:

  inline CATPolyBodyTriangleSet (const unsigned int iEstimatedNbFaces = 0);

  ~CATPolyBodyTriangleSet ();

public:

  /**
   * Inserts a triangle in the set.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> when the triangle is inserted in the set.
   *   <li> <tt>S_FALSE</tt> when the triangle is already found in the set.
   *   <li> <tt>E_FAIL</tt> when any error occurs (memory allocation failure).
   * </ul>
   */
  HRESULT Insert (CATPolyFace* F, int t);

  /**
   * Removes a triangle from the set.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> when the triangle is removed from the set.
   *   <li> <tt>S_FALSE</tt> when the triangle is not found in the set.
   * </ul>
   */
  HRESULT Remove (CATPolyFace* F, int t);

  /**
   * Removes all the triangles from the set.
   */
  HRESULT RemoveAll ();

  /**
   * Returns the set of triangles for a given face.
   */
  const CATSetOfInt* Find (CATPolyFace* F) const;

  /**
   * Finds a triangle from the set.
   */
  bool Find (CATPolyFace* F, int t) const;

  /**
   * Returns the number of faces in the set.
   */
  inline unsigned int GetNbFaces () const;

  /**
   * Returns the total number of triangles from the given face in the set.
   */
  unsigned int GetNbTriangles (CATPolyFace* F) const;

  /**
   * Returns the total number of triangles in the set.
   */
  unsigned int GetNbTriangles () const;

public:

  /**
   * Iterator cycling through all the faces in the set.
   */
  class FaceIterator
  {
  public:

    FaceIterator (const CATPolyBodyTriangleSet& s) : _It (s._FaceMap) {}
    ~FaceIterator () {}

    FaceIterator& Begin () {_It.Begin (); return *this;}
    bool End () {return _It.End () ? true : false;}
    FaceIterator& operator++ () {++_It; return *this;}

    /**
     * Returns the current face.
     */
    CATPolyFace* Face () const {return (CATPolyFace*) _It.GetKey ();}

    /**
     * Returns the set of triangles for the current face.
     */
    const CATSetOfInt* GetTriangles () const { return (const CATSetOfInt*) _It.GetData (); }

  private:

    CATMapOfPtrToPtr::Iterator _It;

  };

public:

  /**
   * Iterator cycling through all the triangles from the set.
   */
  class Iterator
  {
  public:

    Iterator (const CATPolyBodyTriangleSet& s) : _FaceIt (s) {Begin ();}
    ~Iterator () {}

    Iterator& Begin ();
    bool End () { return _TriangleIt.End () ? true : false; }
    Iterator& operator++ ();

    CATPolyFace* Face () const { return _FaceIt.Face (); }
    int Triangle () const { return *_TriangleIt; }

  private:

    FaceIterator _FaceIt;
    CATSetOfInt::Iterator _TriangleIt;

  };

private:

  CATMapOfPtrToPtr _FaceMap;

  friend class FaceIterator;

};

inline CATPolyBodyTriangleSet::CATPolyBodyTriangleSet (const unsigned int iEstimatedSize) :
  _FaceMap (iEstimatedSize)
{
}

inline unsigned int CATPolyBodyTriangleSet::GetNbFaces () const
{
  return _FaceMap.Size ();
}

#endif
