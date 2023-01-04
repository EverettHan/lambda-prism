#ifndef CATIPGMTopCrvToNurbsCrvOperatorProtected_h_
#define CATIPGMTopCrvToNurbsCrvOperatorProtected_h_

// COPYRIGHT DASSAULT SYSTEMES 2020

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopCrvToNurbsCrvOperator.h"

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopCrvToNurbsCrvOperatorProtected;

class ExportedByCATGMOperatorsInterfaces CATIPGMTopCrvToNurbsCrvOperatorProtected: public CATIPGMTopCrvToNurbsCrvOperator
{
public:

  /**
   * Constructor
   */
  CATIPGMTopCrvToNurbsCrvOperatorProtected();

  //
  // ADVANCED mode settings
  //-----------------------
  //
  // The following setting methods follow the creation of a CATIPGMTopCrvToNurbsCrvOperator,
  // (see CATPGMCreateTopCrvToNurbsCrvOperator global function)
  //
  /**
  * Defines the parametrization option.
  * @param iOtionOfParametrization
  * The option value. By default, set to the 0 .
  *   = 0 The Parametrization is not changed
  *   = 1 The resulting parametization is curvilinear (Only for modified curves)
  *   = 2 The resulting parametrization can be changed by the operator ( depending of degre or other parmeter)
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 SetParametrizationOption(CATLONG32 iOtionOfParametrization) = 0;


  /**
  * Retrieves whether the created curve has been approximated for a list of curves.
  * <br>To be called after the <tt>Run</tt> method.
  * @param ioIsExactList
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 IsExactTransformationForEdgeList(CATListOfInt& ioIsExactList) = 0;

  /**
  * Retrieves max deviation for edges for a list of edges.
  * <br>To be called after the <tt>Run</tt> method.
  * @param ioDeviations
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 GetDeviationsForEdgeList(CATListOfDouble& ioDeviations) = 0;


protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopCrvToNurbsCrvOperatorProtected(); // -> delete can't be called
};









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
ExportedByCATGMOperatorsInterfaces CATIPGMTopCrvToNurbsCrvOperatorProtected* CATPGMCreateTopCrvToNurbsCrvOperatorProtected(
	CATGeoFactory* iFactory,
	CATTopData* iTopData,
	CATBody* iWireBody,
	CATCell* iEdgeCell);

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
ExportedByCATGMOperatorsInterfaces CATIPGMTopCrvToNurbsCrvOperatorProtected* CATPGMCreateTopCrvToNurbsCrvOperatorProtected(
	CATGeoFactory* iFactory,
	CATTopData* iTopData,
	CATBody* iWireBody,
	CATLISTP(CATEdge)* iEdgeList);










#endif /* CATIPGMTopCrvToNurbsCrvOperatorProtected_h_ */
