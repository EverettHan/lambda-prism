#ifndef CATIPGMTopRelimitBody_h_
#define CATIPGMTopRelimitBody_h_

// COPYRIGHT DASSAULT SYSTEMES 2017

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATCGMOutput;
class CATCGMStream;
class CATCell;
class CATExtCGMReplay;
class CATExtTopOperator;
class CATGeoFactory;
class CATString;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopRelimitBody;

/**
 * Class defining the operator which relimits a body,  by the given operand.
 * If the operand doesn't intersect the body being relimited, the returned result is the input body.
 * <br>
 * The <tt>CATIPGMTopRelimitBody</tt> operator follows the global frame of the topological operators 
 * and satisfies the smart mechanism: the input bodies are not modified. The resulting body is equal to 
 * the first input body, or is a new created body, possibly sharing data with the input bodies.
 * <ul>
 * <li>A <tt>CATIPGMTopRelimitBody</tt> operator is created with the <tt>CATPGMCreateTopRelimitBody</tt>
 * global function: It must be directly deleted after use with the usual C++ <tt>delete</tt> operator. 
 * It is not streamable. 
 * <li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
 * to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
 * geometry factory. 
 * </ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopRelimitBody: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopRelimitBody();

  /** @nodoc */
  virtual void SetNoSimplif(CATBoolean iNoSimplif) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopRelimitBody(); // -> delete can't be called
};

/**

 * Creates a <tt>CATIPGMTopRelimitBody</tt> operator.
 * @param ipFactory
 * The factory of the geometry. 
 * @param ipTopData
 * The pointer to the data defining the software configuration and the journal. 
 * If the journal inside <tt>ipTopData</tt> is <tt>NULL</tt>, it is not filled.
 * @param iTrimmingBody
 * The pointer to the input body to trim to.
 * @param iRelimitedBody
 * The pointer to the body relimited by the trimming body.
 * @param iSideToKeep
 * The side to keep 
 * <br><b>Legal values</b>:
 * <dl><dt>1</dt><dd> The left side is kept
 * <dt>-1</dt><dd>The right side is kept
 * @return
 * The pointer to the created operator. To delete after use with the usual C++ <tt>delete</tt> operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopRelimitBody *CATPGMCreateTopRelimitBody(
  CATGeoFactory *ipFactory,
  CATTopData *ipTopData,
  CATBody *iTrimmingBody,
  CATBody *iRelimitedBody,
  int iSideToKeep);

#endif /* CATIPGMTopRelimitBody_h_ */
