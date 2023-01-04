// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyDartLink
//
//=============================================================================
// 2009-11-03  NDO: New
//=============================================================================
#pragma once


// This class is not virtual.
template<class DART>
class CATPolyDartLink
{

public:

  inline CATPolyDartLink (DART* iDart, CATPolyDartLink* iNext = 0);
  inline ~CATPolyDartLink ();  // Not virtual.

public:

  inline const DART* GetDart () const;
  inline DART* GetDart ();

public:

  inline const CATPolyDartLink* GetNext () const;
  inline CATPolyDartLink* GetNext ();

  inline void SetNext (CATPolyDartLink *iRHS);

public:

  // Reserved.
  inline void SetDart (DART* d);

  inline CATPolyDartLink (const CATPolyDartLink& iRHS);
  inline CATPolyDartLink& operator = (const CATPolyDartLink& iRHS);

protected:

  DART* _Dart;
  CATPolyDartLink* _Next;

};

template<class DART>
inline CATPolyDartLink<DART>::CATPolyDartLink (DART* iDart, CATPolyDartLink* iNext) :
  _Dart (iDart),
  _Next (iNext)
{
}

template<class DART>
inline CATPolyDartLink<DART>::~CATPolyDartLink ()
{
  _Dart = 0;
  _Next = 0;
}

template<class DART>
inline const DART* CATPolyDartLink<DART>::GetDart () const
{
  return _Dart;
}

template<class DART>
inline DART* CATPolyDartLink<DART>::GetDart ()
{
  return _Dart;
}

template<class DART>
inline void CATPolyDartLink<DART>::SetDart (DART* iDart)
{
  _Dart = iDart;
}

template<class DART>
inline const CATPolyDartLink<DART>* CATPolyDartLink<DART>::GetNext () const
{
  return _Next;
}

template<class DART>
inline CATPolyDartLink<DART>* CATPolyDartLink<DART>::GetNext ()
{
  return _Next;
}

template<class DART>
inline void CATPolyDartLink<DART>::SetNext (CATPolyDartLink* iRHS)
{
  _Next = iRHS;
}

template<class DART>
inline CATPolyDartLink<DART>::CATPolyDartLink (const CATPolyDartLink& iRHS) :
  _Dart (iRHS._Dart),
  _Next (iRHS._Next)
{
}

template<class DART>
inline CATPolyDartLink<DART>& CATPolyDartLink<DART>::operator = (const CATPolyDartLink& iRHS)
{
  _Dart = iRHS._Dart;
  _Next = iRHS._Next;
  return *this;
}
