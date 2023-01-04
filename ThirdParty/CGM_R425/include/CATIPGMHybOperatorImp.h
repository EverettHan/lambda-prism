#ifndef CATIPGMHybOperatorImp_h_
#define CATIPGMHybOperatorImp_h_

// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Protected
 * @usage U2
 */

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMHybOperator.h"

class CATExtHybOperatorImp;
class CATString;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMHybOperatorImp;

/**
* Class defining the operators operating with surfacic and wireframe entities.
*<br>
* These operators operate on the 2D (CATShell), 1D (CATWire) and 0D (CATVertexInVolume)
* domains of a CATBody.
* They follow the global frame of all operator and satisfy to the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
* <li>A CATIPGMHybOperator is created with a global function:
* <ul>
* <li> <tt>CATPGMCreateTopAssemble</tt>: for an operator that assembles CATShell domains or CATWire domains
* <li> <tt>CATCreatTopDisconnect</tt>: for an operator that inserts a vertex in a wire or loop, or an edge in a shell
* <li> <tt>CATCreatTopIntersect</tt>: for an operator that intersects two bodies
* <li> <tt>CATPGMCreateTopSplit</tt>: for an operator that splits a domain by
* another one
* <li> <tt>CATPGMCreateTopTrim</tt>: for an operator that trims a domain by
* another one 
* together
* <li> <tt>CATPGMCreateTopProject</tt>: for an operator that projects a domain on 
* another domain.
* </ul>
* It must be
* directly released with the <tt>Release</tt> methodafter use.
* It is not streamable. 
*<li>Options can be precised with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method. 
*<li>In both cases, the result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
*</ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMHybOperatorImp: public CATIPGMHybOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMHybOperatorImp();

  /**
   * @nodoc
   * Returns a pointer to the resulting CATBody of <tt>this</tt> CATIPGMHybOperator.
   * <br> Must be called after the <tt>Run</tt> method only once. A second call returns a <tt>NULL</tt>
   * pointer.
   * @param iJournal
   * The pointer to the journal that must be filled.
   * @return
   * The pointer to the resulting body. Use @href CATICGMContainer#Remove if you do not want to keep it.
   */
  virtual CATBody *GetResult(CATCGMJournalList *iJournal) = 0;

  /**
   * Returns a pointer to the resulting CATBody of <tt>this</tt> CATIPGMHybOperator.
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

  /** @nodoc  */
  // Non necessaire en R20 CATCGMOperatorDebugDeclareRun(CATIPGMHybOperatorImp,CATCGMOperator);
  // car Run() toujours declare
  virtual int Run() = 0;

  /** @nodoc */
  //   int IsDeprecated() const;
  /** @nodoc */
  virtual void SetCheckReport(short mode = 1) = 0;

  /** @nodoc */
  virtual short GetCheckReport() const = 0;

  /** @nodoc  */
  virtual CATExtHybOperatorImp *GetHybOperatorImpExtensible() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMHybOperatorImp(); // -> delete can't be called
};

#endif /* CATIPGMHybOperatorImp_h_ */
