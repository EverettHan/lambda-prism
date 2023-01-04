#ifndef CATIPGMTopVertex_h_
#define CATIPGMTopVertex_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMGeoToTopOperator.h"

class CATBody;
class CATCGMJournalList;
class CATDomain;
class CATGeoFactory;
class CATLoop;
class CATPoint;
class CATSurface;
class CATVertex;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopVertex;

/** 
* Class representing the operator that creates a point body from one point. 
* <br>To use the CATIPGMTopVertex:
* <ul><li>Create it with the <tt>CATPGMCreateTopVertex</tt> global function. 
* <li>If needed, tune some parameters with the <tt>SetXxx</tt> methods.
* <li> <tt>Run</tt> the operator
* <li>Retrieve the created body (frozen by default) with the <tt>GetResult</tt> method. 
* <li>Release the operator with the <tt>Release</tt> method after use.
* </ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMTopVertex: public CATIPGMGeoToTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopVertex();

  /**
 * Runs <tt>this</tt> operator.
 */
  virtual int Run() = 0;

  /**
 * Returns the pointer to the vertex of the resulting point body.
 * @return
 * The pointer to the vertex of the resulting point body. Remember that the whole body is retrieved with
 * the <tt>GetResult</tt> method, and you must manage its deletion if you do not want to keep it.
 */
  virtual CATVertex *GetVertex() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopVertex(); // -> delete can't be called
};

/**
 * Creates an operator to build a point body from one point.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iPoint
 * The pointer to the point used to define the vertex.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopVertex *CATPGMCreateTopVertex(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATPoint *iPoint);

/** @nodoc */
ExportedByCATGMOperatorsInterfaces CATBody *CATPGMCreateVertex(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATPoint *iPoint);

/**
 * Ascending compatibility for client frameworks.
 */
inline CATBody *CATCGMCreateVertex(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATPoint *iPoint)
{
  return CATPGMCreateVertex(iFactory, iData, iPoint);
}

#endif /* CATIPGMTopVertex_h_ */
