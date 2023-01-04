//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATPolyGraph
//
// Integer-based graph. Decorations on edge and vertices must be handled
// through external property maps.
//
//=============================================================================
// 2008-01-29   BPG: New
//=============================================================================
#ifndef CATPolyGraph_H
#define CATPolyGraph_H

#include "CATErrorDef.h"
#include "CATPolyBuckets_T.h"
#include "CATListOfInt.h"

#include "PolyMathContainers.h"
class ExportedByPolyMathContainers CATPolyGraph
{
public:
  CATPolyGraph();

public:
  /**
   * Add a graph vertex, and return its index.
   * @param oVertex
   *   The index of the added vertex.
   * @return
   *   S_OK if the edge was added successfully.
   */
  HRESULT AddVertex(int &oVertex);

  /**
   * Remove a graph vertex, killing its edges.
   * @param iVertex
   *   The index of the vertex to be removed.
   * @return
   *   S_OK if the edge was added successfully.
   */
  HRESULT RemoveVertex(const int iVertex);

  /**
   * @return the number of vertices in the graph.
   */
  inline int GetNbVertices() const;

public:
  /**
   * @return the number of edges linked to iVertex.
   */
  inline int GetVertexExternalDegre(const int iVertex) const;

  /**
   * Get the set of edges linked to iVertex.
   *
   * @return S_OK upon success, E_FAIL otherwise.
   */
  HRESULT GetVertexEdgeNeighborhood(const int iVertex, CATListOfInt &oEdgeNeighborhood) const;

  /**
   * Get the set of vertices linked to iVertex through an edge.
   *
   * @return S_OK upon success, E_FAIL otherwise.
   */
  HRESULT GetVertexVertexNeighborhood(const int iVertex, CATListOfInt &oVertexNeighborhood) const;

public:
  /**
   * Add a graph edge between two (existing) vertices and return its index.
   * @param iVertex0
   *   The index of the start vertex.
   * @param iVertex1
   *   The index of the end vertex.
   * @param oEdge
   *   The index of the added edge.
   * @return
   *   S_OK if the edge was added successfully, E_FAIL otherwise.
   */
  HRESULT AddEdge(const int iVertex0, const int iVertex1, int &oEdge);

  /**
   * Return the vertices of an edge.
   * @param iEdge
   *   The index of the edge.
   *   <br><b>Legal values</b>: 1 to the number of edges, inclusive.
   * @param oVertex0
   *   The index of the first vertex of the edge.
   * @param oVertex1
   *   The index of the second vertex of the edge.
   * @return
   *   S_OK if the edge is returned successfully, E_FAIL otherwise.
   */
  HRESULT GetEdge(const int oEdge, int& oVertex0, int& oVertex1) const;

  /**
   * Remove an edge.
   * @param iEdge
   *   The index of the edge to remove.
   * @return
   *   S_OK if the edge is removed and E_FAIL otherwise.
   */
  HRESULT RemoveEdge(const int iEdge);

  /**
   * @return
   *   Return the number of edges in the graph.
   */
  inline int GetNbEdges() const;

public:
  /**
   * Find an edge defined by the specified two vertices.
   * @return
   *   Return the index of the (first) edge if found, 0 otherwise.
   */
  int FindEdge(const int iVertex0, const int iVertex1) const;

private:
  class Vertex
  {
  public:
    inline Vertex();
    ~Vertex();

  public:
    inline void Recycle();

    inline CATBoolean IsDefined() const;

  public:
    inline unsigned int GetNbEdges() const;
    inline unsigned int GetEdge(unsigned int n) const;

  public:
    HRESULT Insert(const unsigned int iIdxEdge);
    CATBoolean Remove(const unsigned int iIdxEdge);

  public:
    unsigned int _Defined: 1;
    unsigned int _NbEdges: 15;
    unsigned int _EdgeListSize: 15;
    union
    {
      unsigned int _E;
      unsigned int *_List;
    } _Edge;
  };

  class Specialize_CATPolyBuckets_T(VertexBuckets, Vertex);

private:
  class Edge
  {
  public:
    inline Edge();
    inline Edge(const int v0, const int v1);

  public:
    inline void Recycle(const int v0, const int v1);

  public:
    inline void Undefine(); // Undefine the edge.
    inline CATBoolean IsDefined() const;

  public:
    inline int FindVertex(const int v0) const; // Return index of vertex in edge: 0, 1 (or -1).

  public:
    unsigned int _Vertices[2]; // Edge is not defined if (_Vertices[1] == 0)
  };

  class Specialize_CATPolyBuckets_T(EdgeBuckets, Edge);

private:
  void UndefineAndPushVertex(Vertex &V, unsigned int v);
  unsigned int PopUndefinedVertex();

private:
  void UndefineAndPushEdge(Edge &E, unsigned int e);
  unsigned int PopUndefinedEdge();

private:
  VertexBuckets _Vertices;
  int _NbVertices;
  unsigned int _FirstUndefinedVertex;

private:
  EdgeBuckets _Edges;
  int _NbEdges;
  unsigned int _FirstUndefinedEdge;
};

// ----------------------------------------------------------------------------
// Inline methods implementation

// Vertex

inline
CATPolyGraph::Vertex::Vertex()
{
  _Defined = 0;

  _NbEdges = 0;

  _EdgeListSize = 0;
  _Edge._List = 0; // (Tricky)
}

inline void
CATPolyGraph::Vertex::Recycle()
{
  _Defined = 1;

  _NbEdges = 0; // (keep allocated edge list)
}

inline CATBoolean
CATPolyGraph::Vertex::IsDefined() const
{
  return _Defined;
}

inline unsigned int
CATPolyGraph::Vertex::GetNbEdges() const
{
  return _NbEdges;
}

inline unsigned int
CATPolyGraph::Vertex::GetEdge(unsigned int i) const // WARNING: Assume n is valid (ie 0 < e and e <= _NbFacets)
{
  if (_EdgeListSize)
    return _Edge._List[i - 1];
  return i == 1 ? _Edge._E : 0; // Paranoid
}

// Edge

inline
CATPolyGraph::Edge::Edge()
{
  _Vertices[0] = 0;
  _Vertices[1] = 0;
}

inline
CATPolyGraph::Edge::Edge(const int v0, const int v1)
{
  _Vertices[0] = v0;
  _Vertices[1] = v1;
}

inline void
CATPolyGraph::Edge::Recycle(int v0, int v1)
{
  _Vertices[0] = v0;
  _Vertices[1] = v1;
}

inline CATBoolean
CATPolyGraph::Edge::IsDefined() const
{
  return _Vertices[0] != 0;
}

// Graph

inline int
CATPolyGraph::GetNbVertices() const
{
  return _NbVertices;
}

inline int
CATPolyGraph::GetVertexExternalDegre(const int iVertex) const
{
  if (0 < iVertex && iVertex <= (int) _Vertices.Size())
  {
    const Vertex &V = _Vertices[iVertex];
    return V.IsDefined() ? V.GetNbEdges() : 0;
  }
  return 0;
}

inline int
CATPolyGraph::GetNbEdges() const
{
  return _NbEdges;
}

#endif // !CATPolyGraph_H
