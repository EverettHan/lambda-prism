// COPYRIGHT DASSAULT SYSTEMES 2006, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBars.h
//
//===================================================================
// March 2006  Creation: NDO
//===================================================================
#ifndef CATPolyBars_H
#define CATPolyBars_H

#include "PolyMeshImpl.h"
#include "CATPolyRefCounted.h"
#include "CATBoolean.h"
#include "CATPolyBuckets_T.h"

#include "CATSetOfIntegerSets.h"

class CATPolyBarsObserver;

class CATIPolyMesh;
class CATPolyBarsMeshObserver;


/**
 * Container of bars.  A bar is represented by a pair of vertices.
 * Bars have an index.
 */
class ExportedByPolyMeshImpl CATPolyBars : public CATPolyRefCounted
{

public :

  CATPolyBars ();
  CATPolyBars (CATIPolyMesh& iMesh);

  ~CATPolyBars ();

public:

/** @name Bar management
    @{ */

  /**
   * Adds a bar and returns its index.
   * @param iVertex0
   *   The index of the start vertex.
   * @param iVertex1
   *   The index of the end vertex.
   * @param oIdxBar
   *   The index of the added bar.
   * @return
   *   S_OK if the bar is added successfully, E_FAIL otherwise.
   */
  HRESULT AddBar (const int iVertex0, const int iVertex1, int& oIdxBar);

  /**
   * Returns the vertices of a bar.
   * @param iIdxBar
   *   The index of the bar.
   *   <br><b>Legal values</b>: 1 to the number of bars, inclusive.
   * @param oVertex0
   *   The index of the first vertex of the bar.
   * @param oVertex1
   *   The index of the second vertex of the bar.
   * @return
   *   S_OK if the bar is returned successfully, E_FAIL otherwise.
   */
  HRESULT GetBar (const int oIdxBar, int& oVertex0, int& oVertex1) const;

  /**
   * Removes the bar.
   * @param idxBar
   *   The index of the bar to remove.
   * @return
   *   S_OK if the bar is removed and E_FAIL otherwise.
   */
  HRESULT RemoveBar (const int iIdxBar);

  /**
   * Updates the definition of a bar.
   */
  //HRESULT UpdateBar (const int iIdxBar, const int iVertex0, const int iVertex1);

  /**
   * Flips the orientation of a bar
   */
  HRESULT FlipBar(const int iIdxBar);

  /**
   * Returns the number of bars inserted in the container.
   */
  inline int GetNbBars (void) const;

  /**
   * Returns the number of bars referencing a vertex (valence of the vertex).
   */
  inline int GetNbBars (const int iVertex) const;

  /**
   * Finds if the a bar defined by two vertices is in the data structure.
   * Returns the index of the (first) bar if found and 0 otherwise.
   */
  int FindBar (const int iVertex0, const int iVertex1) const;

/** @} */


public:

/** @name Vertex services
    @{ */

  /**
   * Returns the number of vertices referenced by bars.
   */
  inline int GetNbVertices () const;

  /** 
   * Merges the two vertices by replacing v1 by v0.
   * If there is a bar between v0 and v1, this bar is collapsed (removed).
   */
  HRESULT MergeVertices (const int v0, const int v1);

public:

  /**
   * Returns the smallest index of a vertex that may be referred by a bar.
   */
  inline int GetMinVertexIndex() const;

  /**
   * Returns the largest index of a vertex that may be referred by a bar.
   */
  inline int GetMaxVertexIndex() const;

  /**
   * Returns the smallest index that may refer to a valid bar.
   */
  inline int GetMinBarIndex() const;

  /**
   * Returns the largest index that may refer to a valid bar.
   */
  inline int GetMaxBarIndex() const;

/** @} */


public:

/** @name Event Listener. 
    Event listener are used to update attributes (user-defined layers.)
    @{ */

  /**
   * Registers an observer (event listener) with the instance. 
   * A note about observers:  When several observers are registered, the last observer to be registered
   * is the first to observe an event.  Observers are called in the sequence: Last In, First to Observe.
   * @param iObserver
   *   The observer that is registered with the instance.
   * @return 
   * <ul>
   *   <li> <tt>S_OK</tt> if the observer is successfully registered.
   *   <li> <tt>E_FAIL</tt> otherwise.
   * </ul>
   */
  HRESULT RegisterObserver (CATPolyBarsObserver &iObserver);

  /** 
   * Unregisters an observer (event listener) with the instance. 
   */
  HRESULT UnregisterObserver (CATPolyBarsObserver &iObserver);

/** @} */


public:

  /**
   * @nodoc
   */
  inline CATBoolean IsBarDefined (const int iIdxBar) const;

private:

  class T_Bar
  {
  public:
    inline T_Bar ();
    inline T_Bar (const int v0, const int v1);

  public:
    inline void Recycle (const int v0, const int v1);
    void Absorb (T_Bar& iRHS);

  public:
    inline void Undefine (); // Undefine the bar.
    inline CATBoolean IsDefined () const;

  public:
    inline int FindVertex (const int v0) const;  // Return index of vertex in bar: 0, 1 (or -1).

  public:
    unsigned int _Vertices[2];
  };

  class Specialize_CATPolyBuckets_T (BarBuckets, T_Bar);

private:

  CATSetOfIntegerSets _VertexToBarSet;

  BarBuckets    _Bars;

  unsigned int _NbBars;

  // Recycler of bars.
  int _FirstUndefinedBar;

  CATPolyBarsObserver* _Observer;  // Pointer to first observer.

private:

  void PushUndefinedBar (unsigned int b);
  unsigned int PopUndefinedBar ();

private:

  friend class CATPolyBarsVertexBarIterator;

private:

  HRESULT FinalAddBar (const int v0, const int v1, int& b);
  HRESULT FinalRemoveBar (const int b);

  HRESULT FinalUpdateBar (const int b, const int v0, const int v1);

// ==========================================================================
// DEPRECATED SERVICES, kept for compatibility. DO NOT USE ANYMORE
// ==========================================================================

public:

  CATBoolean Insert (const int iVertex0, const int iVertex1);
  CATBoolean Remove (const int iVertex0, const int iVertex1);
  CATBoolean Locate (const int iVertex0, const int iVertex1) const;

private :

  CATIPolyMesh* _PolyMesh;
  CATPolyBarsMeshObserver* _MeshObserver;

};


//
// Bar
//

inline CATPolyBars::T_Bar::T_Bar ()
{
}

inline CATPolyBars::T_Bar::T_Bar (int v0, int v1)
{
  Recycle (v0, v1);
}

inline void CATPolyBars::T_Bar::Recycle (int v0, int v1)
{
  _Vertices[0] = v0;
  _Vertices[1] = v1;
}

inline int CATPolyBars::T_Bar::FindVertex (int v0) const
{
  if      (v0 == _Vertices[0]) return 0;
  else if (v0 == _Vertices[1]) return 1;
  return -1;
}

inline void CATPolyBars::T_Bar::Undefine ()
{
  _Vertices[1] = 0;
}

inline CATBoolean CATPolyBars::T_Bar::IsDefined () const
{
  return _Vertices[1] != 0;
}

//
// CATPolyBars inline methods.
//

inline int CATPolyBars::GetNbBars (void) const
{
  return _NbBars;
}

inline int CATPolyBars::GetNbBars (const int iVertex) const
{
  CATIntegerSets::HandleOfSet handle = _VertexToBarSet.Find (iVertex);
  return _VertexToBarSet.GetNbElements (handle);
}

inline int CATPolyBars::GetNbVertices () const
{
  return _VertexToBarSet.GetNbSets ();
}

inline int CATPolyBars::GetMinVertexIndex() const
{
  return 1;
}

inline int CATPolyBars::GetMaxVertexIndex() const
{
  unsigned int maxIndex = 0;
  for (CATSetOfIntegerSets::SetIterator it (_VertexToBarSet); !it.End (); ++it)
  {
    if (*it > maxIndex)
      maxIndex = *it;
  }
  return (int) maxIndex;
}

inline int CATPolyBars::GetMinBarIndex() const
{
  return 1;
}

inline int CATPolyBars::GetMaxBarIndex() const
{
  return _Bars.Size ();
}

inline CATBoolean CATPolyBars::IsBarDefined (const int iIdxBar) const
{
  return (0 < iIdxBar && (unsigned int) iIdxBar <= _Bars.Size ()) ? _Bars[iIdxBar].IsDefined () : FALSE;
}

#endif
