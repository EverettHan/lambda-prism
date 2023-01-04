// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolySurfaceIterator.h
//
//===================================================================
//
// Iterate through CATIPolySurface's. 
// Example:
//
// CATIPolySurfaceIterator* it = 0;
// if (SUCCEDED (MyObject.GetSurfaceIterator (it) && it))
// {
//   for (it->Begin (); !it->End (); ++(*it))
//   {
//     CATIPolySurface* surface = it->Get ();   
//     //OR: CATIPolySurface* surface = **it;
//     if (surface)
//     {
//     }
//   }
//   delete it;
//   it = 0;
// }
//
//===================================================================
// April 2009  Creation: NDO
//===================================================================
#ifndef CATIPolySurfaceIterator_H
#define CATIPolySurfaceIterator_H

class CATIPolySurface;
class CATPolyFace;


class CATIPolySurfaceIterator
{
public:

  virtual ~CATIPolySurfaceIterator () {}

public:

  virtual CATIPolySurfaceIterator& Begin () = 0;
  virtual bool End () const = 0;
  virtual CATIPolySurfaceIterator& operator++ () = 0;

  virtual CATPolyFace* GetFace () const { return 0; }
  virtual CATIPolySurface* GetSurface () const { return Get (); }

public:

  /* Don't release the surface returned by the iterator unless you call AddRef () explicitely. */
  virtual CATIPolySurface* Get () const = 0;
  virtual CATIPolySurface* operator* () const = 0;

};

#endif // !CATIPolySurfaceIterator_H
