#ifndef CATICGMTopCrvToNurbsCrvOperator_h_
#define CATICGMTopCrvToNurbsCrvOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATDataType.h"

class CATCell;
class CATEdge;
class CATGeometry;
class CATSurface;
class CATTopData;
class CATLISTP(CATEdge);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopCrvToNurbsCrvOperator;

/**
* Class defining a topological operator that converts the geometry of an edge into a NURBS curve.
* This operator follows the general scheme of the topological operators
* <ul>
*<li> Create the operator with the global function <tt>CATCGMCreateTopCrvToNurbsCrvOperator</tt>, which defines
* the edge to transform using a wire body
*<li> Set the parameters
*<li> Run
*<li> Get the resulting body
*<li> Release the operator with the <tt>Release</tt> method.
*</ul>
*/
class ExportedByCATGMOperatorsInterfaces CATICGMTopCrvToNurbsCrvOperator: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMTopCrvToNurbsCrvOperator();

  //
  // ADVANCED mode settings
  //-----------------------
  //
  // The following setting methods follow the creation of a CATICGMTopCrvToNurbsCrvOperator,
  // (see CATCGMCreateTopCrvToNurbsCrvOperator global function)
  //
   /**
  * Defines the fitting tolerance.
  * @param iTolerance
  * The tolerance value. By default, set to the factory resolution.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 SetTolerance(double iTolerance) = 0;

  /**
  * Defines the maximum degree for the created NURBS.
  * @param iMaxDegree
  * The maximum degree allowed for the created NURBS curve.
  * In case of both <tt>SetMaxDegree</tt> and <tt>SetMaxArcs</tt> methods are used, the
  * priority is given to the maximum degree.
  * Default value is 5.
  * @return
  * Not null in case of error. 
  */
  virtual CATLONG32 SetMaxDegree(CATLONG32 iMaxDegree) = 0;

  /**
  * Defines the maximum number of arcs allowed for the NURBS curve.
  * @param iMaxArcs
  * The maximum number of arcs allowed for the NURBS curve.
  * In case of both <tt>SetMaxDegree</tt> and <tt>SetMaxArcs</tt> methods are used, 
  * the priority is given to the maximum degree.
  * Default value is 3.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 SetMaxArcs(CATLONG32 iMaxArcs) = 0;

  /**
  * Defines whether the resulting curve must be defined as a PCurve or not.
  * @param iOutputDimension
  * The dimension of the output curve.
  * <br><b>Legal values</b>: <tt>TRUE</tt> to force the created curve to be a NURBS curve (and not a PNurbsCurve), 
  * <tt>FALSE</tt> (default value) to force the created curve to be a PNurbs curve. 
  * If the resulting curve must be PCurve, a surface must be defined using the <tt>SetSurface</tt> method.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 Set3DOutputDimension(CATBoolean i3DOutputDimension) = 0;

  /**
  * Defines the underlying surface on which the PCurves must be computed.
  * <br>In case of <tt>iOutputDimension = FALSE</tt> in the <tt>Set3DOutputDimension</tt> method.
  * @param iSurface
  * The pointer to the surface.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 SetSurface(CATSurface *iSurface) = 0;

  /**
  * Defines whether the resulting curve is rational. 
  * @param iRationalAbility
  * <br><b>Legal values</b>:
  * <tt>0</tt> to convert the curve to a non rational curve, <tt>1</tt>
  * to convert the curve to a rational curve.
  * Some canonic curves are transformed into rational CATNurbsCurve,
  * but setting <tt>iRationalAbility = 0</tt> forces the conversion to a non rational curve.
  * The default mode is the conversion into rational (equivalent to <tt>iRationalAbility = 1</tt>).
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 SetRationalAbility(CATLONG32 iRationalAbility) = 0;

  /**
  * Retrieves whether the created curve has been approximated.
  * <br>To be called after the <tt>Run</tt> method.
  * @param ioIsExact
  * <tt>0</tt> if there is an approximation, not null otherwise.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 IsExactTransformation(CATLONG32 &ioIsExact) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopCrvToNurbsCrvOperator(); // -> delete can't be called
};

//
// creation of operator (ADVANCED mode)
//-------------------------------------
/**
* Creates a topological operator to converts the geometry of an edge into a NURBS curve.
* @param iFactory
* The pointer to the factory that creates the resulting body.
* @param iTopData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iWireBody
* The pointer to the wire that contains the edge <tt>iEdgeCell</tt>.
* @param iEdgeCell
* The edge whose curve will be transformed into a NURBS curve.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMTopCrvToNurbsCrvOperator *CATCGMCreateTopCrvToNurbsCrvOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iWireBody,
  CATCell *iEdgeCell);

/**
* Creates a topological operator to convert the geometry of an edge into a NURBS curve.
* @param iFactory
* The pointer to the factory that creates the resulting body.
* @param iTopData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
* is <tt>NULL</tt>, it is not filled.
* @param iWireBody
* The pointer to the wire that contains the edges <tt>iEdgeList</tt>.
* @param iEdgeList
* The list of edges whose curve will be transformed into a NURBS curve.
* Notice that all the edges must belong to the wire.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMTopCrvToNurbsCrvOperator *CATCGMCreateTopCrvToNurbsCrvOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iWireBody,
  CATLISTP(CATEdge) *iEdgeList);

#endif /* CATICGMTopCrvToNurbsCrvOperator_h_ */
