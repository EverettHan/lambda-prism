// COPYRIGHT DASSAULT SYSTEMES 2018, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceVertexLayerImpl.h
//
//===================================================================
// October 2018 Creation: NDO
//===================================================================
#ifndef CATPolySurfaceVertexLayerImpl_H
#define CATPolySurfaceVertexLayerImpl_H

#include "CATPolyBuckets.h"

class CATIPolySurface;
class CATIPolySurfaceObserver;


template <typename TYPE>
class CATPolySurfaceVertexLayerImpl
{

public:

  /**
   * Sets the vertex data.
   */
  HRESULT Set (int v, const TYPE d);

  /**
   * Gets the vertex data.
   */
  HRESULT Get (int v, TYPE& d) const;

public:

  /**
   * Constructs an instance of CATIPolySurfaceObserver.
   * It does not register the observer with the CATIPolySurface.
   */
  CATIPolySurfaceObserver* NewObserver (const CATIPolySurface& S);

//private:

  //int PushBack ();

  //void Resize (unsigned int n);

private:

  CATPolyBuckets<TYPE> _Data;

};


//
// Implementation
//

#include "CATPolyBucketsImpl.h"
#include "CATIPolyMeshObserver.h"
#include "CATIPolySurfaceVertexIterator.h"


// Mesh Observer.
template <typename TYPE>
class CATPolySurfaceVertexLayerImplMeshObserver : public CATIPolyMeshObserver
{
public:

  CATPolySurfaceVertexLayerImplMeshObserver (const CATIPolySurface& S, CATPolyBuckets<TYPE>& data) :
    _PolySurface (S), _Data (data) {}

public:

  HRESULT ReactToAddVertex (int v)
  {
    if (v > _Data.Size ())
    {
      _Data.PushBack (TYPE ());
      while (v > _Data.Size ())
        _Data.PushBack (TYPE ());
    }
    else if (v > 0)
      _Data[v] = TYPE ();
    return S_OK;
  }

  HRESULT ReactToCompact (const CATMapOfIntToInt& iVertexMap, const CATMapOfIntToInt& iTriangleMap)
  {
    unsigned int nbVertices = _PolySurface.GetNbVertices ();
    HRESULT hr = (iVertexMap.Size () == nbVertices) ? S_OK : E_FAIL;
    if (nbVertices > 0)
    {
      TYPE* a = new TYPE [nbVertices + 1];  // Temporary compact buffer.
      for (CATMapOfIntToInt::Iterator it (iVertexMap); !it.End () && SUCCEEDED (hr); ++it)
      {
        int vo = it.GetKey ();
        int vn = it.GetData ();
        if (0 < vn && vn <= nbVertices)
          a[vn] = _Data[vo];
        else
          hr = E_FAIL; // Should not be.
      }
      unsigned int k;
      for (k = 1; k <= nbVertices; ++k)
      {
        _Data[k] = a[k];
      }
      delete [] a;
      _Data.Resize (nbVertices);
    }
    return hr;
  }

private:

  const CATIPolySurface& _PolySurface;
  CATPolyBuckets<TYPE>& _Data;

};


template<typename TYPE>
HRESULT CATPolySurfaceVertexLayerImpl<TYPE>::Set (int v, const TYPE d)
{
  _Data[v] = d;
  return S_OK;
}

template<typename TYPE>
HRESULT CATPolySurfaceVertexLayerImpl<TYPE>::Get (int v, TYPE& d) const
{
  d = _Data[v];
  return S_OK;
}

#if 0
template<typename TYPE>
int CATPolySurfaceVertexLayerImpl<TYPE>::PushBack ()
{
  return _Data.PushBack (TYPE ());
}
#endif

#if 0
template<typename TYPE>
void CATPolySurfaceVertexLayerImpl<TYPE>::Resize (unsigned int n)
{
  _Data.Resize (n);
}
#endif

template<typename TYPE>
CATIPolySurfaceObserver* CATPolySurfaceVertexLayerImpl<TYPE>::NewObserver (const CATIPolySurface& S)
{
  return new CATPolySurfaceVertexLayerImplMeshObserver<TYPE> (S, _Data);
}

#endif // !CATPolySurfaceVertexLayerImpl_H
