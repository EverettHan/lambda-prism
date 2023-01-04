#ifndef CATIPGMTopFRRRailsExtractorOpe_h_
#define CATIPGMTopFRRRailsExtractorOpe_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

#include "CATMathDef.h"

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopFRRRailsExtractorOpe;

//=============================================================================
// Copyright Dassault Systemes Provence 2007, all rights reserved
//=============================================================================
/**
 * Class defining the operator to extract the two Rails needed for Fillet Radius Reduction.
 * <br>
 * This operator follows the general scheme of the topological operators. User should:
 * <ul>
 *<li> Create the operator with the <tt>CATPGMCreateTopFRRRailsExtractorOpe</tt>
 * global function, which defines the shell to treat.
 *<li> Run the operator with the <tt>Run</tt> method. In case of any failing treatment, the <tt>Run</tt>
 * method returns an integer error status different from 0:
 *
 *<li> Get the result body with the <tt>GetResult</tt> method.
 * The result Body should Contain Two domains which you explode in 2 Body.
 * In case of a NOT NULL error status from the <tt>Run</tt> method, the result body is the input body.
 *<li> Delete the operator with the usual C++ <tt>delete</tt> operator.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopFRRRailsExtractorOpe: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopFRRRailsExtractorOpe();

  /**
  * Get a more expansed Error message if run failed
  * The returned Error could be NULL if no Error has been detected
  * The Caller must managed the Error lifecycle and delete it
  */
  virtual void GetError(CATError *&Error) = 0;

  // Split The Body in two MonoDomainBody
  // The Two Bodies are created in the Same iTwoDomainBody's Factory
  //Utilities
  static int TwoDomainBodyToTwoBodiesMonoDomain(
    CATBody *iTwoDomainBody,
    CATBody *&oOneDomainBody1,
    CATBody *&oOneDomainBody2);

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopFRRRailsExtractorOpe(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopFRRRailsExtractorOpe *CATPGMCreateTopFRRRailsExtractorOpe(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iShellBody,
  CATLength iOriginalRadius);

#endif /* CATIPGMTopFRRRailsExtractorOpe_h_ */
