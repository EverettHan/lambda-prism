// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyBarGraphSurfaceLayers.h
//
//===================================================================
// October 2011  Creation NDO
//===================================================================
#ifndef CATPolyBodyBarGraphSurfaceLayers_H
#define CATPolyBodyBarGraphSurfaceLayers_H

#include "CATPolyBarGraph.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATPolyRefCounted.h"

#include "CATMapOfIntToInt.h"
#include "CATPolyBodyBarGraphDataVector.h"
#include <vector>

#include "CATIPolySurfaceVertexTextureCoordConstLayer.h"
#include "CATUnicodeString.h"

class CATPolyBodyBarGraph;
class CATPolyBodyBarGraphSurfaceDataLayer;
class CATPolyBodyBarGraphSurfaceVertexData;

/**
 * Layers associated to a CATPolyFace including:
 *   (1) Vertex normal layer (or layers one for each frame.)
 *   (2) Texture coordinates layer (or layers one for each frame.)
 *   (3) Map of nodes from the graph to a surface vertex to address its normal or its texture coordinates.
 */
class ExportedByPolyBarGraph CATPolyBodyBarGraphSurfaceLayers : public CATPolyRefCounted
{
public:
  class ExportedByPolyBarGraph LayerIdIterator
  {
  public:
    LayerIdIterator(const CATPolyBodyBarGraphSurfaceLayers& iSurfaceLayer, CATPolyBodyBarGraphDataVector::DataType iDataType, unsigned int iFrame);
    ~LayerIdIterator();

  public:
    void Begin();
    CATBoolean End() const;
    void operator++(int);
    unsigned int Get() const;

  private:
    const CATPolyBodyBarGraphDataVector::DataType _DataType;
    const std::vector<CATPolyBodyBarGraphDataVector*> *_DataLayers;
    unsigned int _CurrentId;
  };

public:

  CATPolyBodyBarGraphSurfaceLayers (CATPolyBodyBarGraph& iBodyGraph, const unsigned int iSuggestedSize);

protected:

  ~CATPolyBodyBarGraphSurfaceLayers ();

public:

  /**
   * Adds a new vertex normal/texture/other coordinates layer.
   * @param iLayer
   *   The layer index.
   * @param iType
   *   The layer type.
   * @param iClassId
   *   The class type used to create PolyBody texture layer.
   * @param iDim
   *   The dimension of imported layer.
   * @param iIdentifier
   *   The layer identifier if any.
   * @param iConstraint
   *   The layer is processed as a constraint on position.
   * @param iFrame
   *   The index of the frame (ranging from 0 to GetNbFrames () - 1.)
   */
  HRESULT AddVertexDataCoordLayer (unsigned int iLayer, CATPolyBodyBarGraphDataVector::DataType iType, unsigned int iDim, const CLSID& iClassId, const CATUnicodeString& iIdentifier, CATBoolean iConstraint, unsigned int iFrame);

public:

  /**
   * Adds a surface vertex to the surface layers and returns its index.
   * @param oSurfaceVertex
   *   The returned index of the surface vertex.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if the surface vertex is added successfully;
   *   <li> <tt>E_FAIL</tt> or another error code if an error occurs.
   * </ul>
   */
  HRESULT AddSurfaceVertex (unsigned int& oSurfaceVertex);

  /**
   * Removes a surface vertex from the surface layers.
   * @param iSurfaceVertex
   *   The input index of the surface vertex to remove.
   * @return
   *   <li> <tt>S_OK</tt> if the surface vertex is removed successfully;
   *   <li> <tt>E_FAIL</tt> or another error code if an error occurs.
   */
  HRESULT RemoveSurfaceVertex (const unsigned int iSurfaceVertex);

  /**
   * Associates a surface vertex to a node.
   */
  HRESULT SetSurfaceVertex (const unsigned int iNode, const unsigned int iSurfaceVertex);

  /**
   * Given a node returns its surface vertex.
   */
  HRESULT GetSurfaceVertex (const unsigned int iNode, unsigned int& oSurfaceVertex) const;

  /**
   * Given a node returns its surface node index. Used when normal constraints are enabled.
   */
  HRESULT SetSurfaceNode(const unsigned int iNode, const unsigned int iSurfaceNode); //TODO JBS2 RENAME THAT !!
  HRESULT GetSurfaceNode(const unsigned int iNode, unsigned int& oSurfaceNode) const; //TODO JBS2 RENAME THAT !!

public:

  unsigned int GetNbTextureLayers() const;

  CATPolyBodyBarGraphDataVector* GetVertexDataLayer(const unsigned int iLayer, const unsigned int iFrame);
  const CATPolyBodyBarGraphDataVector* GetVertexDataLayer(const unsigned int iLayer, const unsigned int iFrame) const;

  HRESULT GetNewCutId(unsigned int& oCutId, unsigned int iLayer, unsigned int iFrame); //TODO JBS2 RENAME TO CutSurfaceVertex ??
  HRESULT SetCutId(unsigned int iBar, unsigned int iNode, unsigned int iCutId, unsigned int iLayer, unsigned int iFrame, CATBoolean iIgnoreSurfaceVertex = FALSE);
  HRESULT GetCutId(unsigned int iBar, unsigned int iNode, unsigned int &oCutId, unsigned int iLayer, unsigned int iFrame) const;
  HRESULT RemoveBarCutIdNode0(unsigned int iBar, unsigned int iLayer, unsigned int iFrame);
  HRESULT RemoveBarCutIdNode1(unsigned int iBar, unsigned int iLayer, unsigned int iFrame);

  HRESULT BuildDuplicateNodeData(const CATSetOfInt& iNodes);
  unsigned int GetNbDuplicateNodes(unsigned int iFrame) const;
  unsigned int GetDuplicateCutIds(unsigned int iNode, const std::vector<unsigned int> & iCutIdVec, unsigned int iFrame) const;
  unsigned int GetDuplicateNodeId(unsigned int iIndex, unsigned int iFrame) const;
  unsigned int GetDuplicateNodeCutId(unsigned int iIndex, unsigned int iLayer, unsigned int iFrame) const;
  HRESULT GetCCWTriangleDuplicateNodeIds(unsigned int(&ioTriNodes)[3], unsigned int f, unsigned int iFrame) const;
  HRESULT GetCCWTriangleCutIds(std::vector<unsigned int>(&oTriCutIdVec)[3], unsigned int(&iTriNodes)[3], unsigned int f, unsigned int iFrame) const;

private:

  CATPolyBodyBarGraph& _BodyGraph;

  CATPolyBodyBarGraphSurfaceVertexData *_SurfaceVertexData;
  std::vector<CATPolyBodyBarGraphSurfaceDataLayer*> _FrameDataLayers;

  unsigned int _LayerSize;                     // Size of the layers (normals, texture coordinates).

private:

  HRESULT IncreaseSize ();

  // Forbidden.
  CATPolyBodyBarGraphSurfaceLayers (const CATPolyBodyBarGraphSurfaceLayers& iOther);
  CATPolyBodyBarGraphSurfaceLayers& operator= (const CATPolyBodyBarGraphSurfaceLayers& iOther);

};

#endif
