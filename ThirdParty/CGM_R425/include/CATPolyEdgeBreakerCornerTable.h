// Creation: November 2021 - TCT5

#ifndef _AIX_SOURCE

#ifndef CATPolyEdgeBreakerCornerTable_h
#define CATPolyEdgeBreakerCornerTable_h

#include "PolyEdgeBreaker.h"

#include "CATSysErrorDef.h"

#include <vector>
#include <utility>

class ExportedByPolyEdgeBreaker CATPolyEdgeBreakerCornerTable
{
public:
  CATPolyEdgeBreakerCornerTable(unsigned int iNbTriangles, bool iMapInputIdx = false);
  virtual ~CATPolyEdgeBreakerCornerTable();

public:
  bool IsClosed() const;
  bool VertexIsReferencedByTriangle(int iTriangle, int iVertex) const;

public:
  void SwapCW(int iTriangle);
  void SwapCCW(int iTriangle);
  void SwapTriangles(int iTriangle1, int iTriangle2);

public:
  void ReplaceVertexIndicesWithStreamedVertexIndices(const std::vector<int> &iMapOfStreamedVertexIndicesToInputIndices);

// Filling Methods
public:
  inline void SetVertex(int iCorner, int iVertex)
  {
    m_V[iCorner] = iVertex;
  }

  inline void SetOpposite(int iCorner, int iOppositeCorner)
  {
    m_O[iCorner] = iOppositeCorner;
  }

  inline void SetTriangleInputIndex(int iTriangle, int iInputIndex)
  {
    if (iTriangle < m_InputTriangleIndices.size())
      m_InputTriangleIndices[iTriangle] = iInputIndex;
  }

// Topology Methods 
public:
  HRESULT GetLoops(unsigned int iNbOfBoundaryVertices, std::vector<std::vector<int>> &oLoops);

// Getters
public:
  inline unsigned int GetNbTriangles() const
  {
    return m_NbTriangles;
  }

  inline unsigned int GetTriangle(int iCorner) const
  {
    return iCorner / 3;
  }

  inline int GetOpposite(int iCorner) const
  {
    return m_O[iCorner];
  }

  inline int GetVertex(int iCorner) const
  {
    return m_V[iCorner];
  }

  inline int GetNextCorner(int iCorner) const
  {
    return (iCorner / 3) * 3 + ((iCorner + 1) % 3);
  }

  inline int GetPrevCorner(int iCorner) const
  {
    return GetNextCorner(GetNextCorner(iCorner));
  }

  inline int GetCCWCorner(int iCorner) const
  {
    return GetOpposite(GetPrevCorner(iCorner));
  }

  inline int GetCWCorner(int iCorner) const
  {
    return GetOpposite(GetNextCorner(iCorner));
  }

  inline int GetRightTriangle(int iCorner) const
  {
    return GetTriangle(GetCWCorner(iCorner));
  }

  inline int GetLeftTriangle(int iCorner) const
  {
    return GetTriangle(GetCCWCorner(iCorner));
  }

  inline std::vector<int>&& StealMapOfInputTriangleIndices()
  {
    return std::move(m_InputTriangleIndices);
  }

  inline std::vector<unsigned char>&& StealMapOfTriangleRotations()
  {
    return std::move(m_TriangleRotations);
  }

protected:
  unsigned int m_NbTriangles;

  std::vector<int> m_O;
  std::vector<int> m_V;
  
  std::vector<int> m_InputTriangleIndices; // Optional
  std::vector<unsigned char> m_TriangleRotations; // Optional
};

#endif

#endif // AIX
