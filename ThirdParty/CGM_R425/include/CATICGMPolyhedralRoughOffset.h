#ifndef CATICGMPolyhedralRoughOffset_h_
#define CATICGMPolyhedralRoughOffset_h_

// COPYRIGHT DASSAULT SYSTEMES 2020

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMPolyTopOperator.h"

class CATBody;
class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMPolyhedralRoughOffset;

/**
* Class defining an operator that creates an approximate rolling-ball offset of a polyhedral body
* <ul>
*     <li> A <tt>CATICGMPolyhedralRoughOffset</tt> operator is created with the <tt>CATCGMCreatePolyhedralRoughOffset</tt> global function.
*     <li> It is the user's responsibility to release the operator after it has been used.
*     <li> The results are retrieved by the <tt>Get</tt> methods.
* </ul>
*/

class ExportedByCATGMOperatorsInterfaces CATICGMPolyhedralRoughOffset: public CATICGMPolyTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMPolyhedralRoughOffset();

  //=============================================================================
  // Settings
  //=============================================================================
  /**
  * Defines the signed offset value for all the faces of the input body.
  * This setting is mandatory and the operator will automatically fail if this method is not called before the computation
  * @param iOffsetValue
  * The signed offset value.
  * a positive value will offset volumes outwards (adding matter), and offset skins in a direction equal to their global orientation
  * a negative value will offset volumes inwards (removing matter), and offset skins in a direction opposite to their global orientation
  * a null offset value is totally forbidden, and a too small value regarding the body size may lead to a failure
  */
  virtual void SetOffsetValue(double iOffsetValue) = 0;

  /**
  * Defines a minimum level of accuracy among 3 modes : coarse, medium and fine
  * This option (not mandatory) allows the caller to speed up the computation of an approximate result (coarse mode)
  * or to improve the accuracy of the result in spite of poorer performances (fine mode)
  * The medium level is the default value of accuracy (recommended)
  * The operator can decide internally to increase the accuracy level in order to assure the maximum deviation is always smaller than the offset value
  */
  virtual void SetMinimumAccuracyLevel(int iCoarseMediumOrFine123) = 0;

  //=============================================================================
  // Get additional information after Run
  //=============================================================================
  /**
  * Retrieves the information of maximum deviation from the expected offset value
  * This deviation is supposed to be smaller than the expected offset value, in order to guarantee there is no clash between input and offset bodies
  * This deviation depends on both the offset value and the level of accuracy
  * @param oMaxDeviation
  *   the maximum deviation between the expected offset value and the generated rough offset
  * @param ioComputedAccuracyLevel123
  *   optional argument to know the level of accuracy actually used for the operation.
  *   It allows the caller to know if a better accuracy has been forced internally to optimize the maximum deviation
  * @return [HRESULT]
  *   S_OK    if the maximum deviation has been correctly computed
  *   E_FAIL  if the requested offset value is too low and cannot be applied :
  *         it happens since there is a risk of intersection between input and offset bodies even if the best accuracy has been forced
  */
  virtual HRESULT GetMaxDeviation(
    double &oMaxDeviation,
    int *ioComputedAccuracyLevel123 = 0) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMPolyhedralRoughOffset(); // -> delete can't be called
};

/**
 * Creates a CATICGMPolyhedralRoughOffset operator
 * @param iFactory
 * The factory of the geometry. 
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iBodyToOffset
 * The pointer to the 2D body to offset (under progress, not yet available) or the 3D body to thick
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMPolyhedralRoughOffset *CATCGMCreatePolyhedralRoughOffset(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBodyToOffset);

#endif /* CATICGMPolyhedralRoughOffset_h_ */
