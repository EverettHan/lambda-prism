// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyBarGraphBuilder.h
//
//===================================================================
// September 2011  Creation NDO
//===================================================================
#ifndef CATPolyBodyBarGraphBuilder_H
#define CATPolyBodyBarGraphBuilder_H

#include "PolyBarGraph.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATUnicodeString.h"
#include <vector>

class CATPolyBody;
class CATPolyCell;
class CATPolyFace;
class CATPolyEdge;
class CATPolyVertex;

class CATIPolyBodyFrameLayers;
class CATMathTransformation;

class CATPolyBodyBarGraph;
class CATPolyBodyBarGraphBuilderLayerUpdater;
class CATPolyCellIndexMap;
class CATSetOfInt;


/**
 * Builds a full CATPolyBodyBarGraph by adding all the bars from a CATPolyBody.
 */
class ExportedByPolyBarGraph CATPolyBodyBarGraphBuilder
{

public:

  /*
   * Constructor.
   * @param iWithNormals
   *   An option for inclusion of the normals in the bar graph.  
   * @param iWithTextures
   *   An option to inclusion of the texture coordinates in the bar graph of dimension 1, 2 or 3.
   *   If set to 0, texture coordinates are excluded.
   * @param iWithFilter
   *   Layers with identifier that matches filter will be added.
   */
  inline CATPolyBodyBarGraphBuilder(CATBoolean iWithNormals, CATBoolean iWithTextures, const std::vector<CATUnicodeString>* iWithFilter = NULL);

  /**
   * Constructor.
   * @param iWithNormals
   *   An option for inclusion of the normals in the bar graph.  
   * @param iTextureDimension
   *   An option to inclusion of the texture coordinates in the bar graph of dimension 1, 2 or 3.
   *   If set to 0, texture coordinates are excluded.
   * @param iDataLayerIndices
   *   The indices of the data layers to process in the bar graph.
   */
  //inline CATPolyBodyBarGraphBuilder (CATBoolean iWithNormals, unsigned int iTextureDimension, const CATSetOfInt& iDataLayerIndices);

  ~CATPolyBodyBarGraphBuilder () {}

public:

  /**
   * Observer interface for builder.
   * It can be used to construct mappings from the input CATPolyCell to tags (cell IDs) (or its opposite.)
   */
  class Observer
  {
  public:
    /**
     * Associates a tag to an input poly cell.
     * @param iInputCell
     *        Cell from the input CATPolyBody
     * @param iTag
     *        Associated tag inside bar-graph
     */
    virtual void AssociatePolyCellAndTag (CATPolyCell* iInputCell, const unsigned int iTag) = 0;
    /**
     * Associates a node id to an input micro vertex.
     * @param iInputMicroVertex
     *        Micro vertex index inside input cell. It can be the index of vertex inside a CATIPolySurface, or inside a CATIPolyCurve, and 0 for a CATIPolyPoint.
     * @param iCellTag
     *        Bar-graph tag associated to the cell (see AssociatePolyCellAndTag)
     * @param iNode
     *        Bar-graph node associated to the micro vertex.
     */
    virtual void AssociatePolyVertexAndTag (const int iInputMicroVertex, const unsigned int iNode, const unsigned int iCellTag) = 0;

  };

public:

  /**
   * Adds the data from a CATPolyBody to a bar graph.
   * @param iPolyBody
   *   The input CATPolyBody.
   * @param iMatrix
   *   A CATMathTransformation applied to the CATPolyBody data.
   *   This input parameter can be null.
   * @param ioBodyGraph
   *   The bar graph to which the object is added.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> on successful construction of a bar graph.
   *   <li> <code> E_FAIL </code> on failure.
   * </ul>
   */
  inline HRESULT AddPolyBody (const CATPolyBody& iPolyBody, const CATMathTransformation* iMatrix,
                              CATPolyBodyBarGraph& ioBodyGraph, Observer* iObserver = 0);

  /**
   * Adds the data from a CATPolyBody with multiple frame layers to a bar graph.
   * @param iPolyBody
   *   The input CATPolyBody.
   * @param iFrameLayers
   *   The input frame layers.
   * @param iMatrix
   *   A CATMathTransformation applied to the CATPolyBody data.
   *   This input parameter can be null.
   * @param ioBodyGraph
   *   The bar graph to which the object is added.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> on success construction of a bar graph.
   *   <li> <code> E_FAIL </code> on failure.
   * </ul>
   */
  inline HRESULT AddPolyBody (const CATPolyBody& iPolyBody, const CATIPolyBodyFrameLayers& iFrameLayers, const CATMathTransformation* iMatrix,
                              CATPolyBodyBarGraph& ioBodyGraph, Observer* iObserver = 0);

private:

  HRESULT RunPrivate (const CATPolyBody& iPolyBody, const CATIPolyBodyFrameLayers* iFrameLayers, const CATMathTransformation* iMatrix,
                      CATPolyBodyBarGraph& ioBarGraph, Observer* iObserver);

  HRESULT ProcessVertices (const CATPolyBody& iPolyBody, 
                           CATPolyBodyBarGraph& ioBarGraph, CATPolyCellIndexMap& cellToNode, 
                           CATPolyBodyBarGraphBuilderLayerUpdater* iUpdater, Observer* iObserver);

  HRESULT ProcessVertex (CATPolyVertex& V, const unsigned int gv,
                         CATPolyBodyBarGraph& ioBarGraph, CATPolyCellIndexMap& cellToNode, 
                         CATPolyBodyBarGraphBuilderLayerUpdater* iUpdater, Observer* iObserver);

  HRESULT ProcessEdges (const CATPolyBody& iPolyBody, 
                        CATPolyBodyBarGraph& ioBarGraph, CATPolyCellIndexMap& cellToNode, 
                        CATPolyBodyBarGraphBuilderLayerUpdater* iUpdater, Observer* iObserver);

  HRESULT ProcessEdge (CATPolyEdge& E, const unsigned int ge,
                       CATPolyBodyBarGraph& ioBarGraph, CATPolyCellIndexMap& cellToNode, 
                       CATPolyBodyBarGraphBuilderLayerUpdater* iUpdater, Observer* iObserver);

  HRESULT ProcessFaces (const CATPolyBody& iPolyBody, const CATBoolean iFlipOrientation, 
                        CATPolyBodyBarGraph& ioBarGraph, const CATPolyCellIndexMap& cellToNode, 
                        CATPolyBodyBarGraphBuilderLayerUpdater* iUpdater, Observer* iObserver);

  HRESULT ProcessFace (CATPolyFace& F, const CATBoolean iFlipOrientation, const unsigned int gf, 
                       CATPolyBodyBarGraph& ioBarGraph, const CATPolyCellIndexMap& cellToNode, 
                       CATPolyBodyBarGraphBuilderLayerUpdater* iUpdater, Observer* iObserver);

private:

  CATBoolean _WithNormals;
  CATBoolean _WithTextures;
  const std::vector<CATUnicodeString> *_WithFilter;
};

inline CATPolyBodyBarGraphBuilder::CATPolyBodyBarGraphBuilder (CATBoolean iWithNormals, CATBoolean iWithTextures, const std::vector<CATUnicodeString> *iWithFilter) :
  _WithNormals (iWithNormals),
  _WithTextures (iWithTextures),
  _WithFilter(iWithFilter)
{
}

//inline CATPolyBodyBarGraphBuilder::CATPolyBodyBarGraphBuilder (CATBoolean iWithNormals, unsigned int iTextureDimension, const CATSetOfInt& iDataLayerIndices) :
//  _WithNormals (iWithNormals),
//  _TextureDimension (iTextureDimension)
//{
//  // Process all data layers for now.
//}

inline HRESULT CATPolyBodyBarGraphBuilder::AddPolyBody (const CATPolyBody& iPolyBody, const CATMathTransformation* iMatrix, 
                                                        CATPolyBodyBarGraph& ioBodyGraph, Observer* iObserver)
{
  return RunPrivate (iPolyBody, 0, iMatrix, ioBodyGraph, iObserver);
}

inline HRESULT CATPolyBodyBarGraphBuilder::AddPolyBody (const CATPolyBody& iPolyBody, const CATIPolyBodyFrameLayers& iFrameLayers, const CATMathTransformation* iMatrix,
                                                        CATPolyBodyBarGraph& ioBodyGraph, Observer* iObserver)
{
  return RunPrivate (iPolyBody, &iFrameLayers, iMatrix, ioBodyGraph, iObserver);
}

#endif
