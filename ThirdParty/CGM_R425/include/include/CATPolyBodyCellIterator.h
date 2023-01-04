// COPYRIGHT DASSAULT SYSTEMES 2022, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyBodyCellIterator.h
//
//=============================================================================
// 2022-06-07 NDO
//=============================================================================
#pragma once

#include "CATPolyBody.h"


template<class CELL>
class CATPolyBodyCellIteratorImpl
{
public:

  inline CATPolyBodyCellIteratorImpl (const CATPolyBody* iBody = 0);
  inline CATPolyBodyCellIteratorImpl (const CATPolyBody& iBody);
  inline ~CATPolyBodyCellIteratorImpl ();

public:

  inline CATPolyBodyCellIteratorImpl& Begin (const CATPolyBodyCellIteratorImpl& iOther);
  inline CATPolyBodyCellIteratorImpl& Begin (const CATPolyBody* iBody);
  inline CATPolyBodyCellIteratorImpl& Begin ();
  inline CATPolyBodyCellIteratorImpl& Reset () { return Reset (); }
  inline CATPolyBodyCellIteratorImpl& operator++ ();
  inline bool End () const;

public:

  inline CELL* Get ();
  inline CELL* operator* ();
  inline CELL* operator-> ();

private:

  const CATPolyBody* _Body;
  unsigned int _Index;
};

template<class CELL>
inline CATPolyBodyCellIteratorImpl<CELL>::CATPolyBodyCellIteratorImpl (const CATPolyBody* iBody) :
  _Body (iBody), 
  _Index (1)
{}

template<class CELL>
inline CATPolyBodyCellIteratorImpl<CELL>::CATPolyBodyCellIteratorImpl (const CATPolyBody& iBody) :
  _Body (&iBody), 
  _Index (1)
{}

template<class CELL>
inline CATPolyBodyCellIteratorImpl<CELL>::~CATPolyBodyCellIteratorImpl ()
{
  _Body = 0;
  _Index = 0;
}

template<class CELL>
inline CATPolyBodyCellIteratorImpl<CELL>& CATPolyBodyCellIteratorImpl<CELL>::Begin (const CATPolyBodyCellIteratorImpl<CELL>& iOther)
{
  _Body = iOther._Body;
  _Index = iOther._Index;
  return *this;
}

template<class CELL>
inline CATPolyBodyCellIteratorImpl<CELL>& CATPolyBodyCellIteratorImpl<CELL>::Begin (const CATPolyBody* iBody)
{
  _Body = iBody;
  _Index = 1;
  return *this;
}

template<class CELL>
inline CATPolyBodyCellIteratorImpl<CELL>& CATPolyBodyCellIteratorImpl<CELL>::Begin ()
{
  _Index = 1;
  return *this;
}

template<class CELL>
inline CATPolyBodyCellIteratorImpl<CELL>& CATPolyBodyCellIteratorImpl<CELL>::operator++ ()
{
  ++_Index;
  return *this;
}

// Specialization CATPolyVertex
template<>
inline bool CATPolyBodyCellIteratorImpl<CATPolyVertex>::End () const
{
  return _Body ? (_Body->GetNbVertices () < _Index) : true;
}

// Specialization CATPolyVertex
template<>
inline CATPolyVertex* CATPolyBodyCellIteratorImpl<CATPolyVertex>::Get ()
{
  return _Body ? _Body->GetVertex (_Index) : 0;
}

// Specialization CATPolyEdge
template<>
inline bool CATPolyBodyCellIteratorImpl<CATPolyEdge>::End () const
{
  return _Body ? (_Body->GetNbEdges () < _Index) : true;
}

// Specialization CATPolyEdge
template<>
inline CATPolyEdge* CATPolyBodyCellIteratorImpl<CATPolyEdge>::Get ()
{
  return _Body ? _Body->GetEdge (_Index) : 0;
}

// Specialization CATPolyFace
template<>
inline bool CATPolyBodyCellIteratorImpl<CATPolyFace>::End () const
{
  return _Body ? (_Body->GetNbFaces () < _Index) : true;
}

// Specialization CATPolyFace
template<>
inline CATPolyFace* CATPolyBodyCellIteratorImpl<CATPolyFace>::Get ()
{
  return _Body ? _Body->GetFace (_Index) : 0;
}

// Specialization CATPolyVolume
template<>
inline bool CATPolyBodyCellIteratorImpl<CATPolyVolume>::End () const
{
  return _Body ? (_Body->GetNbVolumes () < _Index) : true;
}

// Specialization CATPolyVolume
template<>
inline CATPolyVolume* CATPolyBodyCellIteratorImpl<CATPolyVolume>::Get ()
{
  return _Body ? _Body->GetVolume (_Index) : 0;
}

template<class CELL>
inline CELL* CATPolyBodyCellIteratorImpl<CELL>::operator* ()
{
  return Get ();
}

template<class CELL>
inline CELL* CATPolyBodyCellIteratorImpl<CELL>::operator-> ()
{
  return Get ();
}


//
// CATPolyBodyCellIterator
//
class CATPolyBodyCellIterator
{
public:

  inline CATPolyBodyCellIterator (const CATPolyBody* iBody = 0);
  inline CATPolyBodyCellIterator (const CATPolyBody& iBody);

public:

  inline CATPolyBodyCellIterator& Begin (const CATPolyBody* iBody = 0);
  inline CATPolyBodyCellIterator& operator++ ();
  inline bool End () const;

public:

  inline CATPolyCell* Get ();
  inline CATPolyCell* operator* ();
  inline CATPolyCell* operator-> ();

private:

  CATPolyBodyCellIteratorImpl<CATPolyVertex> _VertexIt;
  CATPolyBodyCellIteratorImpl<CATPolyEdge> _EdgeIt;
  CATPolyBodyCellIteratorImpl<CATPolyFace> _FaceIt;
  CATPolyBodyCellIteratorImpl<CATPolyVolume> _VolumeIt;
};

inline CATPolyBodyCellIterator::CATPolyBodyCellIterator (const CATPolyBody* iBody) :
  _VertexIt (iBody),
  _EdgeIt (iBody),
  _FaceIt (iBody),
  _VolumeIt (iBody)
{}

inline CATPolyBodyCellIterator::CATPolyBodyCellIterator (const CATPolyBody& iBody) :
  _VertexIt (iBody),
  _EdgeIt (iBody),
  _FaceIt (iBody),
  _VolumeIt (iBody)
{}

inline CATPolyBodyCellIterator& CATPolyBodyCellIterator::Begin (const CATPolyBody* iBody)
{
  _VertexIt.Begin (iBody);
  _EdgeIt.Begin (iBody);
  _FaceIt.Begin (iBody);
  _VolumeIt.Begin (iBody);
  return *this;
}

inline CATPolyBodyCellIterator& CATPolyBodyCellIterator::operator++ ()
{
  if (!_VertexIt.End ())
    ++_VertexIt;
  else if (!_EdgeIt.End ())
    ++_EdgeIt;
  else if (!_FaceIt.End ())
    ++_FaceIt;
  else
    ++_VolumeIt;
  return *this;
}

inline bool CATPolyBodyCellIterator::End () const
{
  return _VertexIt.End () && _EdgeIt.End () && _FaceIt.End () && _VolumeIt.End ();
}

inline CATPolyCell* CATPolyBodyCellIterator::Get ()
{
  if (!_VertexIt.End ())
    return (CATPolyCell*) _VertexIt.Get ();
  else if (!_EdgeIt.End ())
    return (CATPolyCell*) _EdgeIt.Get ();
  else if (!_FaceIt.End ())
    return (CATPolyCell*) _FaceIt.Get ();
  else if (!_VolumeIt.End ())
    return (CATPolyCell*) _VolumeIt.Get ();
  else
    return 0;
}

inline CATPolyCell* CATPolyBodyCellIterator::operator* ()
{
  return Get ();
}

inline CATPolyCell* CATPolyBodyCellIterator::operator-> ()
{
  return Get ();
}
