#ifndef CATICGMTopLineTangentPtCrvOperator_h_
#define CATICGMTopLineTangentPtCrvOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopTangentCurveOperator.h"

class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopLineTangentPtCrvOperator;

/**
 * Class defining a topological operator that computes line bodies tangent to a curve body.
 * This operator follows the general scheme of the topological operators producing several resulting bodies:
 * <ul>
 *<li> Create the operator with the global function <tt>CATCGMCreateTopLnTgtPtCrvOperator</tt>
 *<li> Set the parameters
 *<li> Run
 *<li> Get the resulting bodies (use the iterator on the resulting bodies, because
 * several line bodies can be solution of the computation)
 *<li> Release the operator with the <tt>Release</tt> method.
 *</ul>
 * @see CATICGMTopMultiResult
 */
class ExportedByCATGMOperatorsInterfaces CATICGMTopLineTangentPtCrvOperator: public CATICGMTopTangentCurveOperator
{
public:
  /**
   * Constructor
   */
  CATICGMTopLineTangentPtCrvOperator();

  /**
 * Defines the type of the created geometry.
 * @param iSupport
 * The type of the geometry to create.
 * <br><b>Legal values</b>: <tt>1</tt> if the geometry of the wire is a CATPLine (line on the supporting plane),
 * <tt>0</tt> if it is a CATLine. By default, a CATPline is created.
 */
  virtual void SetSupportMode(CATLONG32 iSupport) = 0;

  /**
 * Returns the type of the created geometry.
 * @param ioSupport
 * The type of the geometry to create.
 * <br><b>Legal values</b>: <tt>1</tt> if the geometry of the wire is a CATPLine (line on the supporting plane),
 * <tt>0</tt> if it is a CATLine.
 */
  virtual void GetSupportMode(CATLONG32 &ioSupport) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopLineTangentPtCrvOperator(); // -> delete can't be called
};

/**
 * Creates a topological operator to compute line bodies tangent to a curve body. 
 * <br> After creating the operator, use the </tt>Setxxx</tt> methods to tune
 * the parameters. Then run it, retrieve the resulting body, and release the operator with <tt>Release</tt>.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. Warning: the 
 * journal of <tt>iTopData</tt> is never filled, because the journal is written for each solution by
 * the parent class of the operator @href CATICGMTopMultiResult .
 * @param iOriginPoint
 * The pointer to the point body, origin of the tangent line bodies to compute.
 * @param iCurve
 * The pointer to the planar curve body to which the resulting line bodies must be tangent.
 * @param iPlane
 * The plane which contains the input and output line bodies.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMTopLineTangentPtCrvOperator *CATCGMCreateTopLnTgtPtCrvOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iOriginPoint,
  CATBody *iCurve,
  CATBody *iPlane);

#endif /* CATICGMTopLineTangentPtCrvOperator_h_ */
