#ifndef CATIPGMCloseOperator_h_
#define CATIPGMCloseOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @level Protected
 * @usage U3
 */

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATDynOperatorDef.h"

class CATBody;
class CATCGMJournalList;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMCloseOperator;


/**
 * Class representing the operator that closes a skin body.
 * If the body is a closed shell (set of faces), it simply creates a volume body out of it. 
 * If it is an open shell, it will try to close it with as many planar faces as possible.
 * <br>The close operator can not create new edges. For instance, trying to
 * close a half-cylinder surface face will fail, because, even if it may
 * be closed by three planes, two new edges need to be created (at the
 * intersection of those planes).
 * <br>To use it:
 *<ul>
 * <li>Create it with the <tt>CATPGMCreateCloseOperator</tt> global function.
 * <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. 
 * <li>Run it
 * <li>Get the resulting GetResult method. If you do not want 
 * to keep these resulting body, use the @href CATICGMContainer#Remove method to remove them from the 
 * geometric factory, after the operator deletion.
 *<li>Release the operator with the <tt>Release</tt> method after use.
 *</ul> 
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMCloseOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMCloseOperator();

  /** 
   * Asks for a boolean operation with the output of the operator
   * (the so called closed skin) and <tt>iOperandBody</tt>.
   * @param iReport
   * The pointer to the journal to fill, if not <tt>NULL</tt>.
   * It can be different from the operator journal given in CATTopData.
  */
  virtual void SetBooleanOperation(
    CATDynBooleanType iOpType,
    CATBody *iOperandBody,
    CATCGMJournalList *iReport = 0) = 0;

  /**
   * Runs the operator.
   * @return
   * <br><b>Legal values</b>: <tt>0</tt> if ok, <tt>1</tt> if failed
   */
  virtual int Run() = 0;

  /**
   * Returns the resulting body of the closure operation.
   * @return
   * The pointer to the created body.If you do not want 
   * to keep these resulting body, use the @href CATICGMContainer#Remove method to remove them from the 
   * geometric factory, after the operator deletion.
   */
  virtual CATBody *GetResult() = 0;

  /**
	 * Returns the body created from the Boolean operation between a given body and the thickened body.
	 * @return
	 * The pointer to the Boolean result.
	 * If you do not want to keep the resulting body, 
     * use the @href CATICGMContainer#Remove method to remove it from the 
     * geometric factory, after the operator deletion.
	 */
  virtual CATBody *GetBooleanResult() = 0;

  // Set a tolerance for closing plane creation, and curve merge. This
  // tolerance may not be smaller than modeler resolution, which is the
  // default value.
  /**  @nodoc */
  virtual void SetTolerance(double iTolerance) = 0;

  /** 
   * Give the list of input profile bodies used for input body generation
   * This service is usefull in case of Loft operation to retrieve underlying plane of body
   * ( topological model and size simplification )
   * Special mode available to search for any type of closing surface under profiles edges
   * (restricted use)
  */
  /**  @nodoc */
  virtual void SetInputProfileBodiesList(
    CATLISTP(CATBody) &iInputProfileBodiesList,
    int iSearchForAnyTypeOfSurface = 0) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMCloseOperator(); // -> delete can't be called
};

/**
 * Creates an operator that closes a skin body.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iBodyToClose
 * The pointer to the skin body to close.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMCloseOperator *CATPGMCreateCloseOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBodyToClose);

/** @nodoc
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMCloseOperator *CATPGMCreateCloseOperator(
  CATGeoFactory *iFactory,
  CATBody *iBodyToClose,
  CATCGMJournalList *iReport = 0);

/** @nodoc
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMCloseOperator *CATPGMCreateCloseOperator(
  CATGeoFactory *iFactory,
  CATBody *iBodyToClose,
  CATTopData *iTopData);

#endif /* CATIPGMCloseOperator_h_ */
