#ifndef CATICGMPolyhedralSweepDraft_h_
#define CATICGMPolyhedralSweepDraft_h_

// COPYRIGHT DASSAULT SYSTEMES 2021

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMPolyTopOperator.h"
#include "CATTopDefine.h"

class CATBody;
class CATGeoFactory;
class CATTopData;
class CATMathDirection;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMPolyhedralSweepDraft;

/**
* Class defining an operator that creates a polyhedral sweep surface from a wire body composed of polycurves
* <ul>
*     <li> A <tt>CATICGMPolyhedralSweepDraft</tt> operator is created with the <tt>CATCGMCreatePolyhedralSweepDraft</tt> global function.
*     <li> It is the user's responsibility to release the operator after it has been used.
*     <li> The results are retrieved by the <tt>Get</tt> methods.
* </ul>
*/

class ExportedByCATGMOperatorsInterfaces CATICGMPolyhedralSweepDraft: public CATICGMPolyTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMPolyhedralSweepDraft();

  //=============================================================================
  // Profile Settings
  //=============================================================================
  // Define successive strips of Sweep,
  // the first one generated from the input wire body,
  // each next one generated from the opposite boundary of the previous strip
  //=============================================================================


  // -------------------------------------------------------------------------------------------
  // "Strip by strip" definition (constant angular parts of SweepDraft)
  // -------------------------------------------------------------------------------------------

  /**
  * Defines a new constant strip to sweep
  * @param iWireSide
  * The side (CATSideLeft / CATSideRight) on which the ruled strip has to be generated, according to the wire orientation and the draft direction
  * @param iRadianAngle
  * The radian angle between the opposite direction ("draft" convention) and the strip to generate :
  * all values in the range [ 0., CATPI ] will be accepted
  * @param iStripLength
  * The constant positive Length of the future ruled strip from the previous wire
  * This value has to be greater than the model tolerant resolution (0.1 mm for NormalRange), else returns 0.
  * @return
  * The integer value associated to the new strip definition, equals to the number of recorded strips including this one.
  * If the strip is not correctly defined (unknown or full side, angle out of range, length smaller than the tolerant resolution ...), 
  * or if this method is called after Run(), then it returns 0
  */
  virtual int AddStripWithLength(
    CATSide iWireSide,
    double iRadianAngle,
    double iStripLength) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMPolyhedralSweepDraft(); // -> delete can't be called
};

/**
 * Creates a CATICGMPolyhedralSweepDraft operator with a direction
 * @param iFactory
 * The factory of the geometry. 
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iWireBody
 * The pointer to the 1D body to guide the sweep
 * @param iDraftDirection
 * The mathematical direction to apply the draft angle (beginning from the opposite direction)
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMPolyhedralSweepDraft *CATCGMCreatePolyhedralSweepDraft(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iWireBody,
  const CATMathDirection &iDraftDirection);

#endif /* CATICGMPolyhedralSweepDraft_h_ */
