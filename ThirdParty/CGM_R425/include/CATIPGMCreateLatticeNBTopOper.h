#ifndef CATIPGMCreateLatticeNBTopOper_h_
#define CATIPGMCreateLatticeNBTopOper_h_

// COPYRIGHT DASSAULT SYSTEMES 2022

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMImplicitTopOperator.h"

class CATBody;
class CATFace;
class CATGeoFactory;
class CATTopData;
class CATVolume;
class LatticeNBModel;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMCreateLatticeNBTopOper;

/**
* Class defining an operator that put implicit specifications for a bar graph lattice on the specified volume,
* with the provided LatticeNBModel (the bar graph that was previously given to old Lattice APIs in LatticeGMOperaots
* (i.e the bar graph might need to be trimmed previously)
* <ul>
*     <li> A <tt>CATIPGMCreateLatticeNBTopOper</tt> operator is created with the <tt>CATPGMCreateCreateLatticeNBTopOper</tt> global function.
*     <li> It is the user's responsibility to release the operator after it has been used.
*     <li> The results are retrieved by the <tt>Get</tt> methods.
* </ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMCreateLatticeNBTopOper: public CATIPGMImplicitTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMCreateLatticeNBTopOper();

  //=============================================================================
  // Settings
  //=============================================================================
  /**
  * Volume to which attach implicit specs.
  * @param a CATVolume specifying the cavity to which we need to attach specs.
  */
  virtual void SetVolume(CATVolume *iCavityVolume) = 0;

  /**
  * The whole bar graph(not just a unit cell) for the lattice you want to create.
  * It should already be trimmed to fit cavity.
  * By passing a latticeNBModel you transfer it's ownership, don't delete or
  * release it on your side.
  * @param iLatticeNBModel a LatticeNBModel specifying the bars of the lattice
  */
  virtual void SetLatticeNBModel(LatticeNBModel* iLatticeNBModel) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMCreateLatticeNBTopOper(); // -> delete can't be called
};

/**
 * Creates a CATIPGMCreateLatticeNBTopOper operator
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
ExportedByCATGMOperatorsInterfaces CATIPGMCreateLatticeNBTopOper *CATPGMCreateCreateLatticeNBTopOper(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iInputBody);

#endif /* CATIPGMCreateLatticeNBTopOper_h_ */
