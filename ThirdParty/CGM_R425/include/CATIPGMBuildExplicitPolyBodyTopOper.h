#ifndef CATIPGMBuildExplicitPolyBodyTopOper_h_
#define CATIPGMBuildExplicitPolyBodyTopOper_h_

// COPYRIGHT DASSAULT SYSTEMES 2022

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMImplicitTopOperator.h"

#include "CATCollec.h"

class CATBody;
class CATFace;
class CATCell;
class CATGeoFactory;
class CATTopData;
class CATVolume;
class CATLISTP(CATVolume);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMBuildExplicitPolyBodyTopOper;

/**
* Class defining an operator that put implicit specifications for a bar graph lattice on the specified volume,
* with the provided LatticeNBModel (the bar graph that was previously given to old Lattice APIs in LatticeGMOperaots
* (i.e the bar graph might need to be trimmed previously)
* <ul>
*     <li> A <tt>CATIPGMBuildExplicitPolyBodyTopOper</tt> operator is created with the <tt>CATPGMCreateBuildExplicitPolyBodyTopOper</tt> global function.
*     <li> It is the user's responsibility to release the operator after it has been used.
*     <li> The results are retrieved by the <tt>Get</tt> methods.
* </ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMBuildExplicitPolyBodyTopOper: public CATIPGMImplicitTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMBuildExplicitPolyBodyTopOper();

  //=============================================================================
  // Settings
  //=============================================================================
  /**
  * Specify the smoothing mode for lattice geometry creation.
  * @param iSmoothingMode
  * The CATVRepType::SmoothingMode
  */
  virtual void SetSmoothingMode(const int iSmoothingMode) = 0;

  /**
  * Specify the smoothing mode for lattice geometry creation.
  * @param iSmoothingAmplitude
  * The amplitude of the smoothing that will be applied during geometry generation
  */
  virtual void SetSmoothingAmplitude(const double iSmoothingAmplitude) = 0;

  /** @nodoc
  */
  virtual void SetDiscretizationAccuracyLevel(const int i123DiscretizationAccuracyLevel) = 0;

  /**
  * Cavity to be filled with conformal lattice.
  * @param a CATVolume specifying the cavity to lattice.
  */
  virtual void SetCavities(const CATLISTP(CATVolume)& iCavityVolumes) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMBuildExplicitPolyBodyTopOper(); // -> delete can't be called
};

/**
 * Creates a CATIPGMBuildExplicitPolyBodyTopOper operator
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
ExportedByCATGMOperatorsInterfaces CATIPGMBuildExplicitPolyBodyTopOper *CATPGMCreateBuildExplicitPolyBodyTopOper(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBodyWithCavityToLattice);

#endif /* CATIPGMBuildExplicitPolyBodyTopOper_h_ */
