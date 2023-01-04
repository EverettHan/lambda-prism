//=============================================================================
// COPYRIGHT Dassault Systemes 2006
//=============================================================================
//
// CATPolyDart
//
// This is an INTERNAL class which is visible only for performance sake. You
// SHALL NOT use it explicitely. If you ever dare to do so, you will face the
// terrible divine power of Bahamut, Fenrir, Kirin and all other Final
// Fantasies' summons. You are stronly suggested to close this file and forget
// it even exists.
//
//=============================================================================
// 2006-08-27   BPG: New
// 2022-02-02   NDO: Extension from 2D to 3D generalized maps.
//=============================================================================
#pragma once

#include "PolyMODEL.h"
#include "CATPolyMicroTopologyFwd.h"
#include "CATPolyMacroTopologyFwd.h"
#include "CATIPolyCurve.h"
#include "CATIPolyPoint.h"

//#define TAG_CATPOLYDART 1


/**
* Implementation of darts (ND generalized maps).
*
* Do not include this file. 
* Reserved to exclusive PolyhedralObjects usage.
*
*/
template<size_t N>
class ExportedByPolyMODEL CATPolyDart
{

public:

  CATPolyDart ();
  CATPolyDart (CATIPolyPoint& P);
  ~CATPolyDart ();

public:

  // G-Map

  inline static size_t Dimension ();

  template<size_t I>
  inline HRESULT SetAlpha (CATPolyDart* iAlpha);

  template<size_t I>
  inline CATPolyDart* GetAlpha ();

  template<size_t I>
  inline const CATPolyDart* GetAlpha () const;

  inline CATPolyDart* GetAlpha (size_t i);

  inline const CATPolyDart* GetAlpha (size_t i) const;

  // Homogenize i and j cells and do sew by alpha-I.
  template<size_t I>
  static HRESULT Sew (CATPolyDart& u, CATPolyDart& v);

  template<size_t I>
  static HRESULT Unsew (CATPolyDart& u, CATPolyDart& v);

  static HRESULT Unsew (size_t i, CATPolyDart& u, CATPolyDart& v);

  // Returns true if dart is I-free.
  template<size_t I>
  inline bool IsFree () const;

  inline bool IsAllFree () const;

  HRESULT UnsewAll ();

public:

  // Cells

  inline HRESULT SetCell (CATPolyCell& iCell);

  template<size_t I>
  inline CATPolyCell* GetCell () const;

  inline CATPolyCell* GetCell (unsigned int i) const;

  template<size_t I>
  inline CATPolyCell* DetachCell ();

  // See CATPolyDartHelpers.
  //template<size_t I>
  //CATPolyCellOrbit GetOrbit () const;

  // See CATPolyDartHelpers.
  //CATPolyCellOrbit GetOrbit (unsigned int i) const;

  inline HRESULT SetVertex (CATPolyVertex& iVertex);
  inline CATPolyVertex* GetVertex () const;
  inline CATPolyVertex* DetachVertex ();

  inline HRESULT SetEdge (CATPolyEdge& iEdge);
  inline CATPolyEdge* GetEdge () const;
  inline CATPolyEdge* DetachEdge ();

  inline HRESULT SetFace (CATPolyFace& iFace);
  inline CATPolyFace* GetFace () const;
  inline CATPolyFace* DetachFace ();

  inline HRESULT SetVolume (CATPolyVolume& iVolume);
  inline CATPolyVolume* GetVolume () const;
  inline CATPolyVolume* DetachVolume ();

public:

  // Geometry

  inline HRESULT SetPoint (CATIPolyPoint* iPoint);
  inline CATIPolyPoint* GetPoint ();
  inline const CATIPolyPoint* GetPoint () const;
  inline HRESULT DetachPoint ();

  inline HRESULT SetCurve (CATIPolyCurve& iCurve);
  inline CATIPolyCurve* GetCurve ();
  inline const CATIPolyCurve* GetCurve () const;
  inline HRESULT DetachCurve ();

public:

  // G-Map

  inline HRESULT SetAlpha0 (CATPolyDart* iAlpha);
  inline CATPolyDart* GetAlpha0 ();
  inline const CATPolyDart* GetAlpha0 () const;

  // Homogenize i and j cells (except vertex) and do sew by alpha0.
  static inline HRESULT Sew0 (CATPolyDart& i, CATPolyDart& j);
  static inline HRESULT Unsew0 (CATPolyDart& i, CATPolyDart& j);

  inline HRESULT SetAlpha1 (CATPolyDart* iAlpha);
  inline CATPolyDart* GetAlpha1 ();
  inline const CATPolyDart* GetAlpha1 () const;

  // Homogenize i and j cells (except edge) and do sew by alpha1.
  static inline HRESULT Sew1 (CATPolyDart& i, CATPolyDart& j);
  static inline HRESULT Unsew1 (CATPolyDart& i, CATPolyDart& j);

  inline HRESULT SetAlpha2 (CATPolyDart* iAlpha);
  inline CATPolyDart* GetAlpha2 ();
  inline const CATPolyDart* GetAlpha2 () const;

  // Homogenize i and j cells (except face) and do sew by alpha2.
  static inline HRESULT Sew2 (CATPolyDart& i, CATPolyDart& j);
  static inline HRESULT Unsew2 (CATPolyDart& i, CATPolyDart& j);

  // Returns true if dart is 0-free.
  inline bool IsFree0 () const;

  // Returns true if dart is 1-free.
  inline bool IsFree1 () const;

  // Returns true if dart is 2-free.
  inline bool IsFree2 () const;

private:

  friend class CATPolyBody;
  void Clear ();

private:

  // Combinatorial map data.

#ifdef TAG_CATPOLYDART
  int _Tag;
#endif

  // Alpha[i] is an involution: Alpha[i] (Alpha[i] (d)) = d.
  // By default: Alpha[i] (d) = d.
  // Alpha[i] cannot be null.
  CATPolyDart* _Alpha[N+1];

  // Cells
  CATPolyCell* _Cell[N+1];  // Cells of dimension 0, 1, ..., N respectively.

  // Geometry
  CATIPolyPoint* _Point;
  CATIPolyCurve* _Curve;

};


//
// G-Map
//

template<size_t N>
template<size_t I>
inline HRESULT CATPolyDart<N>::SetAlpha (CATPolyDart* iAlpha)
{
#ifndef _AIX_SOURCE
  static_assert (I <= N);
#endif
  if (_Alpha[I] != this) return E_FAIL;
  _Alpha[I] = iAlpha;
  return S_OK;
}

template<size_t N>
template<size_t I>
inline CATPolyDart<N>* CATPolyDart<N>::GetAlpha ()
{
  if (I <= N)
    return _Alpha[I];
  else
    return this;
}

template<size_t N>
template<size_t I>
inline const CATPolyDart<N>* CATPolyDart<N>::GetAlpha () const
{
  if (I <= N)
    return _Alpha[I];
  else
    return this;
}

template<size_t N>
inline CATPolyDart<N>* CATPolyDart<N>::GetAlpha (size_t i)
{
  if (i <= N)
    return _Alpha[i];
  else
    return this;
}

template<size_t N>
inline const CATPolyDart<N>* CATPolyDart<N>::GetAlpha (size_t i) const
{
  if (i <= N)
    return _Alpha[i];
  else
    return this;
}

template<size_t N>
template<size_t I>
inline CATPolyCell* CATPolyDart<N>::GetCell () const
{
  if (I <= N)
    return _Cell[I];
  else
    return 0;
}

template<size_t N>
inline CATPolyCell* CATPolyDart<N>::GetCell (unsigned int i) const
{
  if (i <= N)
    return _Cell[i];
  else
    return 0;
}

template<size_t N>
template<size_t I>
inline CATPolyCell* CATPolyDart<N>::DetachCell ()
{
  if (I <= N)
  {
    CATPolyCell* cell = GetCell<I> ();
    _Cell[I] = 0;
    return cell;
  }
  return 0;
}

template<size_t N>
inline size_t CATPolyDart<N>::Dimension ()
{
  return N;
}

template<size_t N>
inline HRESULT CATPolyDart<N>::SetAlpha0 (CATPolyDart* iAlpha)
{
  return SetAlpha<0> (iAlpha);
}

template<size_t N>
inline CATPolyDart<N>* CATPolyDart<N>::GetAlpha0 ()
{
  return GetAlpha<0> ();
}

template<size_t N>
inline const CATPolyDart<N>* CATPolyDart<N>::GetAlpha0 () const
{
  return GetAlpha<0> ();
}

template<size_t N>
inline HRESULT CATPolyDart<N>::Sew0 (CATPolyDart& i, CATPolyDart& j)
{
  return Sew<0> (i, j);
}

template<size_t N>
inline HRESULT CATPolyDart<N>::Unsew0 (CATPolyDart& i, CATPolyDart& j)
{
  return Unsew<0> (i, j);
}

template<size_t N>
inline HRESULT CATPolyDart<N>::SetAlpha1 (CATPolyDart* iAlpha)
{
  return SetAlpha<1> (iAlpha);
}

template<size_t N>
inline CATPolyDart<N>* CATPolyDart<N>::GetAlpha1 ()
{
  return GetAlpha<1> ();
}

template<size_t N>
inline const CATPolyDart<N>* CATPolyDart<N>::GetAlpha1 () const
{
  return GetAlpha<1> ();
}

template<size_t N>
inline HRESULT CATPolyDart<N>::Sew1 (CATPolyDart& i, CATPolyDart& j)
{
  return Sew<1> (i, j);
}

template<size_t N>
inline HRESULT CATPolyDart<N>::Unsew1 (CATPolyDart& i, CATPolyDart& j)
{
  return Unsew<1> (i, j);
}

template<size_t N>
inline HRESULT CATPolyDart<N>::SetAlpha2 (CATPolyDart* iAlpha)
{
  return SetAlpha<2> (iAlpha);
}

template<size_t N>
inline CATPolyDart<N>* CATPolyDart<N>::GetAlpha2 ()
{
  return GetAlpha<2> ();
}

template<size_t N>
inline const CATPolyDart<N>* CATPolyDart<N>::GetAlpha2 () const
{
  return GetAlpha<2> ();
}

template<size_t N>
inline HRESULT CATPolyDart<N>::Sew2 (CATPolyDart& i, CATPolyDart& j)
{
  return Sew<2> (i, j);
}

template<size_t N>
inline HRESULT CATPolyDart<N>::Unsew2 (CATPolyDart& i, CATPolyDart& j)
{
  return Unsew<2> (i, j);
}

template<size_t N>
template<size_t I>
inline bool CATPolyDart<N>::IsFree () const
{
#ifndef _AIX_SOURCE
  static_assert (I <= N);
#endif
  return _Alpha[I] == this;
}

template<>
inline bool CATPolyDart<2>::IsAllFree () const
{
  return IsFree<0> () && IsFree<1> () && IsFree<2> ();
}

template<>
inline bool CATPolyDart<3>::IsAllFree () const
{
  return IsFree<0> () && IsFree<1> () && IsFree<2> () && IsFree<3> ();
}

template<size_t N>
inline bool CATPolyDart<N>::IsFree0 () const
{
  return IsFree<0> ();
}

template<size_t N>
inline bool CATPolyDart<N>::IsFree1 () const
{
  return IsFree<1> ();
}

template<size_t N>
inline bool CATPolyDart<N>::IsFree2 () const
{
  return IsFree<2> ();
}

template<size_t N>
inline HRESULT CATPolyDart<N>::SetVertex (CATPolyVertex& iVertex)
{
  return SetCell ((CATPolyCell&) iVertex);
}

template<size_t N>
inline CATPolyVertex* CATPolyDart<N>::GetVertex () const
{
  return (CATPolyVertex*) GetCell<0> ();
}

template<size_t N>
inline CATPolyVertex* CATPolyDart<N>::DetachVertex ()
{
  return (CATPolyVertex*) DetachCell<0> ();
}

template<size_t N>
inline HRESULT CATPolyDart<N>::SetEdge (CATPolyEdge& iEdge)
{
  return SetCell ((CATPolyCell&) iEdge);
}

template<size_t N>
inline CATPolyEdge* CATPolyDart<N>::GetEdge () const
{
  return (CATPolyEdge*) GetCell<1> ();
}

template<size_t N>
inline CATPolyEdge* CATPolyDart<N>::DetachEdge ()
{
  return (CATPolyEdge*) DetachCell<1> ();
}

template<size_t N>
inline HRESULT CATPolyDart<N>::SetFace (CATPolyFace& iFace)
{
  return SetCell ((CATPolyCell&) iFace);
}

template<size_t N>
inline CATPolyFace* CATPolyDart<N>::GetFace () const
{
  return (CATPolyFace*) GetCell<2> ();
}

template<size_t N>
inline CATPolyFace* CATPolyDart<N>::DetachFace ()
{
  return (CATPolyFace*) DetachCell<2> ();
}

template<size_t N>
inline HRESULT CATPolyDart<N>::SetVolume (CATPolyVolume& iVolume)
{
  return SetCell ((CATPolyCell&) iVolume);
}

template<size_t N>
inline CATPolyVolume* CATPolyDart<N>::GetVolume () const
{
  return (CATPolyVolume*) GetCell<3> ();
}

template<size_t N>
inline CATPolyVolume* CATPolyDart<N>::DetachVolume ()
{
  return (CATPolyVolume*) DetachCell<3> ();
}

template<size_t N>
inline HRESULT CATPolyDart<N>::SetPoint (CATIPolyPoint* iPoint)
{
  if (_Point) return _Point == iPoint ? S_OK : E_FAIL; // Detach first!
  _Point = iPoint;
  if (_Point) _Point->AddRef ();
  return S_OK;
}

template<size_t N>
inline CATIPolyPoint* CATPolyDart<N>::GetPoint ()
{
  return _Point;
}

template<size_t N>
inline const CATIPolyPoint* CATPolyDart<N>::GetPoint () const
{
  return _Point;
}

template<size_t N>
inline HRESULT CATPolyDart<N>::DetachPoint ()
{
  if (_Point) _Point->Release ();
  _Point = 0;
  return S_OK;
}

template<size_t N>
inline HRESULT CATPolyDart<N>::SetCurve (CATIPolyCurve& iCurve)
{
  if (_Curve) return _Curve == &iCurve ? S_OK : E_FAIL; // Detach first!
  _Curve = &iCurve;
  iCurve.AddRef ();
  return S_OK;
}

template<size_t N>
inline CATIPolyCurve* CATPolyDart<N>::GetCurve ()
{
  return _Curve;
}

template<size_t N>
inline const CATIPolyCurve* CATPolyDart<N>::GetCurve () const
{
  return _Curve;
}

template<size_t N>
inline HRESULT CATPolyDart<N>::DetachCurve ()
{
  if (_Curve) _Curve->Release ();
  _Curve = 0;
  return S_OK;
}

template<class DART>
inline void CATSwap (DART*& ioLHS, DART*& ioRHS)
{
  DART* d = ioLHS;
  ioLHS = ioRHS;
  ioRHS = d;
}

#ifndef _AIX_SOURCE
using CATPolyDart2 = CATPolyDart<2>;
using CATPolyDart3 = CATPolyDart<3>;
#else
typedef CATPolyDart<2> CATPolyDart2;
typedef CATPolyDart<3> CATPolyDart3;
#endif

bool operator< (const CATPolyDart<2>& di, const CATPolyDart<2>& dj);
bool operator< (const CATPolyDart<3>& di, const CATPolyDart<3>& dj);
