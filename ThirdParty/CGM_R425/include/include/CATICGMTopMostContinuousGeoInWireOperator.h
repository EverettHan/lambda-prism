#ifndef CATICGMTopMostContinuousGeoInWireOperator_h_
#define CATICGMTopMostContinuousGeoInWireOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"

class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopMostContinuousGeoInWireOperator;

/**
 * Class defining the operator to recover the most continuous geometry of a body wire.
 * <br>
 * This operator follows the general scheme of the topological operators. User should:
 * <ul>
 *<li> Create the operator with the <tt>CATCGMCreateTopMostContinuousGeoInWireOperator</tt>
 * global function, which defines the wire to treat.
 *<li> Run the operator with the <tt>Run</tt> method. In case of any failing treatment, the <tt>Run</tt>
 * method returns an integer error status different from 0:
 *  <ul><li>0 : Correct treatment.
 *      <li>1 : Invalid input body wire (NULL pointer, empty wire, more than one wire).
 *      <li>2 : Invalid input body shell (same diagnostics as for the body wire).
 *      <li>3 : Result body wire has been calculated, but its check has failed.
 *      <li>4 : Result body wire has been calculated, but its check has detected discontinuities in it.
 *      <li>10 : Unidentified internal software error in the treatment.
 *  </ul>
 *<li> Get the result body with the <tt>GetResult</tt> method.
 * In case of a NOT NULL error status from the <tt>Run</tt> method, the result body is the input body.
 *<li> Release the operator with the <tt>Release</tt> method.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATICGMTopMostContinuousGeoInWireOperator: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMTopMostContinuousGeoInWireOperator();

  /**
  * Do not use.
  */
  virtual int GetDump(
    double &oMaxDefG0,
    double &oMaxDefG1,
    double &oMaxDefG2,
    double &oMaxGapG0) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopMostContinuousGeoInWireOperator(); // -> delete can't be called
};

//
// creation of operator (ADVANCED mode)
//-------------------------------------
/**
* Creates a topological operator to recover the most continuous geometry of a body mono-wire,
* the geometry of which is defined on ONE body shell. Concrete case example : Projection
* @param iFactory
* The factory that creates the resulting body.
* @param iTopData
* The pointer to the data defining the configuration and the journal. If the journal inside
* <tt>iTopData</tt> is <tt>NULL</tt>, it is not filled. 
* @param iWireBody
* The pointer to the wire body to treat.
* @param iShellBody
* The pointer to the shell body where the wire geometry is defined.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMTopMostContinuousGeoInWireOperator *CATCGMCreateTopMostContinuousGeoInWireOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iWireBody,
  CATBody *iShellBody);

/**
* Creates a topological operator to recover the most continuous geometry of a body mono-wire,
* the geometry of which is defined on TWO body shells. Concrete case example : Intersection
* @param iFactory
* The factory that creates the resulting body.
* @param iTopData
* The pointer to the data defining the configuration and the journal. If the journal inside
* <tt>iTopData</tt> is <tt>NULL</tt>, it is not filled. 
* @param iWireBody
* The pointer to the wire body to treat.
* @param iShellBody1
* The pointer to the 1st shell body where the former part of the wire geometry is defined.
* @param iShellBody2
* The pointer to the 2nd shell body where the latter part of the wire geometry is defined.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMTopMostContinuousGeoInWireOperator *CATCGMCreateTopMostContinuousGeoInWireOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iWireBody,
  CATBody *iShellBody1,
  CATBody *iShellBody2);

/**
* Do not use.
* @return [out, IUnknown#Release]
*/
ExportedByCATGMOperatorsInterfaces CATICGMTopMostContinuousGeoInWireOperator *CATCGMCreateTopMostContinuousGeoInWireOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iWireBody);

#endif /* CATICGMTopMostContinuousGeoInWireOperator_h_ */
