#ifndef CATIPGMCloneImplicitBodyTopOper_h_
#define CATIPGMCloneImplicitBodyTopOper_h_

// COPYRIGHT DASSAULT SYSTEMES 2022

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMImplicitTopOperator.h"

class CATBody;
class CATFace;
class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMCloneImplicitBodyTopOper;

/**
* Class defining an operator that clone a body with implicit body information attached to it.
* Journal is written in Modification mode (see the clone manager itself for more on this).
* Please check CATIPGMSmartDuplicateImplicitBodyTopOper instead which is used everywhere, refrain
* from using this operator unless you are sure the smart duplicate doesn't do what you want
* and you are familiar with when you should really use the CATCloneManager instead and this operator
* for bodies that would have implicit specs attached.
* <ul>
*     <li> A <tt>CATIPGMCloneImplicitBodyTopOper</tt> operator is created with the <tt>CATPGMCreateCloneImplicitBodyTopOper</tt> global function.
*     <li> It is the user's responsibility to release the operator after it has been used.
*     <li> The results are retrieved by the <tt>Get</tt> methods.
* </ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMCloneImplicitBodyTopOper: public CATIPGMImplicitTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMCloneImplicitBodyTopOper();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMCloneImplicitBodyTopOper(); // -> delete can't be called
};

/**
 * Creates a CATIPGMCloneImplicitBodyTopOper operator
 * @param iFactory
 * The factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt>
 * is <tt>NULL</tt>, it is not filled.
 * @param iBodyWithCavityToLattice
 * The pointer to the 2D body to offset (under progress, not yet available) or the 3D body to thick
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMCloneImplicitBodyTopOper *CATPGMCreateCloneImplicitBodyTopOper(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBodyWithCavityToLattice);

#endif /* CATIPGMCloneImplicitBodyTopOper_h_ */
