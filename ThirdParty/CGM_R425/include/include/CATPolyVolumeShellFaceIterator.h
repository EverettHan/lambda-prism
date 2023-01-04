// COPYRIGHT DASSAULT SYSTEMES 2022, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyVolumeShellFaceIterator
//
//=============================================================================
// June 2022 - NDO
//=============================================================================
#pragma once

#include "PolyMODEL.h"
#include "CATPolyMicroTopologyFwd.h"
#include "CATPolyMacroTopologyFwd.h"
#include "CATPolyVolumeShell.h"


/**
 * Iterator through all the faces across a volume-shell.
 * This iterator cycles through the faces across the shell once and only once.
 */
class ExportedByPolyMODEL CATPolyVolumeShellFaceIterator
{

public:

  inline CATPolyVolumeShellFaceIterator (const CATPolyVolumeShell* L = 0);
  inline ~CATPolyVolumeShellFaceIterator ();

public:

  inline CATPolyVolumeShellFaceIterator& Begin ();
  CATPolyVolumeShellFaceIterator& Begin (const CATPolyVolumeShell* SH);
  inline CATPolyVolumeShellFaceIterator& Begin (const CATPolyVolumeShell& SH);
  inline bool End () const;
  inline CATPolyVolumeShellFaceIterator& operator++ ();

public:

  /**
   * Returns the current face.
   */
  inline CATPolyFace* operator* () const;

  /**
   * Returns the current face.
   */
  inline CATPolyFace* GetFace () const;

  /**
   * Returns the adjacent volume across the face (may be null.)
   */
  inline CATPolyVolume* GetAdjacentVolume () const;

#ifndef _AIX_SOURCE
private:
#else
public:
#endif

  class VolumeShellFaceIterator
  {
  public:
    virtual ~VolumeShellFaceIterator () {}
    virtual bool End () const = 0;
    virtual void operator++ () = 0;
    virtual CATPolyFace* GetFace () const = 0;
    virtual CATPolyVolume* GetAdjacentVolume () const = 0;

    //virtual VolumeShellFaceIterator* Clone () const = 0;
  };

  CATPolyVolumeShell _VolumeShell;
  VolumeShellFaceIterator* _Iterator;

  template<class DART> friend class VolumeShellFaceIteratorImpl;
};


inline CATPolyVolumeShellFaceIterator::CATPolyVolumeShellFaceIterator (const CATPolyVolumeShell* SH) :
  _Iterator (0)
{
  Begin (SH);
}

inline CATPolyVolumeShellFaceIterator::~CATPolyVolumeShellFaceIterator ()
{
  delete _Iterator;
  _Iterator = 0;
}

inline CATPolyVolumeShellFaceIterator& CATPolyVolumeShellFaceIterator::Begin ()
{
  return Begin (&_VolumeShell);
}

inline CATPolyVolumeShellFaceIterator& CATPolyVolumeShellFaceIterator::Begin (const CATPolyVolumeShell& SH)
{
  return Begin (&SH);
}

inline bool CATPolyVolumeShellFaceIterator::End () const
{
  return _Iterator ? _Iterator->End () : true;
}

inline CATPolyVolumeShellFaceIterator& CATPolyVolumeShellFaceIterator::operator++ ()
{
  if (_Iterator)
    ++(*_Iterator);
  return *this;
}

inline CATPolyFace* CATPolyVolumeShellFaceIterator::operator* () const
{
  return _Iterator ? _Iterator->GetFace () : 0;
}

inline CATPolyFace* CATPolyVolumeShellFaceIterator::GetFace () const
{
  return _Iterator ? _Iterator->GetFace () : 0;
}

inline CATPolyVolume* CATPolyVolumeShellFaceIterator::GetAdjacentVolume () const
{
  return _Iterator ? _Iterator->GetAdjacentVolume () : 0;
}
