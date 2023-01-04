// Creation: November 2021 - TCT5

#ifndef _AIX_SOURCE

#ifndef CATPolyEdgeBreakerCompression_h
#define CATPolyEdgeBreakerCompression_h

#include "PolyEdgeBreaker.h"

#include "CATSysErrorDef.h"

#include <unordered_set>
#include <vector>

class CATPolyEdgeBreakerCornerTable; 
class CATPolyEdgeBreakerStreamable;

class CATIPolyEdgeBreaker3DConstLayer
{
public:
  CATIPolyEdgeBreaker3DConstLayer() {}
  virtual ~CATIPolyEdgeBreaker3DConstLayer() {}

public:
  virtual void SetMapOfStreamedVertexIndicesToMeshIndices(const std::vector<int>*) = 0;

public:
  virtual HRESULT Get(int iVertex, double& oX, double& oY, double& oZ) const = 0;
  virtual unsigned int GetPrecision() const = 0;
};

class ExportedByPolyEdgeBreaker CATPolyEdgeBreakerCompression
{
public:
  CATPolyEdgeBreakerCompression(CATPolyEdgeBreakerCornerTable &iCornerTable);
  virtual ~CATPolyEdgeBreakerCompression();

public:
  HRESULT Run(CATPolyEdgeBreakerStreamable &ioStreamable);

public:
  void SetPositionLayer(CATIPolyEdgeBreaker3DConstLayer *ipLayer);
  void SetNormalLayer(CATIPolyEdgeBreaker3DConstLayer *ipLayer);

protected:
  HRESULT Compress();

  HRESULT VisitBoundaryVertices();
  int FindSuitableStartTriangle();

  HRESULT Quantize();
  HRESULT GetParallelogram(int v0, int v1, int v2, double &oX, double &oY, double &oZ) const;

protected:
  CATPolyEdgeBreakerCornerTable &m_CornerTable;
  CATPolyEdgeBreakerStreamable *m_pStreamable;

  unsigned int m_NbOfVisitedTriangles;
  std::unordered_set<int> m_VisitedVertices;

  unsigned int m_NbOfVisitedBoundaryVertices;
  std::unordered_set<int> m_BoundaryVerticesToSet;

  CATIPolyEdgeBreaker3DConstLayer *m_pPositionLayer;
  CATIPolyEdgeBreaker3DConstLayer *m_pNormalLayer;
};

#endif

#endif // AIX
