#ifndef CATIPGMVertexOperator_h_
#define CATIPGMVertexOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopVertex.h"

class CATBody;
class CATCGMJournalList;
class CATDomain;
class CATGeoFactory;
class CATLoop;
class CATPoint;
class CATSurface;
class CATVertex;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMVertexOperator;

/** 
 * Deprecated. Use now @href CATIPGMTopPointOperator .
* Class representing the operator that creates a point body from one point. 
* <br>To use the CATIPGMVertexOperator:
* <ul><li>Create it with the available constructor. 
* <li>If needed, tune some parameters with the <tt>SetXxx</tt> methods.
* <li> <tt>Run</tt> the operator
* <li>Retrieve the created body (frozen by default) with the <tt>GetResult</tt> method. 
* <li>Release the operator with the <tt>Release</tt> method after use.
* </ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMVertexOperator: public CATIPGMTopVertex
{
public:
  /**
   * Constructor
   */
  CATIPGMVertexOperator();

  /**
 * Runs <tt>this</tt> operator.
 */
  virtual int Run() = 0;

  /**
	* Returns the pointer to the vertex of the resulting body.
	* @return
	* The pointer to the vertex of the resulting body. Remember that the whole body is retrieved with
	* the <tt>GetResult</tt> method, and you must manage its deletion if you do not want to keep it.
	*/
  virtual CATVertex *GetVertex() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMVertexOperator(); // -> delete can't be called
};

/**
	* Creates an operator to build a point body from one point.
	* @param iFactory
	* The pointer to the factory of the geometry.
	* @param iPoint
	* The pointer to the point used to define the vertex.
 * @return [out, IUnknown#Release]
	*/
ExportedByCATGMOperatorsInterfaces CATIPGMVertexOperator *CATPGMCreateVertexOperator(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATPoint *iPoint);

/** @nodoc
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMVertexOperator *CATPGMCreateVertexOperator(
  CATGeoFactory *iFactory,
  CATPoint *iPoint,
  CATBody *iTargetBody = NULL,
  CATBodyFreezeMode iBodyfreezemode = CATBodyFreezeOn,
  CATCGMJournalList *iReport = NULL);

#endif /* CATIPGMVertexOperator_h_ */
