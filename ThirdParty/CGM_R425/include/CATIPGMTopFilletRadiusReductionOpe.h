#ifndef CATIPGMTopFilletRadiusReductionOpe_h_
#define CATIPGMTopFilletRadiusReductionOpe_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATMathDef.h"

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopFilletRadiusReductionOpe;

//=============================================================================
// Copyright Dassault Systemes Provence 2007, all rights reserved
//=============================================================================
/**
 * Class defining the operator to reduce the radius of a given input body shell fillet.
 * <br>
 * This operator follows the general scheme of the topological operators. User should:
 * <ul>
 *<li> Create the operator with the <tt>CATPGMCreateTopFilletRadiusReductionOpe</tt>
 * global function, which defines the fillet to treat.
 *<li> Run the operator with the <tt>Run</tt> method. In case of any failing treatment, the <tt>Run</tt>
 * method returns an integer error status different from 0:
 *  <ul><li>0 : Correct treatment.
 *      <li>1 : Invalid input body shell (NULL pointer, empty shell, more than one shell).
 *      <li>2 : Invalid input body wire 1 (same diagnostics as for the body shell).
 *      <li>3 : Invalid input body wire 2 (same diagnostics as for the body shell).
 *      <li>n : ...
 *      <li>10 : Unidentified internal software error in the treatment.
 *  </ul>
 *<li> Get the result body with the <tt>GetResult</tt> method.
 *<li> Delete the operator with the usual C++ <tt>delete</tt> operator.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopFilletRadiusReductionOpe: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopFilletRadiusReductionOpe();

  /**
  * Defines the radius of the reduced fillet to generate.
  * @param iTargetRadius
  * The target radius value is set by default to 85% of the radius of the input fillet to reduce.
  */
  virtual void SetTargetRadius(CATLength iTargetRadius) = 0;

  /**
  * Get a more expansed Error message  if run failed
  * The returned Error could be NULL if no Error has been detected
  * The Caller must managed the Error lifecycle and delete it
  */
  virtual void GetError(CATError *&Error) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopFilletRadiusReductionOpe(); // -> delete can't be called
};

//
// creation of operator (ADVANCED mode)
//-------------------------------------
/*
* Creates a topological operator to reduce the radius of a given input body shell fillet. The geometry
* of the fillet faces  may be of any CATSurface type. But the operator checks that the geometry
* corresponds to a fillet (transverse iso-parameters must be of constant curvature, ...).
* @param iFactory
* The factory that creates the resulting body.
* @param iTopData
* The pointer to the data defining the configuration and the journal. If the journal inside
* <tt>iTopData</tt> is <tt>NULL</tt>, it is not filled. 
* @param iShellBody
* The pointer to the shell body fillet to reduce.
* @param iWireBody1
* The pointer to the 1st wire body corresponding to a fillet path/rail. 
* @param iWireBody2
* The pointer to the 2nd wire body corresponding to a fillet path/rail. 
* @param iOriginalRadius
* The radius of the input fillet.
* @return [out, IUnknown#Release]
* The pointer to the created operator.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopFilletRadiusReductionOpe *CATPGMCreateTopFilletRadiusReductionOpe(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iShellBody,
  CATBody *iWireBody1,
  CATBody *iWireBody2,
  CATLength iOriginalRadius);

#endif /* CATIPGMTopFilletRadiusReductionOpe_h_ */
