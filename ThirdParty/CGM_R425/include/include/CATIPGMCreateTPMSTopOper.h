#ifndef CATIPGMCreateTPMSTopOper_h_
#define CATIPGMCreateTPMSTopOper_h_

// COPYRIGHT DASSAULT SYSTEMES 2022

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMImplicitTopOperator.h"

#include "CATCollec.h"

class CATBody;
class CATFace;
class CATGeoFactory;
class CATTopData;
class CATVolume;
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMCreateTPMSTopOper;

/**
* Class defining an operator that put implicit specifications for a TPMS based lattice structure on the specified volume,
* <ul>
*     <li> A <tt>CATIPGMCreateTPMSTopOper</tt> operator is created with the <tt>CATPGMCreateCreateTPMSTopOper</tt> global function.
*     <li> It is the user's responsibility to release the operator after it has been used.
*     <li> The results are retrieved by the <tt>Get</tt> methods.
* </ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMCreateTPMSTopOper: public CATIPGMImplicitTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMCreateTPMSTopOper();

  //=============================================================================
  // Settings
  //=============================================================================
  /**
  * Volume to which attach implicit specs.
  * @param a CATVolume specifying the cavity to which we need to attach specs.
  */
  virtual void SetVolume(CATVolume *iCavityVolume) = 0;

  /**
  * Let you set the type of Triply Periodic Minimal Surface you want to use
  * to build a lattice structure. This refers directly to the expression
  * template that will be used to specify the implicit geometry of the
  * structure. For values see CATTPMSType.h
  * enum CATTPMSType {
  * UNDEFINED_TPMS_TYPE = 0,
  * GYROID = 1, NEOVIUS = 2, LIDINOID = 3, IWP = 4, FISHER_KOCH = 5, DIAMOND = 6,
  * TWO_EMPTY_SUBDOMAINS_GYROID = 7, TWO_EMPTY_SUBDOMAINS_NEOVIUS = 8,
  * TWO_EMPTY_SUBDOMAINS_LIDINOID = 9, TWO_EMPTY_SUBDOMAINS_IWP = 10,
  * TWO_EMPTY_SUBDOMAINS_FISHER_KOCH = 11, TWO_EMPTY_SUBDOMAINS_DIAMOND = 12
  * };
  * @param iTPMSType a type of TPMS to be used to build lattice structure.
  */
  virtual void SetTPMSType(const int iTPMSType) = 0;

  /**
  * This argument let you specify how frequently the pattern will
  * appear in a given volume.
  * @param iPeriodicity periodicity of the lattice structure.
  */
  virtual void SetPeriodicity(const double iPeriodicity) = 0;

  /**
   * Some rare TPMS pattern need more than one 'frequency' argument. For most
   * patterns (Gyroids...) these parameters won't be used.
   * @param iArgIndex index of the periodicity argument of the lattice structure.
   * @param iPeriodicityN value of the periodicity argument associated with index N.
   */
  virtual void SetArg(const int iArgIndex, const double iValue) = 0;

  /**
  * This parameter let you specify the width of the structure
  * that you want to get in the end (when partitioned body
  * with implicit specs is transformed to explicit geometry).
  * @param iWidth width of the desired structure.
  */
  virtual void SetThickness(const double iWidth) = 0;

  /**
 * In case you want to create a lattice structure with 3 domains, 2 separated empty
 * ones and one full (solid), you often need to specify contact faces for each empty domains.
 * This method allows you to set the contact faces for the first empty domain.
 * This information is used only when you use a DoubleCavity... CATTPMSType
 */
  virtual void SetSubDomain1OpenFaces(CATLISTP(CATFace) &iCavity1ContactFaces) = 0;

  /**
   * In case you want to create a lattice structure with 3 domains, 2 separated empty
   * ones and one full (solid), you often need to specify contact faces for each empty domains.
   * This method allows you to set the contact faces for the second empty domain.
   * This information is used only when you use a DoubleCavity... CATTPMSType
   */
  virtual void SetSubDomain2OpenFaces(CATLISTP(CATFace) &iCavity2ContactFaces) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMCreateTPMSTopOper(); // -> delete can't be called
};

/**
 * Creates a CATIPGMCreateTPMSTopOper operator
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
ExportedByCATGMOperatorsInterfaces CATIPGMCreateTPMSTopOper *CATPGMCreateCreateTPMSTopOper(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iInputBody);

#endif /* CATIPGMCreateTPMSTopOper_h_ */
