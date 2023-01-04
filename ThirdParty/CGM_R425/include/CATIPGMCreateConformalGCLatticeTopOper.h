#ifndef CATIPGMCreateConformalGCLatticeTopOper_h_
#define CATIPGMCreateConformalGCLatticeTopOper_h_

// COPYRIGHT DASSAULT SYSTEMES 2022

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMImplicitTopOperator.h"

class CATBody;
class CATFace;
class CATGeoFactory;
class CATTopData;
class CATVolume;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMCreateConformalGCLatticeTopOper;

/**
* Class defining an operator that put implicit specifications for a conformal based lattice structure on the specified volume,
* <ul>
*     <li> A <tt>CATIPGMCreateConformalGCLatticeTopOper</tt> operator is created with the <tt>CATPGMCreateCreateConformalGCLatticeTopOper</tt> global function.
*     <li> It is the user's responsibility to release the operator after it has been used.
*     <li> The results are retrieved by the <tt>Get</tt> methods.
* </ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMCreateConformalGCLatticeTopOper: public CATIPGMImplicitTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMCreateConformalGCLatticeTopOper();

  //=============================================================================
  // Settings
  //=============================================================================
  /**
  * Volume to which attach implicit specs.
  * @param a CATVolume specifying the cavity to which we need to attach specs.
  */
  virtual void SetVolume(CATVolume *iCavityVolume) = 0;

  /**
  * The Scalar Field expression (SFDag spec) to be associated with the ImplicitSurface
  * that will be created and associated with the specified volume of the body.
  * @param a CATVolume specifying the cavity to lattice.
  */
  virtual void SetExpression(const CATUnicodeString &iExpression) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMCreateConformalGCLatticeTopOper(); // -> delete can't be called
};

/**
 * Creates a CATIPGMCreateConformalGCLatticeTopOper operator
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
ExportedByCATGMOperatorsInterfaces CATIPGMCreateConformalGCLatticeTopOper *CATPGMCreateCreateConformalGCLatticeTopOper(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iInputBody);

#endif /* CATIPGMCreateConformalGCLatticeTopOper_h_ */
