#ifndef CATVertex_H
#define CATVertex_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATCell.h"    

class CATEdge;
class CATFace;
class CATPoint;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATPCurve;
class CATCrvParam;
class CATVertexIterator;
#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATVertex ;
#else
extern "C" const IID IID_CATVertex ;
#endif

/**
 * Interface representing a topological vertex. 
 *<br>A vertex is a topological cell which geometry is a
 * point. Vertices are used to define the extremities of an edge, but they can also
 * be immersed in faces, volumes or 3D space.
 * <br>A vertex is created with the @href CATBody#CreateCell or @href CATBody#CreateVertex methods and
 * deleted with the @href CATICGMContainer#Remove method.
 */ 
class ExportedByCATGMModelInterfaces CATVertex : public CATCell
{
  
  CATDeclareInterface;
  
  public :
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  
/**
 * Sets a the geometry of <tt>this</tt> CATVertex.
 * @param iPoint
 * The pointer to the geometric point. This point must be a CATMacroPoint.
 */
  virtual void       SetPoint( CATPoint * iPoint )=0;

/**
 * Returns the geometry of <tt>this</tt> CATVertex.
 * @return
 * The pointer to the geometric point.
 */
  virtual CATPoint * GetPoint()=0;
  
  
/**
 * Returns the geometry of <tt>this</tt> CATVertex with respect to a given edge.
 * @param iBoundedEdge
 * The pointer to an edge bounded by <tt>this</tt>.
 * @param iSide 
 * The start or end point of the edge. If you do not specify the CATSide,
 * this method raises an exception if <tt>iBoundedEdge</tt> start and end
 * vertices are the same.
 * @return
 * The pointer to the corresponding geometry.
 */
  virtual CATPointOnEdgeCurve * GetGeometryOnEdge(CATEdge * iBoundedEdge,
                                                  const CATSide& iSide = CATSideUnknown)=0;

/**
 * Returns the geometry of <tt>this</tt> CATVertex with respect to a given edge as a
 * parameter on a CATEdgeCurve.
 * @param iBoundedEdge
 * The pointer to an edge bounded by <tt>this</tt>.
 * @param oEdgeCurve
 * The pointer to the edge curve, geometry of <tt>iBoundedEdge</tt>.
 * @param ioParamOnEdgeCurve
 * The parameter on <tt>iBoundedEdge</tt> of <tt>this</tt>.
 * @param iSide
 * The start or end point of the edge. If you do not specify the CATSide,
 * this method raises an exception if <tt>iBoundedEdge</tt> start and end
 * vertices are the same.
 */
  virtual void GetParamOnEdgeCurve(CATEdge *      iBoundedEdge,
				   CATEdgeCurve*& oEdgeCurve,
				   CATCrvParam&   ioParamOnEdgeCurve,
				   const CATSide& iSide = CATSideUnknown)=0;
  
  
/**
 * Sets the geometry of <tt>this</tt> CATVertex with respect to a given edge.
 * @param iBoundedEdge
 * The pointer to an edge bounded by <tt>this</tt>.
 * @param iSide
 * The start or end point of the edge. 
 * @param iPtOnCrv
 * The pointer to the geometry of the vertex, as bounding <tt>iBoundedEdge</tt>.
 */
  virtual void SetGeometryOnEdge(CATEdge *            iBoundedEdge,
                                 const CATSide&       iSide,
				 CATPointOnEdgeCurve* iPtOnCrv)=0;

 /**
 * Creates an iterator on the CATEdge bounded by <tt>this</tt> CATVertex.
 * @param iInBody
 * The pointer to the body in which the bounded edges are searched.
 * @param iTopData
 * The object defining the CATSoftwareConfiguration and the CATCGMJournalList.
 * @return
 * The pointer to the created iterator. You must <tt>delete</tt> this operator after use. 
 */
    virtual CATVertexIterator * CreateRadialIterator(CATBody *iInBody, const CATTopData * iData = 0)=0;

  /**
  * Removes useless components from the CATMacroPoint.
  * <br>Only points with no more topological links will be detached from the CATMacroPoint.
  * @param iSpecificPoint
  * The specific point to analyze. If <tt>NULL</tt>, all components of the CATMacroPoint
  * are taken into account.
  * @param iRemoveFromFactory
  * The complementary action on an useless component of CATMacroPoint.
  * Dedicated to the case where no more links inside the CATGeoFactory refers to <tt>iSpecificPoint</tt>.
  * <br><b>Legal values</b>:
  * <dl><dt><tt>FALSE</tt></dt><dd> <tt>iSpecificPoint</tt> point remains in the factory
  *     <dt><tt>TRUE</tt></dt><dd> <tt>iSpecificPoint</tt> point is removed from the factory with its dependancies.</dl>
  */
  
  virtual void UnlinkUselessGeometry( CATPoint   *iSpecificPoint     = NULL,
                                      CATBoolean  iRemoveFromFactory = TRUE ) = 0;


  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


/**
 * @nodoc
 * Do not use.
 */
  virtual void GetGeometryOnEdgeAndFace(CATEdge * iBoundedEdge,
                                        CATFace * iBoundedFace,
                                        CATPCurve*&  oPCurve,
                                        CATCrvParam& oParam)=0;
/**
 * Returns the continuity of <tt>this</tt> CATVertex with respect to 2 bounded edges.
 * @param iEdge1
 * The first edge bounded by <tt>this</tt>.
 * @param iEdge2
 * The second edge bounded by <tt>this</tt>.
 * @param oContinuity
 * The evaluated continuity :
 * <br><b>Possible values</b>:
 * <dl><dt><tt> CATSharp </tt></dt><dd>
 *     <dt><tt> CATSmooth </tt></dt><dd>
 * @param oAngle
 * Used to ouput the angle between the two edges.
 * If <tt>NULL</tt>, this argument is not filled out.
 * @param oOrientation
 * Used to ouput the correct orientation of the second edge.
 * If <tt>NULL</tt>, this argument is not filled out.
 * @param oDefinedContinuity
 * The way the continuity has been filled out (stored or computed).
 * <br><b>Legal values</b>:
 * <dl><dt><tt> TRUE </tt></dt><dd>if <tt>SetContinuity</tt> has been previously applied.
 *     <dt><tt> FALSE </tt></dt><dd> geometric evaluation of continuity.</dl> 
 * If <tt>NULL</tt>, this argument is not filled out.
 * @param iMinSharpAngle
 * Minimum angle value for which the vertex is declared Sharp
 */
 virtual void  EvalSharpness (CATEdge              *iEdge1,
                              CATEdge              *iEdge2,
                              CATTopGeoContinuity  &oContinuity,
                              CATAngle             *oAngle = NULL,
                              CATTopSign           *oOrientation = NULL,
                              CATBoolean           *oDefinedContinuity = NULL,
                              CATAngle             iMinSharpAngle = CATTopSharpAngle) = 0;

/**
 * Defines the continuity of <tt>this</tt> CATVertex with respect to 2 bounded edges.
 * @param iEdge1
 * The first edge bounded by <tt>this</tt>.
 * @param iEdge2
 * The second edge bounded by <tt>this</tt>.
 * @param iContinuity
 * The tangential continuity.
 * <br><b>Legal values</b>:
 * <dl><dt><tt> CATSharp </tt></dt><dd>
 *     <dt><tt> CATSmooth </tt></dt><dd>
 * @param iMinSharpAngle
 * Minimum angle value for which the vertex is declared Sharp
 */     
 virtual void  SetSharpness (CATEdge              *iEdge1,
                             CATEdge              *iEdge2,
                             CATTopGeoContinuity  iContinuity,
                             CATAngle             iMinSharpAngle = CATTopSharpAngle) = 0;


};

CATDeclareHandler(CATVertex,CATCell);

#endif // CATVertex_H
