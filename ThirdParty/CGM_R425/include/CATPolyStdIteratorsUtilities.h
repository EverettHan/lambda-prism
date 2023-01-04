#ifndef CATPolyStdIteratorsUtilities_H
#define CATPolyStdIteratorsUtilities_H

#include "CATIACGMLevel.h"
#include "CATErrorDef.h"
#include "CATCGMSharedPtr.h"
#include "CATMathPoint.h"
#include "PolyMeshTools.h"

#include "CATIPolySurface.h"
#include "CATIPolyMesh.h"

#include "CATPolyBodyFaceIterator.h"
#include "CATPolyBodyVertexIterator.h"
#include "CATPolyBodyEdgeIterator.h"
#include "CATIPolyIndexIterator.h"
#include "CATIPolyMeshTriangleIterator.h"
#include "CATIPolyVertexPositionConstLayer.h"
#include "CATIPolySurfaceVertexFacetNeighborhood.h"
#include "CATPolySurfaceVertexVertexFacetIterator.h"
#if defined(CATIAR424)
#include "CATPolySurfaceBorderLoopsExtractor.h"
#endif

#include <utility>

class CATPolyBody;
class CATIPolySurface;
class CATIPolyMesh;

/*
 * STL like iterator class encapsulating an PolyIterator classes
 * Iterator template parameter can be CATIPolySurfaceVertexIterator, CATPolyBodyFaceIterator, ...
 */

template<class Iterator>
class CATNestingPolyIterator
{
public:
  explicit CATNestingPolyIterator(Iterator *ipIterator)
    : _pIterator(ipIterator)
  {
    _pIterator->Begin();
  }

  CATNestingPolyIterator& operator++()
  {
    ++*_pIterator;
    return *this;
  }

  /*
   * Dereferences the iterator
   * @return result of operator* of underlying Iterator class
   */
  decltype(auto) operator*()
  {
    return **_pIterator;
  }

  class EndIterator {};

  bool operator==(EndIterator const&) const
  {
    return !_pIterator || _pIterator->End();
  }

  bool operator!=(EndIterator const&) const
  {
    return _pIterator && !_pIterator->End();
  }

  Iterator *_pIterator = nullptr;
};


template<class Iterator>
class CATNestingPolyBarIterator
{
public:
  explicit CATNestingPolyBarIterator(Iterator *ipIterator,int v0, int v1)
    : _pIterator(ipIterator)
  {
    _pIterator->Begin(v0,v1);
  }

  CATNestingPolyBarIterator& operator++()
  {
    ++*_pIterator;
    return *this;
  }

  /*
   * Dereferences the iterator
   * @return result of operator* of underlying Iterator class
   */
  decltype(auto) operator*()
  {
    return **_pIterator;
  }

  class EndIterator {};

  bool operator==(EndIterator const&) const
  {
    return !_pIterator || _pIterator->End();
  }

  bool operator!=(EndIterator const&) const
  {
    return _pIterator && !_pIterator->End();
  }

  Iterator *_pIterator = nullptr;
};

/*
 * C++ range class implementing begin() and end() method for PolyBody face range
 */

class CATPolyBodyEntityEndIterator{};

template<class Iterator>
class CATPolyBodyEntityRange
{
public:
  CATPolyBodyEntityRange(CATPolyBody const &iPolyBody)
    : _polyBody(iPolyBody)
  {}

  Iterator begin()
  {
    return Iterator(_polyBody);
  }

  CATPolyBodyEntityEndIterator end()
  {
    return CATPolyBodyEntityEndIterator();
  }

private:
  CATPolyBody const &_polyBody;
};

template<class Iterator>
inline bool operator==(Iterator const &iIterator, CATPolyBodyEntityEndIterator const&)
{
  return iIterator.End();
}

template<class Iterator>
inline bool operator!=(Iterator const &iIterator, CATPolyBodyEntityEndIterator const&)
{
  return !iIterator.End();
}

/*
 * C++ range class implementing begin() and end() method for vertex range over a PolySurface
 */

class CATIPolyObjectVertexRange
{
public:
  ExportedByPolyMeshTools CATIPolyObjectVertexRange(CATIPolySurface const& iSurface, HRESULT& oHR);
  ExportedByPolyMeshTools CATIPolyObjectVertexRange(CATIPolyCurve const& iCurve, HRESULT& oHR);

  class Iterator : private CATNestingPolyIterator<CATIPolyIndexIterator>
  {
  public:
    using CATNestingPolyIterator<CATIPolyIndexIterator>::CATNestingPolyIterator;
    using CATNestingPolyIterator<CATIPolyIndexIterator>::operator++;
    using CATNestingPolyIterator<CATIPolyIndexIterator>::operator*;
    using CATNestingPolyIterator<CATIPolyIndexIterator>::operator==;
    using CATNestingPolyIterator<CATIPolyIndexIterator>::operator!=;
    using CATNestingPolyIterator<CATIPolyIndexIterator>::EndIterator;
  };

  Iterator begin()
  {
    return Iterator(_pIterator.get());
  }

  Iterator::EndIterator end()
  {
    return Iterator::EndIterator();
  }

  HRESULT hr;

private:
  CATCGMSharedPtr<CATIPolyIndexIterator> _pIterator;
};

/*
 * C++ range class implementing begin() and end() method for vertex range with position over a PolySurface or a PolyCurve
 */

class CATIPolyObjectVertexWithPositionRange
{
public:

  ExportedByPolyMeshTools CATIPolyObjectVertexWithPositionRange(CATIPolySurface const& iSurface, HRESULT& oHR);
  ExportedByPolyMeshTools CATIPolyObjectVertexWithPositionRange(CATIPolyCurve const& iCurve, HRESULT& oHR);

  class Result
  {
  public:
    HRESULT hr;
    int idx;
    CATMathPoint point;
  };

  class Iterator : private CATNestingPolyIterator<CATIPolyIndexIterator>
  {
  public:
    Iterator(CATIPolyIndexIterator* ipIterator, CATIPolyVertexPositionConstLayer* ipPositionLayer)
      : CATNestingPolyIterator<CATIPolyIndexIterator>(ipIterator)
      , _pPositionLayer(ipPositionLayer)
    {}

    using CATNestingPolyIterator<CATIPolyIndexIterator>::CATNestingPolyIterator;
    using CATNestingPolyIterator<CATIPolyIndexIterator>::operator++;
    using CATNestingPolyIterator<CATIPolyIndexIterator>::operator==;
    using CATNestingPolyIterator<CATIPolyIndexIterator>::operator!=;
    using CATNestingPolyIterator<CATIPolyIndexIterator>::EndIterator;

    ExportedByPolyMeshTools Result operator*();

  private:
    CATIPolyVertexPositionConstLayer*_pPositionLayer = nullptr;
  };

  Iterator begin()
  {
    return Iterator(_pIterator.get(), _pPositionLayer.get());
  }

  Iterator::EndIterator end()
  {
    return Iterator::EndIterator();
  }
  
  HRESULT hr;

private:
  CATCGMSharedPtr<CATIPolyIndexIterator> _pIterator;
  CATCGMSharedPtr<CATIPolyVertexPositionConstLayer> _pPositionLayer;
};

/*
 * C++ range class implementing begin() and end() method for triangle range over a PolyMesh
 */

class CATIPolyMeshTriangleRange
{
public:
  CATIPolyMeshTriangleRange(CATIPolyMesh const &iMesh, HRESULT &oHR)
  {
    oHR = iMesh.GetTriangleIterator(_pIterator.ref());
  }

  class Iterator : private CATNestingPolyIterator<CATIPolyMeshTriangleIterator>
  {
  public:
    using CATNestingPolyIterator<CATIPolyMeshTriangleIterator>::CATNestingPolyIterator;
    using CATNestingPolyIterator<CATIPolyMeshTriangleIterator>::operator++;
    using CATNestingPolyIterator<CATIPolyMeshTriangleIterator>::operator*;
    using CATNestingPolyIterator<CATIPolyMeshTriangleIterator>::operator==;
    using CATNestingPolyIterator<CATIPolyMeshTriangleIterator>::operator!=;
    using CATNestingPolyIterator<CATIPolyMeshTriangleIterator>::EndIterator;
  };

  Iterator begin()
  {
    return Iterator(_pIterator.get());
  }

  Iterator::EndIterator end()
  {
    return Iterator::EndIterator();
  }
  
  HRESULT hr;

private:
  CATCGMSharedPtr<CATIPolyMeshTriangleIterator> _pIterator;
};


/*
 * C++ range class implementing begin() and end() method for triangle range over a PolyMesh
 */
#if defined(CATIAR424)
class CATIPolyLoopVertexIteratorRange
{
public:
  CATIPolyLoopVertexIteratorRange(CATPolySurfaceBorderLoopsExtractor::LoopVertexIterator  &iLoop, HRESULT &oHR)
  :_pIterator(iLoop)
  {
    oHR = S_OK;//iMesh.GetTriangleIterator(_pIterator.ref());
  }

  class Iterator : private CATNestingPolyIterator<CATPolySurfaceBorderLoopsExtractor::LoopVertexIterator >
  {
  public:
    using CATNestingPolyIterator<CATPolySurfaceBorderLoopsExtractor::LoopVertexIterator>::CATNestingPolyIterator;
    using CATNestingPolyIterator<CATPolySurfaceBorderLoopsExtractor::LoopVertexIterator>::operator++;
    using CATNestingPolyIterator<CATPolySurfaceBorderLoopsExtractor::LoopVertexIterator>::operator*;
    using CATNestingPolyIterator<CATPolySurfaceBorderLoopsExtractor::LoopVertexIterator>::operator==;
    using CATNestingPolyIterator<CATPolySurfaceBorderLoopsExtractor::LoopVertexIterator>::operator!=;
    using CATNestingPolyIterator<CATPolySurfaceBorderLoopsExtractor::LoopVertexIterator>::EndIterator;
  };

  Iterator begin()
  {
    return Iterator(&_pIterator);
  }

  Iterator::EndIterator end()
  {
    return Iterator::EndIterator();
  }
  
  HRESULT hr;

private:
  CATPolySurfaceBorderLoopsExtractor::LoopVertexIterator & _pIterator;
};

/*
*
 * C++ range class implementing begin() and end() method for triangle range over a PolyMesh
 */

class CATIPolyLoopsIteratorRange
{
public:
  CATIPolyLoopsIteratorRange(CATIPolyMesh const &iMesh, HRESULT &oHR)     
  {
    _LoopExtractor = new CATPolySurfaceBorderLoopsExtractor(iMesh);
    oHR = _LoopExtractor->Run();
    _pIterator = new CATPolySurfaceBorderLoopsExtractor::LoopIterator(*_LoopExtractor);
    _pSubIterator = new CATPolySurfaceBorderLoopsExtractor::LoopVertexIterator(*_pIterator);
  }

  ~CATIPolyLoopsIteratorRange()
  {
    delete _pSubIterator;
    delete _pIterator;
    delete _LoopExtractor;    
  }

  class Iterator
  {
  public:
    Iterator(CATPolySurfaceBorderLoopsExtractor::LoopIterator *iIterator, CATPolySurfaceBorderLoopsExtractor::LoopVertexIterator *iSubIterator) : _pIterator(iIterator),
                                                                                                                                                  _pSubIterator(iSubIterator)
    {
    }
    Iterator &operator++()
    {
      ++*_pIterator;
      return *this;
    }

    /*
   * Dereferences the iterator
   * @return result of operator* of underlying Iterator class
   */
    CATPolySurfaceBorderLoopsExtractor::LoopVertexIterator &operator*()
    {
      return *_pSubIterator;
    }

    class EndIterator
    {
    };

    bool operator==(EndIterator const &) const
    {
      return !_pIterator || _pIterator->End();
    }

    bool operator!=(EndIterator const &) const
    {
      return _pIterator && !_pIterator->End();
    }

    CATPolySurfaceBorderLoopsExtractor::LoopIterator *_pIterator = nullptr;
    CATPolySurfaceBorderLoopsExtractor::LoopVertexIterator *_pSubIterator = nullptr;
  };

  Iterator begin()
  {
    return Iterator(_pIterator,_pSubIterator);
  }

  Iterator::EndIterator end()
  {
    return Iterator::EndIterator();
  }

  HRESULT hr;

private:
  CATPolySurfaceBorderLoopsExtractor *_LoopExtractor = nullptr;
  CATPolySurfaceBorderLoopsExtractor::LoopIterator *_pIterator = nullptr;
  CATPolySurfaceBorderLoopsExtractor::LoopVertexIterator *_pSubIterator = nullptr;
};
#endif

/*
 * C++ range class implementing begin() and end() method for triangle range over a PolyMesh
 */

class CATIPolyMeshTriangleFromBarRange
{
public:
  CATIPolyMeshTriangleFromBarRange(CATIPolyMesh const &iMesh,int v0, int v1, HRESULT &oHR)
  {
    oHR = iMesh.GetVertexFacetNeighborhood(_Neighborhood.ref());
    _barV0= v0;
    _barV1= v1;
    _pIterator = new CATPolySurfaceVertexVertexFacetIterator(iMesh, *_Neighborhood) ;    
  }

  ~CATIPolyMeshTriangleFromBarRange()
  {
    delete _pIterator;
    _pIterator = nullptr;
  }



  class Iterator : private CATNestingPolyBarIterator<CATPolySurfaceVertexVertexFacetIterator>
  {
  public:
    using CATNestingPolyBarIterator<CATPolySurfaceVertexVertexFacetIterator>::CATNestingPolyBarIterator;
    using CATNestingPolyBarIterator<CATPolySurfaceVertexVertexFacetIterator>::operator++;
    using CATNestingPolyBarIterator<CATPolySurfaceVertexVertexFacetIterator>::operator*;
    using CATNestingPolyBarIterator<CATPolySurfaceVertexVertexFacetIterator>::operator==;
    using CATNestingPolyBarIterator<CATPolySurfaceVertexVertexFacetIterator>::operator!=;
    using CATNestingPolyBarIterator<CATPolySurfaceVertexVertexFacetIterator>::EndIterator;
  };

  Iterator begin()
  {
    return Iterator(_pIterator,_barV0,_barV1);
  }

  Iterator::EndIterator end()
  {
    return Iterator::EndIterator();
  }
  
  HRESULT hr;

private:
  CATCGMSharedPtr<CATIPolySurfaceVertexFacetNeighborhood>  _Neighborhood = nullptr;
  CATPolySurfaceVertexVertexFacetIterator *_pIterator =nullptr;
  int _barV0 = 0;
  int _barV1 = 0;
};


/*
 * C++ range class implementing begin() and end() method for triangle with vertices range over a PolyMesh
 */

class CATIPolyMeshTriangleWithVerticesRange
{
public:
  CATIPolyMeshTriangleWithVerticesRange(CATIPolyMesh const &iMesh, HRESULT &oHR)
    : _mesh(iMesh)
  {
    oHR = _mesh.GetTriangleIterator(_pIterator.ref());
  }

  class Result
  {
  public:
    HRESULT hr;
    int idx;
    int vertices[3];
  };

  class Iterator : private CATNestingPolyIterator<CATIPolyMeshTriangleIterator>
  {
  public:
    Iterator(CATIPolyMeshTriangleIterator *ipIterator, CATIPolyMesh const& iMesh)
      : CATNestingPolyIterator<CATIPolyMeshTriangleIterator>(ipIterator)
      , _mesh(iMesh)
    {}

    using CATNestingPolyIterator<CATIPolyMeshTriangleIterator>::CATNestingPolyIterator;
    using CATNestingPolyIterator<CATIPolyMeshTriangleIterator>::operator++;
    using CATNestingPolyIterator<CATIPolyMeshTriangleIterator>::operator==;
    using CATNestingPolyIterator<CATIPolyMeshTriangleIterator>::operator!=;
    using CATNestingPolyIterator<CATIPolyMeshTriangleIterator>::EndIterator;

    ExportedByPolyMeshTools Result operator*();

  private:
    CATIPolyMesh const& _mesh;
  };

  Iterator begin()
  {
    return Iterator(_pIterator.get(), _mesh);
  }

  Iterator::EndIterator end()
  {
    return Iterator::EndIterator();
  }
  
  HRESULT hr;

private:
  CATCGMSharedPtr<CATIPolyMeshTriangleIterator> _pIterator;
  CATIPolyMesh const &_mesh;
};

/*
 * C++ range class implementing begin() and end() method for triangle with vertices idx and coordinates range over a PolyMesh
 */

class CATIPolyMeshTriangleWithVertexCoordsRange
{
public:
  ExportedByPolyMeshTools CATIPolyMeshTriangleWithVertexCoordsRange(CATIPolyMesh const &iMesh, HRESULT &oHR);

  class Result
  {
  public:
    HRESULT hr;
    int idx;
    int vertices[3];
    CATMathPoint coords[3];
  };

  class Iterator : private CATNestingPolyIterator<CATIPolyMeshTriangleIterator>
  {
  public:
    Iterator(CATIPolyMeshTriangleIterator *ipIterator, CATIPolyMesh const& iMesh, CATIPolyVertexPositionConstLayer*ipPositionLayer)
      : CATNestingPolyIterator<CATIPolyMeshTriangleIterator>(ipIterator)
      , _mesh(iMesh)
      , _pPositionLayer(ipPositionLayer)
    {}

    using CATNestingPolyIterator<CATIPolyMeshTriangleIterator>::CATNestingPolyIterator;
    using CATNestingPolyIterator<CATIPolyMeshTriangleIterator>::operator++;
    using CATNestingPolyIterator<CATIPolyMeshTriangleIterator>::operator==;
    using CATNestingPolyIterator<CATIPolyMeshTriangleIterator>::operator!=;
    using CATNestingPolyIterator<CATIPolyMeshTriangleIterator>::EndIterator;

    ExportedByPolyMeshTools Result operator*();

  private:
    CATIPolyMesh const& _mesh;
    CATIPolyVertexPositionConstLayer*_pPositionLayer = nullptr;
  };

  Iterator begin()
  {
    return Iterator(_pIterator.get(), _mesh, _pPositionLayer.get());
  }

  Iterator::EndIterator end()
  {
    return Iterator::EndIterator();
  }   

private:
  CATCGMSharedPtr<CATIPolyMeshTriangleIterator> _pIterator;
  CATIPolyMesh const &_mesh;
  CATCGMSharedPtr<CATIPolyVertexPositionConstLayer> _pPositionLayer;
};

class CATPolyListOfIntIterator
{
public:
  CATPolyListOfIntIterator(CATListOfInt const &iList, int iIndex)
    : _list(iList)
    , _index(iIndex)
  {}

  CATPolyListOfIntIterator& operator++()
  {
    ++_index;
    return *this;
  }

  bool operator==(CATPolyListOfIntIterator const& iIterator) const
  {
    return _index == iIterator._index;
  }

  bool operator!=(CATPolyListOfIntIterator const& iIterator) const
  {
    return _index != iIterator._index;
  }

  int operator*()
  {
    return _list[_index];
  }

private:
  CATListOfInt const &_list;
  int _index;
};

template<class ListOfInt>
class CATPolyListOfIntRange
{
public:
  CATPolyListOfIntRange(ListOfInt ioBuffer) : _elements(ioBuffer) {}
  CATPolyListOfIntRange() = default;
  ~CATPolyListOfIntRange() = default;
  CATPolyListOfIntRange(CATPolyListOfIntRange const&) = default;
  CATPolyListOfIntRange& operator=(CATPolyListOfIntRange const&) = default;
  CATPolyListOfIntRange(CATPolyListOfIntRange &&) = default;
  CATPolyListOfIntRange& operator=(CATPolyListOfIntRange &&) = default;

  CATPolyListOfIntIterator begin()
  {
    return CATPolyListOfIntIterator(_elements, 1);
  }

  CATPolyListOfIntIterator end()
  {
    return CATPolyListOfIntIterator(_elements, _elements.Size() + 1);
  }

protected:
  ListOfInt _elements;
};

template<class ListOfInt>
class CATIPolyMeshFacetNeighborsOfVertexRange : private CATPolyListOfIntRange<ListOfInt>
{
private:
  using Base = CATPolyListOfIntRange<ListOfInt>;
  using Base::_elements;

public:
  CATIPolyMeshFacetNeighborsOfVertexRange(CATIPolySurfaceVertexFacetNeighborhood const &iNeigborhood, int iVertex, HRESULT &ioHr)
  {
    ioHr = iNeigborhood.GetFacetNeighborsOfVertex(iVertex, _elements);
  }

  CATIPolyMeshFacetNeighborsOfVertexRange(CATIPolySurfaceVertexFacetNeighborhood const& iNeigborhood, int iVertex, ListOfInt ioBuffer, HRESULT& ioHr)
    : Base(ioBuffer)
  {
    ioHr = iNeigborhood.GetFacetNeighborsOfVertex(iVertex, _elements);
  }

  using Base::begin;
  using Base::end;
};

template<class ListOfInt>
class CATIPolyMeshFacetNeighborsOfFacetRange : private CATPolyListOfIntRange<ListOfInt>
{
private:
  using Base = CATPolyListOfIntRange<ListOfInt>;
  using Base::_elements;

public:
  CATIPolyMeshFacetNeighborsOfFacetRange(CATIPolySurfaceVertexFacetNeighborhood const &iNeigborhood, int iFacet, HRESULT &ioHr)
  {
    ioHr = iNeigborhood.GetFacetNeighborsOfFacet(iFacet, _elements);
  }

  CATIPolyMeshFacetNeighborsOfFacetRange(CATIPolySurfaceVertexFacetNeighborhood const& iNeigborhood, int iFacet, ListOfInt ioBuffer, HRESULT& ioHr)
    : Base(ioBuffer)
  {
    ioHr = iNeigborhood.GetFacetNeighborsOfFacet(iFacet, _elements);
  }

  using Base::begin;
  using Base::end;
};

template<class ListOfInt>
class CATIPolyMeshVertexNeighborsOfVertexRange : private CATPolyListOfIntRange<ListOfInt>
{
private:
  using Base = CATPolyListOfIntRange<ListOfInt>;
  using Base::_elements;

public:
  CATIPolyMeshVertexNeighborsOfVertexRange(CATIPolySurfaceVertexFacetNeighborhood const &iNeigborhood, int iVertex, HRESULT &ioHr)
  {
    ioHr = iNeigborhood.GetVertexNeighborsOfVertex(iVertex, _elements);
  }

  CATIPolyMeshVertexNeighborsOfVertexRange(CATIPolySurfaceVertexFacetNeighborhood const& iNeigborhood, int iVertex, ListOfInt ioBuffer, HRESULT& ioHr)
    : Base(ioBuffer)
  {
    ioHr = iNeigborhood.GetVertexNeighborsOfVertex(iVertex, _elements);
  }

  using Base::begin;
  using Base::end;
};

/*
 * C++ range class implementing begin() and end() method encapsulating another range whose construction may failed with HRESULT
 */

template<class Range>
class CATPolyhedralRangeWithHR
{
public:
  /* 
   * Constructs encapsulated Range object by forwarding arguments and stores constructor HRESULT
   */
  template<class... Args>
  CATPolyhedralRangeWithHR(Args&& ...iArgs)
    : range(std::forward<Args>(iArgs)..., hr)
  {}

  auto begin()
  {
    return range.begin();
  }

  auto end()
  {
    return range.end();
  }

  HRESULT hr;
  Range range;
};

#endif
