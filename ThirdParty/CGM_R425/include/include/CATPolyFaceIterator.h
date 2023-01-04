#pragma once

class CATPolyFace;
class CATIPolySurface;

class CATPolyFaceIterator
{
public:

  virtual CATPolyFaceIterator& Begin () = 0;
  virtual bool End () const = 0;
  virtual CATPolyFaceIterator& operator++ () = 0;

public:

  virtual CATPolyFace* Get () const = 0;
  virtual CATIPolySurface* GetSurface () const = 0;

public:

  ~CATPolyFaceIterator () {}

};
