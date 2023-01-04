#ifndef CATIPGMCreateConformalLatticeTopOper_h_
#define CATIPGMCreateConformalLatticeTopOper_h_

// COPYRIGHT DASSAULT SYSTEMES 2022

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMImplicitTopOperator.h"

class CATBody;
class CATFace;
class CATGeoFactory;
class CATTopData;
class CATVolume;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMCreateConformalLatticeTopOper;

/**
* Class defining an operator that put implicit specifications for a conformal based lattice structure on the specified volume,
* <ul>
*     <li> A <tt>CATIPGMCreateConformalLatticeTopOper</tt> operator is created with the <tt>CATPGMCreateCreateConformalLatticeTopOper</tt> global function.
*     <li> It is the user's responsibility to release the operator after it has been used.
*     <li> The results are retrieved by the <tt>Get</tt> methods.
* </ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMCreateConformalLatticeTopOper: public CATIPGMImplicitTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMCreateConformalLatticeTopOper();

  //=============================================================================
  // Settings
  //=============================================================================
  /**
  * Desired bar length. Note that the resulting bar graph won't adhere to this but
  * will use instead this value as indicative of the bar length toward which most
  * bars should converge.
  * @param a double specifying the desired iBarLength
  */
  virtual void SetBarLength(const double iBarLength) = 0;

  /**
  * Desired bar radius. Bars of the resulting bar graph will have this radius
  * which will also be used for lattice geometry creation.
  * @param a double specifying the desired iBarLength
  */
  virtual void SetBarRadius(const double iBarRadius) = 0;

  /**
  * Cavity to be filled with conformal lattice.
  * @param a CATVolume specifying the cavity to lattice.
  */
  virtual void SetVolume(CATVolume *iCavityVolume) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMCreateConformalLatticeTopOper(); // -> delete can't be called
};

/**
 * Creates a CATIPGMCreateConformalLatticeTopOper operator
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
ExportedByCATGMOperatorsInterfaces CATIPGMCreateConformalLatticeTopOper *CATPGMCreateCATCreateConformalLatticeTopOper(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBodyWithCavityToLattice);

#endif /* CATIPGMCreateConformalLatticeTopOper_h_ */
