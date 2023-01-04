#ifndef CATIPGMHealGaps_h_
#define CATIPGMHealGaps_h_

// COPYRIGHT DASSAULT SYSTEMES 2014

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATEdge;
class CATFace;
class CATGeoFactory;
class CATTopData;
class CATVertex;
class CATLISTP(CATVertex);
class CATLISTP(CATEdge);
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMHealGaps;

/**
 * Class defining the topological operator that heals edge and vertex gaps in a body.
 * By default, the operator works globally and tries to repair all edge and vertex gaps in the body.
 * If the user calls <tt>SetCellsToHeal</tt>, then the operator will try to repair only the specified edges and vertices.
 * By default, the operator will try to heal edge gaps by extending and reintersecting adjacent faces and edges.
 * Use the <tt>AllowShapeDeformation</tt> method to turn on healing by deforming face and edge geometry.
 * <ul>
 *     <li> The <tt>CATIPGMHealGaps</tt> operator is created with the <tt>CATPGMCreateHealGaps</tt> global function.
 *     <li> It is the user's responsibility to <tt>delete</tt> the operator with the usual C++ delete operator after it has been used.
 * </ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMHealGaps: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMHealGaps();

  /**
	* Restricts healing to specified edges and vertices and adds a vertex to the list of cells to be healed.
	* @param ipVertexToHeal
	* The pointer to the vertex. The vertex must belong to the input body.
	*/
  virtual void SetCellsToHeal(CATVertex *ipVertexToHeal) = 0;

  /**
	* Restricts healing to specified edges and vertices and adds vertices to the list of cells to be healed.
	* @param iVerticesToHeal
	* The list of the vertex pointers. The vertices must belong to the input body.
	*/
  virtual void SetCellsToHeal(CATLISTP(CATVertex) &iVerticesToHeal) = 0;

  /**
	* Restricts healing to specified edges and vertices and adds an edge to the list of cells to be healed.
	* @param ipEdgeToHeal
	* The pointer to the edge. The edge must belong to the input body.
	*/
  virtual void SetCellsToHeal(CATEdge *ipEdgeToHeal) = 0;

  /**
	* Restricts healing to specified edges and vertices and adds edges to the list of cells to be healed.
	* @param iEdgesToHeal
	* The list of edge pointers. The edges must belong to the input body.
	*/
  virtual void SetCellsToHeal(CATLISTP(CATEdge) &iEdgesToHeal) = 0;

  /**
	* Sets the minimum gap to heal. 
	* Healing will not be applied to gaps less than this value. The default value is the model resolution.
	* @param iMinGapTolerance
	* The minimum healing gap.
	*/
  virtual void SetMinGapToHeal(double iMinGapTolerance) = 0;

  /**
	* Sets the maximum healing gap. 
	* Healing will not be applied to gaps greater than this value. The default value is the 1000 * model resolution.
	* @param iMaxGapTolerance
	* The maximum healing gap.
	*/
  virtual void SetMaxGapToHeal(double iMaxGapTolerance) = 0;

  /**
	* Allows face and edge geometry to be deformed and sets the maximum deformation value.
	* By default, shape deformation is disabled.
	* @param iMaxShapeDeformation
	* The the maximum allowed face deformation value. The value must be 
	* greater than factory resolution.
	*/
  virtual void AllowShapeDeformation(double iMaxShapeDeformation) = 0;

  /**
	* Adds an edge to the list of cells that cannot be modified. 
	* By default, all cells are modifiable.
	* @param ipEdgeNotToChange
	* The pointer to the edge. The edge must belong to the input body.
	*/
  virtual void SetCellsNotToChange(CATEdge *ipEdgeNotToChange) = 0;

  /**
	* Adds edges to the list of cells that cannot be modified. 
	* By default, all cells are modifiable.
	* @param iEdgesNotToChange
	* The list of the edge pointers. The edges must belong to the input body.
	*/
  virtual void SetCellsNotToChange(const CATLISTP(CATEdge) &iEdgesNotToChange) = 0;

  /**
	* Adds a face to the list of cells that cannot be modified. 
	* By default, all cells are modifiable.
	* @param ipFaceNotToChange
	* The pointer to the face. The face must belong to the input body.
	*/
  virtual void SetCellsNotToChange(CATFace *ipFaceNotToChange) = 0;

  /**
	* Adds faces to the list of cells that cannot be modified. 
	* By default, all cells are modifiable.
	* @param iFacesNotToChange
	* The list of the face pointers. The faces must belong to the input body.
	*/
  virtual void SetCellsNotToChange(const CATLISTP(CATFace) &iFacesNotToChange) = 0;

  /**
	* Adds all faces whose geometry is of the specified type to the list of cells that cannot be modified. 
	* This is useful, for example, to not allow canonical faces to change.
	* By default, all cells are modifiable.
	* @param iFaceTypeNotToChange
	* The face geometry type. All the faces of the type in the input body belong to the set.
	*/
  virtual void SetCellsNotToChange(CATGeometricType iFaceTypeNotToChange) = 0;

  /**
	* Returns the list of the edges with gaps.
	* If calling before healing, the edges are with gaps greater than the minimum gap tolerance. 
	* If calling after healing, the edges are the remaining un-healed ones.
	* @param oEdgesWithGaps
	* The list of edges with gaps.
	*/
  virtual void GetEdgesWithGaps(CATLISTP(CATEdge) &oEdgesWithGaps) = 0;

  /**
	* Returns the list of the vertices with gaps.
	* If calling before healing, the vertices are with gaps greater than the minimum gap tolerance. 
	* If calling after healing, the vertices are the remaining un-healed ones.
	* @param oVerticesWithGaps
	* The list of vertices with gaps.
	*/
  virtual void GetVerticesWithGaps(CATLISTP(CATVertex) &oVerticesWithGaps) = 0;

  /**
	* Returns the global maximum gap.
	* If calling before healing, the value is from the input body. 
	* If calling after healing, the value is from the result body. 
	* @return
	* The maximum gap on the whole body.
	*/
  virtual double GetMaxGap() = 0;

  /** 
	* @nodoc
	* Need implementation!!!
	* Returns the global maximum gap on all edges.
	* If calling before healing, the value is from the input body. 
	* If calling after healing, the value is from the result body. 
	* @return
	* The maximum edge gap on the whole body.
	*/
  virtual double GetMaxGapOnEdges() = 0;

  /**
	* Returns the global maximum gap on all vertices.
	* If calling before healing, the value is from the input body. 
	* If calling after healing, the value is from the result body. 
	* @return
	* The maximum vertex gap on the whole body.
	*/
  virtual double GetMaxGapOnVertices() = 0;

  /**
	* Returns the gap for the given edge.
	* @ipEdge
	* The edge.
	* @return
	* The maximum gap of the edge.
	*/
  virtual double GetGap(CATEdge *ipEdge) = 0;

  /**
	* Returns the gap for the given vertex.
	* @ipVertex
	* The vertex.
	* @return
	* The maximum gap of the vertex.
	*/
  virtual double GetGap(CATVertex *ipVertex) = 0;

  /**
	* Returns the faces that have been deformed.
	* @oListOfFaces
	* The deformed faces.
	*/
  virtual void GetDeformedFaces(CATLISTP(CATFace) &oListOfFaces) = 0;

  /**
	* Returns the value of the maximum deformation applied to the given face.
	* @ipFace
	* The face to be checked.
	* @return
	* The maximum deformation applied to the face.
	*/
  virtual double GetMaxDeformation(CATFace *ipFace) = 0;

  /**
	* Returns the value of the maximum deformation applied to the given edge.
	* @ipEdge
	* The edge to be checked.
	* @return
	* The maximum deformation applied to the edge.
	*/
  virtual double GetMaxDeformation(CATEdge *ipEdge) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMHealGaps(); // -> delete can't be called
};

/**
 * Creates the operator that heals edge and vertex gaps inside a <tt>CATBody</tt>.
 * @param ipFactory
 * The pointer to the factory of the geometry.
 * @param ipTopData
 * The pointer to the <tt>CATTopData</tt> object used to create the operator.
 * @param ipInputBody
 * The pointer to the input body.
 * @return
 * The pointer to the created operator. To <tt>delete</tt> with the usual C++ delete operator afer use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMHealGaps *CATPGMCreateHealGaps(
  CATGeoFactory *ipFactory,
  CATTopData *ipTopData,
  CATBody *ipInputBody);

#endif /* CATIPGMHealGaps_h_ */
