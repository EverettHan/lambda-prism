#ifndef CATICGMTopCompatible_h_
#define CATICGMTopCompatible_h_

// COPYRIGHT DASSAULT SYSTEMES 2011

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopMultiResult.h"

class CATBody;
class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopCompatible;

/**
 * Class representing the topological operator which performs a compatible Boolean union of bodies.
 * <ul>
 * <li>Create it with the <tt>CATCGMCreateTopCompatibleForCGM</tt> global function.
 * <li>Run it ( only one time ).
 * <li>Get the resulting body with the <tt>GetResult</tt> method. 
 * If you do not want to keep this resulting body, 
 * use the @href CATICGMContainer#Remove method to remove it from the 
 * geometric factory, after the operator deletion.
 * <li>Release it after use with the <tt>Release</tt> method. 
 * </ul>
*/
class ExportedByCATGMOperatorsInterfaces CATICGMTopCompatible: public CATICGMTopMultiResult
{
public:
  /**
   * Constructor
   */
  CATICGMTopCompatible();

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopCompatible(); // -> delete can't be called
};

/**
* Creates the manifold body resulting from the compatible boolean union of two bodies.
* @param iFactory
* A pointer to the factory of the resulting body. 
* @param iTopData
* A pointer to the topological data.
* @param iBody1
* A pointer to the first body.
* @param iBody2
* A pointer to the second body.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMTopCompatible *CATCGMCreateCompatibleForCGM(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody1,
  CATBody *iBody2);

#endif /* CATICGMTopCompatible_h_ */
