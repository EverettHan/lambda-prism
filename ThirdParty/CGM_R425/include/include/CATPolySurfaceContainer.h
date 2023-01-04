// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceContainer.h
//
//===================================================================
// August 2015  Creation: NDO
//===================================================================
#ifndef CATPolySurfaceContainer_H
#define CATPolySurfaceContainer_H

#include "PolyMeshTools.h"
#include "CATIPolySurface.h"
#include "CATIPolySurfaceIterator.h"
#include "CATListPV.h"


/**  
 * List container of CATIPolySurface instances.
 * The surfaces appended to the container are ref-counted.
 * @see CATPolySurfaceList
*/
class ExportedByPolyMeshTools CATPolySurfaceContainer
{

public:

  CATPolySurfaceContainer () {}
  ~CATPolySurfaceContainer ();

public:

  /**
    * Appends a CATIPolySurface to the container.
    */
  inline void Append (CATIPolySurface* surface);


  /**
   * Returns the number of surfaces added to the container.
   */
  inline int Size () const;

  /**
   * Returns the ith surface from the container,
   * the index i ranging from 1 to Size () included.
   * No AddRef () is called for the surface returned.
   */
  inline CATIPolySurface* operator [] (unsigned int i) const;

public:

  /**  
   * Iterator.
   * Iterates through the surfaces of the container.
   */
  class Iterator : public CATIPolySurfaceIterator
  {
  public:

    Iterator (const CATPolySurfaceContainer& iSurfaces) : _Surfaces (iSurfaces), _Index (1) {}
    ~Iterator () {}

  public:

    Iterator& Begin () {_Index = 1; return *this;}
    bool End () const {return _Index > (unsigned int) _Surfaces.Size ();}
    CATIPolySurfaceIterator& operator++ () {++_Index; return *this;}

    /* Don't release the surface returned by the iterator unless you do an AddRef () explicitely. */
    CATIPolySurface* Get () const {return _Surfaces[_Index];}
    CATIPolySurface* operator* () const {return _Surfaces[_Index];}

  private:

    const CATPolySurfaceContainer& _Surfaces;
    unsigned int _Index;

  };

private:

  CATListPV _Surfaces;

};

inline void CATPolySurfaceContainer::Append (CATIPolySurface* surface)
{
  if (surface)
  {
    _Surfaces.Append (surface);
    surface->AddRef ();
  }
}

inline int CATPolySurfaceContainer::Size () const
{
  return _Surfaces.Size ();
}

inline CATIPolySurface* CATPolySurfaceContainer::operator [] (unsigned int i) const
{
  return (CATIPolySurface*) _Surfaces[i];
}

#endif
