#ifndef CATICGMTopExtrapolWireOpe_h_
#define CATICGMTopExtrapolWireOpe_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"

class CATBody;
class CATVertex;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopExtrapolWireOpe;

/**
* Class defining the topological operator to extrapol a wire.
* <br>
* The operator produces a wire topology result of the extrapolation of the input wire.
* The user can customize the extrapolation with the Setxxx methods to
*<ul>
* <li> define the type of continuity : tangency or curvature. 
* <li> define the extremity from which the extrapolation starts.
* <li> define the length of extrapolation or the body to reach.
*</ul>
* <p>
* When no support is defined, 
* the extrapolation in curvature "up to" is only possible if the body to reach is a wire and a plane; 
* the extrapolation in curvature of a given length is the extrapolated wire relimited by the plane
* created at the given length from the chosen extremity.
* When a support is defined, 
* the extrapolation in curvature is only possible on the faces with same geometry. 
*</p>
* This operator follows the general scheme of the topological operators:
* <ul>
*<li> Create the operator with the <tt>CATCGMCreateTopExtrapolWireOpe</tt> global function.
*<li> Set the extrapolation parameters: continuity, extremity, length...
*<li> Run with the <tt>Run</tt> method. 
*<li> Get the result body by the <tt>GetResult</tt> method. 
*<li> Release the operator with the <tt>Release</tt> method after use.
*</ul>
*/
class ExportedByCATGMOperatorsInterfaces CATICGMTopExtrapolWireOpe: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMTopExtrapolWireOpe();

  /**
  * Defines the type of continuity.
  * @param type
  * 1 for tangency continuity
  * 2 for curvature continuity. 
  */
  virtual void SetContinuityType(int type) = 0;

  /**
  * Defines the extremity from which the extrapolation must start and the length of the extrapolation.
  * @param iVertex
  * The vertex must be one of the two extremities of the wire to extrapolate. 
  * The extrapolation is only possible from one vertex.
  * @param ilength
  * The length must be a positive value.
  */
  virtual void SetExtrapolLimit(CATVertex *iVertex, double ilength) = 0;

  /**
  * Defines the extremity from which extrapolation must start and the body to reach.
  * @param iVertex
  * The vertex must be one of the two extremities of the wire to extrapolate. 
  * The extrapolation is only possible from one vertex.
  * @param iLimBody
  * The body to reach can be:
  * <ul>
  *   <li> a wire (laid on the same support than the body to extrapol)
  *   <li> a shell (must be plane when extrapolation in curvature mode and no support defined).
  * </ul>
  */
  virtual void SetExtrapolLimit(CATVertex *iVertex, CATBody *iLimBody) = 0;

  /**
  * Runs <tt>this</tt> operator. Returns 0 if the operation completes properly.
  */
  virtual int Run() = 0;

  /**
  * Returns the result of <tt>this</tt> operator.
  * @return
  * The pointer to the created body. 
  */
  virtual CATBody *GetResult() = 0;

  /**
  * Returns the pointer to the resulting body.
  * The pointer to the journal of the operation.
  * @param iJourn
  * The pointer to the journal to fill.
  * @return
  * The pointer to the resulting body. 
  */
  virtual CATBody *GetResult(CATCGMJournalList *iJourn) = 0;

  /**
  * By default the result of the extrapolation of a line in tangency 
  * when no support is defined gives a body which only contains one edge.
  * The intermediate vertex has been cleaned.
  * To avoid this behaviour and keep the vertex use the following option.
  */
  virtual void SetNoSimplifOnLine() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopExtrapolWireOpe(); // -> delete can't be called
};

#endif /* CATICGMTopExtrapolWireOpe_h_ */
