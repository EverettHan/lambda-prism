#ifndef CATIPGMSmartDuplicateImplicitBodyTopOper_h_
#define CATIPGMSmartDuplicateImplicitBodyTopOper_h_

// COPYRIGHT DASSAULT SYSTEMES 2022

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMImplicitTopOperator.h"

class CATBody;
class CATFace;
class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMSmartDuplicateImplicitBodyTopOper;

/**
* Class defining an operator that creates an approximate rolling-ball offset of a polyhedral body
* <ul>
*     <li> A <tt>CATICGMPolyhedralRoughOffset</tt> operator is created with the <tt>CATCGMCreatePolyhedralRoughOffset</tt> global function.
*     <li> It is the user's responsibility to release the operator after it has been used.
*     <li> The results are retrieved by the <tt>Get</tt> methods.
* </ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMSmartDuplicateImplicitBodyTopOper: public CATIPGMImplicitTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMSmartDuplicateImplicitBodyTopOper();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSmartDuplicateImplicitBodyTopOper(); // -> delete can't be called
};

/**
 * Creates a CATIPGMSmartDuplicateImplicitBodyTopOper operator
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
ExportedByCATGMOperatorsInterfaces CATIPGMSmartDuplicateImplicitBodyTopOper *CATPGMCreateSmartDuplicateImplicitBodyTopOper(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBodyWithCavityToLattice);

#endif /* CATIPGMSmartDuplicateImplicitBodyTopOper_h_ */
