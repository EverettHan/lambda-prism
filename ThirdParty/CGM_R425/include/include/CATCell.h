#ifndef CATCell_H
#define CATCell_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
* @CAA2Level L1
* @CAA2Usage U3
*/ 

#include "CATTopObject.h"
//#include "CATTopDef.h"
#include "CATTopDefine.h"
#include "CATGMModelInterfaces.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATTopology.h"
#include "CATIACGMLevel.h"
#include "ListVOfLong.h"
 
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATCell ;
#else
extern "C" const IID IID_CATCell ;
#endif

class CATBody;
class CATDomain;
class CATBoundaryIterator;
class CATBoundedCellsIterator;
class CATMathPoint;

/**
* Interface representing a topological cell.
* <br>A cell represents a geometry of a given dimension
* bounded by cells of lower dimension. A cell is oriented with regards to an
* underlying geometry:
* <dl><dt><tt>CATOrientationNegative</tt><dd> the cell orientation is reversed
* with regards to the standard orientation.
*     <dt><tt>CATOrientationPositive</tt><dd> the cell orientation is the 
* standard orientation.
*     <dt><tt>CATOrientationUnknown</tt><dd> the cell orientation is not
* defined.</dl>
* The cell CATSide defines the matter side on a bounding cell of a cell:
* <table border=1>
* <tr><td></td><th>CATFace</th><th>CATEdge</th><th>CATVertex</th></tr>
* <tr><th>CATVolume</th>
*     <td><tt>CATSideLeft</tt>: the face normal points inside the volume<br>
*         <tt>CATSideRight</tt>: the face normal points outside the volume<br>
*         <tt>CATSideFull</tt>: the face is immersed into the volume</td>
*     <td><tt>CATSideFull</tt>: the edge is immersed into the volume</td>
*     <td><tt>CATSideFull</tt>: the vertex is immersed into the volume</td>
*</tr>
* <tr><th>CATFace</th>
*     <td>  </td>
*     <td><tt>CATSideleft</tt>: when the observation direction is opposite 
* to the face normal and the edge is run with its own orientation, the matter
* is on the edge left<br>
*         <tt>CATSideRight</tt>: when the observation direction is opposite 
* to the face normal and the edge is run with its own orientation, the matter
* is on the edge right<br>
*         <tt>CATSideFull</tt>: the edge is immersed into the face</td>
*     <td><tt>CATSideFull</tt>: the vertex is immersed into the face</td>
*</tr>
* <tr><th>CATEdge</th>
*     <td>  </td>  <td></td>
*     <td><tt>CATSideLeft</tt>: the vertex is at the edge beginning <br>
*         <tt>CATSideRight</tt>: the vertex is at the edge end<br>
*         <tt>CATSideFull</tt>: impossible</td>
*</tr>
*</table>
* If the cell bounds the domain twice, it is set to <tt>CATSideUnknown</tt>.
* <br> A CATCell is created with the @href CATBody#CreateCell method, and deleted with the
* @href CATICGMContainer#Remove method. By default, this deletion is not recursive at the topological level:
* the domains of the cells are
* not deleted. However, the geometry of the cell, if not used by another object, is also deleted.
*/

class ExportedByCATGMModelInterfaces CATCell : public CATTopObject
{
  
  CATDeclareInterface;
  
public :
  
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  
  /**
  * Adds a CATDomain to <tt>this</tt> CATCell.
  * <br>For volumes and faces only.
  * @param iDomain
  * The pointer to the domain to add.
  * @param iLocation
  * The location of the domain to bound <tt>this</tt>.
  */
  virtual void AddDomain( CATDomain * iDomain, CATLocation iLocation = CATLocationUnknown  )=0;
  
  
  /**
  * Returns the number of internal CATDomains of <tt>this</tt> CATCell.
  *<br>This method performs a recursive scan.
  * @return
  * The number of internal domains.
  */
  virtual CATLONG32 GetNbInternalDomains()=0;
  
  /**
  * Returns the dimension of <tt>this</tt> CATCell.
  * @return
  * The dimension.
  * <br><b>Legal values</b>:
  * <dl><dt>0</dt><dd> for a vertex.
  * <dt>1</dt><dd> for an edge.
  * <dt>2</dt><dd> for a face.
  * <dt>3</dt><dd> for a volume.
  * </dl>
  */
  virtual short GetDimension()=0;
  
  /**
  * Adds a CATCell to the boundary of <tt>this</tt> CATCell.
  * <br> The cells dimensions must match the domain low and high dimensions.
  * @param iBoundingCell
  * The pointer to the cell to add to the boundary of <tt>this</tt>.
  * @param iSideOrientation
  * The side of the matter when walking along the natural orientation of <tt>iBoundingCell</tt>.
  * @param iDomain
  * The pointer to the domain that will contain the added cell.
  * <br>If not <tt>NULL</tt>, the bounding cell is also added to the domain.
  * @param iWithGeometry
  * The pointer to the underlying geometry ( a CATPCurve for an
  *  Edge-Bounding-Face, a CATPointOnEdgeCurve for a Vertex-Bounding-Edge, ..)
  *<br>If not <tt>NULL</tt> at the method call, the geometry is associated with
  * <tt>iBoundingCell</tt>.
  */
  virtual void AddBoundingCell   ( CATCell * iBoundingCell, CATSide iSideOrientation, 
    CATDomain * iDomain=NULL,   CATGeometry* iWithGeometry=NULL )=0;
  
#if defined ( CATIACGMV5R21 )
    /**
    * Removes a CATCell from the boundary of <tt>this</tt> CATCell.
    * @param iCellToRemove
    * The pointer to the cell to remove. 
    * The cell is detached from the boundary, but still exists in the CATGeoFactory.
    * @param iRemoveFromFactory
    * The action on the detached cell <tt>iDomainToDetach</tt>.
    * Dedicated to the case where no more CATDomain refers to <tt>iCellToDetach</tt>.
    * <br><b>Legal values</b>:
    * <dl><dt><tt>FALSE</tt></dt><dd> the <tt>iCellToDetach</tt> remains in the factory
    *     <dt><tt>TRUE</tt></dt><dd> the <tt>iCellToDetach</tt> is removed from the factory with RemoveDependancies management</dl>
    */
  virtual void RemoveBoundingCell( CATCell * iCellToRemove, CATBoolean iRemoveFromFactory = FALSE )=0;
#else
    /**
    * Removes a CATCell from the boundary of <tt>this</tt> CATCell.
    * @param iCellToRemove
    * The pointer to the cell to remove. 
    * The cell is detached from the boundary, but still exists in the CATGeoFactory.
  */
  virtual void RemoveBoundingCell( CATCell * iCellToRemove )=0;
#endif
  
  
  /**
  * Defines the geometry of <tt>this</tt> CATCell. 
  * @param iGeometry
  * The pointer to the geometry to associate with <tt>this</tt>.
  * <ul><li>The geometry of a CATFace is a CATSurface.
  * <li>The geometry of a CATEdge is a CATEdgeCurve.
  * <li>The geometry of a CATVertex is a CATMacroPoint.
  * <li><tt>SetGeometry</tt> is not used in case of a CATVolume,
  * as the geometry of a CATVolume always is the 3D space. 
  *</ul>
  * @param iOrientation
  * The relative orientation of the cell with regards to the geometry.
  */
  virtual void SetGeometry(CATGeometry * iGeometry,
                           CATOrientation iOrientation=CATOrientationPositive )=0;
  
    /**
    * Modifies the orientation of <tt>this</tt> CATCell with regards to its geometry.
    * <br>For faces and edges.
    * @param iNewOrientation
    * The new relative orientation.
  */
  virtual void  SetGeometryOrientation(CATOrientation iNewOrientation)=0;
  
  /**
  * Returns the geometry of <tt>this</tt> CATCell.
  * @param  ioOrientation
  * The relative orientation between <tt>this</tt> and its geometry.
  * If <tt>NULL</tt>, the orientation is not filled out.
  * @return
  * The pointer to the geometry of <tt>this</tt>.
  */
  virtual CATGeometry  * GetGeometry(CATOrientation * ioOrientation=NULL)=0;
  
  /**
  * Returns the orientation of <tt>this</tt> CATCell with regards to its geometry.
  * @return
  * The relative orientation between <tt>this</tt> and its geometry.
  */
  virtual CATOrientation GetGeometryOrientation() = 0;
  
  /**
  * Sets the geometry of <tt>this</tt> CATCell with respect to a bounded cell.
  * @param iBoundedCell
  * The pointer to the cell bounded by <tt>this</tt>.
  * @param iSide
  * The matter side attribute of <tt>this</tt>, as bounding <tt>iBoundedCell</tt>.
  * @param iGeomOnSupport
  * The pointer to the geometry of <tt>this</tt>.
  * <ul><li> If <tt>this</tt> is a CATEdge, <tt>iBoundedCell</tt> is a CATFace, 
  * and <tt>iGeomOnSupport</tt> is a CATPCurve.
  * <li> If <tt>this</tt> is a CATVertex, <tt>iBoundedCell</tt> is a CATEdge, 
  * and <tt>iGeomOnSupport</tt> is a CATPointOnEdgeCurve.
  * </ul>
  */
  virtual void           SetGeometryOnCell(CATCell     * iBoundedCell, 
    CATSide       iSide,
    CATGeometry * iGeomOnSupport)=0;
  
    /**
    * Returns the geometry of <tt>this</tt> CATCell with respect to a bounded cell.
    * @param iBoundedCell
    * The pointer to the cell bounded by <tt>this</tt>.
    * @param iSide
    * The matter side attribute of <tt>this</tt>, as bounding <tt>iBoundedCell</tt>.
    * @param ioOrientation
    * A pointer to the cell orientation with regards to the geometry.
    * If <tt>NULL</tt>, the orientation is not filled out.
    * @return
    * The pointer to the geometry of <tt>this</tt>.
    * <ul><li> If <tt>this</tt> is a CATEdge, <tt>iBoundedCell</tt> is a CATFace, 
    * and <tt>iGeomOnSupport</tt> is a CATPCurve.
    * <li> If <tt>this</tt> is a CATVertex, <tt>iBoundedCell</tt> is a CATEdge, 
    * and <tt>iGeomOnSupport</tt> is a CATPointOnEdgeCurve.
    * </ul>
  */
  virtual CATGeometry  * GetGeometryOnCell(CATCell        * iBoundedCell, 
    CATSide          iSide, 
    CATOrientation * ioOrientation=NULL )=0;
  
    /**
    * Creates an iterator on the boundary of <tt>this</tt> CATCell.
    * @return
    * The pointer to the created iterator. You must <tt>delete</tt> this operator after use. 
  */
  virtual CATBoundaryIterator     * CreateBoundaryIterator()=0;
  
  /**
  * Creates an iterator on the  CATCells bounded by <tt>this</tt> CATCell.
  * @param iInBody
  * The pointer to the body in which the bounded cells are searched. Recall
  * that a same CATCell can be used by several bodies.
  * @return
  * The pointer to the created iterator. If not <tt>NULL</tt>, you must <tt>delete</tt> this operator after use.
  *  <ul><li>If <tt>this</tt> CATCell is inside <tt>iInBody</tt>, iterator is created.
  * <li>If <tt>this</tt> CATCell does not belongs to <tt>iInBody</tt>, <tt>NULL</tt> is output.
  * </ul>
  */
  virtual CATBoundedCellsIterator * CreateBoundedCellsIterator(CATBody* iInBody)=0;
  
  /**
  * Returns the number of cells bounded by <tt>this</tt> cell.
  * @param iInBody
  * The pointer to the body in which the bounded cells are searched. Recall
  * that a same CATCell can be used by several bodies.
  * @param iDifferentiateMatterSide
  * Defines whether a cell that is many times bounded by the same cell with different matter sides
  * must be counted once or twice. Notice that this configuration remains unsual.
  * <br><b>Legal values</b>:
  * <dl><dt><tt>FALSE</tt></dt><dd> if each cell only occurs once in the result (default mode)
  *     <dt><tt>TRUE</tt></dt><dd> each distinct matter side for the same bounding cell occurs in the result </dl>
  * @return
  * The number of bounded cells.
  */
  virtual CATULONG32  GetNbBoundedCells(CATBody*   inBody, CATBoolean iDifferentiateMatterSide = FALSE) = 0;
  
 /**
  * Defines <tt>this</tt> CATCell as infinite.
  *<br> All the cells are bordered, 
  *           but one can consider a cell as infinite by applying this method.
  * @param iYesOrNo
  * The infinity mode of <tt>this</tt>.
  * <br><b>Legal values</b>:
  * <tt>TRUE</tt>, if <tt>this</tt> must be considered as infinite, 
  * <tt>FALSE</tt> if it is finite (default mode).
  */
  virtual void       SetInfinite(CATBoolean iYesOrNo)=0;
  
  /**
  * Returns the infinite property of <tt>this</tt> CATCell.
  * @return
  * The infinity mode of <tt>this</tt>.
  * <br><b>Legal values</b>:
  * <tt>TRUE</tt>, if <tt>this</tt> must be considered as infinite, 
  * <tt>FALSE</tt> if it is finite (default mode).
  */
  virtual CATBoolean GetInfinite() const =0;
  
  /**
  * Tests whether <tt>this</tt> CATCell bounds a given cell of upper dimension.
  * @param iUpperDimCell
  * The pointer to the cell of upper dimension.
  * @param ioSide
  * A pointer to the matter side of the bouding cell.
  * If <tt>NULL</tt>, the side is not filled out.
  * <br>Warning: <tt>ioSide=CATSideUnknown</tt>: 
  * <ul>
  * <li>either if the difference of dimensions is greater than 1
  * <li>or if <tt>this</tt> bounds UpperDimCell twice (Left and Right)
  * </ul>
  * @return
  * The result of the test.
  * <br><b>Legal values</b>:
  * <dl><dt><tt>0</tt></dt><dd> if <tt>this</tt> does not bound 
  * <tt>iUpperDimCell</tt>
  *     <dt><tt>1</tt></dt><dd> if <tt>this</tt> bounds <tt>iUpperDimCell</tt></dl>
  */
  virtual CATBoolean  IsOnBorder(CATCell* iUpperDimCell, CATSide* ioSide=NULL) = 0;
  
    /**
    * Returns the matter side of <tt>this</tt> CATCell with regards to a bounding cell of 
    * upper dimension.
    * @param iUpperDimCell
    * The pointer to the cell of higher dimension.
    * @return
    * The side attribute.
    * @exception
    * If the difference of dimensions is greater than 1, 
    * or if <tt>this</tt> does not bound <tt>iUpperDimCell</tt>.
  */
  virtual CATSide     GetMatterSide(CATCell* iUpperDimCell) = 0;
  

  
#if defined ( CATIACGMV5R23 )

    /**
  * Retrieves the adjacent cells of <tt>this</tt> on the other side of a border cell.
  * @param iBorderCell
  * The pointer to the bounding cell.
  * @param iInBody
  * The pointer to the body in which the bounded cells are searched. Recall
  * that a same CATCell can be used by several bodies.
  * @param ioNeighborCells
  *  The pointer to the other bounded cell, Empty if <tt>iBorderCell</tt> only bounds <tt>this</tt>.
  * @param ioRelativeOrientations
  * The relative orientation of the found cells with regards to <tt>this</tt>. If <tt>NULL</tt>, this argument
  * is not output.
  * @return
  *   An HRESULT value. 
  *   <br><b>Legal values</b>:
  *   <dl>
  *     <dt>S_OK</dt>
  *     <dd>The query succeeds.</dd>
  *     <dt>E_FAIL </dt>
  *     <dd>The <tt>inBody</tt> is not valid, or <tt>this</tt> CATCell does not belongs to <tt>iInBody</tt></dd>
  *   </dl>
  */
  virtual HRESULT  GetNeighborCells(CATCell*           iBorderCell,       CATBody*     iInBody,
                                    CATLISTP(CATCell)& ioNeighborCells,   CATListOfLong * ioRelativeOrientations =NULL ) = 0;
 
#endif
  
  
  /**
  * Retrieves the adjacent cell of <tt>this</tt> on the other side of a border cell.
  * @param iBorderCell
  * The pointer to the bounding cell.
  * @param iInBody
  * The pointer to the body in which the bounded cells are searched. Recall
  * that a same CATCell can be used by several bodies.
  * @param ioRelativeOrientation
  * The relative orientation of the found cell with regards to <tt>this</tt>. If <tt>NULL</tt>, this argument
  * is not output.
  * @return
  * The pointer to the other bounded cell, <tt>NULL</tt> if <tt>iBorderCell</tt> only bounds <tt>this</tt>.
  * @exception 
  * If the result is not unique.
  */
  virtual CATCell*    GetNeighborCell(CATCell*     iBorderCell,
    CATBody*     iInBody,
    short*       ioRelativeOrientation =NULL) = 0;


    /**
    * Retrieves the cells of a given dimension  bounding <tt>this</tt> and an another cell. 
    * @param iCell
    * The pointer to the other cell, of same dimension as <tt>this</tt>.
    * @param iMaxDepthSearch
    * The range of dimensions between the  </tt>this</tt> and <tt>iCell</tt>. For example, 
	* if </tt>this</tt> and <tt>iCell</tt> are faces, specifying 1 returns the common edges, specifying 2
	* returns the common edges plus the common vertices.
    * Current limitation: <tt>this</tt> and <tt>iCell</tt> must have the same dimension.
    * @param ioResultCells
    * The list of pointers to the found cells.
    * @param iResultCellsDimension
    * The dimension <tt>(0,1,2,3)</tt> of the searched cells, <tt>-1</tt> for all the dimensions.
  */
  virtual void GetCommonBorderCells( CATCell*           iCell, 
    short              iMaxDepthSearch,
    CATLISTP(CATCell)& ioResultCells,
    short              iResultCellsDimension = -1) = 0;

  /**
    * Retrieves a point belonging to <tt>this</tt> CATCell.
    * @param ioResult
    * The estimated center of <tt>this</tt> CATCell.
  */
  virtual void EstimateCenter(CATMathPoint& ioResult) const = 0;
  
  /**
  * Retrieves the CATCells on which <tt>this</tt> is directly lying on.
  * @param ioSupports
  * The list of the pointers to the supporting cells.
  * @param iInBody
  * The pointer to the body in which the cells are searched. Recall
  * that a same CATCell can be used by several bodies. 
  * If <tt>NULL</tt>, the search is done among all the bodies.
  */
  virtual void         GetLyingOn         (CATLISTP(CATCell)& ioSupports,CATBody* iInBody) = 0;
  
  /**
  * Returns the geometry of <tt>this</tt> as a geometry lying on the geometry of another cell.
  * @param iSupport
  * The pointer to the supporting cell.
  * @return
  * The pointer to the geometry of <tt>this</tt> lying on <tt>iSupport</tt>.
  */
  virtual CATGeometry* GetLyingGeometryOn (CATCell* iSupport) = 0;
  
  /**
  * Tests whether <tt>this</tt> CATCell is lying (directly or indirectly) on another topological object.
  * @param iContainerOfSupportingCell
  * The pointer to another topological object.
  * @param ioSupports
  * The pointer to the list of supporting cells.
  * @param ioGeomSupports
  * The pointer to the list of the geometry of supporting cells.
  * @return
  * The result of the test.
  */
  virtual CATBoolean   IsLyingOn(CATTopology           *iContainerOfSupportingCell, 
                                 CATLISTP(CATCell)     *ioSupports = NULL, 
                                 CATLISTP(CATGeometry) *ioGeomSupports = NULL)    = 0;


  

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  
  /**
  * @nodoc
  * Tests whether <tt>this</tt> CATCell is candidate for report in <tt>CATCGMJournalList</tt> of a Body construction.
  * @param iInBody
  * The pointer to the body construction which contains <tt>this</tt> CATCell.
  * @return
  * The result of the test.
  * <br><b>Legal values</b>:
  * <tt>TRUE</tt>, if <tt>this</tt> CATCell is a face, a free edge or a free vertex inside <tt>iInBody</tt>.
  * <tt>FALSE</tt> if <tt>this</tt> CATCell must not be logged as a new or kept cell.
  */
  virtual CATBoolean IsCandidateForReporting(CATBody* inBody)  =0;

  /**
  * @nodoc
  *  Retrieve the adjacent cell(s) inside the Body
  * @param iInBody
  * The pointer to the body in which the adjacent cells are searched. 
  ** Recall that a same CATCell can be used by several bodies.
  * @param oNeighbourCells
  * The list of the resulting cells. Each cell only occurs once in the list.
  * @return
  *   An HRESULT value. 
  *   <br><b>Legal values</b>:
  *   <dl>
  *     <dt>S_OK</dt>
  *     <dd>The query succeeds.</dd>
  *     <dt>E_FAIL </dt>
  *     <dd>The <tt>inBody</tt> is not valid, or <tt>this</tt> CATCell does not belongs to <tt>iInBody</tt></dd>
  *   </dl>
  */
  virtual HRESULT CellNeighbours( CATBody *inBody, ListPOfCATCell  &oNeighbourCells) =0;

 
  /**
  * @nodoc
  * Returns the list of the pointers to the supporting geometries. 
  * @param iSupport
  * The pointer to the supporting cell.
  * @param ioSupports
  * The list of the pointers to the supporting geometries.
  */
  virtual void GetLyingGeometriesOn(CATCell* iSupport , CATLISTP(CATGeometry)& ioGeomSupports) = 0;

  /**
  * @nodoc
  * Retrieves the federating topology on which <tt>this</tt> is directly lying on.
  * @param iInBody
  * The pointer to the body in which the cells are searched. Recall
  * that a same CATCell can be used by several bodies. 
  * If <tt>NULL</tt>, the search is done among all the bodies.
  * @param ioSupports
  * The list of the pointers to the supporting topologies.
  */
  virtual void  GetFederatorsLyingOn(CATBody* iInBody, CATLISTP(CATTopology) & ioFederatorsSupport) = 0;

  
  /**
  * @nodoc
  */
  virtual void         SetLyingOn         (CATCell* iSupport,CATGeometry* iWithAssociatedGeometry=NULL) = 0;
  /**
  * @nodoc
  */  
  virtual void         UnsetLyingOn       (CATCell* iSupport) = 0;

};
 
CATDeclareHandler(CATCell,CATTopObject);
 
#endif
 
