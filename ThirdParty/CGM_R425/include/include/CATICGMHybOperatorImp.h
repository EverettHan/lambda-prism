#ifndef CATICGMHybOperatorImp_h_
#define CATICGMHybOperatorImp_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMHybOperator.h"

class CATExtHybOperatorImp;
class CATString;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMHybOperatorImp;

/**
* Class defining the operators operating with surfacic and wireframe entities.
*<br>
* These operators operate on the 2D (CATShell), 1D (CATWire) and 0D (CATVertexInVolume)
* domains of a CATBody.
* They follow the global frame of all operator and satisfy to the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
* <li>A CATICGMHybOperator is created with a global function:
* <ul>
* <li> <tt>CATCGMCreateTopAssemble</tt>: for an operator that assembles CATShell domains or CATWire domains
* <li> <tt>CATCGMCreatTopDisconnect</tt>: for an operator that inserts a vertex in a wire or loop, or an edge in a shell
* <li> <tt>CATCGMCreatTopIntersect</tt>: for an operator that intersects two bodies
* <li> <tt>CATCGMCreateTopSplit</tt>: for an operator that splits a domain by
* another one
* <li> <tt>CATCGMCreateTopTrim</tt>: for an operator that trims a domain by
* another one 
* together
* <li> <tt>CATCGMCreateTopProject</tt>: for an operator that projects a domain on 
* another domain.
* </ul>
* It must be
* directly released with the <tt>Release</tt> method after use.
* It is not streamable. 
*<li>Options can be precised with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method. 
*<li>In both cases, the result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
*</ul>
*/
class ExportedByCATGMOperatorsInterfaces CATICGMHybOperatorImp: public CATICGMHybOperator
{
public:
  /**
   * Constructor
   */
  CATICGMHybOperatorImp();

  /**
   * Returns a pointer to the resulting CATBody of <tt>this</tt> CATICGMHybOperator.
   * <br> Must be called after the <tt>Run</tt> method only once. A second call returns a <tt>NULL</tt>
   * pointer.
   * @return
   * The pointer to the resulting body. Use @href CATICGMContainer#Remove if you do not want to keep it.
   */
  virtual CATBody *GetResult() = 0;

  /** 
   * Defines the tolerance of the geometrically coincident elements to be taken 
   * into acccount by <tt>this</tt> operator.
   * <br>Very sensitive point. The default value is the factory resolution, 
   * and it is strongly recommended to keep it.
   * @param iTol
   * The tolerance.
   */
  virtual void SetTolerance(double iTol) = 0;

  /** 
   * Returns the tolerance of the geometrically coincident elements to be taken 
   * into acccount by <tt>this</tt> operator.
   * @return
   * The tolerance.
   */
  virtual double GetTolerance() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMHybOperatorImp(); // -> delete can't be called
};

#endif /* CATICGMHybOperatorImp_h_ */
